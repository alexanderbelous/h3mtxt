#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/EventBase.h>

namespace h3svg
{
  Troops H3SVGReader::readTroops() const
  {
    Troops troops;
    for (CreatureType32& creature_type : troops.creature_types)
    {
      creature_type = readEnum<CreatureType32>();
    }
    for (int32_t& count : troops.creature_counts)
    {
      count = readInt<int32_t>();
    }
    return troops;
  }

  Guardians H3SVGReader::readGuardians() const
  {
    Guardians guardians;
    guardians.message = readString16();
    if (const Bool has_creatures = readBool())
    {
      guardians.creatures = readTroops();
    }
    return guardians;
  }

  EventBase H3SVGReader::readEventBase() const
  {
    EventBase event;
    if (const Bool has_guardians = readBool())
    {
      event.guardians = readGuardians();
    }
    event.experience = readInt<int32_t>();
    event.spell_points = readInt<int32_t>();
    event.morale = readInt<std::int8_t>();
    event.luck = readInt<std::int8_t>();
    event.resources = readResources();
    event.primary_skills = readPrimarySkills();
    const std::uint8_t num_secondary_skills = readInt<std::uint8_t>();
    event.secondary_skills.reserve(num_secondary_skills);
    for (std::uint8_t i = 0; i < num_secondary_skills; ++i)
    {
      event.secondary_skills.push_back(readSecondarySkill());
    }
    const std::uint8_t num_artifacts = readInt<std::uint8_t>();
    event.artifacts.reserve(num_artifacts);
    for (std::uint8_t i = 0; i < num_artifacts; ++i)
    {
      event.artifacts.push_back(readEnum<ArtifactType8>());
    }
    const std::uint8_t num_spells = readInt<std::uint8_t>();
    event.spells.reserve(num_spells);
    for (std::uint8_t i = 0; i < num_spells; ++i)
    {
      event.spells.push_back(readEnum<SpellType>());
    }
    const std::uint8_t num_creatures = readInt<std::uint8_t>();
    event.creatures.reserve(num_creatures);
    for (std::uint8_t i = 0; i < num_creatures; ++i)
    {
      event.creatures.push_back(readCreatureStack());
    }
    return event;
  }
}
