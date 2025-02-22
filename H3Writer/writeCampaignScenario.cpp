#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<CrossoverOptions>::operator()(std::ostream& stream, const CrossoverOptions& options) const
  {
    writeData(stream, options.retained_features);
    writeData(stream, options.creatures);
    writeData(stream, options.artifacts);
  }

  void H3Writer<CutScene>::operator()(std::ostream& stream, const CutScene& cutscene) const
  {
    writeData(stream, cutscene.movie);
    writeData(stream, cutscene.music);
    writeData(stream, cutscene.message);
  }

  void writeCampaignScenario(std::ostream& stream,
                             const CampaignScenario& scenario,
                             CampaignId campaign_id,
                             std::uint32_t compressed_map_size)
  {
    writeData(stream, scenario.map_filename);
    writeData(stream, compressed_map_size);
    if (campaign_id == CampaignId::UnholyAlliance)
    {
      writeData(stream, scenario.prerequisites);
    }
    else
    {
      writeData(stream, scenario.prerequisites.data[0]);
    }
    writeData(stream, scenario.region_color);
    writeData(stream, scenario.default_difficulty);
    writeData(stream, scenario.region_righ_click_text);
    writeData(stream, scenario.prologue);
    writeData(stream, scenario.epilogue);
    writeData(stream, scenario.crossover_options);
    writeData(stream, scenario.starting_options);
  }
}
