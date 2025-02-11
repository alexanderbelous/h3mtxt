#pragma once

#include <cstdint>

namespace h3m
{

enum class HeroType : std::uint8_t
{
    /* Knight (Castle) */
    ORRIN,          /* 0x00 */
    VALESKA,        /* 0x01 */
    EDRIC,          /* 0x02 */
    SYLVIA,         /* 0x03 */
    LORD_HAART,     /* 0x04 */
    SORSHA,         /* 0x05 */
    CHRISTIAN,      /* 0x06 */
    TYRIS,          /* 0x07 */

    /* Cleric (Castle) */
    RION,           /* 0x08 */
    ADELA,          /* 0x09 */
    CUTHBERT,       /* 0x0A */
    ADELAIDE,       /* 0x0B */
    INGHAM,         /* 0x0C */
    SANYA,          /* 0x0D */
    LOYNIS,         /* 0x0E */
    CAITLIN,        /* 0x0F */

    /* Ranger (Rampart) */
    MEPHALA,        /* 0x10 */
    UFRETIN,        /* 0x11 */
    JENOVA,         /* 0x12 */
    RYLAND,         /* 0x13 */
    THORGRIM,       /* 0x14 */
    IVOR,           /* 0x15 */
    CLANCY,         /* 0x16 */
    KYRRE,          /* 0x17 */

    /* Druid (Rampart) */
    CORONIUS,       /* 0x18 */
    ULAND,          /* 0x19 */
    ELLESHAR,       /* 0x1A */
    GEM,            /* 0x1B */
    MALCOM,         /* 0x1C */
    MELODIA,        /* 0x1D */
    ALAGAR,         /* 0x1E */
    AERIS,          /* 0x1F */
    
    /* Alchemist (Tower) */
    PIQUEDRAM,      /* 0x20 */
    THANE,          /* 0x21 */
    JOSEPHINE,      /* 0x22 */
    NEELA,          /* 0x23 */
    TOROSAR ,       /* 0x24 */
    FAFNER,         /* 0x25 */
    RISSA,          /* 0x26 */
    IONA,           /* 0x27 */
    
    /* Wizard (Tower) */
    ASTRAL,         /* 0x28 */
    HALON,          /* 0x29 */
    SERENA,         /* 0x2A */
    DAREMYTH,       /* 0x2B */
    THEODORUS,      /* 0x2C */
    SOLMYR,         /* 0x2D */
    CYRA,           /* 0x2E */
    AINE,           /* 0x2F */
    
    /* Demoniac (Inferno) */
    FIONA,          /* 0x30 */
    RASHKA,         /* 0x31 */
    MARIUS,         /* 0x32 */
    IGNATIUS,       /* 0x33 */
    OCTAVIA,        /* 0x34 */
    CALH,           /* 0x35 */
    PYRE,           /* 0x36 */
    NYMUS,          /* 0x37 */
    
    /* Heretic (Inferno) */
    AYDEN,          /* 0x38 */
    XYRON,          /* 0x39 */
    AXSIS,          /* 0x3A */
    OLEMA,          /* 0x3B */
    CALID,          /* 0x3C */
    ASH,            /* 0x3D */
    ZYDAR,          /* 0x3E */
    XARFAX,         /* 0x3F */
    
    /* Death Knight (Necropolis) */
    STRAKER,        /* 0x40 */
    VOKIAL,         /* 0x41 */
    MOANDOR,        /* 0x42 */
    CHARNA,         /* 0x43 */
    TAMIKA,         /* 0x44 */
    ISRA,           /* 0x45 */
    CLAVIUS,        /* 0x46 */
    GALTHRAN,       /* 0x47 */
    
    /* Necromancer (Necropolis) */
    SEPTIENNA,      /* 0x48 */
    AISLINN,        /* 0x49 */
    SANDRO,         /* 0x4A */
    NIMBUS,         /* 0x4B */
    THANT,          /* 0x4C */
    XSI,            /* 0x4D */
    VIDOMINA,       /* 0x4E */
    NAGASH,         /* 0x4F */
    
