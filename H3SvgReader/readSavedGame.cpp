#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3m
{
  RumorSvg H3SvgReader::readRumor() const
  {
    RumorSvg rumor;
    rumor.text = readString16();
    rumor.has_been_shown = readBool();
    return rumor;
  }

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

  MonsterSvg H3SvgReader::readMonster() const
  {
    MonsterSvg monster;
    monster.message = readString16();
    monster.resources = readResources();
    monster.artifact = readEnum<ArtifactType8>();
    return monster;
  }

  SeersHutSvg H3SvgReader::readSeersHut() const
  {
    SeersHutSvg seers_hut;
    seers_hut.quest = readQuest();
    seers_hut.reward = readReward();
    readBytes(std::span<std::byte, 3>{ seers_hut.unknown });
    return seers_hut;
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
    // Read 9 bytes.
    // TODO: figure out what it is.
    readBytes(std::span<std::byte, 9>{ saved_game.unknown2 });
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
    // In H3SVG this is serialized as a length-prefixed string; the length is serialized as a
    // 16-bit little-endian integer.
    saved_game.current_rumor = readString16();
    // Read 256 bytes.
    // TODO: figure out what this is.
    readBytes(std::span<std::byte, 256>{ saved_game.unknown6 });
    // Read custom rumors that can appear in the Tavern.
    const std::uint32_t num_custom_rumors = readInt<std::uint32_t>();
    saved_game.rumors.reserve(num_custom_rumors);
    for (std::uint32_t i = 0; i < num_custom_rumors; ++i)
    {
      saved_game.rumors.push_back(readRumor());
    }
    // Read the current state (slots) for each Black Market on the Adventure map.
    // Read 1 byte representing the number of Black Markets.
    const std::uint8_t num_black_markets = readInt<std::uint8_t>();
    saved_game.black_markets.reserve(num_black_markets);
    for (std::uint32_t i = 0; i < num_black_markets; ++i)
    {
      // Read 28 bytes for each Black Market (7 32-bit integers).
      saved_game.black_markets.push_back(readBlackMarket());
    }
    // Read tiles.
    const std::size_t num_tiles = countTiles(saved_game.basic_info);
    saved_game.tiles.reserve(num_tiles);
    for (std::size_t i = 0; i < num_tiles; ++i)
    {
      saved_game.tiles.push_back(readTile());
    }
    // Read objects' templates.
    const std::uint32_t num_objects_templates = readInt<std::uint32_t>();
    saved_game.objects_templates.reserve(num_objects_templates);
    for (std::uint32_t i = 0; i < num_objects_templates; ++i)
    {
      saved_game.objects_templates.push_back(readObjectTemplate());
    }
    // Read objects.
    const std::uint32_t num_objects = readInt<std::uint32_t>();
    saved_game.objects.reserve(num_objects);
    for (std::uint32_t i = 0; i < num_objects; ++i)
    {
      saved_game.objects.push_back(readObject());
    }
    // Read Event and Pandora's Box objects.
    // FYI: it's funny that the number of events is serialized as a 16-bit integer - the Map Editor
    // seems to have a limit of 200 Events on the Adventure Map.
    const std::uint16_t num_event_objects = readInt<std::uint16_t>();
    saved_game.events_and_pandoras_boxes.reserve(num_event_objects);
    for (std::uint16_t i = 0; i < num_event_objects; ++i)
    {
      saved_game.events_and_pandoras_boxes.push_back(readEventBase());
    }
    // Read Artifact and SpellScroll objects.
    const std::uint16_t num_artifact_objects = readInt<std::uint16_t>();
    saved_game.artifacts_and_spell_scrolls.reserve(num_artifact_objects);
    for (std::uint16_t i = 0; i < num_artifact_objects; ++i)
    {
      saved_game.artifacts_and_spell_scrolls.push_back(readArtifact());
    }
    // Read wandering creatures.
    const std::uint16_t num_monster_objects = readInt<std::uint16_t>();
    saved_game.monsters.reserve(num_monster_objects);
    for (std::uint16_t i = 0; i < num_monster_objects; ++i)
    {
      saved_game.monsters.push_back(readMonster());
    }
    // Read Seer's Huts.
    const std::uint16_t num_seers_huts = readInt<std::uint16_t>();
    saved_game.seers_huts.reserve(num_seers_huts);
    for (std::uint16_t i = 0; i < num_seers_huts; ++i)
    {
      saved_game.seers_huts.push_back(readSeersHut());
    }
    // TODO: read the rest.
    return saved_game;
  }
}
