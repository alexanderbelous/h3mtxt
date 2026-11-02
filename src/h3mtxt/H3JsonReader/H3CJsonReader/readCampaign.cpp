#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/Campaign/Campaign.h>

namespace h3json
{
  template<>
  h3m::Campaign JsonReader2<h3m::Campaign>::operator()() const
  {
    using Fields = FieldNames<h3m::Campaign>;
    h3m::Campaign campaign;
    readField(Fields::kHeader, campaign.header);
    readField(Fields::kMaps, campaign.maps);
    return campaign;
  }

  template<>
  h3m::CampaignHeader JsonReader2<h3m::CampaignHeader>::operator()() const
  {
    using Fields = FieldNames<h3m::CampaignHeader>;
    h3m::CampaignHeader header;
    readField(Fields::kFormat, header.format);
    readField(Fields::kId, header.id);
    readField(Fields::kName, header.name);
    readField(Fields::kDescription, header.description);
    readField(Fields::kAllowSelectingDifficulty, header.allow_selecting_difficulty);
    readField(Fields::kThemeMusic, header.theme_music);
    readField(Fields::kScenarios, header.scenarios);
    return header;
  }

  template<>
  h3m::CampaignScenario JsonReader2<h3m::CampaignScenario>::operator()() const
  {
    using Fields = FieldNames<h3m::CampaignScenario>;
    h3m::CampaignScenario scenario;
    readField(Fields::kMapFilename, scenario.map_filename);
    readField(Fields::kMapFileSize, scenario.map_file_size);
    readField(Fields::kPrerequisites, scenario.prerequisites);
    readField(Fields::kRegionColor, scenario.region_color);
    readField(Fields::kDefaultDifficulty, scenario.default_difficulty);
    readField(Fields::kRegionRightClickText, scenario.region_right_click_text);
    readField(Fields::kPrologue, scenario.prologue);
    readField(Fields::kEpilogue, scenario.epilogue);
    readField(Fields::kCrossoverOptions, scenario.crossover_options);
    readField(Fields::kStartingOptions, scenario.starting_options);
    return scenario;
  }

  template<>
  h3m::CrossoverOptions JsonReader2<h3m::CrossoverOptions>::operator()() const
  {
    using Fields = FieldNames<h3m::CrossoverOptions>;
    h3m::CrossoverOptions options;
    readField(Fields::kRetainedFeatures, options.retained_features);
    readField(Fields::kCreatures, options.creatures.bitset);
    readField(Fields::kArtifacts, options.artifacts);
    return options;
  }

  template<>
  h3m::CutScene JsonReader2<h3m::CutScene>::operator()() const
  {
    using Fields = FieldNames<h3m::CutScene>;
    h3m::CutScene cutscene;
    readField(Fields::kMovie, cutscene.movie);
    readField(Fields::kMusic, cutscene.music);
    readField(Fields::kMessage, cutscene.message);
    return cutscene;
  }
}
