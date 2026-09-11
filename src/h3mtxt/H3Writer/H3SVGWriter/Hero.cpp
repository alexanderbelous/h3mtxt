#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3SVGWriter/Utils.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Hero& hero) const
  {
    writeData(hero.x);
    writeData(hero.y);
    writeData(hero.z);
    writeData(hero.is_visible);
    writeData(hero.coordinates_packed);
    writeData(hero.object_class_under);
    writeData(hero.unknown1);
    writeData(hero.is_female);
    writeData(hero.use_custom_biography);
    writeString32(hero.biography);
    writeData(hero.owner);
    writeData(hero.patrol_radius);
    writeData(hero.temp_morale);
    writeData(hero.temp_luck);
    writeData(hero.backpack_count);
    writeData(hero.disguise_level);
    writeData(hero.fly_level);
    writeData(hero.water_walk_level);
    writeData(hero.num_dimension_door_casts);
    writeData(hero.visions_level);
    writeData(hero.type);
    writeData(hero.hero_class);
    writeData(hero.portrait);
    writeData(hero.patrol_x);
    writeData(hero.patrol_y);
    writeData(hero.unknown2);
    writeData(hero.destination_x);
    writeData(hero.destination_y);
    writeData(hero.destination_z);
    writeData(hero.unknown3);
    writeData(hero.move_points_max);
    writeData(hero.move_points);
    writeData(hero.experience);
    writeData(hero.unknown4);
    writeData(hero.spell_points);
    writeData(hero.level);
    writeData(hero.unknown5);
    writeData(hero.learning_stones);
    writeData(hero.marletto_towers);
    writeData(hero.gardens_of_revelation);
    writeData(hero.mercenary_camps);
    writeData(hero.star_axes);
    writeData(hero.trees_of_knowledge);
    writeData(hero.libraries_of_enlightenment);
    writeData(hero.arenas);
    writeData(hero.schools_of_magic);
    writeData(hero.schools_of_war);
    writeData(hero.reserved);
    writeData(hero.flags);
    writeData(hero.army);
    writeData(hero.name);
    writeData(hero.secondary_skills_levels);
    writeData(hero.secondary_skills_slots);
    writeData(hero.primary_skills);
    writeData(hero.spells_learned);
    writeData(hero.spells_available);
    writeData(hero.artifacts);
    writeData(hero.is_sleeping);
    writeData(hero.visited_towns);
  }

  void H3SVGWriter::writeData(const HeroArtifact& artifact) const
  {
    writeData(artifact.type);
    writeData(artifact.spell_type);
  }

  void H3SVGWriter::writeData(const HeroArtifacts& artifacts) const
  {
    writeData(artifacts.equipped);
    writeData(artifacts.backpack);
    writeData(artifacts.unknown);
    writeData(artifacts.locks);
  }
}
