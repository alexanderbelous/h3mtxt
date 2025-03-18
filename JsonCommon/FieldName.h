#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/MetaObjectType.h>

#include <array>
#include <string_view>
#include <type_traits>

namespace h3m
{
  namespace Detail_NS
  {
    template<class T>
    struct EnumBitmaskSize {};

    template<class Enum, std::size_t NumBytes>
    struct EnumBitmaskSize<EnumBitmask<Enum, NumBytes>> : std::integral_constant<std::size_t, NumBytes> {};

    // The size of the input EnumBitmask in bytes.
    template<class T>
    inline constexpr std::size_t EnumBitmaskSize_v = EnumBitmaskSize<T>::value;
  }

  // Stores the names of JSON fields for the specified class.
  // This is to ensure that H3JsonWriter and H3JsonReader use the same names:
  // * A typo in a string will only be discovered at runtime, but a typo in a static
  //   data member will cause a compilation error.
  // * This should also guarantee that these strings are only stored once in the binary.
  template<class T>
  struct FieldNames;

  template<>
  struct FieldNames<ArtifactsBitmask>
  {
    // The number of bits in TownsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<ArtifactsBitmask> * 8;
    // Name for each bit field in TownsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames
    {
      "spellbook",
      "spell_scroll",
      "grail",
      "catapult",
      "ballista",
      "ammo_cart",
      "first_aid_tent",
      "centaur_axe",
      "blackshard_of_the_dead_knight",
      "greater_gnolls_flail",
      "ogres_club_of_havoc",
      "sword_of_hellfire",
      "titans_gladius",
      "shield_of_the_dwarven_lords",
      "shield_of_the_yawning_dead",
      "buckler_of_the_gnoll_king",
      "targ_of_the_rampaging_ogre",
      "shield_of_the_damned",
      "sentinels_shield",
      "helm_of_the_alabaster_unicorn",
      "skull_helmet",
      "helm_of_chaos",
      "crown_of_the_supreme_magi",
      "hellstorm_helmet",
      "thunder_helmet",
      "breastplate_of_petrified_wood",
      "rib_cage",
      "scales_of_the_greater_basilisk",
      "tunic_of_the_cyclops_king",
      "breastplate_of_brimstone",
      "titans_cuirass",
      "armor_of_wonder",
      "sandals_of_the_saint",
      "celestial_necklace_of_bliss",
      "lions_shield_of_courage",
      "sword_of_judgement",
      "helm_of_heavenly_enlightenment",
      "quiet_eye_of_the_dragon",
      "red_dragon_flame_tongue",
      "dragon_scale_shield",
      "dragon_scale_armor",
      "dragonbone_greaves",
      "dragon_wing_tabard",
      "necklace_of_dragonteeth",
      "crown_of_dragontooth",
      "still_eye_of_the_dragon",
      "clover_of_fortune",
      "cards_of_prophecy",
      "ladybird_of_luck",
      "badge_of_courage",
      "crest_of_valor",
      "glyph_of_gallantry",
      "speculum",
      "spyglass",
      "amulet_of_the_undertaker",
      "vampires_cowl",
      "dead_mans_boots",
      "garniture_of_interference",
      "surcoat_of_counterpoise",
      "boots_of_polarity",
      "bow_of_elven_cherrywood",
      "bowstring_of_the_unicorns_mane",
      "angel_feather_arrows",
      "bird_of_perception",
      "stoic_watchman",
      "emblem_of_cognizance",
      "statesmans_medal",
      "diplomats_ring",
      "ambassadors_sash",
      "ring_of_the_wayfarer",
      "equestrians_gloves",
      "necklace_of_ocean_guidance",
      "angel_wings",
      "charm_of_mana",
      "talisman_of_mana",
      "mystic_orb_of_mana",
      "collar_of_conjuring",
      "ring_of_conjuring",
      "cape_of_conjuring",
      "orb_of_the_firmament",
      "orb_of_silt",
      "orb_of_tempestuous_fire",
      "orb_of_driving_rain",
      "recanters_cloak",
      "spirit_of_oppression",
      "hourglass_of_the_evil_hour",
      "tome_of_fire_magic",
      "tome_of_air_magic",
      "tome_of_water_magic",
      "tome_of_earth_magic",
      "boots_of_levitation",
      "golden_bow",
      "sphere_of_permanence",
      "orb_of_vulnerability",
      "ring_of_vitality",
      "ring_of_life",
      "vial_of_lifeblood",
      "necklace_of_swiftness",
      "boots_of_speed",
      "cape_of_velocity",
      "pendant_of_dispassion",
      "pendant_of_second_sight",
      "pendant_of_holiness",
      "pendant_of_life",
      "pendant_of_death",
      "pendant_of_free_will",
      "pendant_of_negativity",
      "pendant_of_total_recall",
      "pendant_of_courage",
      "everflowing_crystal_cloak",
      "ring_of_infinite_gems",
      "everpouring_vial_of_mercury",
      "inexhaustible_cart_of_ore",
      "eversmoking_ring_of_sulfur",
      "inexhaustible_cart_of_lumber",
      "endless_sack_of_gold",
      "endless_bag_of_gold",
      "endless_purse_of_gold",
      "legs_of_legion",
      "loins_of_legion",
      "torso_of_legion",
      "arms_of_legion",
      "head_of_legion",
      "sea_captains_hat",
      "spellbinders_hat",
      "shackles_of_war",
      "orb_of_inhibition",
      "vial_of_dragon_blood",
      "armageddons_blade",
      "angelic_alliance",
      "cloak_of_the_undead_king",
      "elixir_of_life",
      "armor_of_the_damned",
      "statue_of_legion",
      "power_of_the_dragon_father",
      "titans_thunder",
      "admirals_hat",
      "bow_of_the_sharpshooter",
      "wizards_well",
      "ring_of_the_magi",
      "cornucopia",
      "diplomats_suit",
      "mired_in_neutrality",
      "ironfist_of_the_ogre"
    };
  };

