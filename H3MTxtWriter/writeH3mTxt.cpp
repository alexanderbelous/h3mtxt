#include <h3mtxt/H3MTxtWriter/writeH3mTxt.h>

#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeGlobalEvent.h>
#include <h3mtxt/H3MTxtWriter/writeMapBasicInfo.h>
#include <h3mtxt/H3MTxtWriter/writeMapAdditionalInfo.h>
#include <h3mtxt/H3MTxtWriter/writeObjectAttributes.h>
#include <h3mtxt/H3MTxtWriter/writeObjectDetailsData.h>
#include <h3mtxt/H3MTxtWriter/writePlayerSpecs.h>
#include <h3mtxt/H3MTxtWriter/writeTile.h>

#include <span>
#include <stdexcept>
#include <string_view>
#include <type_traits>

namespace Util_NS
{
  namespace
  {
    // Helper class to pass map_size to ValueWriter when writing Map::tiles.
    class TilesWithMapSize
    {
    public:
      constexpr TilesWithMapSize(std::span<const h3m::Tile> tiles, std::uint32_t map_size, bool has_two_levels):
        tiles_(tiles),
        map_size_(map_size),
        has_two_levels_(has_two_levels)
      {
        const std::size_t num_levels = has_two_levels ? 2 : 1;
        const std::size_t expected_num_tiles = num_levels * map_size * map_size;
        if (tiles.size() != expected_num_tiles)
        {
          throw std::runtime_error("Wrong number of tiles in Map.tiles.");
        }
      }

      constexpr std::span<const h3m::Tile> tiles() const noexcept
      {
        return tiles_;
      }

      constexpr std::uint32_t mapSize() const noexcept
      {
        return map_size_;
      }

      constexpr bool hasTwoLevels() const noexcept
      {
        return has_two_levels_;
      }

    private:
      std::span<const h3m::Tile> tiles_;
      std::uint32_t map_size_ = 0;
      bool has_two_levels_ = false;
    };
  }

  // Explicit specialization for std::array<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>
  // to print comments.
  template<>
  struct ValueWriter<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>>
  {
    void operator()(IndentedTextWriter& out, const std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>& players) const
    {
      ScopedArrayWriter<h3m::PlayerSpecs> array_writer = out.writeArray<h3m::PlayerSpecs>();
      for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        array_writer.writeComment(std::string{"Player "} + std::to_string(i));
        array_writer.writeElement(players[i]);
      }
    }
  };

  template<>
  struct ValueWriter<TilesWithMapSize>
  {
    void operator()(IndentedTextWriter& out, const TilesWithMapSize& value) const
    {
      const std::uint32_t num_levels = value.hasTwoLevels() ? 2 : 1;
      const std::uint32_t map_size = value.mapSize();
      const std::span<const h3m::Tile> tiles = value.tiles();
      ScopedArrayWriter<h3m::Tile> array_writer = out.writeArray<h3m::Tile>();
      auto iter = tiles.begin();
      for (std::uint32_t z = 0; z < num_levels; ++z)
      {
        for (std::uint32_t y = 0; y < map_size; ++y)
        {
          for (std::uint32_t x = 0; x < map_size; ++x)
          {
            // std::format() would've been nice here, but it still causes bloat, doesn't it? Check.
            array_writer.writeComment(std::string{"Tile ("} + std::to_string(x) + std::string{", "} +
                                      std::to_string(y) + std::string{", "} + std::to_string(z) + std::string{")"});
            array_writer.writeElement(*iter);
            ++iter;
          }
        }
      }
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetails>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectDetails& object_details) const
    {
      out.writeField("x", object_details.x);
      out.writeField("y", object_details.y);
      out.writeField("z", object_details.z);
      // TODO: print ObjectClass and/or MetaObjectType in a comment.
      out.writeField("kind", object_details.kind);
      out.writeField("unknown", object_details.unknown);
      if (object_details.details.getMetaObjectType() != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        object_details.details.visit(
          [&out](auto&& details)
          {
            out.writeField("details", std::forward<decltype(details)>(details));
          });
      }
    }
  };

  template<>
  struct StructWriter<h3m::Map>
  {
    void operator()(FieldsWriter& out, const h3m::Map& map) const
    {
      out.writeField("format", map.format);
      out.writeField("basic_info", map.basic_info);
      out.writeField("players", map.players);
      out.writeField("additional_info", map.additional_info);
      // Not writing tiles directly because I want to write each tile's coordinates in a comment.
      out.writeField("tiles", TilesWithMapSize(map.tiles, map.basic_info.map_size, map.basic_info.has_two_levels));
      out.writeField("objects_attributes", map.objects_attributes);
      out.writeField("objects_details", map.objects_details);
      out.writeField("global_events", map.global_events);
      out.writeField("padding", map.padding);
    }
  };
}

namespace h3m
{
  void writeH3mTxt(std::ostream& stream, const Map& map)
  {
    Util_NS::IndentedTextWriter writer(stream, 0);
    Util_NS::writeValue(writer, map);
  }
}
