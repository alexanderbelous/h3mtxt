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
  namespace
  {
    // Checks that the given map is "grammatically correct".
    //
    // writeh3m() allows using seemingly incorrect values as long as the map can
    // be parsed. There are, however, a few cases where the input h3m::Map object
    // cannot be serialized into a .h3m file because it violates one or more
    // "grammatic" rules - it would be impossible to parse such a file.
    void checkMap(const h3m::Map& map)
    {
      // Check that the number of tiles is correct.
      if (map.tiles.size() != countTiles(map.basic_info))
      {
        throw std::runtime_error("Wrong number of elements in Map.tiles.");
      }
      // Check that each ObjectDetails refers to an existing ObjectAttributes and
      // has the same MetaObjectType.
      for (const ObjectDetails& object_details : map.objects_details)
      {
        if (object_details.kind >= map.objects_attributes.size())
        {
          throw std::runtime_error("writeh3m(): ObjectDetails.kind is out of range.");
        }
        const ObjectAttributes& object_attributes = map.objects_attributes[object_details.kind];
        const MetaObjectType meta_object_type_expected = getMetaObjectType(object_attributes.object_class);
        if (object_details.details.getMetaObjectType() != meta_object_type_expected)
        {
          throw std::runtime_error("writeh3m(): ObjectDetails.details has MetaObjectType different "
                                   "from the ObjectAttributes it refers to.");
        }
      }
    }
  }

  template<>
  struct H3MWriter<Map>
  {
    void operator()(std::ostream& stream, const Map& map) const
    {
      // Check tha the map is grammatically (not necessarily semantically) correct.
      checkMap(map);

      writeData(stream, map.format);
      writeData(stream, map.basic_info);
      writeData(stream, map.players);
      writeData(stream, map.additional_info);
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
