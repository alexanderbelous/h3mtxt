#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/FixedLengthString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace h3json
{
  template<>
  h3svg::Hero JsonReader2<h3svg::Hero>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Hero>;
    h3svg::Hero hero;
    readField(Fields::kX, hero.x);
    readField(Fields::kY, hero.y);
    readField(Fields::kZ, hero.z);
    readField(Fields::kIsVisible, hero.is_visible);
    readField(Fields::kCoordinatesPacked, hero.coordinates_packed);
    readField(Fields::kHasObjectUnder, hero.has_object_under);
    readField(Fields::kObjectUnder, hero.object_under);
    readField(Fields::kIsFemale, hero.is_female);
    readField(Fields::kUseCustomBiography, hero.use_custom_biography);
    readField(Fields::kBiography, hero.biography);
    readField(Fields::kOwner, hero.owner);
    readField(Fields::kPatrolRadius, hero.patrol_radius);
    readField(Fields::kTempMorale, hero.temp_morale);
    readField(Fields::kTempLuck, hero.temp_luck);
    readField(Fields::kBackpackCount, hero.backpack_count);
    readField(Fields::kActiveSpells, hero.active_spells);
    readField(Fields::kType, hero.type);
    readField(Fields::kHeroClass, hero.hero_class);
    readField(Fields::kPortrait, hero.portrait);
    readField(Fields::kPatrolX, hero.patrol_x);
    readField(Fields::kPatrolY, hero.patrol_y);
    readField(Fields::kOrientation, hero.orientation);
    readField(Fields::kFormationFlags, hero.formation_flags);
    readField(Fields::kSeed, hero.seed);
    readField(Fields::kUnknown1, hero.unknown1);
    readField(Fields::kDestinationX, hero.destination_x);
    readField(Fields::kDestinationY, hero.destination_y);
    readField(Fields::kDestinationZ, hero.destination_z);
    readField(Fields::kUnknown2, hero.unknown2);
    readField(Fields::kMovePointsMax, hero.move_points_max);
    readField(Fields::kMovePoints, hero.move_points);
    readField(Fields::kExperience, hero.experience);
    readField(Fields::kNumSecondarySkills, hero.num_secondary_skills);
    readField(Fields::kSpellPoints, hero.spell_points);
    readField(Fields::kLevel, hero.level);
    readField(Fields::kUnknown3, hero.unknown3);
    readField(Fields::kVisitedObjects, hero.visited_objects);
    readField(Fields::kReserved, hero.reserved);
    readField(Fields::kFlags, hero.flags);
    readField(Fields::kArmy, hero.army);
    readField(Fields::kName, hero.name);
    readField(Fields::kSecondarySkillsLevels, hero.secondary_skills_levels);
    readField(Fields::kSecondarySkillsSlots, hero.secondary_skills_slots);
    readField(Fields::kPrimarySkills, hero.primary_skills);
    readField(Fields::kSpellsLearned, hero.spells_learned);
    readField(Fields::kSpellsAvailable, hero.spells_available);
    readField(Fields::kArtifacts, hero.artifacts);
    readField(Fields::kIsSleeping, hero.is_sleeping);
    readField(Fields::kVisitedTowns, hero.visited_towns);
    return hero;
  }

  template<>
  h3svg::HeroActiveSpells JsonReader2<h3svg::HeroActiveSpells>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::HeroActiveSpells>;
    h3svg::HeroActiveSpells spells;
    readField(Fields::kDisguiseLevel, spells.disguise_level);
    readField(Fields::kFlyLevel, spells.fly_level);
    readField(Fields::kWaterWalkLevel, spells.water_walk_level);
    readField(Fields::kNumDimensionDoorCasts, spells.num_dimension_door_casts);
    readField(Fields::kVisionsLevel, spells.visions_level);
    return spells;
  }

  template<>
  h3svg::HeroArtifact JsonReader2<h3svg::HeroArtifact>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::HeroArtifact>;
    h3svg::HeroArtifact artifact;
    readField(Fields::kType, artifact.type);
    readField(Fields::kSpellType, artifact.spell_type);
    return artifact;
  }

  template<>
  h3svg::HeroArtifacts JsonReader2<h3svg::HeroArtifacts>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::HeroArtifacts>;
    h3svg::HeroArtifacts artifacts;
    readField(Fields::kEquipped, artifacts.equipped);
    readField(Fields::kBackpack, artifacts.backpack);
    readField(Fields::kUnknown, artifacts.unknown);
    readField(Fields::kLocks, artifacts.locks);
    return artifacts;
  }
}
