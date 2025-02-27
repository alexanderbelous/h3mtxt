#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <cstddef>
#include <iosfwd>

// API for reading various H3 structures from an *UNCOMPRESSED* .h3m/.h3c file.
namespace h3m::H3Reader_NS
{
  CampaignHeader readCampaignHeader(std::istream& stream);

  CrossoverOptions readCrossoverOptions(std::istream& stream);

  CutScene readCutScene(std::istream& stream);

  CampaignScenario readCampaignScenario(std::istream& stream, CampaignId campaign_id);

  CreatureStack readCreatureStack(std::istream& stream);

  GlobalEvent readGlobalEvent(std::istream& stream);

  HeroArtifacts readHeroArtifacts(std::istream& stream);

  HeroSettings readHeroSettings(std::istream& stream);

  LossCondition readLossCondition(std::istream& stream);

  MainTown readMainTown(std::istream& stream);

  Map readMap(std::istream& stream);

  MapAdditionalInfo readMapAdditionalInfo(std::istream& stream);

  MapBasicInfo readMapBasicInfo(std::istream& stream);

  ObjectTemplate readObjectTemplate(std::istream& stream);

  // Reads a single Object entry from the stream.
  // \param stream - input stream.
  // \param objects_templates - pointer to the 0th ObjectTemplate.
  //        I'd very much prefer to pass it via std::span, but std::span currently
  //        doesn't allow incomplete types.
  // \param num_objects_templates - the number of elements in @objects_templates array.
  // \return the parsed Object.
  Object readObject(std::istream& stream,
                    const ObjectTemplate* objects_templates,
                    std::size_t num_objects_templates);

  PlayerSpecs readPlayerSpecs(std::istream& stream);

  PrimarySkills readPrimarySkills(std::istream& stream);

  Quest readQuest(std::istream& stream);

  Resources readResources(std::istream& stream);

  Reward readReward(std::istream& stream);

  Rumor readRumor(std::istream& stream);

  StartingBonus readStartingBonus(std::istream& stream);

  StartingHero readStartingHero(std::istream& stream);

  StartingOptions readStartingOptions(std::istream& stream);

  SecondarySkill readSecondarySkill(std::istream& stream);

  TeamsInfo readTeamsInfo(std::istream& stream);

  Tile readTile(std::istream& stream);

  void readTimedEventBase(std::istream& stream, TimedEventBase& event);

  VictoryCondition readVictoryCondition(std::istream& stream);
}
