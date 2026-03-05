#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/SavedGame/Constants/TownType32.h>
#include <h3mtxt/SavedGame/Constants/PlayerTurnDurationType.h>
#include <h3mtxt/SavedGame/EnumIndexedArray.h>
#include <h3mtxt/SavedGame/EventBaseSvg.h>
#include <h3mtxt/SavedGame/ObjectSvg.h>
#include <h3mtxt/SavedGame/ObjectTemplateSvg.h>
#include <h3mtxt/SavedGame/PlayerSpecsSvg.h>
#include <h3mtxt/SavedGame/QuestSvg.h>
#include <h3mtxt/SavedGame/RewardSvg.h>
#include <h3mtxt/SavedGame/TileSvg.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace h3m
{
  // The equivalent of ObjectProperties<ObjectPropertiesType::ARTIFACT> in H3SVG.
  // Unlike H3M, guardians are not optional here.
  struct ArtifactSvg
  {
    GuardiansSvg guardians;
  };

  struct BlackMarket
  {
    // Each element should be either a valid ArtifactType constant or -1 if the slot is empty.
    std::array<ArtifactType32, 7> artifacts{};
  };

  struct MineSvg
  {
    PlayerColor owner {};
    // TODO: replace with something type-safe.
    // * For regular mines - stores {ResourceType, 0} (aka object_subclass of the mine).
    // * For lighthouses - stores {100, 0}.
    // * For abandoned mines - stores {ResourceType, 1}
    std::array<std::uint8_t, 2> unknown {};
    TroopsSvg creatures;
    Coordinates coordinates;
  };

  struct MonsterSvg
  {
    // Serialized in H3SVG as a length-prefixed string, with length being serialized as a 16-bit little-endian integer.
    std::string message;
    Resources resources;
    // ArtifactType or 0xFF if there is none.
    ArtifactType8 artifact {};
  };

  struct QuestGuardSvg
  {
    // Note: H3SVG stores QuestType::None for completed quests.
    QuestSvg quest;
    // 1 bit per player, indicating whether the player has visited this Quest Guard.
    PlayersBitmask visited_by;
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

  struct SeersHutSvg
  {
    // Note: H3SVG stores QuestType::None for completed quests.
    QuestSvg quest;
    // Reward, on the other hand, remains unchanged for completed quests.
    RewardSvg reward;
    std::uint8_t unknown1 {};
    PlayersBitmask visited_by;
    std::uint8_t unknown2 {};
  };

  struct SignSvg
  {
    std::string message;
    // 0 if a random default message should be displayed, 1 otherwise.
    // Note that in H3M an empty string implies that a random default message will be
    // displayed. However, in H3SVG this field has a higher priority - if you manually modify this
    // byte so that is_custom == 1, then some default message will be displayed even if !message.empty().
    Bool is_custom {};
  };

  // The equivalent of h3m::TimedEvent stored in the saved game.
  //
  // This is nearly identical to h3m::TimedEvent, except that `name` and `unknown` are missing.
  struct TimedEventSvg
  {
    std::string message;
    // Given/taken resources.
    Resources resources;
    PlayersBitmask affected_players;
    Bool applies_to_human {};
    Bool applies_to_computer {};
    // 0-based day of first occurence (e.g., 0 stands for Day 1).
    std::uint16_t day_of_first_occurence {};
    // Frequency of this event; 0 means that the event doesn't repeat.
    std::uint16_t repeat_after_days {};
  };

  // The equivalent of h3m::TownEvent stored in the saved game.
  struct TownEventSvg : TimedEventSvg
  {
    std::byte unknown1 {};
    // 1 bit per TownBuildingType indicating whether the building gets built.
    TownBuildingsBitmask buildings;
    std::array<std::byte, 2> unknown2 {};
    // Extra creatures for each creature level.
    std::array<std::uint16_t, 7> creatures {};
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
    EnumIndexedArray<PlayerColor, PlayerSpecsSvg, kMaxPlayers> players;
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
    // Actual alignment for each player, or 0xFFFFFFFF if the player is absent.
    EnumIndexedArray<PlayerColor, TownType32, kMaxPlayers> alignments;
    // TODO: figure out what this is.
    // This looks like 1 byte per PlayerColor data, where 0xFF is used for absent players.
    // It also seems that 0x00 is always used for the human player.
    std::array<std::byte, 8> unknown2 {};
    // Selected difficulty level.
    // This is different from basic_info.difficulty, which is set by the mapmaker and doesn't affect the game.
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
    std::array<std::byte, 3> unknown3 {};
    PlayerTurnDurationType player_turn_duration = PlayerTurnDurationType::Unlimited;
    EnumIndexedArray<PlayerColor, HeroType, kMaxPlayers> starting_heroes;
    EnumIndexedArray<PlayerColor, PlayerStartingBonusType, kMaxPlayers> starting_bonuses;
    // TODO: figure out what this is.
    // Seems to always be {0, 0}
    std::array<std::byte, 2> unknown4 {};
    // Original filename used for this saved game.
    // This doesn't seem to be used anywhere in the game.
    // This is also stored as a fixed-width string. Note that HoMM3 limits the length to 47 characters
    // (e.g., "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefg.GM1"), but it's probably not the limit of this field.
    // It's hard to figure out what the actual limit is, since the value is not used anywhere.
    // I don't know if this needs to be null-terminated (again, because it's not used anywhere).
    std::array<char, 47> original_filename {};
    // TODO: figure out what this is.
    // The last 50 bytes look like some bitmask, but I don't know the meaning yet.
    std::array<std::byte, 352> unknown5 {};
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
    std::array<std::byte, 256> unknown6 {};
    // Custom rumors that can appear in the Tavern.
    std::vector<RumorSvg> rumors;
    // Artifacts currently available in Black Markets on the Adventure Map.
    // TODO: check what is the order here. I guess these are either sorted by (x,y,z) or by object_idx.
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
    // Events and Pandora's Boxes on the Adventure Map.
    std::vector<EventBaseSvg> events_and_pandoras_boxes;
    // Artifacts and Spell scrolls on the Adventure Map.
    // FYI: it seems that the elements are persistent: they are not deleted even after a hero picks them up.
    // Guardians are mutable though.
    // TODO: rename to point out that this also includes resources on the adventure map.
    //       Tile::object_properties stores the quantity, but message&guardians are stored here.
    std::vector<ArtifactSvg> artifacts_and_spell_scrolls;
    // Wandering creatures on the Adventure Map.
    // TODO: consider renaming; this seems more like "monsters with custom message or treasure".
    std::vector<MonsterSvg> monsters;
    // Seer's Huts.
    std::vector<SeersHutSvg> seers_huts;
    // Quest guards.
    std::vector<QuestGuardSvg> quest_guards;
    // Global events (called "Timed Events" in the Map Editor).
    // FYI: it seems that HD mod appends one event to the end of this array.
    // The message looks like Base64-encoded data, but the meaning is unclear.
    // Perhaps, BIG BARATORCH IS WATCHING YOU.
    std::vector<TimedEventSvg> global_events;
    // Timed Events affecting a specific town.
    std::vector<TownEventSvg> town_events;
    // Signs and Ocean Bottles on the Adventure Map.
    std::vector<SignSvg> signs_and_ocean_bottles;
    // Mines, Abandoned Mines and Lighthouses
    std::vector<MineSvg> mines_and_lighthouses;

    // TODO: reverse-engineer the rest.
    // The next fields are approximately:
    // * std::vector<DwellingSvg>
    // * Settings for each town on the Adventure Map
    // * Settings for each hero
    //
    // Obviuously, there are other fields as well, but I don't know yet where they are located:
    // * Timestamp for the saved game (Heroes3.exe stores it somewhere in the file instead of using
    //   filesystem metadata)
    // * Current resources for each player
    // * Artifacts in Artifact Merchants
    // * Current heroes in the Tavern
    // * Which player has visited the Keymaster's tent (for each Keymaster's tent subtype)
    // * Order of heroes (although this might be determined by their order in the objects array).
    // * Which heroes have been defeated by the player (needed in quests)
    // * Previous turns for all opponents (probably for all players, because that would be
    //   necessary in multiplayer games).
    // * etc.
  };
}
