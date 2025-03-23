#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/writeStartingOptionsDetails.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/JsonWriter.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>::Hero>
  {
    void operator()(FieldsWriter& out,
                    const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>::Hero& hero) const
    {
      out.writeField("player", hero.player);
      if (std::string_view enum_str = h3m::getEnumString(hero.player); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
      out.writeField("source_scenario", hero.source_scenario);
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
                    const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>::Hero& hero) const
    {
      out.writeField("player", hero.player);
      if (std::string_view enum_str = h3m::getEnumString(hero.player); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
      out.writeField("type", hero.type);
      if (std::string_view enum_str = getHeroString(hero.type); !enum_str.empty())
      {
        out.writeComment(enum_str);
      }
    }
  };

  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>&) const
  {
  }

  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>& details) const
  {
    out.writeField("player", details.player);
    if (std::string_view enum_str = h3m::getEnumString(details.player); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("options", details.options);
  }

  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>& details) const
  {
    out.writeField("options", details.options);
  }

  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>& details) const
  {
    out.writeField("options", details.options);
  }

  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const
  {
    using Fields = h3m::FieldNames<h3m::StartingOptions>;
    out.writeField(Fields::kType, starting_options.type());
    // TODO: write the name of the enum in a comment.
    std::visit([&out] <h3m::StartingOptionsType T> (const h3m::StartingOptionsDetails<T>& details)
                { out.writeField(Fields::kDetails, details); },
                starting_options.details);
  }
}
