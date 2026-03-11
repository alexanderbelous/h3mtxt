#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string_view>

// Each overload of getEnumString follows the same pattern:
// \param value - input enum value.
// \return a human-readable name for @value,
//         or an empty string_view if @value is not a known enum constant.
namespace h3svg
{
  std::string_view getEnumString(ArtifactType8 value) noexcept;

  std::string_view getEnumString(ArtifactType32 value) noexcept;

  std::string_view getEnumString(CreatureType32 value) noexcept;

  std::string_view getEnumString(ObjectClass16 value) noexcept;

  std::string_view getEnumString(PlayerControlType value) noexcept;

  std::string_view getEnumString(PlayerPersonality value) noexcept;

  std::string_view getEnumString(PlayerStartingBonusType value) noexcept;

  std::string_view getEnumString(PlayerTurnDurationType value) noexcept;

  std::string_view getEnumString(PrimarySkillType32 value) noexcept;

  std::string_view getEnumString(ResourceType32 value) noexcept;

  std::string_view getEnumString(SecondarySkillType32 value) noexcept;

  std::string_view getEnumString(SeerName value) noexcept;

  std::string_view getEnumString(SpellType32 value) noexcept;

  std::string_view getEnumString(TownType32 value) noexcept;
}
