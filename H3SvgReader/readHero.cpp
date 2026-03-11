#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace h3svg
{
  HeroArtifact H3SvgReader::readHeroArtifact() const
  {
    HeroArtifact artifact;
    artifact.type = readEnum<ArtifactType32>();
    artifact.spell_type = readEnum<SpellType32>();
    return artifact;
  }

  HeroArtifacts H3SvgReader::readHeroArtifacts() const
  {
    HeroArtifacts artifacts;
    for (HeroArtifact& artifact : artifacts.equipped)
    {
      artifact = readHeroArtifact();
    }
    for (HeroArtifact& artifact : artifacts.backpack)
    {
      artifact = readHeroArtifact();
    }
    return artifacts;
  }

  Hero H3SvgReader::readHero() const
  {
    Hero hero;
    hero.x = readInt<std::int16_t>();
    hero.y = readInt<std::int16_t>();
    hero.z = readInt<std::int16_t>();
    hero.is_visible = readBool();
    // TODO: use a custom class.
    hero.coordinates_packed = readInt<std::uint32_t>();
    hero.object_class_under = readEnum<ObjectClass>();
    hero.unknown1 = readByteArray<7>();
    hero.biography = readString32();
    hero.owner = readEnum<PlayerColor>();
    hero.patrol_radius = readInt<std::int8_t>();
    readBytes(std::as_writable_bytes(std::span{hero.unknown2}));
    hero.type = readEnum<HeroType>();
    hero.hero_class = readEnum<HeroClass>();
    hero.portrait = readEnum<HeroPortrait>();
    hero.patrol_x = readInt<std::uint8_t>();
    hero.patrol_y = readInt<std::uint8_t>();
    readBytes(std::as_writable_bytes(std::span{hero.unknown3}));
    hero.destination_x = readInt<std::int32_t>();
    hero.destination_y = readInt<std::int32_t>();
    readBytes(std::as_writable_bytes(std::span{hero.unknown4}));
    hero.move_points_max = readInt<std::int32_t>();
    hero.move_points = readInt<std::int32_t>();
    hero.experience = readInt<std::int32_t>();
    readBytes(std::as_writable_bytes(std::span{hero.unknown5}));
    hero.spell_points = readInt<std::int16_t>();
    hero.level = readInt<std::uint16_t>();
    readBytes(std::as_writable_bytes(std::span{hero.unknown6}));
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
    readBytes(std::as_writable_bytes(std::span{hero.unknown7}));
    return hero;
  }
}
