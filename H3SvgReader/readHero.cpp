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
    readBytes(std::as_writable_bytes(std::span{hero.unknown2}));
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
    readBytes(std::as_writable_bytes(std::span{hero.unknown3}));
    hero.artifacts = readHeroArtifacts();
    readBytes(std::as_writable_bytes(std::span{hero.unknown4}));
    return hero;
  }
}
