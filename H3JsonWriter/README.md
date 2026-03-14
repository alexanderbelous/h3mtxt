# Serialization of `h3m::Map` and `h3m::Campaign` into JSON

* [H3MJsonWriter](H3MJsonWriter) is a library for serializing `h3m::Map` into JSON.
* [H3CJsonWriter](H3CJsonWriter) is a library for serializing `h3m::Campaign` into JSON.

The function [`h3m::writeH3mJson()`](H3MJsonWriter/writeH3mJson.h) serializes the entire `h3m::Map` into the output stream. More granular serialization is also possible via `Medea_NS::writeJson`:

```cpp
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Medea/Medea.h>

void writeMapBasicInfoJson(std::ostream& stream, const h3m::MapBasicInfo& map_basic_info)
{
  Medea_NS::writeJson(stream, map_basic_info);
}
```
