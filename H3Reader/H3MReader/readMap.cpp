#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Map.h>

namespace h3m
{
  namespace
  {
    PlayerSpecs::HeroInfo readPlayerSpecsHeroInfo(const H3MReader& reader)
    {
      PlayerSpecs::HeroInfo hero;
      hero.type = reader.readEnum<HeroType>();
      hero.name = reader.readString32();
      return hero;
    }
  }

  MapBasicInfo H3MReader::readMapBasicInfo() const
  {
    MapBasicInfo basic_info;
    basic_info.is_playable = readBool();
    basic_info.map_size = readInt<std::uint32_t>();
    basic_info.has_two_levels = readBool();
    basic_info.name = readString32();
    basic_info.description = readString32();
    basic_info.difficulty = readEnum<MapDifficulty>();
    basic_info.max_hero_level = readInt<std::uint8_t>();
    return basic_info;
  }

  MainTown H3MReader::readMainTown() const
  {
    MainTown main_town;
    main_town.generate_hero = readBool();
    main_town.town_type = readEnum<TownType>();
    main_town.coordinates = readCoordinates();
    return main_town;
  }

  StartingHero H3MReader::readStartingHero() const
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>();
    if (starting_hero.type != HeroType{0xFF})
    {
      starting_hero.portrait = readEnum<HeroPortrait>();
      starting_hero.name = readString32();
    }
    return starting_hero;
  }

  PlayerSpecs H3MReader::readPlayerSpecs() const
  {
    PlayerSpecs player;
    player.can_be_human = readBool();
    player.can_be_computer = readBool();
    player.behavior = readEnum<PlayerBehavior>();
    player.has_customized_alignments = readInt<std::uint8_t>();
    player.allowed_alignments.bitset = readBitSet<2>();
    player.allow_random_alignment = readInt<std::uint8_t>();
    const bool has_main_town = readBool();
    if (has_main_town)
    {
      player.main_town = readMainTown();
    }
    player.has_random_heroes = readBool();
    player.starting_hero = readStartingHero();
    player.num_nonspecific_placeholder_heroes = readInt<std::uint8_t>();
    const std::uint32_t num_heroes = readInt<std::uint32_t>();
    player.heroes.reserve(num_heroes);
    for (std::uint32_t i = 0; i < num_heroes; ++i)
    {
      player.heroes.push_back(readPlayerSpecsHeroInfo(*this));
    }
    return player;
  }

  LossCondition H3MReader::readLossCondition() const
  {
    const LossConditionType loss_condition_type = readEnum<LossConditionType>();
    switch (loss_condition_type)
    {
    case LossConditionType::LoseTown:
    {
      LossConditionDetails<LossConditionType::LoseTown> details;
      details.coordinates = readCoordinates();
      return LossCondition{details};
    }
    case LossConditionType::LoseHero:
    {
      LossConditionDetails<LossConditionType::LoseHero> details;
      details.coordinates = readCoordinates();
      return LossCondition{details};
    }
    case LossConditionType::TimeExpires:
    {
      LossConditionDetails<LossConditionType::TimeExpires> details;
      details.days = readInt<std::int16_t>();
      return LossCondition{details};
    }
    case LossConditionType::Normal:
      return LossCondition{};
    default:
      throw std::runtime_error("Invalid loss condition type.");
    }
  }

  TeamsInfo H3MReader::readTeamsInfo() const
  {
    TeamsInfo teams_info;
    teams_info.num_teams = readInt<std::uint8_t>();
    if (teams_info.num_teams != 0)
    {
      for (std::uint8_t& team : teams_info.team_for_player.data)
      {
        team = readInt<std::uint8_t>();
      }
    }
    return teams_info;
  }

  CustomHero H3MReader::readCustomHero() const
  {
    CustomHero custom_hero;
    custom_hero.type = readEnum<HeroType>();
    custom_hero.portrait = readEnum<HeroPortrait>();
    custom_hero.name = readString32();
    custom_hero.can_hire = readEnumBitmask<PlayerColor, 1>();
    return custom_hero;
  }

  Rumor H3MReader::readRumor() const
  {
    Rumor rumor;
    rumor.name = readString32();
    rumor.description = readString32();
    return rumor;
  }

  HeroSettings H3MReader::readHeroSettings() const
  {
    HeroSettings settings;
    if (const Bool has_experience = readBool())
    {
      settings.experience = readInt<std::int32_t>();
    }
    if (const Bool has_secondary_skills = readBool())
    {
      std::vector<SecondarySkill>& secondary_skills = settings.secondary_skills.emplace();
      const std::uint32_t num_secondary_skills = readInt<std::uint32_t>();
      secondary_skills.reserve(num_secondary_skills);
      for (std::uintmax_t i = 0; i < num_secondary_skills; ++i)
      {
        secondary_skills.push_back(readSecondarySkill());
      }
    }
    if (const Bool has_artifacts = readBool())
    {
      settings.artifacts = readHeroArtifacts();
    }
    if (const Bool has_biography = readBool())
    {
      settings.biography = readString32();
    }
    settings.gender = readEnum<Gender>();
    if (const Bool has_spells = readBool())
    {
      settings.spells = readEnumBitmask<SpellType, 9>();
    }
    if (const Bool has_primary_skills = readBool())
    {
      settings.primary_skills = readPrimarySkills();
    }
    return settings;
  }

  MapAdditionalInfo H3MReader::readMapAdditionalInfo() const
  {
    MapAdditionalInfo additional_info;
    additional_info.victory_condition = readVictoryCondition();
    additional_info.loss_condition = readLossCondition();
    additional_info.teams = readTeamsInfo();
    additional_info.heroes_availability = readEnumBitmask<HeroType, 20>();
    // Read placeholder heroes.
    const std::uint32_t num_placeholder_heroes = readInt<std::uint32_t>();
    additional_info.placeholder_heroes.reserve(num_placeholder_heroes);
    for (std::uint32_t i = 0; i < num_placeholder_heroes; ++i)
    {
      additional_info.placeholder_heroes.push_back(readEnum<HeroType>());
    }
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>();
    additional_info.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      additional_info.custom_heroes.push_back(readCustomHero());
    }
    // Read reserved data.
    additional_info.reserved = readReservedData<31>();
    additional_info.disabled_artifacts = readEnumBitmask<ArtifactType, 18>();
    additional_info.disabled_spells = readEnumBitmask<SpellType, 9>();
    additional_info.disabled_skills = readEnumBitmask<SecondarySkillType, 4>();
    // Read rumors.
    const std::uint32_t num_rumors = readInt<std::uint32_t>();
    additional_info.rumors.reserve(num_rumors);
    for (std::uint32_t i = 0; i < num_rumors; ++i)
    {
      additional_info.rumors.push_back(readRumor());
    }
    // Read heroes
    for (std::uint32_t i = 0; i < kNumHeroes; ++i)
    {
      if (const Bool has_settings = readBool())
      {
        additional_info.heroes_settings[static_cast<HeroType>(i)] = readHeroSettings();
      }
    }
    return additional_info;
  }

  Tile H3MReader::readTile() const
  {
    Tile tile;
    tile.terrain_type = readEnum<TerrainType>();
    tile.terrain_sprite = readInt<std::uint8_t>();
    tile.river_type = readEnum<RiverType>();
    tile.river_sprite = readInt<std::uint8_t>();
    tile.road_type = readEnum<RoadType>();
    tile.road_sprite = readInt<std::uint8_t>();
    tile.flags = readEnumBitmask<TileFlag, 1>();
    return tile;
  }

  SpriteTilesBitmask H3MReader::readSpriteTilesBitmask() const
  {
    return SpriteTilesBitmask{ .data = readByteArray<6>() };
  }

  ObjectTemplate H3MReader::readObjectTemplate() const
  {
    ObjectTemplate result;
    result.def = readString32();
    result.passability = readSpriteTilesBitmask();
    result.actionability = readSpriteTilesBitmask();
    result.allowed_landscapes = readEnumBitmask<TerrainType, 2>();
    result.landscape_group = readEnumBitmask<TerrainType, 2>();
    result.object_class = readEnum<ObjectClass>();
    result.object_subclass = readInt<std::uint32_t>();
    result.object_group = readEnum<ObjectGroup>();
    result.is_ground = readBool();
    result.unknown = readReservedData<16>();
    return result;
  }

  Map H3MReader::readMap() const
  {
    Map map;
    map.format = readEnum<MapFormat>();
    if (map.format != MapFormat::ShadowOfDeath)
    {
      throw std::runtime_error("Unsupported MapFormat. Only ShadowOfDeath is supported.");
    }
    map.basic_info = readMapBasicInfo();
    for (int i = 0; i < kMaxPlayers; ++i)
    {
      map.players[i] = readPlayerSpecs();
    }
    map.additional_info = readMapAdditionalInfo();
    // Read tiles.
    const std::size_t num_tiles = countTiles(map.basic_info);
    map.tiles.reserve(num_tiles);
    for (std::size_t i = 0; i < num_tiles; ++i)
    {
      map.tiles.push_back(readTile());
    }
    // Read objects' templates.
    const std::uint32_t num_objects_templates = readInt<std::uint32_t>();
    map.objects_templates.reserve(num_objects_templates);
    for (std::uint32_t i = 0; i < num_objects_templates; ++i)
    {
      map.objects_templates.push_back(readObjectTemplate());
    }
    // Read objects' details.
    const std::uint32_t num_objects = readInt<std::uint32_t>();
    map.objects.reserve(num_objects);
    for (std::uint32_t i = 0; i < num_objects; ++i)
    {
      map.objects.push_back(readObject(map.objects_templates.data(), map.objects_templates.size()));
    }
    // Read global events.
    const std::uint32_t num_global_events = readInt<std::uint32_t>();
    map.global_events.reserve(num_global_events);
    for (std::uint32_t i = 0; i < num_global_events; ++i)
    {
      map.global_events.push_back(readTimedEvent());
    }
    // Read padding data.
    map.padding = readReservedData<124>();
    return map;
  }
}
