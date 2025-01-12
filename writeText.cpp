#include <h3mparser/Map.h>
#include <h3mparser/writeText.h>

#include <array>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>
#include <type_traits>
#include <vector>

namespace
{
  constexpr std::string_view getBoolString(bool value) noexcept
  {
    return value ? "true" : "false";
  }
}

namespace h3m
{
  namespace
  {
    template<class T, class Enable = void>
    struct IsH3mStruct : std::true_type {};

    template<class T>
    struct IsH3mStruct<T, std::enable_if_t<std::is_integral_v<T> ||
                                           std::is_enum_v<T> ||
                                           std::is_same_v<T, std::string>>> : std::false_type {};

    template<class T, class Alloc>
    struct IsH3mStruct<std::vector<T, Alloc>> : std::false_type {};

    template<class T, std::size_t N>
    struct IsH3mStruct<std::array<T, N>> : std::false_type {};

    template<std::size_t NumBytes>
    struct IsH3mStruct<BitSet<NumBytes>> : std::false_type {};

    template<class T>
    consteval bool isH3mStruct()
    {
      return IsH3mStruct<T>::value;
    }

    template<class T, class Enable = void>
    class Writer
    {
    public:
      // \param num_spaces - current indent.
      void operator()(std::ostream& stream, const T& value, std::size_t num_spaces) const;
    };

    // Writes the textual representation of the specified value into the given stream.
    // \param stream - output stream.
    // \param value - input value.
    // \param num_spaces - indent for nested fields (if any).
    template<class T>
    void writeTextImpl(std::ostream& stream, const T& value, std::size_t num_spaces)
    {
      Writer<T> writer;
      writer(stream, value, num_spaces);
    }

    template<class T>
    void writeElement(std::ostream& stream, const T& value, std::size_t indent)
    {
      if constexpr (isH3mStruct<T>())
      {
        stream << "{\n";
      }
      const std::size_t new_indent = isH3mStruct<T>() ? (indent + 2) : indent;
      writeTextImpl(stream, value, new_indent);
      if constexpr (isH3mStruct<T>())
      {
        stream << '\n' << std::string(indent, ' ') << "}";
      }
    }

    template<class T>
    void writeSpan(std::ostream& stream, std::span<const T> values, std::size_t num_spaces)
    {
      const std::size_t num_elements = values.size();
      if (num_elements == 0)
      {
        stream << "[]";
        return;
      }
      stream << "[\n";
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        stream << std::string(num_spaces + 2, ' ');
        writeElement(stream, values[i], num_spaces + 2);
        if (i + 1 != num_elements)
        {
          stream << ',';
        }
        stream << '\n';
      }
      stream << std::string(num_spaces, ' ') << "]";
    }

    // Writes the name and the textual representation of the specified field into the given stream.
    // \param stream - output stream.
    // \param field_name - name of the field.
    // \param value - value of the field.
    // \param indent - the current indent, i.e. the number of spaces to write before the field name.
    // \param newline - if true, a newline character will be written after the field value.
    template<class T>
    void writeNamedField(std::ostream& stream,
                         std::string_view field_name,
                         const T& value,
                         std::size_t num_spaces,
                         bool newline = true)
    {
      constexpr std::string_view separator = isH3mStruct<T>() ? " " : ": ";
      const std::string whitespace(num_spaces, ' ');
      stream << whitespace << field_name << separator;
      writeElement(stream, value, num_spaces);
      if (newline)
      {
        stream << '\n';
      }
    }

    // Full specialization for std::string.
    template<>
    class Writer<std::string>
    {
    public:
      void operator()(std::ostream& stream, const std::string& value, std::size_t num_spaces) const
      {
        stream << '"' << value << '"';
      }
    };

    // Partial specialization for std::vector.
    template<class T, class Alloc>
    class Writer<std::vector<T, Alloc>>
    {
    public:
      void operator()(std::ostream& stream, const std::vector<T, Alloc>& value, std::size_t num_spaces) const
      {
        writeSpan<T>(stream, value, num_spaces);
      }
    };

