#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReader.h>

#include <array>
#include <type_traits>
#include <variant>

namespace h3m::H3JsonReader_NS
{
  // Utility class for deserializing std::variant.
  // This is to reduce boilerplate that would otherwise occur when writing a switch statement
  // for all alternatives of the variant.
  template<class T>
  class VariantJsonReader;

  template<class... Types>
  class VariantJsonReader<std::variant<Types...>>
  {
    using Variant = std::variant<Types...>;

    // The number of alternatives in std::variant<Types...>.
    static constexpr std::size_t kNumAlternatives = sizeof...(Types);

    // Deserializes the specified alternative.
    // \param value - input JSON value.
    // \return the deserialized atlernative as std::variant<Types...>.
    template<std::size_t N>
    static Variant readAlternative(const Json::Value& value)
    {
      using Alternative = std::variant_alternative_t<N, Variant>;
      return Variant(std::in_place_index<N>, JsonReader<Alternative>{}(value));
    }

    // Type of a pointer to a function that takes const Json::Value& and returns Variant.
    using AlternativeReaderPtr = Variant(*)(const Json::Value&);

    // Compile-time array of function pointers for each instantiation of readAlternative().
    static constexpr std::array<AlternativeReaderPtr, kNumAlternatives> kReaders =
      [] <std::size_t... alternative_idx>
      (std::index_sequence<alternative_idx...> seq)
      consteval
    {
      return std::array<AlternativeReaderPtr, sizeof...(alternative_idx)>
      {
        &readAlternative<alternative_idx>...
      };
    }(std::make_index_sequence<kNumAlternatives>{});

  public:
    // Deserializes the input JSON as the specified alternative of the variant.
    // \param value - input JSON value.
    // \param index - 0-based index of the alternative to deserialize.
    // \return the deserialized alternative.
    // \throw std::out_of_range if index >= sizeof...(Types).
    Variant operator()(const Json::Value& value, std::size_t index) const
    {
      return kReaders.at(index)(value);
    }
  };
}
