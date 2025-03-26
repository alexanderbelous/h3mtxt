#include <h3mtxt/Campaign/Campaign.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::Campaign>::operator()(FieldsWriter& out, const h3m::Campaign& campaign) const
  {
    using Fields = h3m::FieldNames<h3m::Campaign>;
    out.writeField(Fields::kHeader, campaign.header);
    out.writeField(Fields::kMaps, campaign.maps);
  }

  void JsonObjectWriter<h3m::CampaignHeader>::operator()(FieldsWriter& out, const h3m::CampaignHeader& campaign) const
  {
    using Fields = h3m::FieldNames<h3m::CampaignHeader>;
    out.writeField(Fields::kFormat, campaign.format);
    out.writeField(Fields::kId, campaign.id);
    if (std::string_view enum_str = h3m::getEnumString(campaign.id); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kName, campaign.name);
    out.writeField(Fields::kDescription, campaign.description);
    out.writeField(Fields::kThemeMusic, campaign.theme_music);
    if (std::string_view enum_str = h3m::getEnumString(campaign.theme_music); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kAllowSelectingDifficulty, campaign.allow_selecting_difficulty);
    out.writeField(Fields::kScenarios, campaign.scenarios);
  }

  void JsonObjectWriter<h3m::CampaignScenario>::operator()(FieldsWriter& out, const h3m::CampaignScenario& scenario) const
  {
    using Fields = h3m::FieldNames<h3m::CampaignScenario>;
    out.writeField(Fields::kMapFilename, scenario.map_filename);
    out.writeField(Fields::kMapFileSize, scenario.map_file_size);
    out.writeField(Fields::kPrerequisites, scenario.prerequisites);
    out.writeField(Fields::kRegionColor, scenario.region_color);
    out.writeField(Fields::kDefaultDifficulty, scenario.default_difficulty);
    out.writeField(Fields::kRegionRightClickText, scenario.region_righ_click_text);
    if (scenario.prologue)
    {
      out.writeField(Fields::kPrologue, *scenario.prologue);
    }
    if (scenario.epilogue)
    {
      out.writeField(Fields::kEpilogue, *scenario.epilogue);
    }
    out.writeField(Fields::kCrossoverOptions, scenario.crossover_options);
    out.writeField(Fields::kStartingOptions, scenario.starting_options);
  }

  void JsonObjectWriter<h3m::CrossoverOptions>::operator()(FieldsWriter& out, const h3m::CrossoverOptions& cutscene) const
  {
    using Fields = h3m::FieldNames<h3m::CrossoverOptions>;
    out.writeField(Fields::kRetainedFeatures, cutscene.retained_features);
    out.writeField(Fields::kCreatures, cutscene.creatures.bitset);
    out.writeField(Fields::kArtifacts, cutscene.artifacts);
  }

  void JsonObjectWriter<h3m::CutScene>::operator()(FieldsWriter& out, const h3m::CutScene& cutscene) const
  {
    using Fields = h3m::FieldNames<h3m::CutScene>;
    out.writeField(Fields::kMovie, cutscene.movie);
    out.writeField(Fields::kMusic, cutscene.music);
    if (std::string_view enum_str = h3m::getEnumString(cutscene.music); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kMessage, cutscene.message);
  }
}
