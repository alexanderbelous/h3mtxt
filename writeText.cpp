#include <h3mtxt/writeText.h>

#include <h3mtxt/Map/Map.h>
#include <h3mtxt/TextWriter/ValueWriter.h>

#include <ostream>
#include <span>
#include <stdexcept>
#include <string_view>
#include <type_traits>

namespace Util_NS
{
  namespace
  {
    // FunctionObject that calls FieldsWriter::writeField() internally.
    // This is useful when writing std::variant fields.
    class NamedFieldWriter
    {
    public:
      constexpr NamedFieldWriter(FieldsWriter& out, std::string_view field_name) noexcept:
        out_(out),
        field_name_(field_name)
      {}

      template<class T>
      void operator()(const T& value) const
      {
        out_.writeField(field_name_, value);
      }

    private:
      FieldsWriter& out_;
      std::string_view field_name_;
    };

    // Helper class to pass map_size to ValueWriter when writing Map::tiles.
    class TilesWithMapSize
    {
    public:
      constexpr TilesWithMapSize(std::span<const h3m::Tile> tiles, std::uint32_t map_size, bool has_two_levels):
        tiles_(tiles),
        map_size_(map_size),
        has_two_levels_(has_two_levels)
      {
        const std::size_t num_levels = has_two_levels ? 2 : 1;
        const std::size_t expected_num_tiles = num_levels * map_size * map_size;
        if (tiles.size() != expected_num_tiles)
        {
          throw std::runtime_error("Wrong number of tiles in Map.tiles.");
        }
      }

      constexpr std::span<const h3m::Tile> tiles() const noexcept
      {
        return tiles_;
      }

      constexpr std::uint32_t mapSize() const noexcept
      {
        return map_size_;
      }

      constexpr bool hasTwoLevels() const noexcept
      {
        return has_two_levels_;
      }

    private:
      std::span<const h3m::Tile> tiles_;
      std::uint32_t map_size_ = 0;
      bool has_two_levels_ = false;
    };
  }

  template<std::size_t NumBytes>
  struct ValueWriter<h3m::BitSet<NumBytes>>
  {
    void operator()(IndentedTextWriter& out, const h3m::BitSet<NumBytes>& value)
    {
      writeValue(out, value.data());
    }
  };

