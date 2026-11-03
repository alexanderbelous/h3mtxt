#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

// API for deserializing H3SVG data from JSON.
namespace h3json
{
  template<>
  h3svg::Artifact JsonReader2<h3svg::Artifact>::operator()() const;

  template<>
  h3svg::ArtifactMerchants JsonReader2<h3svg::ArtifactMerchants>::operator()() const;

  template<>
  h3svg::Boat JsonReader2<h3svg::Boat>::operator()() const;

  template<>
  h3svg::CampaignInfo JsonReader2<h3svg::CampaignInfo>::operator()() const;

  template<>
  h3svg::CoordinatesPacked JsonReader2<h3svg::CoordinatesPacked>::operator()() const;

  template<>
  h3svg::CreatureBank JsonReader2<h3svg::CreatureBank>::operator()() const;

  template<>
  h3svg::CrossoverInfo JsonReader2<h3svg::CrossoverInfo>::operator()() const;

  template<>
  h3svg::Date JsonReader2<h3svg::Date>::operator()() const;

  template<>
  h3svg::Dwelling JsonReader2<h3svg::Dwelling>::operator()() const;

  template<>
  h3svg::EventBase JsonReader2<h3svg::EventBase>::operator()() const;

  // Defined in FixedLengthString.h.
  template<std::size_t N>
  struct JsonReader2<h3svg::FixedLengthString<N>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    h3svg::FixedLengthString<N> operator()() const;
  };

  template<>
  h3svg::Garrison JsonReader2<h3svg::Garrison>::operator()() const;

  template<>
  h3svg::Guardians JsonReader2<h3svg::Guardians>::operator()() const;

  template<>
  h3svg::Hero JsonReader2<h3svg::Hero>::operator()() const;

  template<>
  h3svg::HeroArtifact JsonReader2<h3svg::HeroArtifact>::operator()() const;

  template<>
  h3svg::HeroArtifacts JsonReader2<h3svg::HeroArtifacts>::operator()() const;

  template<>
  h3svg::LossCondition JsonReader2<h3svg::LossCondition>::operator()() const;

  template<h3svg::LossConditionType T>
  struct JsonReader2<h3svg::LossConditionDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in LossCondition.cpp.
    // Template instantiations are provided for all valid LossConditionTypes.
    h3svg::LossConditionDetails<T> operator()() const;
  };

  template<>
  h3svg::MineLighthouse JsonReader2<h3svg::MineLighthouse>::operator()() const;

  template<>
  h3svg::Monster JsonReader2<h3svg::Monster>::operator()() const;

  template<>
  h3svg::Obelisk JsonReader2<h3svg::Obelisk>::operator()() const;

  template<>
  h3svg::Object JsonReader2<h3svg::Object>::operator()() const;

  template<>
  h3svg::ObjectExits JsonReader2<h3svg::ObjectExits>::operator()() const;

  template<h3svg::ObjectPropertiesType T>
  struct JsonReader2<h3svg::ObjectProperties<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in ObjectProperties.cpp.
    // Template instantiations are provided for all valid ObjectPropertiesTypes.
    h3svg::ObjectProperties<T> operator()() const;
  };

  template<>
  h3svg::ObjectPropertiesTables JsonReader2<h3svg::ObjectPropertiesTables>::operator()() const;

  template<>
  h3svg::ObjectPropertiesVariant JsonReader2<h3svg::ObjectPropertiesVariant>::operator()() const;

  template<>
  h3svg::ObjectTemplate JsonReader2<h3svg::ObjectTemplate>::operator()() const;

  template<>
  h3svg::Player JsonReader2<h3svg::Player>::operator()() const;

  template<>
  h3svg::PlayerSpecs JsonReader2<h3svg::PlayerSpecs>::operator()() const;

  template<>
  h3svg::Portals JsonReader2<h3svg::Portals>::operator()() const;

  template<>
  h3svg::Quest JsonReader2<h3svg::Quest>::operator()() const;

  template<h3svg::QuestType T>
  struct JsonReader2<h3svg::QuestDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in Quest.cpp.
    // Template instantiations are provided for all valid QuestTypes.
    h3svg::QuestDetails<T> operator()() const;
  };

  template<>
  h3svg::QuestGuard JsonReader2<h3svg::QuestGuard>::operator()() const;

  template<>
  h3svg::RegionInfo JsonReader2<h3svg::RegionInfo>::operator()() const;

  template<>
  h3svg::ReplayEvent JsonReader2<h3svg::ReplayEvent>::operator()() const;

  template<h3svg::ReplayEventType T>
  struct JsonReader2<h3svg::ReplayEventDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in ReplayEvent.cpp.
    // Template instantiations are provided for all valid ReplayEventTypes.
    h3svg::ReplayEventDetails<T> operator()() const;
  };

  template<>
  h3svg::ReplayEventDetailsBase JsonReader2<h3svg::ReplayEventDetailsBase>::operator()() const;

  template<>
  h3svg::Reward JsonReader2<h3svg::Reward>::operator()() const;

  template<h3svg::RewardType T>
  struct JsonReader2<h3svg::RewardDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in Reward.cpp.
    // Template instantiations are provided for all valid RewardTypes.
    h3svg::RewardDetails<T> operator()() const;
  };

  template<>
  h3svg::Rumor JsonReader2<h3svg::Rumor>::operator()() const;

  template<>
  h3svg::SavedGame JsonReader2<h3svg::SavedGame>::operator()() const;

  template<>
  h3svg::ScenarioStartingInfo JsonReader2<h3svg::ScenarioStartingInfo>::operator()() const;

  template<>
  h3svg::SeersHut JsonReader2<h3svg::SeersHut>::operator()() const;

  template<>
  h3svg::Sign JsonReader2<h3svg::Sign>::operator()() const;

  template<>
  h3svg::SubterraneanGates JsonReader2<h3svg::SubterraneanGates>::operator()() const;

  template<>
  h3svg::Tile JsonReader2<h3svg::Tile>::operator()() const;

  template<>
  h3svg::TileRenderInfo JsonReader2<h3svg::TileRenderInfo>::operator()() const;

  template<>
  h3svg::TileVisibility JsonReader2<h3svg::TileVisibility>::operator()() const;

  template<>
  h3svg::TimedEvent JsonReader2<h3svg::TimedEvent>::operator()() const;

  template<>
  h3svg::Town JsonReader2<h3svg::Town>::operator()() const;

  template<>
  h3svg::TownEvent JsonReader2<h3svg::TownEvent>::operator()() const;

  template<>
  h3svg::TownUniqueBuildingsProperties JsonReader2<h3svg::TownUniqueBuildingsProperties>::operator()() const;

  template<>
  h3svg::Troops JsonReader2<h3svg::Troops>::operator()() const;

  template<>
  h3svg::University JsonReader2<h3svg::University>::operator()() const;

  template<>
  h3svg::VictoryCondition JsonReader2<h3svg::VictoryCondition>::operator()() const;

  template<h3svg::VictoryConditionType T>
  struct JsonReader2<h3svg::VictoryConditionDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in VictoryCondition.cpp.
    // Template instantiations are provided for all valid VictoryConditionTypes.
    h3svg::VictoryConditionDetails<T> operator()() const;
  };
}
