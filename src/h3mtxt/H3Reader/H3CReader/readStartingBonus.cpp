#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Campaign/StartingBonus.h>

#include <stdexcept>

namespace h3m
{
  template<>
  StartingBonusDetails<StartingBonusType::Spell> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::Spell> details;
    details.hero = readInt<std::uint16_t>();
    details.spell = readEnum<SpellType>();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::Creature> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::Creature> details;
    details.hero = readInt<std::uint16_t>();
    details.creature_stack = H3MReader{ stream_ }.readCreatureStack();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::Building> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::Building> details;
    details.building = readEnum<TownBuildingType>();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::Artifact> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::Artifact> details;
    details.hero = readInt<std::uint16_t>();
    details.artifact = readEnum<ArtifactType>();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::SpellScroll> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::SpellScroll> details;
    details.hero = readInt<std::uint16_t>();
    details.spell = readEnum<SpellType>();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::PrimarySkills> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::PrimarySkills> details;
    details.hero = readInt<std::uint16_t>();
    details.skills = H3MReader{ stream_ }.readPrimarySkills();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::SecondarySkill> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::SecondarySkill> details;
    details.hero = readInt<std::uint16_t>();
    details.skill = H3MReader{ stream_ }.readSecondarySkill();
    return details;
  }

  template<>
  StartingBonusDetails<StartingBonusType::Resource> H3CReader::readStartingBonusDetails() const
  {
    StartingBonusDetails<StartingBonusType::Resource> details;
    details.type = readEnum<StartingBonusResourceType>();
    details.amount = readInt<std::uint32_t>();
    return details;
  }

  StartingBonus H3CReader::readStartingBonus() const
  {
    const StartingBonusType bonus_type = readEnum<StartingBonusType>();
    switch (bonus_type)
    {
    case StartingBonusType::Spell:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Spell>() };
    case StartingBonusType::Creature:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Creature>() };
    case StartingBonusType::Building:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Building>() };
    case StartingBonusType::Artifact:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Artifact>() };
    case StartingBonusType::SpellScroll:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::SpellScroll>() };
    case StartingBonusType::PrimarySkills:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::PrimarySkills>() };
    case StartingBonusType::SecondarySkill:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::SecondarySkill>() };
    case StartingBonusType::Resource:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Resource>() };
    default:
      throw std::runtime_error("readStartingBonus(): invalid bonus_type.");
    }
  }
}
