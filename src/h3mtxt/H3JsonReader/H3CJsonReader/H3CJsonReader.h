#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>

// API for deserializing H3C data from JSON.
namespace h3json
{
  template<>
  h3m::Campaign JsonReader2<h3m::Campaign>::operator()() const;

  template<>
  h3m::CampaignHeader JsonReader2<h3m::CampaignHeader>::operator()() const;

  template<>
  h3m::CampaignScenario JsonReader2<h3m::CampaignScenario>::operator()() const;

  template<>
  h3m::CrossoverOptions JsonReader2<h3m::CrossoverOptions>::operator()() const;

  template<>
  h3m::CutScene JsonReader2<h3m::CutScene>::operator()() const;

  template<>
  h3m::HeroCrossoverOption JsonReader2<h3m::HeroCrossoverOption>::operator()() const;

  template<>
  h3m::StartingBonus JsonReader2<h3m::StartingBonus>::operator()() const;

  template<h3m::StartingBonusType T>
  struct JsonReader2<h3m::StartingBonusDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readStartingBonus.cpp.
    // Template instantiations are provided for all valid StartingBonusTypes.
    h3m::StartingBonusDetails<T> operator()() const;
  };

  template<>
  h3m::StartingHeroOption JsonReader2<h3m::StartingHeroOption>::operator()() const;

  template<>
  h3m::StartingOptions JsonReader2<h3m::StartingOptions>::operator()() const;

  template<h3m::StartingOptionsType T>
  struct JsonReader2<h3m::StartingOptionsDetails<T>> : JsonReader2Base
  {
    using JsonReader2Base::JsonReader2Base;

    // Defined in readStartingOptions.cpp.
    // Template instantiations are provided for each valid StartingOptionsType.
    h3m::StartingOptionsDetails<T> operator()() const;
  };
}
