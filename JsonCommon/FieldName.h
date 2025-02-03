#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <array>
#include <string_view>

namespace h3m
{
  // Stores the names of JSON fields for the specified class.
  // This is to ensure that H3MJsonWriter and H3MJsonReader use the same names:
  // * A typo in a string will only be discovered at runtime, but a typo in a static
  //   data member will cause a compilation error.
  // * This should also guarantee that these strings are only stored once in the binary.
  template<class T>
  struct FieldNames;

  template<>
  struct FieldNames<PlayersBitmask>
  {
  private:
    static inline constexpr std::array<std::string_view, 8> kPlayersNames = {
      "red", "blue", "tan", "green", "orange", "purple", "teal", "pink"
    };

  public:
    // Returns the name of the field for the specified player in PlayersBitmask.
    //
    // PlayersBitmask is stored as 1 byte in .h3m, but in JSON it's serialized as
    // 8 boolean fields (1 per player).
    // \param player - input PlayerColor.
    // \return the name of the field for @player in PlayersBitmask.
    // \throw std::out_of_range if int(player) >= 8.
    static constexpr std::string_view get(PlayerColor player)
    {
      return kPlayersNames.at(static_cast<std::size_t>(player));
    }
  };

  template<>
  struct FieldNames<Map>
  {
    static inline constexpr std::string_view kFormat = "format";
    static inline constexpr std::string_view kBasicInfo = "basic_info";
    static inline constexpr std::string_view kPlayers = "players";
    static inline constexpr std::string_view kAdditionalInfo = "additional_info";
    static inline constexpr std::string_view kTiles = "tiles";
    static inline constexpr std::string_view kObjectsAttributes = "objects_attributes";
    static inline constexpr std::string_view kObjectsDetails = "objects_details";
    static inline constexpr std::string_view kGlobalEvents = "global_events";
    static inline constexpr std::string_view kPadding = "padding";
  };
}
