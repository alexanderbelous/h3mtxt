#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <iosfwd>

// API for writing various H3 structures into an *UNCOMPRESSED* .h3m/.h3c file.
namespace h3m::H3Writer_NS
{
  // Template for writing H3 values into a binary stream storing a .h3m/.h3c file.
  template<class T, class Enable = void>
  struct H3Writer
  {
    // \param stream - output stream.
    // \param value - value to append.
    void operator()(std::ostream& stream, const T& value) const;
  };

  // Utility function that writes a value into a binary stream storing a .h3m/.h3c file.
  // \param stream - output stream.
  // \param value - value to append.
  template<class T>
  void writeData(std::ostream& stream, const T& value)
  {
    const H3Writer<T> writer {};
    writer(stream, value);
  }

  template<>
  struct H3Writer<CreatureStack>
  {
    void operator()(std::ostream& stream, const CreatureStack& value) const;
  };

  template<>
  struct H3Writer<GlobalEvent>
  {
    void operator()(std::ostream& stream, const GlobalEvent& global_event) const;
  };

  template<>
  struct H3Writer<Guardians>
  {
    void operator()(std::ostream& stream, const Guardians& guardians) const;
  };

  template<>
  struct H3Writer<HeroArtifacts>
  {
    void operator()(std::ostream& stream, const HeroArtifacts& artifacts) const;
  };

  template<>
  struct H3Writer<HeroSettings>
  {
    void operator()(std::ostream& stream, const HeroSettings& settings) const;
  };

  template<>
  struct H3Writer<LossCondition>
  {
    void operator()(std::ostream& stream, const LossCondition& loss_condition) const;
  };

  template<>
  struct H3Writer<MainTown>
  {
    void operator()(std::ostream& stream, const MainTown& value) const;
  };

  template<>
  struct H3Writer<Map>
  {
    void operator()(std::ostream& stream, const Map& map) const;
  };

  template<>
  struct H3Writer<MapAdditionalInfo>
  {
    void operator()(std::ostream& stream, const MapAdditionalInfo& value) const;
  };

  template<>
  struct H3Writer<MapBasicInfo>
  {
    void operator()(std::ostream& stream, const MapBasicInfo& value) const;
  };

  template<>
  struct H3Writer<ObjectAttributes>
  {
    void operator()(std::ostream& stream, const ObjectAttributes& value) const;
  };

  template<>
  struct H3Writer<ObjectDetails>
  {
    void operator()(std::ostream& stream, const ObjectDetails& object_details) const;
  };

  template<>
  struct H3Writer<PlayerSpecs>
  {
    void operator()(std::ostream& stream, const PlayerSpecs& value) const;
  };

  template<>
  struct H3Writer<PrimarySkills>
  {
    void operator()(std::ostream& stream, const PrimarySkills& primary_skills) const;
  };

  template<>
  struct H3Writer<Quest>
  {
    void operator()(std::ostream& stream, const Quest& quest) const;
  };

  template<>
  struct H3Writer<Resources>
  {
    void operator()(std::ostream& stream, const Resources& resources) const;
  };

  template<>
  struct H3Writer<Reward>
  {
    void operator()(std::ostream& stream, const Reward& reward) const;
  };

  template<>
  struct H3Writer<Rumor>
  {
    void operator()(std::ostream& stream, const Rumor& value) const;
  };

  template<>
  struct H3Writer<SecondarySkill>
  {
    void operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const;
  };

  template<>
  struct H3Writer<StartingHero>
  {
    void operator()(std::ostream& stream, const StartingHero& value) const;
  };

  template<>
  struct H3Writer<TeamsInfo>
  {
    void operator()(std::ostream& stream, const TeamsInfo& teams) const;
  };

  template<>
  struct H3Writer<Tile>
  {
    void operator()(std::ostream& stream, const Tile& value) const;
  };

  template<>
  struct H3Writer<TownBuildings>
  {
    void operator()(std::ostream& stream, const TownBuildings& town_buildings) const;
  };

  template<>
  struct H3Writer<TownEvent>
  {
    void operator()(std::ostream& stream, const TownEvent& event) const;
  };

  template<>
  struct H3Writer<VictoryCondition>
  {
    void operator()(std::ostream& stream, const VictoryCondition& victory_condition) const;
  };

  void writeTimedEventBase(std::ostream& stream, const TimedEventBase& event);

  // Campaign:

  // Forbid writing Campaign via H3Writer.
  // .h3c is weird - it's actually a sequence of concatenated gzip streams:
  // * The first stream contains everything in h3m::Campaign except the maps
  // * Each next stream contains a single h3m::Map from Campaign::maps.
  //
  // During decompression gzip file format treats such concatenated streams
  // as if they were originally one file.
  template<>
  struct H3Writer<Campaign>
  {
    void operator()(std::ostream& stream, const Campaign& campaign) const = delete;
  };

  template<>
  void H3Writer<CrossoverOptions>::operator()(std::ostream& stream, const CrossoverOptions& options) const;

  template<>
  void H3Writer<CutScene>::operator()(std::ostream& stream, const CutScene& cutscene) const;

  template<>
  void H3Writer<StartingBonus>::operator()(std::ostream& stream, const StartingBonus& bonus) const;

  template<>
  void H3Writer<StartingOptions>::operator()(std::ostream& stream, const StartingOptions& options) const;

  void writeCampaignScenario(std::ostream& stream,
                             const CampaignScenario& scenario,
                             CampaignId campaign_id,
                             std::uint32_t compressed_map_size);
}
