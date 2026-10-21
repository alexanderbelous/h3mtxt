#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/ObjectProperties.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string_view>
#include <type_traits>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  namespace
  {
    // Aggregates data for a test case for h3svg::ObjectProperties.
    template<ObjectPropertiesType T>
    struct TestCaseData
    {
      // "Simple" properties of an Adventure Map object.
      ObjectProperties<T> properties;
      // Bytes representing @properties in H3SVG.
      std::string_view binary_data;
    };

    // Variable template providing test data for each RewardType.
    template<ObjectPropertiesType T>
    const TestCaseData<T> kTestCases;

    template<>
    const TestCaseData<ObjectPropertiesType::None> kTestCases<ObjectPropertiesType::None> = {
      .properties = {
        .reserved = {0, 1, 2, 3}
      },
      .binary_data = "\x00\x01\x02\x03"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::BlackMarket> kTestCases<ObjectPropertiesType::BlackMarket> = {
      .properties = {
        .index = 23
      },
      .binary_data = "\x17\x00\x00\x00"sv
    };

    template<ObjectPropertiesType T>
    using StaticConstant = std::integral_constant<ObjectPropertiesType, T>;
  }

  TEMPLATE_TEST_CASE("H3SVG.ObjectProperties", "[H3SVG]",
                     StaticConstant<ObjectPropertiesType::None>,
                     StaticConstant<ObjectPropertiesType::BlackMarket>)
  {
    static constexpr ObjectPropertiesType kObjectPropertiesType = TestType::value;
    const TestCaseData<kObjectPropertiesType>& test_case_data = kTestCases<kObjectPropertiesType>;

    const ObjectProperties<kObjectPropertiesType>& object_properties = test_case_data.properties;
    const std::string_view binary_data = test_case_data.binary_data;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(object_properties)) == asByteVector(binary_data));
    REQUIRE(H3SVGReaderAdapter(binary_data).readObjectProperties<kObjectPropertiesType>() == object_properties);
    REQUIRE(encodeAndDecodeJson(object_properties) == object_properties);
  }
}
