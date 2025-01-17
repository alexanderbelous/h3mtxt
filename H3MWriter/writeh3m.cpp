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
    class H3MWriter
    {
    public:
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
    class H3MWriter<std::uint8_t>
    {
    public:
      void operator()(std::ostream& stream, std::uint8_t value) const
      {
        stream.put(static_cast<char>(value));
      }
    };

    // Partial specialization for integer types.
    template<class T>
    class H3MWriter<T, std::enable_if_t<std::is_integral_v<T>>>
    {
    public:
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
    class H3MWriter<T, std::enable_if_t<std::is_enum_v<T>>>
    {
    public:
      void operator()(std::ostream& stream, T value) const
      {
        writeData(stream, static_cast<std::underlying_type_t<T>>(value));
      }
    };

    // Full specialization for std::string.
    template<>
    class H3MWriter<std::string>
    {
    public:
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

    // Partial specialization for std::array<std::uint8_t, N>.
    // TODO: generalize this to any instantiation of std::array. In H3M arrays of known
    // width are always encoded as a sequence of individually encoded elements (the size
    // of the array is not encoded).
    template<std::size_t N>
    class H3MWriter<std::array<std::uint8_t, N>>
    {
    public:
      void operator()(std::ostream& stream, const std::array<std::uint8_t, N>& value) const
      {
        stream.write(reinterpret_cast<const char*>(value.data()), N);
      }
    };

    // Partial specialization for ReservedData<N>.
    template<std::size_t N>
    class H3MWriter<ReservedData<N>>
    {
    public:
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

    // Partial specialization for BitSet.
    template<std::size_t NumBytes>
    class H3MWriter<BitSet<NumBytes>>
    {
    public:
      void operator()(std::ostream& stream, const BitSet<NumBytes>& value) const
      {
        writeData(stream, value.data());
      }
    };

    // Full specialization for MapBasicInfo.
    template<>
    class H3MWriter<MapBasicInfo>
    {
    public:
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

    // Full specialization for MainTown.
    template<>
    class H3MWriter<MainTown>
    {
    public:
      void operator()(std::ostream& stream, const MainTown& value) const
      {
        writeData(stream, value.generate_hero);
        writeData(stream, value.town_type);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    // Full specialization for StartingHero.
    template<>
    class H3MWriter<StartingHero>
    {
    public:
      void operator()(std::ostream& stream, const StartingHero& value) const
      {
        writeData(stream, value.is_random);
        writeData(stream, value.type);
        writeData(stream, value.face);
        writeData(stream, value.name);
      }
    };

    // Full specialization for AdditionalPlayerInfo::HeroInfo.
    template<>
    class H3MWriter<AdditionalPlayerInfo::HeroInfo>
    {
    public:
      void operator()(std::ostream& stream, const AdditionalPlayerInfo::HeroInfo& value) const
      {
        writeData(stream, value.type);
        writeData(stream, value.name);
      }
    };

    // Full specialization for AdditionalPlayerInfo.
    template<>
    class H3MWriter<AdditionalPlayerInfo>
    {
    public:
      void operator()(std::ostream& stream, const AdditionalPlayerInfo& value) const
      {
        if (value.heroes.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in AdditionalPlayerInfo.heroes");
        }
        writeData(stream, value.num_placeholder_heroes);
        writeData(stream, static_cast<std::uint32_t>(value.heroes.size()));
        for (const AdditionalPlayerInfo::HeroInfo& hero : value.heroes)
        {
          writeData(stream, hero);
        }
      }
    };

    // Full specialization for PlayerSpecs.
    template<>
    class H3MWriter<PlayerSpecs>
    {
    public:
      void operator()(std::ostream& stream, const PlayerSpecs& value) const
      {
        writeData(stream, value.can_be_human);
        writeData(stream, value.can_be_computer);
        writeData(stream, value.behavior);
        writeData(stream, value.customized_alignments);
        writeData(stream, value.allowed_alignments.town_types);
        writeData(stream, value.random_town);
        writeData(stream, value.main_town.has_value());
        if (value.main_town.has_value())
        {
          writeData(stream, *value.main_town);
        }
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

    // Full specialization for VictoryConditionDetails<VictoryConditionType::AcquireArtifact>.
    template<>
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>
    {
    public:
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.artifact_type);
      }
    };

    // Full specialization for VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>.
    template<>
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>
    {
    public:
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.creature_type);
        writeData(stream, value.count);
      }
    };

    // Full specialization for VictoryConditionDetails<VictoryConditionType::AccumulateResources>.
    template<>
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>
    {
    public:
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateResources>& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.resource_type);
        writeData(stream, value.amount);
      }
    };

    // Full specialization for VictoryConditionDetails<VictoryConditionType::UpgradeTown>.
    template<>
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>
    {
    public:
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

    // Partial specialization for VictoryConditionDetails<VictoryConditionType::BuildGrail>,
    //                            VictoryConditionDetails<VictoryConditionType::DefeatHero>,
    //                            VictoryConditionDetails<VictoryConditionType::CaptureTown> and
    //                            VictoryConditionDetails<VictoryConditionType::DefeatMonster>.
    template<class T>
    class H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::BuildGrail>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatHero>> || 
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::CaptureTown>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatMonster>>>>
    {
    public:
      void operator()(std::ostream& stream, const T& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    // Partial specialization for VictoryConditionDetails<VictoryConditionType::FlagDwellings> and
    //                            VictoryConditionDetails<VictoryConditionType::FlagMines>.
    template<class T>
    class H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagDwellings>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagMines>>>>
    {
    public:
      void operator()(std::ostream& stream, const T& value) const
      {
        writeSpecialVictoryConditionBase(stream, value);
      }
    };

    // Full specialization for VictoryConditionDetails<VictoryConditionType::TransportArtifact>.
    template<>
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>
    {
    public:
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
    class H3MWriter<VictoryConditionDetails<VictoryConditionType::Normal>>
    {
    public:
      void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::Normal>& value) const
      {
      }
    };

    // Full specialization for VictoryCondition.
    template<>
    class H3MWriter<VictoryCondition>
    {
    public:
      void operator()(std::ostream& stream, const VictoryCondition& victory_condition) const
      {
        writeData(stream, victory_condition.type());
        std::visit(DataWriter(stream), victory_condition.details);
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::LoseTown>.
    template<>
    class H3MWriter<LossConditionDetails<LossConditionType::LoseTown>>
    {
    public:
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseTown>& value) const
      {
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::LoseHero>.
    template<>
    class H3MWriter<LossConditionDetails<LossConditionType::LoseHero>>
    {
    public:
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseHero>& value) const
      {
        writeData(stream, value.x);
        writeData(stream, value.y);
        writeData(stream, value.z);
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::TimeExpires>.
    template<>
    class H3MWriter<LossConditionDetails<LossConditionType::TimeExpires>>
    {
    public:
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::TimeExpires>& value) const
      {
        writeData(stream, value.days);
      }
    };

    template<>
    class H3MWriter<LossConditionDetails<LossConditionType::Normal>>
    {
    public:
      void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::Normal>& value) const
      {
      }
    };

    // Full specialization for LossCondition.
    template<>
    class H3MWriter<LossCondition>
    {
    public:
      void operator()(std::ostream& stream, const LossCondition& loss_condition) const
      {
        writeData(stream, loss_condition.type());
        std::visit(DataWriter(stream), loss_condition.details);
      }
    };

    // Full specialization for std::optional<TeamsInfo>.
    template<>
    class H3MWriter<std::optional<TeamsInfo>>
    {
    public:
      void operator()(std::ostream& stream, const std::optional<TeamsInfo>& value) const
      {
        // value->num_teams shouldn't be 0 if value != std::nullopt. It's not a critical error, though -
        // we will just ignore value->team_for_player in this case.
        const std::uint8_t num_teams = value.has_value() ? value->num_teams : std::uint8_t{ 0 };
        writeData(stream, num_teams);
        if (num_teams != 0)
        {
          for (std::uint8_t team : value->team_for_player)
          {
            writeData(stream, team);
          }
        }
      }
    };

    // Full specialization for HeroesAvailability.
    template<>
    class H3MWriter<HeroesAvailability>
    {
    public:
      void operator()(std::ostream& stream, const HeroesAvailability& value) const
      {
        writeData(stream, value.data);
      }
    };

    // Full specialization for MapAdditionalInfo::CustomHero.
    template<>
    class H3MWriter<MapAdditionalInfo::CustomHero>
    {
    public:
      void operator()(std::ostream& stream, const MapAdditionalInfo::CustomHero& value) const
      {
        writeData(stream, value.type);
        writeData(stream, value.face);
        writeData(stream, value.name);
        writeData(stream, value.can_hire);
      }
    };

    // Full specialization for Rumor.
    template<>
    class H3MWriter<Rumor>
    {
    public:
      void operator()(std::ostream& stream, const Rumor& value) const
      {
        writeData(stream, value.name);
        writeData(stream, value.description);
      }
    };

    // Full specialization for SecondarySkill.
    template<>
    class H3MWriter<SecondarySkill>
    {
    public:
      void operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const
      {
        writeData(stream, secondary_skill.type);
        writeData(stream, secondary_skill.level);
      }
    };

    // Full specialization for HeroArtifacts.
    template<>
    class H3MWriter<HeroArtifacts>
    {
    public:
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
        if (artifacts.backpack.size() > std::numeric_limits<std::uint16_t>::max())
        {
          throw std::runtime_error("Too many elements in HeroArtifacts.backpack.");
        }
        writeData(stream, static_cast<std::uint16_t>(artifacts.backpack.size()));
        for (std::uint16_t artifact : artifacts.backpack)
        {
          writeData(stream, artifact);
        }
      }
    };

    // Full specialization for PrimarySkills.
    template<>
    class H3MWriter<PrimarySkills>
    {
    public:
      void operator()(std::ostream& stream, const PrimarySkills& primary_skills) const
      {
        writeData(stream, primary_skills.attack);
        writeData(stream, primary_skills.defense);
        writeData(stream, primary_skills.spell_power);
        writeData(stream, primary_skills.knowledge);
      }
    };

    // Full specialization for HeroSettings.
    template<>
    class H3MWriter<HeroSettings>
    {
    public:
      void operator()(std::ostream& stream, const HeroSettings& settings) const
      {
        // Write experience.
        writeData(stream, settings.experience.has_value());
        if (settings.experience)
        {
          writeData(stream, *settings.experience);
        }
        // Write secondary skills.
        writeData(stream, settings.secondary_skills.has_value());
        if (settings.secondary_skills)
        {
          const std::vector<SecondarySkill>& secondary_skills = *settings.secondary_skills;
          if (secondary_skills.size() > std::numeric_limits<std::uint32_t>::max())
          {
            throw std::runtime_error("Too many elements in HeroSettings.secondary_skills.");
          }
          writeData(stream, static_cast<std::uint32_t>(secondary_skills.size()));
          for (const SecondarySkill& secondary_skill : secondary_skills)
          {
            writeData(stream, secondary_skill);
          }
        }
        // Write artifacts.
        writeData(stream, settings.artifacts.has_value());
        if (settings.artifacts)
        {
          writeData(stream, *settings.artifacts);
        }
        // Write biography.
        writeData(stream, settings.biography.has_value());
        if (settings.biography)
        {
          writeData(stream, *settings.biography);
        }
        writeData(stream, settings.gender);
        writeData(stream, settings.spells.has_value());
        if (settings.spells)
        {
          writeData(stream, *settings.spells);
        }
        writeData(stream, settings.primary_skills.has_value());
        if (settings.primary_skills)
        {
          writeData(stream, *settings.primary_skills);
        }
      }
    };

    // Full specialization for MapAdditionalInfo.
    template<>
    class H3MWriter<MapAdditionalInfo>
    {
    public:
      void operator()(std::ostream& stream, const MapAdditionalInfo& value) const
      {
        writeData(stream, value.victory_condition);
        writeData(stream, value.loss_condition);
        writeData(stream, value.teams);
        writeData(stream, value.heroes_availability);
        // Write placeholder_heroes.
        if (value.placeholder_heroes.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in MapAdditionalInfo.placeholder_heroes.");
        }
        writeData(stream, static_cast<std::uint32_t>(value.placeholder_heroes.size()));
        for (HeroType hero_type : value.placeholder_heroes)
        {
          writeData(stream, hero_type);
        }
        // Write custom_heroes.
        if (value.custom_heroes.size() > std::numeric_limits<std::uint8_t>::max())
        {
          throw std::runtime_error("Too many elements in MapAdditionalInfo.custom_heroes.");
        }
        writeData(stream, static_cast<std::uint8_t>(value.custom_heroes.size()));
        for (const MapAdditionalInfo::CustomHero& custom_hero : value.custom_heroes)
        {
          writeData(stream, custom_hero);
        }
        // Write reserved data.
        writeData(stream, value.reserved);
        writeData(stream, value.artifacts_nonavailability);
        writeData(stream, value.spells_nonavailability);
        writeData(stream, value.skills_nonavailability);
        // Write rumors.
        if (value.rumors.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in MapAdditionalInfo.rumors.");
        }
        writeData(stream, static_cast<std::uint32_t>(value.rumors.size()));
        for (const Rumor& rumor : value.rumors)
        {
          writeData(stream, rumor);
        }
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

    // Full specialization for Tile.
    template<>
    class H3MWriter<Tile>
    {
    public:
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

    // Full specialization for ObjectAttributes.
    template<>
    class H3MWriter<ObjectAttributes>
    {
    public:
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

    // Full specialization for ObjectDetails.
    template<>
    class H3MWriter<ObjectDetails>
    {
    public:
      void operator()(std::ostream& stream, const ObjectDetails& object_details) const
      {
        writeData(stream, object_details.x);
        writeData(stream, object_details.y);
        writeData(stream, object_details.z);
        writeData(stream, object_details.kind);
        writeData(stream, object_details.unknown);
        // TODO: implement.
        const bool has_details =
          std::get_if<ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>>(&object_details.details) == nullptr;
        if (has_details)
        {
          throw std::logic_error("NotImplemented.");
        }
      }
    };

    // Full specialization for GlobalEvent.
    template<>
    class H3MWriter<GlobalEvent>
    {
    public:
      void operator()(std::ostream& stream, const GlobalEvent& global_event) const
      {
        writeData(stream, global_event.name);
        writeData(stream, global_event.message);
        for (std::int32_t amount : global_event.resources.data)
        {
          writeData(stream, amount);
        }
        writeData(stream, global_event.affected_players.bitset);
        writeData(stream, global_event.applies_to_human);
        writeData(stream, global_event.applies_to_computer);
        writeData(stream, global_event.day_of_first_occurence);
        writeData(stream, global_event.repeat_after_days);
        writeData(stream, global_event.unknown);
      }
    };

    // Full specialization for Map.
    template<>
    class H3MWriter<Map>
    {
    public:
      void operator()(std::ostream& stream, const Map& map) const
      {
        writeData(stream, map.format);
        writeData(stream, map.basic_info);
        for (int i = 0; i < kMaxPlayers; ++i)
        {
          writeData(stream, map.players[i]);
        }
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
        if (map.objects_attributes.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in Map.objects_attributes.");
        }
        writeData(stream, static_cast<std::uint32_t>(map.objects_attributes.size()));
        for (const ObjectAttributes& object_attributes : map.objects_attributes)
        {
          writeData(stream, object_attributes);
        }
        // Write objects_details.
        if (map.objects_details.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in Map.objects_details.");
        }
        writeData(stream, static_cast<std::uint32_t>(map.objects_details.size()));
        for (const ObjectDetails& object_details : map.objects_details)
        {
          writeData(stream, object_details);
        }
        // Write global_events.
        if (map.global_events.size() > std::numeric_limits<std::uint32_t>::max())
        {
          throw std::runtime_error("Too many elements in Map.global_events.");
        }
        writeData(stream, static_cast<std::uint32_t>(map.global_events.size()));
        for (const GlobalEvent& global_event : map.global_events)
        {
          writeData(stream, global_event);
        }
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
