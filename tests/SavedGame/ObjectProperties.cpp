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

    template<>
    const TestCaseData<ObjectPropertiesType::CreatureBank> kTestCases<ObjectPropertiesType::CreatureBank> = {
      .properties = {
        .reserved1 = -1,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .index = 23,
        .is_cleared = false,
        .reserved2 = -1
      },
      .binary_data = "\x1f\xe9\x02\xfc"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Event> kTestCases<ObjectPropertiesType::Event> = {
      .properties = {
        .id = 7,
        .affected_players = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .applies_to_computer = true,
        .cancel_after_first_visit = false,
        .reserved = 555
      },
      .binary_data = "\x07\x20\xb5\x22"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Hero> kTestCases<ObjectPropertiesType::Hero> = {
      .properties = {
        .hero = static_cast<HeroType32>(HeroType::Gunnar)
      },
      .binary_data = "\x55\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Monster> kTestCases<ObjectPropertiesType::Monster> = {
      .properties = {
        .quantity = 999,
        .growth_remainder = 3,
        .aggression = 0,
        .never_flees = true,
        .does_not_grow = false,
        .has_message_or_treasure = true,
        .index = 30
      },
      .binary_data = "\xe7\x03\xf2\x98"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::MysticalGarden> kTestCases<ObjectPropertiesType::MysticalGarden> = {
      .properties = {
        .index = 13,
        .reserved1 = 1,
        .resource_type = ResourceType::Gems,
        .is_lootable = true,
        .reserved2 = -1
      },
      .binary_data = "\x6d\xfd\xff\xff"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Obelisk> kTestCases<ObjectPropertiesType::Obelisk> = {
      .properties = {
        .index = 17
      },
      .binary_data = "\x11\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Pyramid> kTestCases<ObjectPropertiesType::Pyramid> = {
      .properties = {
        .spell = SpellType::Implosion,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .is_lootable = true,
        .reserved1 = 5,
        .reserved2 = -200
      },
      .binary_data = "\x0b\x49\x02\xe7"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::RefugeeCamp> kTestCases<ObjectPropertiesType::RefugeeCamp> = {
      .properties = {
        .quantity = 17
      },
      .binary_data = "\x11\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Scholar> kTestCases<ObjectPropertiesType::Scholar> = {
      .properties = {
        .type = ScholarRewardType::PrimarySkill,
        .primary_skill = PrimarySkillType::SpellPower,
        .secondary_skill = static_cast<SecondarySkillType>(0b01111111), // TODO: replace with SecondarySkillType::None.
        .spell = static_cast<SpellType16>(SpellType::None),
        .reserved = -1
      },
      .binary_data = "\xd0\xff\xff\xff"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::SeaChest> kTestCases<ObjectPropertiesType::SeaChest> = {
      .properties = {
        .content = SeaChestContentType::Gold1000Artifact,
        .reserved1 = 0,
        .artifact = static_cast<ArtifactType32>(ArtifactType::Speculum),
        .reserved2 = -1
      },
      .binary_data = "\xa2\xe1\xff\xff"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::ShipwreckSurvivor> kTestCases<ObjectPropertiesType::ShipwreckSurvivor> = {
      .properties = {
        .artifact = static_cast<ArtifactType32>(ArtifactType::AngelWings)
      },
      .binary_data = "\x48\x00\x00\x00"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::TreeOfKnowledge> kTestCases<ObjectPropertiesType::TreeOfKnowledge> = {
      .properties = {
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .index = 23,
        .type = TreeOfKnowledgeType::Gold,
        .reserved1 = 1,
        .reserved2 = 1000
      },
      .binary_data = "\x17\xa9\xe8\x03"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Wagon> kTestCases<ObjectPropertiesType::Wagon> = {
      .properties = {
        .artifact = ArtifactType::None,
        .has_artifact = false,
        .resource_quantity = 5,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .resource_type = ResourceType::Crystal,
        .is_lootable = true,
        .reserved = -1
      },
      .binary_data = "\x05\xa9\xff\xe9"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::WarriorsTomb> kTestCases<ObjectPropertiesType::WarriorsTomb> = {
      .properties = {
        .has_artifact = true,
        .reserved1 = -1,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .artifact = ArtifactType::AngelWings,
        .reserved2 = -1
      },
      .binary_data = "\x1f\x09\x89\xff"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::WaterWheel> kTestCases<ObjectPropertiesType::WaterWheel> = {
      .properties = {
        .bonus = 2,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .reserved = -1
      },
      .binary_data = "\x02\xe9\xff\xff"sv
    };

    template<>
    const TestCaseData<ObjectPropertiesType::Windmill> kTestCases<ObjectPropertiesType::Windmill> = {
      .properties = {
        .resource_type = ResourceType::Gems,
        .resource_quantity = 4,
        .visited_by = []() consteval {
          PlayersBitmask bitmask;
          bitmask.set(PlayerColor::Green, true);
          bitmask.set(PlayerColor::Teal, true);
          return bitmask;
        }(),
        .reserved1 = 1,
        .reserved2 = -1
      },
      .binary_data = "\x15\x89\xfe\xff"sv
    };

    template<ObjectPropertiesType T>
    using StaticConstant = std::integral_constant<ObjectPropertiesType, T>;
  }

  TEMPLATE_TEST_CASE("H3SVG.ObjectProperties", "[H3SVG]",
                     StaticConstant<ObjectPropertiesType::None>,
                     StaticConstant<ObjectPropertiesType::BlackMarket>,
                     StaticConstant<ObjectPropertiesType::CreatureBank>,
                     StaticConstant<ObjectPropertiesType::Event>,
                     StaticConstant<ObjectPropertiesType::Hero>,
                     StaticConstant<ObjectPropertiesType::Monster>,
                     StaticConstant<ObjectPropertiesType::MysticalGarden>,
                     StaticConstant<ObjectPropertiesType::Obelisk>,
                     StaticConstant<ObjectPropertiesType::Pyramid>,
                     StaticConstant<ObjectPropertiesType::RefugeeCamp>,
                     StaticConstant<ObjectPropertiesType::Scholar>,
                     StaticConstant<ObjectPropertiesType::SeaChest>,
                     StaticConstant<ObjectPropertiesType::ShipwreckSurvivor>,
                     StaticConstant<ObjectPropertiesType::TreeOfKnowledge>,
                     StaticConstant<ObjectPropertiesType::Wagon>,
                     StaticConstant<ObjectPropertiesType::WarriorsTomb>,
                     StaticConstant<ObjectPropertiesType::WaterWheel>,
                     StaticConstant<ObjectPropertiesType::Windmill>)
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
