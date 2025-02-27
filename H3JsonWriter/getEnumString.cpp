#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/Formation.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>

#include <iterator>
#include <type_traits>

namespace h3m
{
  std::string_view getEnumString(ArtifactType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Spellbook",
      "SpellScroll",
      "Grail",
      "Catapult",
      "Ballista",
      "AmmoCart",
      "FirstAidTent",
      "CentaurAxe",
      "BlackshardOfTheDeadKnight",
      "GreaterGnollsFlail",
      "OgresClubOfHavoc",
      "SwordOfHellfire",
      "TitansGladius",
      "ShieldOfTheDwarvenLords",
      "ShieldOfTheYawningDead",
      "BucklerOfTheGnollKing",
      "TargOfTheRampagingOgre",
      "ShieldOfTheDamned",
      "SentinelsShield",
      "HelmOfTheAlabasterUnicorn",
      "SkullHelmet",
      "HelmOfChaos",
      "CrownOfTheSupremeMagi",
      "HellstormHelmet",
      "ThunderHelmet",
      "BreastplateOfPetrifiedWood",
      "RibCage",
      "ScalesOfTheGreaterBasilisk",
      "TunicOfTheCyclopsKing",
      "BreastplateOfBrimstone",
      "TitansCuirass",
      "ArmorOfWonder",
      "SandalsOfTheSaint",
      "CelestialNecklaceOfBliss",
      "LionsShieldOfCourage",
      "SwordOfJudgement",
      "HelmOfHeavenlyEnlightenment",
      "QuietEyeOfTheDragon",
      "RedDragonFlameTongue",
      "DragonScaleShield",
      "DragonScaleArmor",
      "DragonboneGreaves",
      "DragonWingTabard",
      "NecklaceOfDragonteeth",
      "CrownOfDragontooth",
      "StillEyeOfTheDragon",
      "CloverOfFortune",
      "CardsOfProphecy",
      "LadybirdOfLuck",
      "BadgeOfCourage",
      "CrestOfValor",
      "GlyphOfGallantry",
      "Speculum",
      "Spyglass",
      "AmuletOfTheUndertaker",
      "VampiresCowl",
      "DeadMansBoots",
      "GarnitureOfInterference",
      "SurcoatOfCounterpoise",
      "BootsOfPolarity",
      "BowOfElvenCherrywood",
      "BowstringOfTheUnicornsMane",
      "AngelFeatherArrows",
      "BirdOfPerception",
      "StoicWatchman",
      "EmblemOfCognizance",
      "StatesmansMedal",
      "DiplomatsRing",
      "AmbassadorsSash",
      "RingOfTheWayfarer",
      "EquestriansGloves",
      "NecklaceOfOceanGuidance",
      "AngelWings",
      "CharmOfMana",
      "TalismanOfMana",
      "MysticOrbOfMana",
      "CollarOfConjuring",
      "RingOfConjuring",
      "CapeOfConjuring",
      "OrbOfTheFirmament",
      "OrbOfSilt",
      "OrbOfTempestuousFire",
      "OrbOfDrivingRain",
      "RecantersCloak",
      "SpiritOfOppression",
      "HourglassOfTheEvilHour",
      "TomeOfFireMagic",
      "TomeOfAirMagic",
      "TomeOfWaterMagic",
      "TomeOfEarthMagic",
      "BootsOfLevitation",
      "GoldenBow",
      "SphereOfPermanence",
      "OrbOfVulnerability",
      "RingOfVitality",
      "RingOfLife",
      "VialOfLifeblood",
      "NecklaceOfSwiftness",
      "BootsOfSpeed",
      "CapeOfVelocity",
      "PendantOfDispassion",
      "PendantOfSecondSight",
      "PendantOfHoliness",
      "PendantOfLife",
      "PendantOfDeath",
      "PendantOfFreeWill",
      "PendantOfNegativity",
      "PendantOfTotalRecall",
      "PendantOfCourage",
      "EverflowingCrystalCloak",
      "RingOfInfiniteGems",
      "EverpouringVialOfMercury",
      "InexhaustibleCartOfOre",
      "EversmokingRingOfSulfur",
      "InexhaustibleCartOfLumber",
      "EndlessSackOfGold",
      "EndlessBagOfGold",
      "EndlessPurseOfGold",
      "LegsOfLegion",
      "LoinsOfLegion",
      "TorsoOfLegion",
      "ArmsOfLegion",
      "HeadOfLegion",
      "SeaCaptainsHat",
      "SpellbindersHat",
      "ShacklesOfWar",
      "OrbOfInhibition",
      "VialOfDragonBlood",
      "ArmageddonsBlade",
      "AngelicAlliance",
      "CloakOfTheUndeadKing",
      "ElixirOfLife",
      "ArmorOfTheDamned",
      "StatueOfLegion",
      "PowerOfTheDragonFather",
      "TitansThunder",
      "AdmiralsHat",
      "BowOfTheSharpshooter",
      "WizardsWell",
      "RingOfTheMagi",
      "Cornucopia",
      "DiplomatsSuit",
      "MiredInNeutrality",
      "IronfistOfTheOgre"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return {};
  }

