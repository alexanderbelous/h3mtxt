#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace h3m
{
  struct Coordinates
  {
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };

  // The equivalent of PlayersSpecs stored in the saved game.
  struct PlayerSpecsSvg
  {
    Bool can_be_human{};
    Bool can_be_computer{};
    PlayerBehavior behavior{};
    TownsBitmask allowed_alignments;
    // TODO: figure out what this is (has_random_heroes?).
    std::byte unknown;
    // Initial coordinates of the hero that was generated for this player at the start of the game,
    // or std::nullopt if no hero was generated.
    // Note that a hero can only be generated inside the main town, so this can also be interpreted
    // as the coordinates of the main town.
    std::optional<Coordinates> generated_hero_coordinates;
    // Note that in saved games the length of the string StartingHero::name is
    // serialized as a 16-bit integer (in .h3m it's serialized as a 32-bit integer).
    StartingHero starting_hero;
  };

  // Represents a saved game for Heroes of Might and Magic 3 (.GM1, .GM2, ... files).
  struct SavedGame
  {
    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: apparently, HD Mod may sometimes use "HDSvG" instead.
    static constexpr std::string_view kFileSignature = "H3SVG";

    ReservedData<3> reserved1;
    std::uint32_t version_major{};
    std::uint32_t version_minor{};
    // HD mod keeps this zero-initialized; the vanilla game (HoMM3 complete) doesn't, but the values
    // don't seem to mean anything.
    ReservedData<32> reserved2;
    // Format of the map (same as Map::format).
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map (same as Map::basic_info).
    MapBasicInfo basic_info;
    // Basic information about the players.
    std::array<PlayerSpecsSvg, kMaxPlayers> players {};
    // TODO: check that this works correctly for all victory condition types.
    VictoryCondition victory_condition;
    // TODO: check that this works correctly for all loss condition types.
    LossCondition loss_condition;
    TeamsInfo teams;
    std::vector<CustomHero> custom_heroes;
    // TODO: figure out what this is.
    // Seems to always be {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    // The values suggest that it has something to do with players, but it's
    // hard to figure out what it is without other examples.
    std::array<std::byte, 16> unknown1 {};
    // TODO: figure out what this is.
    // The first 32 bytes seem to represent 8 32-bit integers, which
    // have something to do with the players (and 0xFFFFFFFF being used for absent players).
    // This data seem to be a property of the map rather than the saved game:
    // the values don't seem to change throught the game.
    std::array<std::byte, 41> unknown2 {};
    // The original filename of the map (this is used by Restart Scenario command).
    //
    // In H3SVG this is stored as a fixed-width string (instead of a length-prefixed or null-terminated string).
    // Only the bytes up to the first null terminator are significant - the rest often contain junk.
    //
    // Note that in practice it's hard to use long filenames because in Windows a path cannot be
    // longer than MAX_PATH, which is 260 characters by default.
    //
    // I've tested that filenames with 244 characters work; testing even longer filenames requires
    // more tricks, and I have better things to do.
    //
    // I'm not sure what's the best API for this: we can either store it as an array of 251 bytes,
    // or as std::string. Neither is perfect: on the one hand, the junk bytes should be ignored, but on
    // the other hand, h3mtxt aims to allow inspecting and modifying any byte, as long as it doesn't lead
    // to corrupt data.
    //
    // For now, I will define this as an array of 251 bytes, but this might change in the future.
    std::array<char, 251> map_filename {};
    // Relative (to Heroes3.exe) path to the directory in which the original map is located.
    // Normally, this is always equal to "maps", but the game correctly handles other paths as well.
    //
    // Like with map_filename, H3SVG explicitly stores 100 bytes for this string, even if the path
    // is shorter than that:
    // * If any byte is the null terminator, then only the prefix before the first null
    //   terminator is used as the path.
    // * Otherwise, all 100 bytes are used as the path (the string doesn't have to be null-terminated).
    //
    // Subdirectories are supported (both forward '/' and backward '\' slash characters).
    //
    // Special filename ".." (the parent directory) is supported.
    //
    // Absolute paths (e.g., "F:\Maps") are NOT supported.
    std::array<char, 100> map_directory {};
    // TODO: figure out what this is.
    std::array<std::byte, 30> unknown3 {};
    // Original filename used for this saved game.
    // This doesn't seem to be used anywhere in the game.
    // This is also stored as a fixed-width string. Note that HoMM3 limits the length to 47 characters
    // (e.g., "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefg.GM1"), but it's probably not the limit of this field.
    // It's hard to figure out what the actual limit is, since the value is not used anywhere.
    // I don't know if this needs to be null-terminated (again, because it's not used anywhere).
    std::array<char, 47> original_filename {};
    // TODO: figure out what this is.
    // The last 50 bytes look like some bitmask, but I don't know the meaning yet.
    std::array<std::byte, 352> unknown4 {};
    // Bitmask indicating which artifacts are disabled on this map (1 - disabled, 0 - enabled).
    ArtifactsBitmask disabled_artifacts;
    // Another bitmask for artifacts; the meaning is not clear yet.
    // TODO: figure out what this is. It seems that the value is always 1 if the artifact is disabled,
    // but it can also be 1 even if the artifact is enabled.
    ArtifactsBitmask artifacts_bitmask_unknown;
    // Bitmask indicating which secondary skills are disabled on this map (1 - disabled, 0 - enabled).
    SecondarySkillsBitmask disabled_skills;
    // The currently displayed rumor in the Tavern.
    std::string current_rumor;

    // TODO: reverse-engineer the rest.
    // The next fields are approximately:
    // * Custom rumors that can appear in the Tavern
    // * Tiles data (similar to h3m::Tile, but seem to contain more info; visibility per player?)
    // * Object templates
    // * Objects on the Adventure map
    // * Settings for each hero
    //
    // Obviuously, there are other fields as well, but I don't know yet where they are located:
    // * current resources for each player
    // * artifacts in Artifacts Merchant
    // * Current heroes in the Tavern
    // * which player has visited the Keymaster's tent (for each Keymaster's tent subtype)
    // * Order of heroes (although this might be determined by their order in the objects array).
    // * Which heroes have been defeated by the player (needed in quests)
    // * etc.
  };
}
