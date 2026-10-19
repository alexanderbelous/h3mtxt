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
    Campfire,
    CreatureBank,
    Dwelling,
    Corpse,
    Floatsam,
    FountainOfFortune,
    Garrison,
    LeanTo,
    University,
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
    case ObjectClass::CAMPFIRE:
      return ObjectPropertiesType::Campfire;
    case ObjectClass::CREATURE_BANK:
    case ObjectClass::DERELICT_SHIP:
    case ObjectClass::DRAGON_UTOPIA:
      return ObjectPropertiesType::CreatureBank;
    case ObjectClass::CREATURE_GENERATOR1:
      // TODO: probably should be returned for CREATURE_GENERATOR4 as well.
      return ObjectPropertiesType::Dwelling;
    case ObjectClass::CORPSE:
      return ObjectPropertiesType::Corpse;
    case ObjectClass::FLOTSAM:
      return ObjectPropertiesType::Floatsam;
    case ObjectClass::FOUNTAIN_OF_FORTUNE:
      return ObjectPropertiesType::FountainOfFortune;
    case ObjectClass::GARRISON:
    case ObjectClass::GARRISON2:
      return ObjectPropertiesType::Garrison;
    case ObjectClass::LEAN_TO:
      return ObjectPropertiesType::LeanTo;
    case ObjectClass::UNIVERSITY:
      return ObjectPropertiesType::University;
    case ObjectClass::WITCH_HUT:
      return ObjectPropertiesType::WitchHut;
    default:
      return ObjectPropertiesType::None;
    }
  }
}
