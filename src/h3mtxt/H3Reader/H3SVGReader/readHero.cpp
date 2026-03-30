#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace h3svg
{
  HeroArtifact H3SVGReader::readHeroArtifact() const
  {
    HeroArtifact artifact;
    artifact.type = readEnum<ArtifactType32>();
    artifact.spell_type = readEnum<SpellType32>();
    return artifact;
  }

  HeroArtifacts H3SVGReader::readHeroArtifacts() const
  {
    HeroArtifacts artifacts;
    for (HeroArtifact& artifact : artifacts.equipped.data)
    {
      artifact = readHeroArtifact();
    }
    for (HeroArtifact& artifact : artifacts.backpack)
    {
      artifact = readHeroArtifact();
    }
    artifacts.unknown = readInt<std::uint8_t>();
    for (std::uint8_t& num_locks : artifacts.locks.data)
    {
      num_locks = readInt<std::uint8_t>();
    }
    return artifacts;
  }

  Hero H3SVGReader::readHero() const
  {
    Hero hero;
    hero.x = readInt<std::int16_t>();
    hero.y = readInt<std::int16_t>();
    hero.z = readInt<std::int16_t>();
    hero.is_visible = readBool();
    // TODO: use a custom class.
    hero.coordinates_packed = readInt<std::uint32_t>();
    hero.object_class_under = readEnum<ObjectClass>();
    hero.unknown1 = readByteArray<5>();
    hero.is_female = readBool();
    hero.use_custom_biography = readBool();
    hero.biography = readString32();
    hero.owner = readEnum<PlayerColor>();
    hero.patrol_radius = readInt<std::int8_t>();
    hero.temp_morale = readInt<std::int8_t>();
    hero.temp_luck = readInt<std::int8_t>();
    hero.unknown2 = readInt<std::uint8_t>();
    hero.disguise_level = readInt<std::int8_t>();
    hero.fly_level = readInt<std::int8_t>();
    hero.water_walk_level = readInt<std::int8_t>();
    hero.num_dimension_door_casts = readInt<std::uint8_t>();
    hero.visions_level = readInt<std::int8_t>();
    hero.type = readEnum<HeroType>();
    hero.hero_class = readEnum<HeroClass>();
    hero.portrait = readEnum<HeroPortrait>();
    hero.patrol_x = readInt<std::uint8_t>();
    hero.patrol_y = readInt<std::uint8_t>();
    hero.unknown3 = readByteArray<4>();
    hero.destination_x = readInt<std::int32_t>();
    hero.destination_y = readInt<std::int32_t>();
    hero.destination_z = readInt<std::int8_t>();
    hero.unknown4 = readByteArray<3>();
    hero.move_points_max = readInt<std::int32_t>();
    hero.move_points = readInt<std::int32_t>();
    hero.experience = readInt<std::int32_t>();
    hero.unknown5 = readByteArray<4>();
    hero.spell_points = readInt<std::int16_t>();
    hero.level = readInt<std::int16_t>();
    hero.unknown6 = readByteArray<2>();
    hero.learning_stones = readBitSet<4>();
    hero.marletto_towers = readBitSet<4>();
    hero.gardens_of_revelation = readBitSet<4>();
    hero.mercenary_camps = readBitSet<4>();
    hero.star_axes = readBitSet<4>();
    hero.trees_of_knowledge = readBitSet<4>();
    hero.libraries_of_enlightenment = readBitSet<4>();
    hero.arenas = readBitSet<4>();
    hero.schools_of_magic = readBitSet<4>();
    hero.schools_of_war = readBitSet<4>();
    hero.reserved = readReservedData<16>();
    hero.flags = readEnumBitmask<HeroFlag, 4>();
    hero.army = readTroops();
    readBytes(std::as_writable_bytes(std::span{hero.name}));
    for (std::uint8_t& level : hero.secondary_skills_levels.data)
    {
      level = readInt<std::uint8_t>();
    }
    for (std::uint8_t& slot : hero.secondary_skills_slots.data)
    {
      slot = readInt<std::uint8_t>();
    }
    hero.primary_skills = readPrimarySkills();
    for (Bool& is_spell_learned : hero.spells_learned.data)
    {
      is_spell_learned = readBool();
    }
    for (Bool& is_spell_available : hero.spells_available.data)
    {
      is_spell_available = readBool();
    }
    hero.artifacts = readHeroArtifacts();
    hero.is_sleeping = readBool();
    hero.unknown7 = readByteArray<6>();
    return hero;
  }
}
