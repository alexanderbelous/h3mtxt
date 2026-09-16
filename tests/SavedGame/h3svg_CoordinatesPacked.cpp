#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>
#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>
#include <h3mtxt/SavedGame/CoordinatesPacked.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3svg
{
  namespace
  {
    std::string encodeCoordinatesPacked(const CoordinatesPacked& coordinates)
    {
      std::ostringstream stream;
      H3SVGWriter{ stream }.writeData(coordinates);
      return std::move(stream).str();
    }

    CoordinatesPacked decodeCoordinatesPacked(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3SVGReader{ stream }.readCoordinatesPacked();
    }
  }

  // Test encoding/decoding CoordinatesPacked for H3SVG.
  TEST_CASE("H3SVG.CoordinatesPacked", "[H3SVG]")
  {
    static constexpr CoordinatesPacked kCoordinates{
      .x = 100,
      .padding1 = 13,
      .y = 50,
      .z = 1,
      .padding2 = 1
    };
    // The binary representation of kCoordinates.
    // +----+------+--------------+---------+--------------+
    // | p2 | z    | y            | p1      | x            | // fields
    // +----+------+--------------+---------+--------------+
    // | 01 | 0001 | 00 0011 0010 | 00 1101 | 00 0110 0100 | // bits (MSB -> LSB)
    // +----+------+--------------+---------+--------------+
    // | 2  | 4    | 10           | 6       | 10           | // num bits
    // +----+------+--------------+---------+--------------+
    // =
    // +-----------+-----------+-----------+-----------+
    // | 0100 0100 | 0011 0010 | 0011 0100 | 0110 0100 | // bytes (MSB -> LSB)
    // +-----------+-----------+-----------+-----------+
    // | 0x44      | 0x32      | 0x34      | 0x64      |
    // +-----------+-----------+-----------+-----------+
    static constexpr std::string_view kBinaryData = "\x64\x34\x32\x44"sv;

    REQUIRE(asByteVector(encodeCoordinatesPacked(kCoordinates)) == asByteVector(kBinaryData));
    REQUIRE(decodeCoordinatesPacked(kBinaryData) == kCoordinates);
    REQUIRE(encodeAndDecodeJson(kCoordinates) == kCoordinates);
  }
}
