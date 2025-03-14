#include <h3mtxt/H3JsonWriter/getSecondarySkillLevelString.h>

#include <h3mtxt/Map/Constants/SecondarySkillLevel.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>

namespace h3m
{
  namespace
  {
    template<SecondarySkillType T>
    std::string_view getHexedSkillLevelString(std::uint8_t level) noexcept;

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Scouting>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Scouting>;
      switch (level)
      {
      case HexedLevels::k4Tiles:
        return "4 tiles";
      case HexedLevels::k3Tiles:
        return "3 tiles";
      case HexedLevels::k2Tiles:
        return "2 tiles";
      case HexedLevels::k1Tile:
        return "1 tile";
      case HexedLevels::kFullMap:
      case HexedLevels::kFullMap2:
        return "Full map";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Leadership>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Leadership>;
      switch (level)
      {
      case HexedLevels::k101058054:
        return "+101,058,054 morale";
      case HexedLevels::k100860675:
        return "+100,860,675 morale";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Wisdom>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Wisdom>;
      switch (level)
      {
      case HexedLevels::kMaxLevel1:
        return "Only level 1 spells";
      case HexedLevels::kNoSpells:
        return "No spells";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Mysticism>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Mysticism>;
      switch (level)
      {
      case HexedLevels::kFull:
      case HexedLevels::kFull2:
      case HexedLevels::kFull3:
        return "Full mana";
      case HexedLevels::kNoPoints:
      case HexedLevels::kNoPoints2:
      case HexedLevels::kNoPoints3:
        return "0 spell points";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Luck>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Luck>;
      switch (level)
      {
      case HexedLevels::k101058054:
        return "+101,058,054 luck";
      case HexedLevels::k100860675:
        return "+100,860,675 luck";
      case HexedLevels::k1028:
        return "+1028 luck";
      case HexedLevels::k771:
        return "+771 luck";
      case HexedLevels::k33686018:
        return "+33,686,018 luck";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Ballistics>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Ballistics>;
      switch (level)
      {
      case HexedLevels::k8Shots:
        return "8 shots";
      case HexedLevels::k0Shots1:
      case HexedLevels::k0Shots2:
      case HexedLevels::k0Shots3:
      case HexedLevels::k0Shots4:
      case HexedLevels::k0Shots5:
      case HexedLevels::k0Shots6:
        return "0 shots";
      case HexedLevels::kInstakill:
      case HexedLevels::kInstakill2:
        return "Instakill";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Estates>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Estates>;
      switch (level)
      {
      case HexedLevels::kBillionPerDay:
        return "+1,000,000,000 gold";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Offense>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Offense>;
      switch (level)
      {
      case HexedLevels::k50Percent:
        return "50%";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Armorer>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Armorer>;
      switch (level)
      {
      case HexedLevels::k50Percent:
        return "50%";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Resistance>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Resistance>;
      switch (level)
      {
      case HexedLevels::k60Percent:
      case HexedLevels::k60Percent2:
        return "60%";
      case HexedLevels::k40Percent:
      case HexedLevels::k40Percent2:
        return "40%";
      default:
        return {};
      }
    }

    template<>
    std::string_view getHexedSkillLevelString<SecondarySkillType::Sorcery>(std::uint8_t level) noexcept
    {
      using HexedLevels = SecondarySkillLevel<SecondarySkillType::Sorcery>;
      switch (level)
      {
      case HexedLevels::k60Percent:
      case HexedLevels::k60Percent2:
        return "60%";
      case HexedLevels::k50Percent:
      case HexedLevels::k50Percent2:
        return "50%";
      case HexedLevels::k40Percent:
      case HexedLevels::k40Percent2:
        return "40%";
      case HexedLevels::k30Percent:
        return "30%";
      case HexedLevels::k20Percent:
      case HexedLevels::k20Percent2:
      case HexedLevels::k20Percent3:
        return "20%";
      default:
        return {};
      }
    }
  }

  std::string_view getSecondarySkillLevelString(SecondarySkillType skill, std::uint8_t level) noexcept
  {
    switch (level)
    {
    case 0:
      return "None";
    case 1:
      return "Basic";
    case 2:
      return "Advanced";
    case 3:
      return "Expert";
    default:
      break;
    }
    switch (skill)
    {
    case SecondarySkillType::Scouting:
      return getHexedSkillLevelString<SecondarySkillType::Scouting>(level);
    case SecondarySkillType::Leadership:
      return getHexedSkillLevelString<SecondarySkillType::Leadership>(level);
    case SecondarySkillType::Wisdom:
      return getHexedSkillLevelString<SecondarySkillType::Wisdom>(level);
    case SecondarySkillType::Mysticism:
      return getHexedSkillLevelString<SecondarySkillType::Mysticism>(level);
    case SecondarySkillType::Luck:
      return getHexedSkillLevelString<SecondarySkillType::Luck>(level);
    case SecondarySkillType::Ballistics:
      return getHexedSkillLevelString<SecondarySkillType::Ballistics>(level);
    case SecondarySkillType::Estates:
      return getHexedSkillLevelString<SecondarySkillType::Estates>(level);
    case SecondarySkillType::Offense:
      return getHexedSkillLevelString<SecondarySkillType::Offense>(level);
    case SecondarySkillType::Armorer:
      return getHexedSkillLevelString<SecondarySkillType::Armorer>(level);
    case SecondarySkillType::Resistance:
      return getHexedSkillLevelString<SecondarySkillType::Resistance>(level);
    case SecondarySkillType::Sorcery:
      return getHexedSkillLevelString<SecondarySkillType::Sorcery>(level);
    default:
      return {};
    }
  }
}
