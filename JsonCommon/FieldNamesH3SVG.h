#pragma once

// Names of JSON fields for various types used in SavedGame library.

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string_view>

namespace h3json
{
  template<>
  inline constexpr std::array<std::string_view, 48> kEnumFieldNames<h3svg::TownBuildingTypeH3SVG> =
  {
    "mage_guild1",
    "mage_guild2",
    "mage_guild3",
    "mage_guild4",
    "mage_guild5",
    "tavern",
    "wharf",
    "fort",
    "citadel",
    "castle",
    "village_hall",
    "town_hall",
    "city_hall",
    "capitol",
    "market",
    "resource_silo",
    "blacksmith",
    "special17",
    "horde1",
    "horde1u",
    "wharf2",
    "special21",
    "special22",
    "special23",
    "horde2",
    "horde2u",
    "grail",
    "decor27",
    "decor28",
    "decor29",
    "dwelling1",
    "dwelling2",
    "dwelling3",
    "dwelling4",
    "dwelling5",
    "dwelling6",
    "dwelling7",
    "dwelling1u",
    "dwelling2u",
    "dwelling3u",
    "dwelling4u",
    "dwelling5u",
    "dwelling6u",
    "dwelling7u",
    "padding_44",
    "padding_45",
    "padding_46",
    "padding_47"
  };

  template<>
  struct FieldNames<h3svg::Artifact>
  {
    static constexpr std::string_view kGuardians = "guardians";
  };

  template<>
  struct FieldNames<h3svg::Boat>
  {
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kObjectSubclass = "object_sublcass";
    static constexpr std::string_view kDirection = "direction";
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kOwnerHero = "owner_hero";
    static constexpr std::string_view kIsOccupied = "is_occupied";
    static constexpr std::string_view kX = "x";
    static constexpr std::string_view kY = "y";
    static constexpr std::string_view kZ = "z";
    static constexpr std::string_view kUnknown2 = "unknown2";
  };

