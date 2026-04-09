#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/PlayerSpecs.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace h3m
{
  namespace
  {
    // Encodes h3m::MainTown via H3MWriter.
    // \param main_town - input MainTown.
    // \return std::string storing the encoded data.
    std::string encodeMainTown(const MainTown& main_town)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(main_town);
      return std::move(stream).str();
    }

    // Decodes h3m::MainTown via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::MainTown decoded from @encoded_data.
    MainTown decodeMainTown(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readMainTown();
    }

    // Encodes h3m::StartingHero via H3MWriter.
    // \param starting_hero - input StartingHero.
    // \return std::string storing the encoded data.
    std::string encodeStartingHero(const StartingHero& starting_hero)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(starting_hero);
      return std::move(stream).str();
    }

    // Decodes h3m::StartingHero via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::StartingHero decoded from @encoded_data.
    StartingHero decodeStartingHero(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readStartingHero();
    }

    // Encodes h3m::PlayerSpecs via H3MWriter.
    // \param player_specs - input PlayerSpecs.
    // \return std::string storing the encoded data.
    std::string encodePlayerSpecs(const PlayerSpecs& player_specs)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(player_specs);
      return std::move(stream).str();
    }

    // Decodes h3m::PlayerSpecs via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::PlayerSpecs decoded from @encoded_data.
    PlayerSpecs decodePlayerSpecs(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readPlayerSpecs();
    }
  }

  TEST_CASE("H3M.MainTown", "[H3M]")
  {
    constexpr MainTown kMainTown = {
      .generate_hero = 1,
      .town_type = TownType::Dungeon,
      .coordinates{.x = 70, .y = 24, .z = 1}
    };
    static constexpr char kBinaryDataCStr[] = "\x01\x05\x46\x18\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(encodeMainTown(kMainTown) == kBinaryData);
    REQUIRE(decodeMainTown(kBinaryData) == kMainTown);
  }

  TEST_CASE("H3M.StartingHero", "[H3M]")
  {
    SECTION("None")
    {
      const StartingHero kStartingHero = { .type = static_cast<HeroType>(-1) };
      constexpr std::string_view kBinaryData = "\xff";
      REQUIRE(encodeStartingHero(kStartingHero) == kBinaryData);
      REQUIRE(decodeStartingHero(kBinaryData) == kStartingHero);
    }
    SECTION("Not None")
    {
      const StartingHero kStartingHero = {
        .type = HeroType::Mutare,
        .portrait = HeroPortrait::Mephala,
        .name = "Jessica"
      };
      static constexpr char kBinaryDataCStr[] = "\x97\x10\x07\x00\x00\x00Jessica";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeStartingHero(kStartingHero) == kBinaryData);
      REQUIRE(decodeStartingHero(kBinaryData) == kStartingHero);
    }
  }

  TEST_CASE("H3M.PlayerSpecs", "[H3M]")
  {
    const PlayerSpecs kPlayerSpecs = {
      .can_be_human = 1,
      .can_be_computer = 1,
      .behavior = PlayerBehavior::Random,
      .has_customized_alignments = 1,
      .allowed_alignments = []() consteval {
        TownsBitmask bitmask;
        bitmask.set(TownType::Rampart, true);
        bitmask.set(TownType::Dungeon, true);
        return bitmask;
      }(),
      .allow_random_alignment = 0,
      .main_town = MainTown{
        .generate_hero = 1,
        .town_type = TownType::Random,
        .coordinates {.x = 44, .y = 12, .z = 1}
      },
      .has_random_heroes = 0,
      .starting_hero {
        .type = HeroType::Mutare,
        .portrait = HeroPortrait::Mephala,
        .name = "Jessica"
      },
      .num_nonspecific_placeholder_heroes = 0,
      .heroes = {
        PlayerSpecs::HeroInfo{.type = HeroType::Mutare, .name = "Jessica"},
        PlayerSpecs::HeroInfo{.type = HeroType::Orrin, .name = ""},
      }
    };
    static constexpr char kBinaryDataCStr[] =
      "\x01"                                                                   // can_be_human
      "\x01"                                                                   // can_be_computer
      "\x00"                                                                   // behavior
      "\x01"                                                                   // has_customized_alignments
      "\x22\x00"                                                               // allowed_alignments
      "\x00"                                                                   // allow_random_alignment
      "\x01"                                                                   // has_main_town
      "\x01" "\xff" "\x2c\x0c\x01"                                             // ?main_town
      "\x00"                                                                   // has_random_heroes
      "\x97\x10\x07\x00\x00\x00Jessica"                                        // starting_hero
      "\x00"                                                                   // num_nonspecific_placeholder_heroes
      "\x02\x00\x00\x00" "\x97\x07\x00\x00\x00Jessica" "\x00\x00\x00\x00\x00"; // heroes
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(encodePlayerSpecs(kPlayerSpecs) == kBinaryData);
    REQUIRE(decodePlayerSpecs(kBinaryData) == kPlayerSpecs);
  }
}
