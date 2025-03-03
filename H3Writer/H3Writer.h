#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <iosfwd>

// API for writing uncompressed H3 data.
namespace h3m::H3Writer_NS
{
  // Template for writing uncompressed H3 values into a binary stream.
  template<class T, class Enable = void>
  struct H3Writer
  {
    // \param stream - output stream.
    // \param value - value to append.
    void operator()(std::ostream& stream, const T& value) const;
  };

  // Utility function that writes an uncompressed H3 value into a binary stream.
  // \param stream - output stream.
  // \param value - value to append.
  template<class T>
  void writeData(std::ostream& stream, const T& value)
  {
    const H3Writer<T> writer {};
    writer(stream, value);
  }

  template<>
  void H3Writer<CreatureStack>::operator()(std::ostream& stream, const CreatureStack& value) const;

  template<>
  void H3Writer<GlobalEvent>::operator()(std::ostream& stream, const GlobalEvent& global_event) const;

  template<>
  void H3Writer<Guardians>::operator()(std::ostream& stream, const Guardians& guardians) const;

  template<>
  void H3Writer<HeroArtifacts>::operator()(std::ostream& stream, const HeroArtifacts& artifacts) const;

  template<>
  void H3Writer<HeroSettings>::operator()(std::ostream& stream, const HeroSettings& settings) const;

  template<>
  void H3Writer<LossCondition>::operator()(std::ostream& stream, const LossCondition& loss_condition) const;

  template<>
  void H3Writer<MainTown>::operator()(std::ostream& stream, const MainTown& value) const;

  template<>
  void H3Writer<Map>::operator()(std::ostream& stream, const Map& map) const;

  template<>
  void H3Writer<MapAdditionalInfo>::operator()(std::ostream& stream, const MapAdditionalInfo& value) const;

  template<>
  void H3Writer<MapBasicInfo>::operator()(std::ostream& stream, const MapBasicInfo& value) const;

  template<>
  void H3Writer<ObjectTemplate>::operator()(std::ostream& stream, const ObjectTemplate& value) const;

  template<>
  void H3Writer<Object>::operator()(std::ostream& stream, const Object& object) const;

  template<>
  void H3Writer<PlayerSpecs>::operator()(std::ostream& stream, const PlayerSpecs& value) const;

  template<>
  void H3Writer<PrimarySkills>::operator()(std::ostream& stream, const PrimarySkills& primary_skills) const;

  template<>
  void H3Writer<Quest>::operator()(std::ostream& stream, const Quest& quest) const;

  template<>
  void H3Writer<Resources>::operator()(std::ostream& stream, const Resources& resources) const;

  template<>
  void H3Writer<Reward>::operator()(std::ostream& stream, const Reward& reward) const;

  template<>
  void H3Writer<Rumor>::operator()(std::ostream& stream, const Rumor& value) const;

  template<>
  void H3Writer<SecondarySkill>::operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const;

  template<>
  void H3Writer<StartingHero>::operator()(std::ostream& stream, const StartingHero& value) const;

  template<>
  void H3Writer<TeamsInfo>::operator()(std::ostream& stream, const TeamsInfo& teams) const;

  template<>
  void H3Writer<Tile>::operator()(std::ostream& stream, const Tile& value) const;

  template<>
  void H3Writer<TownBuildings>::operator()(std::ostream& stream, const TownBuildings& town_buildings) const;

  template<>
  void H3Writer<TownEvent>::operator()(std::ostream& stream, const TownEvent& event) const;

  template<>
  void H3Writer<VictoryCondition>::operator()(std::ostream& stream, const VictoryCondition& victory_condition) const;

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
                             std::uint32_t map_file_size);
}
