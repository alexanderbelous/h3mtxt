#pragma once

#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/SavedGame/FixedWidthString.h>

namespace Medea_NS
{
  template<std::size_t N>
  std::string_view JsonScalarGetter<h3svg::FixedWidthString<N>>::operator()(const h3svg::FixedWidthString<N>& str) const
  {
    return std::string_view{ str };
  }
}
