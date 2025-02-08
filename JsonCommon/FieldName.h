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
  struct FieldNames<MapBasicInfo>
  {
    static inline constexpr std::string_view kIsPlayable = "is_playable";
    static inline constexpr std::string_view kMapSize = "map_size";
    static inline constexpr std::string_view kHasTwoLevels = "has_two_levels";
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kDescription = "description";
    static inline constexpr std::string_view kDifficulty = "difficulty";
    static inline constexpr std::string_view kMaxHeroLevel = "max_hero_level";
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
  struct FieldNames<ObjectAttributes>
  {
    static inline constexpr std::string_view kDef = "def";
    static inline constexpr std::string_view kPassability = "passability";
    static inline constexpr std::string_view kActionability = "actionability";
    static inline constexpr std::string_view kAllowedLandscapes = "allowed_landscapes";
    static inline constexpr std::string_view kLandscapeGroup = "landscape_group";
    static inline constexpr std::string_view kObjectClass = "object_class";
    static inline constexpr std::string_view kObjectNumber = "object_number";
    static inline constexpr std::string_view kObjectGroup = "object_group";
    static inline constexpr std::string_view kIsGround = "is_ground";
    static inline constexpr std::string_view kUnknown = "unknown";
  };

  template<>
  struct FieldNames<PlayerSpecs>
  {
    static inline constexpr std::string_view kCanBeHuman = "can_be_human";
    static inline constexpr std::string_view kCanBeComputer = "can_be_computer";
    static inline constexpr std::string_view kBehavior = "behavior";
    static inline constexpr std::string_view kCustomizedAlignments = "customized_alignments";
    static inline constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static inline constexpr std::string_view kRandomTown = "random_town";
    static inline constexpr std::string_view kMainTown = "main_town";
    static inline constexpr std::string_view kStartingHero = "starting_hero";
    static inline constexpr std::string_view kAdditionalInfo = "additional_info";
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
  struct FieldNames<PrimarySkills>
  {
    static inline constexpr std::string_view kAttack = "attack";
    static inline constexpr std::string_view kDefense = "defense";
    static inline constexpr std::string_view kSpellPower = "spell_power";
    static inline constexpr std::string_view kKnowledge = "knowledge";
  };

  template<>
  struct FieldNames<Rumor>
  {
    static inline constexpr std::string_view kName = "name";
    static inline constexpr std::string_view kDescription = "description";
  };

  template<>
  struct FieldNames<SecondarySkill>
  {
    static inline constexpr std::string_view kType = "type";
    static inline constexpr std::string_view kLevel = "level";
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

  template<>
  struct FieldNames<TeamsInfo>
  {
    static inline constexpr std::string_view kNumTeams = "num_teams";
    static inline constexpr std::string_view kTeamForPlayer = "team_for_player";
  };

  template<>
  struct FieldNames<Tile>
  {
    static inline constexpr std::string_view kTerrainType = "terrain_type";
    static inline constexpr std::string_view kTerrainSprite = "terrain_sprite";
    static inline constexpr std::string_view kRiverType = "river_type";
    static inline constexpr std::string_view kRiverSprite = "river_sprite";
    static inline constexpr std::string_view kRoadType = "road_type";
    static inline constexpr std::string_view kRoadSprite = "road_sprite";
    static inline constexpr std::string_view kMirroring = "mirroring";
  };
}
