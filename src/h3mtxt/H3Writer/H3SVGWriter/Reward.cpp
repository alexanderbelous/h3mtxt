#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Reward.h>

namespace h3svg
{
  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::None>& details) const
  {
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Experience>& details) const
  {
    writeData(details.experience);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::SpellPoints>& details) const
  {
    writeData(details.spell_points);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Morale>& details) const
  {
    writeData(details.morale);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Luck>& details) const
  {
    writeData(details.luck);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Resource>& details) const
  {
    writeData(details.resource);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::PrimarySkill>& details) const
  {
    writeData(details.type);
    writeData(details.value);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::SecondarySkill>& details) const
  {
    writeData(details.type);
    writeData(details.level);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Artifact>& details) const
  {
    writeData(details.artifact);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Spell>& details) const
  {
    writeData(details.spell);
    writeData(details.reserved);
  }

  template<>
  void H3SVGWriter::writeData(const RewardDetails<RewardType::Creatures>& details) const
  {
    writeData(details.creatures);
  }

  void H3SVGWriter::writeData(const Reward& reward) const
  {
    writeData(reward.type());
    std::visit([this] <RewardType T> (const RewardDetails<T>& details)
               { writeData(details); },
               reward.details);
  }
}
