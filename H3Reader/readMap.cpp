#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/readSecondarySkillsVector.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/Map.h>

namespace h3m::H3Reader_NS
{
  namespace
  {
    PlayerSpecs::HeroInfo readPlayerSpecsHeroInfo(std::istream& stream)
    {
      PlayerSpecs::HeroInfo hero;
      hero.type = readEnum<HeroType>(stream);
      hero.name = readString(stream);
      return hero;
    }

    MapAdditionalInfo::CustomHero readCustomHero(std::istream& stream)
    {
      MapAdditionalInfo::CustomHero custom_hero;
      custom_hero.type = readEnum<HeroType>(stream);
      custom_hero.portrait = readEnum<HeroPortrait>(stream);
      custom_hero.name = readString(stream);
      custom_hero.can_hire = readEnumBitmask<PlayerColor, 1>(stream);
      return custom_hero;
    }
  }

  MapBasicInfo readMapBasicInfo(std::istream& stream)
  {
    MapBasicInfo basic_info;
    basic_info.is_playable = readBool(stream);
    basic_info.map_size = readInt<std::uint32_t>(stream);
    basic_info.has_two_levels = readBool(stream);
    basic_info.name = readString(stream);
    basic_info.description = readString(stream);
    basic_info.difficulty = readEnum<MapDifficulty>(stream);
    basic_info.max_hero_level = readInt<std::uint8_t>(stream);
    return basic_info;
  }

  MainTown readMainTown(std::istream& stream)
  {
    MainTown main_town;
    main_town.generate_hero = readBool(stream);
    main_town.town_type = readEnum<TownType>(stream);
    main_town.x = readInt<std::uint8_t>(stream);
    main_town.y = readInt<std::uint8_t>(stream);
    main_town.z = readInt<std::uint8_t>(stream);
    return main_town;
  }

  StartingHero readStartingHero(std::istream& stream)
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>(stream);
    if (starting_hero.type != HeroType{0xFF})
    {
      starting_hero.portrait = readEnum<HeroPortrait>(stream);
      starting_hero.name = readString(stream);
    }
    return starting_hero;
  }

  PlayerSpecs readPlayerSpecs(std::istream& stream)
  {
    PlayerSpecs player;
    player.can_be_human = readBool(stream);
    player.can_be_computer = readBool(stream);
    player.behavior = readEnum<PlayerBehavior>(stream);
    player.customized_alignments = readInt<std::uint8_t>(stream);
    player.allowed_alignments.bitset = readBitSet<2>(stream);
    player.random_town = readInt<std::uint8_t>(stream);
    const bool has_main_town = readBool(stream);
    if (has_main_town)
    {
      player.main_town = readMainTown(stream);
    }
    player.has_random_heroes = readBool(stream);
    player.starting_hero = readStartingHero(stream);
    player.num_nonspecific_placeholder_heroes = readInt<std::uint8_t>(stream);
    const std::uint32_t num_heroes = readInt<std::uint32_t>(stream);
    player.heroes.reserve(num_heroes);
    for (std::uint32_t i = 0; i < num_heroes; ++i)
    {
      player.heroes.push_back(readPlayerSpecsHeroInfo(stream));
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
      details.x = readInt<std::uint8_t>(stream);
      details.y = readInt<std::uint8_t>(stream);
      details.z = readInt<std::uint8_t>(stream);
      return details;
    }
    case LossConditionType::LoseHero:
    {
      LossConditionDetails<LossConditionType::LoseHero> details;
      details.x = readInt<std::uint8_t>(stream);
      details.y = readInt<std::uint8_t>(stream);
      details.z = readInt<std::uint8_t>(stream);
      return details;
    }
    case LossConditionType::TimeExpires:
    {
      LossConditionDetails<LossConditionType::TimeExpires> details;
      details.days = readInt<std::uint16_t>(stream);
      return details;
    }
    case LossConditionType::Normal:
      return LossConditionDetails<LossConditionType::Normal>();
    default:
      throw std::runtime_error("Invalid loss condition type.");
    }
  }

  TeamsInfo readTeamsInfo(std::istream& stream)
  {
    TeamsInfo teams_info;
    teams_info.num_teams = readInt<std::uint8_t>(stream);
    if (teams_info.num_teams != 0)
    {
      for (int i = 0; i < 8; ++i)
      {
        teams_info.team_for_player[i] = readInt<std::uint8_t>(stream);
      }
    }
    return teams_info;
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
      settings.experience = readInt<std::uint32_t>(stream);
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
      settings.spells = readEnumBitmask<SpellType, 9>(stream);
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
    additional_info.heroes_availability = readEnumBitmask<HeroType, 20>(stream);
    // Read placeholder heroes.
    const std::uint32_t num_placeholder_heroes = readInt<std::uint32_t>(stream);
    additional_info.placeholder_heroes.reserve(num_placeholder_heroes);
    for (std::uint32_t i = 0; i < num_placeholder_heroes; ++i)
    {
      additional_info.placeholder_heroes.push_back(readEnum<HeroType>(stream));
    }
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>(stream);
    additional_info.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      additional_info.custom_heroes.push_back(readCustomHero(stream));
    }
    // Read reserved data.
    additional_info.reserved = readReservedData<31>(stream);
    additional_info.disabled_artifacts = readEnumBitmask<ArtifactType, 18>(stream);
    additional_info.disabled_spells = readEnumBitmask<SpellType, 9>(stream);
    additional_info.disabled_skills = readEnumBitmask<SecondarySkillType, 4>(stream);
    // Read rumors.
    const std::uint32_t num_rumors = readInt<std::uint32_t>(stream);
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
    tile.terrain_sprite = readInt<std::uint8_t>(stream);
    tile.river_type = readEnum<RiverType>(stream);
    tile.river_sprite = readInt<std::uint8_t>(stream);
    tile.road_type = readEnum<RoadType>(stream);
    tile.road_sprite = readInt<std::uint8_t>(stream);
    tile.mirroring = readInt<std::uint8_t>(stream);
    return tile;
  }

  ObjectAttributes readObjectAttributes(std::istream& stream)
  {
    ObjectAttributes result;
    result.def = readString(stream);
    result.passability = readByteArray<6>(stream);
    result.actionability = readByteArray<6>(stream);
    result.allowed_landscapes = readInt<std::uint16_t>(stream);
    result.landscape_group = readInt<std::uint16_t>(stream);
    result.object_class = readEnum<ObjectClass>(stream);
    result.object_number = readInt<std::uint32_t>(stream);
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

  Map readMap(std::istream& stream)
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
    const std::uint32_t num_object_kinds = readInt<std::uint32_t>(stream);
    map.objects_attributes.reserve(num_object_kinds);
    for (std::uint32_t i = 0; i < num_object_kinds; ++i)
    {
      map.objects_attributes.push_back(readObjectAttributes(stream));
    }
    // Read objects' details.
    const std::uint32_t num_objects = readInt<std::uint32_t>(stream);
    map.objects_details.reserve(num_objects);
    for (std::uint32_t i = 0; i < num_objects; ++i)
    {
      map.objects_details.push_back(readObjectDetails(stream,
                                                      map.objects_attributes.data(),
                                                      map.objects_attributes.size()));
    }
    // Read global events.
    const std::uint32_t num_global_events = readInt<std::uint32_t>(stream);
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
