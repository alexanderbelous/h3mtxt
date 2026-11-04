#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>

#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Medea/Medea.h>

#include <limits>
#include <type_traits>

using ::h3m::StartingBonusDetails;
using ::h3m::StartingBonusType;

namespace Medea_NS
{
  namespace
  {
    // TODO: just define HeroType16 instead.
    enum class CampaignHeroType16 : std::uint16_t
    {
      MostPowerfulHero = static_cast<std::uint16_t>(-3),
      GeneratedHero = static_cast<std::uint16_t>(-2)
    };
  }

  // Specialize EnumCommentGetter for CampaignHeroType16.
  template<>
  std::string_view EnumCommentGetter::operator()(CampaignHeroType16 hero) const
  {
    switch (hero)
    {
    case CampaignHeroType16::MostPowerfulHero:
      return "(Most Powerful Hero)";
    case CampaignHeroType16::GeneratedHero:
      return "(Generated Hero)";
    default:
      break;
    }
    if (static_cast<std::uint16_t>(hero) > std::numeric_limits<std::underlying_type_t<h3m::HeroType>>::max())
    {
      return {};
    }
    return (*this)(static_cast<h3m::HeroType>(hero));
  }

  template<StartingBonusType T>
  void JsonObjectWriter<StartingBonusDetails<T>>::operator()(FieldsWriter& out,
                                                             const StartingBonusDetails<T>& details) const
  {
    if constexpr (T == StartingBonusType::Spell)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("spell", details.spell);
    }
    else if constexpr (T == StartingBonusType::Creature)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("creature_stack", details.creature_stack);
    }
    else if constexpr (T == StartingBonusType::Building)
    {
      out.writeField("building", details.building);
    }
    else if constexpr (T == StartingBonusType::Artifact)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("artifact", details.artifact);
    }
    else if constexpr (T == StartingBonusType::SpellScroll)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("spell", details.spell);
    }
    else if constexpr (T == StartingBonusType::PrimarySkills)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("skills", details.skills);
    }
    else if constexpr (T == StartingBonusType::SecondarySkill)
    {
      out.writeField("hero", static_cast<CampaignHeroType16>(details.hero));
      out.writeField("skill", details.skill);
    }
    else if constexpr (T == StartingBonusType::Resource)
    {
      out.writeField("resource", details.resource);
    }
    else
    {
      static_assert(false, "Invalid StartingBonusType.");
    }
  }

  template<>
  void JsonObjectWriter<h3m::StartingBonus>::operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const
  {
    using Fields = h3json::FieldNames<h3m::StartingBonus>;
    out.writeField(Fields::kType, bonus.type());
    std::visit([&out] <StartingBonusType T> (const StartingBonusDetails<T>& details)
               { out.writeField(Fields::kDetails, details); },
               bonus.details);
  }
}
