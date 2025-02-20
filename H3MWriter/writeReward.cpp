#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/Reward.h>

namespace h3m
{
  template<>
  struct H3MWriter<RewardDetails<RewardType::None>>
  {
    void operator()(std::ostream&, const RewardDetails<RewardType::None>&) const
    {
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Experience>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Experience>& data) const
    {
      writeData(stream, data.experience);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::SpellPoints>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::SpellPoints>& data) const
    {
      writeData(stream, data.spell_points);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Morale>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Morale>& data) const
    {
      writeData(stream, data.morale);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Luck>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Luck>& data) const
    {
      writeData(stream, data.luck);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Resource>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Resource>& data) const
    {
      writeData(stream, data.type);
      writeData(stream, data.amount);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::PrimarySkill>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::PrimarySkill>& data) const
    {
      writeData(stream, data.type);
      writeData(stream, data.value);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::SecondarySkill>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::SecondarySkill>& data) const
    {
      writeData(stream, data.skill);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Artifact>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Artifact>& data) const
    {
      writeData(stream, data.artifact);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Spell>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Spell>& data) const
    {
      writeData(stream, data.spell);
    }
  };

  template<>
  struct H3MWriter<RewardDetails<RewardType::Creature>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Creature>& data) const
    {
      writeData(stream, data.type);
      writeData(stream, data.count);
    }
  };

  void H3MWriter<Reward>::operator()(std::ostream& stream, const Reward& reward) const
  {
    writeData(stream, reward.type());
    std::visit([&stream] <RewardType T> (const RewardDetails<T>& value) { writeData(stream, value); },
               reward.details);
  }
}
