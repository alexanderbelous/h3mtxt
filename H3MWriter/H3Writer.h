#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <iosfwd>

// API for writing various H3 structures into an *UNCOMPRESSED* .h3m/.h3c file.
namespace h3m
{
  // Template for writing H3 values into a binary stream storing a .h3m/.h3c file.
  template<class T, class Enable = void>
  struct H3MWriter
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
    const H3MWriter<T> writer {};
    writer(stream, value);
  }

  template<>
  struct H3MWriter<CreatureStack>
  {
    void operator()(std::ostream& stream, const CreatureStack& value) const;
  };

  template<>
  struct H3MWriter<GlobalEvent>
  {
    void operator()(std::ostream& stream, const GlobalEvent& global_event) const;
  };

  template<>
  struct H3MWriter<Guardians>
  {
    void operator()(std::ostream& stream, const Guardians& guardians) const;
  };

  template<>
  struct H3MWriter<HeroArtifacts>
  {
    void operator()(std::ostream& stream, const HeroArtifacts& artifacts) const;
  };

  template<>
  struct H3MWriter<HeroSettings>
  {
    void operator()(std::ostream& stream, const HeroSettings& settings) const;
  };

  template<>
  struct H3MWriter<LossCondition>
  {
    void operator()(std::ostream& stream, const LossCondition& loss_condition) const;
  };

  template<>
  struct H3MWriter<MainTown>
  {
    void operator()(std::ostream& stream, const MainTown& value) const;
  };

  template<>
  struct H3MWriter<Map>
  {
    void operator()(std::ostream& stream, const Map& map) const;
  };

  template<>
  struct H3MWriter<MapAdditionalInfo>
  {
    void operator()(std::ostream& stream, const MapAdditionalInfo& value) const;
  };

  template<>
  struct H3MWriter<MapBasicInfo>
  {
    void operator()(std::ostream& stream, const MapBasicInfo& value) const;
  };

  template<>
  struct H3MWriter<ObjectAttributes>
  {
    void operator()(std::ostream& stream, const ObjectAttributes& value) const;
  };

  template<>
  struct H3MWriter<ObjectDetails>
  {
    void operator()(std::ostream& stream, const ObjectDetails& object_details) const;
  };

  template<>
  struct H3MWriter<PlayerSpecs>
  {
    void operator()(std::ostream& stream, const PlayerSpecs& value) const;
  };

  template<>
  struct H3MWriter<PrimarySkills>
  {
    void operator()(std::ostream& stream, const PrimarySkills& primary_skills) const;
  };

  template<>
  struct H3MWriter<Quest>
  {
    void operator()(std::ostream& stream, const Quest& quest) const;
  };

  template<>
  struct H3MWriter<Resources>
  {
    void operator()(std::ostream& stream, const Resources& resources) const;
  };

  template<>
  struct H3MWriter<Reward>
  {
    void operator()(std::ostream& stream, const Reward& reward) const;
  };

  template<>
  struct H3MWriter<Rumor>
  {
    void operator()(std::ostream& stream, const Rumor& value) const;
  };

  template<>
  struct H3MWriter<SecondarySkill>
  {
    void operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const;
  };

  template<>
  struct H3MWriter<StartingHero>
  {
    void operator()(std::ostream& stream, const StartingHero& value) const;
  };

  template<>
  struct H3MWriter<TeamsInfo>
  {
    void operator()(std::ostream& stream, const TeamsInfo& teams) const;
  };

  template<>
  struct H3MWriter<Tile>
  {
    void operator()(std::ostream& stream, const Tile& value) const;
  };

  template<>
  struct H3MWriter<TownBuildings>
  {
    void operator()(std::ostream& stream, const TownBuildings& town_buildings) const;
  };

  template<>
  struct H3MWriter<TownEvent>
  {
    void operator()(std::ostream& stream, const TownEvent& event) const;
  };

  template<>
  struct H3MWriter<VictoryCondition>
  {
    void operator()(std::ostream& stream, const VictoryCondition& victory_condition) const;
  };

  void writeTimedEventBase(std::ostream& stream, const TimedEventBase& event);
}
