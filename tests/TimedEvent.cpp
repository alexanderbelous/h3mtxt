#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/TimedEvent.h>

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
    // Encodes h3m::TimedEvent via H3MWriter.
    // \param timed_event - input TimedEvent.
    // \return std::string storing the encoded data.
    std::string encodeTimedEvent(const TimedEvent& timed_event)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(timed_event);
      return std::move(stream).str();
    }

    // Decodes h3m::TimedEvent via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::TimedEvent decoded from @encoded_data.
    TimedEvent decodeTimedEvent(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readTimedEvent();
    }
  }

  TEST_CASE("H3M.TimedEvent", "[H3M]")
  {
    const TimedEvent kTimedEvent
    {
      .name = "Resources for Red",
      .message = "Enjoy!",
      .resources {1, 2, 3, 4, 5, 6, 7}, // Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold
      .affected_players = []() consteval {
        PlayersBitmask bitmask;
        bitmask.set(PlayerColor::Red, true);
        return bitmask;
      }(),
      .applies_to_human = 1,
      .applies_to_computer = 0,
      .day_of_first_occurence = 7, // Month: 1; Week: 2; Day: 1
      .repeat_after_days = 28,     // Every month
      .unknown = ReservedData<16>{}
    };
    // The binary representation of kTimedEvent.
    static constexpr char kBinaryDataCStr[] =
      "\x11\x00\x00\x00" "Resources for Red"                              // name
      "\x06\x00\x00\x00" "Enjoy!"                                         // message
      "\x01\x00\x00\x00" "\x02\x00\x00\x00" "\x03\x00\x00\x00"            // resources
                         "\x04\x00\x00\x00" "\x05\x00\x00\x00"
                         "\x06\x00\x00\x00" "\x07\x00\x00\x00"
      "\x01"                                                              // affected_players
      "\x01"                                                              // applies_to_human
      "\x00"                                                              // applies_to_computer
      "\x07\x00"                                                          // day_of_first_occurence
      "\x1c\x00"                                                          // repeat_after_days
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; // unknown
    // std::string_view into kBinaryDataCStr.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeTimedEvent(kTimedEvent)) == asByteVector(kBinaryData));
    REQUIRE(decodeTimedEvent(kBinaryData) == kTimedEvent);
    REQUIRE(encodeAndDecodeJson(kTimedEvent) == kTimedEvent);
  }
}
