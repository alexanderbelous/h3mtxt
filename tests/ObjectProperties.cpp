#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectProperties.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::ObjectProperties<T> via H3MWriter.
    // \param object_properties - input ObjectProperties<T>.
    // \return std::string storing the encoded data.
    template<ObjectPropertiesType T>
    std::string encodeObjectProperties(const ObjectProperties<T>& object_properties)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(object_properties);
      return std::move(stream).str();
    }

    // Decodes h3m::ObjectProperties<T> via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::ObjectProperties<T> decoded from @encoded_data.
    template<ObjectPropertiesType T>
    ObjectProperties<T> decodeObjectProperties(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readObjectProperties<T>();
    }
  }

  TEST_CASE("H3M.ObjectProperties.AbandonedMine", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::ABANDONED_MINE> kProperties = {
      .potential_resources = []() consteval {
        ResourcesBitmask bitmask;
        bitmask.set(ResourceType::Gems, true);
        bitmask.set(ResourceType::Crystal, true);
        return bitmask;
      }(),
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x30\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::ABANDONED_MINE>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Artifact", "[H3M]")
  {
    SECTION("No guardians")
    {
      const ObjectProperties<ObjectPropertiesType::ARTIFACT> kProperties = {
        .guardians = std::nullopt
      };
      static constexpr char kBinaryDataCStr[] = "\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::ARTIFACT>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("With guardians")
    {
      const ObjectProperties<ObjectPropertiesType::ARTIFACT> kProperties = {
        .guardians = Guardians{
          .message = "Ready to fight some dragons?",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::BlackDragon, .count = 5},
            CreatureStack{.type = CreatureType::GreenDragon, .count = 11},
            CreatureStack{.type = CreatureType::RedDragon, .count = 10},
            CreatureStack{.type = CreatureType::GoldDragon, .count = 6},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        }
      };
      static constexpr char kBinaryDataCStr[] =
        "\x01"                                              // has_guardians
          "\x1c\x00\x00\x00" "Ready to fight some dragons?" // message
          "\x01"                                            // has_creatures
            "\x53\x00" "\x05\x00"                           // creatures
            "\x1a\x00" "\x0b\x00"
            "\x52\x00" "\x0a\x00"
            "\x1b\x00" "\x06\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
          "\x00\x00\x00\x00";                               // unknown
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::ARTIFACT>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.Event", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::EVENT> kProperties = {
      EventBase{
        .guardians = Guardians{
          .message = "Boo!",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::GhostDragon, .count = 5},
            CreatureStack{.type = CreatureType::Wraith, .count = 100},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        },
        .experience = 1000,
        .spell_points = 100,
        .morale = -3,
        .luck = 1,
        .resources = []() consteval {
          Resources resources;
          resources[ResourceType::Crystal] = 10;
          resources[ResourceType::Gold] = 5000;
          return resources;
        }(),
        .primary_skills = PrimarySkills{
          .attack = 1,
          .defense = 2,
          .spell_power = 3,
          .knowledge = 4
        },
        .secondary_skills = {
          SecondarySkill{.type = SecondarySkillType::EarthMagic, .level = 3},
          SecondarySkill{.type = SecondarySkillType::Wisdom, .level = 3},
        },
        .artifacts = {
          ArtifactType::TomeOfEarthMagic,
          ArtifactType::DragonWingTabard
        },
        .spells = {
          SpellType::TownPortal,
          SpellType::ForceField
        },
        .creatures = {
          CreatureStack{.type = CreatureType::Sharpshooter, .count = 50},
          CreatureStack{.type = CreatureType::HarpyHag, .count = 100}
        },
        .unknown = ReservedData<8>{}
      },
      /* .affected_players = */ []() consteval {
        PlayersBitmask bitmask;
        bitmask.set(PlayerColor::Green, true);
        return bitmask;
      }(),
      /* .applies_to_computer = */ Bool{0},
      /* .remove_after_first_visit = */ Bool{1},
      /* .unknown2 = */ ReservedData<4>{}
    };

    static constexpr char kBinaryDataCStr[] =
      "\x01"                                       // has_guardians
      "\x04\x00\x00\x00" "Boo!"                    //   message
      "\x01"                                       //   has_creatures
      "\x45\x00" "\x05\x00"                        //   creatures
      "\x3d\x00" "\x64\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\x00\x00\x00\x00"                           //   unknown
      "\xe8\x03\x00\x00"                           // experience
      "\x64\x00\x00\x00"                           // spell_points
      "\xfd"                                       // morale
      "\x01"                                       // luck
      "\x00\x00\x00\x00"                           // resources
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x0a\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x88\x13\x00\x00"
      "\x01\x02\x03\x04"                           // primary_skills
      "\x02" "\x11\x03" "\x07\x03"                 // secondary_skills
      "\x02" "\x59\x00" "\x2a\x00"                 // artifacts
      "\x02" "\x09" "\x0c"                         // spells
      "\x02" "\x89\x00\x32\x00" "\x49\x00\x64\x00" // creatures
      "\x00\x00\x00\x00\x00\x00\x00\x00"           // unknown
      "\x08"                                       // affected_players
      "\x00"                                       // applies_to_computer
      "\x01"                                       // remove_after_first_visit
      "\x00\x00\x00\x00";                          // unknown2
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::EVENT>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Garrison", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::GARRISON> kProperties = {
      .owner = PlayerColor::Green,
      .unknown = ReservedData<3>{},
      .creatures = {
        CreatureStack{.type = CreatureType::Sharpshooter, .count = 200},
        CreatureStack{.type = CreatureType::Enchanter, .count = 100},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{}
      },
      .can_remove_units = 1,
      .unknown2 = ReservedData<8>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\x03"                              // owner
      "\x00\x00\x00"                      // unknown
        "\x89\x00" "\xc8\x00"             // creatures
        "\x88\x00" "\x64\x00"
        "\xff\xff" "\x00\x00"
        "\xff\xff" "\x00\x00"
        "\xff\xff" "\x00\x00"
        "\xff\xff" "\x00\x00"
        "\xff\xff" "\x00\x00"
      "\x01"                              // can_remove_units
      "\x00\x00\x00\x00\x00\x00\x00\x00"; // unknown2
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::GARRISON>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.GenericNoProperties", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES> kProperties{};
    constexpr std::string_view kBinaryData = "";

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Grail", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::GRAIL> kProperties = {
      .allowable_radius = 10,
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x0a\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::GRAIL>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Hero", "[H3M]")
  {
    // TODO: ideally, I should add tests for each optional field when it's missing.
    const ObjectProperties<ObjectPropertiesType::HERO> kProperties = {
      .absod_id = 24601,
      .owner = PlayerColor::Green,
      .type = HeroType::Vokial,
      .name = "Edward",
      .experience = 10000,
      .portrait = HeroPortrait::LordHaart,
      .secondary_skills = std::vector<SecondarySkill>{
        SecondarySkill{.type = SecondarySkillType::Diplomacy, .level = 3},
        SecondarySkill{.type = SecondarySkillType::EagleEye, .level = 3}
      },
      .creatures = std::array<CreatureStack, 7>{
        CreatureStack{.type = CreatureType::Sprite, .count = 1},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
      },
      .formation = Formation::Grouped,
      .artifacts = HeroArtifacts{
        .equipped = []() consteval {
          auto artifacts = HeroArtifacts::kNoEquippedArtifacts;
          artifacts[ArtifactSlot::Shoulders] = ArtifactType::EverflowingCrystalCloak;
          return artifacts;
        }(),
        .backpack = {ArtifactType::RingOfInfiniteGems}
      },
      .patrol_radius = 10,
      .biography = "Sparkling vampire",
      .gender = Gender::Male,
      .spells = []() consteval {
        SpellsBitmask bitmask;
        bitmask.set(SpellType::Bloodlust, true);
        return bitmask;
      }(),
      .primary_skills = PrimarySkills{
        .attack = 10,
        .defense = 10,
        .spell_power = 1,
        .knowledge = 3
      },
      .unknown = ReservedData<16>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\x19\x60\x00\x00"                              // absod_id
      "\x03"                                          // owner
      "\x41"                                          // type
      "\x01" "\x06\x00\x00\x00" "Edward"              // name
      "\x01" "\x10\x27\x00\x00"                       // experience
      "\x01" "\x04"                                   // portrait
      "\x01" "\x02\x00\x00\x00" "\x04\x03" "\x0b\x03" // secondary_skills
      "\x01"                                          // creatures
      "\x77\x00" "\x01\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\x01"                                          // formation
      "\x01"                                          // artifacts
      "\xff\xff"                                      //   Head
      "\x6d\x00"                                      //   Shoulders
      "\xff\xff"                                      //   Neck
      "\xff\xff"                                      //   RightHand
      "\xff\xff"                                      //   LeftHand
      "\xff\xff"                                      //   Torso
      "\xff\xff"                                      //   RightRing
      "\xff\xff"                                      //   LeftRing
      "\xff\xff"                                      //   Feet
      "\xff\xff"                                      //   Misc1
      "\xff\xff"                                      //   Misc2
      "\xff\xff"                                      //   Misc3
      "\xff\xff"                                      //   Misc4
      "\xff\xff"                                      //   WarMachine1
      "\xff\xff"                                      //   WarMachine2
      "\xff\xff"                                      //   WarMachine3
      "\xff\xff"                                      //   WarMachine4
      "\xff\xff"                                      //   Spellbook
      "\xff\xff"                                      //   Misc5
      "\x01\x00" "\x6e\x00"                           //   backpack
      "\x0a"                                          // patrol_radius
      "\x01" "\x11\x00\x00\x00" "Sparkling vampire"   // biography
      "\x00"                                          // gender
      "\x01" "\x00\x00\x00\x00\x00\x08\x00\x00\x00"   // spells
      "\x01" "\x0a\x0a\x01\x03"                       // primary_skills
      "\x00\x00\x00\x00\x00\x00\x00\x00"              // unknown
      "\x00\x00\x00\x00\x00\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::HERO>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Monster", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::MONSTER> kProperties = {
      .absod_id = 2026,
      .count = 100,
      .disposition = Disposition::Savage,
      .message_and_treasure = MessageAndTreasure{
        .message = "Boo!",
        .resources = []() consteval {
          Resources resources;
          resources[ResourceType::Gems] = 5;
          return resources;
        }(),
        .artifact = ArtifactType::BadgeOfCourage
      },
      .never_flees = 1,
      .does_not_grow = 1,
      .unknown = ReservedData<2>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\xea\x07\x00\x00"        // absod_id
      "\x64\x00"                // count
      "\x04"                    // disposition
      "\x01"                    // ?message_and_treasure
      "\x04\x00\x00\x00" "Boo!" //   message
      "\x00\x00\x00\x00"        //   resources
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x05\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x31\x00"                //   artifact
      "\x01"                    // never_flees
      "\x01"                    // does_not_grow
      "\x00\x00";               // unknown
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::MONSTER>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.PandorasBox", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> kProperties = {
      EventBase{
        .guardians = Guardians{
          .message = "Boo!",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::GhostDragon, .count = 5},
            CreatureStack{.type = CreatureType::Wraith, .count = 100},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        },
        .experience = 1000,
        .spell_points = 100,
        .morale = -3,
        .luck = 1,
        .resources = []() consteval {
          Resources resources;
          resources[ResourceType::Crystal] = 10;
          resources[ResourceType::Gold] = 5000;
          return resources;
        }(),
        .primary_skills = PrimarySkills{
          .attack = 1,
          .defense = 2,
          .spell_power = 3,
          .knowledge = 4
        },
        .secondary_skills = {
          SecondarySkill{.type = SecondarySkillType::EarthMagic, .level = 3},
          SecondarySkill{.type = SecondarySkillType::Wisdom, .level = 3},
        },
        .artifacts = {
          ArtifactType::TomeOfEarthMagic,
          ArtifactType::DragonWingTabard
        },
        .spells = {
          SpellType::TownPortal,
          SpellType::ForceField
        },
        .creatures = {
          CreatureStack{.type = CreatureType::Sharpshooter, .count = 50},
          CreatureStack{.type = CreatureType::HarpyHag, .count = 100}
        },
        .unknown = ReservedData<8>{}
      }
    };

    static constexpr char kBinaryDataCStr[] =
      "\x01"                                       // has_guardians
      "\x04\x00\x00\x00" "Boo!"                    //   message
      "\x01"                                       //   has_creatures
      "\x45\x00" "\x05\x00"                        //   creatures
      "\x3d\x00" "\x64\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\xff\xff" "\x00\x00"
      "\x00\x00\x00\x00"                           //   unknown
      "\xe8\x03\x00\x00"                           // experience
      "\x64\x00\x00\x00"                           // spell_points
      "\xfd"                                       // morale
      "\x01"                                       // luck
      "\x00\x00\x00\x00"                           // resources
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x0a\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x88\x13\x00\x00"
      "\x01\x02\x03\x04"                           // primary_skills
      "\x02" "\x11\x03" "\x07\x03"                 // secondary_skills
      "\x02" "\x59\x00" "\x2a\x00"                 // artifacts
      "\x02" "\x09" "\x0c"                         // spells
      "\x02" "\x89\x00\x32\x00" "\x49\x00\x64\x00" // creatures
      "\x00\x00\x00\x00\x00\x00\x00\x00";          // unknown
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::PANDORAS_BOX>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.PlaceholderHero", "[H3M]")
  {
    SECTION("Specific")
    {
      constexpr ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO> kProperties = {
        .owner = PlayerColor::Green,
        .type = HeroType::Gunnar
      };
      static constexpr char kBinaryDataCStr[] = "\x03" "\x55";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Power-rated")
    {
      constexpr ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO> kProperties = {
        .owner = PlayerColor::Green,
        .type = HeroType{0xFF},
        .power_rating = 2
      };
      static constexpr char kBinaryDataCStr[] = "\x03" "\xff" "\x02";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.QuestGuard", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::QUEST_GUARD> kProperties = {
      .quest = Quest{
        .details = QuestDetails<QuestType::BeHero>{
          .hero = HeroType::Mephala
        },
        .deadline = 28,
        .proposal = "Only Mephala may pass.",
        .progress = "You're not Mephala.",
        .completion = "You may pass."
      }
    };
    static constexpr char kBinaryDataCStr[] =
      "\x08"                                      // quest_type
      "\x10"                                      //   hero
      "\x1c\x00\x00\x00"                          // deadline
      "\x16\x00\x00\x00" "Only Mephala may pass." // proposal
      "\x13\x00\x00\x00" "You're not Mephala."    // progress
      "\x0d\x00\x00\x00" "You may pass.";         // completion
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::QUEST_GUARD>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.RandomDwelling", "[H3M]")
  {
    SECTION("Tied to town")
    {
      constexpr ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING> kProperties = {
        .owner = static_cast<std::uint32_t>(PlayerColor::Green),
        .town_absod_id = 2026,
        .min_level = 4,
        .max_level = 6
      };
      static constexpr char kBinaryDataCStr[] =
        "\x03\x00\x00\x00" // owner
        "\xea\x07\x00\x00" // town_absod_id
        "\x04"             // min_level
        "\x06";            // max_level
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Not tied to town")
    {
      constexpr ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING> kProperties = {
        .owner = static_cast<std::uint32_t>(PlayerColor::Green),
        .town_absod_id = 0,
        .alignment = []() consteval {
          TownsBitmask bitmask;
          bitmask.set(TownType::Rampart, true);
          bitmask.set(TownType::Dungeon, true);
          bitmask.set(TownType::Conflux, true);
          return bitmask;
        }(),
        .min_level = 4,
        .max_level = 6
      };
      static constexpr char kBinaryDataCStr[] =
        "\x03\x00\x00\x00" // owner
        "\x00\x00\x00\x00" // town_absod_id
        "\x22\x01"         // alignment
        "\x04"             // min_level
        "\x06";            // max_level
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.RandomDwellingPresetAlignment", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT> kProperties = {
      .owner = static_cast<std::uint32_t>(PlayerColor::Green),
      .min_level = 4,
      .max_level = 6
    };
    static constexpr char kBinaryDataCStr[] =
      "\x03\x00\x00\x00" // owner
      "\x04"             // min_level
      "\x06";            // max_level
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.RandomDwellingPresetLevel", "[H3M]")
  {
    SECTION("Tied to town")
    {
      constexpr ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL> kProperties = {
        .owner = static_cast<std::uint32_t>(PlayerColor::Green),
        .town_absod_id = 2026
      };
      static constexpr char kBinaryDataCStr[] =
        "\x03\x00\x00\x00"  // owner
        "\xea\x07\x00\x00"; // town_absod_id
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Not tied to town")
    {
      constexpr ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL> kProperties = {
        .owner = static_cast<std::uint32_t>(PlayerColor::Green),
        .town_absod_id = 0,
        .alignment = []() consteval {
          TownsBitmask bitmask;
          bitmask.set(TownType::Rampart, true);
          bitmask.set(TownType::Dungeon, true);
          bitmask.set(TownType::Conflux, true);
          return bitmask;
        }()
      };
      static constexpr char kBinaryDataCStr[] =
        "\x03\x00\x00\x00" // owner
        "\x00\x00\x00\x00" // town_absod_id
        "\x22\x01";        // alignment
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.Resource", "[H3M]")
  {
    SECTION("No guardians")
    {
      const ObjectProperties<ObjectPropertiesType::RESOURCE> kProperties = {
        .guardians = std::nullopt,
        .quantity = 30,
        .unknown = ReservedData<4>{}
      };
      static constexpr char kBinaryDataCStr[] = "\x00" "\x1e\x00\x00\x00" "\x00\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RESOURCE>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("With guardians")
    {
      const ObjectProperties<ObjectPropertiesType::RESOURCE> kProperties = {
        .guardians = Guardians{
          .message = "Ready to fight some dragons?",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::BlackDragon, .count = 5},
            CreatureStack{.type = CreatureType::GreenDragon, .count = 11},
            CreatureStack{.type = CreatureType::RedDragon, .count = 10},
            CreatureStack{.type = CreatureType::GoldDragon, .count = 6},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        },
        .quantity = 200,
        .unknown = ReservedData<4>{}
      };
      static constexpr char kBinaryDataCStr[] =
        "\x01"                                              // has_guardians
          "\x1c\x00\x00\x00" "Ready to fight some dragons?" //   message
          "\x01"                                            //   has_creatures
            "\x53\x00" "\x05\x00"                           //   creatures
            "\x1a\x00" "\x0b\x00"
            "\x52\x00" "\x0a\x00"
            "\x1b\x00" "\x06\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
          "\x00\x00\x00\x00"                                //   unknown
        "\xc8\x00\x00\x00"                                  // quantity
        "\x00\x00\x00\x00";                                 // unknown
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::RESOURCE>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.SCHOLAR", "[H3M]")
  {
    SECTION("Primary skill")
    {
      constexpr ObjectProperties<ObjectPropertiesType::SCHOLAR> kProperties = {
        .reward = PrimarySkillType::SpellPower,
        .unknown = ReservedData<6>{}
      };
      static constexpr char kBinaryDataCStr[] = "\x00" "\x02" "\x00\x00\x00\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SCHOLAR>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Secondary skill")
    {
      constexpr ObjectProperties<ObjectPropertiesType::SCHOLAR> kProperties = {
        .reward = SecondarySkillType::EagleEye,
        .unknown = ReservedData<6>{}
      };
      static constexpr char kBinaryDataCStr[] = "\x01" "\x0b" "\x00\x00\x00\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SCHOLAR>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Spell")
    {
      constexpr ObjectProperties<ObjectPropertiesType::SCHOLAR> kProperties = {
        .reward = SpellType::Armageddon,
        .unknown = ReservedData<6>{}
      };
      static constexpr char kBinaryDataCStr[] = "\x02" "\x1a" "\x00\x00\x00\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SCHOLAR>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("Random")
    {
      constexpr ObjectProperties<ObjectPropertiesType::SCHOLAR> kProperties = {
        .reward = ScholarRandomRewardType::Default,
        .unknown = ReservedData<6>{}
      };
      static constexpr char kBinaryDataCStr[] = "\xff" "\x00" "\x00\x00\x00\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SCHOLAR>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.SeersHut", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::SEERS_HUT> kProperties = {
      .quest = Quest{
        .details = QuestDetails<QuestType::BeHero>{
          .hero = HeroType::Mephala
        },
        .deadline = 28,
        .proposal = "I'm seeking Mephala.",
        .progress = "You're not Mephala.",
        .completion = "Finally!"
      },
      .reward = Reward{
        .details = RewardDetails<RewardType::Spell>{
          .spell = SpellType::ForceField
        }
      },
      .unknown = ReservedData<2>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\x08"                                    // quest_type
      "\x10"                                    //   hero
      "\x1c\x00\x00\x00"                        // deadline
      "\x14\x00\x00\x00" "I'm seeking Mephala." // proposal
      "\x13\x00\x00\x00" "You're not Mephala."  // progress
      "\x08\x00\x00\x00" "Finally!"             // completion
      "\x09"                                    // reward_type
      "\x0c"                                    //   spell
      "\x00\x00";                               // unknown
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::SEERS_HUT>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Shrine", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::SHRINE> kProperties = {
      .spell = SpellType::Slow,
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x36\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::SHRINE>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.Sign", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::SIGN> kProperties = {
      .message = "KEEP OFF THE GRASS",
      .unknown = ReservedData<4>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\x12\x00\x00\x00" "KEEP OFF THE GRASS"
      "\x00\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::SIGN>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.SpellScroll", "[H3M]")
  {
    SECTION("No guardians")
    {
      const ObjectProperties<ObjectPropertiesType::SPELL_SCROLL> kProperties = {
        .guardians = std::nullopt,
        .spell = SpellType::TownPortal,
        .unknown = ReservedData<3>{}
      };
      static constexpr char kBinaryDataCStr[] = "\x00\x09\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SPELL_SCROLL>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
    SECTION("With guardians")
    {
      const ObjectProperties<ObjectPropertiesType::SPELL_SCROLL> kProperties = {
        .guardians = Guardians{
          .message = "Ready to fight some dragons?",
          .creatures = std::array<CreatureStack, 7>{
            CreatureStack{.type = CreatureType::BlackDragon, .count = 5},
            CreatureStack{.type = CreatureType::GreenDragon, .count = 11},
            CreatureStack{.type = CreatureType::RedDragon, .count = 10},
            CreatureStack{.type = CreatureType::GoldDragon, .count = 6},
            CreatureStack{},
            CreatureStack{},
            CreatureStack{}
          },
          .unknown = ReservedData<4>{}
        },
        .spell = SpellType::ForceField,
        .unknown = ReservedData<3>{}
      };
      static constexpr char kBinaryDataCStr[] =
        "\x01"                                              // has_guardians
          "\x1c\x00\x00\x00" "Ready to fight some dragons?" //   message
          "\x01"                                            //   has_creatures
            "\x53\x00" "\x05\x00"                           //   creatures
            "\x1a\x00" "\x0b\x00"
            "\x52\x00" "\x0a\x00"
            "\x1b\x00" "\x06\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
            "\xff\xff" "\x00\x00"
          "\x00\x00\x00\x00"                                //   unknown
        "\x0c"                                              // spell
        "\x00\x00\x00";                                     // unknown
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
      REQUIRE(decodeObjectProperties<ObjectPropertiesType::SPELL_SCROLL>(kBinaryData) == kProperties);
      REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
    }
  }

  TEST_CASE("H3M.ObjectProperties.Town", "[H3M]")
  {
    const ObjectProperties<ObjectPropertiesType::TOWN> kProperties = {
      .absod_id = 1931,
      .owner = PlayerColor::Blue,
      .name = "Innsmouth",
      .garrison = std::array<CreatureStack, 7>{
        CreatureStack{.type = CreatureType::Lizardman, .count = 70},
        CreatureStack{.type = CreatureType::Peasant, .count = 200},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{},
        CreatureStack{}
      },
      .formation = Formation::Grouped,
      .buildings = TownBuildings{
        .is_built = []() consteval {
          TownBuildingsBitmask bitmask;
          bitmask.set(TownBuildingType::Tavern, true);
          bitmask.set(TownBuildingType::Shipyard, true);
          return bitmask;
        }(),
        .is_disabled = []() consteval {
          TownBuildingsBitmask bitmask;
          bitmask.set(TownBuildingType::Grail, true);
          return bitmask;
        }()
      },
      .must_have_spell = []() consteval {
        SpellsBitmask bitmask;
        bitmask.set(SpellType::Sacrifice, true);
        return bitmask;
      }(),
      .may_not_have_spell = []() consteval {
        SpellsBitmask bitmask;
        bitmask.set(SpellType::Bless, true);
        return bitmask;
      }(),
      .events = {
        TownEvent{
          TimedEvent{
            .name = "The Deep Ones",
            .message = "The Deep Ones arrive in Innsmouth.",
            .resources = []() consteval {
              Resources resources;
              resources[ResourceType::Gold] = 500;
              return resources;
            }(),
            .affected_players = []() consteval {
              PlayersBitmask bitmask;
              bitmask.set(PlayerColor::Blue, true);
              return bitmask;
            }(),
            .applies_to_human = 0,
            .applies_to_computer = 1,
            .day_of_first_occurence = 28,
            .repeat_after_days = 100,
            .unknown = ReservedData<16>{}
          },
          /* .buildings = */ TownBuildingsBitmask{},
          /* .creatures = */ std::array<std::uint16_t, 7>{ 0, 5, 0, 0, 0, 0, 0 },
          /* .unknown2 = */ ReservedData<4>{}
        }
      },
      .alignment = 0xFF,
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] =
      "\x8b\x07\x00\x00"                     // absod_id
      "\x01"                                 // owner
      "\x01"                                 // ?name
             "\x09\x00\x00\x00" "Innsmouth"
      "\x01"                                 // ?garrison
             "\x64\x00" "\x46\x00"
             "\x8b\x00" "\xc8\x00"
             "\xff\xff" "\x00\x00"
             "\xff\xff" "\x00\x00"
             "\xff\xff" "\x00\x00"
             "\xff\xff" "\x00\x00"
             "\xff\xff" "\x00\x00"
      "\x01"                                 // formation
      "\x01"                                 // ?buildings
             "\x40\x00\x01\x00\x00\x00"      //   is_built
             "\x00\x00\x02\x00\x00\x00"      //   is_disabled
      "\x00\x00\x00\x00\x00\x01\x00\x00\x00" // must_have_spell
      "\x00\x00\x00\x00\x00\x02\x00\x00\x00" // may_not_have_spell
      "\x01\x00\x00\x00"                     // events
          "\x0d\x00\x00\x00" "The Deep Ones"                      // name
          "\x22\x00\x00\x00" "The Deep Ones arrive in Innsmouth." // message
          "\x00\x00\x00\x00"                                      // resources
          "\x00\x00\x00\x00"
          "\x00\x00\x00\x00"
          "\x00\x00\x00\x00"
          "\x00\x00\x00\x00"
          "\x00\x00\x00\x00"
          "\xf4\x01\x00\x00"
          "\x02"                                                  // affected_players
          "\x00"                                                  // applies_to_human
          "\x01"                                                  // applies_to_computer
          "\x1c\x00"                                              // day_of_first_occurence
          "\x64\x00"                                              // repeat_after_days
          "\x00\x00\x00\x00\x00\x00\x00\x00"                      // unknown
          "\x00\x00\x00\x00\x00\x00\x00\x00"
          "\x00\x00\x00\x00\x00\x00"                              // buildings
          "\x00\x00" "\x05\x00" "\x00\x00" "\x00\x00"             // creatures
          "\x00\x00" "\x00\x00" "\x00\x00"
          "\x00\x00\x00\x00"                                      // unknown2
      "\xff"                                 // alignment
      "\x00\x00\x00";                        // unknown
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::TOWN>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.TrivialOwnedObject", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT> kProperties = {
      .owner = PlayerColor::Green,
      .unknown = ReservedData<3>{}
    };
    static constexpr char kBinaryDataCStr[] = "\x03\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }

  TEST_CASE("H3M.ObjectProperties.WitchHut", "[H3M]")
  {
    constexpr ObjectProperties<ObjectPropertiesType::WITCH_HUT> kProperties = {
      .potential_skills = []() consteval {
        SecondarySkillsBitmask bitmask;
        bitmask.set(SecondarySkillType::AirMagic, true);
        bitmask.set(SecondarySkillType::EarthMagic, true);
        bitmask.set(SecondarySkillType::FireMagic, true);
        bitmask.set(SecondarySkillType::WaterMagic, true);
        return bitmask;
      }()
    };
    static constexpr char kBinaryDataCStr[] = "\x00\xc0\x03\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeObjectProperties(kProperties)) == asByteVector(kBinaryData));
    REQUIRE(decodeObjectProperties<ObjectPropertiesType::WITCH_HUT>(kBinaryData) == kProperties);
    REQUIRE(encodeAndDecodeJson(kProperties) == kProperties);
  }
}
