#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>

#include <h3mtxt/Campaign/Constants/CampaignFormat.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Map/Constants/MapFormat.h>

#include <iterator>

namespace Medea_NS
{
  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignFormat value) const
  {
    // Reuse the implementation for MapFormat.
    switch (value)
    {
    case h3m::CampaignFormat::RestorationOfErathia:
      return (*this)(h3m::MapFormat::RestorationOfErathia);
    case h3m::CampaignFormat::ArmageddonsBlade:
      return (*this)(h3m::MapFormat::ArmageddonsBlade);
    case h3m::CampaignFormat::ShadowOfDeath:
      return (*this)(h3m::MapFormat::ShadowOfDeath);
    default:
      return {};
    }
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignId value) const
  {
    static constexpr std::string_view kNames[] = {
      std::string_view{},
      "Long Live the Queen",
      "Liberation",
      "Song for the Father",
      "Dungeons and Devils",
      "Long Live the King",
      "Spoils of War",
      "Seeds of Discontent",
      "Bracada",
      "Islands",
      "Krewlod",
      "Nighon",
      "Tatalia",
      "Armageddon",
      "Hack and Slash",
      "Birth of a Barbarian",
      "New Beginning",
      "Elixir of Life",
      "Rise of the Necromancer",
      "Unholy Alliance",
      "Specter of Power"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignMusic value) const
  {
    static constexpr std::string_view kNames[] = {
      "CampainMusic01",
      "CampainMusic02",
      "CampainMusic03",
      "CampainMusic04",
      "CampainMusic05",
      "CampainMusic06",
      "CampainMusic07",
      "CampainMusic08",
      "CampainMusic09",
      "AiTheme0",
      "AiTheme1",
      "AiTheme2",
      "Combat01",
      "Combat02",
      "Combat03",
      "Combat04",
      "CstleTown",
      "TowerTown",
      "Rampart",
      "InfernoTown",
      "NecroTown",
      "Dungeon",
      "Stronghold",
      "FortressTown",
      "ElemTown",
      "Dirt",
      "Sand",
      "Grass",
      "Snow",
      "Swamp",
      "Rough",
      "Underground",
      "Lava",
      "Water",
      "GoodTheme",
      "NeutralTheme",
      "EvilTheme",
      "SecretTheme",
      "LoopLepr",
      "MainMenu",
      "Win Scenario",
      "CampainMusic10",
      "BladeABCampaign",
      "BladeDBCampaign",
      "BladeDSCampaign",
      "BladeFLCampaign",
      "BladeFWCampaign",
      "BladePFCampaign",
      "CampainMusic11",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::CampaignVideo value) const
  {
    static constexpr std::string_view kNames[] = {
      "Good1_a",
      "Good1_b",
      "Good1_c",
      "Evil1_a",
      "Evil1_b",
      "Evil1_c",
      "Neutral1_a",
      "Neutral1_b",
      "Neutral1_c",
      "Good2_a",
      "Good2_b",
      "Good2_c",
      "Good2_d",
      "Evil2_a",
      "Evil2ap1",
      "Evil2_b",
      "Evil2_c",
      "Evil2_d",
      "Good3_a",
      "Good3_b",
      "Good3_c",
      "Secret_a",
      "Secret_b",
      "Secret_c",
      "ArmageddonsBlade_a",
      "ArmageddonsBlade_b",
      "ArmageddonsBlade_c",
      "ArmageddonsBlade_d",
      "ArmageddonsBlade_e",
      "ArmageddonsBlade_f",
      "ArmageddonsBlade_g",
      "ArmageddonsBlade_h",
      "ArmageddonsBlade_end",
      "DragonsBlood_a",
      "DragonsBlood_b",
      "DragonsBlood_c",
      "DragonsBlood_d",
      "DragonsBlood_end",
      "DragonSlayer_a",
      "DragonSlayer_b",
      "DragonSlayer_c",
      "DragonSlayer_d",
      "DragonSlayer_end",
      "FestivalOfLife_a",
      "FestivalOfLife_b",
      "FestivalOfLife_c",
      "FestivalOfLife_d",
      "FestivalOfLife_end",
      "FoolhardyWaywardness_a",
      "FoolhardyWaywardness_b",
      "FoolhardyWaywardness_c",
      "FoolhardyWaywardness_d",
      "FoolhardyWaywardness_end",
      "PlayingWithFire_a",
      "PlayingWithFire_b",
      "PlayingWithFire_c",
      "PlayingWithFire_end",
      "BirthOfABarbarian_a",
      "BirthOfABarbarian_b",
      "BirthOfABarbarian_c",
      "BirthOfABarbarian_d",
      "BirthOfABarbarian_e",
      "BirthOfABarbarian_end",
      "ElixirOfLife_a",
      "ElixirOfLife_b",
      "ElixirOfLife_c",
      "ElixirOfLife_d",
      "ElixirOfLife_end",
      "HackAndSlash_a",
      "HackAndSlash_b",
      "HackAndSlash_c",
      "HackAndSlash_d",
      "HackAndSlash_end",
      "NewBeginning_a",
      "NewBeginning_b",
      "NewBeginning_c",
      "NewBeginning_d",
      "NewBeginning_end",
      "RiseOfTheNecromancer_a",
      "RiseOfTheNecromancer_b",
      "RiseOfTheNecromancer_c",
      "RiseOfTheNecromancer_d",
      "RiseOfTheNecromancer_end",
      "SpectreOfPower_a",
      "SpectreOfPower_b",
      "SpectreOfPower_c",
      "SpectreOfPower_d",
      "SpectreOfPower_end",
      "UnholyAlliance_a",
      "UnholyAlliance_b",
      "UnholyAlliance_c",
      "UnholyAlliance_d",
      "UnholyAlliance_e",
      "UnholyAlliance_f",
      "UnholyAlliance_g",
      "UnholyAlliance_h",
      "UnholyAlliance_I",
      "UnholyAlliance_j",
      "UnholyAlliance_k",
      "UnholyAlliance_l",
      "UnholyAlliance_end"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::StartingBonusType value) const
  {
    static constexpr std::string_view kNames[] = {
      "Spell",
      "Creature",
      "Building",
      "Artifact",
      "Spell scroll",
      "Primary skill",
      "Secondary skill",
      "Resource",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3m::StartingOptionsType value) const
  {
    static constexpr std::string_view kNames[] = {
      "None",
      "Starting bonus options",
      "Hero crossover options",
      "Starting hero options"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }
}