  std::string_view getEnumString(CreatureType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Pikeman",
      "Halberdier",
      "Archer",
      "Marksman",
      "Griffin",
      "RoyalGriffin",
      "Swordsman",
      "Crusader",
      "Monk",
      "Zealot",
      "Cavalier",
      "Champion",
      "Angel",
      "Archangel",
      "Centaur",
      "CentaurCaptain",
      "Dwarf",
      "BattleDwarf",
      "WoodElf",
      "GrandElf",
      "Pegasus",
      "SilverPegasus",
      "DendroidGuard",
      "DendroidSoldier",
      "Unicorn",
      "WarUnicorn",
      "GreenDragon",
      "GoldDragon",
      "Gremlin",
      "MasterGremlin",
      "StoneGargoyle",
      "ObsidianGargoyle",
      "StoneGolem",
      "IronGolem",
      "Mage",
      "ArchMage",
      "Genie",
      "MasterGenie",
      "Naga",
      "NagaQueen",
      "Giant",
      "Titan",
      "Imp",
      "Familiar",
      "Gog",
      "Magog",
      "HellHound",
      "Cerberus",
      "Demon",
      "HornedDemon",
      "PitFiend",
      "PitLord",
      "Efreeti",
      "EfreetSultan",
      "Devil",
      "ArchDevil",
      "Skeleton",
      "SkeletonWarrior",
      "WalkingDead",
      "Zombie",
      "Wight",
      "Wraith",
      "Vampire",
      "VampireLord",
      "Lich",
      "PowerLich",
      "BlackKnight",
      "DreadKnight",
      "BoneDragon",
      "GhostDragon",
      "Troglodyte",
      "InfernalTroglodyte",
      "Harpy",
      "HarpyHag",
      "Beholder",
      "EvilEye",
      "Medusa",
      "MedusaQueen",
      "Minotaur",
      "MinotaurKing",
      "Manticore",
      "Scorpicore",
      "RedDragon",
      "BlackDragon",
      "Goblin",
      "Hobgoblin",
      "WolfRider",
      "WolfRaider",
      "Orc",
      "OrcChieftain",
      "Ogre",
      "OgreMage",
      "Roc",
      "Thunderbird",
      "Cyclops",
      "CyclopsKing",
      "Behemoth",
      "AncientBehemoth",
      "Gnoll",
      "GnollMarauder",
      "Lizardman",
      "LizardWarrior",
      "Gorgon",
      "MightyGorgon",
      "SerpentFly",
      "DragonFly",
      "Basilisk",
      "GreaterBasilisk",
      "Wyvern",
      "WyvernMonarch",
      "Hydra",
      "ChaosHydra",
      "AirElemental",
      "EarthElemental",
      "FireElemental",
      "WaterElemental",
      "GoldGolem",
      "DiamondGolem",
      "Pixie",
      "Sprite",
      "PsychicElemental",
      "MagicElemental",
      "",
      "IceElemental",
      "",
      "MagmaElemental",
      "",
      "StormElemental",
      "",
      "EnergyElemental",
      "Firebird",
      "Phoenix",
      "AzureDragon",
      "CrystalDragon",
      "FaerieDragon",
      "RustDragon",
      "Enchanter",
      "Sharpshooter",
      "Halfling",
      "Peasant",
      "Boar",
      "Mummy",
      "Nomad",
      "Rogue",
      "Troll",
      "Catapult",
      "Ballista",
      "FirstAidTent",
      "AmmoCart",
      "ArrowTowers"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    if (idx == 0xFFFF)
    {
      return "(None)";  // As displayed in the Editor.
    }
    return {};
  }

