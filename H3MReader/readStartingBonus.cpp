#include <h3mtxt/H3MReader/readStartingBonus.h>

#include <h3mtxt/H3MReader/readCreatureStack.h>
#include <h3mtxt/H3MReader/readPrimarySkills.h>
#include <h3mtxt/H3MReader/readSecondarySkillsVector.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    template<StartingBonusType T>
    StartingBonusDetails<T> readStartingBonusDetails(std::istream&);

    template<>
    StartingBonusDetails<StartingBonusType::Spell>
    readStartingBonusDetails<StartingBonusType::Spell>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Spell> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.spell = readEnum<SpellType>(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::Creature>
    readStartingBonusDetails<StartingBonusType::Creature>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Creature> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.creature_stack = readCreatureStack(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::Building>
    readStartingBonusDetails<StartingBonusType::Building>(std::istream&)
    {
      throw std::runtime_error("readStartingBonusDetails(): NotImplemented for Building.");
    }

    template<>
    StartingBonusDetails<StartingBonusType::Artifact>
    readStartingBonusDetails<StartingBonusType::Artifact>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Artifact> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.artifact = readEnum<ArtifactType>(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::SpellScroll>
    readStartingBonusDetails<StartingBonusType::SpellScroll>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::SpellScroll> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.spell = readEnum<SpellType>(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::PrimarySkills>
      readStartingBonusDetails<StartingBonusType::PrimarySkills>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::PrimarySkills> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.skills = readPrimarySkills(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::SecondarySkill>
      readStartingBonusDetails<StartingBonusType::SecondarySkill>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::SecondarySkill> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.skill = readSecondarySkill(stream);
      return details;
    }

    template<>
    StartingBonusDetails<StartingBonusType::Resource>
      readStartingBonusDetails<StartingBonusType::Resource>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Resource> details;
      details.type = readInt<std::uint8_t>(stream);
      details.amount = readInt<std::uint32_t>(stream);
      return details;
    }
  }

  StartingBonus readStartingBonus(std::istream& stream)
  {
    const StartingBonusType bonus_type = readEnum<StartingBonusType>(stream);
    switch (bonus_type)
    {
    case StartingBonusType::Spell:
      return readStartingBonusDetails<StartingBonusType::Spell>(stream);
    case StartingBonusType::Creature:
      return readStartingBonusDetails<StartingBonusType::Creature>(stream);
    case StartingBonusType::Building:
      return readStartingBonusDetails<StartingBonusType::Building>(stream);
    case StartingBonusType::Artifact:
      return readStartingBonusDetails<StartingBonusType::Artifact>(stream);
    case StartingBonusType::SpellScroll:
      return readStartingBonusDetails<StartingBonusType::SpellScroll>(stream);
    case StartingBonusType::PrimarySkills:
      return readStartingBonusDetails<StartingBonusType::PrimarySkills>(stream);
    case StartingBonusType::SecondarySkill:
      return readStartingBonusDetails<StartingBonusType::SecondarySkill>(stream);
    case StartingBonusType::Resource:
      return readStartingBonusDetails<StartingBonusType::Resource>(stream);
    default:
      throw std::runtime_error("readStartingBonus(): invalid bonus_type.");
    }
  }
}