  template<>
  struct FieldNames<CreatureStack>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kCount = "count";
  };

  template<>
  struct FieldNames<CrossoverFeaturesBitmask>
  {
    // The number of bits in CrossoverFeaturesBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<CrossoverFeaturesBitmask> * 8;
    // Name for each bit field in CrossoverFeaturesBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames
    {
      "experience",
      "primary_skills",
      "secondary_skills",
      "spells",
      "artifacts",
      "padding_5",
      "padding_6",
      "padding_7",
    };
  };

  template<>
  struct FieldNames<EventBase>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
    static inline constexpr std::string_view kExperience = "experience";
    static inline constexpr std::string_view kSpellPoints = "spell_points";
    static inline constexpr std::string_view kMorale = "morale";
    static inline constexpr std::string_view kLuck = "luck";
    static inline constexpr std::string_view kResources = "resources";
    static inline constexpr std::string_view kPrimarySkills = "primary_skills";
    static inline constexpr std::string_view kSecondarySkills = "secondary_skills";
    static inline constexpr std::string_view kArtifacts = "artifacts";
    static inline constexpr std::string_view kSpells = "spells";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<Guardians>
  {
    static inline constexpr std::string_view kMessage = "message";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<HeroArtifacts>
  {
    static inline constexpr std::string_view kHead = "head";
    static inline constexpr std::string_view kShoulders = "shoulders";
    static inline constexpr std::string_view kNeck = "neck";
    static inline constexpr std::string_view kRightHand = "right_hand";
    static inline constexpr std::string_view kLeftHand = "left_hand";
    static inline constexpr std::string_view kTorso = "torso";
    static inline constexpr std::string_view kRightRing = "right_ring";
    static inline constexpr std::string_view kLeftRing = "left_ring";
    static inline constexpr std::string_view kFeet = "feet";
    static inline constexpr std::string_view kMisc1 = "misc1";
    static inline constexpr std::string_view kMisc2 = "misc2";
    static inline constexpr std::string_view kMisc3 = "misc3";
    static inline constexpr std::string_view kMisc4 = "misc4";
    static inline constexpr std::string_view kMisc5 = "misc5";
    static inline constexpr std::string_view kWarMachine1 = "war_machine1";
    static inline constexpr std::string_view kWarMachine2 = "war_machine2";
    static inline constexpr std::string_view kWarMachine3 = "war_machine3";
    static inline constexpr std::string_view kWarMachine4 = "war_machine4";
    static inline constexpr std::string_view kSpellbook = "spellbook";
    static inline constexpr std::string_view kBackpack = "backpack";
  };

  template<>
  struct FieldNames<HeroSettings>
  {
    static inline constexpr std::string_view kExperience = "experience";
    static inline constexpr std::string_view kSecondarySkills = "secondary_skills";
    static inline constexpr std::string_view kArtifacts = "artifacts";
    static inline constexpr std::string_view kBiography = "biography";
    static inline constexpr std::string_view kGender = "gender";
    static inline constexpr std::string_view kSpells = "spells";
    static inline constexpr std::string_view kPrimarySkills = "primary_skills";
  };

  template<>
  struct FieldNames<HeroesBitmask>
  {
    // The number of bits in HeroesBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<HeroesBitmask> * 8;
    // Name for each bit field in HeroesBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames
    {
      "orrin",
      "valeska",
      "edric",
      "sylvia",
      "lord_haart",
      "sorsha",
      "christian",
      "tyris",
      "rion",
      "adela",
      "cuthbert",
      "adelaide",
      "ingham",
      "sanya",
      "loynis",
      "caitlin",
      "mephala",
      "ufretin",
      "jenova",
      "ryland",
      "thorgrim",
      "ivor",
      "clancy",
      "kyrre",
      "coronius",
      "uland",
      "elleshar",
      "gem",
      "malcom",
      "melodia",
      "alagar",
      "aeris",
      "piquedram",
      "thane",
      "josephine",
      "neela",
      "torosar",
      "fafner",
      "rissa",
      "iona",
      "astral",
      "halon",
      "serena",
      "daremyth",
      "theodorus",
      "solmyr",
      "cyra",
      "aine",
      "fiona",
      "rashka",
      "marius",
      "ignatius",
      "octavia",
      "calh",
      "pyre",
      "nymus",
      "ayden",
      "xyron",
      "axsis",
      "olema",
      "calid",
      "ash",
      "zydar",
      "xarfax",
      "straker",
      "vokial",
      "moandor",
      "charna",
      "tamika",
      "isra",
      "clavius",
      "galthran",
      "septienna",
      "aislinn",
      "sandro",
      "nimbus",
      "thant",
      "xsi",
      "vidomina",
      "nagash",
      "lorelei",
      "arlach",
      "dace",
      "ajit",
      "damacon",
      "gunnar",
      "synca",
      "shakti",
      "alamar",
      "jaegar",
      "malekith",
      "jeddite",
      "geon",
      "deemer",
      "sephinroth",
      "darkstorm",
      "yog",
      "gurnisson",
      "jabarkas",
      "shiva",
      "gretchin",
      "krellion",
      "crag_hack",
      "tyraxor",
      "gird",
      "vey",
      "dessa",
      "terek",
      "zubin",
      "gundula",
      "oris",
      "saurug",
      "bron",
      "drakon",
      "wystan",
      "tazar",
      "alkin",
      "korbac",
      "gerwulf",
      "broghild",
      "mirlanda",
      "rosic",
      "voy",
      "verdish",
      "merist",
      "styg",
      "andra",
      "tiva",
      "pasis",
      "thunar",
      "ignissa",
      "lacus",
      "monere",
      "erdamon",
      "fiur",
      "kalt",
      "luna",
      "brissa",
      "ciele",
      "labetha",
      "inteus",
      "aenain",
      "gelare",
      "grindan",
      "sir_mullich",
      "adrienne",
      "catherine",
      "dracon",
      "gelu",
      "kilgor",
      "haart_lich",
      "mutare",
      "roland",
      "mutare_drake",
      "boragus",
      "xeron",
      "padding_156",
      "padding_157",
      "padding_158",
      "padding_159"
    };
  };

  template<>
  struct FieldNames<LossCondition>
  {
    // Note: LossCondition has only 1 data member `details`, which is a std::variant.
    // However, it is serialized as 2 fields: `type` (LossConditionType) and
    // `details` (LossConditionDetails<type>).
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<MainTown>
  {
    static inline constexpr std::string_view kGenerateHero = "generate_hero";
    static inline constexpr std::string_view kTownType = "town_type";
    static inline constexpr std::string_view kX = "x";
    static inline constexpr std::string_view kY = "y";
    static inline constexpr std::string_view kZ = "z";
  };

  template<>
  struct FieldNames<Map>
  {
    static inline constexpr std::string_view kFormat = "format";
    static inline constexpr std::string_view kBasicInfo = "basic_info";
    static inline constexpr std::string_view kPlayers = "players";
    static inline constexpr std::string_view kAdditionalInfo = "additional_info";
    static inline constexpr std::string_view kTiles = "tiles";
    static inline constexpr std::string_view kObjectsTemplates = "objects_templates";
    static inline constexpr std::string_view kObjects = "objects";
    static inline constexpr std::string_view kGlobalEvents = "global_events";
    static inline constexpr std::string_view kPadding = "padding";
  };

  template<>
  struct FieldNames<MapBasicInfo>
  {
    static inline constexpr std::string_view kIsPlayable = "is_playable";
    static inline constexpr std::string_view kMapSize = "map_size";
    static inline constexpr std::string_view kHasTwoLevels = "has_two_levels";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kDescription = "description";
    static inline constexpr std::string_view kDifficulty = "difficulty";
    static inline constexpr std::string_view kMaxHeroLevel = "max_hero_level";
  };

  template<>
  struct FieldNames<MapAdditionalInfo>
  {
    static inline constexpr std::string_view kVictoryCondition = "victory_condition";
    static inline constexpr std::string_view kLossCondition = "loss_condition";
    static inline constexpr std::string_view kTeams = "teams";
    static inline constexpr std::string_view kHeroesAvailability = "heroes_availability";
    static inline constexpr std::string_view kPlaceholderHeroes = "placeholder_heroes";
    static inline constexpr std::string_view kCustomHeroes = "custom_heroes";
    static inline constexpr std::string_view kReserved = "reserved";
    static inline constexpr std::string_view kDisabledArtifacts = "disabled_artifacts";
    static inline constexpr std::string_view kDisabledSpells = "disabled_spells";
    static inline constexpr std::string_view kDisabledSkills = "disabled_skills";
    static inline constexpr std::string_view kRumors = "rumors";
    static inline constexpr std::string_view kHeroesSettings = "heroes_settings";
  };

  template<>
  struct FieldNames<MessageAndTreasure>
  {
    static inline constexpr std::string_view kMessage = "message";
    static inline constexpr std::string_view kResources = "resources";
    static inline constexpr std::string_view kArtifact = "artifact";
  };

  template<>
  struct FieldNames<ObjectTemplate>
  {
    static inline constexpr std::string_view kDef = "def";
    static inline constexpr std::string_view kPassability = "passability";
    static inline constexpr std::string_view kActionability = "actionability";
    static inline constexpr std::string_view kAllowedLandscapes = "allowed_landscapes";
    static inline constexpr std::string_view kLandscapeGroup = "landscape_group";
    static inline constexpr std::string_view kObjectClass = "object_class";
    static inline constexpr std::string_view kObjectSubclass = "object_subclass";
    static inline constexpr std::string_view kObjectGroup = "object_group";
    static inline constexpr std::string_view kIsGround = "is_ground";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<Object>
  {
    static inline constexpr std::string_view kX = "x";
    static inline constexpr std::string_view kY = "y";
    static inline constexpr std::string_view kZ = "z";
    static inline constexpr std::string_view kTemplateIdx = "template_idx";
    static inline constexpr std::string_view kUnknown = "unknown";
    static inline constexpr std::string_view kProperties = "properties";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::ABANDONED_MINE>>
  {
    static inline constexpr std::string_view kPotentialResources = "potential_resources";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::ARTIFACT>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::EVENT>> : FieldNames<EventBase>
  {
    static inline constexpr std::string_view kAffectedPlayers = "affected_players";
    static inline constexpr std::string_view kAppliesToComputer = "applies_to_computer";
    static inline constexpr std::string_view kRemoveAfterFirstVisit = "remove_after_first_visit";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::GARRISON>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kUnknown = "unknown";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kCanRemoveUnits = "can_remove_units";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::GRAIL>>
  {
    static inline constexpr std::string_view kAllowableRadius = "allowable_radius";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::HERO>>
  {
    static inline constexpr std::string_view kAbsodId = "absod_id";
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kExperience = "experience";
    static inline constexpr std::string_view kPortrait = "portrait";
    static inline constexpr std::string_view kSecondarySkills = "secondary_skills";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kFormation = "formation";
    static inline constexpr std::string_view kArtifacts = "artifacts";
    static inline constexpr std::string_view kPatrolRadius = "patrol_radius";
    static inline constexpr std::string_view kBiography = "biography";
    static inline constexpr std::string_view kGender = "gender";
    static inline constexpr std::string_view kSpells = "spells";
    static inline constexpr std::string_view kPrimarySkills = "primary_skills";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::MONSTER>>
  {
    static inline constexpr std::string_view kAbsodId = "absod_id";
    static inline constexpr std::string_view kCount = "count";
    static inline constexpr std::string_view kDisposition = "disposition";
    static inline constexpr std::string_view kMessageAndTreasure = "message_and_treasure";
    static inline constexpr std::string_view kNeverFlees = "never_flees";
    static inline constexpr std::string_view kDoesNotGrow = "does_not_grow";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::PANDORAS_BOX>> : FieldNames<EventBase>
  {};

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kPowerRating = "power_rating";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::QUEST_GUARD>>
  {
    static inline constexpr std::string_view kQuest = "quest";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kTownAbsodId = "town_absod_id";
    static inline constexpr std::string_view kAlignment = "alignment";
    static inline constexpr std::string_view kMinLevel = "min_level";
    static inline constexpr std::string_view kMaxLevel = "max_level";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kMinLevel = "min_level";
    static inline constexpr std::string_view kMaxLevel = "max_level";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kTownAbsodId = "town_absod_id";
    static inline constexpr std::string_view kAlignment = "alignment";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RESOURCE>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
    static inline constexpr std::string_view kQuantity = "quantity";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SCHOLAR>>
  {
    static inline constexpr std::string_view kRewardType = "reward_type";
    static inline constexpr std::string_view kRewardValue = "reward_value";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SEERS_HUT>>
  {
    static inline constexpr std::string_view kQuest = "quest";
    static inline constexpr std::string_view kReward = "reward";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SHRINE>>
  {
    static inline constexpr std::string_view kSpell = "spell";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SIGN>>
  {
    static inline constexpr std::string_view kMessage = "message";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SPELL_SCROLL>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
    static inline constexpr std::string_view kSpell = "spell";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::TOWN>>
  {
    static inline constexpr std::string_view kAbsodId = "absod_id";
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kGarrison = "garrison";
    static inline constexpr std::string_view kFormation = "formation";
    static inline constexpr std::string_view kBuildings = "buildings";
    static inline constexpr std::string_view kHasFort = "has_fort";
    static inline constexpr std::string_view kMustHaveSpell = "must_have_spell";
    static inline constexpr std::string_view kMayNotHaveSpell = "may_not_have_spell";
    static inline constexpr std::string_view kEvents = "events";
    static inline constexpr std::string_view kAlignment = "alignment";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::WITCH_HUT>>
  {
    static inline constexpr std::string_view kPotentialSkills = "potential_skills";
  };

  template<>
  struct FieldNames<PlayerSpecs>
  {
    static inline constexpr std::string_view kCanBeHuman = "can_be_human";
    static inline constexpr std::string_view kCanBeComputer = "can_be_computer";
    static inline constexpr std::string_view kBehavior = "behavior";
    static inline constexpr std::string_view kHasCustomizedAlignments = "has_customized_alignments";
    static inline constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static inline constexpr std::string_view kAllowRandomAlignment = "allow_random_alignment";
    static inline constexpr std::string_view kMainTown = "main_town";
    static inline constexpr std::string_view kHasRandomHeroes = "has_random_heroes";
    static inline constexpr std::string_view kStartingHero = "starting_hero";
    static inline constexpr std::string_view kNumNonspecificPlaceholderHeroes = "num_nonspecific_placeholder_heroes";
    static inline constexpr std::string_view kHeroes = "heroes";
  };

  template<>
  struct FieldNames<PlayersBitmask>
  {
  private:
    static inline constexpr std::array<std::string_view, 8> kPlayersNames = {
      "red", "blue", "tan", "green", "orange", "purple", "teal", "pink"
    };

  public:
    // Returns the name of the field for the specified player in PlayersBitmask.
    //
    // PlayersBitmask is stored as 1 byte in .h3m, but in JSON it's serialized as
    // 8 boolean fields (1 per player).
    // \param player - input PlayerColor.
    // \return the name of the field for @player in PlayersBitmask.
    // \throw std::out_of_range if int(player) >= 8.
    static constexpr std::string_view get(PlayerColor player)
    {
      return kPlayersNames.at(static_cast<std::size_t>(player));
    }
  };

  template<>
  struct FieldNames<PrimarySkills>
  {
    static inline constexpr std::string_view kAttack = "attack";
    static inline constexpr std::string_view kDefense = "defense";
    static inline constexpr std::string_view kSpellPower = "spell_power";
    static inline constexpr std::string_view kKnowledge = "knowledge";
  };

  template<>
  struct FieldNames<Quest>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
    static inline constexpr std::string_view kDeadline = "deadline";
    static inline constexpr std::string_view kProposal = "proposal";
    static inline constexpr std::string_view kProgress = "progress";
    static inline constexpr std::string_view kCompletion = "completion";
  };

  template<>
  struct FieldNames<Resources>
  {
    static inline constexpr std::string_view kWood = "wood";
    static inline constexpr std::string_view kMercury = "mercury";
    static inline constexpr std::string_view kOre = "ore";
    static inline constexpr std::string_view kSulfur = "sulfur";
    static inline constexpr std::string_view kCrystal = "crystal";
    static inline constexpr std::string_view kGems = "gems";
    static inline constexpr std::string_view kGold = "gold";
  };

  template<>
  struct FieldNames<ResourcesBitmask>
  {
    // Name for each bit in the bitmask (from LSB to MSB).
    static inline constexpr std::string_view kNames[] = {
      "wood", "mercury", "ore", "sulfur", "crystal", "gems", "gold", "unknown"
    };
  };

  template<>
  struct FieldNames<Reward>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<Rumor>
  {
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kDescription = "description";
  };

  template<>
  struct FieldNames<SecondarySkill>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kLevel = "level";
  };

  template<>
  struct FieldNames<SecondarySkillsBitmask>
  {
    // The number of bits in SecondarySkillsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<SecondarySkillsBitmask> * 8;
    // Name for each bit field in SecondarySkillsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames{
        "pathfinding",
        "archery",
        "logistics",
        "scouting",
        "diplomacy",
        "navigation",
        "leadership",
        "wisdom",
        "mysticism",
        "luck",
        "ballistics",
        "eagle_eye",
        "necromancy",
        "estates",
        "fire_magic",
        "air_magic",
        "water_magic",
        "earth_magic",
        "scholar",
        "tactics",
        "artillery",
        "learning",
        "offense",
        "armorer",
        "intelligence",
        "sorcery",
        "resistance",
        "first_aid",
        "padding_28",
        "padding_29",
        "padding_30",
        "padding_31"
    };
  };

  template<>
  struct FieldNames<SpellsBitmask>
  {
    // The number of bits in SpellsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<SpellsBitmask> * 8;
    // Name for each bit field in SpellsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames{
      "summon_boat",
      "scuttle_boat",
      "visions",
      "view_earth",
      "disguise",
      "view_air",
      "fly",
      "water_walk",
      "dimension_door",
      "town_portal",
      "quick_sand",
      "land_mine",
      "force_field",
      "fire_wall",
      "earthquake",
      "magic_arrow",
      "ice_bolt",
      "lightning_bolt",
      "implosion",
      "chain_lightning",
      "frost_ring",
      "fireball",
      "inferno",
      "meteor_shower",
      "death_ripple",
      "destroy_undead",
      "armageddon",
      "shield",
      "air_shield",
      "fire_shield",
      "protection_from_air",
      "protection_from_fire",
      "protection_from_water",
      "protection_from_earth",
      "anti_magic",
      "dispel",
      "magic_mirror",
      "cure",
      "resurrection",
      "animate_dead",
      "sacrifice",
      "bless",
      "curse",
      "bloodlust",
      "precision",
      "weakness",
      "stone_skin",
      "disrupting_ray",
      "prayer",
      "mirth",
      "sorrow",
      "fortune",
      "misfortune",
      "haste",
      "slow",
      "slayer",
      "frenzy",
      "titans_lightning_bolt",
      "counterstrike",
      "berserk",
      "hypnotize",
      "forgetfulness",
      "blind",
      "teleport",
      "remove_obstacle",
      "clone",
      "fire_elemental",
      "earth_elemental",
      "water_elemental",
      "air_elemental",
      "padding_70",
      "padding_71"
    };
  };

  template<>
  struct FieldNames<StartingHero>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kPortrait = "portrait";
    static inline constexpr std::string_view kName = "name";
  };

  template<>
  struct FieldNames<TeamsInfo>
  {
    static inline constexpr std::string_view kNumTeams = "num_teams";
    static inline constexpr std::string_view kTeamForPlayer = "team_for_player";
  };

  template<>
  struct FieldNames<Tile>
  {
    static inline constexpr std::string_view kTerrainType = "terrain_type";
    static inline constexpr std::string_view kTerrainSprite = "terrain_sprite";
    static inline constexpr std::string_view kRiverType = "river_type";
    static inline constexpr std::string_view kRiverSprite = "river_sprite";
    static inline constexpr std::string_view kRoadType = "road_type";
    static inline constexpr std::string_view kRoadSprite = "road_sprite";
    static inline constexpr std::string_view kMirroring = "mirroring";
  };

  template<>
  struct FieldNames<TimedEventBase>
  {
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kMessage = "message";
    static inline constexpr std::string_view kResources = "resources";
    static inline constexpr std::string_view kAffectedPlayers = "affected_players";
    static inline constexpr std::string_view kAppliesToHuman = "applies_to_human";
    static inline constexpr std::string_view kAppliesToComputer = "applies_to_computer";
    static inline constexpr std::string_view kDayOfFirstOccurence = "day_of_first_occurence";
    static inline constexpr std::string_view kRepeatAfterDays = "repeat_after_days";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<TownBuildings>
  {
    static inline constexpr std::string_view kIsBuilt = "is_built";
    static inline constexpr std::string_view kIsDisabled = "is_disabled";
  };

  template<>
  struct FieldNames<TownBuildingsBitmask>
  {
    // The number of bits in TownBuildingsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<TownBuildingsBitmask> * 8;
    // Name for each bit field in TownBuildingsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames
    {
      "town_hall",
      "city_hall",
      "capitol",
      "fort",
      "citadel",
      "castle",
      "tavern",
      "blacksmith",
      "marketplace",
      "resource_silo",
      "artifact_merchants",
      "mage_guild_1",
      "mage_guild_2",
      "mage_guild_3",
      "mage_guild_4",
      "mage_guild_5",
      "shipyard",
      "grail",
      "special_building_1",
      "special_building_2",
      "special_building_3",
      "special_building_4",
      "dwelling_1",
      "dwelling_1u",
      "horde_1",
      "dwelling_2",
      "dwelling_2u",
      "horde_2",
      "dwelling_3",
      "dwelling_3u",
      "horde_3",
      "dwelling_4",
      "dwelling_4u",
      "horde_4",
      "dwelling_5",
      "dwelling_5u",
      "horde_5",
      "dwelling_6",
      "dwelling_6u",
      "dwelling_7",
      "dwelling_7u",
      "padding_41",
      "padding_42",
      "padding_43",
      "padding_44",
      "padding_45",
      "padding_46",
      "padding_47"
    };
  };

  template<>
  struct FieldNames<TownEvent> : FieldNames<TimedEventBase>
  {
    static inline constexpr std::string_view kBuildings = "buildings";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<TownsBitmask>
  {
    // The number of bits in TownsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<TownsBitmask> * 8;
    // Name for each bit field in TownsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames
    {
      "castle",
      "rampart",
      "tower",
      "inferno",
      "necropolis",
      "dungeon",
      "stronghold",
      "fortress",
      "conflux",
      "padding_9",
      "padding_10",
      "padding_11",
      "padding_12",
      "padding_13",
      "padding_14",
      "padding_15",
    };
  };

  template<>
  struct FieldNames<VictoryCondition>
  {
    // Note: VictoryCondition has only 1 data member `details`, which is a std::variant.
    // However, it is serialized as 2 fields: `type` (VictoryConditionType) and
    // `details` (VictoryConditionDetails<type>).
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
  };

  // === Campaign ===
  template<>
  struct FieldNames<Campaign>
  {
    static inline constexpr std::string_view kHeader = "header";
    static inline constexpr std::string_view kMaps = "maps";
  };

  template<>
  struct FieldNames<CampaignHeader>
  {
    static inline constexpr std::string_view kFormat = "format";
    static inline constexpr std::string_view kId = "id";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kDescription = "description";
    static inline constexpr std::string_view kAllowSelectingDifficulty = "allow_selecting_difficulty";
    static inline constexpr std::string_view kThemeMusic = "theme_music";
    static inline constexpr std::string_view kScenarios = "scenarios";
  };

  template<>
  struct FieldNames<CampaignScenario>
  {
    static inline constexpr std::string_view kMapFilename = "map_filename";
    static inline constexpr std::string_view kMapFileSize = "map_file_size";
    static inline constexpr std::string_view kPrerequisites = "prerequisites";
    static inline constexpr std::string_view kRegionColor = "region_color";
    static inline constexpr std::string_view kDefaultDifficulty = "default_difficulty";
    static inline constexpr std::string_view kRegionRightClickText = "region_righ_click_text";
    static inline constexpr std::string_view kPrologue = "prologue";
    static inline constexpr std::string_view kEpilogue = "epilogue";
    static inline constexpr std::string_view kCrossoverOptions = "crossover_options";
    static inline constexpr std::string_view kStartingOptions = "starting_options";
  };

  template<>
  struct FieldNames<CrossoverOptions>
  {
    static inline constexpr std::string_view kRetainedFeatures = "retained_features";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kArtifacts = "artifacts";
  };

  template<>
  struct FieldNames<CutScene>
  {
    static inline constexpr std::string_view kMovie = "movie";
    static inline constexpr std::string_view kMusic = "music";
    static inline constexpr std::string_view kMessage = "message";
  };

  template<>
  struct FieldNames<StartingBonus>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<StartingOptions>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kDetails = "details";
  };
}
