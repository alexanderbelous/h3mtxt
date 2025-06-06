#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3m::H3Writer_NS
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
        throw std::runtime_error("H3Writer<Map>: Wrong number of elements in Map::tiles.");
      }
      // Check that each Object refers to an existing ObjectTemplate and has the same ObjectPropertiesType.
      for (const Object& object : map.objects)
      {
        if (object.template_idx >= map.objects_templates.size())
        {
          throw std::runtime_error("H3Writer<Map>: Object::template_idx is out of range.");
        }
        const ObjectTemplate& object_template = map.objects_templates[object.template_idx];
        if (object.properties.type() !=
            getObjectPropertiesType(object_template.object_class, object_template.object_subclass))
        {
          throw std::runtime_error("H3Writer<Map>: Object::properties has ObjectPropertiesType different "
                                   "from the ObjectTemplate it refers to.");
        }
      }
    }
  }

  void H3Writer<Map>::operator()(std::ostream& stream, const Map& map) const
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
    writeVector<std::uint32_t>(stream, map.objects_templates);
    writeVector<std::uint32_t>(stream, map.objects);
    writeVector<std::uint32_t>(stream, map.global_events);
    writeData(stream, map.padding);
  }
}
