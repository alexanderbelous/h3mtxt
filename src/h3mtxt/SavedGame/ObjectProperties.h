#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/SavedGame/Constants/ObjectPropertiesType.h>

#include <cstdint>

namespace h3svg
{
  // In H3SVG the "simple" properties of an object on the Adventure Map are always serialized as 4 bytes,
  // whose meaning depends on ObjectClass.
  // Credits to Maurice for reverse-engineering: http://heroescommunity.com/viewthread.php3?TID=46018

  // The equivalent of h3m::ObjectProperties stored in saved games.
  //
  // The properties of objects in H3SVG differ from their properties in H3M: for example, a
  // Shipwreck Survivor doesn't have any properties in H3M, but in H3SVG it stores the type of the
  // artifact that you will be rewarded with.
  //
  // In H3SVG this is always serialized as 4 bytes and fields are often packed. Every tile on the
  // Adventure Map stores such an array of 4 bytes (see h3svg::Tile::object_properties):
  // * If there is no object on the tile, the values are usually 0x00000000.
  // * If there is an object and this is an actionable tile, these bytes store the properties.
  // * Otherwise (if there is an object but the tile is not actionable), the behavior varies:
  //   * For some objects (e.g., UNIVERSITY) the bytes are always 0xFFFFFFFF.
  //   * For other objects (e.g., TOWN, PRISON) the bytes remain meaningful.
  //
  // Moreover, there are objects, for which 0xFFFFFFFF is a meaningful representation of their
  // properties: for example, for Magic Spring they would mean that it's the 31st Magic Spring on
  // the map and all players have visited it this week.
  //
  // This SUCKS. Without knowing if the tile is actionable you cannot say if the bytes are
  // meaningful, but this information is stored separately from the tile. We are left with 3
  // options:
  // 1) Always parse the bytes, which will lead to junk values for enums / creature counts / etc.
  // 2) Don't parse the bytes when reading the saved game, and just provide getters/setters,
  //    making it the responsibility of the user to check if the bytes are meaningful.
  // 3) Always try to parse the bytes, but detect 0xFFFFFFFF in places where it cannot represent
  //    meaningful properties (e.g., PRISON stores HeroType, but 0xFFFFFFFF doesn't reprsent a
  //    valid HeroType).
  //
  // Who fucking writes code like that?!
  //
  // Possible solution: add ObjectPropertiesType::JunkBytes, which is always serialized as
  // 0xFFFFFFFF. This is still lame - it means that for most ObjectClasses there are 2 valid
  // alternatives in std::variant. Alternatively - rename it to RawBytes and allow setting
  // arbitrary values to the stored bytes.
  // * This is a bit problematic for JSON deserialization, but workarounds exist: for example,
  //   I can say that object_properties is either a JSON object whose schema is determined by
  //   object_class, or a JSON array of 4 integers whose values are within [0; 255].

  template<>
  struct ObjectProperties<ObjectPropertiesType::None>
  {
    ReservedData<4> reserved;
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::BlackMarket>
  {
    // 0-based index of the element in SavedGame::black_markets.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Campfire>
  {
    ReservedData<3> reserved;
    std::uint8_t quantity : 4 = 0;
    ResourceType resource_type : 4 {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::CreatureBank>
  {
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
    // 0-based index of the element in ObjectPropertiesTables::dwellings.
    std::uint32_t index {};
  };

  template<>
  struct ObjectProperties<ObjectPropertiesType::Corpse>
  {
    // 0-based index of the corpse. This is used in h3svg::Player::corpses to keep track
    // of the corpses visited by the player.
    std::uint16_t id : 5 = {};
    std::uint16_t reserved1 : 1 = 1;
    ArtifactType artifact : 10 = ArtifactType::None;
    std::uint16_t is_lootable : 1 = false;
    std::int16_t reserved2 : 15 = -1;
  };
}
