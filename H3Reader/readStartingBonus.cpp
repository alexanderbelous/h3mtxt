#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Campaign/StartingBonus.h>

#include <stdexcept>

namespace h3m::H3Reader_NS
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
    readStartingBonusDetails<StartingBonusType::Building>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Building> details;
      details.building = readEnum<TownBuildingType>(stream);
      return details;
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
      details.type = readEnum<StartingBonusResourceType>(stream);
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
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Spell>(stream) };
    case StartingBonusType::Creature:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Creature>(stream) };
    case StartingBonusType::Building:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Building>(stream) };
    case StartingBonusType::Artifact:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Artifact>(stream) };
    case StartingBonusType::SpellScroll:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::SpellScroll>(stream) };
    case StartingBonusType::PrimarySkills:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::PrimarySkills>(stream) };
    case StartingBonusType::SecondarySkill:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::SecondarySkill>(stream) };
    case StartingBonusType::Resource:
      return StartingBonus{ readStartingBonusDetails<StartingBonusType::Resource>(stream) };
    default:
      throw std::runtime_error("readStartingBonus(): invalid bonus_type.");
    }
  }
}
