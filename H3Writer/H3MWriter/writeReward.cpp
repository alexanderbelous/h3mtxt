#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Reward.h>

namespace h3m
{
  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::None>&) const
  {
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Experience>& data) const
  {
    writeData(data.experience);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::SpellPoints>& data) const
  {
    writeData(data.spell_points);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Morale>& data) const
  {
    writeData(data.morale);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Luck>& data) const
  {
    writeData(data.luck);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Resource>& data) const
  {
    writeData(data.type);
    writeData(data.amount);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::PrimarySkill>& data) const
  {
    writeData(data.type);
    writeData(data.value);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::SecondarySkill>& data) const
  {
    writeData(static_cast<const SecondarySkill&>(data));
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Artifact>& data) const
  {
    writeData(data.artifact);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Spell>& data) const
  {
    writeData(data.spell);
  }

  template<>
  void H3MWriter::writeData(const RewardDetails<RewardType::Creature>& data) const
  {
    writeData(static_cast<const CreatureStack&>(data));
  }

  void H3MWriter::writeData(const Reward& reward) const
  {
    writeData(reward.type());
    std::visit([this] <RewardType T> (const RewardDetails<T>& value) { writeData(value); },
               reward.details);
  }
}
