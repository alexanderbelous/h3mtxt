#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  // Serialize h3m::BlackMarket as a JSON array.
  template<>
  void JsonArrayWriter<h3m::BlackMarket>::operator()(const ArrayElementsWriter& out,
                                                     const h3m::BlackMarket& black_market) const;

  template<>
  void JsonObjectWriter<h3m::ObjectSvg>::operator()(FieldsWriter& out, const h3m::ObjectSvg& object) const;

  template<>
  void JsonObjectWriter<h3m::ObjectTemplateSvg>::operator()(FieldsWriter& out,
                                                            const h3m::ObjectTemplateSvg& object_template) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSpecsSvg>::operator()(FieldsWriter& out,
                                                         const h3m::PlayerSpecsSvg& player_specs) const;

  template<>
  void JsonObjectWriter<h3m::RumorSvg>::operator()(FieldsWriter& out, const h3m::RumorSvg& rumor) const;

  template<>
  void JsonObjectWriter<h3m::SavedGame>::operator()(FieldsWriter& out, const h3m::SavedGame& saved_game) const;

  template<>
  void JsonObjectWriter<h3m::TileSvg>::operator()(FieldsWriter& out, const h3m::TileSvg& tile) const;
}
