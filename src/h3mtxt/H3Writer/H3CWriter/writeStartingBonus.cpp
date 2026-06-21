#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Campaign/StartingBonus.h>

namespace h3m
{
  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Spell>& details) const
  {
    writeData(details.hero);
    writeData(details.spell);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Creature>& details) const
  {
    writeData(details.hero);
    H3MWriter{ stream_ }.writeData(details.creature_stack);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Building>& details) const
  {
    writeData(details.building);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Artifact>& details) const
  {
    writeData(details.hero);
    writeData(details.artifact);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::SpellScroll>& details) const
  {
    writeData(details.hero);
    writeData(details.spell);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::PrimarySkills>& details) const
  {
    writeData(details.hero);
    H3MWriter{ stream_ }.writeData(details.skills);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::SecondarySkill>& details) const
  {
    writeData(details.hero);
    H3MWriter{ stream_ }.writeData(details.skill);
  }

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Resource>& details) const
  {
    const TypedQuantity<StartingBonusResourceType, std::int32_t>& resources = details;
    writeData(resources);
  }

  void H3CWriter::writeData(const StartingBonus& bonus) const
  {
    writeData(bonus.type());
    std::visit([this] <StartingBonusType T> (const StartingBonusDetails<T>& details)
               { writeData(details); },
               bonus.details);
  }
}
