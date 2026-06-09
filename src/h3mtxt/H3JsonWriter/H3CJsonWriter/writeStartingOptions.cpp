#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>

#include <h3mtxt/Campaign/StartingOptions.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/Medea/Medea.h>

#include <limits>
#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    std::string_view getStartingHeroOptionComment(std::uint16_t hero) noexcept
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
      return EnumCommentGetter{}(static_cast<h3m::HeroType>(hero));
    }
  }

  template<>
  void JsonObjectWriter<h3m::HeroCrossoverOption>::operator()(FieldsWriter& out,
                                                              const h3m::HeroCrossoverOption& option) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(option)>>;
    out.writeField(Fields::kPlayer, option.player);
    out.writeField(Fields::kSourceScenario, option.source_scenario);
  }

  template<>
  void JsonObjectWriter<h3m::StartingHeroOption>::operator()(FieldsWriter& out,
                                                             const h3m::StartingHeroOption& option) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(option)>>;
    out.writeField(Fields::kPlayer, option.player);
    out.writeField(Fields::kType, option.type);
    if (std::string_view enum_str = getStartingHeroOptionComment(option.type); !enum_str.empty())
    {
      out.writeComment(enum_str);
    }
  }

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>&) const
  {
  }

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kPlayer, details.player);
    out.writeField(Fields::kOptions, details.options);
  }

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kOptions, details.options);
  }

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>::operator()(
    FieldsWriter& out, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>& details) const
  {
    using Fields = h3json::FieldNames<std::remove_cvref_t<decltype(details)>>;
    out.writeField(Fields::kOptions, details.options);
  }

  template<>
  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const
  {
    using Fields = h3json::FieldNames<h3m::StartingOptions>;
    out.writeField(Fields::kType, starting_options.type());
    std::visit([&out] <h3m::StartingOptionsType T> (const h3m::StartingOptionsDetails<T>& details)
               { out.writeField(Fields::kDetails, details); },
               starting_options.details);
  }
}
