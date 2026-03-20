#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/Campaign/Campaign.h>

namespace h3json
{
  h3m::Campaign JsonReader<h3m::Campaign>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Campaign>;
    h3m::Campaign campaign;
    readField(campaign.header, value, Fields::kHeader);
    readField(campaign.maps, value, Fields::kMaps);
    return campaign;
  }

  h3m::CampaignHeader JsonReader<h3m::CampaignHeader>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CampaignHeader>;
    h3m::CampaignHeader header;
    readField(header.format, value, Fields::kFormat);
    readField(header.id, value, Fields::kId);
    readField(header.name, value, Fields::kName);
    readField(header.description, value, Fields::kDescription);
    readField(header.allow_selecting_difficulty, value, Fields::kAllowSelectingDifficulty);
    readField(header.theme_music, value, Fields::kThemeMusic);
    readField(header.scenarios, value, Fields::kScenarios);
    return header;
  }

  h3m::CampaignScenario JsonReader<h3m::CampaignScenario>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CampaignScenario>;
    h3m::CampaignScenario scenario;
    readField(scenario.map_filename, value, Fields::kMapFilename);
    readField(scenario.map_file_size, value, Fields::kMapFileSize);
    readField(scenario.prerequisites, value, Fields::kPrerequisites);
    readField(scenario.region_color, value, Fields::kRegionColor);
    readField(scenario.default_difficulty, value, Fields::kDefaultDifficulty);
    readField(scenario.region_right_click_text, value, Fields::kRegionRightClickText);
    readField(scenario.prologue, value, Fields::kPrologue);
    readField(scenario.epilogue, value, Fields::kEpilogue);
    readField(scenario.crossover_options, value, Fields::kCrossoverOptions);
    readField(scenario.starting_options, value, Fields::kStartingOptions);
    return scenario;
  }

  h3m::CrossoverOptions JsonReader<h3m::CrossoverOptions>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CrossoverOptions>;
    h3m::CrossoverOptions options;
    readField(options.retained_features, value, Fields::kRetainedFeatures);
    readField(options.creatures.bitset, value, Fields::kCreatures);
    readField(options.artifacts, value, Fields::kArtifacts);
    return options;
  }

  h3m::CutScene JsonReader<h3m::CutScene>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CutScene>;
    h3m::CutScene cutscene;
    readField(cutscene.movie, value, Fields::kMovie);
    readField(cutscene.music, value, Fields::kMusic);
    readField(cutscene.message, value, Fields::kMessage);
    return cutscene;
  }
}
