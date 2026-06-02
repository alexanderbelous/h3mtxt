#pragma once

// Template for automatically generating a switch statement for a function template f<T>()
// with labels T{0}, T{1}, ..., T{N-1}.
//
// This is used in H3Reader and H3JsonReader for reading various "polymorphic" types, e.g.,
// Object, Quest, Reward, ...

#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace SwitchStatement_NS
{
  // Wrapper for array of function pointers, which emultates a switch statement.
  // \param ConditionType - the type of the value used in the condition.
  //        Similar to the native switch statement, this can be either an integral type or an enumeration type.
  // \param NumLabels - the number of labels in this SwitchStatement.
  //        Note that the labels always correspond to ConditionType{0}, ConditionType{1}, ...,
  //        ConditionType{NumLabels - 1}.
  // \param IsNoexcept - true if the underlying functions are marked noexcept, false otherwise.
  // \param Result - type of the returned value.
  // \param Args... - types of the input arguments that will be passed to the underlying functions.
  template<class ConditionType, std::size_t NumLabels, bool IsNoexcept, class Result, class... Args>
  class SwitchStatement
  {
  public:
    static_assert(std::is_integral_v<ConditionType> || std::is_enum_v<ConditionType>,
                  "ConditionType must be either an integral type or an enumeration type");

    // Type of stored pointers to functions.
    using FunctionPtr = Result(*)(Args...) noexcept(IsNoexcept);

    // Constructs a SwitchStatement for the given array of function pointers.
    // This constructor is intentionally marked consteval to ensure that
    // SwitchStatement is always constructed at compile time.
    // \param function_pointers - input array of function pointers.
    //        Note that the constructor doesn't check if any pointer is null - this allows emulating
    //        unreachable cases.
    explicit consteval SwitchStatement(std::array<FunctionPtr, NumLabels> function_pointers) noexcept;

    // Executes the switch statement.
    // \param condition - the value of the condition. This will be used to determine which underlying function to call.
    // \param args... - arguments to pass to the underlying function.
    // \return the result of invoking the underlying function.
    // \throw std::invalid_argument if the integral value of @condition is outside of [0; NumLabels).
    constexpr Result operator()(ConditionType condition, Args... args) const;

  private:
    std::array<FunctionPtr, NumLabels> function_pointers;
  };

  // Generates a SwitchStatement for the specified function template.
  // \param ConditionType - type of the switch condition. This must be either an integral type or an enumeration type.
  // \param NumLabels - the number of labels to generate for the SwitchStatement.
  // \param FunctionPtrTemplateAlias - class template or alias template whose instantiations are
  //            std::integral_constant<FunctionPtrType, FunctionPtr>,
  //        where 
  //            FunctionPtrType is the type of a pointer to non-member function,
  //            FunctionPtr is a constant of the type FunctionPtrType.
  //        Each instantiation should have the same FunctionPtrType; FunctionPtr, obviously, may differ.
  // \return the generated SwitchStatement.
  template<class ConditionType, std::size_t NumLabels, template<ConditionType> class FunctionPtrTemplateAlias>
  consteval auto generateSwitchStatement();

  // Helper alias for a type that wraps a compile-time constant with the specified value.
  // \param Value - value to wrap.
  template<auto Value>
  using StaticConstant = std::integral_constant<decltype(Value), Value>;

  // ============================================================
  // All code below is implementation details.
  // ------------------------------------------------------------
  namespace Detail_NS
  {
    // Type trait that provides the appropriate insantiation of SwitchStatement for
    // functions of the specified type.
    template<class ConditionType, std::size_t NumLabels, class FunctionPtrSignature>
    struct SwitchStatementTraits {};

    // Partial specialization for function types that aren't noexcept
    template<class ConditionType, std::size_t NumLabels, class Result, class... Args>
    struct SwitchStatementTraits<ConditionType, NumLabels, Result(*)(Args...)>
    {
      using type = SwitchStatement<ConditionType, NumLabels, false, Result, Args...>;
    };

    // Partial specialization for function types that are noexcept
    template<class ConditionType, std::size_t NumLabels, class Result, class... Args>
    struct SwitchStatementTraits<ConditionType, NumLabels, Result(*)(Args...) noexcept>
    {
      using type = SwitchStatement<ConditionType, NumLabels, true, Result, Args...>;
    };

    // Helper alias for SwitchStatementTraits.
    template<class ConditionType, std::size_t NumLabels, class FunctionPtrSignature>
    using SwitchStatementTraits_t = typename SwitchStatementTraits<ConditionType, NumLabels, FunctionPtrSignature>::type;

    // Constructs an array of function pointers from the given template (class template or alias template).
    // \param ConditionType - type of the template parameter.
    // \param N - the number of elements in the output array. N
    // \param TemplateAlias - class template or alias template. Each instantiation should be
    //            std::integral_constant<FunctionPtrType, FunctionPtr>,
    //        where
    //            FunctionPtrType is the type of a pointer to non-member function,
    //            FunctionPtr is a constant of the type FunctionPtrType.
    //        Each instantiation should have the same FunctionPtrType; FunctionPtr, obviously, may differ.
    template<class ConditionType, std::size_t N, template<ConditionType> class TemplateAlias>
    consteval
    std::array<typename TemplateAlias<static_cast<ConditionType>(0)>::value_type, N>
    makeArrayOfValuesFromTemplateAlias()
    {
      // Check that the number of elements is nonzero.
      // 0 is problematic because the type of the elements is determined by instantiating the input template.
      static_assert(N > 0, "N must be greater than 0");
      // TODO: check at compile time that
      // * each instantiaion TemplateAlias<0>, TemplateAlias<1>, ..., TemplateAlias<N-1> is std::integral_constant.
      // * that they all have the same value_type.
      using value_type = typename TemplateAlias<static_cast<ConditionType>(0)>::value_type;
      return [] <std::size_t... indices>
             (std::index_sequence<indices...> seq)
             consteval
             {
               return std::array<value_type, sizeof...(indices)>
               {
                 TemplateAlias<static_cast<ConditionType>(indices)>::value...
               };
             }(std::make_index_sequence<N>{});
    }

    // Computes the index of the function pointer in SwitchStatement::function_pointers for the given condition value.
    // \param condition - input condition value.
    // \return the 0-based index of the function pointer in SwitchStatement::function_pointers
    //         corresponding to @condition.
    template<class ConditionType>
    constexpr std::size_t getFunctionIndex(ConditionType condition) noexcept
    {
      // Type of the underlying integer type if ConditionType is an enumeration type,
      // or ConditionType itself otherwise (i.e. if it's an integral type).
      using UnderlyingType = typename std::conditional_t<std::is_enum_v<ConditionType>, std::underlying_type<ConditionType>,
                                                                                        std::type_identity<ConditionType>>::type;
      // Unsigned counterpart of UnderlyingType.
      using UnderlyingTypeUnsigned = std::make_unsigned_t<UnderlyingType>;
      // Cast to UnderlyingTypeUnsigned first, then to std::size_t.
      return static_cast<std::size_t>(static_cast<UnderlyingTypeUnsigned>(condition));
    }
  }

  template<class ConditionType, std::size_t NumLabels, bool IsNoexcept, class Result, class... Args>
  consteval
  SwitchStatement<ConditionType, NumLabels, IsNoexcept, Result, Args...>::SwitchStatement(
    std::array<FunctionPtr, NumLabels> function_pointers) noexcept
    : function_pointers{ function_pointers }
  {}

  template<class ConditionType, std::size_t NumLabels, bool IsNoexcept, class Result, class... Args>
  constexpr
  Result
  SwitchStatement<ConditionType, NumLabels, IsNoexcept, Result, Args...>::operator()(ConditionType condition,
                                                                                     Args... args) const
  {
    const std::size_t function_index = Detail_NS::getFunctionIndex(condition);
    if (function_index >= NumLabels)
    {
      throw std::invalid_argument("SwitchStatement: invalid condition value.");
    }
    const FunctionPtr function_ptr = function_pointers[function_index];
    return function_ptr(std::forward<Args>(args)...);
  }

  template<class ConditionType, std::size_t NumLabels, template<ConditionType> class FunctionPtrTemplateAlias>
  consteval auto generateSwitchStatement()
  {
    using FunctionPtr = typename FunctionPtrTemplateAlias<static_cast<ConditionType>(0)>::value_type;
    // TODO: check that FunctionPtr is actually a pointer to function.
    using SwitchStatementType = Detail_NS::SwitchStatementTraits_t<ConditionType, NumLabels, FunctionPtr>;
    constexpr std::array<FunctionPtr, NumLabels> function_pointers =
      Detail_NS::makeArrayOfValuesFromTemplateAlias<ConditionType, NumLabels, FunctionPtrTemplateAlias>();
    return SwitchStatementType{ function_pointers };
  }
}
