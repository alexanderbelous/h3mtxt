#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/SavedGame/ObjectTemplateSvg.h>
#include <h3mtxt/SavedGame/PlayerSpecsSvg.h>
#include <h3mtxt/SavedGame/TileSvg.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace h3m
{
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

  // Represents a saved game for Heroes of Might and Magic 3 (.GM1, .GM2, ... files).
  struct SavedGame
  {
    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: apparently, HD Mod may sometimes use "HDSvG" instead.
    static constexpr std::string_view kFileSignature = "H3SVG";

    ReservedData<3> reserved1;
    std::uint32_t version_major{};
    std::uint32_t version_minor{};
    // HD mod keeps this zero-initialized; the vanilla game (HoMM3 Complete) doesn't, but the values
    // don't seem to mean anything.
    ReservedData<32> reserved2;
    // Format of the map.
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map.
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
    // TODO: figure out what this is.
    // The values seem to always be either 0x00 or 0x01; mostly 0x00.
    std::array<std::byte, 256> unknown5 {};
    // Custom rumors that can appear in the Tavern.
    std::vector<RumorSvg> rumors;
    // TODO: figure out what this is.
    // There are some bytes between rumors and tiles in H3SVG, but their number is not constant.
    // It seems that the first byte is some number N, followed by N*28 bytes, which
    // look like N*7 32-bit integers.
    std::vector<std::array<std::int32_t, 7>> unknown6;
    // Terrain data for each tile on the map.
    // The number of elements should be (has_two_levels ? 2 : 1) * map_size * map_size,
    // i.e. countTiles(this->basic_info).
    // Tile (x, y, z) has the index ((z * map_size + y) * map_size + x).
    std::vector<TileSvg> tiles;
    // "Templates" for objects on the Adventure Map.
    std::vector<ObjectTemplateSvg> objects_templates;

    // TODO: reverse-engineer the rest.
    // The next fields are approximately:
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
