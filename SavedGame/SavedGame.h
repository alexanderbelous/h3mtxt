#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/SavedGame/EnumIndexedArray.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>
#include <h3mtxt/SavedGame/ObjectSvg.h>
#include <h3mtxt/SavedGame/ObjectTemplateSvg.h>
#include <h3mtxt/SavedGame/PlayerSpecsSvg.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>
#include <h3mtxt/SavedGame/TileSvg.h>

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

// TODO: rename to h3svg.
// Basically, the issue is that some structures are represented differently in H3SVG than they are in H3M.
// We have 3 options:
// 1) Use the same namespace but different names for such classes.
// 2) Use different namespaces but the same names for such classes.
// 3) Use the same namespace, the same names, but make them specializations of a template,
//    e.g., PlayerSpecs<FileFormat::H3M>, PlayerSpecs<FileFormat::H3SVG>.
//
// Option (3) is is ugly and essentially equivalent to (1), so fuck it.
// Option (1) is OKish, but I don't like appending "Svg" suffix to every class - what is this,
// Hungarian notation?
// The main reason I didn't pick option (2) from the beginning is that I was concerned about the
// potential ambiguity. However, it would only really an issue if the namespaces were nested
// (e.g., h3m::h3svg::PlayerSpecs), which is not the plan.
namespace h3m
{
  struct BlackMarket
  {
    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, 7> artifacts {};
  };

  // Always 145 bytes?
  struct PlayerSvg
  {
    PlayerColor player_color {};
    std::uint8_t num_heroes {};
    // HeroType of the currently active hero, 0xFF if there is none.
    HeroType active_hero {};
    // All heroes on the Adventure Map (i.e. not garrisoned inside towns).
    // If the player has fewer than 8 heroes, 0xFF is used in empty slots.
    std::array<HeroType, 8> heroes {};
    std::array<HeroType, 2> heroes_in_tavern {};
    std::array<std::uint8_t, 85> unknown1 {};
    Resources resources;
    std::array<std::uint8_t, 19> unknown2 {};
  };

  // The equivalent of h3m::Rumor stored in the saved game.
  struct RumorSvg
  {
    std::string text;
    // Indicates whether this rumor has been displayed in the Tavern.
    // This doesn't necessarily mean that the player has read this rumor - the value is set to 1
    // when this rumor becomes the "rumor of the week", not when the player sees it in the Tavern.
    // Note, however, that the value can be reset from 1 to 0 sometimes - I'm not sure why.
    Bool has_been_shown {};
  };

  // Information about a town stored in H3SVG.
  // Credits to RoseKavalier: instead of figuring out the meaning of every byte, I followed the already
  // reverse-engineering representation of the town in the process memory
  //   https://github.com/RoseKavalier/H3API/blob/master/include/h3api/H3Towns/H3Town.hpp
  // and it seems that they are very similar.
  struct TownSvg
  {
    // 0-based index of this town in SavedGame::towns.
    std::uint8_t id {};
    PlayerColor owner {};
    std::array<std::uint8_t, 2> unknown1 {}; // unknown1[0] is probably Bool built_this_turn
    TownType type {};
    Coordinates coordinates;
    // X and Y coordinates of the tile where the boat will be generated when built via the town's
    // Shipyard, or {0xFF, 0xFF} if this town cannot build ships.
    std::uint8_t generated_boat_x {};
    std::uint8_t generated_boat_y {};
    // TODO: reverse-engineer
    // unknown2[57] -> HeroType visiting_hero.
    std::array<std::uint8_t, 60> unknown2 {};
    std::string name;
    // TODO: reverse-engineer
    std::array<std::uint8_t, 310> unknown3 {};
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
    EnumIndexedArray<PlayerColor, PlayerSpecsSvg, kMaxPlayers> players;
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
    std::vector<RumorSvg> rumors;
    // Artifacts currently available in Black Markets on the Adventure Map.
    // Ideally, this should be a member of object_properties_tables, but in H3SVG it is serialized
    // immediately after rumors.
    std::vector<BlackMarket> black_markets;
    // Terrain data for each tile on the map.
    // The number of elements should be (has_two_levels ? 2 : 1) * map_size * map_size,
    // i.e. countTiles(this->basic_info).
    // Tile (x, y, z) has the index ((z * map_size + y) * map_size + x).
    std::vector<TileSvg> tiles;
    // "Templates" for objects on the Adventure Map.
    std::vector<ObjectTemplateSvg> objects_templates;
    // Objects on the Adventure Map.
    std::vector<ObjectSvg> objects;
    // Tables storing additional data for objects whose properties aren't fully described by TileSvg.
    ObjectPropertiesTables object_properties_tables;
    // Current state for each player.
    EnumIndexedArray<PlayerColor, PlayerSvg, 8> players_svg;
    // Towns on the Adventure Map.
    std::vector<TownSvg> towns;

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
