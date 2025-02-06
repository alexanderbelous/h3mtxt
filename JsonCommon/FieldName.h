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
  struct FieldNames<HeroSettings>
  {
    static inline constexpr std::string_view kExperience = "experience";
    static inline constexpr std::string_view kSecondarySkills = "secondary_skills";
    static inline constexpr std::string_view kArtifacts = "artifacts";
    static inline constexpr std::string_view kBiography = "biography";
    static inline constexpr std::string_view kGender = "gender";
    static inline constexpr std::string_view kSpells = "spells";
    static inline constexpr std::string_view kPrimarySkills = "primary_skills";
  };

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

  template<>
  struct FieldNames<MapAdditionalInfo>
  {
    static inline constexpr std::string_view kVictoryCondition = "victory_condition";
    static inline constexpr std::string_view kLossCondition = "loss_condition";
    static inline constexpr std::string_view kTeams = "teams";
    static inline constexpr std::string_view kHeroesAvailability = "heroes_availability";
    static inline constexpr std::string_view kPlaceholderHeroes = "placeholder_heroes";
    static inline constexpr std::string_view kCustomHeroes = "custom_heroes";
    static inline constexpr std::string_view kReserved = "reserved";
    static inline constexpr std::string_view kArtifactsNonavailability = "artifacts_nonavailability";
    static inline constexpr std::string_view kDisabledSpells = "disabled_spells";
    static inline constexpr std::string_view kDisabledSkills = "disabled_skills";
    static inline constexpr std::string_view kRumors = "rumors";
    static inline constexpr std::string_view kHeroesSettings = "heroes_settings";
  };

  template<>
  struct FieldNames<SecondarySkillsBitmask>
  {
    // The number of bit fields in SecondarySkillsBitmask.
    static constexpr std::size_t kNumBits = 32;
    // Name for each bit field in SecondarySkillsBitmask.
    static inline constexpr std::array<std::string_view, kNumBits> kNames{
        "pathfinding",
        "archery",
        "logistics",
        "scouting",
        "diplomacy",
        "navigation",
        "leadership",
        "wisdom",
        "mysticism",
        "luck",
        "ballistics",
        "eagle_eye",
        "necromancy",
        "estates",
        "fire_magic",
        "air_magic",
        "water_magic",
        "earth_magic",
        "scholar",
        "tactics",
        "artillery",
        "learning",
        "offense",
        "armorer",
        "intelligence",
        "sorcery",
        "resistance",
        "first_aid",
        "padding_28",
        "padding_29",
        "padding_30",
        "padding_31"
    };
  };
}
