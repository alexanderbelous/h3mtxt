#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectTemplate.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::ObjectTemplate via H3MWriter.
    // \param object_template - input ObjectTemplate.
    // \return std::string storing the encoded data.
    std::string encodeObjectTemplate(const ObjectTemplate& object_template)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(object_template);
      return std::move(stream).str();
    }

    // Decodes h3m::ObjectTemplate via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::ObjectTemplate decoded from @encoded_data.
    ObjectTemplate decodeObjectTemplate(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readObjectTemplate();
    }
  }

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

    REQUIRE(asByteVector(encodeObjectTemplate(kObjectTemplate)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectTemplate(kBinaryData) == kObjectTemplate);
    REQUIRE(encodeAndDecodeJson(kObjectTemplate) == kObjectTemplate);
  }
}
