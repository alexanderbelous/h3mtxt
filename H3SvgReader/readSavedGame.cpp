#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3m
{
  ArtifactSvg H3SvgReader::readArtifact() const
  {
    return ArtifactSvg{ .guardians = readGuardians() };
  }

  BlackMarket H3SvgReader::readBlackMarket() const
  {
    BlackMarket black_market;
    for (ArtifactType32& artifact : black_market.artifacts)
    {
      artifact = readEnum<ArtifactType32>();
    }
    return black_market;
  }

  MineSvg H3SvgReader::readMine() const
  {
    MineSvg mine;
    mine.owner = readEnum<PlayerColor>();
    mine.unknown = readByteArray<2>();
    mine.creatures = readTroops();
    mine.coordinates = readCoordinates();
    return mine;
  }

  MonsterSvg H3SvgReader::readMonster() const
  {
    MonsterSvg monster;
    monster.message = readString16();
    monster.resources = readResources();
    monster.artifact = readEnum<ArtifactType8>();
    return monster;
  }

  QuestGuardSvg H3SvgReader::readQuestGuard() const
  {
    QuestGuardSvg quest_guard;
    quest_guard.quest = readQuest();
    quest_guard.visited_by = readEnumBitmask<PlayerColor, 1>();
    return quest_guard;
  }

  RumorSvg H3SvgReader::readRumor() const
  {
    RumorSvg rumor;
    rumor.text = readString16();
    rumor.has_been_shown = readBool();
    return rumor;
  }

  SeersHutSvg H3SvgReader::readSeersHut() const
  {
    SeersHutSvg seers_hut;
    seers_hut.quest = readQuest();
    seers_hut.reward = readReward();
    seers_hut.unknown1 = readInt<std::uint8_t>();
    seers_hut.visited_by = readEnumBitmask<PlayerColor, 1>();
    seers_hut.unknown2 = readInt<std::uint8_t>();
    return seers_hut;
  }

  SignSvg H3SvgReader::readSign() const
  {
    SignSvg sign;
    sign.message = readString16();
    sign.is_custom = readBool();
    return sign;
  }

  TimedEventSvg H3SvgReader::readTimedEvent() const
  {
    TimedEventSvg event;
    event.message = readString16();
    event.resources = readResources();
    event.affected_players = readEnumBitmask<PlayerColor, 1>();
    event.applies_to_human = readBool();
    event.applies_to_computer = readBool();
    event.day_of_first_occurence = readInt<std::uint16_t>();
    event.repeat_after_days = readInt<std::uint16_t>();
    return event;
  }

  TownEventSvg H3SvgReader::readTownEvent() const
  {
    TownEventSvg town_event{ readTimedEvent() };
    town_event.unknown1 = static_cast<std::byte>(readInt<std::uint8_t>());
    town_event.buildings = readEnumBitmask<TownBuildingType, 6>();
    readBytes(std::span<std::byte, 2>{ town_event.unknown2 });
    for (std::uint16_t& growth : town_event.creatures)
    {
      growth = readInt<std::uint16_t>();
    }
    return town_event;
  }

  SavedGame H3SvgReader::readSavedGame() const
  {
    SavedGame saved_game;
    // Read and check the file signature.
    char file_signature[5] {};
    readBytes(std::as_writable_bytes(std::span{ file_signature }));
    if (std::string_view{ file_signature, sizeof(file_signature) } != SavedGame::kFileSignature)
    {
      throw std::runtime_error("readSavedGame(): invalid file signature.");
    }
    saved_game.reserved1 = readReservedData<3>();
    saved_game.version_major = readInt<std::uint32_t>();
    saved_game.version_minor = readInt<std::uint32_t>();
    saved_game.reserved2 = readReservedData<32>();
    saved_game.format = readEnum<h3m::MapFormat>();
    saved_game.basic_info = readMapBasicInfo();
    for (PlayerSpecsSvg& player : saved_game.players.data)
    {
      player = readPlayerSpecs();
    }
    saved_game.victory_condition = H3Reader_NS::readVictoryCondition(stream_);
    saved_game.loss_condition = H3Reader_NS::readLossCondition(stream_);
    saved_game.teams = readTeamsInfo();
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>();
    saved_game.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      saved_game.custom_heroes.push_back(readCustomHero());
    }
    // Read 16 bytes.
    // These seem to to always be {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    readBytes(std::span<std::byte, 16>{ saved_game.unknown1 });
    // Read 32 bytes - 4 bytes per player, specifying their alignment.
    for (TownType32& alignment : saved_game.alignments.data)
    {
      alignment = readEnum<TownType32>();
    }
    // Read 8 bytes.
    // TODO: figure out what it is.
    readBytes(std::span<std::byte, 8>{ saved_game.unknown2 });
    // Read 1 byte - the selected difficulty level.
    saved_game.difficulty = readEnum<MapDifficulty>();
    // Read 251 bytes representing the filename of the original map.
    readBytes(std::as_writable_bytes(std::span{ saved_game.map_filename }));
    // Read 100 bytes representing the relative path to the directory in which the original map is located.
    readBytes(std::as_writable_bytes(std::span{ saved_game.map_directory }));
    // Read 8 bytes - 1 byte per PlayerColor, indicating who can control this color.
    for (PlayerControlType& player_control : saved_game.players_control.data)
    {
      player_control = readEnum<PlayerControlType>();
    }
    // Read 3 bytes.
    // TODO: figure out what this is. Seems to always be {255, 1, 1}.
    readBytes(std::span<std::byte, 3>{ saved_game.unknown3 });
    // Read 1 byte specifying the player turn duration.
    saved_game.player_turn_duration = readEnum<PlayerTurnDurationType>();
    // Read 8 bytes - 1 byte per player, specifying the starting hero.
    for (HeroType& starting_hero : saved_game.starting_heroes.data)
    {
      starting_hero = readEnum<HeroType>();
    }
    // Read 8 bytes - 1 byte per player, specifying the starting bonus.
    for (PlayerStartingBonusType& starting_bonus : saved_game.starting_bonuses.data)
    {
      starting_bonus = readEnum<PlayerStartingBonusType>();
    }
    // Read 2 bytes.
    // TODO: figure out what this is. Seems to always be {0, 0}.
    readBytes(std::span<std::byte, 2>{ saved_game.unknown4 });
    // Read 47 bytes representing the original filename for this saved game.
    readBytes(std::as_writable_bytes(std::span{ saved_game.original_filename }));
    // Read 352 bytes.
    // TODO: figure out what this is.
    readBytes(std::span<std::byte, 352>{ saved_game.unknown5 });
    // Read 144 bytes indicating which artifacts are disabled on this map (1 byte per artifact).
    saved_game.disabled_artifacts.data = readByteArray<144>();
    // Read 144 bytes for another bitmask for artifacts.
    // TODO: figure out what this is.
    saved_game.artifacts_bitmask_unknown.data = readByteArray<144>();
    // Read 28 bytes indicating which secondary skills are disabled on this map (1 byte per skill).
    saved_game.disabled_skills.data = readByteArray<28>();
    // Read the rumor currently displayed in the Tavern.
    saved_game.current_rumor = readString16();
    // Read 256 bytes.
    // TODO: figure out what this is.
    readBytes(std::span<std::byte, 256>{ saved_game.unknown6 });
    // Read custom rumors that can appear in the Tavern.
    {
      const std::uint32_t num_custom_rumors = readInt<std::uint32_t>();
      saved_game.rumors.reserve(num_custom_rumors);
      for (std::uint32_t i = 0; i < num_custom_rumors; ++i)
      {
        saved_game.rumors.push_back(readRumor());
      }
    }
    // Read the current state (slots) for each Black Market on the Adventure map.
    {
      const std::uint8_t num_black_markets = readInt<std::uint8_t>();
      saved_game.black_markets.reserve(num_black_markets);
      for (std::uint32_t i = 0; i < num_black_markets; ++i)
      {
        // Read 28 bytes for each Black Market (7 32-bit integers).
        saved_game.black_markets.push_back(readBlackMarket());
      }
    }
    // Read tiles.
    {
      const std::size_t num_tiles = countTiles(saved_game.basic_info);
      saved_game.tiles.reserve(num_tiles);
      for (std::size_t i = 0; i < num_tiles; ++i)
      {
        saved_game.tiles.push_back(readTile());
      }
    }
    // Read objects' templates.
    {
      const std::uint32_t num_objects_templates = readInt<std::uint32_t>();
      saved_game.objects_templates.reserve(num_objects_templates);
      for (std::uint32_t i = 0; i < num_objects_templates; ++i)
      {
        saved_game.objects_templates.push_back(readObjectTemplate());
      }
    }
    // Read objects.
    {
      const std::uint32_t num_objects = readInt<std::uint32_t>();
      saved_game.objects.reserve(num_objects);
      for (std::uint32_t i = 0; i < num_objects; ++i)
      {
        saved_game.objects.push_back(readObject());
      }
    }
    // Read Event and Pandora's Box objects.
    // FYI: it's funny that the number of events is serialized as a 16-bit integer - the Map Editor
    // seems to have a limit of 200 Events on the Adventure Map.
    {
      const std::uint16_t num_event_objects = readInt<std::uint16_t>();
      saved_game.events_and_pandoras_boxes.reserve(num_event_objects);
      for (std::uint16_t i = 0; i < num_event_objects; ++i)
      {
        saved_game.events_and_pandoras_boxes.push_back(readEventBase());
      }
    }
    // Read Artifact and SpellScroll objects.
    {
      const std::uint16_t num_artifact_objects = readInt<std::uint16_t>();
      saved_game.artifacts_and_spell_scrolls.reserve(num_artifact_objects);
      for (std::uint16_t i = 0; i < num_artifact_objects; ++i)
      {
        saved_game.artifacts_and_spell_scrolls.push_back(readArtifact());
      }
    }
    // Read wandering creatures.
    {
      const std::uint16_t num_monster_objects = readInt<std::uint16_t>();
      saved_game.monsters.reserve(num_monster_objects);
      for (std::uint16_t i = 0; i < num_monster_objects; ++i)
      {
        saved_game.monsters.push_back(readMonster());
      }
    }
    // Read Seer's Huts.
    {
      const std::uint16_t num_seers_huts = readInt<std::uint16_t>();
      saved_game.seers_huts.reserve(num_seers_huts);
      for (std::uint16_t i = 0; i < num_seers_huts; ++i)
      {
        saved_game.seers_huts.push_back(readSeersHut());
      }
    }
    // Read Quest Guards.
    {
      const std::uint16_t num_quest_guards = readInt<std::uint16_t>();
      saved_game.quest_guards.reserve(num_quest_guards);
      for (std::uint16_t i = 0; i < num_quest_guards; ++i)
      {
        saved_game.quest_guards.push_back(readQuestGuard());
      }
    }
    // Read global events.
    {
      const std::uint32_t num_global_events = readInt<std::uint32_t>();
      saved_game.global_events.reserve(num_global_events);
      for (std::uint32_t i = 0; i < num_global_events; ++i)
      {
        saved_game.global_events.push_back(readTimedEvent());
      }
    }
    // Read town events.
    {
      const std::uint32_t num_town_events = readInt<std::uint32_t>();
      saved_game.town_events.reserve(num_town_events);
      for (std::uint32_t i = 0; i < num_town_events; ++i)
      {
        saved_game.town_events.push_back(readTownEvent());
      }
    }
    // Read Signs and Ocean Bottles.
    {
      const std::uint8_t num_signs_and_ocean_bottles = readInt<std::uint8_t>();
      saved_game.signs_and_ocean_bottles.reserve(num_signs_and_ocean_bottles);
      for (std::uint32_t i = 0; i < num_signs_and_ocean_bottles; ++i)
      {
        saved_game.signs_and_ocean_bottles.push_back(readSign());
      }
    }
    // Read Mines and Lighthouses.
    {
      const std::uint8_t num_mines_and_lighthouses = readInt<std::uint8_t>();
      saved_game.mines_and_lighthouses.reserve(num_mines_and_lighthouses);
      for (std::uint32_t i = 0; i < num_mines_and_lighthouses; ++i)
      {
        saved_game.mines_and_lighthouses.push_back(readMine());
      }
    }
    // TODO: read the rest.
    return saved_game;
  }
}
