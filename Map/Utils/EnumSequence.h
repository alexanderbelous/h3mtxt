#pragma once

#include <type_traits>
#include <utility>

namespace h3m
{
  // Like std::integer_sequence, but for enums.
  template<class Enum, Enum... values>
  class EnumSequence
  {
  public:
    static_assert(std::is_enum_v<Enum>, "Enum must be an enum type.");

    using value_type = Enum;

    static constexpr std::size_t size() noexcept
    {
      return sizeof...(values);
    }
  };

  namespace Detail_NS
  {
    template<class Enum, class IntegerSequence>
    struct MakeEnumSequenceImpl;

    template<class Enum, std::underlying_type_t<Enum>... indices>
    struct MakeEnumSequenceImpl<Enum, std::integer_sequence<std::underlying_type_t<Enum>, indices...>>
    {
      using type = EnumSequence<Enum, static_cast<Enum>(indices)...>;
    };
  }

  // Generates EnumSequence<Enum{0}, Enum{1}, ..., Enum{N-1}>.
  template<class Enum, std::underlying_type_t<Enum> N>
  using MakeEnumSequence = typename Detail_NS::MakeEnumSequenceImpl<Enum,
    std::make_integer_sequence<std::underlying_type_t<Enum>, N>>::type;
}
