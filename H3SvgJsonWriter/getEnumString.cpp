#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/SavedGame/Constants/PlayerControlType.h>

#include <limits>
#include <type_traits>

namespace h3m
{
  std::string_view getEnumString(ArtifactType8 value) noexcept
  {
    constexpr ArtifactType8 kNone {0xFF};
    // ArtifactType8 is unsigned, but 0xFF should be treated as -1.
    const std::int16_t integer_value = (value == kNone) ? std::int16_t{ -1 }
                                                        : static_cast<std::int16_t>(value);
    return getEnumString(static_cast<ArtifactType>(static_cast<std::uint16_t>(integer_value)));
  }

  std::string_view getEnumString(ArtifactType32 value) noexcept
  {
    // TODO: replace the underlying type of h3m::ArtifactType with std::int16_t.
    // The issue is basically this:
    //   static_cast<ArtifactType>(std::int32_t(65535)) == static_cast<ArtifactType>(std::int32_t(-1))
    // In reality, ArtifactType::None is encoded as 0xFFFFFFFF when using a 32-bit integer, not as
    // 0x0000FFFF.
    static_assert(std::is_same_v<std::underlying_type_t<h3m::ArtifactType>, std::uint16_t>,
                  "This function assumes that h3m::ArtifactType has uint16_t as the underlying type.");
    using UnderlyingType32 = std::underlying_type_t<h3m::ArtifactType32>;
    const UnderlyingType32 integer_value = static_cast<UnderlyingType32>(value);
    if (integer_value >= std::numeric_limits<std::int16_t>::min() ||
        integer_value <= std::numeric_limits<std::int16_t>::max())
    {
      return getEnumString(static_cast<h3m::ArtifactType>(static_cast<std::int16_t>(integer_value)));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(CreatureType32 value) noexcept
  {
    constexpr std::uint8_t kNumCreatures = 150;
    const auto integer_value = static_cast<std::underlying_type_t<CreatureType32>>(value);
    if (integer_value >= 0 && integer_value < kNumCreatures)
    {
      return getEnumString(static_cast<CreatureType>(integer_value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(ObjectClass16 value) noexcept
  {
    if (static_cast<std::underlying_type_t<ObjectClass16>>(value) < kNumObjectClasses)
    {
      return getEnumString(static_cast<ObjectClass>(value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(PlayerControlType value) noexcept
  {
    switch (value)
    {
    case PlayerControlType::Cpu:
      return "CPU";
    case PlayerControlType::HumanOrCpu:
      return "Human Or CPU";
    case PlayerControlType::None:
      return "None";
    default:
      return std::string_view{};
    }
  }

  std::string_view getEnumString(PlayerStartingBonusType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "Artifact",
      "Gold",
      "Resource"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(PlayerTurnDurationType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "1 Minute",
      "2 Minutes",
      "4 Minutes",
      "6 Minutes",
      "8 Minutes",
      "10 Minutes",
      "15 Minutes",
      "20 Minutes",
      "25 Minutes",
      "30 Minutes",
      "Unlimited"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  std::string_view getEnumString(PrimarySkillType32 value) noexcept
  {
    constexpr std::uint8_t kNumPrimarySkills = 4;
    const auto integer_value = static_cast<std::underlying_type_t<PrimarySkillType32>>(value);
    if (integer_value >= 0 && integer_value < kNumPrimarySkills)
    {
      return getEnumString(static_cast<PrimarySkillType>(integer_value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(ResourceType32 value) noexcept
  {
    const auto integer_value = static_cast<std::underlying_type_t<ResourceType32>>(value);
    if (integer_value >= 0 && integer_value < kNumResources)
    {
      return getEnumString(static_cast<ResourceType>(integer_value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(SecondarySkillType32 value) noexcept
  {
    constexpr std::uint8_t kNumSecondarySkills = 28;
    const auto integer_value = static_cast<std::underlying_type_t<SecondarySkillType32>>(value);
    if (integer_value >= 0 && integer_value < kNumSecondarySkills)
    {
      return getEnumString(static_cast<SecondarySkillType>(integer_value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(SpellType32 value) noexcept
  {
    constexpr std::uint8_t kNumSpells = 70;
    const auto integer_value = static_cast<std::underlying_type_t<SpellType32>>(value);
    if (integer_value >= 0 && integer_value < kNumSpells)
    {
      return getEnumString(static_cast<SpellType>(integer_value));
    }
    return std::string_view{};
  }

  std::string_view getEnumString(TownType32 value) noexcept
  {
    // Reuse the names for h3m::TownType.
    using UnderlyingType = std::underlying_type_t<h3m::TownType>;
    using UnderlyingType32 = std::underlying_type_t<h3m::TownType32>;
    const UnderlyingType32 integer_value = static_cast<UnderlyingType32>(value);
    if (integer_value >= std::numeric_limits<UnderlyingType>::min() &&
        integer_value <= std::numeric_limits<UnderlyingType>::max())
    {
      return getEnumString(static_cast<TownType>(integer_value));
    }
    return std::string_view{};
  }
}
