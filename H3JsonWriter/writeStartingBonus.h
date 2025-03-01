#pragma once

#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapFwd.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    inline std::string_view getStartingBonusHeroString(std::uint16_t hero) noexcept
    {
      using HeroTypeUnderlyingType = std::underlying_type_t<h3m::HeroType>;
      if (hero == 0xFDFFu)
      {
        return "(Most powerful)";
      }
      if (hero > std::numeric_limits<HeroTypeUnderlyingType>::max())
      {
        return {};
      }
      return h3m::getEnumString(static_cast<h3m::HeroType>(hero));
    }
  }

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("spell", details.spell);
      if (std::string_view enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("creature_stack", details.creature_stack);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Building>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Building>& details) const
    {
      out.writeField("building", details.building);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("artifact", details.artifact);
      if (std::string_view enum_str = h3m::getEnumString(details.artifact); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("spell", details.spell);
      if (std::string_view enum_str = h3m::getEnumString(details.spell); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("skills", details.skills);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>& details) const
    {
      out.writeField("hero", details.hero);
      if (std::string_view enum_str = Detail_NS::getStartingBonusHeroString(details.hero); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("skill", details.skill);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>& details) const
    {
      out.writeField("type", details.type);
      out.writeField("amount", details.amount);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingBonus>
  {
    void operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const
    {
      out.writeField("type", bonus.type());
      // TODO: write the name of the enum in a comment.
      std::visit([&out] <h3m::StartingBonusType T> (const h3m::StartingBonusDetails<T>& details)
                 { out.writeField("details", details); },
                 bonus.details);
    }
  };
}
