#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/H3JsonReader/VariantJsonReader.h>
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

  template<>
  struct JsonReader<StartingBonusDetails<StartingBonusType::Creature>>
  {
    StartingBonusDetails<StartingBonusType::Creature> operator()(const Json::Value& value) const
    {
      StartingBonusDetails<StartingBonusType::Creature> details;
      readField(details.hero, value, "hero");
      readField(details.creature_stack, value, "creature_stack");
      return details;
    }
  };

  StartingBonus JsonReader<StartingBonus>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingBonus>;
    StartingBonus bonus;
    const StartingBonusType starting_bonus_type = readField<StartingBonusType>(value, Fields::kType);
    VariantJsonReader<StartingBonus::Details> variant_reader{};
    bonus.details = variant_reader(getJsonField(value, Fields::kDetails),
                                   StartingBonus::getAlternativeIdx(starting_bonus_type));
    return bonus;
  }
}
