#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::CoordinatesPacked>::operator()(FieldsWriter& out,
                                                              const h3svg::CoordinatesPacked& coordinates) const
  {
    using Fields = h3json::FieldNames<h3svg::CoordinatesPacked>;
    out.writeField(Fields::kX, coordinates.x);
    out.writeField(Fields::kY, coordinates.y);
    out.writeField(Fields::kZ, coordinates.z);
    out.writeField(Fields::kPadding1, coordinates.padding1);
    out.writeField(Fields::kPadding2, coordinates.padding2);
  }

  void JsonObjectWriter<h3svg::HeroArtifact>::operator()(FieldsWriter& out, const h3svg::HeroArtifact& artifact) const
  {
    out.writeField("type", artifact.type);
    out.writeField("spell_type", static_cast<std::underlying_type_t<h3svg::SpellType32>>(artifact.spell_type));
    if (artifact.type == static_cast<h3svg::ArtifactType32>(h3m::ArtifactType::SpellScroll))
    {
      out.writeComment(EnumCommentGetter{}(artifact.spell_type), false);
    }
  }

  void JsonObjectWriter<h3svg::HeroArtifacts>::operator()(FieldsWriter& out,
                                                          const h3svg::HeroArtifacts& artifacts) const
  {
    using Fields = h3json::FieldNames<h3svg::HeroArtifacts>;

    out.writeField(Fields::kEquipped, artifacts.equipped);
    out.writeField(Fields::kBackpack, artifacts.backpack);
    out.writeField(Fields::kUnknown, artifacts.unknown);
    out.writeField(Fields::kLocks, artifacts.locks);
  }

  void JsonObjectWriter<h3svg::Hero>::operator()(FieldsWriter& out, const h3svg::Hero& hero) const
  {
    using Fields = h3json::FieldNames<h3svg::Hero>;

    out.writeField(Fields::kX, hero.x);
    out.writeField(Fields::kY, hero.y);
    out.writeField(Fields::kZ, hero.z);
    out.writeField(Fields::kIsVisible, hero.is_visible);
    out.writeField(Fields::kCoordinatesPacked, hero.coordinates_packed);
    out.writeField(Fields::kObjectClassUnder, hero.object_class_under);
    out.writeField(Fields::kUnknown1, hero.unknown1);
    out.writeField(Fields::kIsFemale, hero.is_female);
    out.writeField(Fields::kUseCustomBiography, hero.use_custom_biography);
    out.writeField(Fields::kBiography, hero.biography);
    out.writeField(Fields::kOwner, hero.owner);
    out.writeField(Fields::kPatrolRadius, hero.patrol_radius);
    out.writeField(Fields::kTempMorale, hero.temp_morale);
    out.writeField(Fields::kTempLuck, hero.temp_luck);
    out.writeField(Fields::kBackpackCount, hero.backpack_count);
    out.writeField(Fields::kDisguiseLevel, hero.disguise_level);
    out.writeField(Fields::kFlyLevel, hero.fly_level);
    out.writeField(Fields::kWaterWalkLevel, hero.water_walk_level);
    out.writeField(Fields::kNumDimensionDoorCasts, hero.num_dimension_door_casts);
    out.writeField(Fields::kVisionsLevel, hero.visions_level);
    out.writeField(Fields::kType, hero.type);
    out.writeField(Fields::kHeroClass, hero.hero_class);
    out.writeField(Fields::kPortrait, hero.portrait);
    out.writeField(Fields::kPatrolX, hero.patrol_x);
    out.writeField(Fields::kPatrolY, hero.patrol_y);
    out.writeField(Fields::kUnknown2, hero.unknown2);
    out.writeField(Fields::kDestinationX, hero.destination_x);
    out.writeField(Fields::kDestinationY, hero.destination_y);
    out.writeField(Fields::kDestinationZ, hero.destination_z);
    out.writeField(Fields::kUnknown3, hero.unknown3);
    out.writeField(Fields::kMovePointsMax, hero.move_points_max);
    out.writeField(Fields::kMovePoints, hero.move_points);
    out.writeField(Fields::kExperience, hero.experience);
    out.writeField(Fields::kUnknown4, hero.unknown4);
    out.writeField(Fields::kSpellPoints, hero.spell_points);
    out.writeField(Fields::kLevel, hero.level);
    out.writeField(Fields::kUnknown5, hero.unknown5);
    out.writeField(Fields::kLearningStones, hero.learning_stones);
    out.writeField(Fields::kMarlettoTowers, hero.marletto_towers);
    out.writeField(Fields::kGardensOfRevelation, hero.gardens_of_revelation);
    out.writeField(Fields::kMercenaryCamps, hero.mercenary_camps);
    out.writeField(Fields::kStarAxes, hero.star_axes);
    out.writeField(Fields::kTreesOfKnowledge, hero.trees_of_knowledge);
    out.writeField(Fields::kLibrariesOfEnlightenment, hero.libraries_of_enlightenment);
    out.writeField(Fields::kArenas, hero.arenas);
    out.writeField(Fields::kSchoolsOfMagic, hero.schools_of_magic);
    out.writeField(Fields::kSchoolsOfWar, hero.schools_of_war);
    out.writeField(Fields::kReserved, hero.reserved);
    out.writeField(Fields::kFlags, hero.flags);
    out.writeField(Fields::kArmy, hero.army);
    out.writeField(Fields::kName, hero.name);
    out.writeField(Fields::kSecondarySkillsLevels, hero.secondary_skills_levels);
    out.writeField(Fields::kSecondarySkillsSlots, hero.secondary_skills_slots);
    out.writeField(Fields::kPrimarySkills, hero.primary_skills);
    out.writeField(Fields::kSpellsLearned, hero.spells_learned);
    out.writeField(Fields::kSpellsAvailable, hero.spells_available);
    out.writeField(Fields::kArtifacts, hero.artifacts);
    out.writeField(Fields::kIsSleeping, hero.is_sleeping);
    out.writeField(Fields::kVisitedTowns, hero.visited_towns);
  }
}
