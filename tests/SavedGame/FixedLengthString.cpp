#include "TestingUtils_H3SVG.h"

#include <h3mtxt/H3Writer/H3SVGWriter/Utils.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>

#include <catch2/catch_test_macros.hpp>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.FixedLengthString", "[H3SVG]")
  {
    static constexpr std::size_t kSize = 20;
    static constexpr FixedLengthString<kSize> kStr = "Hello, World!";
    static constexpr std::string_view kBinaryData = kStr.bufferView();
    REQUIRE(asByteVector(encodeViaH3SVGWriter(kStr)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readFixedLengthString<kSize>() == kStr);
    //REQUIRE(encodeAndDecodeJson(kStr) == kStr);
  }
}
