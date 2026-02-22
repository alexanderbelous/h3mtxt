#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
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
    // If !can_be_human && !can_be_computer, only 4 bytes should be read before starting_hero
    // (otherwise, it's 5 bytes).
    PlayerBehavior behavior{};
    TownsBitmask allowed_alignments;
    // TODO: I don't thinks these are actually padding bytes, but I don't know yet what they mean.
    ReservedData<2> unknown;
    HeroType starting_hero_type { 0xFF };
    HeroPortrait starting_hero_portrait = HeroPortrait::DEFAULT;
    // Empty string implies the default name. This field is only read/written if can_be_human || can_be_computer.
    // The length is serialized as a 16-bit integer.
    std::string starting_hero_name;
  };

  // Represents a saved game for Heroes of Might and Magic 3 (.GM1, .GM2, ... files).
  struct SavedGame
  {
    // The first 5 bytes are always the file signature (aka magic numbers / magic bytes): "H3SVG".
    // TODO: apparently, HD Mod may sometimes use "HDSvG" instead.
    static constexpr std::string_view kFileSignature = "H3SVG";

    ReservedData<3> reserved1;
    std::uint32_t version_major;
    std::uint32_t version_minor;
    // HD mod keeps this zero-initialized; the vanilla game (HoMM3 complete) doesn't, but the values
    // don't seem to mean anything.
    ReservedData<32> reserved2;
    // Format of the map (same as Map::format).
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map (same as Map::basic_info).
    //
    // Note, however, that the strings MapBasicInfo::name and MapBasicInfo::description are serialized
    // differently from how it's done in .h3m: the length of a string is serialized as a 16-bit integer,
    // whereas in .h3m it is serialized as a 32-bit integer.
    MapBasicInfo basic_info;

    // TODO: reverse-engineer the rest.
    std::array<PlayerSpecsSvg, 8> players {};
    VictoryCondition victory_condition;
    LossCondition loss_condition;
  };
}
