#include "Utils.h"

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/ObjectTemplate.h>

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <iterator>
#include <span>
#include <sstream>
#include <string>
#include <string_view>

using ::Testing_NS::asByteVector;

namespace h3m
{
  namespace
  {
    // Encodes h3m::Object via H3MWriter.
    // \param object - input Object.
    // \return std::string storing the encoded data.
    std::string encodeObject(const Object& object)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(object);
      return std::move(stream).str();
    }

    // Decodes h3m::Object via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Object decoded from @encoded_data.
    Object decodeObject(std::span<const ObjectTemplate> objects_templates, std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readObject(objects_templates.data(), objects_templates.size());
    }
  }

  TEST_CASE("H3M.ObjectPropertiesVariant.DefaultConstructor", "[H3M]")
  {
    const ObjectPropertiesVariant properties;
    REQUIRE(properties.type() == ObjectPropertiesType::NONE);
  }

  TEST_CASE("H3M.Object", "[H3M]")
  {
    const std::array<ObjectTemplate, 2> kObjectsTemplates{
      ObjectTemplate{
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
      },
      ObjectTemplate{
        .def = "AVWmrnd0.def",
        .passability {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
        .actionability {0, 0, 0, 0, 0, 0x80},
        .allowed_landscapes {0xFF, 0},
        .landscape_group {1, 0},
        .object_class = ObjectClass::SIGN,
        .object_subclass = 0,
        .object_group = ObjectGroup::Terrain,
        .is_ground = 0,
        .unknown = ReservedData<16>{}
      }
    };
    const Object kObject{
      .coordinates = {.x = 75, .y = 22, .z = 1},
      .template_idx = 1,
      .unknown = ReservedData<5>{},
      .properties = ObjectProperties<ObjectPropertiesType::SIGN>{
        .message = "KEEP OFF THE GRASS",
        .unknown = ReservedData<4>{}
      }
    };
    static constexpr char kBinaryDataCStr[] =
      "\x4b\x16\x01"                          // coordinates
      "\x01\x00\x00\x00"                      // template_idx
      "\x00\x00\x00\x00\x00"                  // unknown
                                              // properties
      "\x12\x00\x00\x00" "KEEP OFF THE GRASS" //   message
      "\x00\x00\x00\x00";                     //   unknown
    // std::string_view into kBinaryDataCStr.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
    REQUIRE(asByteVector(encodeObject(kObject)) == asByteVector(kBinaryData));
    REQUIRE(decodeObject(kObjectsTemplates, kBinaryData) == kObject);
  }
}
