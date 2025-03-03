#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  StartingOptions JsonReader<StartingOptions>::operator()(const Json::Value& value) const
  {
    const StartingOptionsType starting_options_type = readField<StartingOptionsType>(value, "type");
    switch (starting_options_type)
    {
    case StartingOptionsType::None:
      return StartingOptionsDetails<StartingOptionsType::None>();
    case StartingOptionsType::StartingBonus:
    case StartingOptionsType::HeroCrossover:
    case StartingOptionsType::StartingHero:
      // TODO: implement.
      throw std::runtime_error("JsonReader<StartingOptions>: NotImplemented.");
    default:
      throw std::runtime_error("JsonReader<StartingOptions>: invalid starting_options_type.");
    }
  }
}
