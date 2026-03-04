#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/SavedGame/Constants/ObjectPropertiesSvgType.h>

namespace h3m
{
  // The equivalent of h3m::ObjectProperties stored in saved games.
  //
  // The properties of objects in H3SVG differ from their properties in H3M: for example, a
  // Shipwreck Survivor doesn't have any properties in H3M, but in H3SVG it stores the type of the
  // artifact that you will be rewarded with.
  //
  // Note that for some objects their properties are stored in a separate table, and
  // ObjectPropertiesSvg simply stores the index of the element in that table.
  //
  // Also note that in H3SVG this is always serialized as 4 bytes and fields are often packed.
  template<ObjectPropertiesSvgType T>
  struct ObjectPropertiesSvg;

  template<>
  struct ObjectPropertiesSvg<ObjectPropertiesSvgType::None>
  {
    ReservedData<4> reserved;
  };
}