    // Partial specialization for std::array.
    template<class T, std::size_t N>
    class Writer<std::array<T, N>>
    {
    public:
      void operator()(std::ostream& stream, const std::array<T, N>& value, std::size_t num_spaces) const
      {
        writeSpan<T>(stream, value, num_spaces);
      }
    };

    // Partial specialization for integer types.
    template<class T>
    class Writer<T, std::enable_if_t<std::is_integral_v<T>>>
    {
    public:
      void operator()(std::ostream& stream, const T& value, std::size_t num_spaces) const
      {
        if constexpr (std::is_same_v<T, char>)
        {
          stream << static_cast<int>(value);
        }
        else if constexpr (std::is_same_v<T, unsigned char>)
        {
          stream << static_cast<unsigned int>(value);
        }
        else
        {
          stream << value;
        }
      }
    };

    // Partial specialization for enum types.
    template<class T>
    class Writer<T, std::enable_if_t<std::is_enum_v<T>>>
    {
    public:
      void operator()(std::ostream& stream, const T& value, std::size_t num_spaces) const
      {
        writeTextImpl(stream, static_cast<std::underlying_type_t<T>>(value), num_spaces);
      }
    };

    // Partial specialization for BitSet.
    template<std::size_t NumBytes>
    class Writer<BitSet<NumBytes>>
    {
    public:
      void operator()(std::ostream& stream, const BitSet<NumBytes>& value, std::size_t num_spaces) const
      {
        writeTextImpl(stream, value.data(), num_spaces);
      }
    };

