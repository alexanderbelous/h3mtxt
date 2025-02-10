#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/Map/Constants/Formation.h>
#include <h3mtxt/Map/Constants/Gender.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/ScholarRewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>

#include <iterator>

namespace h3m
{
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
