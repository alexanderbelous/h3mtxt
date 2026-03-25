#pragma once

#include <cstdint>

namespace h3m
{
  // Valid values for a hero's portrait.
  //
  // This is almost identical to HeroType, but there are a few extra portraits
  // whose integer values do not refer to a valid HeroType. In other words, it's
  // always safe to cast HeroType to HeroPortrait, but not the other way around.
  enum class HeroPortrait : std::uint8_t
  {
    // Knight (Castle)
    Orrin         = 0,   // 0x00
    Valeska       = 1,   // 0x01
    Edric         = 2,   // 0x02
    Sylvia        = 3,   // 0x03
    LordHaart     = 4,   // 0x04
    Sorsha        = 5,   // 0x05
    Christian     = 6,   // 0x06
    Tyris         = 7,   // 0x07

    // Cleric (Castle)
    Rion          = 8,   // 0x08
    Adela         = 9,   // 0x09
    Cuthbert      = 10,  // 0x0A
    Adelaide      = 11,  // 0x0B
    Ingham        = 12,  // 0x0C
    Sanya         = 13,  // 0x0D
    Loynis        = 14,  // 0x0E
    Caitlin       = 15,  // 0x0F

    // Ranger (Rampart)
    Mephala       = 16,  // 0x10
    Ufretin       = 17,  // 0x11
    Jenova        = 18,  // 0x12
    Ryland        = 19,  // 0x13
    Thorgrim      = 20,  // 0x14
    Ivor          = 21,  // 0x15
    Clancy        = 22,  // 0x16
    Kyrre         = 23,  // 0x17

    // Druid (Rampart)
    Coronius      = 24,  // 0x18
    Uland         = 25,  // 0x19
    Elleshar      = 26,  // 0x1A
    Gem           = 27,  // 0x1B
    Malcom        = 28,  // 0x1C
    Melodia       = 29,  // 0x1D
    Alagar        = 30,  // 0x1E
    Aeris         = 31,  // 0x1F

    // Alchemist (Tower)
    Piquedram     = 32,  // 0x20
    Thane         = 33,  // 0x21
    Josephine     = 34,  // 0x22
    Neela         = 35,  // 0x23
    Torosar       = 36,  // 0x24
    Fafner        = 37,  // 0x25
    Rissa         = 38,  // 0x26
    Iona          = 39,  // 0x27

    // Wizard (Tower)
    Astral        = 40,  // 0x28
    Halon         = 41,  // 0x29
    Serena        = 42,  // 0x2A
    Daremyth      = 43,  // 0x2B
    Theodorus     = 44,  // 0x2C
    Solmyr        = 45,  // 0x2D
    Cyra          = 46,  // 0x2E
    Aine          = 47,  // 0x2F

    // Demoniac (Inferno)
    Fiona         = 48,  // 0x30
    Rashka        = 49,  // 0x31
    Marius        = 50,  // 0x32
    Ignatius      = 51,  // 0x33
    Octavia       = 52,  // 0x34
    Calh          = 53,  // 0x35
    Pyre          = 54,  // 0x36
    Nymus         = 55,  // 0x37

    // Heretic (Inferno)
    Ayden         = 56,  // 0x38
    Xyron         = 57,  // 0x39
    Axsis         = 58,  // 0x3A
    Olema         = 59,  // 0x3B
    Calid         = 60,  // 0x3C
    Ash           = 61,  // 0x3D
    Zydar         = 62,  // 0x3E
    Xarfax        = 63,  // 0x3F

    // Death Knight (Necropolis)
    Straker       = 64,  // 0x40
    Vokial        = 65,  // 0x41
    Moandor       = 66,  // 0x42
    Charna        = 67,  // 0x43
    Tamika        = 68,  // 0x44
    Isra          = 69,  // 0x45
    Clavius       = 70,  // 0x46
    Galthran      = 71,  // 0x47

    // Necromancer (Necropolis)
    Septienna     = 72,  // 0x48
    Aislinn       = 73,  // 0x49
    Sandro        = 74,  // 0x4A
    Nimbus        = 75,  // 0x4B
    Thant         = 76,  // 0x4C
    Xsi           = 77,  // 0x4D
    Vidomina      = 78,  // 0x4E
    Nagash        = 79,  // 0x4F

