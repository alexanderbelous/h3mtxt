#pragma once

#include <h3mtxt/H3Reader/H3ReaderBase/H3ReaderBase.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  // API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
  class H3SVGReader : public h3m::H3ReaderBase
  {
  public:
    // Inherit the constructor from H3ReaderBase.
    using H3ReaderBase::H3ReaderBase;

    Artifact readArtifact() const;

    ArtifactMerchants readArtifactMerchants() const;

    Coordinates readCoordinates() const;

    CreatureStack readCreatureStack() const;

    CustomHero readCustomHero() const;

    Boat readBoat() const;

    Dwelling readDwelling() const;

    EventBase readEventBase() const;

    Garrison readGarrison() const;

    Guardians readGuardians() const;

    Hero readHero() const;

    HeroArtifact readHeroArtifact() const;

    HeroArtifacts readHeroArtifacts() const;

    LossCondition readLossCondition() const;

    template<LossConditionType T>
    LossConditionDetails<T> readLossConditionDetails() const;

    MapBasicInfo readMapBasicInfo() const;

    Mine readMine() const;

    Monster readMonster() const;

    Obelisk readObelisk() const;

    Object readObject() const;

    ObjectPropertiesTables readObjectPropertiesTables() const;

    ObjectTemplate readObjectTemplate() const;

    Player readPlayer() const;

    PlayerSpecs readPlayerSpecs() const;

    PrimarySkills readPrimarySkills() const;

    Quest readQuest() const;

    template<QuestType T>
    QuestDetails<T> readQuestDetails() const;

    QuestGuard readQuestGuard() const;

    Resources readResources() const;

    Reward readReward() const;

    template<RewardType T>
    RewardDetails<T> readRewardDetails() const;

    Rumor readRumor() const;

    SavedGame readSavedGame() const;

    ScenarioStartingInfo readScenarioStartingInfo() const;

    SecondarySkill readSecondarySkill() const;

    SpriteTilesBitmask readSpriteTilesBitmask() const;

    SeersHut readSeersHut() const;

    Sign readSign() const;

    SpecialVictoryConditionBase readSpecialVictoryConditionBase() const;

    StartingHero readStartingHero() const;

    TeamsInfo readTeamsInfo() const;

    Tile readTile() const;

    TileVisibility readTileVisibility() const;

    TimedEvent readTimedEvent() const;

    TownEvent readTownEvent() const;

    Town readTown() const;

    Troops readTroops() const;

    VictoryCondition readVictoryCondition() const;

    // Defined in readVictoryCondition.cpp.
    // Explicit instantiations are provided for VictoryConditionTypes that use the default template implementation.
    // A few specializations are declared below.
    template<VictoryConditionType T>
    VictoryConditionDetails<T> readVictoryConditionDetails() const;
  };

  template<> LossConditionDetails<LossConditionType::LoseTown> H3SVGReader::readLossConditionDetails() const;

  template<> LossConditionDetails<LossConditionType::LoseHero> H3SVGReader::readLossConditionDetails() const;

  template<> LossConditionDetails<LossConditionType::TimeExpires> H3SVGReader::readLossConditionDetails() const;

  template<> LossConditionDetails<LossConditionType::Normal> H3SVGReader::readLossConditionDetails() const;

  template<QuestType T>
  QuestDetails<T> H3SVGReader::readQuestDetails() const
  {
    static_assert(false, "Missing specialization for readQuestDetails<T>().");
  }

  template<> QuestDetails<QuestType::None> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Level> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::PrimarySkills> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatHero> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatMonster> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Artifacts> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Creatures> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Resources> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BeHero> H3SVGReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BePlayer> H3SVGReader::readQuestDetails() const;

  template<RewardType T>
  RewardDetails<T> H3SVGReader::readRewardDetails() const
  {
    static_assert(false, "Invalid RewardType.");
  }

  template<> RewardDetails<RewardType::None> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Experience> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SpellPoints> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Morale> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Luck> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Resource> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::PrimarySkill> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SecondarySkill> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Artifact> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Spell> H3SVGReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Creature> H3SVGReader::readRewardDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AcquireArtifact> H3SVGReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> H3SVGReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatHero> H3SVGReader::readVictoryConditionDetails() const;
}
