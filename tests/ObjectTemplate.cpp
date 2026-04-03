#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectTemplate.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

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
    // The binary representation of kMapBasicInfo.
    static constexpr char kBinaryDataCStr[] =
      "\x0c\x00\x00\x00" "AVWmrnd0.def"                                   // def
      "\xff\xff\xff\xff\xff\x7f"                                          // passability
      "\x00\x00\x00\x00\x00\x80"                                          // actionability
      "\xff\x00"                                                          // allowed_landscapes
      "\x01\x00"                                                          // landscape_group
      "\x47\x00\x00\x00"                                                  // object_class
      "\x00\x00\x00\x00"                                                  // object_subclass
      "\x02"                                                              // object_group
      "\x00"                                                              // is_ground
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; // unknown
    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    SECTION("Encode")
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(kObjectTemplate);
      REQUIRE(stream.view() == kBinaryData);
    }

    SECTION("Decode")
    {
      std::istringstream stream{ std::string{kBinaryData}};
      REQUIRE(H3MReader{ stream }.readObjectTemplate() == kObjectTemplate);
    }
  }
}
