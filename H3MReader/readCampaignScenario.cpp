#include <h3mtxt/H3MReader/H3Reader.h>

#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    CutScene readCutScene(std::istream& stream)
    {
      CutScene cutscene;
      cutscene.movie = readEnum<CampaignVideo>(stream);
      cutscene.music = readEnum<CampaignMusic>(stream);
      cutscene.message = readString(stream);
      return cutscene;
    }

    CrossoverOptions readCrossoverOptions(std::istream& stream)
    {
      CrossoverOptions options;
      options.retained_features = readEnumBitmask<CrossoverFeature, 1>(stream);
      options.creatures = readEnumBitmask<CreatureType, 19>(stream);
      options.artifacts = readEnumBitmask<ArtifactType, 18>(stream);
      return options;
    }

    StartingOptionsDetails<StartingOptionsType::StartingBonus> readStartingBonusOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
      details.player = readEnum<PlayerColor>(stream);
      const std::uint8_t num_bonuses = readInt<std::uint8_t>(stream);
      details.options.reserve(num_bonuses);
      for (std::uint8_t i = 0; i < num_bonuses; ++i)
      {
        details.options.push_back(readStartingBonus(stream));
      }
      return details;
    }

    StartingOptionsDetails<StartingOptionsType::HeroCrossover> readHeroCrossoverOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
      const std::uint8_t num_heroes = readInt<std::uint8_t>(stream);
      details.options.reserve(num_heroes);
      for (std::uint8_t i = 0; i < num_heroes; ++i)
      {
        StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero hero;
        hero.player = readEnum<PlayerColor>(stream);
        hero.source_scenario = readInt<std::uint8_t>(stream);
        details.options.push_back(std::move(hero));
      }
      return details;
    }

    StartingOptionsDetails<StartingOptionsType::StartingHero> readStartingHeroOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::StartingHero> details;
      const std::uint8_t num_heroes = readInt<std::uint8_t>(stream);
      details.options.reserve(num_heroes);
      for (std::uint8_t i = 0; i < num_heroes; ++i)
      {
        StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero hero;
        hero.player = readEnum<PlayerColor>(stream);
        hero.type = readInt<std::uint16_t>(stream);
        details.options.push_back(std::move(hero));
      }
      return details;
    }

    StartingOptions readStartingOptions(std::istream& stream)
    {
      const StartingOptionsType starting_options_type = readEnum<StartingOptionsType>(stream);
      switch (starting_options_type)
      {
      case StartingOptionsType::None:
        return StartingOptionsDetails<StartingOptionsType::None>{};
      case StartingOptionsType::StartingBonus:
        return readStartingBonusOptions(stream);
      case StartingOptionsType::HeroCrossover:
        return readHeroCrossoverOptions(stream);
      case StartingOptionsType::StartingHero:
        return readStartingHeroOptions(stream);
      default:
        throw std::runtime_error("Invalid starting_options_type.");
      }
    }
  }

  CampaignScenario readCampaignScenario(std::istream& stream, CampaignId campaign_id)
  {
    CampaignScenario scenario;
    scenario.map_filename = readString(stream);
    scenario.compressed_map_size = readInt<std::uint32_t>(stream);
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
    scenario.region_righ_click_text = readString(stream);
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
