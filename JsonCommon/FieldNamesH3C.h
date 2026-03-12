#pragma once

// Names of JSON fields for various types used in Campaign library.

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <h3mtxt/Campaign/CampaignFwd.h>

#include <array>
#include <string_view>

namespace h3json
{
  template<>
  inline constexpr std::array<std::string_view, 8> kEnumFieldNames<h3m::CrossoverFeature> =
  {
    "experience",
    "primary_skills",
    "secondary_skills",
    "spells",
    "artifacts",
    "padding_5",
    "padding_6",
    "padding_7"
  };
}

namespace h3m
{
  template<>
  struct FieldNames<Campaign>
  {
    static constexpr std::string_view kHeader = "header";
    static constexpr std::string_view kMaps = "maps";
  };

  template<>
  struct FieldNames<CampaignHeader>
  {
    static constexpr std::string_view kFormat = "format";
    static constexpr std::string_view kId = "id";
    static constexpr std::string_view kName = "name";
    static constexpr std::string_view kDescription = "description";
    static constexpr std::string_view kAllowSelectingDifficulty = "allow_selecting_difficulty";
    static constexpr std::string_view kThemeMusic = "theme_music";
    static constexpr std::string_view kScenarios = "scenarios";
  };

  template<>
  struct FieldNames<CampaignScenario>
  {
    static constexpr std::string_view kMapFilename = "map_filename";
    static constexpr std::string_view kMapFileSize = "map_file_size";
    static constexpr std::string_view kPrerequisites = "prerequisites";
    static constexpr std::string_view kRegionColor = "region_color";
    static constexpr std::string_view kDefaultDifficulty = "default_difficulty";
    static constexpr std::string_view kRegionRightClickText = "region_right_click_text";
    static constexpr std::string_view kPrologue = "prologue";
    static constexpr std::string_view kEpilogue = "epilogue";
    static constexpr std::string_view kCrossoverOptions = "crossover_options";
    static constexpr std::string_view kStartingOptions = "starting_options";
  };

  template<>
  struct FieldNames<CrossoverOptions>
  {
    static constexpr std::string_view kRetainedFeatures = "retained_features";
    static constexpr std::string_view kCreatures = "creatures";
    static constexpr std::string_view kArtifacts = "artifacts";
  };

  template<>
  struct FieldNames<CutScene>
  {
    static constexpr std::string_view kMovie = "movie";
    static constexpr std::string_view kMusic = "music";
    static constexpr std::string_view kMessage = "message";
  };

  template<>
  struct FieldNames<StartingBonus>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };

  template<>
  struct FieldNames<StartingOptions>
  {
    static constexpr std::string_view kType = "type";
    static constexpr std::string_view kDetails = "details";
  };
}
