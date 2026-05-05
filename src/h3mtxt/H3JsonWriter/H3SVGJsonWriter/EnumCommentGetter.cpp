#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/PlayerBehavior.h>
#include <h3mtxt/SavedGame/Constants/Constants.h>
#include <h3mtxt/SavedGame/Constants/PlayerControlType.h>
#include <h3mtxt/SavedGame/Constants/PlayerPersonality.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ArtifactType8 value) const
  {
    constexpr h3svg::ArtifactType8 kNone {0xFF};
    // ArtifactType8 is unsigned, but 0xFF should be treated as -1.
    const std::int16_t integer_value = (value == kNone) ? std::int16_t{ -1 }
                                                        : static_cast<std::int16_t>(value);
    return (*this)(static_cast<h3svg::ArtifactType>(static_cast<std::uint16_t>(integer_value)));
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ArtifactType32 value) const
  {
    // TODO: replace the underlying type of h3m::ArtifactType with std::int16_t.
    // The issue is basically this:
    //   static_cast<ArtifactType>(std::int32_t(65535)) == static_cast<ArtifactType>(std::int32_t(-1))
    // In reality, ArtifactType::None is encoded as 0xFFFFFFFF when using a 32-bit integer, not as
    // 0x0000FFFF.
    static_assert(std::is_same_v<std::underlying_type_t<h3svg::ArtifactType>, std::uint16_t>,
                  "This function assumes that h3svg::ArtifactType has uint16_t as the underlying type.");
    using UnderlyingType32 = std::underlying_type_t<h3svg::ArtifactType32>;
    const UnderlyingType32 integer_value = static_cast<UnderlyingType32>(value);
    if (integer_value >= std::numeric_limits<std::int16_t>::min() ||
        integer_value <= std::numeric_limits<std::int16_t>::max())
    {
      return (*this)(static_cast<h3svg::ArtifactType>(static_cast<std::int16_t>(integer_value)));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::CreatureType8 value) const
  {
    // TODO: fix this for special negative values CreatureType::Creature1, CreatureType::Creature1U,
    // ..., CreatureType::Creature7U.
    // I don't think they can ever appear in the contexts where CreatureType8 is used (in fact, I don't
    // think they ever appear in H3SVG), but the function should behave correctly for them.
    const h3svg::CreatureType creature_type =
      (value == h3svg::CreatureType8{ 0xFFu }) ? h3svg::CreatureType::None
                                               : static_cast<h3svg::CreatureType>(value);
    return (*this)(creature_type);
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::CreatureType32 value) const
  {
    // This implementation relies on the fact that the underlying types of both
    // CreatureType and CreatureType32 are signed integers.
    static_assert(std::is_same_v<std::underlying_type_t<h3svg::CreatureType>, std::int16_t>);
    static_assert(std::is_same_v<std::underlying_type_t<h3svg::CreatureType32>, std::int32_t>);
    // If @value can be represented without losses as std::int16_t - delegate to operator()(CreatureType).
    const std::int32_t integer_value = static_cast<std::int32_t>(value);
    if (integer_value >= std::numeric_limits<std::int16_t>::min() &&
        integer_value <= std::numeric_limits<std::int16_t>::max())
    {
      return (*this)(static_cast<h3svg::CreatureType>(static_cast<std::int16_t>(integer_value)));
    }
    // Otherwise - return an empty string_view.
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::HeroType16 value) const
  {
    const std::uint16_t integer_value = static_cast<std::uint16_t>(value);
    if (integer_value < h3svg::kNumHeroes)
    {
      return (*this)(static_cast<h3svg::HeroType>(static_cast<std::uint8_t>(integer_value)));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass8 value) const
  {
    const std::uint8_t integer_value = static_cast<std::uint8_t>(value);
    if (integer_value < h3m::kNumObjectClasses)
    {
      return (*this)(static_cast<h3svg::ObjectClass>(integer_value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass16 value) const
  {
    if (static_cast<std::underlying_type_t<h3svg::ObjectClass16>>(value) < h3m::kNumObjectClasses)
    {
      return (*this)(static_cast<h3svg::ObjectClass>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerControlType value) const
  {
    switch (value)
    {
    case h3svg::PlayerControlType::Cpu:
      return "CPU";
    case h3svg::PlayerControlType::HumanOrCpu:
      return "Human Or CPU";
    case h3svg::PlayerControlType::None:
      return "None";
    default:
      return std::string_view{};
    }
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerPersonality value) const
  {
    switch (value)
    {
    case h3svg::PlayerPersonality::Warrior:
      return (*this)(h3svg::PlayerBehavior::Warrior);
    case h3svg::PlayerPersonality::Builder:
      return (*this)(h3svg::PlayerBehavior::Builder);
    case h3svg::PlayerPersonality::Exporer:
      return (*this)(h3svg::PlayerBehavior::Explorer);
    case h3svg::PlayerPersonality::Human:
      return "Human";
    default:
      return std::string_view{};
    }
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerStartingBonusType value) const
  {
    static constexpr std::string_view kNames[] = {
      "Artifact",
      "Gold",
      "Resource"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerTurnDurationType value) const
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

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PrimarySkillType32 value) const
  {
    constexpr std::uint8_t kNumPrimarySkills = 4;
    const auto integer_value = static_cast<std::underlying_type_t<h3svg::PrimarySkillType32>>(value);
    if (integer_value >= 0 && integer_value < kNumPrimarySkills)
    {
      return (*this)(static_cast<h3svg::PrimarySkillType>(integer_value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ResourceType32 value) const
  {
    const auto integer_value = static_cast<std::underlying_type_t<h3svg::ResourceType32>>(value);
    if (integer_value >= 0 && integer_value < h3svg::kNumResources)
    {
      return (*this)(static_cast<h3svg::ResourceType>(integer_value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SecondarySkillType32 value) const
  {
    const auto integer_value = static_cast<std::underlying_type_t<h3svg::SecondarySkillType32>>(value);
    if (integer_value >= 0 && integer_value < h3svg::kNumSecondarySkills)
    {
      return (*this)(static_cast<h3svg::SecondarySkillType>(integer_value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SeerName value) const
  {
    static constexpr std::string_view kNames[] = {
      "Abraham",
      "Goldwyn",
      "Bryce",
      "Blain",
      "Engle",
      "Carsten",
      "Dulcie",
      "Donard",
      "Esslock",
      "Evander",
      "Frederick",
      "Fay",
      "Genevieve",
      "Horace",
      "Heather",
      "Ike",
      "Jhem",
      "Julius",
      "Joseph",
      "Kae",
      "Kendrick",
      "Lynwood",
      "Kyriell",
      "Marigold",
      "Norwood",
      "Clova",
      "Tim",
      "Gier",
      "Paige",
      "Pierce",
      "Rae",
      "Raphael",
      "Rex",
      "Hester",
      "Spiridion",
      "Skye",
      "Rival",
      "Timeus",
      "Sulmand",
      "Rizlav",
      "Violet",
      "Wendell",
      "Winston",
      "Xanthe",
      "Xavier",
      "Yvette",
      "Zaray",
      "Zoe"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SpellType32 value) const
  {
    const auto integer_value = static_cast<std::underlying_type_t<h3svg::SpellType32>>(value);
    if (integer_value >= 0 && integer_value < h3svg::kNumSpells)
    {
      return (*this)(static_cast<h3svg::SpellType>(integer_value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::TownType32 value) const
  {
    // Reuse the names for TownType.
    using UnderlyingType = std::underlying_type_t<h3svg::TownType>;
    using UnderlyingType32 = std::underlying_type_t<h3svg::TownType32>;
    const UnderlyingType32 integer_value = static_cast<UnderlyingType32>(value);
    if (integer_value >= std::numeric_limits<UnderlyingType>::min() &&
        integer_value <= std::numeric_limits<UnderlyingType>::max())
    {
      return (*this)(static_cast<h3svg::TownType>(integer_value));
    }
    return std::string_view{};
  }
}
