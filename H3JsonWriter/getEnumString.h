#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <string_view>

// Each overload of getEnumString follows the same pattern:
// \param value - input enum value.
// \return a human-readable name for @value,
//         or an empty string_view if @value is not a known enum constant.
namespace h3m
{
  std::string_view getEnumString(ArtifactType value) noexcept;

  std::string_view getEnumString(CreatureType value) noexcept;

  std::string_view getEnumString(Disposition value) noexcept;

  std::string_view getEnumString(Formation value) noexcept;

  std::string_view getEnumString(Gender value) noexcept;

  std::string_view getEnumString(HeroPortrait value) noexcept;

  std::string_view getEnumString(HeroType value) noexcept;

  std::string_view getEnumString(LossConditionType value) noexcept;

  std::string_view getEnumString(MapDifficulty value) noexcept;

  std::string_view getEnumString(ObjectPropertiesType value) noexcept;

  std::string_view getEnumString(ObjectClass value) noexcept;

  std::string_view getEnumString(ObjectGroup value) noexcept;

  std::string_view getEnumString(PlayerBehavior value) noexcept;

  std::string_view getEnumString(PlayerColor value) noexcept;

  std::string_view getEnumString(PrimarySkillType value) noexcept;

  std::string_view getEnumString(QuestType value) noexcept;

  std::string_view getEnumString(ResourceType value) noexcept;

  std::string_view getEnumString(RewardType value) noexcept;

  std::string_view getEnumString(RiverType value) noexcept;

  std::string_view getEnumString(RoadType value) noexcept;

  std::string_view getEnumString(ScholarRewardType value) noexcept;

  std::string_view getEnumString(SecondarySkillType value) noexcept;

  std::string_view getEnumString(SpellType value) noexcept;

  std::string_view getEnumString(TerrainType value) noexcept;

  std::string_view getEnumString(TownType value) noexcept;

  std::string_view getEnumString(VictoryConditionType value) noexcept;

  // ===== Campaign =====

  std::string_view getEnumString(CampaignId value) noexcept;

  std::string_view getEnumString(CampaignMusic value) noexcept;

  std::string_view getEnumString(CampaignVideo value) noexcept;

  std::string_view getEnumString(StartingBonusResourceType value) noexcept;

  std::string_view getEnumString(StartingBonusType value) noexcept;

  std::string_view getEnumString(StartingOptionsType value) noexcept;
}
