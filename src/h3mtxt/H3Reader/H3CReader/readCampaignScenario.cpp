#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>

#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>

namespace h3m
{
  CrossoverOptions H3CReader::readCrossoverOptions() const
  {
    CrossoverOptions options;
    options.retained_features = readEnumBitmask<CrossoverFeature, 1>();
    options.creatures = readEnumBitmask<CreatureType, 19>();
    options.artifacts = readEnumBitmask<ArtifactType, 18>();
    return options;
  }

  CutScene H3CReader::readCutScene() const
  {
    CutScene cutscene;
    cutscene.movie = readEnum<CampaignVideo>();
    cutscene.music = readEnum<CampaignMusic>();
    cutscene.message = readString32();
    return cutscene;
  }

  CampaignScenario H3CReader::readCampaignScenario(CampaignId campaign_id) const
  {
    CampaignScenario scenario;
    scenario.map_filename = readString32();
    scenario.map_file_size = readInt<std::uint32_t>();
    if (campaign_id == CampaignId::UnholyAlliance)
    {
      scenario.prerequisites = readBitSet<2>();
    }
    else
    {
      scenario.prerequisites.data[0] = readInt<std::uint8_t>();
    }
    scenario.region_color = readEnum<RegionColor>();
    scenario.default_difficulty = readEnum<MapDifficulty>();
    scenario.region_right_click_text = readString32();
    if (const bool has_prologue = readBool())
    {
      scenario.prologue = readCutScene();
    }
    if (const bool has_epilogue = readBool())
    {
      scenario.epilogue = readCutScene();
    }
    scenario.crossover_options = readCrossoverOptions();
    scenario.starting_options = readStartingOptions();
    return scenario;
  }
}
