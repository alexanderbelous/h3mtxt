#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace h3json
{
  template<>
  h3svg::Hero JsonReader<h3svg::Hero>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Hero>;
    h3svg::Hero hero;
    readField(hero.x, value, Fields::kX);
    readField(hero.y, value, Fields::kY);
    readField(hero.z, value, Fields::kZ);
    readField(hero.is_visible, value, Fields::kIsVisible);
    readField(hero.coordinates_packed, value, Fields::kCoordinatesPacked);
    readField(hero.object_class_under, value, Fields::kObjectClassUnder);
    readField(hero.unknown1, value, Fields::kUnknown1);
    readField(hero.is_female, value, Fields::kIsFemale);
    readField(hero.use_custom_biography, value, Fields::kUseCustomBiography);
    readField(hero.biography, value, Fields::kBiography);
    readField(hero.owner, value, Fields::kOwner);
    readField(hero.patrol_radius, value, Fields::kPatrolRadius);
    readField(hero.temp_morale, value, Fields::kTempMorale);
    readField(hero.temp_luck, value, Fields::kTempLuck);
    readField(hero.backpack_count, value, Fields::kBackpackCount);
    readField(hero.disguise_level, value, Fields::kDisguiseLevel);
    readField(hero.fly_level, value, Fields::kFlyLevel);
    readField(hero.water_walk_level, value, Fields::kWaterWalkLevel);
    readField(hero.num_dimension_door_casts, value, Fields::kNumDimensionDoorCasts);
    readField(hero.visions_level, value, Fields::kVisionsLevel);
    readField(hero.type, value, Fields::kType);
    readField(hero.hero_class, value, Fields::kHeroClass);
    readField(hero.portrait, value, Fields::kPortrait);
    readField(hero.patrol_x, value, Fields::kPatrolX);
    readField(hero.patrol_y, value, Fields::kPatrolY);
    readField(hero.unknown2, value, Fields::kUnknown2);
    readField(hero.destination_x, value, Fields::kDestinationX);
    readField(hero.destination_y, value, Fields::kDestinationY);
    readField(hero.destination_z, value, Fields::kDestinationZ);
    readField(hero.unknown3, value, Fields::kUnknown3);
    readField(hero.move_points_max, value, Fields::kMovePointsMax);
    readField(hero.move_points, value, Fields::kMovePoints);
    readField(hero.experience, value, Fields::kExperience);
    readField(hero.unknown4, value, Fields::kUnknown4);
    readField(hero.spell_points, value, Fields::kSpellPoints);
    readField(hero.level, value, Fields::kLevel);
    readField(hero.unknown5, value, Fields::kUnknown5);
    readField(hero.learning_stones, value, Fields::kLearningStones);
    readField(hero.marletto_towers, value, Fields::kMarlettoTowers);
    readField(hero.gardens_of_revelation, value, Fields::kGardensOfRevelation);
    readField(hero.mercenary_camps, value, Fields::kMercenaryCamps);
    readField(hero.star_axes, value, Fields::kStarAxes);
    readField(hero.trees_of_knowledge, value, Fields::kTreesOfKnowledge);
    readField(hero.libraries_of_enlightenment, value, Fields::kLibrariesOfEnlightenment);
    readField(hero.arenas, value, Fields::kArenas);
    readField(hero.schools_of_magic, value, Fields::kSchoolsOfMagic);
    readField(hero.schools_of_war, value, Fields::kSchoolsOfWar);
    readField(hero.reserved, value, Fields::kReserved);
    readField(hero.flags, value, Fields::kFlags);
    readField(hero.army, value, Fields::kArmy);
    readField(hero.name, value, Fields::kName);
    readField(hero.secondary_skills_levels, value, Fields::kSecondarySkillsLevels);
    readField(hero.secondary_skills_slots, value, Fields::kSecondarySkillsSlots);
    readField(hero.primary_skills, value, Fields::kPrimarySkills);
    readField(hero.spells_learned, value, Fields::kSpellsLearned);
    readField(hero.spells_available, value, Fields::kSpellsAvailable);
    readField(hero.artifacts, value, Fields::kArtifacts);
    readField(hero.is_sleeping, value, Fields::kIsSleeping);
    readField(hero.visited_towns, value, Fields::kVisitedTowns);
    return hero;
  }

  template<>
  h3svg::HeroArtifact
  JsonReader<h3svg::HeroArtifact>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::HeroArtifact>;
    h3svg::HeroArtifact artifact;
    readField(artifact.type, value, Fields::kType);
    readField(artifact.spell_type, value, Fields::kSpellType);
    return artifact;
  }

  template<>
  h3svg::HeroArtifacts
  JsonReader<h3svg::HeroArtifacts>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::HeroArtifacts>;
    h3svg::HeroArtifacts artifacts;
    readField(artifacts.equipped, value, Fields::kEquipped);
    readField(artifacts.backpack, value, Fields::kBackpack);
    readField(artifacts.unknown, value, Fields::kUnknown);
    readField(artifacts.locks, value, Fields::kLocks);
    return artifacts;
  }
}
