# Serialization of `h3m::Map` into JSON

`h3m::writeH3mJson()` from [writeH3mJson.h](writeH3mJson.h) serializes the entire `h3m::Map` into the output stream. More granular serialization is also possible via `Medea_NS::JsonDocumentWriter`:

```cpp
#include <h3mtxt/H3MJsonWriter/writeMapBasicInfo.h>

void writeMapBasicInfo(std::ostream& stream, const h3m::MapBasicInfo& info)
{
  Medea_NS::JsonDocumentWriter writer(stream);
  Medea_NS::writeValue(writer, info);
}
```
