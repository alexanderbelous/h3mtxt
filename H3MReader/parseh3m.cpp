#include <h3mtxt/H3MReader/parseh3m.h>

#include <h3mtxt/H3MReader/readHeroArtifacts.h>
#include <h3mtxt/H3MReader/readObjectDetails.h>
#include <h3mtxt/H3MReader/readPrimarySkills.h>
#include <h3mtxt/H3MReader/readResources.h>
#include <h3mtxt/H3MReader/readSecondarySkillsVector.h>
#include <h3mtxt/H3MReader/readTimedEventBase.h>
#include <h3mtxt/H3MReader/readVictoryCondition.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <cstddef>
#include <istream>
#include <span>
#include <stdexcept>
#include <type_traits>

namespace h3m
{
namespace
{

MapBasicInfo readMapBasicInfo(std::istream& stream)
{
  MapBasicInfo basic_info;
  basic_info.is_playable = readBool(stream);
  basic_info.map_size = readUint<std::uint32_t>(stream);
  basic_info.has_two_levels = readBool(stream);
  basic_info.name = readString(stream);
  basic_info.description = readString(stream);
  basic_info.difficulty = readEnum<MapDifficulty>(stream);
  basic_info.max_hero_level = readUint8(stream);
  return basic_info;
}

MainTown readMainTown(std::istream& stream)
{
  MainTown main_town;
  main_town.generate_hero = readBool(stream);
  main_town.town_type = readEnum<TownType>(stream);
  main_town.x = readUint8(stream);
  main_town.y = readUint8(stream);
  main_town.z = readUint8(stream);
  return main_town;
}

StartingHero readStartingHero(std::istream& stream)
{
  StartingHero starting_hero;
  starting_hero.is_random = readBool(stream);
  starting_hero.type = readEnum<HeroType>(stream);
  starting_hero.face = readUint8(stream);
  starting_hero.name = readString(stream);
  return starting_hero;
}

AdditionalPlayerInfo readAdditionalPlayerInfo(std::istream& stream)
{
  AdditionalPlayerInfo additional_info;
  additional_info.num_placeholder_heroes = readUint8(stream);
  const std::uint32_t num_heroes = readUint<std::uint32_t>(stream);
  additional_info.heroes.reserve(num_heroes);
  for (std::uint32_t i = 0; i < num_heroes; ++i)
  {
    AdditionalPlayerInfo::HeroInfo hero;
    hero.type = readEnum<HeroType>(stream);
    hero.name = readString(stream);
    additional_info.heroes.push_back(std::move(hero));
  }
  return additional_info;
}

PlayerSpecs readPlayerSpecs(std::istream& stream)
{
  PlayerSpecs player;
  player.can_be_human = readBool(stream);
  player.can_be_computer = readBool(stream);
  player.behavior = readEnum<PlayerBehavior>(stream);
  player.customized_alignments = readUint8(stream);
  player.allowed_alignments.town_types = readBitSet<2>(stream);
  player.random_town = readUint8(stream);
  const bool has_main_town = readBool(stream);
  if (has_main_town)
  {
    player.main_town = readMainTown(stream);
  }
  player.starting_hero = readStartingHero(stream);
  if (shouldHaveAdditionalPlayerInfo(player))
  {
    player.additional_info = readAdditionalPlayerInfo(stream);
  }
  return player;
}

LossCondition readLossCondition(std::istream& stream)
{
  const LossConditionType loss_condition_type = readEnum<LossConditionType>(stream);
  switch (loss_condition_type)
  {
  case LossConditionType::LoseTown:
  {
    LossConditionDetails<LossConditionType::LoseTown> details;
    details.x = readUint8(stream);
    details.y = readUint8(stream);
    details.z = readUint8(stream);
    return details;
  }
  case LossConditionType::LoseHero:
  {
    LossConditionDetails<LossConditionType::LoseHero> details;
    details.x = readUint8(stream);
    details.y = readUint8(stream);
    details.z = readUint8(stream);
    return details;
  }
  case LossConditionType::TimeExpires:
  {
    LossConditionDetails<LossConditionType::TimeExpires> details;
    details.days = readUint<std::uint16_t>(stream);
    return details;
  }
  case LossConditionType::Normal:
    return LossConditionDetails<LossConditionType::Normal>();
  default:
    throw std::runtime_error("Invalid loss condition type.");
  }
}

std::optional<TeamsInfo> readTeamsInfo(std::istream& stream)
{
  const std::uint8_t num_teams = readUint8(stream);
  if (num_teams == 0)
  {
    return std::nullopt;
  }
  TeamsInfo teams_info;
  teams_info.num_teams = num_teams;
  for (int i = 0; i < 8; ++i)
  {
    teams_info.team_for_player[i] = readUint8(stream);
  }
  return teams_info;
}

MapAdditionalInfo::CustomHero readCustomHero(std::istream& stream)
{
  MapAdditionalInfo::CustomHero custom_hero;
  custom_hero.type = readEnum<HeroType>(stream);
  custom_hero.face = readUint8(stream);
  custom_hero.name = readString(stream);
  custom_hero.can_hire = readBitSet<1>(stream);
  return custom_hero;
}

Rumor readRumor(std::istream& stream)
{
  Rumor rumor;
  rumor.name = readString(stream);
  rumor.description = readString(stream);
  return rumor;
}

HeroSettings readHeroSettings(std::istream& stream)
{
  HeroSettings settings;
  if (const Bool has_experience = readBool(stream))
  {
    settings.experience = readUint<std::uint32_t>(stream);
  }
  if (const Bool has_secondary_skills = readBool(stream))
  {
    settings.secondary_skills = readSecondarySkillsVector<std::uint32_t>(stream);
  }
  if (const Bool has_artifacts = readBool(stream))
  {
    settings.artifacts = readHeroArtifacts(stream);
  }
  if (const Bool has_biography = readBool(stream))
  {
    settings.biography = readString(stream);
  }
  settings.gender = readEnum<Gender>(stream);
  if (const Bool has_spells = readBool(stream))
  {
    settings.spells = readBitSet<9>(stream);
  }
  if (const Bool has_primary_skills = readBool(stream))
  {
    settings.primary_skills = readPrimarySkills(stream);
  }
  return settings;
}

MapAdditionalInfo readMapAdditionalInfo(std::istream& stream)
{
  MapAdditionalInfo additional_info;
  additional_info.victory_condition = readVictoryCondition(stream);
  additional_info.loss_condition = readLossCondition(stream);
  additional_info.teams = readTeamsInfo(stream);
  additional_info.heroes_availability.data = readBitSet<20>(stream);
  // Read placeholder heroes.
  const std::uint32_t num_placeholder_heroes = readUint<std::uint32_t>(stream);
  additional_info.placeholder_heroes.reserve(num_placeholder_heroes);
  for (std::uint32_t i = 0; i < num_placeholder_heroes; ++i)
  {
    additional_info.placeholder_heroes.push_back(readEnum<HeroType>(stream));
  }
  // Read custom heroes.
  const std::uint8_t num_custom_heroes = readUint8(stream);
  additional_info.custom_heroes.reserve(num_custom_heroes);
  for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
  {
    additional_info.custom_heroes.push_back(readCustomHero(stream));
  }
  // Read reserved data.
  additional_info.reserved = readReservedData<31>(stream);
  additional_info.artifacts_nonavailability = readBitSet<18>(stream);
  additional_info.spells_nonavailability = readBitSet<9>(stream);
  additional_info.skills_nonavailability = readBitSet<4>(stream);
  // Read rumors.
  const std::uint32_t num_rumors = readUint<std::uint32_t>(stream);
  additional_info.rumors.reserve(num_rumors);
  for (std::uint32_t i = 0; i < num_rumors; ++i)
  {
    additional_info.rumors.push_back(readRumor(stream));
  }
  // Read heroes
  for (std::uint32_t i = 0; i < kNumHeroes; ++i)
  {
    if (const Bool has_settings = readBool(stream))
    {
      additional_info.heroes_settings[static_cast<HeroType>(i)] = readHeroSettings(stream);
    }
  }
  return additional_info;
}

Tile readTile(std::istream& stream)
{
  Tile tile;
  tile.terrain_type = readEnum<TerrainType>(stream);
  tile.terrain_sprite = readUint8(stream);
  tile.river_type = readEnum<RiverType>(stream);
  tile.river_sprite = readUint8(stream);
  tile.road_type = readEnum<RoadType>(stream);
  tile.road_sprite = readUint8(stream);
  tile.mirroring = readUint8(stream);
  return tile;
}

ObjectAttributes readObjectAttributes(std::istream& stream)
{
  ObjectAttributes result;
  result.def = readString(stream);
  result.passability = readByteArray<6>(stream);
  result.actionability = readByteArray<6>(stream);
  result.allowed_landscapes = readUint<std::uint16_t>(stream);
  result.landscape_group = readUint<std::uint16_t>(stream);
  result.object_class = readEnum<ObjectClass>(stream);
  result.object_number = readUint<std::uint32_t>(stream);
  result.object_group = readEnum<ObjectGroup>(stream);
  result.is_ground = readBool(stream);
  result.unknown = readReservedData<16>(stream);
  return result;
}

GlobalEvent readGlobalEvent(std::istream& stream)
{
  GlobalEvent global_event;
  readTimedEventBase(stream, global_event);
  return global_event;
}

}

Map parseh3m(std::istream& stream, bool read_objects_details)
{
  Map map;
  map.format = readEnum<MapFormat>(stream);
  if (map.format != MapFormat::ShadowOfDeath)
  {
    throw std::runtime_error("Unsupported MapFormat. Only ShadowOfDeath is supported.");
  }
  map.basic_info = readMapBasicInfo(stream);
  for (int i = 0; i < kMaxPlayers; ++i)
  {
    map.players[i] = readPlayerSpecs(stream);
  }
  map.additional_info = readMapAdditionalInfo(stream);
  // Read tiles.
  const std::size_t num_tiles = countTiles(map.basic_info);
  map.tiles.reserve(num_tiles);
  for (std::size_t i = 0; i != num_tiles; ++i)
  {
    map.tiles.push_back(readTile(stream));
  }
  // Read objects' attributes.
  const std::uint32_t num_object_kinds = readUint<std::uint32_t>(stream);
  map.objects_attributes.reserve(num_object_kinds);
  for (std::uint32_t i = 0; i < num_object_kinds; ++i)
  {
    map.objects_attributes.push_back(readObjectAttributes(stream));
  }
  // TODO: remove this after all ObjectDetails are supported.
  if (!read_objects_details)
  {
    return map;
  }
  // Read objects' details.
  const std::uint32_t num_objects = readUint<std::uint32_t>(stream);
  map.objects_details.reserve(num_objects);
  for (std::uint32_t i = 0; i < num_objects; ++i)
  {
    map.objects_details.push_back(readObjectDetails(stream, map.objects_attributes));
  }
  // Read global events.
  const std::uint32_t num_global_events = readUint<std::uint32_t>(stream);
  map.global_events.reserve(num_global_events);
  for (std::uint32_t i = 0; i < num_global_events; ++i)
  {
    map.global_events.push_back(readGlobalEvent(stream));
  }
  // Read padding data.
  map.padding = readReservedData<124>(stream);
  return map;
}

}
