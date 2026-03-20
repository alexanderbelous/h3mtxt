#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>

namespace h3m
{
  void H3CWriter::writeData(const CrossoverOptions& options) const
  {
    writeData(options.retained_features);
    writeData(options.creatures);
    writeData(options.artifacts);
  }

  void H3CWriter::writeData(const CutScene& cutscene) const
  {
    writeData(cutscene.movie);
    writeData(cutscene.music);
    writeData(cutscene.message);
  }

  void H3CWriter::writeCampaignScenario(const CampaignScenario& scenario,
                                        CampaignId campaign_id,
                                        std::uint32_t map_file_size) const
  {
    writeData(scenario.map_filename);
    writeData(map_file_size);
    if (campaign_id == CampaignId::UnholyAlliance)
    {
      writeData(scenario.prerequisites);
    }
    else
    {
      writeData(scenario.prerequisites.data[0]);
    }
    writeData(scenario.region_color);
    writeData(scenario.default_difficulty);
    writeData(scenario.region_right_click_text);
    writeData(scenario.prologue);
    writeData(scenario.epilogue);
    writeData(scenario.crossover_options);
    writeData(scenario.starting_options);
  }
}
