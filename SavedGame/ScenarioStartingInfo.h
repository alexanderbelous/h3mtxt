#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/SavedGame/EnumIndexedArray.h>
#include <h3mtxt/SavedGame/Constants/PlayerControlType.h>
#include <h3mtxt/SavedGame/Constants/PlayerStartingBonusType.h>
#include <h3mtxt/SavedGame/Constants/PlayerTurnDurationType.h>
#include <h3mtxt/SavedGame/Constants/TownType32.h>

#include <array>
#include <cstddef>

namespace h3svg
{
  // Starting settings for the map.
  //
  // The data in this class normally doesn't change during the game - H3SVG stores it so that it
  // can be displayed in "Scenario Information".
  struct ScenarioStartingInfo
  {
    // Starting town (i.e. alignment) for each player, or 0xFFFFFFFF if the player is absent.
    EnumIndexedArray<PlayerColor, TownType32, kMaxPlayers> starting_towns;
    // TODO: figure out what this is.
    // This looks like 1 byte per PlayerColor data:
    // * 0x00 is used for the human player.
    // * 0x0A is used for computer players.
    // * 0xFF is used for missing players.
    //
    // AFAIK, this only affects whether the player will be displayed in "Scenario Information" -
    // players, for which 0xFF is stored, will not be displayed. If you manually modify the saved
    // game and set 0xFF for an existing player, this player will not be shown in "Scenario
    // Information" anymore.
    std::array<std::byte, 8> unknown1 {};
    // Selected difficulty level.
    // This is different from MapBasicInfo::difficulty, which is set by the mapmaker and doesn't affect the game.
    MapDifficulty difficulty {};
    // The original filename of the map (this is used by Restart Scenario command).
    //
    // In H3SVG this is stored as a fixed-width string (251 bytes). Only the bytes up to the first null terminator are
    // significant - the rest often contain junk.
    //
    // Note that in practice it's hard to use long filenames because in Windows a path cannot be longer than MAX_PATH,
    // which is 260 characters by default. I've tested that filenames with 244 characters work; testing even longer
    // filenames requires more tricks, and I have better things to do.
    //
    // I'm not sure what's the best API for this: we can either store it as an array of 251 bytes, or as std::string.
    // Neither is perfect: on the one hand, the junk bytes should be ignored, but on the other hand, h3mtxt aims to
    // allow inspecting and modifying any byte, as long as it doesn't lead to corrupt data.
    //
    // For now, I will define this as an array of 251 bytes, but this might change in the future.
    std::array<char, 251> map_filename {};
    // Relative (to Heroes3.exe) path to the directory in which the original map is located.
    //
    // In H3SVG this is stored as a fixed-width string (100 bytes):
    // * If any byte is the null terminator, then only the prefix before the first null
    //   terminator is used as the path.
    // * Otherwise, all 100 bytes are used as the path (the string doesn't have to be null-terminated).
    //
    // Normally, this is always equal to "maps", but the game correctly handles other paths as well.
    // * Subdirectories are supported (both '/' and '\').
    // * Special filename ".." (the parent directory) is supported.
    // * Absolute paths (e.g., "F:\Maps") are NOT supported.
    std::array<char, 100> map_directory {};
    // 8 bytes: 1 byte per PlayerColor, indicating who can control this color
    // (0 - only CPU, 1 - Human or CPU, 0xFF - nobody).
    // This duplicates data from SavedGame::players, but H3SVG explicitly stores it, so we should too.
    EnumIndexedArray<PlayerColor, PlayerControlType, kMaxPlayers> players_control;
    // TODO: figure out what this is.
    // Seems to always be {255, 1, 1}
    std::array<std::byte, 3> unknown2 {};
    PlayerTurnDurationType player_turn_duration = PlayerTurnDurationType::Unlimited;
    EnumIndexedArray<PlayerColor, HeroType, kMaxPlayers> starting_heroes;
    EnumIndexedArray<PlayerColor, PlayerStartingBonusType, kMaxPlayers> starting_bonuses;
  };
}
