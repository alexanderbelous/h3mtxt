#pragma once

#include <h3mtxt/H3Reader/H3ReaderBase/H3ReaderBase.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>

#include <cstddef>

namespace h3m
{
  // API for reading various structures from an *UNCOMPRESSED* .h3m file.
  //
  // Like H3ReaderBase, this class doesn't maintain any internal buffer; for example,
  //     const h3m::Tile tile1 = h3m::H3MReader{my_stream}.readTile();
  //     const h3m::Tile tile2 = h3m::H3MReader{my_stream}.readTile();
  // is equivalent to
  //     const h3m::H3MReader reader {my_stream};
  //     const h3m::Tile tile1 = reader.readTile();
  //     const h3m::Tile tile2 = reader.readTile();
  class H3MReader : public H3ReaderBase
  {
  public:
    // Constructs a H3MReader that will read bytes from the specified istream.
    // \param stream - istream to read bytes from.
    explicit constexpr H3MReader(std::istream& stream) noexcept :
      H3ReaderBase{ stream }
    {}

    Coordinates readCoordinates() const;

    CustomHero readCustomHero() const;

    CreatureStack readCreatureStack() const;

    Guardians readGuardians() const;

    HeroArtifacts readHeroArtifacts() const;

    HeroSettings readHeroSettings() const;

    LossCondition readLossCondition() const;

    MainTown readMainTown() const;

    Map readMap() const;

    MapAdditionalInfo readMapAdditionalInfo() const;

    MapBasicInfo readMapBasicInfo() const;

    MessageAndTreasure readMessageAndTreasure() const;

    ObjectTemplate readObjectTemplate() const;

    // Reads a single Object entry from the stream.
    // \param objects_templates - pointer to the 0th ObjectTemplate.
    //        I'd very much prefer to pass it via std::span, but std::span currently
    //        doesn't allow incomplete types.
    // \param num_objects_templates - the number of elements in @objects_templates array.
    // \return the parsed Object.
    Object readObject(const ObjectTemplate* objects_templates, std::size_t num_objects_templates) const;

    template<ObjectPropertiesType T>
    ObjectProperties<T> readObjectProperties() const;

    PlayerSpecs readPlayerSpecs() const;

    PrimarySkills readPrimarySkills() const;

    Quest readQuest() const;

    template<QuestType T>
    QuestDetails<T> readQuestDetails() const;

    Resources readResources() const;

    Reward readReward() const;

    template<RewardType T>
    RewardDetails<T> readRewardDetails() const;

    Rumor readRumor() const;

    SecondarySkill readSecondarySkill() const;

    SpecialVictoryConditionBase readSpecialVictoryConditionBase() const;

    SpriteTilesBitmask readSpriteTilesBitmask() const;

    StartingHero readStartingHero() const;

    Teams readTeams() const;

    Tile readTile() const;

    TimedEvent readTimedEvent() const;

    TownEvent readTownEvent() const;

    VictoryCondition readVictoryCondition() const;

    template<VictoryConditionType T>
    VictoryConditionDetails<T> readVictoryConditionDetails() const;

  private:
    void readEventBase(EventBase& event) const;
  };

  template<ObjectPropertiesType T>
  ObjectProperties<T> H3MReader::readObjectProperties() const
  {
    static_assert(false, "Invalid ObjectPropertiesType.");
    return {};
  }

  template<> ObjectProperties<ObjectPropertiesType::ABANDONED_MINE> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::ARTIFACT> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::EVENT> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::GARRISON> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::NONE> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::GRAIL> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::HERO> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::MONSTER> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::QUEST_GUARD> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::RESOURCE> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::SCHOLAR> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::SEERS_HUT> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::SHRINE> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::SIGN> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::SPELL_SCROLL> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::TOWN> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT> H3MReader::readObjectProperties() const;

  template<> ObjectProperties<ObjectPropertiesType::WITCH_HUT> H3MReader::readObjectProperties() const;

  template<QuestType T>
  QuestDetails<T> H3MReader::readQuestDetails() const
  {
    static_assert(false, "Invalid QuestType.");
    return {};
  }

  template<> QuestDetails<QuestType::None> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Level> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::PrimarySkills> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatHero> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatMonster> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Artifacts> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Creatures> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Resources> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BeHero> H3MReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BePlayer> H3MReader::readQuestDetails() const;

  template<RewardType T>
  RewardDetails<T> H3MReader::readRewardDetails() const
  {
    static_assert(false, "Invalid RewardType.");
    return {};
  }

  template<> RewardDetails<RewardType::None> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Experience> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SpellPoints> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Morale> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Luck> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Resource> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::PrimarySkill> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SecondarySkill> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Artifact> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Spell> H3MReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Creature> H3MReader::readRewardDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AcquireArtifact> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateResources> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::UpgradeTown> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::BuildGrail> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatHero> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::CaptureTown> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatMonster> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagDwellings> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagMines> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::TransportArtifact> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> H3MReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::Normal> H3MReader::readVictoryConditionDetails() const;
}