    /* Overlord (Dungeon) */
    LORELEI,        /* 0x50 */
    ARLACH,         /* 0x51 */
    DACE,           /* 0x52 */
    AJIT,           /* 0x53 */
    DAMACON,        /* 0x54 */
    GUNNAR,         /* 0x55 */
    SYNCA,          /* 0x56 */
    SHAKTI,         /* 0x57 */

    /* Warlock (Dungeon) */
    ALAMAR,         /* 0x58 */
    JAEGAR,         /* 0x59 */
    MALEKITH,       /* 0x5A */
    JEDDITE,        /* 0x5B */
    GEON,           /* 0x5C */
    DEEMER,         /* 0x5D */
    SEPHINROTH,     /* 0x5E */
    DARKSTORM,      /* 0x5F */
    

    /* Barbarian (Stronghold) */
    YOG,            /* 0x60 */
    GURNISSON,      /* 0x61 */
    JABARKAS,       /* 0x62 */
    SHIVA,          /* 0x63 */
    GRETCHIN,       /* 0x64 */
    KRELLION,       /* 0x65 */
    CRAG_HACK,      /* 0x66 */
    TYRAXOR,        /* 0x67 */
    
    /* Battle Mage (Stronghold) */
    GIRD,           /* 0x68 */
    VEY,            /* 0x69 */
    DESSA,          /* 0x6A */
    TEREK,          /* 0x6B */
    ZUBIN,          /* 0x6C */
    GUNDULA,        /* 0x6D */
    ORIS,           /* 0x6E */
    SAURUG,         /* 0x6F */
    
    /* Beastmaster (Fortress) */
    BRON,           /* 0x70 */
    DRAKON,         /* 0x71 */
    WYSTAN,         /* 0x72 */
    TAZAR,          /* 0x73 */
    ALKIN,          /* 0x74 */
    KORBAC,         /* 0x75 */
    GERWULF,        /* 0x76 */
    BROGHILD,       /* 0x77 */
    
    /* Witch (Fortress) */
    MIRLANDA,       /* 0x78 */
    ROSIC,          /* 0x79 */
    VOY,            /* 0x7A */
    VERDISH,        /* 0x7B */
    MERIST,         /* 0x7C */
    STYG,           /* 0x7D */
    ANDRA,          /* 0x7E */
    TIVA,           /* 0x7F */
    
    /* Planeswalker (Conflux) */
    PASIS,          /* 0x80 */
    THUNAR,         /* 0x81 */
    IGNISSA,        /* 0x82 */
    LACUS,          /* 0x83 */
    MONERE,         /* 0x84 */
    ERDAMON,        /* 0x85 */
    FIUR,           /* 0x86 */
    KALT,           /* 0x87 */
    
    /* Elementalist (Conflux) */
    LUNA,           /* 0x88 */
    BRISSA,         /* 0x89 */
    CIELE,          /* 0x8A */
    LABETHA,        /* 0x8B */
    INTEUS,         /* 0x8C */
    AENAIN,         /* 0x8D */
    GELARE,         /* 0x8E */
    GRINDAN,        /* 0x8F */

    /* Special  (Campaign) */
    SIR_MULLICH,    /* 0x90 */ // IN CHARGE OF BEING BROKEN
    ADRIENNE,       /* 0x91 */
    CATHERINE,      /* 0x92 */
    DRACON,         /* 0x93 */
    GELU,           /* 0x94 */
    KILGOR,         /* 0x95 */
    LORD_HAART2,    /* 0x96 */ // UNDEAD LORD HAART
    MUTARE,         /* 0x97 */
    ROLAND,         /* 0x98 */
    MUTARE_DRAKE,   /* 0x99 */
    BORAGUS,        /* 0x9A */
    XERON,          /* 0x9B */
};

}
