#include <h3mtxt/H3MWriter/writeh3m.h>

#include <h3mtxt/Map/Map.h>

#include <array>
#include <iterator>
#include <limits>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string_view>

namespace h3m
{
  namespace
  {
    // Writes a little-endian unsigned integer.
    void writeUintImpl(std::ostream& stream, std::uintmax_t value, unsigned int num_bytes)
    {
      constexpr std::uintmax_t kMask = 0xFF;
      for (unsigned int i = 0; i < num_bytes; ++i)
      {
        const std::uint8_t byte = static_cast<std::uint8_t>(value & kMask);
        stream.put(static_cast<char>(byte));
        value >>= 8;
      }
    }

    template<class T, class Enable = void>
    struct H3MWriter
    {
      void operator()(std::ostream& stream, const T& value) const;
    };

    // Utility function for template argument deduction.
    template<class T>
    void writeData(std::ostream& stream, const T& value)
    {
      const H3MWriter<T> writer;
      writer(stream, value);
    }

    // FunctionObject that calls writeData() internally.
    // This is useful when serializing std::variant fields.
    class DataWriter
    {
    public:
      // Constructs a DataWriter that will write data into the given stream.
      // \param stream - output stream.
      explicit constexpr DataWriter(std::ostream& stream) noexcept:
        stream_(stream)
      {}

      // Writes the given value into the stream.
      // \param value - value to write.
      template<class T>
      void operator()(const T& value) const
      {
        writeData(stream_, value);
      }

    private:
      std::ostream& stream_;
    };

    // Full specialization for std::uint8_t.
    template<>
    struct H3MWriter<std::uint8_t>
    {
      void operator()(std::ostream& stream, std::uint8_t value) const
      {
        stream.put(static_cast<char>(value));
      }
    };

    // Partial specialization for integer types.
    template<class T>
    struct H3MWriter<T, std::enable_if_t<std::is_integral_v<T>>>
    {
      void operator()(std::ostream& stream, T value) const
      {
        // TODO: this is likely redundant, just cast to uintmax_t.
        // Widest integer type with the same signedness as T.
        using WidestInteger = std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>;
        // Cast the input value to WidestInteger first, then to uintmax_t.
        writeUintImpl(stream, static_cast<std::uintmax_t>(static_cast<WidestInteger>(value)), sizeof(T));
      }
    };

    // Partial specialization for enum types.
    template<class T>
    struct H3MWriter<T, std::enable_if_t<std::is_enum_v<T>>>
    {
      void operator()(std::ostream& stream, T value) const
      {
        writeData(stream, static_cast<std::underlying_type_t<T>>(value));
      }
    };

    // Full specialization for std::string.
    template<>
    struct H3MWriter<std::string>
    {
      void operator()(std::ostream& stream, const std::string& value) const
      {
        if (value.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("The string is too long.");
        }
        writeData(stream, static_cast<std::uint32_t>(value.size()));
        stream.write(value.data(), value.size());
      }
    };

    // Partial specialization for std::array<T, N>.
    // In H3M arrays of known width are always encoded as a sequence of
    // individually encoded elements (the size of the array is not encoded).
    template<class T, std::size_t N>
    struct H3MWriter<std::array<T, N>>
    {
      void operator()(std::ostream& stream, const std::array<T, N>& values) const
      {
        // Optimization for std::uint8_t and std::int8_t.
        if constexpr (std::is_same_v<T, std::uint8_t> || std::is_same_v<T, std::int8_t>)
        {
          stream.write(reinterpret_cast<const char*>(values.data()), N);
        }
        else
        {
          for (const T& element : values)
          {
            writeData(stream, element);
          }
        }
      }
    };

    // Partial specialization for std::optional.
    template<class T>
    struct H3MWriter<std::optional<T>>
    {
      void operator()(std::ostream& stream, const std::optional<T>& value) const
      {
        writeData(stream, static_cast<Bool>(value.has_value()));
        if (value.has_value())
        {
          writeData(stream, *value);
        }
      }
    };

