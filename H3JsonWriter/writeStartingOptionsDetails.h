#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>

// API for JSON serialization of h3m::StartingOptionsDetails.
//
// These specializations are declared here rather than in API.h because I don't want to
// include the full definition of StartingOptionsType in API.h.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>&) const;
}
