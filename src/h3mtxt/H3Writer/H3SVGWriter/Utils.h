#pragma once

#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/FixedLengthString.h>

namespace h3svg
{
  // Defined in Utils.h
  template<std::size_t N>
  void H3SVGWriter::writeData(const FixedLengthString<N>& str) const
  {
    writeSpan(std::span<const char>{ str.buffer() });
  }
}
