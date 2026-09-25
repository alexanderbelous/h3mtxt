#pragma once

#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/SavedGame/FixedLengthString.h>

namespace Medea_NS
{
  template<std::size_t N>
  std::string_view JsonScalarGetter<h3svg::FixedLengthString<N>>::operator()(const h3svg::FixedLengthString<N>& str) const
  {
    return std::string_view{ str };
  }
}
