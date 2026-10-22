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
    Pyramid,
    SeersHut,
    Shrine,
    Sign,
    TreeOfKnowledge,
    University,
    WitchHut
  };

  inline constexpr std::size_t kNumObjectPropertiesTypes = 17;

  // Returns ObjectPropertiesType for the given ObjectClass.
  // \param object_class - ObjectClass of the object.
  // \return ObjectPropertiesType for the input object.
  constexpr ObjectPropertiesType getObjectPropertiesType(ObjectClass object_class)
  {
    switch (object_class)
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
    case ObjectClass::PYRAMID:
      return ObjectPropertiesType::Pyramid;
    case ObjectClass::SHRINE_OF_MAGIC_INCANTATION:
    case ObjectClass::SHRINE_OF_MAGIC_GESTURE:
    case ObjectClass::SHRINE_OF_MAGIC_THOUGHT:
      return ObjectPropertiesType::Shrine;
    case ObjectClass::OCEAN_BOTTLE:
    case ObjectClass::SIGN:
      return ObjectPropertiesType::Sign;
    case ObjectClass::SEER_HUT:
      return ObjectPropertiesType::SeersHut;
    case ObjectClass::TREE_OF_KNOWLEDGE:
      return ObjectPropertiesType::TreeOfKnowledge;
    case ObjectClass::UNIVERSITY:
      return ObjectPropertiesType::University;
    case ObjectClass::WITCH_HUT:
      return ObjectPropertiesType::WitchHut;
    default:
      return ObjectPropertiesType::None;
    }
  }
}
