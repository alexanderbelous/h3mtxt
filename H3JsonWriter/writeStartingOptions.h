#pragma once

#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/writeStartingBonus.h>
#include <h3mtxt/Map/MapFwd.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>
  {
    void operator()(FieldsWriter&,
                    const h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>&) const
    {
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>& details) const
    {
      out.writeField("player", details.player);
      if (std::string_view enum_str = h3m::getEnumString(details.player); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("options", details.options);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>::Hero>
  {
    void operator()(FieldsWriter& out,
                    const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>::Hero& details) const
    {
      out.writeField("player", details.player);
      if (std::string_view enum_str = h3m::getEnumString(details.player); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("source_scenario", details.source_scenario);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>& details) const
    {
      out.writeField("options", details.options);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>::Hero>
  {
    static std::string_view getHeroString(std::uint16_t hero) noexcept
    {
      using HeroTypeUnderlyingType = std::underlying_type_t<h3m::HeroType>;
      if (hero == 0xFFFFu)
      {
        return "(Random)";
      }
      if (hero > std::numeric_limits<HeroTypeUnderlyingType>::max())
      {
        return {};
      }
      return h3m::getEnumString(static_cast<h3m::HeroType>(hero));
    }

    void operator()(FieldsWriter& out,
      const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>::Hero& details) const
    {
      out.writeField("player", details.player);
      if (std::string_view enum_str = h3m::getEnumString(details.player); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("type", details.type);
      if (std::string_view enum_str = getHeroString(details.type); !enum_str.empty())
      {
        out.writeComment(enum_str);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>
  {
    void operator()(FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>& details) const
    {
      out.writeField("options", details.options);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingOptions>
  {
    void operator()(FieldsWriter& out, const h3m::StartingOptions& starting_options) const
    {
      out.writeField("type", starting_options.type());
      // TODO: write the name of the enum in a comment.
      std::visit([&out] <h3m::StartingOptionsType T> (const h3m::StartingOptionsDetails<T>& details)
                 {
                   out.writeField("details", details);
                 },
                 starting_options.details);
    }
  };
}