  std::string_view getEnumString(Disposition value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Compliant",
      "Friendly",
      "Aggressive",
      "Hostile",
      "Savage"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(Formation value) noexcept
  {
    switch (value)
    {
    case Formation::Spread:
      return "Spread";
    case Formation::Grouped:
      return "Grouped";
    default:
      return {};
    }
  }

  std::string_view getEnumString(Gender value) noexcept
  {
    switch (value)
    {
    case Gender::Male:
      return "Male";
    case Gender::Female:
      return "Female";
    case Gender::Default:
      return "Default";
    default:
      return {};
    }
  }

  std::string_view getEnumString(HeroPortrait value) noexcept
  {
    using UnderlyingType = std::underlying_type_t<HeroPortrait>;
    const UnderlyingType idx = static_cast<UnderlyingType>(value);
    if (idx < kNumHeroes)
    {
      return getEnumString(static_cast<HeroType>(idx));
    }
    switch (value)
    {
    case HeroPortrait::GENERAL_KENDAL:
      return "General Kendal";
    case HeroPortrait::CHRISTIAN2:
      return "Christian2";
    case HeroPortrait::ORDWALD:
      return "Ordwald";
    case HeroPortrait::FINNEAS:
      return "Finneas";
    case HeroPortrait::GEM2:
      return "Gem2";
    case HeroPortrait::SANDRO2:
      return "Sandro2";
    case HeroPortrait::YOG2:
      return "Yog2";
    default:
      return std::string_view{};
    }
  }

  std::string_view getEnumString(HeroType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Orrin",
      "Valeska",
      "Edric",
      "Sylvia",
      "Lord Haart",
      "Sorsha",
      "Christian",
      "Tyris",
      "Rion",
      "Adela",
      "Cuthbert",
      "Adelaide",
      "Ingham",
      "Sanya",
      "Loynis",
      "Caitlin",
      "Mephala",
      "Ufretin",
      "Jenova",
      "Ryland",
      "Thorgrim",
      "Ivor",
      "Clancy",
      "Kyrre",
      "Coronius",
      "Uland",
      "Elleshar",
      "Gem",
      "Malcom",
      "Melodia",
      "Alagar",
      "Aeris",
      "Piquedram",
      "Thane",
      "Josephine",
      "Neela",
      "Torosar",
      "Fafner",
      "Rissa",
      "Iona",
      "Astral",
      "Halon",
      "Serena",
      "Daremyth",
      "Theodorus",
      "Solmyr",
      "Cyra",
      "Aine",
      "Fiona",
      "Rashka",
      "Marius",
      "Ignatius",
      "Octavia",
      "Calh",
      "Pyre",
      "Nymus",
      "Ayden",
      "Xyron",
      "Axsis",
      "Olema",
      "Calid",
      "Ash",
      "Zydar",
      "Xarfax",
      "Straker",
      "Vokial",
      "Moandor",
      "Charna",
      "Tamika",
      "Isra",
      "Clavius",
      "Galthran",
      "Septienna",
      "Aislinn",
      "Sandro",
      "Nimbus",
      "Thant",
      "Xsi",
      "Vidomina",
      "Nagash",
      "Lorelei",
      "Arlach",
      "Dace",
      "Ajit",
      "Damacon",
      "Gunnar",
      "Synca",
      "Shakti",
      "Alamar",
      "Jaegar",
      "Malekith",
      "Jeddite",
      "Geon",
      "Deemer",
      "Sephinroth",
      "Darkstorm",
      "Yog",
      "Gurnisson",
      "Jabarkas",
      "Shiva",
      "Gretchin",
      "Krellion",
      "Crag Hack",
      "Tyraxor",
      "Gird",
      "Vey",
      "Dessa",
      "Terek",
      "Zubin",
      "Gundula",
      "Oris",
      "Saurug",
      "Bron",
      "Drakon",
      "Wystan",
      "Tazar",
      "Alkin",
      "Korbac",
      "Gerwulf",
      "Broghild",
      "Mirlanda",
      "Rosic",
      "Voy",
      "Verdish",
      "Merist",
      "Styg",
      "Andra",
      "Tiva",
      "Pasis",
      "Thunar",
      "Ignissa",
      "Lacus",
      "Monere",
      "Erdamon",
      "Fiur",
      "Kalt",
      "Luna",
      "Brissa",
      "Ciele",
      "Labetha",
      "Inteus",
      "Aenain",
      "Gelare",
      "Grindan",
      "Sir Mullich",
      "Adrienne",
      "Catherine",
      "Dracon",
      "Gelu",
      "Kilgor",
      "Haart Lich",
      "Mutare",
      "Roland",
      "Mutare Drake",
      "Boragus",
      "Xeron"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(MapDifficulty value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Easy",
      "Normal",
      "Hard",
      "Expert",
      "Impossible"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(LossConditionType value) noexcept
  {
    switch (value)
    {
    case LossConditionType::LoseTown:
      return "LoseTown";
    case LossConditionType::LoseHero:
      return "LoseHero";
    case LossConditionType::TimeExpires:
      return "TimeExpires";
    case LossConditionType::Normal:
      return "Normal";
    default:
      return {};
    }
  }

  std::string_view getEnumString(MetaObjectType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "ABANDONED_MINE",
      "ARTIFACT",
      "EVENT",
      "GARRISON",
      "GENERIC_NO_PROPERTIES",
      "GRAIL",
      "HERO",
      "MONSTER",
      "PANDORAS_BOX",
      "PLACEHOLDER_HERO",
      "QUEST_GUARD",
      "RANDOM_DWELLING",
      "RANDOM_DWELLING_PRESET_ALIGNMENT",
      "RANDOM_DWELLING_PRESET_LEVEL",
      "RESOURCE",
      "SCHOLAR",
      "SEERS_HUT",
      "SHRINE",
      "SIGN",
      "SPELL_SCROLL",
      "TOWN",
      "TRIVIAL_OWNED_OBJECT",
      "WITCH_HUT",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return {};
  }

  std::string_view getEnumString(ObjectClass value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "NONE_0",
      "DECORATIVE_TOWN",
      "ALTAR_OF_SACRIFICE",
      "ANCHOR_POINT",
      "ARENA",
      "ARTIFACT",
      "PANDORAS_BOX",
      "BLACK_MARKET",
      "BOAT",
      "BORDERGUARD",
      "KEYMASTER",
      "BUOY",
      "CAMPFIRE",
      "CARTOGRAPHER",
      "SWAN_POND",
      "COVER_OF_DARKNESS",
      "CREATURE_BANK",
      "CREATURE_GENERATOR1",
      "CREATURE_GENERATOR2",
      "CREATURE_GENERATOR3",
      "CREATURE_GENERATOR4",
      "CURSED_GROUND1",
      "CORPSE",
      "MARLETTO_TOWER",
      "DERELICT_SHIP",
      "DRAGON_UTOPIA",
      "EVENT",
      "EYE_OF_MAGI",
      "FAERIE_RING",
      "FLOTSAM",
      "FOUNTAIN_OF_FORTUNE",
      "FOUNTAIN_OF_YOUTH",
      "GARDEN_OF_REVELATION",
      "GARRISON",
      "HERO",
      "HILL_FORT",
      "GRAIL",
      "HUT_OF_MAGI",
      "IDOL_OF_FORTUNE",
      "LEAN_TO",
      "BLANK_40",
      "LIBRARY_OF_ENLIGHTENMENT",
      "LIGHTHOUSE",
      "MONOLITH_ONE_WAY_ENTRANCE",
      "MONOLITH_ONE_WAY_EXIT",
      "MONOLITH_TWO_WAY",
      "MAGIC_PLAINS1",
      "SCHOOL_OF_MAGIC",
      "MAGIC_SPRING",
      "MAGIC_WELL",
      "MARKET_OF_TIME",
      "MERCENARY_CAMP",
      "MERMAID",
      "MINE",
      "MONSTER",
      "MYSTICAL_GARDEN",
      "OASIS",
      "OBELISK",
      "REDWOOD_OBSERVATORY",
      "OCEAN_BOTTLE",
      "PILLAR_OF_FIRE",
      "STAR_AXIS",
      "PRISON",
      "PYRAMID",
      "RALLY_FLAG",
      "RANDOM_ART",
      "RANDOM_TREASURE_ART",
      "RANDOM_MINOR_ART",
      "RANDOM_MAJOR_ART",
      "RANDOM_RELIC_ART",
      "RANDOM_HERO",
      "RANDOM_MONSTER",
      "RANDOM_MONSTER_L1",
      "RANDOM_MONSTER_L2",
      "RANDOM_MONSTER_L3",
      "RANDOM_MONSTER_L4",
      "RANDOM_RESOURCE",
      "RANDOM_TOWN",
      "REFUGEE_CAMP",
      "RESOURCE",
      "SANCTUARY",
      "SCHOLAR",
      "SEA_CHEST",
      "SEER_HUT",
      "CRYPT",
      "SHIPWRECK",
      "SHIPWRECK_SURVIVOR",
      "SHIPYARD",
      "SHRINE_OF_MAGIC_INCANTATION",
      "SHRINE_OF_MAGIC_GESTURE",
      "SHRINE_OF_MAGIC_THOUGHT",
      "SIGN",
      "SIRENS",
      "SPELL_SCROLL",
      "STABLES",
      "TAVERN",
      "TEMPLE",
      "DEN_OF_THIEVES",
      "TOWN",
      "TRADING_POST",
      "LEARNING_STONE",
      "TREASURE_CHEST",
      "TREE_OF_KNOWLEDGE",
      "SUBTERRANEAN_GATE",
      "UNIVERSITY",
      "WAGON",
      "WAR_MACHINE_FACTORY",
      "SCHOOL_OF_WAR",
      "WARRIORS_TOMB",
      "WATER_WHEEL",
      "WATERING_HOLE",
      "WHIRLPOOL",
      "WINDMILL",
      "WITCH_HUT",
      "IMPASSABLE_BRUSH",
      "IMPASSABLE_BUSH",
      "IMPASSABLE_CACTUS",
      "IMPASSABLE_CANYON",
      "IMPASSABLE_CRATER",
      "IMPASSABLE_DEADVEGETATION",
      "IMPASSABLE_FLOWERS",
      "IMPASSABLE_FROZENLIKE",
      "IMPASSABLE_HEDGE",
      "IMPASSABLE_HILL",
      "PASSABLE_HOLE",
      "PASSABLE_KELP",
      "IMPASSABLE_LAKE",
      "IMPASSABLE_LAVAFLOW",
      "IMPASSABLE_LAVALAKE",
      "IMPASSABLE_MUSHROOMS",
      "IMPASSABLE_LOG",
      "IMPASSABLE_MANDRAKE",
      "IMPASSABLE_MOSS",
      "IMPASSABLE_MOUND",
      "IMPASSABLE_MOUNTAIN",
      "IMPASSABLE_OAKTREES",
      "IMPASSABLE_OUTCROPPING",
      "IMPASSABLE_PINETREES",
      "IMPASSABLE_PLANT",
      "PASSABLE_139",
      "PASSABLE_140",
      "PASSABLE_141",
      "PASSABLE_142",
      "IMPASSABLE_RIVERDELTA",
      "PASSABLE_144",
      "PASSABLE_145",
      "PASSABLE_146",
      "IMPASSABLE_ROCK",
      "IMPASSABLE_SANDDUNE",
      "IMPASSABLE_SANDPIT",
      "IMPASSABLE_SHRUB",
      "IMPASSABLE_SKULL",
      "IMPASSABLE_STALAGMITE",
      "IMPASSABLE_STUMP",
      "IMPASSABLE_TARPIT",
      "IMPASSABLE_TREES",
      "IMPASSABLE_VINE",
      "IMPASSABLE_VOLCANICVENT",
      "IMPASSABLE_VOLCANO",
      "IMPASSABLE_WILLOWTREES",
      "IMPASSABLE_YUCCATREES",
      "IMPASSABLE_REEF",
      "RANDOM_MONSTER_L5",
      "RANDOM_MONSTER_L6",
      "RANDOM_MONSTER_L7",
      "IMPASSABLE_BRUSH2",
      "IMPASSABLE_BUSH2",
      "IMPASSABLE_CACTUS2",
      "IMPASSABLE_CANYON2",
      "IMPASSABLE_CRATER2",
      "IMPASSABLE_DEADVEGETATION2",
      "IMPASSABLE_FLOWERS2",
      "IMPASSABLE_FROZENLIKE2",
      "IMPASSABLE_HEDGE2",
      "IMPASSABLE_HILL2",
      "PASSABLE_HOLE2",
      "PASSABLE_KELP2",
      "IMPASSABLE_LAKE2",
      "IMPASSABLE_LAVAFLOW2",
      "IMPASSABLE_LAVALAKE2",
      "IMPASSABLE_MUSHROOMS2",
      "IMPASSABLE_LOG2",
      "IMPASSABLE_MANDRAKE2",
      "IMPASSABLE_MOSS2",
      "IMPASSABLE_MOUND2",
      "IMPASSABLE_MOUNTAIN2",
      "IMPASSABLE_OAKTREES2",
      "IMPASSABLE_OUTCROPPING2",
      "IMPASSABLE_PINETREES2",
      "IMPASSABLE_PLANT2",
      "IMPASSABLE_RIVERDELTA2",
      "IMPASSABLE_ROCK2",
      "IMPASSABLE_SANDDUNE2",
      "IMPASSABLE_SANDPIT2",
      "IMPASSABLE_SHRUB2",
      "IMPASSABLE_SKULL2",
      "IMPASSABLE_STALAGMITE2",
      "IMPASSABLE_STUMP2",
      "IMPASSABLE_TARPIT2",
      "IMPASSABLE_TREES2",
      "IMPASSABLE_VINE2",
      "IMPASSABLE_VOLCANICVENT2",
      "IMPASSABLE_VOLCANO2",
      "IMPASSABLE_WILLOWTREES2",
      "IMPASSABLE_YUCCATREES2",
      "IMPASSABLE_REEF2",
      "IMPASSABLE_DESERTHILLS",
      "IMPASSABLE_DIRTHILLS",
      "IMPASSABLE_GRASSHILLS",
      "IMPASSABLE_ROUGHHILLS",
      "IMPASSABLE_SUBTERRANEANROCKS",
      "IMPASSABLE_SWAMPFOLIAGE",
      "BORDER_GATE",
      "FREELANCERS_GUILD",
      "HERO_PLACEHOLDER",
      "QUEST_GUARD",
      "RANDOM_DWELLING",
      "RANDOM_DWELLING_LVL",
      "RANDOM_DWELLING_FACTION",
      "GARRISON2",
      "ABANDONED_MINE",
      "TRADING_POST_SNOW",
      "CLOVER_FIELD",
      "CURSED_GROUND2",
      "EVIL_FOG",
      "FAVORABLE_WINDS",
      "FIERY_FIELDS",
      "HOLY_GROUNDS",
      "LUCID_POOLS",
      "MAGIC_CLOUDS",
      "MAGIC_PLAINS2",
      "ROCKLANDS",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return {};
  }

  std::string_view getEnumString(ObjectGroup value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Terrain",
      "Town",
      "Monster",
      "Hero",
      "Artifact",
      "Treasure"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(PlayerBehavior value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Random",
      "Warrior",
      "Builder",
      "Explorer"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(PlayerColor value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Red",
      "Blue",
      "Tan",
      "Green",
      "Orange",
      "Purple",
      "Teal",
      "Pink"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(PrimarySkillType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Attack",
      "Defense",
      "SpellPower",
      "Knowledge"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(ResourceType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Wood",
      "Mercury",
      "Ore",
      "Sulfur",
      "Crystal",
      "Gems",
      "Gold",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(RewardType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "None",
      "Experience",
      "SpellPoints",
      "Morale",
      "Luck",
      "Resource",
      "PrimarySkill",
      "SecondarySkill",
      "Artifact",
      "Spell",
      "Creature"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(ScholarRewardType value) noexcept
  {
    switch (value)
    {
    case ScholarRewardType::PrimarySkill:
      return "PrimarySkill";
    case ScholarRewardType::SecondarySkill:
      return "SecondarySkill";
    case ScholarRewardType::Spell:
      return "Spell";
    case ScholarRewardType::Random:
      return "Random";
    default:
      return {};
    }
  }

  std::string_view getEnumString(SecondarySkillType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Pathfinding",
      "Archery",
      "Logistics",
      "Scouting",
      "Diplomacy",
      "Navigation",
      "Leadership",
      "Wisdom",
      "Mysticism",
      "Luck",
      "Ballistics",
      "EagleEye",
      "Necromancy",
      "Estates",
      "FireMagic",
      "AirMagic",
      "WaterMagic",
      "EarthMagic",
      "Scholar",
      "Tactics",
      "Artillery",
      "Learning",
      "Offense",
      "Armorer",
      "Intelligence",
      "Sorcery",
      "Resistance",
      "FirstAid"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(SpellType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Summon Boat",
      "Scuttle Boat",
      "Visions",
      "View Earth",
      "Disguise",
      "View Air",
      "Fly",
      "Water Walk",
      "Dimension Door",
      "Town Portal",
      "Quick Sand",
      "Land Mine",
      "Force Field",
      "Fire Wall",
      "Earthquake",
      "Magic Arrow",
      "Ice Bolt",
      "Lightning Bolt",
      "Implosion",
      "Chain Lightning",
      "Frost Ring",
      "Fireball",
      "Inferno",
      "Meteor Shower",
      "Death Ripple",
      "Destroy Undead",
      "Armageddon",
      "Shield",
      "Air Shield",
      "Fire Shield",
      "Protection from Air",
      "Protection from Fire",
      "Protection from Water",
      "Protection from Earth",
      "Anti Magic",
      "Dispel",
      "Magic Mirror",
      "Cure",
      "Resurrection",
      "Animate Dead",
      "Sacrifice",
      "Bless",
      "Curse",
      "Bloodlust",
      "Precision",
      "Weakness",
      "Stone Skin",
      "Disrupting Ray",
      "Prayer",
      "Mirth",
      "Sorrow",
      "Fortune",
      "Misfortune",
      "Haste",
      "Slow",
      "Slayer",
      "Frenzy",
      "Titan's Lightning Bolt",
      "Counterstrike",
      "Berserk",
      "Hypnotize",
      "Forgetfulness",
      "Blind",
      "Teleport",
      "Remove Obstacle",
      "Clone",
      "Fire Elemental",
      "Earth Elemental",
      "Water Elemental",
      "Air Elemental"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(TerrainType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Dirt",
      "Sand",
      "Grass",
      "Snow",
      "Swamp",
      "Rough",
      "Subterranean",
      "Lava",
      "Water",
      "Rock"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(TownType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Castle",
      "Rampart",
      "Tower",
      "Inferno",
      "Necropolis",
      "Dungeon",
      "Stronghold",
      "Fortress",
      "Conflux"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(RiverType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "None",
      "Clear",
      "Icy",
      "Muddy",
      "Lava"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(RoadType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "None",
      "Dirt",
      "Gravel",
      "Cobblestone"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(QuestType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "None",
      "Level",
      "PrimarySkills",
      "DefeatHero",
      "DefeatMonster",
      "Artifacts",
      "Creatures",
      "Resources",
      "BeHero",
      "BePlayer"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return {};
  }

  std::string_view getEnumString(VictoryConditionType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "AcquireArtifact",
      "AccumulateCreatures",
      "AccumulateResources",
      "UpgradeTown",
      "BuildGrail",
      "DefeatHero",
      "CaptureTown",
      "DefeatMonster",
      "FlagDwellings",
      "FlagMines",
      "TransportArtifact"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return value == VictoryConditionType::Normal ? "Normal" : std::string_view{};
  }
}
