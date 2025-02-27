#include <h3mtxt/H3JsonReader/H3JsonReader.h>
#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m::H3JsonReader_NS
{
  CreatureStack JsonReader<CreatureStack>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CreatureStack>;
    CreatureStack creature_stack;
    readField(creature_stack.type, value, Fields::kType);
    readField(creature_stack.count, value, Fields::kCount);
    return creature_stack;
  }
}
