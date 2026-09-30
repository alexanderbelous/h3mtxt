#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/makeArrayOfDuplicates.h>
#include <h3mtxt/SavedGame/Constants/PlayerControlType.h>
#include <h3mtxt/SavedGame/Constants/PlayerStartingBonusType.h>
#include <h3mtxt/SavedGame/Constants/PlayerType.h>
#include <h3mtxt/SavedGame/Constants/TownType32.h>
#include <h3mtxt/SavedGame/Constants/TurnDurationType.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>

#include <array>
#include <cstddef>
#include <optional>
#include <vector>

namespace h3svg
{
  // Starting settings for the map.
  //
  // The data in this class doesn't change during the game.
  // The game uses it in "Scenario Information" and "Restart Scenario" commands.
  //
  // Similar to h3::H3PlayersInfo in H3API.
  struct ScenarioStartingInfo
  {
    // Starting town (i.e. alignment) for each player, or 0xFFFFFFFF if the player is absent.
    EnumIndexedArray<PlayerColor, TownType32, h3m::kMaxPlayers> starting_towns = {
      .data = h3m::Detail_NS::makeArrayOfDuplicates<h3m::kMaxPlayers>(TownType32{-1})
    };
    // Type for each player (Human/Computer), or 0xFF if the player is absent.
    // AFAIK, this only affects whether the player will be displayed in "Scenario Information" -
    // players, for which 0xFF is stored, will not be displayed. If you manually modify the saved
    // game and set 0xFF for an existing player, this player will not be shown in "Scenario
    // Information" anymore.
    EnumIndexedArray<PlayerColor, PlayerType, h3m::kMaxPlayers> player_types = {
      .data = h3m::Detail_NS::makeArrayOfDuplicates<h3m::kMaxPlayers>(PlayerType::None)
    };
    // Selected difficulty level.
    // This is different from MapBasicInfo::difficulty, which is set by the mapmaker and doesn't affect the game.
    MapDifficulty difficulty = MapDifficulty::Normal;
    // The original filename of the map (this is used by Restart Scenario command).
    //
    // For campaign scenarios the game always writes "test.h3m" here.
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
    FixedLengthString<251> map_filename;
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
    //
    // For campaigns this is normally an empty string.
    FixedLengthString<100> map_directory;
    // 8 bytes: 1 byte per PlayerColor, indicating who can control this color
    // (0 - only CPU, 1 - Human or CPU, 0xFF - nobody).
    // This duplicates data from SavedGame::players, but H3SVG explicitly stores it, so we should too.
    EnumIndexedArray<PlayerColor, PlayerControlType, h3m::kMaxPlayers> players_control = {
      .data = h3m::Detail_NS::makeArrayOfDuplicates<h3m::kMaxPlayers>(PlayerControlType::None)
    };
    // Unknown; seems to always be {255, 1, 1}.
    std::array<std::uint8_t, 3> unknown = { 255, 1, 1 };
    // 1 byte indicating player turn duration.
    // The value is junk for campaigns (usually zero-initialized). Note that
    // limiting player turn duration is not supported in campaigns at all.
    TurnDurationType player_turn_duration = TurnDurationType::Unlimited;
    // 8 bytes: 1 byte per player, indicating the type of the starting hero.
    // The values are junk for campaigns (usually zero-initialized).
    EnumIndexedArray<PlayerColor, HeroType, h3m::kMaxPlayers> starting_heroes = {
      .data = h3m::Detail_NS::makeArrayOfDuplicates<h3m::kMaxPlayers>(HeroType{0xFFu})
    };
    // 8 bytes: 1 byte per player, indicating the type of the starting bonus.
    // The values are junk for campaigns (usually zero-initialized).
    EnumIndexedArray<PlayerColor, PlayerStartingBonusType, h3m::kMaxPlayers> starting_bonuses = {
      .data = h3m::Detail_NS::makeArrayOfDuplicates<h3m::kMaxPlayers>(PlayerStartingBonusType::Random)
    };
    // Campaign-specific data, or std::nullopt if this is a standalone map.
    std::optional<CampaignInfo> campaign_info;
    // Hero placeholders configured as "Specific" (as opposed to "Power rating").
    // Note that is explicitly serialized even for standalone maps, in which case it will
    // be an empty vector even if the original .h3m file has placeholder heroes (they disappear
    // at the start of the game anyway).
    // Size is serialized as an 8-bit integer.
    std::vector<HeroType16> placeholder_heroes;
  };
}
