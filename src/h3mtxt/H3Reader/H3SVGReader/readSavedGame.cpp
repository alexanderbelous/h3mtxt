#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3svg
{
  ArtifactMerchants H3SVGReader::readArtifactMerchants() const
  {
    ArtifactMerchants artifact_merchants;
    for (ArtifactType32& artifact : artifact_merchants.artifacts)
    {
      artifact = readEnum<ArtifactType32>();
    }
    return artifact_merchants;
  }

  CreatureBank H3SVGReader::readCreatureBank() const
  {
    CreatureBank creature_bank;
    creature_bank.guards = readTroops();
    creature_bank.resources = readResources();
    creature_bank.creatures = readTypedQuantity<CreatureType32, std::uint8_t>();
    const std::uint16_t num_artifacts = readInt<std::uint16_t>();
    creature_bank.artifacts.reserve(num_artifacts);
    for (std::uint16_t i = 0; i < num_artifacts; ++i)
    {
      creature_bank.artifacts.push_back(readEnum<ArtifactType32>());
    }
    return creature_bank;
  }

  ObjectExits H3SVGReader::readObjectExits() const
  {
    ObjectExits object_exits;
    const std::uint16_t num_exits = readInt<std::uint16_t>();
    object_exits.exits.reserve(num_exits);
    for (std::uint16_t i = 0; i < num_exits; ++i)
    {
      object_exits.exits.push_back(readCoordinatesPacked());
    }
    return object_exits;
  }

  Rumor H3SVGReader::readRumor() const
  {
    Rumor rumor;
    rumor.text = readString16();
    rumor.has_been_shown = readBool();
    return rumor;
  }

  SavedGame H3SVGReader::readSavedGame() const
  {
    SavedGame saved_game;
    saved_game.signature = readFixedLengthString<5>();
    // Check the file signature (always 5 bytes).
    {
      const std::string_view signature = saved_game.signature;
      if (signature != SavedGame::kSignatureMap &&
          signature != SavedGame::kSignatureCampaign)
      {
        throw std::runtime_error("readSavedGame(): invalid file signature \"" + std::string{ signature } + "\".");
      }
    }
    saved_game.reserved1 = readReservedData<3>();
    saved_game.version_major = readInt<std::uint32_t>();
    saved_game.version_minor = readInt<std::uint32_t>();
    saved_game.reserved2 = readReservedData<32>();
    saved_game.format = readEnum<h3m::MapFormat>();
    saved_game.basic_info = readMapBasicInfo();
    for (PlayerSpecs& player_specs : saved_game.players_specs.data)
    {
      player_specs = readPlayerSpecs();
    }
    saved_game.victory_condition = readVictoryCondition();
    saved_game.loss_condition = readLossCondition();
    saved_game.teams = readTeams();
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>();
    saved_game.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      saved_game.custom_heroes.push_back(readCustomHero());
    }
    // Read 16 bytes.
    // These seem to to always be {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    saved_game.unknown1 = readByteArray<16>();
    // Read the starting settings for this scenario.
    // FYI: for standalone maps this is always 422 bytes; for campaigns, however, the size varies.
    saved_game.starting_info = readScenarioStartingInfo();
    // Read 47 bytes representing the original filename for this saved game.
    saved_game.original_filename = readFixedLengthString<47>();
    // Read 352 bytes.
    // TODO: figure out what this is.
    saved_game.unknown2 = readByteArray<352>();
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
    saved_game.unknown3 = readByteArray<256>();
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
        saved_game.black_markets.push_back(readArtifactMerchants());
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
    // Read the tables storing additional data for objects whose properties aren't fully described by Tile.
    saved_game.object_properties_tables = readObjectPropertiesTables();
    // Read 1160 bytes - 145 bytes per player, representing the current state of the player.
    for (Player& player : saved_game.players.data)
    {
      player = readPlayer();
    }
    // Read towns.
    {
      const std::uint8_t num_towns = readInt<std::uint8_t>();
      saved_game.towns.reserve(num_towns);
      for (std::uint32_t i = 0; i < num_towns; ++i)
      {
        saved_game.towns.push_back(readTown());
      }
    }
    // Read heroes.
    {
      saved_game.heroes.reserve(h3m::kNumHeroes);
      for (std::uint32_t i = 0; i < h3m::kNumHeroes; ++i)
      {
        saved_game.heroes.push_back(readHero());
      }
    }
    // Read 323 bytes.
    // TODO: figure out what this is.
    saved_game.unknown4 = readByteArray<323>();
    // Read 6 bytes - the current date.
    saved_game.current_date = readDate();
    // Read 32 bytes.
    // TODO: figure out what this is.
    saved_game.unknown5 = readByteArray<32>();
    // Read Artifact Merchants.
    saved_game.artifact_merchants = readArtifactMerchants();
    // Read 32 bytes.
    // TODO: figure out what this is.
    saved_game.unknown6 = readByteArray<32>();
    // Read 8 bytes - Keymaster's Tents.
    for (PlayersBitmask& bitmask : saved_game.keymasters_tents.data)
    {
      bitmask = readEnumBitmask<PlayerColor, 1>();
    }
    // Read 6 bytes.
    // TODO: figure out what this is.
    saved_game.unknown7 = readByteArray<6>();
    // Read 3 bytes - 1 byte per Cartographer type.
    saved_game.cartographer_water = readEnumBitmask<PlayerColor, 1>();
    saved_game.cartographer_land = readEnumBitmask<PlayerColor, 1>();
    saved_game.cartographer_subterranean = readEnumBitmask<PlayerColor, 1>();
    // Read 4 bytes.
    // TODO: figure out what this is.
    saved_game.unknown8 = readByteArray<4>();
    // Read Fog of War.
    {
      const std::size_t num_tiles = countTiles(saved_game.basic_info);
      saved_game.fog_of_war.reserve(num_tiles);
      for (std::size_t i = 0; i < num_tiles; ++i)
      {
        saved_game.fog_of_war.push_back(readTileVisibility());
      }
    }
    // Read Two-Way Monoliths.
    for (ObjectExits& monolith : saved_game.monoliths_two_way)
    {
      monolith = readObjectExits();
    }
    // Read One-Way Monoliths.
    for (ObjectExits& monolith : saved_game.monoliths_one_way)
    {
      monolith = readObjectExits();
    }
    // Read Whirlpools.
    saved_game.whirlpools = readObjectExits();
    // Read Subterranean Gates.
    saved_game.subterranean_gates = readObjectExits();
    // Read unknown9.
    {
      const std::uint16_t num_elements = readInt<std::uint16_t>();
      saved_game.unknown9.reserve(num_elements);
      for (std::uint16_t i = 0; i < num_elements; ++i)
      {
        saved_game.unknown9.push_back(readInt<std::uint32_t>());
      }
    }
    // Read Universities.
    {
      const std::uint16_t num_universities = readInt<std::uint16_t>();
      saved_game.universities.reserve(num_universities);
      for (std::uint16_t i = 0; i < num_universities; ++i)
      {
        saved_game.universities.push_back(readUniversity());
      }
    }
    // Read Creature Banks.
    {
      const std::uint16_t num_creature_banks = readInt<std::uint16_t>();
      saved_game.creature_banks.reserve(num_creature_banks);
      for (std::uint16_t i = 0; i < num_creature_banks; ++i)
      {
        saved_game.creature_banks.push_back(readCreatureBank());
      }
    }
    // Read Replay data.
    {
      const std::uint32_t num_replay_events = readInt<std::uint32_t>();
      saved_game.previous_turn.reserve(num_replay_events);
      for (std::uint32_t i = 0; i < num_replay_events; ++i)
      {
        saved_game.previous_turn.push_back(readReplayEvent());
      }
    }
    //saved_game.previous_turn = readReplayEvents();
    // TODO: read the rest.
    //saved_game.unknown10 = readByteArray<512>();
    return saved_game;
  }

  TileVisibility H3SVGReader::readTileVisibility() const
  {
    TileVisibility tile_visibility;
    tile_visibility.visibility = readEnumBitmask<PlayerColor, 1>();
    tile_visibility.has_adjacent_monster = readBool();
    return tile_visibility;
  }

  University H3SVGReader::readUniversity() const
  {
    University university;
    for (std::uint32_t& secondary_skill : university.skills)
    {
      secondary_skill = readInt<std::uint32_t>();
    }
    return university;
  }
}
