#pragma once

#include <h3mtxt/Map/Constants/ObjectClass.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // Enum type that that makes it easier to determine which properties are applicable to objects
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
  // AFAIU, there's no explicit concept of MetaObjectType in the H3M format - this is just added here
  // to simplify the representation of Object. Some other H3M parsers define this enum differently
  // in order to disambiguate between objects that have the same set of properties but serve different
  // purposes. Here, however, we only care about the stored data, so all objects that have the same
  // "details" are grouped into the same "MetaObjectType".
  //
  // TODO: consider renaming to ObjectPropertiesType.
  enum class MetaObjectType
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

  inline constexpr std::uint32_t kNumMetaObjectTypes = 23;

  // Returns MetaObjectType for the given object.
  // \param object_class - ObjectClass of the object.
  // \param object_subtype - subtype of the object.
  // \return MetaObjectType for the input object.
  // \throw std::runtime_error if @object_class is not a valid object class.
  constexpr MetaObjectType getMetaObjectType(ObjectClass object_class, std::uint32_t object_subtype)
  {
    switch (object_class)
    {
    // ObjectClass::MINE and ObjectClass::ABANDONED_MINE are edge cases - their MetaObjectType depends on the subtype.
    case ObjectClass::ABANDONED_MINE:
    case ObjectClass::MINE:
      return object_subtype == 7 ? MetaObjectType::ABANDONED_MINE : MetaObjectType::TRIVIAL_OWNED_OBJECT;

    // For everything else MetaObjectType can be determined from ObjectClass alone.
    case ObjectClass::ARTIFACT:
    case ObjectClass::RANDOM_ART:
    case ObjectClass::RANDOM_TREASURE_ART:
    case ObjectClass::RANDOM_MINOR_ART:
    case ObjectClass::RANDOM_MAJOR_ART:
    case ObjectClass::RANDOM_RELIC_ART:
      return MetaObjectType::ARTIFACT;
    case ObjectClass::EVENT:
      return MetaObjectType::EVENT;
    case ObjectClass::GARRISON:
    case ObjectClass::GARRISON2:
      return MetaObjectType::GARRISON;

    // GENERIC_IMPASSABLE_TERRAIN
    case ObjectClass::NONE_0:
    case ObjectClass::BLANK_40:
    case ObjectClass::IMPASSABLE_BRUSH:
    case ObjectClass::IMPASSABLE_BUSH:
    case ObjectClass::IMPASSABLE_CACTUS:
    case ObjectClass::IMPASSABLE_CANYON:
    case ObjectClass::IMPASSABLE_CRATER:
    case ObjectClass::IMPASSABLE_DEADVEGETATION:
    case ObjectClass::IMPASSABLE_FLOWERS:
    case ObjectClass::IMPASSABLE_FROZENLIKE:
    case ObjectClass::IMPASSABLE_HEDGE:
    case ObjectClass::IMPASSABLE_HILL:
    case ObjectClass::IMPASSABLE_LAKE:
    case ObjectClass::IMPASSABLE_LAVAFLOW:
    case ObjectClass::IMPASSABLE_LAVALAKE:
    case ObjectClass::IMPASSABLE_MUSHROOMS:
    case ObjectClass::IMPASSABLE_LOG:
    case ObjectClass::IMPASSABLE_MANDRAKE:
    case ObjectClass::IMPASSABLE_MOSS:
    case ObjectClass::IMPASSABLE_MOUND:
    case ObjectClass::IMPASSABLE_MOUNTAIN:
    case ObjectClass::IMPASSABLE_OAKTREES:
    case ObjectClass::IMPASSABLE_OUTCROPPING:
    case ObjectClass::IMPASSABLE_PINETREES:
    case ObjectClass::IMPASSABLE_PLANT:
    case ObjectClass::IMPASSABLE_RIVERDELTA:
    case ObjectClass::IMPASSABLE_ROCK:
    case ObjectClass::IMPASSABLE_SANDDUNE:
    case ObjectClass::IMPASSABLE_SANDPIT:
    case ObjectClass::IMPASSABLE_SHRUB:
    case ObjectClass::IMPASSABLE_SKULL:
    case ObjectClass::IMPASSABLE_STALAGMITE:
    case ObjectClass::IMPASSABLE_STUMP:
    case ObjectClass::IMPASSABLE_TARPIT:
    case ObjectClass::IMPASSABLE_TREES:
    case ObjectClass::IMPASSABLE_VINE:
    case ObjectClass::IMPASSABLE_VOLCANICVENT:
    case ObjectClass::IMPASSABLE_VOLCANO:
    case ObjectClass::IMPASSABLE_WILLOWTREES:
    case ObjectClass::IMPASSABLE_YUCCATREES:
    case ObjectClass::IMPASSABLE_REEF:
    // GENERIC_IMPASSABLE_TERRAIN_ABSOD
    case ObjectClass::IMPASSABLE_BRUSH2:
    case ObjectClass::IMPASSABLE_BUSH2:
    case ObjectClass::IMPASSABLE_CACTUS2:
    case ObjectClass::IMPASSABLE_CANYON2:
    case ObjectClass::IMPASSABLE_CRATER2:
    case ObjectClass::IMPASSABLE_DEADVEGETATION2:
    case ObjectClass::IMPASSABLE_FLOWERS2:
    case ObjectClass::IMPASSABLE_FROZENLIKE2:
    case ObjectClass::IMPASSABLE_HEDGE2:
    case ObjectClass::IMPASSABLE_HILL2:
    case ObjectClass::IMPASSABLE_LAKE2:
    case ObjectClass::IMPASSABLE_LAVAFLOW2:
    case ObjectClass::IMPASSABLE_LAVALAKE2:
    case ObjectClass::IMPASSABLE_MUSHROOMS2:
    case ObjectClass::IMPASSABLE_LOG2:
    case ObjectClass::IMPASSABLE_MANDRAKE2:
    case ObjectClass::IMPASSABLE_MOSS2:
    case ObjectClass::IMPASSABLE_MOUND2:
    case ObjectClass::IMPASSABLE_MOUNTAIN2:
    case ObjectClass::IMPASSABLE_OAKTREES2:
    case ObjectClass::IMPASSABLE_OUTCROPPING2:
    case ObjectClass::IMPASSABLE_PINETREES2:
    case ObjectClass::IMPASSABLE_PLANT2:
    case ObjectClass::IMPASSABLE_RIVERDELTA2:
    case ObjectClass::IMPASSABLE_ROCK2:
    case ObjectClass::IMPASSABLE_SANDDUNE2:
    case ObjectClass::IMPASSABLE_SANDPIT2:
    case ObjectClass::IMPASSABLE_SHRUB2:
    case ObjectClass::IMPASSABLE_SKULL2:
    case ObjectClass::IMPASSABLE_STALAGMITE2:
    case ObjectClass::IMPASSABLE_STUMP2:
    case ObjectClass::IMPASSABLE_TARPIT2:
    case ObjectClass::IMPASSABLE_TREES2:
    case ObjectClass::IMPASSABLE_VINE2:
    case ObjectClass::IMPASSABLE_VOLCANICVENT2:
    case ObjectClass::IMPASSABLE_VOLCANO2:
    case ObjectClass::IMPASSABLE_WILLOWTREES2:
    case ObjectClass::IMPASSABLE_YUCCATREES2:
    case ObjectClass::IMPASSABLE_REEF2:
    case ObjectClass::IMPASSABLE_DESERTHILLS:
    case ObjectClass::IMPASSABLE_DIRTHILLS:
    case ObjectClass::IMPASSABLE_GRASSHILLS:
    case ObjectClass::IMPASSABLE_ROUGHHILLS:
    case ObjectClass::IMPASSABLE_SUBTERRANEANROCKS:
    case ObjectClass::IMPASSABLE_SWAMPFOLIAGE:
    // GENERIC_VISITABLE
    case ObjectClass::ALTAR_OF_SACRIFICE:
    case ObjectClass::ANCHOR_POINT:
    case ObjectClass::ARENA:
    case ObjectClass::BLACK_MARKET:
    case ObjectClass::CARTOGRAPHER:
    case ObjectClass::BUOY:
    case ObjectClass::SWAN_POND:
    case ObjectClass::COVER_OF_DARKNESS:
    case ObjectClass::CREATURE_BANK:
    case ObjectClass::CORPSE:
    case ObjectClass::MARLETTO_TOWER:
    case ObjectClass::DERELICT_SHIP:
    case ObjectClass::DRAGON_UTOPIA:
    case ObjectClass::EYE_OF_MAGI:
    case ObjectClass::FAERIE_RING:
    case ObjectClass::FOUNTAIN_OF_FORTUNE:
    case ObjectClass::FOUNTAIN_OF_YOUTH:
    case ObjectClass::GARDEN_OF_REVELATION:
    case ObjectClass::HILL_FORT:
    case ObjectClass::HUT_OF_MAGI:
    case ObjectClass::IDOL_OF_FORTUNE:
    case ObjectClass::LEAN_TO:
    case ObjectClass::LIBRARY_OF_ENLIGHTENMENT:
    case ObjectClass::SCHOOL_OF_MAGIC:
    case ObjectClass::MAGIC_SPRING:
    case ObjectClass::MAGIC_WELL:
    case ObjectClass::MERCENARY_CAMP:
    case ObjectClass::MERMAID:
    case ObjectClass::MYSTICAL_GARDEN:
    case ObjectClass::OASIS:
    case ObjectClass::OBELISK:
    case ObjectClass::REDWOOD_OBSERVATORY:
    case ObjectClass::PILLAR_OF_FIRE:
    case ObjectClass::STAR_AXIS:
    case ObjectClass::RALLY_FLAG:
    case ObjectClass::BORDERGUARD:
    case ObjectClass::KEYMASTER:
    case ObjectClass::REFUGEE_CAMP:
    case ObjectClass::SANCTUARY:
    case ObjectClass::CRYPT:
    case ObjectClass::SHIPWRECK:
    case ObjectClass::SIRENS:
    case ObjectClass::STABLES:
    case ObjectClass::TAVERN:
    case ObjectClass::TEMPLE:
    case ObjectClass::DEN_OF_THIEVES:
    case ObjectClass::TRADING_POST:
    case ObjectClass::LEARNING_STONE:
    case ObjectClass::TREE_OF_KNOWLEDGE:
    case ObjectClass::UNIVERSITY:
    case ObjectClass::WAGON:
    case ObjectClass::WAR_MACHINE_FACTORY:
    case ObjectClass::SCHOOL_OF_WAR:
    case ObjectClass::WARRIORS_TOMB:
    case ObjectClass::WATER_WHEEL:
    case ObjectClass::WATERING_HOLE:
    case ObjectClass::WHIRLPOOL:
    case ObjectClass::WINDMILL:
    case ObjectClass::MARKET_OF_TIME:
    case ObjectClass::DECORATIVE_TOWN:
    // GENERIC_VISITABLE_ABSOD
    case ObjectClass::TRADING_POST_SNOW:
    case ObjectClass::PYRAMID:
    case ObjectClass::BORDER_GATE:
    case ObjectClass::FREELANCERS_GUILD:
    // GENERIC_BOAT
    case ObjectClass::BOAT:
    // GENERIC_PASSABLE_TERRAIN_SOD
    case ObjectClass::CLOVER_FIELD:
    case ObjectClass::EVIL_FOG:
    case ObjectClass::FAVORABLE_WINDS:
    case ObjectClass::FIERY_FIELDS:
    case ObjectClass::HOLY_GROUNDS:
    case ObjectClass::LUCID_POOLS:
    case ObjectClass::MAGIC_CLOUDS:
    case ObjectClass::ROCKLANDS:
    case ObjectClass::CURSED_GROUND2:
    case ObjectClass::MAGIC_PLAINS2:
    case ObjectClass::PASSABLE_139:
    case ObjectClass::PASSABLE_140:
    case ObjectClass::PASSABLE_141:
    case ObjectClass::PASSABLE_142:
    case ObjectClass::PASSABLE_144:
    case ObjectClass::PASSABLE_145:
    case ObjectClass::PASSABLE_146:
    // GENERIC_PASSABLE_TERRAIN
    case ObjectClass::PASSABLE_HOLE:
    case ObjectClass::CURSED_GROUND1:
    case ObjectClass::MAGIC_PLAINS1:
    case ObjectClass::PASSABLE_KELP:
    case ObjectClass::PASSABLE_KELP2:
    case ObjectClass::PASSABLE_HOLE2:
    // GENERIC_VISITABLE_ABSOD
    case ObjectClass::MONOLITH_TWO_WAY:
    case ObjectClass::MONOLITH_ONE_WAY_ENTRANCE:
    case ObjectClass::MONOLITH_ONE_WAY_EXIT:
    // GENERIC_TREASURE
    case ObjectClass::CAMPFIRE:
    case ObjectClass::FLOTSAM:
    case ObjectClass::SEA_CHEST:
    case ObjectClass::SHIPWRECK_SURVIVOR:
    case ObjectClass::TREASURE_CHEST:
    // SUBTERRANEAN_GATE
    case ObjectClass::SUBTERRANEAN_GATE:
      return MetaObjectType::GENERIC_NO_PROPERTIES;

    case ObjectClass::GRAIL:
      return MetaObjectType::GRAIL;
    case ObjectClass::HERO:
    case ObjectClass::PRISON:
    case ObjectClass::RANDOM_HERO:
      return MetaObjectType::HERO;
    case ObjectClass::MONSTER:
    case ObjectClass::RANDOM_MONSTER:
    case ObjectClass::RANDOM_MONSTER_L1:
    case ObjectClass::RANDOM_MONSTER_L2:
    case ObjectClass::RANDOM_MONSTER_L3:
    case ObjectClass::RANDOM_MONSTER_L4:
    case ObjectClass::RANDOM_MONSTER_L5:
    case ObjectClass::RANDOM_MONSTER_L6:
    case ObjectClass::RANDOM_MONSTER_L7:
      return MetaObjectType::MONSTER;
    case ObjectClass::PANDORAS_BOX:
      return MetaObjectType::PANDORAS_BOX;
    case ObjectClass::HERO_PLACEHOLDER:
      return MetaObjectType::PLACEHOLDER_HERO;
    case ObjectClass::RANDOM_DWELLING:
      return MetaObjectType::RANDOM_DWELLING;
    case ObjectClass::RANDOM_DWELLING_LVL:
      return MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL;
    case ObjectClass::RANDOM_DWELLING_FACTION:
      return MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT;
    case ObjectClass::QUEST_GUARD:
      return MetaObjectType::QUEST_GUARD;
    case ObjectClass::RESOURCE:
    case ObjectClass::RANDOM_RESOURCE:
      return MetaObjectType::RESOURCE;
    case ObjectClass::SCHOLAR:
      return MetaObjectType::SCHOLAR;
    case ObjectClass::SEER_HUT:
      return MetaObjectType::SEERS_HUT;
    case ObjectClass::SHRINE_OF_MAGIC_INCANTATION:
    case ObjectClass::SHRINE_OF_MAGIC_GESTURE:
    case ObjectClass::SHRINE_OF_MAGIC_THOUGHT:
      return MetaObjectType::SHRINE;
    case ObjectClass::OCEAN_BOTTLE:
    case ObjectClass::SIGN:
      return MetaObjectType::SIGN;
    case ObjectClass::SPELL_SCROLL:
      return MetaObjectType::SPELL_SCROLL;
    case ObjectClass::RANDOM_TOWN:
    case ObjectClass::TOWN:
      return MetaObjectType::TOWN;
    case ObjectClass::CREATURE_GENERATOR1:
    case ObjectClass::CREATURE_GENERATOR2:
    case ObjectClass::CREATURE_GENERATOR3:
    case ObjectClass::CREATURE_GENERATOR4:
    case ObjectClass::LIGHTHOUSE:
    case ObjectClass::SHIPYARD:
      return MetaObjectType::TRIVIAL_OWNED_OBJECT;
    case ObjectClass::WITCH_HUT:
      return MetaObjectType::WITCH_HUT;

    default:
      throw std::runtime_error("Invalid object_class.");
    }
  }

  // Check at compile time that all known ObjectClasses are mapped to some MetaObjectType.
  static_assert(
    [] {
      for (std::uint32_t i = 0; i < kNumObjectClasses; ++i)
      {
        (void)getMetaObjectType(static_cast<ObjectClass>(i), 0);
      }
      return true;
    }(), "getMetaObjectType() is not implemented for 1 or more ObjectClass constants.");
}
