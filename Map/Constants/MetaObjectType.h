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
    DWELLING,
    DWELLING_ABSOD,
    EVENT,
    GARRISON,
    GENERIC_NO_PROPERTIES,  // Any object for which ObjectDetails doesn't store any additional info.
    GRAIL,
    HERO,
    LIGHTHOUSE,
    MONSTER,
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
    TOWN,
    WITCH_HUT
  };

  inline constexpr std::uint32_t kNumMetaObjectTypes = 30;

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
    case ObjectClass::TREASURE_CHEST:
    // SUBTERRANEAN_GATE
    case ObjectClass::SUBTERRANEAN_GATE:
      return MetaObjectType::GENERIC_NO_PROPERTIES;

    case ObjectClass::GRAIL:
      return MetaObjectType::GRAIL;
    case ObjectClass::HERO:
      return MetaObjectType::HERO;
    case ObjectClass::LIGHTHOUSE:
      return MetaObjectType::LIGHTHOUSE;
    case ObjectClass::PANDORAS_BOX:
      return MetaObjectType::PANDORAS_BOX;
    case ObjectClass::HERO_PLACEHOLDER:
      return MetaObjectType::PLACEHOLDER_HERO;
    case ObjectClass::SCHOLAR:
      return MetaObjectType::SCHOLAR;
    case ObjectClass::SHRINE_OF_MAGIC_INCANTATION:
    case ObjectClass::SHRINE_OF_MAGIC_GESTURE:
    case ObjectClass::SHRINE_OF_MAGIC_THOUGHT:
      return MetaObjectType::SHRINE;
    default:
      // TODO: implement the rest.
      throw std::runtime_error("Invalid object_class.");
    }
  }

  // TODO: check via static_assert that all known ObjectClasses are mapped to some MetaObjectType.
}
