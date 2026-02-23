#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

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
    // The original filename of the map (I assume that's the filename used by Restart Scenario command).
    // Note: .GM* files store this as a null-terminated string, which is unusual (virtually all other
    // strings are stored as Pascal strings).
    std::string map_filename;

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
