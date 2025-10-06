#pragma once

#include <h3mtxt/H3JsonWriter/LocalizedStringsData.h>

#include <iosfwd>

namespace h3m::H3JsonWriter_NS
{
  // Reads the localized strings from the specified stream.
  //
  // The function reads up to kNumLocalizedStringIds lines from the input stream.
  // Each line corresponds to a single localized string:
  // * the 0th line will be used for LocalizedStringId{0}
  // * the 1st line will be used for LocalizedStringId{1}
  // ...
  // * the k-th line will be used for LocalizedStringId{k}
  //
  // If the input stream has fewer than kNumLocalizedStringIds lines, the function won't fail,
  // but the returned LocalizedStringsData will return empty strings for the missing IDs.
  // 
  // \param stream - input stream.
  // \return the parsed LocalizedStringsData.
  LocalizedStringsData readLocalizedStringsFromStream(std::istream& stream);
}
