#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures from Campaign library.
namespace Medea_NS
{
  // ============================================================
  // Human-readable comments for enum values.
  // ------------------------------------------------------------
  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignFormat value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignId value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignMusic value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignVideo value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::StartingBonusType value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::StartingOptionsType value) const;
  // ============================================================

  template<>
  void JsonObjectWriter<h3m::Campaign>::operator()(FieldsWriter& out, const h3m::Campaign& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignHeader>::operator()(FieldsWriter& out, const h3m::CampaignHeader& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignScenario>::operator()(FieldsWriter& out,
                                                           const h3m::CampaignScenario& scenario) const;

  template<>
  void JsonObjectWriter<h3m::CrossoverOptions>::operator()(FieldsWriter& out,
                                                           const h3m::CrossoverOptions& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::CutScene>::operator()(FieldsWriter& out, const h3m::CutScene& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::HeroCrossoverOption>::operator()(FieldsWriter& out,
                                                              const h3m::HeroCrossoverOption& option) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonus>::operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const;

  template<h3m::StartingBonusType T>
  struct JsonObjectWriter<h3m::StartingBonusDetails<T>>
  {
    // Defined in writeStartingBonus.cpp.
    // Template instantiations are provided for all valid StartingBonusTypes.
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<T>& details) const;
  };

  template<>
  void JsonObjectWriter<h3m::StartingHeroOption>::operator()(FieldsWriter& out,
                                                             const h3m::StartingHeroOption& option) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const;

  template<h3m::StartingOptionsType T>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<T>>
  {
    // Defined in writeStartingOptions.cpp.
    // Template instantiations are provided for all valid StartingOptionsTypes.
    void operator()(FieldsWriter& out, const h3m::StartingOptionsDetails<T>& details) const;
  };
}