  template<>
  struct FieldNames<h3svg::Dwelling>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kObjectClass = "object_class";
    static constexpr std::string_view kObjectSubclass = "object_subclass";
    static constexpr std::string_view kCreatureTypes = "creature_types";
    static constexpr std::string_view kCreatureCounts = "creature_counts";
    static constexpr std::string_view kCoordinates = "coordinates";
    static constexpr std::string_view kGuardians = "guardians";
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<h3svg::Garrison>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kCoordinates = "coordinates";
    static constexpr std::string_view kCanRemoveUnits = "can_remove_units";
  };

  template<>
  struct FieldNames<h3svg::Guardians>
  {
    static constexpr std::string_view kMessage = h3m::FieldNames<h3m::Guardians>::kMessage;
    static constexpr std::string_view kCreatures = h3m::FieldNames<h3m::Guardians>::kCreatures;
  };

  template<>
  struct FieldNames<h3svg::EventBase>
  {
    static constexpr std::string_view kGuardians = h3m::FieldNames<h3m::EventBase>::kGuardians;
    static constexpr std::string_view kExperience = h3m::FieldNames<h3m::EventBase>::kExperience;
    static constexpr std::string_view kSpellPoints = h3m::FieldNames<h3m::EventBase>::kSpellPoints;
    static constexpr std::string_view kMorale = h3m::FieldNames<h3m::EventBase>::kMorale;
    static constexpr std::string_view kLuck = h3m::FieldNames<h3m::EventBase>::kLuck;
    static constexpr std::string_view kResources = h3m::FieldNames<h3m::EventBase>::kResources;
    static constexpr std::string_view kPrimarySkills = h3m::FieldNames<h3m::EventBase>::kPrimarySkills;
    static constexpr std::string_view kSecondarySkills = h3m::FieldNames<h3m::EventBase>::kSecondarySkills;
    static constexpr std::string_view kArtifacts = h3m::FieldNames<h3m::EventBase>::kArtifacts;
    static constexpr std::string_view kSpells = h3m::FieldNames<h3m::EventBase>::kSpells;
    static constexpr std::string_view kCreatures = h3m::FieldNames<h3m::EventBase>::kCreatures;
  };

  template<>
  struct FieldNames<h3svg::Hero>
  {
    static constexpr std::string_view kX = "x";
    static constexpr std::string_view kY = "y";
    static constexpr std::string_view kZ = "z";
    static constexpr std::string_view kIsVisible = "is_visible";
    static constexpr std::string_view kCoordinatesPacked = "coordinates_packed";
    static constexpr std::string_view kObjectClassUnder = "object_class_under";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kIsFemale = "is_female";
    static constexpr std::string_view kUseCustomBiography = "use_custom_biography";
    static constexpr std::string_view kBiography = "biography";
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kPatrolRadius = "patrol_radius";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kHeroClass = "hero_class";
    static constexpr std::string_view kPortrait = "portrait";
    static constexpr std::string_view kPatrolX = "patrol_x";
    static constexpr std::string_view kPatrolY = "patrol_y";
    static constexpr std::string_view kUnknown3 = "unknown3";
    static constexpr std::string_view kDestinationX = "destination_x";
    static constexpr std::string_view kDestinationY = "destination_y";
    static constexpr std::string_view kDestinationZ = "destination_z";
    static constexpr std::string_view kUnknown4 = "unknown4";
    static constexpr std::string_view kMovePointsMax = "move_points_max";
    static constexpr std::string_view kMovePoints = "move_points";
    static constexpr std::string_view kExperience = "experience";
    static constexpr std::string_view kUnknown5 = "unknown5";
    static constexpr std::string_view kSpellPoints = "spell_points";
    static constexpr std::string_view kLevel = "level";
    static constexpr std::string_view kUnknown6 = "unknown6";
    static constexpr std::string_view kLearningStones = "learning_stones";
    static constexpr std::string_view kMarlettoTowers = "marletto_towers";
    static constexpr std::string_view kGardensOfRevelation = "gardens_of_revelation";
    static constexpr std::string_view kMercenaryCamps = "mercenary_camps";
    static constexpr std::string_view kStarAxes = "star_axes";
    static constexpr std::string_view kTreesOfKnowledge = "trees_of_knowledge";
    static constexpr std::string_view kLibrariesOfEnlightenment = "libraries_of_enlightenment";
    static constexpr std::string_view kArenas = "arenas";
    static constexpr std::string_view kSchoolsOfMagic = "schools_of_magic";
    static constexpr std::string_view kSchoolsOfWar = "schools_of_war";
    static constexpr std::string_view kUnknown7 = "unknown7";
    static constexpr std::string_view kArmy = "army";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kSecondarySkillsLevels = "secondary_skills_levels";
    static constexpr std::string_view kSecondarySkillsSlots = "secondary_skills_slots";
    static constexpr std::string_view kPrimarySkills = "primary_skills";
    static constexpr std::string_view kSpellsLearned = "spells_learned";
    static constexpr std::string_view kSpellsAvailable = "spells_available";
    static constexpr std::string_view kArtifacts = "artifacts";
    static constexpr std::string_view kUnknown8 = "unknown8";
  };

  template<>
  struct FieldNames<h3svg::Mine>
  {
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kUnknown = "unknown";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kCoordinates = "coordinates";
  };

  template<>
  struct FieldNames<h3svg::Monster>
  {
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kResources = "resources";
    static constexpr std::string_view kArtifact = "artifact";
  };

  template<>
  struct FieldNames<h3svg::Obelisk>
  {
    static constexpr std::string_view kVisitedBy = "visited_by";
  };

  template<>
  struct FieldNames<h3svg::ObjectPropertiesTables>
  {
    static constexpr std::string_view kEventsAndPandorasBoxes = "events_and_pandoras_boxes";
    static constexpr std::string_view kArtifactsAndSpellScrolls = "artifacts_and_spell_scrolls";
    static constexpr std::string_view kMonsters = "monsters";
    static constexpr std::string_view kSeersHuts = "seers_huts";
    static constexpr std::string_view kQuestGuards = "quest_guards";
    static constexpr std::string_view kGlobalEvents = "global_events";
    static constexpr std::string_view kTownEvents = "town_events";
    static constexpr std::string_view kSignsAndOceanBottles = "signs_and_ocean_bottles";
    static constexpr std::string_view kMinesAndLighthouses = "mines_and_lighthouses";
    static constexpr std::string_view kDwellings = "dwellings";
    static constexpr std::string_view kGarrisons = "garrisons";
    static constexpr std::string_view kBoats = "boats";
    static constexpr std::string_view kNumObelisks = "num_obelisks";
    static constexpr std::string_view kObelisks = "obelisks";
  };

  template<>
  struct FieldNames<h3svg::Object>
  {
    static constexpr std::string_view kCoordinates = "coordinates";
    static constexpr std::string_view kTemplateIdx = "template_idx";
  };

  template<>
  struct FieldNames<h3svg::ObjectTemplate>
  {
    static constexpr std::string_view kDef = "def";
    static constexpr std::string_view kWidth = "width";
    static constexpr std::string_view kHeight = "height";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kPassability = "passability";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kActionability = "actionability";
    static constexpr std::string_view kObjectClass = "object_class";
    static constexpr std::string_view kObjectSubclass = "object_subclass";
    static constexpr std::string_view kReserved = "reserved";
    static constexpr std::string_view kIsGround = "is_ground";
  };

  template<>
  struct FieldNames<h3svg::Player>
  {
    static constexpr std::string_view kPlayerColor = "player_color";
    static constexpr std::string_view kNumHeroes = "num_heroes";
    static constexpr std::string_view kActiveHero = "active_hero";
    static constexpr std::string_view kHeroes = "heroes";
    static constexpr std::string_view kHeroesInTavern = "heroes_in_tavern";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kPersonality = "personality";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kDaysLeft = "days_left";
    static constexpr std::string_view kNumTowns = "num_towns";
    static constexpr std::string_view kCurrentTown = "current_town";
    static constexpr std::string_view kTowns = "towns";
    static constexpr std::string_view kUnknown3 = "unknown3";
    static constexpr std::string_view kResources = "resources";
    static constexpr std::string_view kMysticalGardens = "mystical_gardens";
    static constexpr std::string_view kUnknown4 = "unknown4";
    static constexpr std::string_view kCorpses = "corpses";
    static constexpr std::string_view kLeanTos = "lean_tos";
    static constexpr std::string_view kUnknown5 = "unknown5";
  };

  template<>
  struct FieldNames<h3svg::PlayerSpecs>
  {
    static constexpr std::string_view kCanBeHuman = "can_be_human";
    static constexpr std::string_view kCanBeComputer = "can_be_computer";
    static constexpr std::string_view kBehavior = "behavior";
    static constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static constexpr std::string_view kAllowRandomAlignment = "allow_random_alignment";
    static constexpr std::string_view kGeneratedHeroCoordinates = "generated_hero_coordinates";
    static constexpr std::string_view kStartingHero = "starting_hero";
  };

  template<>
  struct FieldNames<h3svg::Quest> : h3m::FieldNames<h3m::Quest>
  {
    // Same fields as for h3m::Quest, plus 1 currently unknown 2-byte field.
    static constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<h3svg::QuestGuard>
  {
    static constexpr std::string_view kQuest = "quest";
    static constexpr std::string_view kVisitedBy = "visited_by";
  };

  template<>
  struct FieldNames<h3svg::Reward> : h3m::FieldNames<h3m::Reward>
  {
    // Same fields as for h3m::Reward.
  };

  template<>
  struct FieldNames<h3svg::Rumor>
  {
    static constexpr std::string_view kText = "text";
    static constexpr std::string_view kHasBeenShown = "has_been_shown";
  };

  template<>
  struct FieldNames<h3svg::SavedGame>
  {
    static constexpr std::string_view kReserved1 = "reserved1";
    static constexpr std::string_view kVersionMajor = "version_major";
    static constexpr std::string_view kVersionMinor = "version_minor";
    static constexpr std::string_view kReserved2 = "reserved2";
    static constexpr std::string_view kFormat = "format";
    static constexpr std::string_view kBasicInfo = "basic_info";
    static constexpr std::string_view kPlayersSpecs = "players_specs";
    static constexpr std::string_view kVictoryCondition = "victory_condition";
    static constexpr std::string_view kLossCondition = "loss_condition";
    static constexpr std::string_view kTeams = "teams";
    static constexpr std::string_view kCustomHeroes = "custom_heroes";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kStartingInfo = "starting_info";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kOriginalFilename = "original_filename";
    static constexpr std::string_view kUnknown3 = "unknown3";
    static constexpr std::string_view kDisabledArtifacts = "disabled_artifacts";
    static constexpr std::string_view kArtifactsBitmaskUnknown = "artifacts_bitmask_unknown";
    static constexpr std::string_view kDisabledSkills = "disabled_skills";
    static constexpr std::string_view kCurrentRumor = "current_rumor";
    static constexpr std::string_view kUnknown4 = "unknown4";
    static constexpr std::string_view kRumors = "rumors";
    static constexpr std::string_view kBlackMarkets = "black_markets";
    static constexpr std::string_view kTiles = "tiles";
    static constexpr std::string_view kObjectsTemplates = "objects_templates";
    static constexpr std::string_view kObjects = "objects";
    static constexpr std::string_view kObjectPropertiesTables = "object_properties_tables";
    static constexpr std::string_view kPlayers = "players";
    static constexpr std::string_view kTowns = "towns";
    static constexpr std::string_view kHeroes = "heroes";
  };

  template<>
  struct FieldNames<h3svg::ScenarioStartingInfo>
  {
    static constexpr std::string_view kStartingTowns = "starting_towns";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kDifficulty = "difficulty";
    static constexpr std::string_view kMapFilename = "map_filename";
    static constexpr std::string_view kMapDirectory = "map_directory";
    static constexpr std::string_view kPlayersControl = "players_control";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kPlayerTurnDuration = "player_turn_duration";
    static constexpr std::string_view kStartingHeroes = "starting_heroes";
    static constexpr std::string_view kStartingBonuses = "starting_bonuses";
  };

  template<>
  struct FieldNames<h3svg::SeersHut>
  {
    static constexpr std::string_view kQuest = "quest";
    static constexpr std::string_view kReward = "reward";
    static constexpr std::string_view kReserved = "reserved";
    static constexpr std::string_view kVisitedBy = "visited_by";
    static constexpr std::string_view kName = "name";
  };

  template<>
  struct FieldNames<h3svg::Sign>
  {
    static constexpr std::string_view kMessage = "message";
    static constexpr std::string_view kIsCustom = "is_custom";
  };

  template<>
  struct FieldNames<h3svg::Tile>
  {
    static constexpr std::string_view kTerrainType = "terrain_type";
    static constexpr std::string_view kTerrainSprite = "terrain_sprite";
    static constexpr std::string_view kRiverType = "river_type";
    static constexpr std::string_view kRiverSprite = "river_sprite";
    static constexpr std::string_view kRoadType = "road_type";
    static constexpr std::string_view kRoadSprite = "road_sprite";
    static constexpr std::string_view kFlags1 = "flags1";
    static constexpr std::string_view kFlags2 = "flags2";
    static constexpr std::string_view kObjectClass = "object_class";
    static constexpr std::string_view kObjectSubclass = "object_subclass";
    static constexpr std::string_view kObjectIdx = "object_idx";
    static constexpr std::string_view kObjectProperties = "properties";
    static constexpr std::string_view kObjectsToRender = "objects_to_render";
  };

  template<>
  struct FieldNames<h3svg::TimedEvent>
  {
    static constexpr std::string_view kMessage = h3m::FieldNames<h3m::TimedEvent>::kMessage;
    static constexpr std::string_view kResources = h3m::FieldNames<h3m::TimedEvent>::kResources;
    static constexpr std::string_view kAffectedPlayers = h3m::FieldNames<h3m::TimedEvent>::kAffectedPlayers;
    static constexpr std::string_view kAppliesToHuman = h3m::FieldNames<h3m::TimedEvent>::kAppliesToHuman;
    static constexpr std::string_view kAppliesToComputer = h3m::FieldNames<h3m::TimedEvent>::kAppliesToComputer;
    static constexpr std::string_view kDayOfFirstOccurence = h3m::FieldNames<h3m::TimedEvent>::kDayOfFirstOccurence;
    static constexpr std::string_view kRepeatAfterDays = h3m::FieldNames<h3m::TimedEvent>::kRepeatAfterDays;
  };

  template<>
  struct FieldNames<h3svg::Town>
  {
    static constexpr std::string_view kId = "id";
    static constexpr std::string_view kOwner = "owner";
    static constexpr std::string_view kBuiltThisTurn = "built_this_turn";
    static constexpr std::string_view kUnknown1 = "unknown1";
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kCoordinates = "coordinates";
    static constexpr std::string_view kGeneratedBoatX = "generated_boat_x";
    static constexpr std::string_view kGeneratedBoatY = "generated_boat_y";
    static constexpr std::string_view kGarrison = "garrison";
    static constexpr std::string_view kGarrisonedHero = "garrisoned_hero";
    static constexpr std::string_view kVisitingHero = "visiting_hero";
    static constexpr std::string_view kMageGuildLevel = "mage_guild_level";
    static constexpr std::string_view kUnknown2 = "unknown2";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kRecruitsNonUpgraded = "recruits_nonupgraded";
    static constexpr std::string_view kRecruitsUpgraded = "recruits_upgraded";
    static constexpr std::string_view kNumExternalDwellings = "num_external_dwellings";
    static constexpr std::string_view kNumExternalDwellings2 = "num_external_dwellings2";
    static constexpr std::string_view kUnknown3 = "unknown3";
    static constexpr std::string_view kBuilt = "built";
    static constexpr std::string_view kReserved1 = "reserved1";
    static constexpr std::string_view kCanBeBuilt = "can_be_built";
    static constexpr std::string_view kReserved2 = "reserved2";
    static constexpr std::string_view kSpells = "spells";
    static constexpr std::string_view kBannedSpells = "banned_spells";
    static constexpr std::string_view kUnknown4 = "unknown4";
  };

  template<>
  struct FieldNames<h3svg::TownEvent> : FieldNames<h3svg::TimedEvent>
  {
    static constexpr std::string_view kTownId = "town_id";
    static constexpr std::string_view kBuildings = "buildings";
    static constexpr std::string_view kReserved = "reserved";
    static constexpr std::string_view kCreatures = "creatures";
  };

  template<>
  struct FieldNames<h3svg::Troops>
  {
    static constexpr std::string_view kCreatureTypes = "creature_types";
    static constexpr std::string_view kCreatureCounts = "creature_counts";
  };
}
