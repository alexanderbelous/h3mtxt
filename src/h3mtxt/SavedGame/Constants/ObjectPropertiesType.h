#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ObjectClass.h>

#include <cstdint>

namespace h3svg
{
  enum class ObjectPropertiesType
  {
    None,  // Used for objects that don't have properties (e.g., mountains, flowers, etc).
    BlackMarket,
    WitchHut
  };

  // Returns ObjectPropertiesType for the given object.
  // \param object_class - ObjectClass16 of the object.
  // \param object_subclass - subtype of the object.
  // \return ObjectPropertiesType for the input object.
  // \throw std::invalid_argument if @object_class and @object_subclass do not define a valid object type.
  constexpr ObjectPropertiesType getObjectPropertiesType(ObjectClass16 object_class, std::uint16_t)
  {
    switch (static_cast<ObjectClass>(object_class))
    {
    case ObjectClass::BLACK_MARKET:
      return ObjectPropertiesType::BlackMarket;
    case ObjectClass::WITCH_HUT:
      return ObjectPropertiesType::WitchHut;
    default:
      return ObjectPropertiesType::None;
    }
  }
}
