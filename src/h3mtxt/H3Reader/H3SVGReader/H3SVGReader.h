#pragma once

#include <h3mtxt/H3Reader/H3ReaderBase/H3ReaderBase.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>

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

    Boat readBoat() const;

    CampaignInfo readCampaignInfo() const;

    Coordinates readCoordinates() const;

    CoordinatesPacked readCoordinatesPacked() const;

    CreatureBank readCreatureBank() const;

    CrossoverInfo readCrossoverInfo() const;

    CustomHero readCustomHero() const;

    Date readDate() const;

    Dwelling readDwelling() const;

    EventBase readEventBase() const;

    template<std::size_t N>
    FixedLengthString<N> readFixedLengthString() const;

    Garrison readGarrison() const;

    Guardians readGuardians() const;

    Hero readHero() const;

    HeroArtifact readHeroArtifact() const;

    HeroArtifacts readHeroArtifacts() const;

    LossCondition readLossCondition() const;

    // Defined in readLossCondition.cpp.
    // Template instantiations are provided for all valid LossConditionTypes.
    template<LossConditionType T>
    LossConditionDetails<T> readLossConditionDetails() const;

    MapBasicInfo readMapBasicInfo() const;

    MineLighthouse readMine() const;

    ObjectExits readObjectExits() const;

    Monster readMonster() const;

    Obelisk readObelisk() const;

    Object readObject() const;

    ObjectPropertiesTables readObjectPropertiesTables() const;

    ObjectTemplate readObjectTemplate() const;

    Player readPlayer() const;

    PlayerSpecs readPlayerSpecs() const;

    PrimarySkills readPrimarySkills() const;

    Portals readPortals() const;

    Quest readQuest() const;

    // Defined in readQuest.cpp.
    // Template instantiations are provided for all valid QuestTypes.
    template<QuestType T>
    QuestDetails<T> readQuestDetails() const;

    QuestGuard readQuestGuard() const;

    RegionInfo readRegionInfo() const;

    ReplayEvent readReplayEvent() const;

    template<ReplayEventType T>
    ReplayEventDetails<T> readReplayEventDetails() const;

    ReplayEventDetailsBase readReplayEventDetailsBase() const;

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

    SubterraneanGates readSubterraneanGates() const;

    Teams readTeams() const;

    Tile readTile() const;

    TileRenderInfo readTileRenderInfo() const;

    TileVisibility readTileVisibility() const;

    TimedEvent readTimedEvent() const;

    Town readTown() const;

    TownEvent readTownEvent() const;

    TownUniqueBuildingsProperties readTownUniqueBuildingsProperties() const;

    Troops readTroops() const;

    University readUniversity() const;

    VictoryCondition readVictoryCondition() const;

    // Defined in readVictoryCondition.cpp.
    // Template instantiations are provided for all valid VictoryConditionTypes.
    template<VictoryConditionType T>
    VictoryConditionDetails<T> readVictoryConditionDetails() const;
  };

  template<std::size_t N>
  FixedLengthString<N> H3SVGReader::readFixedLengthString() const
  {
    FixedLengthString<N> str;
    readBytes(std::as_writable_bytes(str.buffer()));
    return str;
  }

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

  template<> RewardDetails<RewardType::Creatures> H3SVGReader::readRewardDetails() const;
}
