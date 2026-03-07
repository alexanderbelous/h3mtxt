#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3svg
{
  BlackMarket H3SvgReader::readBlackMarket() const
  {
    BlackMarket black_market;
    for (ArtifactType32& artifact : black_market.artifacts)
    {
      artifact = readEnum<ArtifactType32>();
    }
    return black_market;
  }

  // Seems to always be 145 bytes.
  Player H3SvgReader::readPlayer() const
  {
    Player player;
    player.player_color = readEnum<PlayerColor>();
    player.num_heroes = readInt<std::uint8_t>();
    player.active_hero = readEnum<HeroType>();
    for (HeroType& hero : player.heroes)
    {
      hero = readEnum<HeroType>();
    }
    for (HeroType& hero : player.heroes_in_tavern)
    {
      hero = readEnum<HeroType>();
    }
    player.unknown1 = readByteArray<85>();
    player.resources = readResources();
    player.unknown2 = readByteArray<19>();
    return player;
  }

  Rumor H3SvgReader::readRumor() const
  {
    Rumor rumor;
    rumor.text = readString16();
    rumor.has_been_shown = readBool();
    return rumor;
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
    for (PlayerSpecs& player_specs : saved_game.players_specs.data)
    {
      player_specs = readPlayerSpecs();
    }
    saved_game.victory_condition = h3m::H3Reader_NS::readVictoryCondition(stream_);
    saved_game.loss_condition = h3m::H3Reader_NS::readLossCondition(stream_);
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
    saved_game.unknown1 = readByteArray<16>();
    // Read 420 bytes - the starting settings for the map.
    saved_game.starting_info = readScenarioStartingInfo();
    // Read 2 bytes.
    // TODO: figure out what this is. Seems to always be {0, 0}.
    saved_game.unknown2 = readByteArray<2>();
    // Read 47 bytes representing the original filename for this saved game.
    readBytes(std::as_writable_bytes(std::span{ saved_game.original_filename }));
    // Read 352 bytes.
    // TODO: figure out what this is.
    saved_game.unknown3 = readByteArray<352>();
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
    saved_game.unknown4 = readByteArray<256>();
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
    // Read the tables storing additional data for objects whose properties aren't fully described by Tile.
    saved_game.object_properties_tables = readObjectPropertiesTables();
    // Read Players' Info.
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
      saved_game.heroes.reserve(kNumHeroes);
      for (std::uint32_t i = 0; i < kNumHeroes; ++i)
      {
        saved_game.heroes.push_back(readHero());
      }
    }
    // TODO: read the rest.
    return saved_game;
  }

  ScenarioStartingInfo H3SvgReader::readScenarioStartingInfo() const
  {
    ScenarioStartingInfo starting_info;
    // Read 32 bytes - 4 bytes per player, specifying their alignment.
    for (TownType32& alignment : starting_info.starting_towns.data)
    {
      alignment = readEnum<TownType32>();
    }
    // Read 8 bytes.
    // TODO: figure out what it is.
    readBytes(std::span<std::byte, 8>{ starting_info.unknown1 });
    // Read 1 byte - the selected difficulty level.
    starting_info.difficulty = readEnum<MapDifficulty>();
    // Read 251 bytes representing the filename of the original map.
    readBytes(std::as_writable_bytes(std::span{ starting_info.map_filename }));
    // Read 100 bytes representing the relative path to the directory in which the original map is located.
    readBytes(std::as_writable_bytes(std::span{ starting_info.map_directory }));
    // Read 8 bytes - 1 byte per PlayerColor, indicating who can control this color.
    for (PlayerControlType& player_control : starting_info.players_control.data)
    {
      player_control = readEnum<PlayerControlType>();
    }
    // Read 3 bytes.
    // TODO: figure out what this is. Seems to always be {255, 1, 1}.
    readBytes(std::span<std::byte, 3>{ starting_info.unknown2 });
    // Read 1 byte specifying the player turn duration.
    starting_info.player_turn_duration = readEnum<PlayerTurnDurationType>();
    // Read 8 bytes - 1 byte per player, specifying the starting hero.
    for (HeroType& starting_hero : starting_info.starting_heroes.data)
    {
      starting_hero = readEnum<HeroType>();
    }
    // Read 8 bytes - 1 byte per player, specifying the starting bonus.
    for (PlayerStartingBonusType& starting_bonus : starting_info.starting_bonuses.data)
    {
      starting_bonus = readEnum<PlayerStartingBonusType>();
    }
    return starting_info;
  }

  Town H3SvgReader::readTown() const
  {
    Town town;
    town.id = readInt<std::uint8_t>();
    town.owner = readEnum<PlayerColor>();
    town.built_this_turn = readBool();
    town.unknown1 = readInt<std::uint8_t>();
    town.type = readEnum<TownType>();
    town.coordinates = readCoordinates();
    town.generated_boat_x = readInt<std::uint8_t>();
    town.generated_boat_y = readInt<std::uint8_t>();
    town.garrison = readTroops();
    town.garrisoned_hero = readEnum<HeroType>();
    town.visiting_hero = readEnum<HeroType>();
    town.mage_guild_level = readInt<std::uint8_t>();
    town.unknown2 = readInt<std::uint8_t>();
    town.name = readString16();
    for (std::uint16_t& count : town.recruits_nonupgraded)
    {
      count = readInt<std::uint16_t>();
    }
    for (std::uint16_t& count : town.recruits_upgraded)
    {
      count = readInt<std::uint16_t>();
    }
    town.unknown3 = readByteArray<282>();
    return town;
  }
}
