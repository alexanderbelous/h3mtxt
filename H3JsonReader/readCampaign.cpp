#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/Campaign.h>

namespace h3m::H3JsonReader_NS
{
  Campaign JsonReader<Campaign>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Campaign>;
    Campaign campaign;
    readField(campaign.header, value, Fields::kHeader);
    readField(campaign.maps, value, Fields::kMaps);
    return campaign;
  }

  CampaignHeader JsonReader<CampaignHeader>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CampaignHeader>;
    CampaignHeader header;
    readField(header.format, value, Fields::kFormat);
    readField(header.id, value, Fields::kId);
    readField(header.name, value, Fields::kName);
    readField(header.description, value, Fields::kDescription);
    readField(header.allow_selecting_difficulty, value, Fields::kAllowSelectingDifficulty);
    readField(header.theme_music, value, Fields::kThemeMusic);
    readField(header.scenarios, value, Fields::kScenarios);
    return header;
  }

  CampaignScenario JsonReader<CampaignScenario>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CampaignScenario>;
    CampaignScenario scenario;
    readField(scenario.map_filename, value, Fields::kMapFilename);
    readField(scenario.map_file_size, value, Fields::kMapFileSize);
    readField(scenario.prerequisites, value, Fields::kPrerequisites);
    readField(scenario.region_color, value, Fields::kRegionColor);
    readField(scenario.default_difficulty, value, Fields::kDefaultDifficulty);
    readField(scenario.region_righ_click_text, value, Fields::kRegionRightClickText);
    readField(scenario.prologue, value, Fields::kPrologue);
    readField(scenario.epilogue, value, Fields::kEpilogue);
    readField(scenario.crossover_options, value, Fields::kCrossoverOptions);
    readField(scenario.starting_options, value, Fields::kStartingOptions);
    return scenario;
  }

  CrossoverOptions JsonReader<CrossoverOptions>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CrossoverOptions>;
    CrossoverOptions options;
    readField(options.retained_features, value, Fields::kRetainedFeatures);
    readField(options.creatures.bitset, value, Fields::kCreatures);
    readField(options.artifacts, value, Fields::kArtifacts);
    return options;
  }

  CutScene JsonReader<CutScene>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CutScene>;
    CutScene cutscene;
    readField(cutscene.movie, value, Fields::kMovie);
    readField(cutscene.music, value, Fields::kMusic);
    readField(cutscene.message, value, Fields::kMessage);
    return cutscene;
  }
}
