#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3json
{
  h3m::CreatureStack JsonReader<h3m::CreatureStack>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CreatureStack>;
    h3m::CreatureStack creature_stack;
    readField(creature_stack.type, value, Fields::kType);
    readField(creature_stack.count, value, Fields::kCount);
    return creature_stack;
  }
}
