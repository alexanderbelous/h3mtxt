#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>

#include <h3mtxt/Map/Utils/SwitchStatement.h>

#include <variant>

namespace h3json
{
  // Utility class for deserializing std::variant.
  // This is to reduce boilerplate that would otherwise occur when writing a switch statement
  // for all alternatives of the variant.
  template<class T>
  class VariantJsonReader;

  template<class... Types>
  class VariantJsonReader<std::variant<Types...>>
  {
  public:
    using Variant = std::variant<Types...>;

  private:
    // The number of alternatives in std::variant<Types...>.
    static constexpr std::size_t kNumAlternatives = sizeof...(Types);

    // Deserializes the specified alternative.
    // \param value - input JSON value.
    // \return the deserialized atlernative as std::variant<Types...>.
    template<std::size_t N>
    static Variant readAlternative(const Json::Value& value)
    {
      using Alternative = std::variant_alternative_t<N, Variant>;
      return Variant{ std::in_place_index<N>, JsonReader<Alternative>{}(value) };
    }

    // Convert the function template readAlternative<T>() into an alias template,
    // so that it can be passed as a template template parameter to generateSwitchStatement().
    template<std::size_t N>
    using AlternativeReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readAlternative<N>>;

    // Generate a switch statement for alternatives [0; kNumAlternatives).
    // kSwitchStatement(N, json_value) will trigger readAlternative<N>(json_value).
    static constexpr auto kSwitchStatement =
      SwitchStatement_NS::generateSwitchStatement<std::size_t, kNumAlternatives, AlternativeReaderTemplateAlias>();

  public:
    // Deserializes the input JSON as the specified alternative of the variant.
    // \param value - input JSON value.
    // \param index - 0-based index of the alternative to deserialize.
    // \return the deserialized alternative.
    // \throw std::out_of_range if index >= sizeof...(Types).
    Variant operator()(const Json::Value& value, std::size_t index) const
    {
      return kSwitchStatement(index, value);
    }
  };
}
