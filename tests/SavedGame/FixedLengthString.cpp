#include "../Utils.h"

#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>
#include <h3mtxt/H3Writer/H3SVGWriter/Utils.h>
#include <h3mtxt/SavedGame/FixedLengthString.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <sstream>
#include <string>
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3svg
{
  namespace
  {
    template<std::size_t N>
    std::string encodeData(const FixedLengthString<N>& str)
    {
      std::ostringstream stream;
      H3SVGWriter{ stream }.writeData(str);
      return std::move(stream).str();
    }

    template<std::size_t N>
    FixedLengthString<N> decodeData(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3SVGReader{ stream }.readFixedLengthString<N>();
    }
  }

  TEST_CASE("H3SVG.FixedLengthString.DefaultConstructor", "[H3SVG]")
  {
    static constexpr std::size_t kSize = 20;
    static constexpr FixedLengthString<kSize> kStr = "Hello, World!";
    static constexpr std::string_view kBinaryData = kStr.bufferView();
    REQUIRE(asByteVector(encodeData(kStr)) == asByteVector(kBinaryData));
    REQUIRE(decodeData<kSize>(kBinaryData) == kStr);
    //REQUIRE(encodeAndDecodeJson(kStr) == kStr);
  }
}
