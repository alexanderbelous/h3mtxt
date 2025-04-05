#pragma once

#include <h3mtxt/Map/Constants/ObjectClass.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // Enum type that makes it easier to determine which properties are applicable to objects
  // based on their ObjectClass and subtype.
  //
  // Different objects on the Adventure Map have different properties in H3M. Generally, it is
  // sufficient to know the ObjectClass of the object (ObjectTemplate::object_class) to deduce
  // which properties it has. However, in the Shadow of Death there are 2 exceptions where the
  // object's subtype (ObjectTemplate::object_subclass) is also needed: ObjectClass::MINE and
  // ObjectClass::ABANDONED_MINE. Specifically, their properties are either:
  // * the owner (PlayerColor) if subtype is within [0; 6], or
  // * the potential resources (ResourcesBitmask) if subtype == 7 (which represents an Abandoned Mine).
  //
  // There is no explicit concept of ObjectPropertiesType in the H3M format - this is just added here
  // to simplify the representation of Object. Objects that have the same set of properties
  // have the same ObjectPropertiesType.
  enum class ObjectPropertiesType
  {
    ABANDONED_MINE,
    ARTIFACT,
    EVENT,
    GARRISON,
    GENERIC_NO_PROPERTIES,  // Any object for which Object doesn't store any additional info.
    GRAIL,
    HERO,  // HERO, PRISON and RANDOM_HERO
    MONSTER,
    PANDORAS_BOX,
    PLACEHOLDER_HERO,
    QUEST_GUARD,
    RANDOM_DWELLING,
    RANDOM_DWELLING_PRESET_ALIGNMENT,
    RANDOM_DWELLING_PRESET_LEVEL,
    RESOURCE,
    SCHOLAR,
    SEERS_HUT,
    SHRINE,
    SIGN,  // SIGN and OCEAN_BOTTLE.
    SPELL_SCROLL,
    TOWN,
    TRIVIAL_OWNED_OBJECT,  // Any object whose only property is the owner (non-random dwelling, lighthouse, mine, shipyard).
    WITCH_HUT
  };

  inline constexpr std::uint32_t kNumObjectPropertiesTypes = 23;

  // Returns ObjectPropertiesType for the given object.
  // \param object_class - ObjectClass of the object.
  // \param object_subtype - subtype of the object.
  // \return ObjectPropertiesType for the input object.
  // \throw std::runtime_error if @object_class is not a valid object class.
  constexpr ObjectPropertiesType getObjectPropertiesType(ObjectClass object_class, std::uint32_t object_subtype)
  {
    // The Shadow of Death has 232 object types; @object_class must be within [0; 231].
    if (static_cast<std::underlying_type_t<ObjectClass>>(object_class) >= kNumObjectClasses)
    {
      throw std::runtime_error("Invalid object_class.");
    }

    switch (object_class)
    {
    // ObjectClass::MINE and ObjectClass::ABANDONED_MINE are edge cases -
    // their ObjectPropertiesType depends on the subtype.
    case ObjectClass::ABANDONED_MINE:
    case ObjectClass::MINE:
      return object_subtype == 7 ? ObjectPropertiesType::ABANDONED_MINE
                                 : ObjectPropertiesType::TRIVIAL_OWNED_OBJECT;

    // For everything else ObjectPropertiesType can be determined from ObjectClass alone.
    case ObjectClass::ARTIFACT:
    case ObjectClass::RANDOM_ART:
    case ObjectClass::RANDOM_TREASURE_ART:
    case ObjectClass::RANDOM_MINOR_ART:
    case ObjectClass::RANDOM_MAJOR_ART:
    case ObjectClass::RANDOM_RELIC_ART:
      return ObjectPropertiesType::ARTIFACT;
    case ObjectClass::EVENT:
      return ObjectPropertiesType::EVENT;
    case ObjectClass::GARRISON:
    case ObjectClass::GARRISON2:
      return ObjectPropertiesType::GARRISON;
    case ObjectClass::GRAIL:
      return ObjectPropertiesType::GRAIL;
    case ObjectClass::HERO:
    case ObjectClass::PRISON:
    case ObjectClass::RANDOM_HERO:
      return ObjectPropertiesType::HERO;
    case ObjectClass::MONSTER:
    case ObjectClass::RANDOM_MONSTER:
    case ObjectClass::RANDOM_MONSTER_L1:
    case ObjectClass::RANDOM_MONSTER_L2:
    case ObjectClass::RANDOM_MONSTER_L3:
    case ObjectClass::RANDOM_MONSTER_L4:
    case ObjectClass::RANDOM_MONSTER_L5:
    case ObjectClass::RANDOM_MONSTER_L6:
    case ObjectClass::RANDOM_MONSTER_L7:
      return ObjectPropertiesType::MONSTER;
    case ObjectClass::PANDORAS_BOX:
      return ObjectPropertiesType::PANDORAS_BOX;
    case ObjectClass::HERO_PLACEHOLDER:
      return ObjectPropertiesType::PLACEHOLDER_HERO;
    case ObjectClass::RANDOM_DWELLING:
      return ObjectPropertiesType::RANDOM_DWELLING;
    case ObjectClass::RANDOM_DWELLING_LVL:
      return ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL;
    case ObjectClass::RANDOM_DWELLING_FACTION:
      return ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT;
    case ObjectClass::QUEST_GUARD:
      return ObjectPropertiesType::QUEST_GUARD;
    case ObjectClass::RESOURCE:
    case ObjectClass::RANDOM_RESOURCE:
      return ObjectPropertiesType::RESOURCE;
    case ObjectClass::SCHOLAR:
      return ObjectPropertiesType::SCHOLAR;
    case ObjectClass::SEER_HUT:
      return ObjectPropertiesType::SEERS_HUT;
    case ObjectClass::SHRINE_OF_MAGIC_INCANTATION:
    case ObjectClass::SHRINE_OF_MAGIC_GESTURE:
    case ObjectClass::SHRINE_OF_MAGIC_THOUGHT:
      return ObjectPropertiesType::SHRINE;
    case ObjectClass::OCEAN_BOTTLE:
    case ObjectClass::SIGN:
      return ObjectPropertiesType::SIGN;
    case ObjectClass::SPELL_SCROLL:
      return ObjectPropertiesType::SPELL_SCROLL;
    case ObjectClass::RANDOM_TOWN:
    case ObjectClass::TOWN:
      return ObjectPropertiesType::TOWN;
    case ObjectClass::CREATURE_GENERATOR1:
    case ObjectClass::CREATURE_GENERATOR2:
    case ObjectClass::CREATURE_GENERATOR3:
    case ObjectClass::CREATURE_GENERATOR4:
    case ObjectClass::LIGHTHOUSE:
    case ObjectClass::SHIPYARD:
      return ObjectPropertiesType::TRIVIAL_OWNED_OBJECT;
    case ObjectClass::WITCH_HUT:
      return ObjectPropertiesType::WITCH_HUT;
    // All other objects have no properties.
    default:
      return ObjectPropertiesType::GENERIC_NO_PROPERTIES;
    }
  }
}
