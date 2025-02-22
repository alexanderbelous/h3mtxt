#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Campaign/StartingBonus.h>

namespace h3m::H3Writer_NS
{
  namespace
  {
    template<StartingBonusType T>
    void writeStartingBonusDetails(std::ostream& stream, const StartingBonusDetails<T>& details);

    template<>
    void writeStartingBonusDetails<StartingBonusType::Spell>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::Spell>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.spell);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::Creature>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::Creature>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.creature_stack);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::Building>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::Building>& details)
    {
      writeData(stream, details.building);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::Artifact>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::Artifact>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.artifact);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::SpellScroll>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::SpellScroll>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.spell);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::PrimarySkills>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::PrimarySkills>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.skills);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::SecondarySkill>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::SecondarySkill>& details)
    {
      writeData(stream, details.hero);
      writeData(stream, details.skill);
    }

    template<>
    void writeStartingBonusDetails<StartingBonusType::Resource>(
      std::ostream& stream, const StartingBonusDetails<StartingBonusType::Resource>& details)
    {
      writeData(stream, details.type);
      writeData(stream, details.amount);
    }
  }

  void H3Writer<StartingBonus>::operator()(std::ostream& stream, const StartingBonus& bonus) const
  {
    writeData(stream, bonus.type());
    std::visit([&stream] <StartingBonusType T> (const StartingBonusDetails<T>& details)
               { writeStartingBonusDetails<T>(stream, details); },
               bonus.details);
  }
}
