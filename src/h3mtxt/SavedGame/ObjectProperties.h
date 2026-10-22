#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/SavedGame/Constants/FloatsamContentType.h>
#include <h3mtxt/SavedGame/Constants/ObjectPropertiesType.h>
#include <h3mtxt/SavedGame/Constants/TreeOfKnowledgeType.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // In H3SVG the "simple" properties of an object on the Adventure Map are always serialized as 4 bytes,
  // whose meaning depends on ObjectClass.
  //
  // Credits to Maurice for reverse-engineering: http://heroescommunity.com/viewthread.php3?TID=46018
  //
  // H3SVG often uses bit packing to fit such "simple" properties into 4 bytes; to improve the API,
  // the specializations of ObjectProperties<T> below provide structured access to the properties.

  template<>
  struct ObjectProperties<ObjectPropertiesType::None>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::array<std::uint8_t, 4> reserved {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::BlackMarket>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in SavedGame::black_markets,
    // or -1 if this is not an actionable tile.
    std::int32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Campfire>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    ResourceType resource_type : 4 {};       // Bits [0; 3]
    std::uint8_t quantity : 4 = 0;           // Bits [4; 7]
    std::array<std::uint8_t, 3> reserved {}; // Bits [8; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::CreatureBank>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // Not used; 5 bits, always 1s by default.
    std::int8_t reserved1 : 5 = -1;
    PlayersBitmask visited_by;
    // 0-based of the element in SavedGame::creature_banks.
    // TODO: a few MSBs are not part of the index, they mean something else.
    std::uint16_t index : 14 = {};
    // Not used; 5 bits, always 1s by default.
    std::int8_t reserved2 : 5 = -1;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Dwelling>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::dwellings.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Corpse>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the corpse. This is used in h3svg::Player::corpses to keep track
    // of the corpses visited by the player.
    std::uint16_t id : 5 = {};
    std::uint16_t reserved1 : 1 = 1;
    ArtifactType artifact : 10 = ArtifactType::None;
    std::uint16_t is_lootable : 1 = false;
    std::int16_t reserved2 : 15 = -1;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Floatsam>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    FloatsamContentType content = FloatsamContentType::None;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::FountainOfFortune>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::int32_t reserved1 : 5 = -1;  // Bits [0; 4]
    std::int32_t reserved2 : 8 = 0;   // Bits [5; 12]
    std::int32_t luck_bonus : 4 = 0;  // Bits [13; 16]
    std::int32_t reserved3 : 15 = -1; // Bits [17; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Garrison>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::garrisons.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::LeanTo>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the Lean-To. This is used in h3svg::Player::lean_tos to keep track
    // of the Lean-Tos visited by the player.
    std::uint8_t index : 5 = {};         // Bits [0; 4]
    std::uint8_t reserved1 : 1 = 1;      // Bits [5; 5]
    std::uint8_t quantity : 4 = 0;       // Bits [6; 9]
    ResourceType resource_type : 4 = {}; // Bits [10; 13]
    std::int32_t reserved2 : 18 = -1;    // Bits [14; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Pyramid>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    SpellType spell = SpellType::None;     // Bits [13; 20]
    PlayersBitmask visited_by;             // Bits [5; 12]
    std::uint16_t is_lootable : 1 = false; // Bits [0; 0]
    std::int16_t reserved1 : 4 = -1;       // Bits [1; 4]
    std::int16_t reserved2 : 11 = -1;      // Bits [21; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SeersHut>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::seers_huts.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::ShipwreckSurvivor>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // TODO: check if this can be None.
    ArtifactType32 artifact {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Shrine>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    PlayersBitmask visited_by;        // Bits [5; 12]
    std::int16_t spell : 10 {};       // Bits [13; 22]
    std::int16_t reserved1 : 5 = -1;  // Bits [0; 4]
    std::int16_t reserved2 : 9 = -1;  // Bits [23; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Sign>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::signs_and_ocean_bottles.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::TreeOfKnowledge>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    PlayersBitmask visited_by;                                // Bits [5; 12]
    // 0-based index of the element in Hero::trees_of_knowledge.
    std::uint8_t index : 5 = {};                              // Bits [0; 4]
    TreeOfKnowledgeType type : 2 = TreeOfKnowledgeType::Free; // Bits [13; 14]
    std::uint8_t reserved1 : 1 = 0;                           // Bits [15; 15]
    std::int16_t reserved2 = -1;                              // Bits [16; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::University>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::int32_t reserved1 : 5 = -1;  // Bits [0; 4]
    std::int32_t reserved2 : 8 = 0;   // Bits [5; 12]
    // 0-based index of the element in SavedGame::universities,
    // or -1 if this is not an actionable tile.
    std::int32_t index : 12 = {};     // Bits [13; 24]
    std::int32_t reserved3 : 7 = -1;  // Bits [25; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::WitchHut>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::uint16_t reserved1 : 5 = 0;  // Bits [0; 4]
    std::uint16_t reserved2 : 11 = 0; // Bits [21; 31]
    // TODO: probably should be 7 bits (and reserved2 should be 12 bits):
    // None is represented by 0x7F, not by 0xFF.
    SecondarySkillType skill = static_cast<SecondarySkillType>(0x7F); // Bits [13; 20]
    PlayersBitmask visited_by;        // Bits [5; 12]
  };
}