    template<std::size_t N>
    struct H3MWriter<ReservedData<N>>
    {
      void operator()(std::ostream& stream, const ReservedData<N>& reserved_data) const
      {
        if (reserved_data.isExplicit())
        {
          stream.write(reinterpret_cast<const char*>(reserved_data.data()), N);
        }
        else
        {
          std::fill_n(std::ostreambuf_iterator<char>(stream), N, char{0});
        }
      }
    };

    template<std::size_t NumBytes>
    struct H3MWriter<BitSet<NumBytes>>
    {
      void operator()(std::ostream& stream, const BitSet<NumBytes>& value) const
      {
        writeData(stream, value.data());
      }
    };

    template<class T>
    struct H3MWriter<Resources<T>>
    {
      void operator()(std::ostream& stream, const Resources<T>& resources) const
      {
        writeData(stream, resources.data);
      }
    };

    template<>
    struct H3MWriter<AffectedPlayers>
    {
      void operator()(std::ostream& stream, const AffectedPlayers& affected_players) const
      {
        writeData(stream, affected_players.bitset);
      }
    };

    template<class VectorSizeType, class T, class Alloc>
    void writeVector(std::ostream& stream, const std::vector<T, Alloc>& vec, std::string_view field_name)
    {
      static_assert(std::is_integral_v<VectorSizeType> && std::is_unsigned_v<VectorSizeType>,
                    "VectorSizeType must be an unsigned integer type.");

      if (vec.size() > std::numeric_limits<VectorSizeType>::max())
      {
        std::string error_message = "Too many elements in";
        error_message.append(field_name);
        error_message.append(".");
        throw std::runtime_error(std::move(error_message));
      }
      writeData(stream, static_cast<VectorSizeType>(vec.size()));
      for (const T& element : vec)
      {
        writeData(stream, element);
      }
    }

    template<>
    struct H3MWriter<MapBasicInfo>
    {
      void operator()(std::ostream& stream, const MapBasicInfo& value) const
      {
        writeData(stream, value.is_playable);
        writeData(stream, value.map_size);
        writeData(stream, value.has_two_levels);
        writeData(stream, value.name);
        writeData(stream, value.description);
        writeData(stream, value.difficulty);
        writeData(stream, value.max_hero_level);
      }
    };

