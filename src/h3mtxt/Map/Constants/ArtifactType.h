#pragma once

#include <cstdint>

namespace h3m
{
  // ArtifactType used to be written as uint8 in RoE. In SoD this was changed to uint16
  // almost everywhere; however, there is at least one case where it's still written
  // as uint8 - "Transport Artifact" victory condition.
  // Regardless, this shouldn't be an issue, since there are fewer than 256 artifacts.
  enum class ArtifactType : std::uint16_t
  {
    Spellbook                   = 0,    // 0x00
    SpellScroll                 = 1,    // 0x01
    Grail                       = 2,    // 0x02
    Catapult                    = 3,    // 0x03
    Ballista                    = 4,    // 0x04
    AmmoCart                    = 5,    // 0x05
    FirstAidTent                = 6,    // 0x06
    CentaurAxe                  = 7,    // 0x07
    BlackshardOfTheDeadKnight   = 8,    // 0x08
    GreaterGnollsFlail          = 9,    // 0x09
    OgresClubOfHavoc            = 10,   // 0x0A
    SwordOfHellfire             = 11,   // 0x0B
    TitansGladius               = 12,   // 0x0C
    ShieldOfTheDwarvenLords     = 13,   // 0x0D
    ShieldOfTheYawningDead      = 14,   // 0x0E
    BucklerOfTheGnollKing       = 15,   // 0x0F
    TargOfTheRampagingOgre      = 16,   // 0x10
    ShieldOfTheDamned           = 17,   // 0x11
    SentinelsShield             = 18,   // 0x12
    HelmOfTheAlabasterUnicorn   = 19,   // 0x13
    SkullHelmet                 = 20,   // 0x14
    HelmOfChaos                 = 21,   // 0x15
    CrownOfTheSupremeMagi       = 22,   // 0x16
    HellstormHelmet             = 23,   // 0x17
    ThunderHelmet               = 24,   // 0x18
    BreastplateOfPetrifiedWood  = 25,   // 0x19
    RibCage                     = 26,   // 0x1A
    ScalesOfTheGreaterBasilisk  = 27,   // 0x1B
    TunicOfTheCyclopsKing       = 28,   // 0x1C
    BreastplateOfBrimstone      = 29,   // 0x1D
    TitansCuirass               = 30,   // 0x1E
    ArmorOfWonder               = 31,   // 0x1F
    SandalsOfTheSaint           = 32,   // 0x20
    CelestialNecklaceOfBliss    = 33,   // 0x21
    LionsShieldOfCourage        = 34,   // 0x22
    SwordOfJudgement            = 35,   // 0x23
    HelmOfHeavenlyEnlightenment = 36,   // 0x24
    QuietEyeOfTheDragon         = 37,   // 0x25
    RedDragonFlameTongue        = 38,   // 0x26
    DragonScaleShield           = 39,   // 0x27
    DragonScaleArmor            = 40,   // 0x28
    DragonboneGreaves           = 41,   // 0x29
    DragonWingTabard            = 42,   // 0x2A
    NecklaceOfDragonteeth       = 43,   // 0x2B
    CrownOfDragontooth          = 44,   // 0x2C
    StillEyeOfTheDragon         = 45,   // 0x2D
    CloverOfFortune             = 46,   // 0x2E
    CardsOfProphecy             = 47,   // 0x2F
    LadybirdOfLuck              = 48,   // 0x30
    BadgeOfCourage              = 49,   // 0x31
    CrestOfValor                = 50,   // 0x32
    GlyphOfGallantry            = 51,   // 0x33
    Speculum                    = 52,   // 0x34
    Spyglass                    = 53,   // 0x35
    AmuletOfTheUndertaker       = 54,   // 0x36
    VampiresCowl                = 55,   // 0x37
    DeadMansBoots               = 56,   // 0x38
    GarnitureOfInterference     = 57,   // 0x39
    SurcoatOfCounterpoise       = 58,   // 0x3A
    BootsOfPolarity             = 59,   // 0x3B
    BowOfElvenCherrywood        = 60,   // 0x3C
    BowstringOfTheUnicornsMane  = 61,   // 0x3D
    AngelFeatherArrows          = 62,   // 0x3E
    BirdOfPerception            = 63,   // 0x3F
    StoicWatchman               = 64,   // 0x40
    EmblemOfCognizance          = 65,   // 0x41
    StatesmansMedal             = 66,   // 0x42
    DiplomatsRing               = 67,   // 0x43
    AmbassadorsSash             = 68,   // 0x44
    RingOfTheWayfarer           = 69,   // 0x45
    EquestriansGloves           = 70,   // 0x46
    NecklaceOfOceanGuidance     = 71,   // 0x47
    AngelWings                  = 72,   // 0x48
    CharmOfMana                 = 73,   // 0x49
    TalismanOfMana              = 74,   // 0x4A
    MysticOrbOfMana             = 75,   // 0x4B
    CollarOfConjuring           = 76,   // 0x4C
    RingOfConjuring             = 77,   // 0x4D
    CapeOfConjuring             = 78,   // 0x4E
    OrbOfTheFirmament           = 79,   // 0x4F
    OrbOfSilt                   = 80,   // 0x50
    OrbOfTempestuousFire        = 81,   // 0x51
    OrbOfDrivingRain            = 82,   // 0x52
    RecantersCloak              = 83,   // 0x53
    SpiritOfOppression          = 84,   // 0x54
    HourglassOfTheEvilHour      = 85,   // 0x55
    TomeOfFireMagic             = 86,   // 0x56
    TomeOfAirMagic              = 87,   // 0x57
    TomeOfWaterMagic            = 88,   // 0x58
    TomeOfEarthMagic            = 89,   // 0x59
    BootsOfLevitation           = 90,   // 0x5A
    GoldenBow                   = 91,   // 0x5B
    SphereOfPermanence          = 92,   // 0x5C
    OrbOfVulnerability          = 93,   // 0x5D
    RingOfVitality              = 94,   // 0x5E
    RingOfLife                  = 95,   // 0x5F
    VialOfLifeblood             = 96,   // 0x60
    NecklaceOfSwiftness         = 97,   // 0x61
    BootsOfSpeed                = 98,   // 0x62
    CapeOfVelocity              = 99,   // 0x63
    PendantOfDispassion         = 100,  // 0x64
    PendantOfSecondSight        = 101,  // 0x65
    PendantOfHoliness           = 102,  // 0x66
    PendantOfLife               = 103,  // 0x67
    PendantOfDeath              = 104,  // 0x68
    PendantOfFreeWill           = 105,  // 0x69
    PendantOfNegativity         = 106,  // 0x6A
    PendantOfTotalRecall        = 107,  // 0x6B
    PendantOfCourage            = 108,  // 0x6C
    EverflowingCrystalCloak     = 109,  // 0x6D
    RingOfInfiniteGems          = 110,  // 0x6E
    EverpouringVialOfMercury    = 111,  // 0x6F
    InexhaustibleCartOfOre      = 112,  // 0x70
    EversmokingRingOfSulfur     = 113,  // 0x71
    InexhaustibleCartOfLumber   = 114,  // 0x72
    EndlessSackOfGold           = 115,  // 0x73
    EndlessBagOfGold            = 116,  // 0x74
    EndlessPurseOfGold          = 117,  // 0x75
    LegsOfLegion                = 118,  // 0x76
    LoinsOfLegion               = 119,  // 0x77
    TorsoOfLegion               = 120,  // 0x78
    ArmsOfLegion                = 121,  // 0x79
    HeadOfLegion                = 122,  // 0x7A
    SeaCaptainsHat              = 123,  // 0x7B
    SpellbindersHat             = 124,  // 0x7C
    ShacklesOfWar               = 125,  // 0x7D
    OrbOfInhibition             = 126,  // 0x7E
    VialOfDragonBlood           = 127,  // 0x7F
    ArmageddonsBlade            = 128,  // 0x80
    AngelicAlliance             = 129,  // 0x81
    CloakOfTheUndeadKing        = 130,  // 0x82
    ElixirOfLife                = 131,  // 0x83
    ArmorOfTheDamned            = 132,  // 0x84
    StatueOfLegion              = 133,  // 0x85
    PowerOfTheDragonFather      = 134,  // 0x86
    TitansThunder               = 135,  // 0x87
    AdmiralsHat                 = 136,  // 0x88
    BowOfTheSharpshooter        = 137,  // 0x89
    WizardsWell                 = 138,  // 0x8A
    RingOfTheMagi               = 139,  // 0x8B
    Cornucopia                  = 140,  // 0x8C
    // Unused content.
    // These artifacts are recognized by the game but don't actually do anything.
    // They also don't have decent sprites.
    DiplomatsSuit               = 141,  // 0x8D
    MiredInNeutrality           = 142,  // 0x8E
    IronfistOfTheOgre           = 143,  // 0x8F
    // Magic number indicating "None" (the absence of an artifact in the slot).
    None                        = 65535 // 0xFFFF
  };
}
