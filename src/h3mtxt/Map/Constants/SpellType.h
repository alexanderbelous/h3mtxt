#pragma once

#include <cstdint>

namespace h3m
{
  enum class SpellType : std::uint8_t
  {
    SummonBoat          = 0,   // 0x00
    ScuttleBoat         = 1,   // 0x01
    Visions             = 2,   // 0x02
    ViewEarth           = 3,   // 0x03
    Disguise            = 4,   // 0x04
    ViewAir             = 5,   // 0x05
    Fly                 = 6,   // 0x06
    WaterWalk           = 7,   // 0x07
    DimensionDoor       = 8,   // 0x08
    TownPortal          = 9,   // 0x09
    QuickSand           = 10,  // 0x0A
    LandMine            = 11,  // 0x0B
    ForceField          = 12,  // 0x0C
    FireWall            = 13,  // 0x0D
    Earthquake          = 14,  // 0x0E
    MagicArrow          = 15,  // 0x0F
    IceBolt             = 16,  // 0x10
    LightningBolt       = 17,  // 0x11
    Implosion           = 18,  // 0x12
    ChainLightning      = 19,  // 0x13
    FrostRing           = 20,  // 0x14
    Fireball            = 21,  // 0x15
    Inferno             = 22,  // 0x16
    MeteorShower        = 23,  // 0x17
    DeathRipple         = 24,  // 0x18
    DestroyUndead       = 25,  // 0x19
    Armageddon          = 26,  // 0x1A
    Shield              = 27,  // 0x1B
    AirShield           = 28,  // 0x1C
    FireShield          = 29,  // 0x1D
    ProtectionFromAir   = 30,  // 0x1E
    ProtectionFromFire  = 31,  // 0x1F
    ProtectionFromWater = 32,  // 0x20
    ProtectionFromEarth = 33,  // 0x21
    AntiMagic           = 34,  // 0x22
    Dispel              = 35,  // 0x23
    MagicMirror         = 36,  // 0x24
    Cure                = 37,  // 0x25
    Resurrection        = 38,  // 0x26
    AnimateDead         = 39,  // 0x27
    Sacrifice           = 40,  // 0x28
    Bless               = 41,  // 0x29
    Curse               = 42,  // 0x2A
    Bloodlust           = 43,  // 0x2B
    Precision           = 44,  // 0x2C
    Weakness            = 45,  // 0x2D
    StoneSkin           = 46,  // 0x2E
    DisruptingRay       = 47,  // 0x2F
    Prayer              = 48,  // 0x30
    Mirth               = 49,  // 0x31
    Sorrow              = 50,  // 0x32
    Fortune             = 51,  // 0x33
    Misfortune          = 52,  // 0x34
    Haste               = 53,  // 0x35
    Slow                = 54,  // 0x36
    Slayer              = 55,  // 0x37
    Frenzy              = 56,  // 0x38
    TitansLightningBolt = 57,  // 0x39
    Counterstrike       = 58,  // 0x3A
    Berserk             = 59,  // 0x3B
    Hypnotize           = 60,  // 0x3C
    Forgetfulness       = 61,  // 0x3D
    Blind               = 62,  // 0x3E
    Teleport            = 63,  // 0x3F
    RemoveObstacle      = 64,  // 0x40
    Clone               = 65,  // 0x41
    FireElemental       = 66,  // 0x42
    EarthElemental      = 67,  // 0x43
    WaterElemental      = 68,  // 0x44
    AirElemental        = 69,  // 0x45

    // Some creatures have special abilities which are treated during combat as spells
    // (e.g., Binding by Dendroids or Aging by Ghost Dragons). However, they can never appear
    // in H3M format itself (e.g., you cannot set such spells in a Spell Scroll), so I'm not
    // defining these constants.
    //
    // Stone               = 70,  // 0x46
    // Poison              = 71,  // 0x47
    // Bind                = 72,  // 0x48
    // Disease             = 73,  // 0x49
    // Paralyze            = 74,  // 0x4A
    // Aging               = 75,  // 0x4B
    // DeathCloud          = 76,  // 0x4C
    // Thunderbolt         = 77,  // 0x4D
    // DragonflyDispel     = 78,  // 0x4E
    // DeathStare          = 79,  // 0x4F
    // AcidBreath          = 80   // 0x50
  };
}
