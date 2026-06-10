#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/PlayerBehavior.h>
#include <h3mtxt/SavedGame/Constants/Constants.h>
#include <h3mtxt/SavedGame/Constants/PlayerControlType.h>
#include <h3mtxt/SavedGame/Constants/PlayerPersonality.h>

#include <limits>
#include <type_traits>

using ::h3m::kNumHeroes;

namespace Medea_NS
{
  namespace
  {
    // Checks if the input enum value of the type `From` can be precisely represented by the enum type `To`.
    // \param To - destination enum type.
    // \param value - input enum value.
    // \return true if @value can be precisely represented by the type @To, false otherwise.
    template<class To, class From>
    constexpr bool isLosslessEnumCast(From value) noexcept
    {
      static_assert(std::is_enum_v<To>, "To must be an enum type.");
      static_assert(std::is_enum_v<From>, "From must be an enum type.");
      using UnderlyingTypeTo = std::underlying_type_t<To>;
      using UnderlyingTypeFrom = std::underlying_type_t<From>;
      // This is too strict - technically, we can always safely cast std::uint8_t to std::int32_t.
      // However, HoMM3 often uses "magic" values in which all bits are set to 1; their integral
      // value depend on signedness (-1 if signed, MAX_VALUE if unsigned). If the input and output
      // types have different signedness, the expected behavior of isLosslessEnumCast() is confusing.
      // For example, h3svg::HeroType32 is signed, but h3m::HeroType is unsigned; the expected result
      // of casting h3svg::HeroType32{-1} to h3m::HeroType is h3m::HeroType{0xFFu}, but that contradicts
      // the logic for casting integer values: -1 cannot be accurately represented by std::uint8_t.
      static_assert(std::is_unsigned_v<UnderlyingTypeTo> == std::is_unsigned_v<UnderlyingTypeFrom>,
                    "The underlying integer types of To an From must have the same signedness.");

      // Check that @value is greater or equal to the minimum value of UnderlyingTypeTo.
      //
      // No check is performed if the minimum value of UnderlyingTypeFrom is greater or equal
      // to the minimum value of UnderlyingTypeTo.
      if constexpr (std::numeric_limits<UnderlyingTypeFrom>::min() < std::numeric_limits<UnderlyingTypeTo>::min())
      {
        if (static_cast<UnderlyingTypeFrom>(value) < std::numeric_limits<UnderlyingTypeTo>::min())
        {
          return false;
        }
      }
      // Check that @value is less or equal to the maximum value of UnderlyingTypeTo.
      //
      // No check is performed if the maximum value of UnderlyingTypeFrom is less or equal
      // to the maximum value of UnderlyingTypeTo.
      if constexpr (std::numeric_limits<UnderlyingTypeFrom>::max() > std::numeric_limits<UnderlyingTypeTo>::max())
      {
        if (static_cast<UnderlyingTypeFrom>(value) > std::numeric_limits<UnderlyingTypeTo>::max())
        {
          return false;
        }
      }
      return true;
    }

    // A few compile-time tests.
    static_assert(isLosslessEnumCast<h3m::SpellType>(h3svg::SpellType32{ -1 }));
    static_assert(!isLosslessEnumCast<h3m::SpellType>(h3svg::SpellType32{ 255 }));
    static_assert(isLosslessEnumCast<h3m::PrimarySkillType>(h3svg::PrimarySkillType32{ 0 }));
    static_assert(isLosslessEnumCast<h3m::PrimarySkillType>(h3svg::PrimarySkillType32{ 255 }));
    static_assert(!isLosslessEnumCast<h3m::PrimarySkillType>(h3svg::PrimarySkillType32{ 256 }));
  }

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
  std::string_view EnumCommentGetter::operator()(h3svg::CampaignId value) const
  {
    // FYI: reuse the implementation for h3m::CampaignId for standard campaigns.
    static constexpr std::string_view kNames[] = {
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
      "Specter of Power",
      "Custom"
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    return (idx < std::size(kNames)) ? kNames[idx] : std::string_view{};
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
    if (isLosslessEnumCast<h3m::CreatureType>(value))
    {
      return (*this)(static_cast<h3svg::CreatureType>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::HeroType16 value) const
  {
    const std::uint16_t integer_value = static_cast<std::uint16_t>(value);
    if (integer_value < kNumHeroes)
    {
      return (*this)(static_cast<h3svg::HeroType>(static_cast<std::uint8_t>(integer_value)));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass8 value) const
  {
    if (isLosslessEnumCast<h3m::ObjectClass>(value))
    {
      return (*this)(static_cast<h3svg::ObjectClass>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass16 value) const
  {
    if (isLosslessEnumCast<h3m::ObjectClass>(value))
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
    if (isLosslessEnumCast<h3m::PrimarySkillType>(value))
    {
      return (*this)(static_cast<h3svg::PrimarySkillType>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ResourceType32 value) const
  {
    if (isLosslessEnumCast<h3m::ResourceType>(value))
    {
      return (*this)(static_cast<h3svg::ResourceType>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SecondarySkillType32 value) const
  {
    if (isLosslessEnumCast<h3m::SecondarySkillType>(value))
    {
      return (*this)(static_cast<h3svg::SecondarySkillType>(value));
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
    if (isLosslessEnumCast<h3m::SpellType>(value))
    {
      return (*this)(static_cast<h3svg::SpellType>(value));
    }
    return std::string_view{};
  }

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::TownType32 value) const
  {
    if (isLosslessEnumCast<h3m::TownType>(value))
    {
      return (*this)(static_cast<h3svg::TownType>(value));
    }
    return std::string_view{};
  }
}
