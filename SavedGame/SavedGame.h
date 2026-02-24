#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace h3m
{
  // The equivalent of PlayersSpecs stored in the saved game.
  struct PlayerSpecsSvg
  {
    Bool can_be_human{};
    Bool can_be_computer{};
    PlayerBehavior behavior{};
    TownsBitmask allowed_alignments;
    // TODO: I don't thinks these are actually padding bytes, but I don't know yet what they mean.
    ReservedData<2> unknown;
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
    // Seems to always be {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    // The values suggest that it has something to do with players, but it's
    // hard to figure out what it is without other examples.
    ReservedData<16> unknown1;
    // Currently unknown, but looks like some bitmask(s) (artifacts ?).
    // This data seem to be a property of the map rather than the saved game:
    // the values don't seem to change throught the game.
    // * Actually, the first 32 bytes seem to represent 8 32-bit integers, which
    //   have something to do with the players (and 0xFFFFFFFF being used for absent players).
    ReservedData<41> unknown2;
    // The original filename of the map (this is used by Restart Scenario command).
    //
    // Note: H3SVG uses an idiotic convention for storing this field - the string is always serialized
    // as 48 bytes, where the last byte is the null terminator (the maximum allowed length of the filename
    // without the null terminator is 47 characters). However, a null terminator may appear earlier
    // (if the filename is shorter than 47 characters), in which case the bytes after the first null
    // terminator may contain junk.
    //
    // I'm not sure what's the best API for this: we can either store it as an array of 48 bytes,
    // or as std::string. Neither is perfect: on the one hand, the junk bytes should be ignored, but on
    // the other hand, h3mtxt aims to allow inspecting and modifying any byte, as long as it doesn't lead
    // to corrupt data.
    //
    // For now, I will define this as an array of 48 bytes, but this might change in the future.
    //
    // TODO: it's possible that longer filenames are allowed, and that SavedGame::reserved3 should
    // be defined as a shorter block. Requires investigating.
    // TODO: check if it actually has to be null-terminated.
    std::array<char, 48> map_filename {};
    // Seems to always be zero-filled.
    ReservedData<203> reserved3;
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

    // TODO: reverse-engineer the rest.
    // The next fields are approximately:
    // * Original name of the saved game file
    // * The currently displayed rumor in the Tavern
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
