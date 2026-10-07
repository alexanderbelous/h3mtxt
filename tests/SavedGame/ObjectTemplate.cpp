#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/ObjectTemplate.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  // Test encoding/decoding ObjectTemplate for H3SVG.
  TEST_CASE("H3SVG.ObjectTemplate", "[H3SVG]")
  {
    const ObjectTemplate kObjectTemplate {
      .def = "AVCcasx0.def",
      .width = 6,
      .height = 6,
      .colors = {252, 252, 252, 252, 252, 252},
      .passability = {255, 255, 255, 143, 7, 7},
      .shadows = {252, 252, 252, 252, 252, 252},
      .actionability = {0, 0, 0, 0, 0, 32},
      .object_class = static_cast<ObjectClass16>(ObjectClass::TOWN),
      .object_subclass = 0,
      .reserved = {},
      .is_ground = false
    };
    // Binary representation of kObjectTemplate.
    static constexpr std::string_view kBinaryData =
      "\x0c\x00" "AVCcasx0.def" // def
      "\x06" // width
      "\x06" // height
      "\xfc\xfc\xfc\xfc\xfc\xfc" // colors
      "\xff\xff\xff\x8f\x07\x07" // passability
      "\xfc\xfc\xfc\xfc\xfc\xfc" // shadows
      "\x00\x00\x00\x00\x00\x20" // actionability
      "\x62\x00" // object_class
      "\x00\x00" // object_subclass
      "\x00\x00" // reserved
      "\x00" // is_ground
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kObjectTemplate)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readObjectTemplate() == kObjectTemplate);
    REQUIRE(encodeAndDecodeJson(kObjectTemplate) == kObjectTemplate);
  }
}
