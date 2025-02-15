#pragma once

#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/BitSet.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace h3m
{
  // Note: the values are different from MapFormat.
  enum class CampaignFormat : std::uint32_t
  {
    RestorationOfErathia = 0x04,
    ArmageddonsBlade = 0x05,
    ShadowOfDeath = 0x06,
  };

  // Template to use for the campaign (see CampText.txt).
  // The maximum number of regions depends on the template.
  enum class CampaignId : std::uint8_t
  {
    Armageddon = 0x0d,
    // TODO: add the rest.
  };

  // Returns the maximum number of map regions for the given CampaignId.
  // \param campaign_map - input CampaignId.
  // \return the maximum number of map regions for @campaign_map,
  //         or 0 if @campaign_map is not a valid CampaignId constant.
  constexpr std::uint8_t countMapRegions(CampaignId campaign_id) noexcept
  {
    switch (campaign_id)
    {
    case CampaignId::Armageddon:
      return 8;
    // TODO: add the rest.
    default:
      return 0;
    }
  }

  enum class CampaignMusic : std::uint8_t {};

  enum class CampaignVideo : std::uint8_t {};

  enum class RegionColor : std::uint8_t
  {
    Red = 0,
    Blue = 1,
    Tan = 2,
    Green = 3,
    Orange = 4,
    Purple = 5,
    Teal = 6,
    Pink = 7
  };

  struct CampaignProperties
  {
    CampaignFormat format = CampaignFormat::ShadowOfDeath;
    CampaignId id {};
    std::string name;
    std::string description;
    Bool allow_selecting_difficulty {};
    CampaignMusic theme_music {};
  };

  struct CutScene
  {
    CampaignVideo movie {};
    CampaignMusic music {};
    std::string message;
  };

  struct CrossoverOptions
  {
    // Bitmask. TODO: replace with a wrapper.
    std::byte crossover_heroes_retain {};
    // Which creatures crossover heroes retain.
    // Bitmask CreatureType -> bool. TODO: replace with a wrapper.
    BitSet<19> creatures {};
    // Which artifacts crossover heroes retain.
    BitSet<18> artifacts;
  };

  enum class StartingOptionsType : std::uint8_t
  {
    StartingBonus = 1,
    HeroCrossover = 2,
    StartingHero = 3
  };

  template<StartingOptionsType>
  struct StartingOptionsDetails;

  enum class StartingBonusType : std::uint8_t
  {
    Spell = 0,
    Creature = 1,
    Building = 2,
    Artifact = 3,
    SpellScroll = 4,
    PrimarySkills = 5,
    SecondarySkill = 6,
    Resource = 7,
  };

  template<StartingBonusType>
  struct StartingBonusDetails;

  template<>
  struct StartingBonusDetails<StartingBonusType::Spell>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    SpellType spell {};
  };

  struct StartingBonus
  {
    using Details = std::variant<
      StartingBonusDetails<StartingBonusType::Spell>
      // TODO: add the rest
    >;

    Details details;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::StartingBonus>
  {
    PlayerColor player {};
    // Size is serialized as std::uint8_t.
    std::vector<StartingBonus> options;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::HeroCrossover>
  {
    struct Hero
    {
      PlayerColor player {};
      std::uint8_t source_scenario {};
    };

    // Size is serialized as std::uint8_t.
    std::vector<Hero> options;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::StartingHero>
  {
    struct Hero
    {
      PlayerColor player{};
      // HeroType or 0xFFFF if random.
      std::uint16_t type{};
    };

    // Size is serialized as std::uint8_t.
    std::vector<Hero> options;
  };

  struct StartingOptions
  {
    using Details = std::variant<
      StartingOptionsDetails<StartingOptionsType::StartingBonus>,
      StartingOptionsDetails<StartingOptionsType::HeroCrossover>,
      StartingOptionsDetails<StartingOptionsType::StartingHero>
    >;

    constexpr StartingOptionsType type() const noexcept;

    Details details;
  };

  constexpr StartingOptionsType StartingOptions::type() const noexcept
  {
    return static_cast<StartingOptionsType>(details.index() + 1);
  }

  struct CampaignScenario
  {
    MapFormat format = MapFormat::ShadowOfDeath;
    std::string map_filename;
    // Bitmask.
    std::uint8_t prerequisites {};
    RegionColor region_color {};
    MapDifficulty default_difficulty {};
    std::string region_righ_click_text;
    std::optional<CutScene> prologue;
    std::optional<CutScene> epilogue;
    CrossoverOptions crossover_options;
    StartingOptions starting_options;
  };

  // Represents a *.h3c campaign.
  struct Campaign
  {
    CampaignProperties properties;
    std::vector<CampaignScenario> scenarios;
    // TODO: Maps are serialized after all scenarios, but there is some padding/unknown data in between.
    // std::vector<Map> maps;
  };
}
