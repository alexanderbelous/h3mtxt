#pragma once

#include <h3mtxt/H3Writer/H3WriterBase/H3WriterBase.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/QuestType.h>

#include <optional>
#include <string>

namespace h3m
{
  // API for writing various structures into an *UNCOMPRESSED* .h3m file.
  class H3MWriter : public h3mtxt::H3WriterBase
  {
  public:
    // Constructs H3MWriter that will append data to the specified stream.
    // \param stream - stream to append data to.
    explicit constexpr H3MWriter(std::ostream& stream) noexcept:
      H3WriterBase{stream}
    {}

    // Reintroduce writeData() from the base class, so that the new overloads in H3MWriter don't hide it.
    using H3WriterBase::writeData;

    void writeData(const Coordinates& value) const;

    void writeData(const CreatureStack& value) const;

    void writeData(const CustomHero& value) const;

    void writeData(const Guardians& guardians) const;

    void writeData(const HeroArtifacts& value) const;

    void writeData(const HeroSettings& settings) const;

    void writeData(const LossCondition& loss_condition) const;

    template<LossConditionType T>
    void writeData(const LossConditionDetails<T>& details) const;

    void writeData(const MainTown& value) const;

    void writeData(const Map& map) const;

    void writeData(const MapAdditionalInfo& value) const;

    void writeData(const MapBasicInfo& value) const;

    void writeData(const MessageAndTreasure& value) const;

    void writeData(const ObjectTemplate& value) const;

    void writeData(const Object& object) const;

    template<ObjectPropertiesType T>
    void writeData(const ObjectProperties<T>& properties) const;

    void writeData(const PlayerSpecs& value) const;

    void writeData(const Quest& quest) const;

    template<QuestType T>
    void writeData(const QuestDetails<T>& details) const;

    void writeData(const Reward& reward) const;

    template<RewardType T>
    void writeData(const RewardDetails<T>& details) const;

    void writeData(const Rumor& value) const;

    void writeData(const SecondarySkill& secondary_skill) const;

    void writeData(const SpriteTilesBitmask& value) const;

    void writeData(const StartingHero& value) const;

    void writeData(const Teams& teams) const;

    void writeData(const Tile& value) const;

    void writeData(const TimedEvent& event) const;

    void writeData(const TownBuildings& town_buildings) const;

    void writeData(const TownEvent& event) const;

    void writeData(const VictoryCondition& victory_condition) const;

    // In H3M strings are always written as length-prefixed strings with length being serialized as
    // a 32-bit integer, so we can just overload writeData() for std::string.
    void writeData(const std::string& value) const;

    // Appends an array of elements to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    //
    // The function does NOT write the length of the array to the binary stream - it is the
    // responsibility of the user to do that (if needed at all).
    template<class T>
    void writeSpan(std::span<const T> values) const;

    // Appends a fixed-size array to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    template<class T, std::size_t N>
    void writeData(const std::array<T, N>& value) const;

    // Appends an h3m::EnumIndexedArray to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    template<class Enum, class T, std::size_t NumElements>
    void writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const;

    // Appends std::optional to the binary stream.
    template<class T>
    void writeData(const std::optional<T>& value) const;

  private:
    void writeEventBase(const EventBase& event) const;
  };

  template<> void H3MWriter::writeData(const LossConditionDetails<LossConditionType::LoseTown>& details) const;

  template<> void H3MWriter::writeData(const LossConditionDetails<LossConditionType::LoseHero>& details) const;

  template<> void H3MWriter::writeData(const LossConditionDetails<LossConditionType::TimeExpires>& details) const;

  template<> void H3MWriter::writeData(const LossConditionDetails<LossConditionType::Normal>& details) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::ARTIFACT>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::EVENT>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::GARRISON>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::NONE>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::GRAIL>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::HERO>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::MONSTER>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::QUEST_GUARD>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RESOURCE>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SCHOLAR>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SEERS_HUT>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SHRINE>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SIGN>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::TOWN>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>& properties) const;

  template<> void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::WITCH_HUT>& properties) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::None>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::Level>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::PrimarySkills>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::DefeatHero>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::DefeatMonster>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::Artifacts>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::Creatures>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::Resources>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::BeHero>& details) const;

  template<> void H3MWriter::writeData(const QuestDetails<QuestType::BePlayer>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::None>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Experience>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::SpellPoints>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Morale>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Luck>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Resource>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::PrimarySkill>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::SecondarySkill>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Artifact>& details) const;

  template<> void H3MWriter::writeData(const RewardDetails<RewardType::Creature>& details) const;

  template<class T>
  void H3MWriter::writeSpan(std::span<const T> values) const
  {
    if constexpr ((std::is_integral_v<std::remove_cvref_t<T>> && !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                  std::is_enum_v<std::remove_cvref_t<T>>)
    {
      H3WriterBase::writeSpan(values);
    }
    else
    {
      for (const T& element : values)
      {
        writeData(element);
      }
    }
  }

  template<class T, std::size_t N>
  void H3MWriter::writeData(const std::array<T, N>& value) const
  {
    writeSpan(std::span<const T>{value});
  }

  template<class Enum, class T, std::size_t NumElements>
  void H3MWriter::writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const
  {
    writeData(enum_indexed_array.data);
  }

  template<class T>
  void H3MWriter::writeData(const std::optional<T>& value) const
  {
    writeData(static_cast<Bool>(value.has_value()));
    if (value.has_value())
    {
      writeData(*value);
    }
  }
}
