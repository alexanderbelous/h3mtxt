#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/StartingBonus.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  template<StartingBonusType T>
  struct JsonReader<StartingBonusDetails<T>>
  {
    StartingBonusDetails<T> operator()(const Json::Value&) const
    {
      throw std::runtime_error("JsonReader<StartingBonusDetails<T>>: NotImplemented.");
    }
  };

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Spell>>
  {
    StartingBonusDetails<StartingBonusType::Spell> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Spell> details;
      readField(details.hero, value, "hero");
      readField(details.spell, value, "spell");
      return details;
    }
  };

  // Utility class for deserializing std::variant.
  template<class T>
  class VariantJsonReader;

  template<class... Types>
  class VariantJsonReader<std::variant<Types...>>
  {
    static constexpr std::size_t kNumAlternatives = sizeof...(Types);

    using Variant = std::variant<Types...>;

    // Deserializes the specified alternative from JSON and returns it as std::variant.
    template<std::size_t N>
    static Variant readAlternative(const Json::Value& value)
    {
      using Alternative = std::variant_alternative_t<N, Variant>;
      return Variant(std::in_place_index<N>, JsonReader<Alternative>{}(value));
    }

    // Type of a pointer to a function that takes const Json::Value& and returns Variant.
    using AlternativeReaderPtr = Variant(*)(const Json::Value&);

    // Generate (at compile time) an array of function pointers for each instantiation of
    // readAlternative().
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
    Variant operator()(const Json::Value& value, std::size_t index) const
    {
      return kReaders.at(index)(value);
    }
  };

  const Json::Value& getJsonField(const Json::Value& value, std::string_view field_name)
  {
    if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
    {
      return *field;
    }
    throw MissingJsonFieldError(field_name);
  }

  StartingBonus JsonReader<StartingBonus>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingBonus>;
    const StartingBonusType starting_bonus_type = readField<StartingBonusType>(value, Fields::kType);

    StartingBonus bonus;
    VariantJsonReader<StartingBonus::Details> variant_reader {};
    // The N-th alternative of StartingBonus::Details is StartingBonusDetails<static_cast<StartingBonusType>(N)>,
    // so we can simply cast starting_bonus_type to StartingBonusType to get the index of the alternative.
    const std::size_t variant_alternative_idx = static_cast<std::size_t>(starting_bonus_type);
    bonus.details = variant_reader(getJsonField(value, Fields::kDetails), variant_alternative_idx);
    return bonus;
  }
}
