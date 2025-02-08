# Serialization of `h3m::Map` into JSON

This module doesn't use [jsoncpp](https://github.com/open-source-parsers/jsoncpp) or any other thirdparty library for serialization because I want to add a lot of comments in the output JSON; existing libraries for JSON serialization generally don't have a good API for that.

`h3m::writeH3mJson()` from [writeH3mJson.h](writeH3mJson.h) serializes the entire `h3m::Map` into the output stream. More granular serialization is also possible via `JsonDocumentWriter`:

```cpp
#include <h3mtxt/H3MJsonWriter/writeMapBasicInfo.h>

void writeMapBasicInfo(std::ostream& stream, const h3m::MapBasicInfo& info)
{
  Util_NS::JsonDocumentWriter writer(stream);
  Util_NS::writeValue(writer, info);
}
```
