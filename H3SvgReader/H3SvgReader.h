#pragma once

#include <h3mtxt/H3SvgReader/H3ReaderBase.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3m
{
  // API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
  //
  // FYI: originally, the functions in this class were declared as global functions. However, making
  // them member functions of a class has a few advantages:
  // 1) It reduces the risk of calling a "wrong" function, i.e. one intended for .h3m files.
  // 2) It doesn't pollute the namespace.
  // 3) It allows omitting the stream parameter.
  class H3SvgReader : public H3ReaderBase
  {
  public:
    // Inherit the constructor from H3ReaderBase.
    using H3ReaderBase::H3ReaderBase;

    ArtifactSvg readArtifact() const;

    BlackMarket readBlackMarket() const;

    BoatSvg readBoat() const;

    DwellingSvg readDwelling() const;

    EventBaseSvg readEventBase() const;

    GarrisonSvg readGarrison() const;

    GuardiansSvg readGuardians() const;

    MapBasicInfo readMapBasicInfo() const;

    MineSvg readMine() const;

    MonsterSvg readMonster() const;

    ObeliskSvg readObelisk() const;

    ObjectSvg readObject() const;

    ObjectPropertiesTables readObjectPropertiesTables() const;

    ObjectTemplateSvg readObjectTemplate() const;

    PlayerSvg readPlayer() const;

    PlayerSpecsSvg readPlayerSpecs() const;

    QuestSvg readQuest() const;

    template<QuestType T>
    QuestDetailsSvg<T> readQuestDetails() const;

    QuestGuardSvg readQuestGuard() const;

    RewardSvg readReward() const;

    template<RewardType T>
    RewardDetailsSvg<T> readRewardDetails() const;

    RumorSvg readRumor() const;

    SavedGame readSavedGame() const;

    ScenarioStartingInfo readScenarioStartingInfo() const;

    SeersHutSvg readSeersHut() const;

    SignSvg readSign() const;

    StartingHero readStartingHero() const;

    TileSvg readTile() const;

    TimedEventSvg readTimedEvent() const;

    TownEventSvg readTownEvent() const;

    TownSvg readTown() const;

    TroopsSvg readTroops() const;
  };

  template<QuestType T>
  QuestDetailsSvg<T> H3SvgReader::readQuestDetails() const
  {
    static_assert(false, "Missing specialization for readQuestDetails<T>().");
  }

  template<> QuestDetailsSvg<QuestType::None> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::Level> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::PrimarySkills> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::DefeatHero> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::DefeatMonster> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::Artifacts> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::Creatures> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::Resources> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::BeHero> H3SvgReader::readQuestDetails() const;

  template<> QuestDetailsSvg<QuestType::BePlayer> H3SvgReader::readQuestDetails() const;

  template<RewardType T>
  RewardDetailsSvg<T> H3SvgReader::readRewardDetails() const
  {
    static_assert(false, "Invalid RewardType.");
  }

  template<> RewardDetailsSvg<RewardType::None> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Experience> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::SpellPoints> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Morale> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Luck> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Resource> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::PrimarySkill> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::SecondarySkill> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Artifact> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Spell> H3SvgReader::readRewardDetails() const;

  template<> RewardDetailsSvg<RewardType::Creature> H3SvgReader::readRewardDetails() const;
}
