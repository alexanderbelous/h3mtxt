#pragma once

#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>

namespace h3json
{
  template<std::size_t N>
  h3svg::FixedLengthString<N> JsonReader<h3svg::FixedLengthString<N>>::operator()(const Json::Value& value) const
  {
    // TODO: eliminate redundant memory allocation and copy.
    const std::string str = fromJson<std::string>(value);
    return h3svg::FixedLengthString<N>{ std::string_view{ str } };
  }
}
