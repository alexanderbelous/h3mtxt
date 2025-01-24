#include <h3mtxt/H3MWriter/writeh3m.h>

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/H3MWriter/writeGlobalEvent.h>
#include <h3mtxt/H3MWriter/writeMapAdditionalInfo.h>
#include <h3mtxt/H3MWriter/writeMapBasicInfo.h>
#include <h3mtxt/H3MWriter/writeObjectAttributes.h>
#include <h3mtxt/H3MWriter/writeObjectDetails.h>
#include <h3mtxt/H3MWriter/writePlayerSpecs.h>
#include <h3mtxt/H3MWriter/writeTile.h>
#include <h3mtxt/Map/Map.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <stdexcept>

namespace h3m
{
  template<>
  struct H3MWriter<Map>
  {
    void operator()(std::ostream& stream, const Map& map) const
    {
      writeData(stream, map.format);
      writeData(stream, map.basic_info);
      writeData(stream, map.players);
      writeData(stream, map.additional_info);
      // Write tiles.
      if (map.tiles.size() != countTiles(map.basic_info))
      {
        throw std::runtime_error("Wrong number of elements in Map.tiles.");
      }
      for (const Tile& tile : map.tiles)
      {
        writeData(stream, tile);
      }
      writeVector<std::uint32_t>(stream, map.objects_attributes);
      writeVector<std::uint32_t>(stream, map.objects_details);
      writeVector<std::uint32_t>(stream, map.global_events);
      writeData(stream, map.padding);
    }
  };

  void writeh3m(std::ostream& stream, const Map& map, bool compress)
  {
    // Ugly hack.
    // C++ guarantees that temporary objects remain valid until the end of the expression,
    // but static_cast cannot be used to convert an rvalue reference to an lvalue reference.
    const auto remove_rvalue_ref = [](zstr::ostream&& stream) -> std::ostream& {return stream; };
    writeData(compress ? remove_rvalue_ref(zstr::ostream(stream)) : stream, map);
  }
}
