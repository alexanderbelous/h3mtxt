#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/SavedGame/Constants/CartographerType.h>
#include <h3mtxt/SavedGame/Constants/KeymastersTentType.h>
#include <h3mtxt/SavedGame/Constants/VisitableObjectType.h>
#include <h3mtxt/SavedGame/ArtifactMerchants.h>
#include <h3mtxt/SavedGame/CreatureBank.h>
#include <h3mtxt/SavedGame/Date.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>
#include <h3mtxt/SavedGame/Hero.h>
#include <h3mtxt/SavedGame/LossCondition.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>
#include <h3mtxt/SavedGame/Object.h>
#include <h3mtxt/SavedGame/ObjectTemplate.h>
#include <h3mtxt/SavedGame/Player.h>
#include <h3mtxt/SavedGame/PlayerSpecs.h>
#include <h3mtxt/SavedGame/Portals.h>
#include <h3mtxt/SavedGame/ReplayEvent.h>
#include <h3mtxt/SavedGame/Rumor.h>
#include <h3mtxt/SavedGame/ScenarioStartingInfo.h>
#include <h3mtxt/SavedGame/Tile.h>
#include <h3mtxt/SavedGame/TileVisibility.h>
#include <h3mtxt/SavedGame/Town.h>
#include <h3mtxt/SavedGame/University.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace h3svg
{
  // Represents a saved game for Heroes of Might and Magic 3 (.CGM, .GM1, .GM2, ... files).
  //
  // HoMM3 uses the same format for saved maps and saved campaigns, so this class is used for both.
  struct SavedGame
  {
    // Signature for saved maps.
    static constexpr std::string_view kSignatureMap = "H3SVG";
    // Signature for saved campaigns.
    static constexpr std::string_view kSignatureCampaign = "H3SVC";

    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes).
    // This must always be one of the following:
    // * "H3SVG", which is normally used for standalone maps.
    // * "H3SVC", which is normally used for campaigns.
    // Note, however, that the game doesn't really care which signature is used: instead,
    // it relies on this->starting_info.campaign_info.has_value() to distinguish
    // between standalone scenarios and campaigns.
    //
    // FYI: apparently, HD Mod used to use "HDSvG" instead (when using HD+ ?),
    // but this doesn't seem to be the case anymore.
    FixedLengthString<5> signature = "H3SVG";
    ReservedData<3> reserved1;
    std::uint32_t version_major = 42;
    std::uint32_t version_minor = 2;
    // HD mod keeps this zero-initialized; the vanilla game (HoMM3 Complete) doesn't, but the values
    // don't seem to mean anything.
    ReservedData<32> reserved2;
    // Format of the map.
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map.
    MapBasicInfo basic_info;
    // Basic information about the players.
    EnumIndexedArray<PlayerColor, PlayerSpecs, h3m::kMaxPlayers> players_specs;
    VictoryCondition victory_condition;
    LossCondition loss_condition;
    Teams teams;
    std::vector<CustomHero> custom_heroes;
    // 16 bytes with unknown meaning: the values are always {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    // Modifying these bytes doesn't seem to affect anything.
    // The last 8 bytes are likely supposed to represent handicap, but the game ignores doesn't read it
    // from the saved games (bug?) and doesn't support modifying handicap when loading saved games.
    std::array<std::uint8_t, 16> unknown1 = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7 };
    // Starting settings for this scenario.
    ScenarioStartingInfo starting_info;
    // Original filename used for this saved game.
    // This doesn't seem to be used anywhere in the game.
    // This is also stored as a fixed-width string. Note that HoMM3 limits the length to 47 characters
    // (e.g., "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefg.GM1"), but it's probably not the limit of this field.
    // It's hard to figure out what the actual limit is, since the value is not used anywhere.
    // I don't know if this needs to be null-terminated (again, because it's not used anywhere).
    FixedLengthString<47> original_filename;
    // TODO: figure out what this is.
    // The last 50 bytes look like some bitmask, but I don't know the meaning yet.
    std::array<std::uint8_t, 352> unknown2 {};
    // Array of boolean values indicating which artifacts are disabled on this map (1 - disabled, 0 - enabled).
    EnumIndexedArray<ArtifactType, Bool, h3m::kNumArtifactTypes> disabled_artifacts;
    // Another array of boolean values for artifacts; the meaning is not clear yet.
    // TODO: figure out what this is. It seems that the value is always 1 if the artifact is disabled,
    // but it can also be 1 even if the artifact is enabled.
    // * The value is often (but not always) 1 if the artifact is present on the map.
    EnumIndexedArray<ArtifactType, Bool, h3m::kNumArtifactTypes> artifacts_bitmask_unknown;
    // Array of boolean values indicating which secondary skills are disabled on this map (1 - disabled, 0 - enabled).
    EnumIndexedArray<SecondarySkillType, Bool, h3m::kNumSecondarySkills> disabled_skills;
    // The currently displayed rumor in the Tavern.
    std::string current_rumor;
    // TODO: figure out what this is.
    // The values seem to always be either 0x00 or 0x01; mostly 0x00.
    std::array<std::uint8_t, 256> unknown3 {};
    // Custom rumors that can appear in the Tavern.
    std::vector<Rumor> rumors;
    // Artifacts currently available in Black Markets on the Adventure Map.
    // Ideally, this should be a member of object_properties_tables, but in H3SVG it is serialized
    // immediately after rumors.
    std::vector<ArtifactMerchants> black_markets;
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
    EnumIndexedArray<PlayerColor, Player, h3m::kMaxPlayers> players;
    // Towns on the Adventure Map.
    std::vector<Town> towns;
    // The number of elements must always be equal to h3m::kNumHeroes (156).
    // However, I'm not using std::array here because that would make sizeof(SavedGame) Hueg Like XBox (~160KB).
    std::vector<Hero> heroes;
    // Owner for each hero.
    // * 0x40 is a special value indicating that the hero is disabled
    //   OR currently available in the Tavern for some player.
    EnumIndexedArray<HeroType, PlayerColor, h3m::kNumHeroes> hero_owner {};
    // 156 bitmasks - 1 per HeroType, indicating which players can hire this hero.
    // The value is meaningless if this hero is disabled altogether (usually 0xFF).
    // Partially duplicates @custom_heroes.
    EnumIndexedArray<HeroType, PlayersBitmask, h3m::kNumHeroes> hero_can_be_hired_by {};
    std::array<std::uint8_t, 2> unknown4 {};
    // Coordinates of the Grail or (-1,-1,-1) if there is none.
    std::int16_t grail_x = -1;
    std::int16_t grail_y = -1;
    std::int8_t grail_z = -1;
    std::array<std::uint8_t, 3> unknown5 {};
    // Indicates whether any player has cheated.
    Bool is_cheater = false;
    // The current date.
    Date current_date;
    // TODO: figure out what this is.
    // * Always 0s?
    std::array<std::uint8_t, 32> unknown6 {};
    ArtifactMerchants artifact_merchants;
    // 1 PlayersBitmask per VisitableObjectType, indicating which players have visited an object of this type.
    // This is used in the game to determine whether to show the description when hovering over an object of this type.
    EnumIndexedArray<VisitableObjectType, PlayersBitmask, 32> visited_objects;
    // 8 bitmasks - 1 for each Keymaster's Tent type - indicating which players have visited that Keymaster's Tent.
    EnumIndexedArray<KeymastersTentType, PlayersBitmask, kNumKeymastersTentTypes> keymasters_tents;
    // 3 bitmasks - 1 for each Cartographer type - indicating which TerrainTypes are revealed by this Cartographer.
    EnumIndexedArray<CartographerType, TerrainsBitmask, kNumCartographerTypes> cartographer_effects = {
      .data = {
        TerrainsBitmask{.bitset {.data = {0, 1}}},   // Only Water
        TerrainsBitmask{.bitset {.data = {191, 0}}}, // All except Subterranean and Water
        TerrainsBitmask{.bitset {.data = {64, 0}}}   // Only Subterranean
      }
    };
    // 3 bitmasks - 1 for each Cartographer type - indicating which players have visited that Cartographer.
    EnumIndexedArray<CartographerType, PlayersBitmask, kNumCartographerTypes> cartographer_visited;
    // TODO: figure out what this is.
    // Seems to always be 0s.
    std::array<std::uint8_t, 4> unknown7 {};
    // Visibility of each tile for each player.
    // The number of elements should be (has_two_levels ? 2 : 1) * map_size * map_size,
    // i.e. countTiles(this->basic_info).
    // Tile (x, y, z) has the index ((z * map_size + y) * map_size + x).
    std::vector<TileVisibility> fog_of_war;
    // Information about all portals on the map (i.e. Monoliths, Whirlpools and Subterranean Gates).
    Portals portals;
    // Properties for each University on the Adventure Map.
    // The length is serialized as a 16-bit integer.
    std::vector<University> universities;
    // Creature banks on the Adventure Map.
    // The length is serialized as a 16-bit integer.
    std::vector<CreatureBank> creature_banks;
    // Data recorded for the last turn for all players.
    // The length is serialized as a 32-bit integer.
    std::vector<ReplayEvent> previous_turn;

    // TODO: when using SoD_SP, there seem to be some extra bytes after `previous_turn`, but it's unclear how many.
    // Discarding these bytes seems unwise - they might store meaningful data for SoD_SP. The safest approach
    // would be to exhaust the input stream when reading the saved game (or, in case of GZIP-compressed files,
    // get the size of the uncompressed data from GZIP metadata), and store it, for example,
    // as std::vector<std::uint8_t>.
  };
}
