#include <h3mtxt/H3MReader/parseh3c.h>

#include <h3mtxt/H3MReader/Utils.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
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
      options.retained_features = readEnum<std::byte>(stream);
      options.creatures = readBitSet<19>(stream);
      options.artifacts = readBitSet<18>(stream);
      return options;
    }

    template<StartingBonusType T>
    StartingBonusDetails<T> readStartingBonusDetails(std::istream& stream)
    {
      throw std::runtime_error("readStartingBonusDetails(): NotImplmented().");
    }

    template<>
    StartingBonusDetails<StartingBonusType::Spell>
    readStartingBonusDetails<StartingBonusType::Spell>(std::istream& stream)
    {
      StartingBonusDetails<StartingBonusType::Spell> details;
      details.hero = readInt<std::uint16_t>(stream);
      details.spell = readEnum<SpellType>(stream);
      return details;
    }

    StartingBonus readStartingBonus(std::istream& stream)
    {
      const StartingBonusType bonus_type = readEnum<StartingBonusType>(stream);
      switch (bonus_type)
      {
      case StartingBonusType::Spell:
        return readStartingBonusDetails<StartingBonusType::Spell>(stream);
      case StartingBonusType::Creature:
        return readStartingBonusDetails<StartingBonusType::Creature>(stream);
      case StartingBonusType::Building:
        return readStartingBonusDetails<StartingBonusType::Building>(stream);
      case StartingBonusType::Artifact:
        return readStartingBonusDetails<StartingBonusType::Artifact>(stream);
      case StartingBonusType::SpellScroll:
        return readStartingBonusDetails<StartingBonusType::SpellScroll>(stream);
      case StartingBonusType::PrimarySkills:
        return readStartingBonusDetails<StartingBonusType::PrimarySkills>(stream);
      case StartingBonusType::SecondarySkill:
        return readStartingBonusDetails<StartingBonusType::SecondarySkill>(stream);
      case StartingBonusType::Resource:
        return readStartingBonusDetails<StartingBonusType::Resource>(stream);
      default:
        throw std::runtime_error("readStartingBonus(): invalid bonus_type.");
      }
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

    CampaignScenario readCampaignScenario(std::istream& stream)
    {
      CampaignScenario scenario;
      scenario.format = readEnum<MapFormat>(stream);
      scenario.map_filename = readString(stream);
      scenario.prerequisites = readInt<std::uint8_t>(stream);
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
    }

    Campaign parseh3cUncompressed(std::istream& stream)
    {
      Campaign campaign;
      campaign.format = readEnum<CampaignFormat>(stream);
      campaign.id = readEnum<CampaignId>(stream);
      campaign.name = readString(stream);
      campaign.description = readString(stream);
      campaign.allow_selecting_difficulty = readBool(stream);
      campaign.theme_music = readEnum<CampaignMusic>(stream);
      return campaign;
    }
  }

  Campaign parseh3c(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3c(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    // Check the first byte. If it's 0x1F, then it cannot be an uncompressed .h3c file,
    // so assume that it's a compressed one.
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3c(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return parseh3cUncompressed(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return parseh3cUncompressed(zstr_stream);
    }
  }
}
