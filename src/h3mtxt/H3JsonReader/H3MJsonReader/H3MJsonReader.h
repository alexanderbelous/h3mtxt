#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>

// API for deserializing H3M data from JSON.
namespace h3json
{
  template<>
  h3m::Army JsonReader2<h3m::Army>::operator()() const;

  template<>
  h3m::Coordinates JsonReader2<h3m::Coordinates>::operator()() const;

  template<>
  h3m::CustomHero JsonReader2<h3m::CustomHero>::operator()() const;

  template<>
  h3m::EventBase JsonReader2<h3m::EventBase>::operator()() const;

  template<>
  h3m::Guardians JsonReader2<h3m::Guardians>::operator()() const;

  template<>
  h3m::HeroArtifacts JsonReader2<h3m::HeroArtifacts>::operator()() const;

  template<>
  h3m::HeroSettings JsonReader2<h3m::HeroSettings>::operator()() const;

  template<>
  h3m::HeroesSettings JsonReader2<h3m::HeroesSettings>::operator()() const;

  template<>
  h3m::LossCondition JsonReader2<h3m::LossCondition>::operator()() const;

  // Partial specialization for h3m::LossConditionDetails.
  template<h3m::LossConditionType T>
  struct JsonReader2<h3m::LossConditionDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readLossCondition.cpp.
    // Template instantiations are provided for all valid LossConditionTypes.
    h3m::LossConditionDetails<T> operator()() const;
  };

  template<>
  h3m::MainTown JsonReader2<h3m::MainTown>::operator()() const;

  template<>
  h3m::Map JsonReader2<h3m::Map>::operator()() const;

  template<>
  h3m::MapAdditionalInfo JsonReader2<h3m::MapAdditionalInfo>::operator()() const;

  template<>
  h3m::MapBasicInfo JsonReader2<h3m::MapBasicInfo>::operator()() const;

  template<>
  h3m::MessageAndTreasure JsonReader2<h3m::MessageAndTreasure>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO_PLACEHOLDER>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO_PLACEHOLDER>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>::operator()() const;

  template<>
  h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>
  JsonReader2<h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>>::operator()() const;

  template<>
  h3m::ObjectTemplate JsonReader2<h3m::ObjectTemplate>::operator()() const;

  template<>
  h3m::PlayerSpecs JsonReader2<h3m::PlayerSpecs>::operator()() const;

  template<>
  h3m::Quest JsonReader2<h3m::Quest>::operator()() const;

  template<h3m::QuestType T>
  struct JsonReader2<h3m::QuestDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readQuest.cpp.
    // Template instantiations are provided for all valid QuestTypes.
    h3m::QuestDetails<T> operator()() const;
  };

  template<>
  h3m::Reward JsonReader2<h3m::Reward>::operator()() const;

  template<h3m::RewardType T>
  struct JsonReader2<h3m::RewardDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readReward.cpp.
    // Template instantiations are provided for all valid RewardTypes.
    h3m::RewardDetails<T> operator()() const;
  };

  template<>
  h3m::Rumor JsonReader2<h3m::Rumor>::operator()() const;

  template<>
  h3m::SecondarySkill JsonReader2<h3m::SecondarySkill>::operator()() const;

  template<>
  h3m::SpriteTilesBitmask JsonReader2<h3m::SpriteTilesBitmask>::operator()() const;

  template<>
  h3m::StartingHero JsonReader2<h3m::StartingHero>::operator()() const;

  template<>
  h3m::SpecialVictoryConditionBase JsonReader2<h3m::SpecialVictoryConditionBase>::operator()() const;

  template<>
  h3m::Teams JsonReader2<h3m::Teams>::operator()() const;

  // Full specialization for TerrainsBitmask. The template version from Utils.h
  // is not used here because TerrainsBitmask is currently serialized as an array of bytes.
  template<>
  h3m::TerrainsBitmask JsonReader2<h3m::TerrainsBitmask>::operator()() const;

  template<>
  h3m::Tile JsonReader2<h3m::Tile>::operator()() const;

  template<>
  h3m::TimedEvent JsonReader2<h3m::TimedEvent>::operator()() const;

  template<>
  h3m::TownBuildings JsonReader2<h3m::TownBuildings>::operator()() const;

  template<>
  h3m::TownEvent JsonReader2<h3m::TownEvent>::operator()() const;

  template<>
  h3m::VictoryCondition JsonReader2<h3m::VictoryCondition>::operator()() const;

  template<h3m::VictoryConditionType T>
  struct JsonReader2<h3m::VictoryConditionDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readVictoryCondition.cpp.
    // Template instantiations are provided for all valid VictoryConditionTypes.
    h3m::VictoryConditionDetails<T> operator()() const;
  };

  h3m::ObjectPropertiesVariant readObjectPropertiesVariant(const Json::Value& value,
                                                           h3m::ObjectPropertiesType object_properties_type);
}
