#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/writeStartingBonusDetails.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/Medea.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    std::string_view getStartingBonusHeroString(std::uint16_t hero) noexcept
    {
      if (hero == 0xFDFFu)
      {
        return "(Most powerful)";
      }
      if (hero > std::numeric_limits<std::underlying_type_t<h3m::HeroType>>::max())
      {
        return {};
      }
      return h3m::getEnumString(static_cast<h3m::HeroType>(hero));
    }

    void writeStaringBonusHeroField(FieldsWriter& out, std::uint16_t hero)
    {
      out.writeField("hero", hero);
      if (std::string_view enum_str = getStartingBonusHeroString(hero); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("spell", details.spell);
    if (std::string_view enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("creature_stack", details.creature_stack);
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Building>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Building>& details) const
  {
    out.writeField("building", details.building);
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("artifact", details.artifact);
    if (std::string_view enum_str = h3m::getEnumString(details.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("spell", details.spell);
    if (std::string_view enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("skills", details.skills);
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>& details) const
  {
    writeStaringBonusHeroField(out, details.hero);
    out.writeField("skill", details.skill);
  }

  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>& details) const
  {
    out.writeField("type", details.type);
    if (std::string_view enum_str = h3m::getEnumString(details.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("amount", details.amount);
  }

  void JsonObjectWriter<h3m::StartingBonus>::operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const
  {
    using Fields = h3m::FieldNames<h3m::StartingBonus>;
    out.writeField(Fields::kType, bonus.type());
    if (std::string_view enum_str = h3m::getEnumString(bonus.type()); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    std::visit([&out] <h3m::StartingBonusType T> (const h3m::StartingBonusDetails<T>& details)
                { out.writeField(Fields::kDetails, details); },
                bonus.details);
  }
}
