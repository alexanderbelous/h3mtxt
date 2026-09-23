#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Replay.h>

#include <stdexcept>

namespace h3json
{
  // This template is implicitly instantiated for all valid ReplayEventType
  // in JsonReader<h3svg::ReplayEvent>::operator().
  template<h3svg::ReplayEventType T>
  h3svg::ReplayEventDetails<T>
  JsonReader<h3svg::ReplayEventDetails<T>>::operator()(const Json::Value& /* value */) const
  {
    throw std::logic_error("JsonReader<h3svg::ReplayEventDetails<T>>: Not implemented.");
  }

  template<>
  h3svg::ReplayEvent JsonReader<h3svg::ReplayEvent>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ReplayEvent>;
    const h3svg::ReplayEventType event_type = readField<h3svg::ReplayEventType>(value, Fields::kType);
    return h3svg::ReplayEvent{
      .details = VariantJsonReader<h3svg::ReplayEvent::Details>{}(getJsonField(value, Fields::kDetails),
                                                                  h3svg::ReplayEvent::getAlternativeIdx(event_type))
    };
  }
}
