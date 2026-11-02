#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Coordinates.h>

namespace h3json
{
  template<>
  h3m::Coordinates JsonReader2<h3m::Coordinates>::operator()() const
  {
    using Fields = FieldNames<h3m::Coordinates>;
    h3m::Coordinates coordinates;
    readField(Fields::kX, coordinates.x);
    readField(Fields::kY, coordinates.y);
    readField(Fields::kZ, coordinates.z);
    return coordinates;
  }
}
