#pragma once

#include <h3mtxt/H3SvgReader/H3ReaderBase.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  // API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
  //
  // FYI: originally, the functions in this class were declared as global functions. However, making
  // them member functions of a class has a few advantages:
  // 1) It reduces the risk of calling a "wrong" function, i.e. one intended for .h3m files.
  // 2) It doesn't pollute the namespace.
  // 3) It allows omitting the stream parameter.
  class H3SvgReader : public h3m::H3ReaderBase
  {
  public:
    // Inherit the constructor from H3ReaderBase.
    using H3ReaderBase::H3ReaderBase;

    Artifact readArtifact() const;

    BlackMarket readBlackMarket() const;

    Boat readBoat() const;

    Dwelling readDwelling() const;

    EventBase readEventBase() const;

    Garrison readGarrison() const;

    Guardians readGuardians() const;

    Hero readHero() const;

    HeroArtifact readHeroArtifact() const;

    HeroArtifacts readHeroArtifacts() const;

    MapBasicInfo readMapBasicInfo() const;

    Mine readMine() const;

    Monster readMonster() const;

    Obelisk readObelisk() const;

    Object readObject() const;

    ObjectPropertiesTables readObjectPropertiesTables() const;

    ObjectTemplate readObjectTemplate() const;

    Player readPlayer() const;

    PlayerSpecs readPlayerSpecs() const;

    Quest readQuest() const;

    template<QuestType T>
    QuestDetails<T> readQuestDetails() const;

    QuestGuard readQuestGuard() const;

    Reward readReward() const;

    template<RewardType T>
    RewardDetails<T> readRewardDetails() const;

    Rumor readRumor() const;

    SavedGame readSavedGame() const;

    ScenarioStartingInfo readScenarioStartingInfo() const;

    SeersHut readSeersHut() const;

    Sign readSign() const;

    StartingHero readStartingHero() const;

    Tile readTile() const;

    TimedEvent readTimedEvent() const;

    TownEvent readTownEvent() const;

    Town readTown() const;

    Troops readTroops() const;
  };

  template<QuestType T>
  QuestDetails<T> H3SvgReader::readQuestDetails() const
  {
    static_assert(false, "Missing specialization for readQuestDetails<T>().");
  }

  template<> QuestDetails<QuestType::None> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Level> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::PrimarySkills> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatHero> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::DefeatMonster> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Artifacts> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Creatures> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::Resources> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BeHero> H3SvgReader::readQuestDetails() const;

  template<> QuestDetails<QuestType::BePlayer> H3SvgReader::readQuestDetails() const;

  template<RewardType T>
  RewardDetails<T> H3SvgReader::readRewardDetails() const
  {
    static_assert(false, "Invalid RewardType.");
  }

  template<> RewardDetails<RewardType::None> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Experience> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SpellPoints> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Morale> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Luck> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Resource> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::PrimarySkill> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::SecondarySkill> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Artifact> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Spell> H3SvgReader::readRewardDetails() const;

  template<> RewardDetails<RewardType::Creature> H3SvgReader::readRewardDetails() const;
}
