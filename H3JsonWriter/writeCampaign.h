#pragma once

#include <h3mtxt/Campaign/Campaign.h>
#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/writeStartingOptions.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::CutScene>
  {
    void operator()(FieldsWriter& out, const h3m::CutScene& cutscene) const
    {
      out.writeField("movie", cutscene.movie);
      out.writeField("music", cutscene.music);
      out.writeField("message", cutscene.message);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::CrossoverOptions>
  {
    void operator()(FieldsWriter& out, const h3m::CrossoverOptions& cutscene) const
    {
      out.writeField("retained_features", cutscene.retained_features.bitset);
      out.writeField("creatures", cutscene.creatures.bitset);
      out.writeField("artifacts", cutscene.artifacts);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::CampaignScenario>
  {
    void operator()(FieldsWriter& out, const h3m::CampaignScenario& scenario) const
    {
      out.writeField("map_filename", scenario.map_filename);
      out.writeField("compressed_map_size", scenario.compressed_map_size);
      out.writeField("prerequisites", scenario.prerequisites);
      out.writeField("region_color", scenario.region_color);
      out.writeField("default_difficulty", scenario.default_difficulty);
      out.writeField("region_righ_click_text", scenario.region_righ_click_text);
      if (scenario.prologue)
      {
        out.writeField("prologue", *scenario.prologue);
      }
      if (scenario.epilogue)
      {
        out.writeField("epilogue", *scenario.epilogue);
      }
      out.writeField("crossover_options", scenario.crossover_options);
      out.writeField("starting_options", scenario.starting_options);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::CampaignHeader>
  {
    void operator()(FieldsWriter& out, const h3m::CampaignHeader& campaign) const
    {
      out.writeField("format", campaign.format);
      out.writeField("id", campaign.id);
      out.writeField("name", campaign.name);
      out.writeField("description", campaign.description);
      out.writeField("allow_selecting_difficulty", campaign.allow_selecting_difficulty);
      out.writeField("scenarios", campaign.scenarios);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::Campaign>
  {
    void operator()(FieldsWriter& out, const h3m::Campaign& campaign) const
    {
      out.writeField("header", campaign.header);
      out.writeField("maps", campaign.maps);
    }
  };
}
