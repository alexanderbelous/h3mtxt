#include "TestUtils_H3M.h"

#include <h3mtxt/Map/ObjectTemplate.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.ObjectTemplate", "[H3M]")
  {
    const ObjectTemplate kObjectTemplate
    {
      .def = "AVWmrnd0.def",
      .passability {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
      .actionability {0, 0, 0, 0, 0, 0x80},
      .allowed_landscapes {0xFF, 0},
      .landscape_group {1, 0},
      .object_class = ObjectClass::RANDOM_MONSTER,
      .object_subclass = 0,
      .object_group = ObjectGroup::Monster,
      .is_ground = 0,
      .unknown = ReservedData<16>{}
    };
    // The binary representation of kObjectTemplate.
    static constexpr std::string_view kBinaryData =
      "\x0c\x00\x00\x00" "AVWmrnd0.def"                                     // def
      "\xff\xff\xff\xff\xff\x7f"                                            // passability
      "\x00\x00\x00\x00\x00\x80"                                            // actionability
      "\xff\x00"                                                            // allowed_landscapes
      "\x01\x00"                                                            // landscape_group
      "\x47\x00\x00\x00"                                                    // object_class
      "\x00\x00\x00\x00"                                                    // object_subclass
      "\x02"                                                                // object_group
      "\x00"                                                                // is_ground
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"sv; // unknown

    REQUIRE(asByteVector(encodeViaH3MWriter(kObjectTemplate)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readObjectTemplate() == kObjectTemplate);
    REQUIRE(encodeAndDecodeJson(kObjectTemplate) == kObjectTemplate);
  }
}
