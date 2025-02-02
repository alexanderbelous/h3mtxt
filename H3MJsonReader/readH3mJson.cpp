#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <json/json.h>

#include <istream>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <type_traits>

namespace h3m
{
  namespace
  {
    template<class T, class Enable = void>
    struct JsonReader
    {
      static_assert(false, "NotImplemented.");
    };

    // Utility wrapper.
    template<class T>
    T fromJson(const Json::Value& value)
    {
      return JsonReader<T>{}(value);
    }

    // Utility function for parsing a single field of the input JSON value.
    // \param value - input JSON value.
    // \param field_name - name of the field.
    // \return the value of the specified field as T.
    // \throw std::runtime_error if @value doesn't have a field named @field_name.
    template<class T>
    T readField(const Json::Value& value, std::string_view field_name)
    {
      if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
      {
        return fromJson<T>(*field);
      }
      throw std::runtime_error("readH3mJson(): missing field " + std::string(field_name));
    }

    // Utility function for reading optional fields.
    template<class T>
    std::optional<T> readOptionalField(const Json::Value& value, std::string_view field_name)
    {
      if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
      {
        return fromJson<T>(*field);
      }
      return std::nullopt;
    }

    // Full specialization for bool.
    template<>
    struct JsonReader<bool>
    {
      bool operator()(const Json::Value& value) const
      {
        if (!value.isBool())
        {
          throw std::runtime_error("readH3mJson(): expected bool, got " + value.toStyledString());
        }
        return value.asBool();
      }
    };

    // Full specialization for std::string.
    template<>
    struct JsonReader<std::string>
    {
      std::string operator()(const Json::Value& value) const
      {
        if (!value.isString())
        {
          throw std::runtime_error("readH3mJson(): expected std::string, got " + value.toStyledString());
        }
        return value.asString();
      }
    };

    // Partial specialization for integer types.
    template<class T>
    struct JsonReader <T, std::enable_if_t<std::is_integral_v<T>>>
    {
      T operator()(const Json::Value& value) const
      {
        using LargestInt = std::conditional_t<std::is_signed_v<T>, Json::LargestInt, Json::LargestUInt>;
        if (!value.isIntegral())
        {
          throw std::runtime_error("readH3mJson(): expected an integral type, got " + value.toStyledString());
        }
        LargestInt integral_value{};
        if constexpr (std::is_signed_v<T>)
        {
          integral_value = value.asLargestInt();
        }
        else
        {
          integral_value = value.asLargestUInt();
        }
        // Check that the number fits in T.
        if (integral_value > std::numeric_limits<T>::max() || integral_value < std::numeric_limits<T>::min())
        {
          throw std::runtime_error("readH3mJson(): value is out of range: " + std::to_string(integral_value));
        }
        return static_cast<T>(integral_value);
      }
    };

    // Partial specialization for enum types.
    template<class T>
    struct JsonReader <T, std::enable_if_t<std::is_enum_v<T>>>
    {
      T operator()(const Json::Value& value) const
      {
        return static_cast<T>(fromJson<std::underlying_type_t<T>>(value));
      }
    };

