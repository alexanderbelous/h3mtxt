#pragma once

#include <cstdint>

namespace h3m
{
  // Spells are generally stored as 8-bit unsigned integers in H3M, although there
  // are a couple places where 32-bit unsigned integers are used instead.
  enum class SpellType : std::uint8_t
  {
    SUMMON_BOAT,       /* 0x00 */
    SCUTTLE_BOAT,       /* 0x01 */
    VISIONS,       /* 0x02 */
    VIEW_EARTH,       /* 0x03 */
    DISGUISE,       /* 0x04 */
    VIEW_AIR,       /* 0x05 */
    FLY,       /* 0x06 */
    WATER_WALK,       /* 0x07 */
    DIMENSION_DOOR,       /* 0x08 */
    TOWN_PORTAL,       /* 0x09 */
    QUICK_SAND,       /* 0x0A */
    LAND_MINE,       /* 0x0B */
    FORCE_FIELD,       /* 0x0C */
    FIRE_WALL,       /* 0x0D */
    EARTHQUAKE,       /* 0x0E */
    MAGIC_ARROW,       /* 0x0F */
    ICE_BOLT,       /* 0x10 */
    LIGHTNING_BOLT,       /* 0x11 */
    IMPLOSION,       /* 0x12 */
    CHAIN_LIGHTNING,       /* 0x13 */
    FROST_RING,       /* 0x14 */
    FIREBALL,       /* 0x15 */
    INFERNO,       /* 0x16 */
    METEOR_SHOWER,       /* 0x17 */
    DEATH_RIPPLE,       /* 0x18 */
    DESTROY_UNDEAD,       /* 0x19 */
    ARMAGEDDON,       /* 0x1A */
    SHIELD,       /* 0x1B */
    AIR_SHIELD,       /* 0x1C */
    FIRE_SHIELD,       /* 0x1D */
    PROTECTION_FROM_AIR,       /* 0x1E */
    PROTECTION_FROM_FIRE,       /* 0x1F */
    PROTECTION_FROM_WATER,       /* 0x20 */
    PROTECTION_FROM_EARTH,       /* 0x21 */
    ANTI_MAGIC,       /* 0x22 */
    DISPEL,       /* 0x23 */
    MAGIC_MIRROR,       /* 0x24 */
    CURE,       /* 0x25 */
    RESURRECTION,       /* 0x26 */
    ANIMATE_DEAD,       /* 0x27 */
    SACRIFICE,       /* 0x28 */
    BLESS,       /* 0x29 */
    CURSE,       /* 0x2A */
    BLOODLUST,       /* 0x2B */
    PRECISION,       /* 0x2C */
    WEAKNESS,       /* 0x2D */
    STONE_SKIN,       /* 0x2E */
    DISRUPTING_RAY,       /* 0x2F */
    PRAYER,       /* 0x30 */
    MIRTH,       /* 0x31 */
    SORROW,       /* 0x32 */
    FORTUNE,       /* 0x33 */
    MISFORTUNE,       /* 0x34 */
    HASTE,       /* 0x35 */
    SLOW,       /* 0x36 */
    SLAYER,       /* 0x37 */
    FRENZY,       /* 0x38 */
    TITANS_LIGHTNING_BOLT,       /* 0x39 */
    COUNTERSTRIKE,       /* 0x3A */
    BERSERK,       /* 0x3B */
    HYPNOTIZE,       /* 0x3C */
    FORGETFULNESS,       /* 0x3D */
    BLIND,       /* 0x3E */
    TELEPORT,       /* 0x3F */
    REMOVE_OBSTACLE,       /* 0x40 */
    CLONE,       /* 0x41 */
    FIRE_ELEMENTAL,       /* 0x42 */
    EARTH_ELEMENTAL,       /* 0x43 */
    WATER_ELEMENTAL,       /* 0x44 */
    AIR_ELEMENTAL,       /* 0x45 */

    // Some creatures have special abilities which are treated during combat as spells
    // (e.g., Binding by Dendroids or Aging by Ghost Dragons). However, they can never appear
    // in H3M format itself (e.g., you cannot set such spells in a Spell Scroll), so I'm not
    // defining these constants.
    //
    // STONE,             /* 0x46 */
    // POISON,            /* 0x47 */
    // BIND,              /* 0x48 */
    // DISEASE,           /* 0x49 */
    // PARALYZE,          /* 0x4A */
    // AGING,             /* 0x4B */
    // DEATH_CLOUD,       /* 0x4C */
    // THUNDERBOLT,       /* 0x4D */
    // DRAGONFLY_DISPEL,  /* 0x4E */
    // DEATH_STARE,       /* 0x4F */
    // ACID_BREATH        /* 0x50 */
  };
}