  // Explicit specialization for std::array<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>
  // to print comments.
  template<>
  struct ValueWriter<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>>
  {
    void operator()(IndentedTextWriter& out, const std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>& players) const
    {
      ScopedArrayWriter<h3m::PlayerSpecs> array_writer = out.writeArray<h3m::PlayerSpecs>();
      for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        array_writer.writeComment(std::string{"Player "} + std::to_string(i));
        array_writer.writeElement(players[i]);
      }
    }
  };

  template<>
  struct ValueWriter<TilesWithMapSize>
  {
    void operator()(IndentedTextWriter& out, const TilesWithMapSize& value) const
    {
      const std::uint32_t num_levels = value.hasTwoLevels() ? 2 : 1;
      const std::uint32_t map_size = value.mapSize();
      const std::span<const h3m::Tile> tiles = value.tiles();
      ScopedArrayWriter<h3m::Tile> array_writer = out.writeArray<h3m::Tile>();
      auto iter = tiles.begin();
      for (std::uint32_t z = 0; z < num_levels; ++z)
      {
        for (std::uint32_t y = 0; y < map_size; ++y)
        {
          for (std::uint32_t x = 0; x < map_size; ++x)
          {
            // std::format() would've been nice here, but it still causes bloat, doesn't it? Check.
            array_writer.writeComment(std::string{"Tile ("} + std::to_string(x) + std::string{", "} +
                                      std::to_string(y) + std::string{", "} + std::to_string(z) + std::string{")"});
            array_writer.writeElement(*iter);
            ++iter;
          }
        }
      }
    }
  };

  template<>
  struct ValueWriter<h3m::HeroesAvailability>
  {
    void operator()(IndentedTextWriter& out, const h3m::HeroesAvailability& value) const
    {
      writeValue(out, value.data);
    }
  };

  template<>
  struct StructWriter<h3m::MapBasicInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const
    {
      out.writeField("is_playable", value.is_playable);
      out.writeField("map_size", value.map_size);
      out.writeField("has_two_levels", value.has_two_levels);
      out.writeField("name", value.name);
      out.writeField("description", value.description);
      out.writeField("difficulty", value.difficulty);
      out.writeField("max_hero_level", value.max_hero_level);
    }
  };

  template<>
  struct StructWriter<h3m::MainTown>
  {
    void operator()(FieldsWriter& out, const h3m::MainTown& value) const
    {
      out.writeField("generate_hero", value.generate_hero);
      out.writeField("town_type", value.town_type);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct StructWriter<h3m::StartingHero>
  {
    void operator()(FieldsWriter& out, const h3m::StartingHero& value) const
    {
      out.writeField("is_random", value.is_random);
      out.writeField("type", value.type);
      out.writeField("face", value.face);
      out.writeField("name", value.name);
    }
  };

  template<>
  struct StructWriter<h3m::AdditionalPlayerInfo::HeroInfo>
  {
    void operator()(FieldsWriter& out, const h3m::AdditionalPlayerInfo::HeroInfo& value) const
    {
      out.writeField("type", value.type);
      out.writeField("name", value.name);
    }
  };

  template<>
  struct StructWriter<h3m::AdditionalPlayerInfo>
  {
    void operator()(FieldsWriter& out, const h3m::AdditionalPlayerInfo& value) const
    {
      out.writeField("num_placeholder_heroes", value.num_placeholder_heroes);
      out.writeField("heroes", value.heroes);
    }
  };

  template<>
  struct StructWriter<h3m::PlayerSpecs>
  {
    void operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const
    {
      out.writeField("can_be_human", value.can_be_human);
      out.writeField("can_be_computer", value.can_be_computer);
      out.writeField("behavior", value.behavior);
      out.writeField("customized_alignments", value.customized_alignments);
      out.writeField("allowed_alignments", value.allowed_alignments.town_types);
      out.writeField("random_town", value.random_town);
      if (value.main_town)
      {
        out.writeField("main_town", *value.main_town);
      }
      out.writeField("starting_hero", value.starting_hero);
      if (h3m::shouldHaveAdditionalPlayerInfo(value))
      {
        out.writeField("additional_info", value.additional_info);
      }
    }
  };

  static void writeSpecialVictoryConditionBase(FieldsWriter& out, const h3m::SpecialVictoryConditionBase& base)
  {
    out.writeField("allow_normal_win", base.allow_normal_win);
    out.writeField("applies_to_computer", base.applies_to_computer);
  }

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("artifact_type", value.artifact_type);
    }
  };

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("creature_type", value.creature_type);
      out.writeField("count", value.count);
    }
  };

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("resource_type", value.resource_type);
      out.writeField("amount", value.amount);
    }
  };

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
      out.writeField("hall_level", value.hall_level);
      out.writeField("castle_level", value.castle_level);
    }
  };

  template<class T>
  struct StructWriter<T, std::enable_if_t<std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<class T>
  struct StructWriter<T, std::enable_if_t<std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>> ||
                                          std::is_same_v<T, h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
    }
  };

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(out, value);
      out.writeField("artifact_type", value.artifact_type);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct StructWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>& value) const
    {}
  };

  template<>
  struct StructWriter<h3m::VictoryCondition>
  {
    void operator()(FieldsWriter& out, const h3m::VictoryCondition& value) const
    {
      const bool has_details = value.type() != h3m::VictoryConditionType::Normal;
      out.writeField("type", value.type());
      if (has_details)
      {
        std::visit(NamedFieldWriter(out, "details"), value.details);
      }
    }
  };

  template<class T>
  struct StructWriter<T, std::enable_if_t<std::is_same_v<T, h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>> ||
                                          std::is_same_v<T, h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct StructWriter<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>& value) const
    {
      out.writeField("days", value.days);
    }
  };

  template<>
  struct StructWriter<h3m::LossConditionDetails<h3m::LossConditionType::Normal>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::LossConditionDetails<h3m::LossConditionType::Normal>& value) const
    {
    }
  };

  template<>
  struct StructWriter<h3m::LossCondition>
  {
    void operator()(FieldsWriter& out, const h3m::LossCondition& loss_condition) const
    {
      const bool has_details = loss_condition.type() != h3m::LossConditionType::Normal;
      out.writeField("type", loss_condition.type());
      if (has_details)
      {
        std::visit(NamedFieldWriter(out, "details"), loss_condition.details);
      }
    }
  };

  template<>
  struct StructWriter<h3m::TeamsInfo>
  {
    void operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const
    {
      out.writeField("num_teams", value.num_teams);
      out.writeField("team_for_player", value.team_for_player);
    }
  };

  template<>
  struct StructWriter<h3m::MapAdditionalInfo::CustomHero>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo::CustomHero& value) const
    {
      out.writeField("type", value.type);
      out.writeField("face", value.face);
      out.writeField("name", value.name);
      out.writeField("can_hire", value.can_hire);
    }
  };

  template<>
  struct StructWriter<h3m::Rumor>
  {
    void operator()(FieldsWriter& out, const h3m::Rumor& value) const
    {
      out.writeField("name", value.name);
      out.writeField("description", value.description);
    }
  };

  template<>
  struct StructWriter<h3m::SecondarySkill>
  {
    void operator()(FieldsWriter& out, const h3m::SecondarySkill& value) const
    {
      out.writeField("type", value.type);
      out.writeField("level", value.level);
    }
  };

  template<>
  struct StructWriter<h3m::HeroArtifacts>
  {
    void operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
    {
      out.writeField("headwear", value.headwear);
      out.writeField("shoulders", value.shoulders);
      out.writeField("neck", value.neck);
      out.writeField("right_hand", value.right_hand);
      out.writeField("left_hand", value.left_hand);
      out.writeField("torso", value.torso);
      out.writeField("right_ring", value.right_ring);
      out.writeField("left_ring", value.left_ring);
      out.writeField("feet", value.feet);
      out.writeField("misc1", value.misc1);
      out.writeField("misc2", value.misc2);
      out.writeField("misc3", value.misc3);
      out.writeField("misc4", value.misc4);
      out.writeField("device1", value.device1);
      out.writeField("device2", value.device2);
      out.writeField("device3", value.device3);
      out.writeField("device4", value.device4);
      out.writeField("spellbook", value.spellbook);
      out.writeField("misc5", value.misc5);
      out.writeField("backpack", value.backpack);
    }
  };

  template<>
  struct StructWriter<h3m::PrimarySkills>
  {
    void operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const
    {
      out.writeField("attack", value.attack);
      out.writeField("defense", value.defense);
      out.writeField("spell_power", value.spell_power);
      out.writeField("knowledge", value.knowledge);
    }
  };

  template<>
  struct StructWriter<h3m::HeroSettings>
  {
    void operator()(FieldsWriter& out, const h3m::HeroSettings& value) const
    {
      if (value.experience)
      {
        out.writeField("experience", *value.experience);
      }
      if (value.secondary_skills)
      {
        out.writeField("secondary_skills", *value.secondary_skills);
      }
      if (value.artifacts)
      {
        out.writeField("artifacts", *value.artifacts);
      }
      if (value.biography)
      {
        out.writeField("biography", *value.biography);
      }
      out.writeField("gender", value.gender);
      if (value.spells)
      {
        out.writeField("spells", *value.spells);
      }
      if (value.primary_skills)
      {
        out.writeField("primary_skills", *value.primary_skills);
      }
    }
  };

  template<>
  struct StructWriter<h3m::MapAdditionalInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const
    {
      out.writeField("victory_condition", value.victory_condition);
      out.writeField("loss_condition", value.loss_condition);
      if (value.teams)
      {
        out.writeField( "teams", *value.teams);
      }
      out.writeField("heroes_availability", value.heroes_availability);
      out.writeField("placeholder_heroes", value.placeholder_heroes);
      out.writeField("custom_heroes", value.custom_heroes);
      out.writeField("reserved", value.reserved);
      out.writeField("artifacts_nonavailability", value.artifacts_nonavailability);
      out.writeField("spells_nonavailability", value.spells_nonavailability);
      out.writeField("skills_nonavailability", value.skills_nonavailability);
      out.writeField("rumors", value.rumors);
      out.writeField("heroes_settings", value.heroes_settings.settings());
    }
  };

  template<>
  struct StructWriter<h3m::Tile>
  {
    void operator()(FieldsWriter& out, const h3m::Tile& value) const
    {
      out.writeField("terrain_type", value.terrain_type);
      out.writeField("terrain_sprite", value.terrain_sprite);
      out.writeField("river_type", value.river_type);
      out.writeField("river_sprite", value.river_sprite);
      out.writeField("road_type", value.road_type);
      out.writeField("road_sprite", value.road_sprite);
      out.writeField("mirroring", value.mirroring);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectAttributes>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectAttributes& value) const
    {
      out.writeField("def", value.def);
      out.writeField("passability", value.passability);
      out.writeField("actionability", value.actionability);
      out.writeField("allowed_landscapes", value.allowed_landscapes);
      out.writeField("landscape_group", value.landscape_group);
      out.writeField("object_class", value.object_class);
      out.writeField("object_number", value.object_number);
      out.writeField("object_group", value.object_group);
      out.writeField("is_ground", value.is_ground);
      out.writeField("unknown", value.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetails>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectDetails& object_details) const
    {
      // An object has details if its MetaObjectType is *not* GENERIC_NO_PROPERTIES.
      const bool has_details =
        std::get_if<h3m::ObjectDetailsData<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>(&object_details.details) == nullptr;

      out.writeField("x", object_details.x);
      out.writeField("y", object_details.y);
      out.writeField("z", object_details.z);
      out.writeField("kind", object_details.kind);
      out.writeField("unknown", object_details.unknown);
      if (has_details)
      {
        // TODO: impelement.
        throw std::runtime_error("NotImplemented.");
      }
    }
  };

  template<>
  struct StructWriter<h3m::GlobalEvent>
  {
    void operator()(FieldsWriter& out, const h3m::GlobalEvent& global_event) const
    {
      out.writeField("name", global_event.name);
      out.writeField("message", global_event.message);
      out.writeField("resources", global_event.resources);
      out.writeField("affected_players", global_event.affected_players);
      out.writeField("applies_to_human", global_event.applies_to_human);
      out.writeField("applies_to_computer", global_event.applies_to_computer);
      out.writeField("day_of_first_occurence", global_event.day_of_first_occurence);
      out.writeField("repeat_after_days", global_event.repeat_after_days);
      out.writeField("unknown", global_event.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::Map>
  {
    void operator()(FieldsWriter& out, const h3m::Map& map) const
    {
      out.writeField("format", map.format);
      out.writeField("basic_info", map.basic_info);
      out.writeField("players", map.players);
      out.writeField("additional_info", map.additional_info);
      // Not writing tiles directly because I want to write each tile's coordinates in a comment.
      out.writeField("tiles", TilesWithMapSize(map.tiles, map.basic_info.map_size, map.basic_info.has_two_levels));
      out.writeField("objects_attributes", map.objects_attributes);
      out.writeField("objects_details", map.objects_details);
      out.writeField("global_events", map.global_events);
      out.writeField("padding", map.padding);
    }
  };
}

namespace h3m
{
  void writeText(std::ostream& stream, const Map& map)
  {
    Util_NS::IndentedTextWriter writer(stream, 0);
    Util_NS::writeValue(writer, map);
  }
}
