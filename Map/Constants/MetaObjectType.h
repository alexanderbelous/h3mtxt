#pragma once

#include <h3mparser/Map/Constants/ObjectClass.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // ObjectDetails in H3M are different depending on ObjectAttributes.object_class.
  // However, a lot of object classes have the same details, so another layer of abstraction
  // is added here - an enum which groups object classes that have the same details.
  //
  // AFAIU, there's no explicit concept of MetaObjectType in the H3M format - this is just
  // added here to simplify the representation of ObjectDetails. Other H3M parsers may
  // define this enum differently in order to disambiguate between objects that have the
  // same "ObjectDetails" but serve different purposes. Here, however, we only care about
  // the stored data, so all objects that have the same "details" are grouped into the same
  // "MetaObjectType".
  enum class MetaObjectType
  {
    ABANDONED_MINE_ABSOD,
    ARTIFACT,
    ARTIFACT_AB,  // TODO: probably should be removed.
    ARTIFACT_SOD, // TODO: probably should be removed.
    DWELLING,
    DWELLING_ABSOD,
    EVENT,
    GARRISON,
    GARRISON_ABSOD,
    GENERIC_BOAT,
    GENERIC_IMPASSABLE_TERRAIN,
    GENERIC_IMPASSABLE_TERRAIN_ABSOD,
    GENERIC_PASSABLE_TERRAIN,
    GENERIC_PASSABLE_TERRAIN_SOD,
    GENERIC_TREASURE,
    GENERIC_VISITABLE,
    GENERIC_VISITABLE_ABSOD,
    GRAIL,
    HERO,
    HERO_AB,
    LIGHTHOUSE,
    MONOLITH_TWO_WAY,
    MONSTER,
    MONSTER_ABSOD,
    OCEAN_BOTTLE,
    PANDORAS_BOX,
    PLACEHOLDER_HERO,
    PRISON,
    QUEST_GUARD,
    RANDOM_DWELLING_ABSOD,
    RANDOM_DWELLING_PRESET_ALIGNMENT_ABSOD,
    RANDOM_DWELLING_PRESET_LEVEL_ABSOD,
    RANDOM_HERO,
    RESOURCE,
    RESOURCE_GENERATOR,
    SCHOLAR,
    SEERS_HUT,
    SHIPYARD,
    SHRINE,
    SIGN,
    SPELL_SCROLL,
    SUBTERRANEAN_GATE,
    TOWN,
    TOWN_ABSOD,
    WITCH_HUT
  };

  // Returns MetaObjectType for the given object class.
  // \param object_class - input object class.
  // \return MetaObjectType for @object_class.
  // \throw std::runtime_error if @object_class is not a valid object class.
  constexpr MetaObjectType getMetaObjectType(ObjectClass object_class)
  {
    switch (object_class)
    {
    case ObjectClass::EVENT:
      return MetaObjectType::EVENT;
    case ObjectClass::GRAIL:
      return MetaObjectType::GRAIL;
    case ObjectClass::HERO:
      return MetaObjectType::HERO;
    case ObjectClass::LIGHTHOUSE:
      return MetaObjectType::LIGHTHOUSE;
    case ObjectClass::PANDORAS_BOX:
      return MetaObjectType::PANDORAS_BOX;
    default:
      // TODO: implement the rest.
      throw std::runtime_error("Invalid object_class.");
    }
  }
}
