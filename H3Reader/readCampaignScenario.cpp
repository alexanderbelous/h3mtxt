#include <h3mtxt/H3Reader/H3Reader.h>

#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>
#include <h3mtxt/H3Reader/Utils.h>

#include <stdexcept>

namespace h3m::H3Reader_NS
{
  CrossoverOptions readCrossoverOptions(std::istream& stream)
  {
    CrossoverOptions options;
    options.retained_features = readEnumBitmask<CrossoverFeature, 1>(stream);
    options.creatures = readEnumBitmask<CreatureType, 19>(stream);
    options.artifacts = readEnumBitmask<ArtifactType, 18>(stream);
    return options;
  }

  CutScene readCutScene(std::istream& stream)
  {
    CutScene cutscene;
    cutscene.movie = readEnum<CampaignVideo>(stream);
    cutscene.music = readEnum<CampaignMusic>(stream);
    cutscene.message = readString(stream);
    return cutscene;
  }

  CampaignScenario readCampaignScenario(std::istream& stream, CampaignId campaign_id)
  {
    CampaignScenario scenario;
    scenario.map_filename = readString(stream);
    scenario.map_file_size = readInt<std::uint32_t>(stream);
    if (campaign_id == CampaignId::UnholyAlliance)
    {
      scenario.prerequisites = readBitSet<2>(stream);
    }
    else
    {
      scenario.prerequisites.data[0] = readInt<std::uint8_t>(stream);
    }
    scenario.region_color = readEnum<RegionColor>(stream);
    scenario.default_difficulty = readEnum<MapDifficulty>(stream);
    scenario.region_right_click_text = readString(stream);
    if (const bool has_prologue = readBool(stream))
    {
      scenario.prologue = readCutScene(stream);
    }
    if (const bool has_epilogue = readBool(stream))
    {
      scenario.epilogue = readCutScene(stream);
    }
    scenario.crossover_options = readCrossoverOptions(stream);
    scenario.starting_options = readStartingOptions(stream);
    return scenario;
  }
}
