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
  // * This also guarantees that these strings are only stored once in the binary,
  //   even if string pooling is disabled.
  template<class T>
  struct FieldNames;

  template<>
  struct FieldNames<ArtifactsBitmask>
  {
    // The number of bits in TownsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<ArtifactsBitmask> * 8;
    // Name for each bit field in TownsBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames
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
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kCount = "count";
  };

  template<>
  struct FieldNames<EventBase>
  {
    static constexpr std::string_view kGuardians = "guardians";
    static constexpr std::string_view kExperience = "experience";
    static constexpr std::string_view kSpellPoints = "spell_points";
    static constexpr std::string_view kMorale = "morale";
    static constexpr std::string_view kLuck = "luck";
    static constexpr std::string_view kResources = "resources";
    static constexpr std::string_view kPrimarySkills = "primary_skills";
    static constexpr std::string_view kSecondarySkills = "secondary_skills";
    static constexpr std::string_view kArtifacts = "artifacts";
    static constexpr std::string_view kSpells = "spells";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<Guardians>
  {
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<HeroArtifacts>
  {
    static constexpr std::string_view kHead = "head";
    static constexpr std::string_view kShoulders = "shoulders";
    static constexpr std::string_view kNeck = "neck";
    static constexpr std::string_view kRightHand = "right_hand";
    static constexpr std::string_view kLeftHand = "left_hand";
    static constexpr std::string_view kTorso = "torso";
    static constexpr std::string_view kRightRing = "right_ring";
    static constexpr std::string_view kLeftRing = "left_ring";
    static constexpr std::string_view kFeet = "feet";
    static constexpr std::string_view kMisc1 = "misc1";
    static constexpr std::string_view kMisc2 = "misc2";
    static constexpr std::string_view kMisc3 = "misc3";
    static constexpr std::string_view kMisc4 = "misc4";
    static constexpr std::string_view kMisc5 = "misc5";
    static constexpr std::string_view kWarMachine1 = "war_machine1";
    static constexpr std::string_view kWarMachine2 = "war_machine2";
    static constexpr std::string_view kWarMachine3 = "war_machine3";
    static constexpr std::string_view kWarMachine4 = "war_machine4";
    static constexpr std::string_view kSpellbook = "spellbook";
    static constexpr std::string_view kBackpack = "backpack";
  };

  template<>
  struct FieldNames<HeroSettings>
  {
    static constexpr std::string_view kExperience = "experience";
    static constexpr std::string_view kSecondarySkills = "secondary_skills";
    static constexpr std::string_view kArtifacts = "artifacts";
    static constexpr std::string_view kBiography = "biography";
    static constexpr std::string_view kGender = "gender";
    static constexpr std::string_view kSpells = "spells";
    static constexpr std::string_view kPrimarySkills = "primary_skills";
  };

  template<>
  struct FieldNames<HeroesBitmask>
  {
    // The number of bits in HeroesBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<HeroesBitmask> * 8;
    // Name for each bit field in HeroesBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames
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
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<MainTown>
  {
    static constexpr std::string_view kGenerateHero = "generate_hero";
    static constexpr std::string_view kTownType = "town_type";
    static constexpr std::string_view kX = "x";
    static constexpr std::string_view kY = "y";
    static constexpr std::string_view kZ = "z";
  };

  template<>
  struct FieldNames<Map>
  {
    static constexpr std::string_view kFormat = "format";
    static constexpr std::string_view kBasicInfo = "basic_info";
    static constexpr std::string_view kPlayers = "players";
    static constexpr std::string_view kAdditionalInfo = "additional_info";
    static constexpr std::string_view kTiles = "tiles";
    static constexpr std::string_view kObjectsTemplates = "objects_templates";
    static constexpr std::string_view kObjects = "objects";
    static constexpr std::string_view kGlobalEvents = "global_events";
    static constexpr std::string_view kPadding = "padding";
  };

  template<>
  struct FieldNames<MapBasicInfo>
  {
    static constexpr std::string_view kIsPlayable = "is_playable";
    static constexpr std::string_view kMapSize = "map_size";
    static constexpr std::string_view kHasTwoLevels = "has_two_levels";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kDescription = "description";
    static constexpr std::string_view kDifficulty = "difficulty";
    static constexpr std::string_view kMaxHeroLevel = "max_hero_level";
  };

  template<>
  struct FieldNames<MapAdditionalInfo>
  {
    static constexpr std::string_view kVictoryCondition = "victory_condition";
    static constexpr std::string_view kLossCondition = "loss_condition";
    static constexpr std::string_view kTeams = "teams";
    static constexpr std::string_view kHeroesAvailability = "heroes_availability";
    static constexpr std::string_view kPlaceholderHeroes = "placeholder_heroes";
    static constexpr std::string_view kCustomHeroes = "custom_heroes";
    static constexpr std::string_view kReserved = "reserved";
    static constexpr std::string_view kDisabledArtifacts = "disabled_artifacts";
    static constexpr std::string_view kDisabledSpells = "disabled_spells";
    static constexpr std::string_view kDisabledSkills = "disabled_skills";
    static constexpr std::string_view kRumors = "rumors";
    static constexpr std::string_view kHeroesSettings = "heroes_settings";
  };

  template<>
  struct FieldNames<MessageAndTreasure>
  {
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kResources = "resources";
    static constexpr std::string_view kArtifact = "artifact";
  };

  template<>
  struct FieldNames<ObjectTemplate>
  {
    static constexpr std::string_view kDef = "def";
    static constexpr std::string_view kPassability = "passability";
    static constexpr std::string_view kActionability = "actionability";
    static constexpr std::string_view kAllowedLandscapes = "allowed_landscapes";
    static constexpr std::string_view kLandscapeGroup = "landscape_group";
    static constexpr std::string_view kObjectClass = "object_class";
    static constexpr std::string_view kObjectSubclass = "object_subclass";
    static constexpr std::string_view kObjectGroup = "object_group";
    static constexpr std::string_view kIsGround = "is_ground";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<Object>
  {
    static constexpr std::string_view kX = "x";
    static constexpr std::string_view kY = "y";
    static constexpr std::string_view kZ = "z";
    static constexpr std::string_view kTemplateIdx = "template_idx";
    static constexpr std::string_view kUnknown = "unknown";
    static constexpr std::string_view kProperties = "properties";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::ABANDONED_MINE>>
  {
    static constexpr std::string_view kPotentialResources = "potential_resources";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::ARTIFACT>>
  {
    static constexpr std::string_view kGuardians = "guardians";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::EVENT>> : FieldNames<EventBase>
  {
    static constexpr std::string_view kAffectedPlayers = "affected_players";
    static constexpr std::string_view kAppliesToComputer = "applies_to_computer";
    static constexpr std::string_view kRemoveAfterFirstVisit = "remove_after_first_visit";
    static constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::GARRISON>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kUnknown = "unknown";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kCanRemoveUnits = "can_remove_units";
    static constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::GRAIL>>
  {
    static constexpr std::string_view kAllowableRadius = "allowable_radius";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::HERO>>
  {
    static constexpr std::string_view kAbsodId = "absod_id";
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kExperience = "experience";
    static constexpr std::string_view kPortrait = "portrait";
    static constexpr std::string_view kSecondarySkills = "secondary_skills";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kFormation = "formation";
    static constexpr std::string_view kArtifacts = "artifacts";
    static constexpr std::string_view kPatrolRadius = "patrol_radius";
    static constexpr std::string_view kBiography = "biography";
    static constexpr std::string_view kGender = "gender";
    static constexpr std::string_view kSpells = "spells";
    static constexpr std::string_view kPrimarySkills = "primary_skills";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::MONSTER>>
  {
    static constexpr std::string_view kAbsodId = "absod_id";
    static constexpr std::string_view kCount = "count";
    static constexpr std::string_view kDisposition = "disposition";
    static constexpr std::string_view kMessageAndTreasure = "message_and_treasure";
    static constexpr std::string_view kNeverFlees = "never_flees";
    static constexpr std::string_view kDoesNotGrow = "does_not_grow";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::PANDORAS_BOX>> : FieldNames<EventBase>
  {};

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kPowerRating = "power_rating";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::QUEST_GUARD>>
  {
    static constexpr std::string_view kQuest = "quest";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kTownAbsodId = "town_absod_id";
    static constexpr std::string_view kAlignment = "alignment";
    static constexpr std::string_view kMinLevel = "min_level";
    static constexpr std::string_view kMaxLevel = "max_level";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kMinLevel = "min_level";
    static constexpr std::string_view kMaxLevel = "max_level";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kTownAbsodId = "town_absod_id";
    static constexpr std::string_view kAlignment = "alignment";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::RESOURCE>>
  {
    static constexpr std::string_view kGuardians = "guardians";
    static constexpr std::string_view kQuantity = "quantity";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SCHOLAR>>
  {
    static constexpr std::string_view kRewardType = "reward_type";
    static constexpr std::string_view kRewardValue = "reward_value";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SEERS_HUT>>
  {
    static constexpr std::string_view kQuest = "quest";
    static constexpr std::string_view kReward = "reward";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SHRINE>>
  {
    static constexpr std::string_view kSpell = "spell";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SIGN>>
  {
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::SPELL_SCROLL>>
  {
    static constexpr std::string_view kGuardians = "guardians";
    static constexpr std::string_view kSpell = "spell";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::TOWN>>
  {
    static constexpr std::string_view kAbsodId = "absod_id";
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kGarrison = "garrison";
    static constexpr std::string_view kFormation = "formation";
    static constexpr std::string_view kBuildings = "buildings";
    static constexpr std::string_view kHasFort = "has_fort";
    static constexpr std::string_view kMustHaveSpell = "must_have_spell";
    static constexpr std::string_view kMayNotHaveSpell = "may_not_have_spell";
    static constexpr std::string_view kEvents = "events";
    static constexpr std::string_view kAlignment = "alignment";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectProperties<MetaObjectType::WITCH_HUT>>
  {
    static constexpr std::string_view kPotentialSkills = "potential_skills";
  };

  template<>
  struct FieldNames<PlayerSpecs>
  {
    static constexpr std::string_view kCanBeHuman = "can_be_human";
    static constexpr std::string_view kCanBeComputer = "can_be_computer";
    static constexpr std::string_view kBehavior = "behavior";
    static constexpr std::string_view kHasCustomizedAlignments = "has_customized_alignments";
    static constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static constexpr std::string_view kAllowRandomAlignment = "allow_random_alignment";
    static constexpr std::string_view kMainTown = "main_town";
    static constexpr std::string_view kHasRandomHeroes = "has_random_heroes";
    static constexpr std::string_view kStartingHero = "starting_hero";
    static constexpr std::string_view kNumNonspecificPlaceholderHeroes = "num_nonspecific_placeholder_heroes";
    static constexpr std::string_view kHeroes = "heroes";
  };

  template<>
  struct FieldNames<PlayersBitmask>
  {
    // The number of bits in PlayersBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<PlayersBitmask> *8;
    // Name for each bit in the bitmask (from LSB to MSB).
    static constexpr std::array<std::string_view, kNumBits> kNames =
    {
      "red", "blue", "tan", "green", "orange", "purple", "teal", "pink"
    };
  };

  template<>
  struct FieldNames<PrimarySkills>
  {
    static constexpr std::string_view kAttack = "attack";
    static constexpr std::string_view kDefense = "defense";
    static constexpr std::string_view kSpellPower = "spell_power";
    static constexpr std::string_view kKnowledge = "knowledge";
  };

  template<>
  struct FieldNames<Quest>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
    static constexpr std::string_view kDeadline = "deadline";
    static constexpr std::string_view kProposal = "proposal";
    static constexpr std::string_view kProgress = "progress";
    static constexpr std::string_view kCompletion = "completion";
  };

  template<>
  struct FieldNames<Resources>
  {
    static constexpr std::string_view kWood = "wood";
    static constexpr std::string_view kMercury = "mercury";
    static constexpr std::string_view kOre = "ore";
    static constexpr std::string_view kSulfur = "sulfur";
    static constexpr std::string_view kCrystal = "crystal";
    static constexpr std::string_view kGems = "gems";
    static constexpr std::string_view kGold = "gold";
  };

  template<>
  struct FieldNames<ResourcesBitmask>
  {
    // The number of bits in ResourcesBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<ResourcesBitmask> *8;
    // Name for each bit in the bitmask (from LSB to MSB).
    static constexpr std::array<std::string_view, kNumBits> kNames =
    {
      "wood", "mercury", "ore", "sulfur", "crystal", "gems", "gold", "unknown"
    };
  };

  template<>
  struct FieldNames<Reward>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<Rumor>
  {
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kDescription = "description";
  };

  template<>
  struct FieldNames<SecondarySkill>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kLevel = "level";
  };

  template<>
  struct FieldNames<SecondarySkillsBitmask>
  {
    // The number of bits in SecondarySkillsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<SecondarySkillsBitmask> * 8;
    // Name for each bit field in SecondarySkillsBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames{
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
    static constexpr std::array<std::string_view, kNumBits> kNames{
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
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kPortrait = "portrait";
    static constexpr std::string_view kName = "name";
  };

  template<>
  struct FieldNames<TeamsInfo>
  {
    static constexpr std::string_view kNumTeams = "num_teams";
    static constexpr std::string_view kTeamForPlayer = "team_for_player";
  };

  template<>
  struct FieldNames<Tile>
  {
    static constexpr std::string_view kTerrainType = "terrain_type";
    static constexpr std::string_view kTerrainSprite = "terrain_sprite";
    static constexpr std::string_view kRiverType = "river_type";
    static constexpr std::string_view kRiverSprite = "river_sprite";
    static constexpr std::string_view kRoadType = "road_type";
    static constexpr std::string_view kRoadSprite = "road_sprite";
    static constexpr std::string_view kMirroring = "mirroring";
  };

  template<>
  struct FieldNames<TimedEventBase>
  {
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kResources = "resources";
    static constexpr std::string_view kAffectedPlayers = "affected_players";
    static constexpr std::string_view kAppliesToHuman = "applies_to_human";
    static constexpr std::string_view kAppliesToComputer = "applies_to_computer";
    static constexpr std::string_view kDayOfFirstOccurence = "day_of_first_occurence";
    static constexpr std::string_view kRepeatAfterDays = "repeat_after_days";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<TownBuildings>
  {
    static constexpr std::string_view kIsBuilt = "is_built";
    static constexpr std::string_view kIsDisabled = "is_disabled";
  };

  template<>
  struct FieldNames<TownBuildingsBitmask>
  {
    // The number of bits in TownBuildingsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<TownBuildingsBitmask> * 8;
    // Name for each bit field in TownBuildingsBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames
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
    static constexpr std::string_view kBuildings = "buildings";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<TownsBitmask>
  {
    // The number of bits in TownsBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<TownsBitmask> * 8;
    // Name for each bit field in TownsBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames
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
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };

  // === Campaign ===
  template<>
  struct FieldNames<Campaign>
  {
    static constexpr std::string_view kHeader = "header";
    static constexpr std::string_view kMaps = "maps";
  };

  template<>
  struct FieldNames<CampaignHeader>
  {
    static constexpr std::string_view kFormat = "format";
    static constexpr std::string_view kId = "id";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kDescription = "description";
    static constexpr std::string_view kAllowSelectingDifficulty = "allow_selecting_difficulty";
    static constexpr std::string_view kThemeMusic = "theme_music";
    static constexpr std::string_view kScenarios = "scenarios";
  };

  template<>
  struct FieldNames<CampaignScenario>
  {
    static constexpr std::string_view kMapFilename = "map_filename";
    static constexpr std::string_view kMapFileSize = "map_file_size";
    static constexpr std::string_view kPrerequisites = "prerequisites";
    static constexpr std::string_view kRegionColor = "region_color";
    static constexpr std::string_view kDefaultDifficulty = "default_difficulty";
    static constexpr std::string_view kRegionRightClickText = "region_righ_click_text";
    static constexpr std::string_view kPrologue = "prologue";
    static constexpr std::string_view kEpilogue = "epilogue";
    static constexpr std::string_view kCrossoverOptions = "crossover_options";
    static constexpr std::string_view kStartingOptions = "starting_options";
  };

  template<>
  struct FieldNames<CrossoverFeaturesBitmask>
  {
    // The number of bits in CrossoverFeaturesBitmask.
    static constexpr std::size_t kNumBits = Detail_NS::EnumBitmaskSize_v<CrossoverFeaturesBitmask> * 8;
    // Name for each bit field in CrossoverFeaturesBitmask.
    static constexpr std::array<std::string_view, kNumBits> kNames
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
  struct FieldNames<CrossoverOptions>
  {
    static constexpr std::string_view kRetainedFeatures = "retained_features";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kArtifacts = "artifacts";
  };

  template<>
  struct FieldNames<CutScene>
  {
    static constexpr std::string_view kMovie = "movie";
    static constexpr std::string_view kMusic = "music";
    static constexpr std::string_view kMessage = "message";
  };

  template<>
  struct FieldNames<StartingBonus>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<StartingOptions>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };
}