    // Full specialization for MapBasicInfo.
    template<>
    class Writer<MapBasicInfo>
    {
    public:
      void operator()(std::ostream& stream, const MapBasicInfo& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "is_playable", value.is_playable, num_spaces);
        writeNamedField(stream, "map_size", value.map_size, num_spaces);
        writeNamedField(stream, "has_two_levels", value.has_two_levels, num_spaces);
        writeNamedField(stream, "name", value.name, num_spaces);
        writeNamedField(stream, "description", value.description, num_spaces);
        writeNamedField(stream, "difficulty", value.difficulty, num_spaces);
        writeNamedField(stream, "max_hero_level", value.max_hero_level, num_spaces, false);
      }
    };

    // Full specialization for MainTown.
    template<>
    class Writer<MainTown>
    {
    public:
      void operator()(std::ostream& stream, const MainTown& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "generate_hero", value.generate_hero, num_spaces);
        writeNamedField(stream, "town_type", value.town_type, num_spaces);
        writeNamedField(stream, "x", value.x, num_spaces);
        writeNamedField(stream, "y", value.y, num_spaces);
        writeNamedField(stream, "z", value.z, num_spaces, false);
      }
    };

    // Full specialization for StartingHero.
    template<>
    class Writer<StartingHero>
    {
    public:
      void operator()(std::ostream& stream, const StartingHero& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "is_random", value.is_random, num_spaces);
        writeNamedField(stream, "type", value.type, num_spaces);
        writeNamedField(stream, "face", value.face, num_spaces);
        writeNamedField(stream, "name", value.name, num_spaces, false);
      }
    };

    // Full specialization for AdditionalPlayerInfo::HeroInfo.
    template<>
    class Writer<AdditionalPlayerInfo::HeroInfo>
    {
    public:
      void operator()(std::ostream& stream, const AdditionalPlayerInfo::HeroInfo& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "type", value.type, num_spaces);
        writeNamedField(stream, "name", value.name, num_spaces, false);
      }
    };

    // Full specialization for AdditionalPlayerInfo.
    template<>
    class Writer<AdditionalPlayerInfo>
    {
    public:
      void operator()(std::ostream& stream, const AdditionalPlayerInfo& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "num_placeholder_heroes", value.num_placeholder_heroes, num_spaces);
        writeNamedField(stream, "heroes", value.heroes, num_spaces, false);
      }
    };

    // Full specialization for PlayerSpecs.
    template<>
    class Writer<PlayerSpecs>
    {
    public:
      void operator()(std::ostream& stream, const PlayerSpecs& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "can_be_human", value.can_be_human, num_spaces);
        writeNamedField(stream, "can_be_computer", value.can_be_computer, num_spaces);
        writeNamedField(stream, "behavior", value.behavior, num_spaces);
        writeNamedField(stream, "customized_alignments", value.customized_alignments, num_spaces);
        writeNamedField(stream, "town_types", value.town_types, num_spaces);
        writeNamedField(stream, "town_conflux", value.town_conflux, num_spaces);
        writeNamedField(stream, "random_town", value.random_town, num_spaces);
        if (value.main_town)
        {
          writeNamedField(stream, "main_town", *value.main_town, num_spaces);
        }
        writeNamedField(stream, "starting_hero", value.starting_hero, num_spaces);
        writeNamedField(stream, "additional_info", value.additional_info, num_spaces, false);
      }
    };

    // Full specialization for VictoryCondition.
    template<>
    class Writer<VictoryCondition>
    {
    public:
      void operator()(std::ostream& stream, const VictoryCondition& value, std::size_t num_spaces) const
      {
        const bool has_details = value.type() != VictoryConditionType::Normal;
        writeNamedField(stream, "type", value.type(), num_spaces, has_details);
        //switch (value.type())
        //{
        //case LossConditionType::LoseTown:
        //  writeNamedField(stream, "details", *value.details<LossConditionType::LoseTown>(), num_spaces, false);
        //  break;
        //case LossConditionType::LoseHero:
        //  writeNamedField(stream, "details", *value.details<LossConditionType::LoseHero>(), num_spaces, false);
        //  break;
        //case LossConditionType::TimeExpires:
        //  writeNamedField(stream, "details", *value.details<LossConditionType::TimeExpires>(), num_spaces, false);
        //  break;
        //default:
        //  break;
        //}
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::LoseTown>.
    template<>
    class Writer<LossConditionDetails<LossConditionType::LoseTown>>
    {
    public:
      void operator()(std::ostream& stream,
                      const LossConditionDetails<LossConditionType::LoseTown>& value,
                      std::size_t num_spaces) const
      {
        writeNamedField(stream, "x", value.x, num_spaces);
        writeNamedField(stream, "y", value.y, num_spaces);
        writeNamedField(stream, "z", value.z, num_spaces, false);
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::LoseHero>.
    template<>
    class Writer<LossConditionDetails<LossConditionType::LoseHero>>
    {
    public:
      void operator()(std::ostream& stream,
                      const LossConditionDetails<LossConditionType::LoseHero>& value,
                      std::size_t num_spaces) const
      {
        writeNamedField(stream, "x", value.x, num_spaces);
        writeNamedField(stream, "y", value.y, num_spaces);
        writeNamedField(stream, "z", value.z, num_spaces, false);
      }
    };

    // Full specialization for LossConditionDetails<LossConditionType::TimeExpires>.
    template<>
    class Writer<LossConditionDetails<LossConditionType::TimeExpires>>
    {
    public:
      void operator()(std::ostream& stream,
                      const LossConditionDetails<LossConditionType::TimeExpires>& value,
                      std::size_t num_spaces) const
      {
        writeNamedField(stream, "days", value.days, num_spaces, false);
      }
    };

    // Full specialization for LossCondition.
    template<>
    class Writer<LossCondition>
    {
    public:
      void operator()(std::ostream& stream, const LossCondition& value, std::size_t num_spaces) const
      {
        const bool has_details = value.type() != LossConditionType::Normal;
        writeNamedField(stream, "type", value.type(), num_spaces, has_details);
        switch (value.type())
        {
        case LossConditionType::LoseTown:
          writeNamedField(stream, "details", *value.details<LossConditionType::LoseTown>(), num_spaces, false);
          break;
        case LossConditionType::LoseHero:
          writeNamedField(stream, "details", *value.details<LossConditionType::LoseHero>(), num_spaces, false);
          break;
        case LossConditionType::TimeExpires:
          writeNamedField(stream, "details", *value.details<LossConditionType::TimeExpires>(), num_spaces, false);
          break;
        default:
          break;
        }
      }
    };

    // Full specialization for TeamsInfo.
    template<>
    class Writer<TeamsInfo>
    {
    public:
      void operator()(std::ostream& stream, const TeamsInfo& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "num_teams", value.num_teams, num_spaces);
        writeNamedField(stream, "team_for_player", value.team_for_player, num_spaces, false);
      }
    };

    // Full specialization for HeroesAvailability.
    template<>
    class Writer<HeroesAvailability>
    {
    public:
      void operator()(std::ostream& stream, const HeroesAvailability& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "bitset", value.data, num_spaces, false);
      }
    };

    // Full specialization for MapAdditionalInfo::CustomHero.
    template<>
    class Writer<MapAdditionalInfo::CustomHero>
    {
    public:
      void operator()(std::ostream& stream, const MapAdditionalInfo::CustomHero& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "type", value.type, num_spaces);
        writeNamedField(stream, "face", value.face, num_spaces);
        writeNamedField(stream, "name", value.name, num_spaces);
        writeNamedField(stream, "can_hire", value.can_hire, num_spaces, false);
      }
    };

    // Full specialization for Rumor.
    template<>
    class Writer<Rumor>
    {
    public:
      void operator()(std::ostream& stream, const Rumor& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "name", value.name, num_spaces);
        writeNamedField(stream, "description", value.description, num_spaces, false);
      }
    };

    // Full specialization for MapAdditionalInfo.
    template<>
    class Writer<MapAdditionalInfo>
    {
    public:
      void operator()(std::ostream& stream, const MapAdditionalInfo& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "victory_condition", value.victory_condition, num_spaces);
        writeNamedField(stream, "loss_condition", value.loss_condition, num_spaces);
        if (value.teams)
        {
          writeNamedField(stream, "teams", *value.teams, num_spaces);
        }
        writeNamedField(stream, "heroes_availability", value.heroes_availability, num_spaces);
        writeNamedField(stream, "placeholder_heroes", value.placeholder_heroes, num_spaces);
        writeNamedField(stream, "custom_heroes", value.custom_heroes, num_spaces);
        writeNamedField(stream, "reserved", value.reserved, num_spaces);
        writeNamedField(stream, "artifacts_nonavailability", value.artifacts_nonavailability, num_spaces);
        writeNamedField(stream, "spells_nonavailability", value.spells_nonavailability, num_spaces);
        writeNamedField(stream, "skills_nonavailability", value.skills_nonavailability, num_spaces);
        writeNamedField(stream, "rumors", value.rumors, num_spaces, false);
        // TODO: write artifacts.
      }
    };

    // Full specialization for Tile.
    template<>
    class Writer<Tile>
    {
    public:
      void operator()(std::ostream& stream, const Tile& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "terrain_type", value.terrain_type, num_spaces);
        writeNamedField(stream, "terrain_sprite", value.terrain_sprite, num_spaces);
        writeNamedField(stream, "river_type", value.river_type, num_spaces);
        writeNamedField(stream, "river_sprite", value.river_sprite, num_spaces);
        writeNamedField(stream, "road_type", value.road_type, num_spaces);
        writeNamedField(stream, "road_sprite", value.road_sprite, num_spaces);
        writeNamedField(stream, "mirroring", value.mirroring, num_spaces, false);
      }
    };

    // Full specialization for Map.
    template<>
    class Writer<Map>
    {
    public:
      void operator()(std::ostream& stream, const Map& value, std::size_t num_spaces) const
      {
        writeNamedField(stream, "format", value.format, num_spaces);
        writeNamedField(stream, "basic_info", value.basic_info, num_spaces);
        writeNamedField(stream, "players", value.players, num_spaces);
        writeNamedField(stream, "additional_info", value.additional_info, num_spaces);
        writeNamedField(stream, "tiles", value.tiles, num_spaces, false);
      }
    };

  }

  void writeText(std::ostream& stream, const Map& map)
  {
    writeTextImpl(stream, map, 0);
  }
}
