#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/SavedGame/Constants/FloatsamContentType.h>
#include <h3mtxt/SavedGame/Constants/ObjectPropertiesType.h>
#include <h3mtxt/SavedGame/Constants/SeaChestContentType.h>
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

  // FYI: the values are junk for non-actionable tiles (all bits are set to 1 by default).
  template<>
  struct ObjectProperties<ObjectPropertiesType::CreatureBank>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::int8_t reserved1 : 5 = -1;  // Bits [0; 4]
    PlayersBitmask visited_by;       // Bits [5; 12]
    // 0-based of the element in SavedGame::creature_banks.
    std::uint16_t index : 12 = {};   // Bits [13; 24]
    // Indicates whether this creature bank has been cleared.
    Bool is_cleared : 1 = false;     // Bits [25; 25]
    std::int8_t reserved2 : 6 = -1;  // Bits [26; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Dwelling>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::dwellings.
    std::uint32_t index {};
  };

  // FYI: the values are junk for non-actionable tiles (all bits are set to 1 by default).
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
  struct ObjectProperties<ObjectPropertiesType::Event>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::events_and_pandoras_boxes.
    std::uint16_t id : 10 = {};               // Bits [0; 9]
    PlayersBitmask affected_players;          // Bits [10; 17]
    Bool applies_to_computer : 1 = false;     // Bits [18; 18]
    Bool cancel_after_first_visit : 1 = true; // Bits [19; 19]
    std::uint16_t reserved : 12 = {};         // Bits [20; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Floatsam>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // Content or 0xFFFFFFFF if this is not an actionable tile.
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
  struct ObjectProperties<ObjectPropertiesType::Hero>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    HeroType32 hero {};
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
  struct ObjectProperties<ObjectPropertiesType::MysticalGarden>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    std::uint8_t index : 5 = {};
    std::uint8_t reserved1 : 1 = 1;
    ResourceType resource_type : 4 = ResourceType::Gold;
    Bool is_lootable : 1 = false;
    std::int32_t reserved2 : 21 = -1;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Obelisk>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // 0-based index of the element in ObjectPropertiesTables::obelisks.
    std::uint32_t index {};
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
  struct ObjectProperties<ObjectPropertiesType::RefugeeCamp>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // The number of creatures available for hire.
    // Note that the type of the creatures is stored in Tile::object_subclass.
    std::int32_t quantity = 0;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Scholar>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    ScholarRewardType type : 3 = {};                                    // Bits [0; 2]
    PrimarySkillType primary_skill : 3 {};                              // Bits [3; 5]
    SecondarySkillType secondary_skill : 7 {};                          // Bits [6; 12]
    SpellType16 spell : 10 = static_cast<SpellType16>(SpellType::None); // Bits [13; 22]
    std::int16_t reserved : 9 = -1;                                     // Bits [23; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::SeaChest>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    SeaChestContentType content : 2 = SeaChestContentType::Empty;                   // Bits [0; 1]
    std::uint32_t reserved1 : 1 = 0;                                                // Bits [2; 2]
    ArtifactType32 artifact : 10 = static_cast<ArtifactType32>(ArtifactType::None); // Bits [3; 12]
    std::int32_t reserved2 : 19 = -1;                                               // Bits [13; 31]
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

    // FYI: None (i.e. 0xFFFFFFFF) cannot be used here, causes the game to crash
    // when interacting with the Shipwreck Survivor.
    ArtifactType32 artifact {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Shrine>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    PlayersBitmask visited_by;        // Bits [5; 12]
    SpellType16 spell : 10 {};        // Bits [13; 22]
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
  struct ObjectProperties<ObjectPropertiesType::Wagon>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    ArtifactType artifact : 10 = ArtifactType::None; // Bits [15; 24]
    std::uint16_t has_artifact : 1 = false;          // Bits [14; 14]
    std::uint16_t resource_quantity : 5 = 0;         // Bits [0; 4]
    PlayersBitmask visited_by;                       // Bits [5; 12]
    ResourceType resource_type : 4 = {};             // Bits [25; 28]
    Bool is_lootable : 1 = false;                    // Bits [13; 13]
    std::int8_t reserved : 3 = -1;                   // Bits [29; 31]
  };

  // FYI: the values are junk for non-actionable tiles (all bits are set to 1 by default).
  template<>
  struct ObjectProperties<ObjectPropertiesType::WarriorsTomb>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // Indicates whether the tomb contains an artifact.
    Bool has_artifact : 1 = false;   // Bits [0; 0]
    std::int8_t reserved1 : 4 = -1;  // Bits [1; 4]
    PlayersBitmask visited_by;       // Bits [5; 12]
    // Note: ArtifactType::None should never be used for actionable tiles - this will cause the
    // game to crash when visiting the tomb. Instead, has_artifact should be set to 0.
    ArtifactType artifact : 10 = {}; // Bits [13; 22]
    std::int16_t reserved2 : 9 = -1; // Bits [23; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::WaterWheel>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    // Multiply by 500 to get the amount of Gold.
    std::uint8_t bonus : 5 = 0;      // Bits [0; 4]
    PlayersBitmask visited_by;       // Bits [5; 12]
    std::int32_t reserved : 19 = -1; // Bits [13; 31]
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Windmill>
  {
    constexpr bool operator==(const ObjectProperties&) const noexcept = default;

    ResourceType resource_type : 4 = {};    // Bits [0; 3]
    std::uint8_t resource_quantity : 4 = 0; // Bits [13; 16]
    PlayersBitmask visited_by;              // Bits [5; 12]
    std::uint16_t reserved1 : 1 = 1;        // Bits [4; 4]
    std::int16_t reserved2 : 15 = -1;       // Bits [17; 31]
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
