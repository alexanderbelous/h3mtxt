# Serialization of `h3m::Map` into JSON

`h3m::writeH3mJson()` from [writeH3mJson.h](writeH3mJson.h) serializes the entire `h3m::Map` into the output stream. More granular serialization is also possible via `Medea_NS::JsonDocumentWriter`:

```cpp
#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>

void writeMapBasicInfoJson(std::ostream& stream, const h3m::MapBasicInfo& map_basic_info)
{
  Medea_NS::JsonDocumentWriter document_writer(stream);
  Medea_NS::JsonValueWriter<h3m::MapBasicInfo> value_writer {};
  value_writer(document_writer, map_basic_info);
}
```
