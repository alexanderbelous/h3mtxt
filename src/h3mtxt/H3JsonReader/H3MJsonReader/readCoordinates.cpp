#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Coordinates.h>

namespace h3json
{
  h3m::Coordinates JsonReader<h3m::Coordinates>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Coordinates>;
    h3m::Coordinates coordinates;
    readField(coordinates.x, value, Fields::kX);
    readField(coordinates.y, value, Fields::kY);
    readField(coordinates.z, value, Fields::kZ);
    return coordinates;
  }
}
