#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

#include <array>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::PlayerSpecsSvg>::operator()(FieldsWriter& out, const h3m::PlayerSpecsSvg& player_specs) const;

  template<>
  void JsonArrayWriter<std::array<h3m::PlayerSpecsSvg, h3m::kMaxPlayers>>::operator()(
    const ArrayElementsWriter& out,
    const std::array<h3m::PlayerSpecsSvg, h3m::kMaxPlayers>& players) const;

  template<>
  void JsonObjectWriter<h3m::SavedGame>::operator()(FieldsWriter& out, const h3m::SavedGame& saved_game) const;
}
