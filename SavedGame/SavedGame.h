#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/SavedGame/Constants/Constants.h>
#include <h3mtxt/SavedGame/EnumIndexedArray.h>
#include <h3mtxt/SavedGame/Hero.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>
#include <h3mtxt/SavedGame/Object.h>
#include <h3mtxt/SavedGame/ObjectTemplate.h>
#include <h3mtxt/SavedGame/PlayerSpecs.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>
#include <h3mtxt/SavedGame/Tile.h>
#include <h3mtxt/SavedGame/Town.h>

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace h3svg
{
  struct BlackMarket
  {
    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, 7> artifacts {};
  };

  // Always 145 bytes?
  struct Player
  {
    PlayerColor player_color {};
    std::uint8_t num_heroes {};
    // HeroType of the currently active hero, 0xFF if there is none.
    HeroType active_hero {};
    // All heroes on the Adventure Map (i.e. not garrisoned inside towns).
    // If the player has fewer than 8 heroes, 0xFF is used in empty slots.
    std::array<HeroType, 8> heroes {};
    std::array<HeroType, 2> heroes_in_tavern {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 10> unknown1 {};
    // The number of days left to live without a town, or -1 if the player has at least 1 town.
    std::int8_t days_left {};
    // The number of towns owned by the player.
    std::uint8_t num_towns {};
    // ID of the currently selected town, or -1 if there is none.
    std::int8_t current_town {};
    // IDs of towns owned by the player (see Town::id). Only the first @num_towns elements are meaningful - the
    // rest are usually set to 0xFF.
    std::array<std::int8_t, 48> towns {};
    // TODO: figure out what this is.
    // Each element seems to always be 0xFF. Maybe reserved for more towns?
    std::array<std::uint8_t, 24> unknown2 {};
    Resources resources;
    // 1 bit per Mystical Garden, indicating if the player has visited it this week.
    BitSet<4> mystical_gardens;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 4> unknown3 {};
    // 1 bit per Corpse, indicating if the player has visited it.
    BitSet<4> corpses;
    // 1 bit per Lean To, indicating if the player has visited it.
    BitSet<4> lean_tos;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown4 {};
  };

  // The equivalent of h3m::Rumor stored in the saved game.
  struct Rumor
  {
    std::string text;
    // Indicates whether this rumor has been displayed in the Tavern.
    // This doesn't necessarily mean that the player has read this rumor - the value is set to 1
    // when this rumor becomes the "rumor of the week", not when the player sees it in the Tavern.
    // Note, however, that the value can be reset from 1 to 0 sometimes - I'm not sure why.
    Bool has_been_shown {};
  };

  // Represents a saved game for Heroes of Might and Magic 3 (.GM1, .GM2, ... files).
  struct SavedGame
  {
    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: apparently, HD Mod may sometimes use "HDSvG" instead.
    static constexpr std::string_view kFileSignature = "H3SVG";

    ReservedData<3> reserved1;
    std::uint32_t version_major {};
    std::uint32_t version_minor {};
    // HD mod keeps this zero-initialized; the vanilla game (HoMM3 Complete) doesn't, but the values
    // don't seem to mean anything.
    ReservedData<32> reserved2;
    // Format of the map.
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map.
    MapBasicInfo basic_info;
    // Basic information about the players.
    EnumIndexedArray<PlayerColor, PlayerSpecs, kMaxPlayers> players_specs;
    // TODO: check that this works correctly for all victory condition types.
    VictoryCondition victory_condition;
    // TODO: check that this works correctly for all loss condition types.
    LossCondition loss_condition;
    TeamsInfo teams;
    std::vector<CustomHero> custom_heroes;
    // 16 bytes with unknown meaning: the values are always {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    // Modifying these bytes doesn't seem to affect anything.
    std::array<std::uint8_t, 16> unknown1 {};
    // Starting settings for the map.
    ScenarioStartingInfo starting_info;
    // TODO: figure out what this is.
    // Seems to always be {0, 0}
    std::array<std::uint8_t, 2> unknown2 {};
    // Original filename used for this saved game.
    // This doesn't seem to be used anywhere in the game.
    // This is also stored as a fixed-width string. Note that HoMM3 limits the length to 47 characters
    // (e.g., "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefg.GM1"), but it's probably not the limit of this field.
    // It's hard to figure out what the actual limit is, since the value is not used anywhere.
    // I don't know if this needs to be null-terminated (again, because it's not used anywhere).
    std::array<char, 47> original_filename {};
    // TODO: figure out what this is.
    // The last 50 bytes look like some bitmask, but I don't know the meaning yet.
    std::array<std::uint8_t, 352> unknown3 {};
    // Array of boolean values indicating which artifacts are disabled on this map (1 - disabled, 0 - enabled).
    EnumIndexedArray<ArtifactType, Bool, 144> disabled_artifacts;
    // Another array of boolean values for artifacts; the meaning is not clear yet.
    // TODO: figure out what this is. It seems that the value is always 1 if the artifact is disabled,
    // but it can also be 1 even if the artifact is enabled.
    EnumIndexedArray<ArtifactType, Bool, 144> artifacts_bitmask_unknown;
    // Array of boolean values indicating which secondary skills are disabled on this map (1 - disabled, 0 - enabled).
    EnumIndexedArray<SecondarySkillType, Bool, 28> disabled_skills;
    // The currently displayed rumor in the Tavern.
    std::string current_rumor;
    // TODO: figure out what this is.
    // The values seem to always be either 0x00 or 0x01; mostly 0x00.
    std::array<std::uint8_t, 256> unknown4 {};
    // Custom rumors that can appear in the Tavern.
    std::vector<Rumor> rumors;
    // Artifacts currently available in Black Markets on the Adventure Map.
    // Ideally, this should be a member of object_properties_tables, but in H3SVG it is serialized
    // immediately after rumors.
    std::vector<BlackMarket> black_markets;
    // Terrain data for each tile on the map.
    // The number of elements should be (has_two_levels ? 2 : 1) * map_size * map_size,
    // i.e. countTiles(this->basic_info).
    // Tile (x, y, z) has the index ((z * map_size + y) * map_size + x).
    std::vector<Tile> tiles;
    // "Templates" for objects on the Adventure Map.
    std::vector<ObjectTemplate> objects_templates;
    // Objects on the Adventure Map.
    std::vector<Object> objects;
    // Tables storing additional data for objects whose properties aren't fully described by Tile.
    ObjectPropertiesTables object_properties_tables;
    // Current state for each player.
    EnumIndexedArray<PlayerColor, Player, 8> players;
    // Towns on the Adventure Map.
    std::vector<Town> towns;
    // The number of elements must always be equal to h3m::kNumHeroes (156).
    // However, I'm not using std::array here because that would make sizeof(SavedGame) Hueg Like XBox (~160KB).
    std::vector<Hero> heroes;

    // TODO: reverse-engineer the rest.
    // The next fields are approximately:
    // * Settings for each hero
    //
    // Obviuously, there are other fields as well, but I don't know yet where they are located:
    // * Timestamp for the saved game (Heroes3.exe stores it somewhere in the file instead of using
    //   filesystem metadata)
    // * Artifacts in Artifact Merchants
    // * Which player has visited the Keymaster's tent (for each Keymaster's tent subtype)
    // * Which heroes have been defeated by the player (needed in quests)
    // * Previous turns for all opponents (probably for all players, because that would be
    //   necessary in multiplayer games).
    // * etc.
  };
}