    // Overlord (Dungeon)
    Lorelei       = 80,  // 0x50
    Arlach        = 81,  // 0x51
    Dace          = 82,  // 0x52
    Ajit          = 83,  // 0x53
    Damacon       = 84,  // 0x54
    Gunnar        = 85,  // 0x55
    Synca         = 86,  // 0x56
    Shakti        = 87,  // 0x57

    // Warlock (Dungeon)
    Alamar        = 88,  // 0x58
    Jaegar        = 89,  // 0x59
    Malekith      = 90,  // 0x5A
    Jeddite       = 91,  // 0x5B
    Geon          = 92,  // 0x5C
    Deemer        = 93,  // 0x5D
    Sephinroth    = 94,  // 0x5E
    Darkstorm     = 95,  // 0x5F


    // Barbarian (Stronghold)
    Yog           = 96,  // 0x60
    Gurnisson     = 97,  // 0x61
    Jabarkas      = 98,  // 0x62
    Shiva         = 99,  // 0x63
    Gretchin      = 100, // 0x64
    Krellion      = 101, // 0x65
    CragHack      = 102, // 0x66
    Tyraxor       = 103, // 0x67

    // Battle Mage (Stronghold)
    Gird          = 104, // 0x68
    Vey           = 105, // 0x69
    Dessa         = 106, // 0x6A
    Terek         = 107, // 0x6B
    Zubin         = 108, // 0x6C
    Gundula       = 109, // 0x6D
    Oris          = 110, // 0x6E
    Saurug        = 111, // 0x6F

    // Beastmaster (Fortress)
    Bron          = 112, // 0x70
    Drakon        = 113, // 0x71
    Wystan        = 114, // 0x72
    Tazar         = 115, // 0x73
    Alkin         = 116, // 0x74
    Korbac        = 117, // 0x75
    Gerwulf       = 118, // 0x76
    Broghild      = 119, // 0x77

    // Witch (Fortress)
    Mirlanda      = 120, // 0x78
    Rosic         = 121, // 0x79
    Voy           = 122, // 0x7A
    Verdish       = 123, // 0x7B
    Merist        = 124, // 0x7C
    Styg          = 125, // 0x7D
    Andra         = 126, // 0x7E
    Tiva          = 127, // 0x7F

    // Planeswalker (Conflux)
    Pasis         = 128, // 0x80
    Thunar        = 129, // 0x81
    Ignissa       = 130, // 0x82
    Lacus         = 131, // 0x83
    Monere        = 132, // 0x84
    Erdamon       = 133, // 0x85
    Fiur          = 134, // 0x86
    Kalt          = 135, // 0x87

    // Elementalist (Conflux)
    Luna          = 136, // 0x88
    Brissa        = 137, // 0x89
    Ciele         = 138, // 0x8A
    Labetha       = 139, // 0x8B
    Inteus        = 140, // 0x8C
    Aenain        = 141, // 0x8D
    Gelare        = 142, // 0x8E
    Grindan       = 143, // 0x8F

    // Special  (Campaign)
    SirMullich    = 144, // 0x90
    Adrienne      = 145, // 0x91
    Catherine     = 146, // 0x92
    Dracon        = 147, // 0x93
    Gelu          = 148, // 0x94
    Kilgor        = 149, // 0x95
    LordHaart2    = 150, // 0x96  - Undead Lord Haart
    Mutare        = 151, // 0x97
    Roland        = 152, // 0x98
    MutareDrake   = 153, // 0x99
    Boragus       = 154, // 0x9A
    Xeron         = 155, // 0x9B

    // Custom (not default for any hero)
    GeneralKendal = 156, // 0x9C
    Christian2    = 157, // 0x9D - As he appears in the "Foolhardy Waywardness" campaign.
    Ordwald       = 158, // 0x9E
    Finneas       = 159, // 0x9F
    Gem2          = 160, // 0xA0 - As she appears in the "Shadow of Death" campaigns.
    Sandro2       = 161, // 0xA1 - As he appears in the campaigns before he turned into a lich.
    Yog2          = 162, // 0xA2 - As he appears in the "Birth of a Barbarian" campaign.

    // Special value for the default portrait
    Default       = 255  // 0xFF
  };
}