    template<>
    struct H3MWriter<MainTown>
    {
      void operator()(std::ostream& stream, const MainTown& value) const
      {
        writeData(stream, value.generate_hero);
        writeData(stream, value.town_type);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    template<>
    struct H3MWriter<StartingHero>
    {
      void operator()(std::ostream& stream, const StartingHero& value) const
      {
        writeData(stream, value.is_random);
        writeData(stream, value.type);
        writeData(stream, value.face);
        writeData(stream, value.name);
      }
    };

    template<>
    struct H3MWriter<AdditionalPlayerInfo::HeroInfo>
    {
      void operator()(std::ostream& stream, const AdditionalPlayerInfo::HeroInfo& value) const
      {
        writeData(stream, value.type);
        writeData(stream, value.name);
      }
    };

    template<>
    struct H3MWriter<AdditionalPlayerInfo>
    {
      void operator()(std::ostream& stream, const AdditionalPlayerInfo& value) const
      {
        writeData(stream, value.num_placeholder_heroes);
        writeVector<std::uint32_t>(stream, value.heroes, "AdditionalPlayerInfo.heroes");
      }
    };

    template<>
    struct H3MWriter<PlayerSpecs>
    {
      void operator()(std::ostream& stream, const PlayerSpecs& value) const
      {
        writeData(stream, value.can_be_human);
        writeData(stream, value.can_be_computer);
        writeData(stream, value.behavior);
        writeData(stream, value.customized_alignments);
        writeData(stream, value.allowed_alignments.town_types);
        writeData(stream, value.random_town);
        writeData(stream, value.main_town);
        writeData(stream, value.starting_hero);
        if (shouldHaveAdditionalPlayerInfo(value))
        {
          writeData(stream, value.additional_info);
        }
      }
    };

    // Writes common data of a special victory conditions into the given stream.
    // \param stream - output stream.
    // \param base - common data of a special victory condtion.
    void writeSpecialVictoryConditionBase(std::ostream& stream, const SpecialVictoryConditionBase& base)
    {
      writeData(stream, base.allow_normal_win);
      writeData(stream, base.applies_to_computer);
    }

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.artifact_type);
      }
    };

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.creature_type);
        writeData(stream, value.count);
      }
    };

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateResources>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.resource_type);
        writeData(stream, value.amount);
      }
    };

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::UpgradeTown>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
        writeData(stream, value.hall_level);
        writeData(stream, value.castle_level);
      }
    };

    template<class T>
    struct H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::BuildGrail>> ||
                                         std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatHero>> || 
                                         std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::CaptureTown>> ||
                                         std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatMonster>>>>
    {
      void operator()(std::ostream& stream, const T& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    template<class T>
    struct H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagDwellings>> ||
                                         std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagMines>>>>
    {
      void operator()(std::ostream& stream, const T& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
      }
    };

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::TransportArtifact>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.artifact_type);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    template<>
    struct H3MWriter<VictoryConditionDetails<VictoryConditionType::Normal>>
    {
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::Normal>& value) const
      {
      }
    };

    template<>
    struct H3MWriter<VictoryCondition>
    {
      void operator()(std::ostream& stream, const VictoryCondition& victory_condition) const
      {
        writeData(stream, victory_condition.type());
        std::visit(DataWriter(stream), victory_condition.details);
      }
    };

    template<>
    struct H3MWriter<LossConditionDetails<LossConditionType::LoseTown>>
    {
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseTown>& value) const
      {
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    template<>
    struct H3MWriter<LossConditionDetails<LossConditionType::LoseHero>>
    {
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseHero>& value) const
      {
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    template<>
    struct H3MWriter<LossConditionDetails<LossConditionType::TimeExpires>>
    {
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::TimeExpires>& value) const
      {
        writeData(stream, value.days);
      }
    };

    template<>
    struct H3MWriter<LossConditionDetails<LossConditionType::Normal>>
    {
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::Normal>& value) const
      {
      }
    };

    template<>
    struct H3MWriter<LossCondition>
    {
      void operator()(std::ostream& stream, const LossCondition& loss_condition) const
      {
        writeData(stream, loss_condition.type());
        std::visit(DataWriter(stream), loss_condition.details);
      }
    };

    template<>
    struct H3MWriter<TeamsInfo>
    {
      void operator()(std::ostream& stream, const TeamsInfo& teams) const
      {
        writeData(stream, teams.num_teams);
        if (teams.num_teams != 0)
        {
          writeData(stream, teams.team_for_player);
        }
      }
    };

    template<>
    struct H3MWriter<HeroesAvailability>
    {
      void operator()(std::ostream& stream, const HeroesAvailability& value) const
      {
        writeData(stream, value.data);
      }
    };

    template<>
    struct H3MWriter<MapAdditionalInfo::CustomHero>
    {
      void operator()(std::ostream& stream, const MapAdditionalInfo::CustomHero& value) const
      {
        writeData(stream, value.type);
        writeData(stream, value.face);
        writeData(stream, value.name);
        writeData(stream, value.can_hire);
      }
    };

    template<>
    struct H3MWriter<Rumor>
    {
      void operator()(std::ostream& stream, const Rumor& value) const
      {
        writeData(stream, value.name);
        writeData(stream, value.description);
      }
    };

    template<>
    struct H3MWriter<SecondarySkill>
    {
      void operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const
      {
        writeData(stream, secondary_skill.type);
        writeData(stream, secondary_skill.level);
      }
    };

    template<>
    struct H3MWriter<HeroArtifacts>
    {
      void operator()(std::ostream& stream, const HeroArtifacts& artifacts) const
      {
        writeData(stream, artifacts.headwear);
        writeData(stream, artifacts.shoulders);
        writeData(stream, artifacts.neck);
        writeData(stream, artifacts.right_hand);
        writeData(stream, artifacts.left_hand);
        writeData(stream, artifacts.torso);
        writeData(stream, artifacts.right_ring);
        writeData(stream, artifacts.left_ring);
        writeData(stream, artifacts.feet);
        writeData(stream, artifacts.misc1);
        writeData(stream, artifacts.misc2);
        writeData(stream, artifacts.misc3);
        writeData(stream, artifacts.misc4);
        writeData(stream, artifacts.device1);
        writeData(stream, artifacts.device2);
        writeData(stream, artifacts.device3);
        writeData(stream, artifacts.device4);
        writeData(stream, artifacts.spellbook);
        writeData(stream, artifacts.misc5);
        writeVector<std::uint16_t>(stream, artifacts.backpack, "HeroArtifacts.backpack");
      }
    };

    template<>
    struct H3MWriter<PrimarySkills>
    {
      void operator()(std::ostream& stream, const PrimarySkills& primary_skills) const
      {
        writeData(stream, primary_skills.attack);
        writeData(stream, primary_skills.defense);
        writeData(stream, primary_skills.spell_power);
        writeData(stream, primary_skills.knowledge);
      }
    };

    template<>
    struct H3MWriter<HeroSettings>
    {
      void operator()(std::ostream& stream, const HeroSettings& settings) const
      {
        writeData(stream, settings.experience);
        // Write secondary skills.
        writeData(stream, settings.secondary_skills.has_value());
        if (settings.secondary_skills)
        {
          writeVector<std::uint32_t>(stream, *settings.secondary_skills, "HeroSettings.secondary_skills");
        }
        writeData(stream, settings.artifacts);
        writeData(stream, settings.biography);
        writeData(stream, settings.gender);
        writeData(stream, settings.spells);
        writeData(stream, settings.primary_skills);
      }
    };

    template<>
    struct H3MWriter<MapAdditionalInfo>
    {
      void operator()(std::ostream& stream, const MapAdditionalInfo& value) const
      {
        writeData(stream, value.victory_condition);
        writeData(stream, value.loss_condition);
        writeData(stream, value.teams);
        writeData(stream, value.heroes_availability);
        writeVector<std::uint32_t>(stream, value.placeholder_heroes, "MapAdditionalInfo.placeholder_heroes");
        writeVector<std::uint8_t>(stream, value.custom_heroes, "MapAdditionalInfo.custom_heroes");
        writeData(stream, value.reserved);
        writeData(stream, value.artifacts_nonavailability);
        writeData(stream, value.spells_nonavailability);
        writeData(stream, value.skills_nonavailability);
        writeVector<std::uint32_t>(stream, value.rumors, "MapAdditionalInfo.rumors");
        // Write heroes' settings.
        for (std::uint8_t hero_idx = 0; hero_idx < kNumHeroes; ++hero_idx)
        {
          const HeroType hero_type = static_cast<HeroType>(hero_idx);
          const bool has_settings = value.heroes_settings.hasSettings(hero_type);
          writeData(stream, has_settings);
          if (has_settings)
          {
            writeData(stream, value.heroes_settings[hero_type]);
          }
        }
      }
    };

    template<>
    struct H3MWriter<Tile>
    {
      void operator()(std::ostream& stream, const Tile& value) const
      {
        writeData(stream, value.terrain_type);
        writeData(stream, value.terrain_sprite);
        writeData(stream, value.river_type);
        writeData(stream, value.river_sprite);
        writeData(stream, value.road_type);
        writeData(stream, value.road_sprite);
        writeData(stream, value.mirroring);
      }
    };

    template<>
    struct H3MWriter<ObjectAttributes>
    {
      void operator()(std::ostream& stream, const ObjectAttributes& value) const
      {
        writeData(stream, value.def);
        writeData(stream, value.passability);
        writeData(stream, value.actionability);
        writeData(stream, value.allowed_landscapes);
        writeData(stream, value.landscape_group);
        writeData(stream, value.object_class);
        writeData(stream, value.object_number);
        writeData(stream, value.object_group);
        writeData(stream, value.is_ground);
        writeData(stream, value.unknown);
      }
    };

    template<>
    struct H3MWriter<CreatureStack>
    {
      void operator()(std::ostream& stream, const CreatureStack& value) const
      {
        writeData(stream, value.type);
        writeData(stream, value.count);
      }
    };

    template<>
    struct H3MWriter<Guardians>
    {
      void operator()(std::ostream& stream, const Guardians& guardians) const
      {
        writeData(stream, guardians.message);
        writeData(stream, guardians.creatures);
        writeData(stream, guardians.unknown);
      }
    };

    void writeEventBase(std::ostream& stream, const EventBase& event)
    {
      writeData(stream, event.guardians);
      writeData(stream, event.experience);
      writeData(stream, event.spell_points);
      writeData(stream, event.morale);
      writeData(stream, event.luck);
      writeData(stream, event.resources);
      writeData(stream, event.primary_skills);
      writeVector<std::uint8_t>(stream, event.secondary_skills, "EventBase.secondary_skills");
      writeVector<std::uint8_t>(stream, event.artifacts, "EventBase.artifacts");
      writeVector<std::uint8_t>(stream, event.spells, "EventBase.spells");
      writeVector<std::uint8_t>(stream, event.creatures, "EventBase.creatures");
      writeData(stream, event.unknown);
    }

    // TODO: remove once specialized for each MetaObjectType.
    template<MetaObjectType T>
    struct H3MWriter<ObjectDetailsData<T>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<T>& data) const
      {
        throw std::logic_error("NotImplemented.");
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::ABANDONED_MINE>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::ABANDONED_MINE>& data) const
      {
        writeData(stream, data.potential_resources);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::ARTIFACT>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::ARTIFACT>& data) const
      {
        writeData(stream, data.guardians);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::EVENT>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::EVENT>& event) const
      {
        writeEventBase(stream, event);
        writeData(stream, event.affected_players);
        writeData(stream, event.applies_to_computer);
        writeData(stream, event.remove_after_first_visit);
        writeData(stream, event.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::GARRISON>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GARRISON>& garrison) const
      {
        writeData(stream, garrison.owner);
        writeData(stream, garrison.creatures);
        writeData(stream, garrison.can_remove_units);
        writeData(stream, garrison.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>& data) const
      {
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::GRAIL>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GRAIL>& grail) const
      {
        writeData(stream, grail.allowable_radius);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::HERO>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::HERO>& hero) const
      {
        writeData(stream, hero.absod_id);
        writeData(stream, hero.owner);
        writeData(stream, hero.type);
        writeData(stream, hero.name);
        writeData(stream, hero.experience);
        writeData(stream, hero.face);
        writeData(stream, static_cast<Bool>(hero.secondary_skills.has_value()));
        if (hero.secondary_skills)
        {
          writeVector<std::uint32_t>(stream, *hero.secondary_skills, "ObjectDetailsData<HERO>.secondary_skills");
        }
        writeData(stream, hero.creatures);
        writeData(stream, hero.formation);
        writeData(stream, hero.artifacts);
        writeData(stream, hero.patrol_radius);
        writeData(stream, hero.biography);
        writeData(stream, hero.gender);
        writeData(stream, hero.spells);
        writeData(stream, hero.primary_skills);
        writeData(stream, hero.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::MONSTER>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::MONSTER>& monster) const
      {
        writeData(stream, monster.absod_id);
        writeData(stream, monster.count);
        writeData(stream, monster.disposition);
        writeData(stream, static_cast<Bool>(monster.message_and_treasure.has_value()));
        if (monster.message_and_treasure)
        {
          writeData(stream, monster.message_and_treasure->message);
          writeData(stream, monster.message_and_treasure->resources);
          writeData(stream, monster.message_and_treasure->artifact);
        }
        writeData(stream, monster.never_flees);
        writeData(stream, monster.does_not_grow);
        writeData(stream, monster.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::PANDORAS_BOX>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::PANDORAS_BOX>& pandoras_box) const
      {
        writeEventBase(stream, pandoras_box);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>& hero) const
      {
        constexpr HeroType kRandomHeroType {0xFF};

        writeData(stream, hero.owner);
        writeData(stream, hero.type);
        if (hero.type == kRandomHeroType)
        {
          writeData(stream, hero.power_rating);
        }
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::RESOURCE>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::RESOURCE>& data) const
      {
        writeData(stream, data.guardians);
        writeData(stream, data.quantity);
        writeData(stream, data.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::SHRINE>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SHRINE>& shrine) const
      {
        writeData(stream, shrine.spell);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::SIGN>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SIGN>& sign) const
      {
        writeData(stream, sign.message);
        writeData(stream, sign.unknown);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::SPELL_SCROLL>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SPELL_SCROLL>& spell_scroll) const
      {
        writeData(stream, spell_scroll.guardians);
        writeData(stream, spell_scroll.spell);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>& data) const
      {
        writeData(stream, data.owner);
      }
    };

    template<>
    struct H3MWriter<ObjectDetailsData<MetaObjectType::WITCH_HUT>>
    {
      void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::WITCH_HUT>& witch_hut) const
      {
        writeData(stream, witch_hut.skills_availability);
      }
    };

    template<>
    struct H3MWriter<ObjectDetails>
    {
      void operator()(std::ostream& stream, const ObjectDetails& object_details) const
      {
        writeData(stream, object_details.x);
        writeData(stream, object_details.y);
        writeData(stream, object_details.z);
        writeData(stream, object_details.kind);
        writeData(stream, object_details.unknown);
        // TODO: Check that MetaObjectType in object_details.details matches the one in ObjectAttributes.
        object_details.details.visit(DataWriter(stream));
      }
    };

    template<>
    struct H3MWriter<GlobalEvent>
    {
      void operator()(std::ostream& stream, const GlobalEvent& global_event) const
      {
        writeData(stream, global_event.name);
        writeData(stream, global_event.message);
        writeData(stream, global_event.resources);
        writeData(stream, global_event.affected_players.bitset);
        writeData(stream, global_event.applies_to_human);
        writeData(stream, global_event.applies_to_computer);
        writeData(stream, global_event.day_of_first_occurence);
        writeData(stream, global_event.repeat_after_days);
        writeData(stream, global_event.unknown);
      }
    };

    template<>
    struct H3MWriter<Map>
    {
      void operator()(std::ostream& stream, const Map& map) const
      {
        writeData(stream, map.format);
        writeData(stream, map.basic_info);
        writeData(stream, map.players);
        writeData(stream, map.additional_info);
        // Write tiles.
        if (map.tiles.size() != countTiles(map.basic_info))
        {
          throw std::runtime_error("Wrong number of elements in Map.tiles.");
        }
        for (const Tile& tile : map.tiles)
        {
          writeData(stream, tile);
        }
        // Write objects_attributes.
        writeVector<std::uint32_t>(stream, map.objects_attributes, "Map.objects_attributes");
        // Write objects_details.
        writeVector<std::uint32_t>(stream, map.objects_details, "Map.objects_details");
        // Write global_events.
        writeVector<std::uint32_t>(stream, map.global_events, "Map.global_events");
        // Write padding data.
        writeData(stream, map.padding);
      }
    };

  }

  void writeh3m(std::ostream& stream, const Map& map)
  {
    writeData(stream, map);
  }
}
