#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/MetaObjectType.h>

#include <array>
#include <string_view>

namespace h3m
{
  // Stores the names of JSON fields for the specified class.
  // This is to ensure that H3MJsonWriter and H3MJsonReader use the same names:
  // * A typo in a string will only be discovered at runtime, but a typo in a static
  //   data member will cause a compilation error.
  // * This should also guarantee that these strings are only stored once in the binary.
  template<class T>
  struct FieldNames;

  template<>
  struct FieldNames<CreatureStack>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kCount = "count";
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
    static inline constexpr std::string_view kHeadwear = "headwear";
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
    static inline constexpr std::string_view kDevice1 = "device1";
    static inline constexpr std::string_view kDevice2 = "device2";
    static inline constexpr std::string_view kDevice3 = "device3";
    static inline constexpr std::string_view kDevice4 = "device4";
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
  struct FieldNames<Map>
  {
    static inline constexpr std::string_view kFormat = "format";
    static inline constexpr std::string_view kBasicInfo = "basic_info";
    static inline constexpr std::string_view kPlayers = "players";
    static inline constexpr std::string_view kAdditionalInfo = "additional_info";
    static inline constexpr std::string_view kTiles = "tiles";
    static inline constexpr std::string_view kObjectsAttributes = "objects_attributes";
    static inline constexpr std::string_view kObjectsDetails = "objects_details";
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
    static inline constexpr std::string_view kArtifactsNonavailability = "artifacts_nonavailability";
    static inline constexpr std::string_view kDisabledSpells = "disabled_spells";
    static inline constexpr std::string_view kDisabledSkills = "disabled_skills";
    static inline constexpr std::string_view kRumors = "rumors";
    static inline constexpr std::string_view kHeroesSettings = "heroes_settings";
  };

  template<>
  struct FieldNames<ObjectAttributes>
  {
    static inline constexpr std::string_view kDef = "def";
    static inline constexpr std::string_view kPassability = "passability";
    static inline constexpr std::string_view kActionability = "actionability";
    static inline constexpr std::string_view kAllowedLandscapes = "allowed_landscapes";
    static inline constexpr std::string_view kLandscapeGroup = "landscape_group";
    static inline constexpr std::string_view kObjectClass = "object_class";
    static inline constexpr std::string_view kObjectNumber = "object_number";
    static inline constexpr std::string_view kObjectGroup = "object_group";
    static inline constexpr std::string_view kIsGround = "is_ground";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetails>
  {
    static inline constexpr std::string_view kX = "x";
    static inline constexpr std::string_view kY = "y";
    static inline constexpr std::string_view kZ = "z";
    static inline constexpr std::string_view kKind = "kind";
    static inline constexpr std::string_view kUnknown = "unknown";
    static inline constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::ABANDONED_MINE>>
  {
    static inline constexpr std::string_view kPotentialResources = "potential_resources";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::ARTIFACT>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::EVENT>> : FieldNames<EventBase>
  {
    static inline constexpr std::string_view kAffectedPlayers = "affected_players";
    static inline constexpr std::string_view kAppliesToComputer = "applies_to_computer";
    static inline constexpr std::string_view kRemoveAfterFirstVisit = "remove_after_first_visit";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::GARRISON>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kCanRemoveUnits = "can_remove_units";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::GRAIL>>
  {
    static inline constexpr std::string_view kAllowableRadius = "allowable_radius";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::HERO>>
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
  struct FieldNames<ObjectDetailsData<MetaObjectType::PANDORAS_BOX>> : FieldNames<EventBase>
  {};

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>>
  {
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kPowerRating = "power_rating";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::RESOURCE>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
    static inline constexpr std::string_view kQuantity = "quantity";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::SHRINE>>
  {
    static inline constexpr std::string_view kSpell = "spell";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::SIGN>>
  {
    static inline constexpr std::string_view kMessage = "message";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::SPELL_SCROLL>>
  {
    static inline constexpr std::string_view kGuardians = "guardians";
    static inline constexpr std::string_view kSpell = "spell";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::TOWN>>
  {
    static inline constexpr std::string_view kAbsodId = "absod_id";
    static inline constexpr std::string_view kOwner = "owner";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kCreatures = "creatures";
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
  struct FieldNames<ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    static inline constexpr std::string_view kOwner = "owner";
  };

  template<>
  struct FieldNames<ObjectDetailsData<MetaObjectType::WITCH_HUT>>
  {
    static inline constexpr std::string_view kSkillsAvailability = "skills_availability";
  };

  template<>
  struct FieldNames<PlayerSpecs>
  {
    static inline constexpr std::string_view kCanBeHuman = "can_be_human";
    static inline constexpr std::string_view kCanBeComputer = "can_be_computer";
    static inline constexpr std::string_view kBehavior = "behavior";
    static inline constexpr std::string_view kCustomizedAlignments = "customized_alignments";
    static inline constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static inline constexpr std::string_view kRandomTown = "random_town";
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

  struct FieldNamesResourcesBase
  {
    static inline constexpr std::string_view kWood = "wood";
    static inline constexpr std::string_view kMercury = "mercury";
    static inline constexpr std::string_view kOre = "ore";
    static inline constexpr std::string_view kSulfur = "sulfur";
    static inline constexpr std::string_view kCrystal = "crystal";
    static inline constexpr std::string_view kGems = "gems";
    static inline constexpr std::string_view kGold = "gold";
  };

  template<class T>
  struct FieldNames<Resources<T>> : FieldNamesResourcesBase {};

  template<>
  struct FieldNames<ResourcesBitmask>
  {
    // Name for each bit in the bitmask (from LSB to MSB).
    static inline constexpr std::string_view kNames[] = {
      "wood", "mercury", "ore", "sulfur", "crystal", "gems", "gold", "unknown"
    };
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
    // The number of bit fields in SecondarySkillsBitmask.
    static constexpr std::size_t kNumBits = 32;
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
  struct FieldNames<TownEvent> : FieldNames<TimedEventBase>
  {
    static inline constexpr std::string_view kBuildings = "buildings";
    static inline constexpr std::string_view kCreatures = "creatures";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
  };
}