    // Partial specialization for std::array.
    template<class T, std::size_t N>
    struct JsonReader<std::array<T, N>>
    {
      std::array<T, N> operator()(const Json::Value& value) const
      {
        if (!value.isArray())
        {
          throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
        }
        if (value.size() != N)
        {
          throw std::runtime_error("readH3mJson(): expected array of " + std::to_string(N) +
                                   " elements, got an array of " + std::to_string(value.size()) + " elements");
        }
        std::array<T, N> result;
        for (std::size_t i = 0; i < N; ++i)
        {
          result[i] = fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]);
        }
        return result;
      }
    };

    // Partial specialization for std::vector.
    template<class T, class Alloc>
    struct JsonReader<std::vector<T, Alloc>>
    {
      std::vector<T, Alloc> operator()(const Json::Value& value) const
      {
        if (!value.isArray())
        {
          throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
        }
        const std::size_t num_elements = value.size();
        std::vector<T, Alloc> result;
        result.reserve(num_elements);
        for (std::size_t i = 0; i < num_elements; ++i)
        {
          result.push_back(fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]));
        }
        return result;
      }
    };

    template<>
    struct JsonReader<MapBasicInfo>
    {
      MapBasicInfo operator()(const Json::Value& value) const
      {
        MapBasicInfo basic_info{};
        basic_info.is_playable = readField<Bool>(value, "is_playable");
        basic_info.map_size = readField<std::uint32_t>(value, "map_size");
        basic_info.has_two_levels = readField<Bool>(value, "has_two_levels");
        basic_info.name = readField<std::string>(value, "name");
        basic_info.description = readField<std::string>(value, "description");
        basic_info.difficulty = readField<MapDifficulty>(value, "difficulty");
        basic_info.max_hero_level = readField<std::uint8_t>(value, "max_hero_level");
        return basic_info;
      }
    };

    template<>
    struct JsonReader<MainTown>
    {
      MainTown operator()(const Json::Value& value) const
      {
        MainTown main_town {};
        main_town.generate_hero = readField<Bool>(value, "generate_hero");
        main_town.town_type = readField<TownType>(value, "town_type");
        main_town.x = readField<std::uint8_t>(value, "x");
        main_town.y = readField<std::uint8_t>(value, "y");
        main_town.z = readField<std::uint8_t>(value, "z");
        return main_town;
      }
    };

    template<>
    struct JsonReader<StartingHero>
    {
      StartingHero operator()(const Json::Value& value) const
      {
        StartingHero hero {};
        hero.is_random = readField<Bool>(value, "is_random");
        hero.type = readField<HeroType>(value, "type");
        hero.portrait = readField<HeroPortrait>(value, "portrait");
        hero.name = readField<std::string>(value, "name");
        return hero;
      }
    };

    template<>
    struct JsonReader<AdditionalPlayerInfo::HeroInfo>
    {
      AdditionalPlayerInfo::HeroInfo operator()(const Json::Value& value) const
      {
        AdditionalPlayerInfo::HeroInfo info{};
        info.type = readField<HeroType>(value, "type");
        info.name = readField<std::string>(value, "name");
        return info;
      }
    };

    template<>
    struct JsonReader<AdditionalPlayerInfo>
    {
      AdditionalPlayerInfo operator()(const Json::Value& value) const
      {
        AdditionalPlayerInfo info {};
        info.num_placeholder_heroes = readField<std::uint8_t>(value, "num_placeholder_heroes");
        info.heroes = readField<std::vector<AdditionalPlayerInfo::HeroInfo>>(value, "heroes");
        return info;
      }
    };

    template<>
    struct JsonReader<PlayerSpecs>
    {
      PlayerSpecs operator()(const Json::Value& value) const
      {
        PlayerSpecs player {};
        player.can_be_human = readField<Bool>(value, "can_be_human");
        player.can_be_computer = readField<Bool>(value, "can_be_computer");
        player.behavior = readField<PlayerBehavior>(value, "behavior");
        player.customized_alignments = readField<Bool>(value, "customized_alignments");
        // TODO:
        //player.allowed_alignments = readField<AllowedAlignments>(value, "allowed_alignments");
        player.random_town = readField<Bool>(value, "random_town");
        player.main_town = readOptionalField<MainTown>(value, "main_town");
        player.starting_hero = readField<StartingHero>(value, "starting_hero");
        if (shouldHaveAdditionalPlayerInfo(player))
        {
          player.additional_info = readField<AdditionalPlayerInfo>(value, "additional_info");
        }
        return player;
      }
    };

    template<>
    struct JsonReader<Tile>
    {
      Tile operator()(const Json::Value& value) const
      {
        Tile tile {};
        tile.terrain_type = readField<TerrainType>(value, "terrain_type");
        tile.terrain_sprite = readField<std::uint8_t>(value, "terrain_sprite");
        tile.river_type = readField<RiverType>(value, "river_type");
        tile.river_sprite = readField<std::uint8_t>(value, "river_sprite");
        tile.road_type = readField<RoadType>(value, "road_type");
        tile.road_sprite = readField<std::uint8_t>(value, "road_sprite");
        tile.mirroring = readField<std::uint8_t>(value, "mirroring");
        return tile;
      }
    };

    template<>
    struct JsonReader<Map>
    {
      Map operator()(const Json::Value& value) const
      {
        Map map;
        map.format = readField<MapFormat>(value, "format");
        map.basic_info = readField<MapBasicInfo>(value, "basic_info");
        map.players = readField<std::array<PlayerSpecs, kMaxPlayers>>(value, "players");
        map.tiles = readField<std::vector<Tile>>(value, "tiles");
        // TODO: read the rest of the fields.
        return map;
      }
    };
  }

  Map readH3mJson(std::istream& stream)
  {
    Json::Value root;
    {
      Json::CharReaderBuilder builder;
      builder["collectComments"] = false;
      Json::String errs;
      if (!parseFromStream(builder, stream, &root, &errs))
      {
        throw std::runtime_error("readH3mJson(): " + errs);
      }
    }
    return fromJson<Map>(root);
  }
}
