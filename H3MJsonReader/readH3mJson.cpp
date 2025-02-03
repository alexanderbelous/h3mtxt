#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <h3mtxt/H3MJsonReader/JsonReader.h>

#include <istream>
#include <stdexcept>

namespace h3m
{
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
  struct JsonReader<TownsBitmask>
  {
    TownsBitmask operator()(const Json::Value& value) const
    {
      TownsBitmask towns_bitmask {};
      towns_bitmask.bitset = fromJson<BitSet<2>>(value);
      return towns_bitmask;
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
      player.allowed_alignments = readField<TownsBitmask>(value, "allowed_alignments");
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
