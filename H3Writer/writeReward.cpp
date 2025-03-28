#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/Reward.h>

namespace h3m::H3Writer_NS
{
  template<>
  struct H3Writer<RewardDetails<RewardType::None>>
  {
    void operator()(std::ostream&, const RewardDetails<RewardType::None>&) const
    {
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Experience>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Experience>& data) const
    {
      writeData(stream, data.experience);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::SpellPoints>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::SpellPoints>& data) const
    {
      writeData(stream, data.spell_points);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Morale>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Morale>& data) const
    {
      writeData(stream, data.morale);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Luck>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Luck>& data) const
    {
      writeData(stream, data.luck);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Resource>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Resource>& data) const
    {
      writeData(stream, data.type);
      writeData(stream, data.amount);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::PrimarySkill>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::PrimarySkill>& data) const
    {
      writeData(stream, data.type);
      writeData(stream, data.value);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::SecondarySkill>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::SecondarySkill>& data) const
    {
      writeData<SecondarySkill>(stream, data);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Artifact>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Artifact>& data) const
    {
      writeData(stream, data.artifact);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Spell>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Spell>& data) const
    {
      writeData(stream, data.spell);
    }
  };

  template<>
  struct H3Writer<RewardDetails<RewardType::Creature>>
  {
    void operator()(std::ostream& stream, const RewardDetails<RewardType::Creature>& data) const
    {
      writeData<CreatureStack>(stream, data);
    }
  };

  void H3Writer<Reward>::operator()(std::ostream& stream, const Reward& reward) const
  {
    writeData(stream, reward.type());
    std::visit([&stream] <RewardType T> (const RewardDetails<T>& value) { writeData(stream, value); },
               reward.details);
  }
}
