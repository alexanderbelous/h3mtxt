#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/JsonWriter.h>
#include <h3mtxt/Map/Map.h>

#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    // Helper class to pass map_size to JsonValueWriter when writing Map::tiles.
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

    // Wrapper for std::vector<Object> that also keeps a reference to
    // std::vector<h3m::ObjectTemplate>.
    class WrappedObjects
    {
    public:
      constexpr WrappedObjects(const std::vector<h3m::ObjectTemplate>& objects_templates,
                               const std::vector<h3m::Object>& objects) noexcept:
        objects_templates(objects_templates),
        objects(objects)
      {}

      const std::vector<h3m::ObjectTemplate>& objects_templates;
      const std::vector<h3m::Object>& objects;
    };

    // Wrapper for Object that also keeps a reference to all objects' templates.
    class WrappedObject
    {
    public:
      constexpr WrappedObject(const std::vector<h3m::ObjectTemplate>& objects_templates,
                              const h3m::Object& object) noexcept:
        objects_templates(objects_templates),
        object(object)
      {}

      const std::vector<h3m::ObjectTemplate>& objects_templates;
      const h3m::Object& object;
    };
  }

  // Explicit specialization for std::array<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>
  // to print comments.
  template<>
  struct JsonArrayWriter<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>>
  {
    void operator()(const ArrayElementsWriter& scoped_array_writer,
                    const std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>& players) const
    {
      h3m::H3JsonWriter_NS::CommentBuilder comment_builder;
      for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        const h3m::PlayerColor player = static_cast<h3m::PlayerColor>(i);
        const std::string_view player_str = h3m::getEnumString(player);
        scoped_array_writer.writeComment(comment_builder.build({ "Player ", i, " (", player_str, ")" }));
        scoped_array_writer.writeElement(players[i]);
      }
    }
  };

  // Serialize TilesWithMapSize as a JSON array.
  template<>
  struct JsonArrayWriter<TilesWithMapSize>
  {
    void operator()(const ArrayElementsWriter& scoped_array_writer, const TilesWithMapSize& value) const
    {
      h3m::H3JsonWriter_NS::CommentBuilder comment_builder;
      const std::uint32_t num_levels = value.hasTwoLevels() ? 2 : 1;
      const std::uint32_t map_size = value.mapSize();
      const std::span<const h3m::Tile> tiles = value.tiles();
      auto iter = tiles.begin();
      for (std::uint32_t z = 0; z < num_levels; ++z)
      {
        for (std::uint32_t y = 0; y < map_size; ++y)
        {
          for (std::uint32_t x = 0; x < map_size; ++x)
          {
            scoped_array_writer.writeComment(comment_builder.build({ "Tile (", x, ", ", y, ", ", z, ")" }));
            scoped_array_writer.writeElement(*iter);
            ++iter;
          }
        }
      }
    }
  };

  template<>
  struct JsonObjectWriter<WrappedObject>
  {
    void operator()(FieldsWriter& out, const WrappedObject& wrapped_object) const
    {
      const JsonObjectWriter<h3m::Object> object_writer(wrapped_object.objects_templates.data(),
                                                        wrapped_object.objects_templates.size());
      object_writer(out, wrapped_object.object);
    }
  };

  // Serialize WrappedObjects as a JSON array.
  template<>
  struct JsonArrayWriter<WrappedObjects>
  {
    void operator()(const ArrayElementsWriter& scoped_array_writer, const WrappedObjects& wrapped_objects) const
    {
      h3m::H3JsonWriter_NS::CommentBuilder comment_builder;
      for (std::size_t i = 0; i < wrapped_objects.objects.size(); ++i)
      {
        scoped_array_writer.writeComment(comment_builder.build({ "Object ", i }));
        scoped_array_writer.writeElement(WrappedObject(wrapped_objects.objects_templates, wrapped_objects.objects[i]));
      }
    }
  };

  void JsonObjectWriter<h3m::Map>::operator()(FieldsWriter& out, const h3m::Map& map) const
  {
    using FieldNames = h3m::FieldNames<h3m::Map>;

    out.writeField(FieldNames::kFormat, map.format);
    out.writeField(FieldNames::kBasicInfo, map.basic_info);
    out.writeField(FieldNames::kPlayers, map.players);
    out.writeField(FieldNames::kAdditionalInfo, map.additional_info);
    // Not writing tiles directly because I want to write each tile's coordinates in a comment.
    out.writeField(FieldNames::kTiles, TilesWithMapSize(map.tiles, map.basic_info.map_size, map.basic_info.has_two_levels));
    out.writeField(FieldNames::kObjectsTemplates, map.objects_templates);
    // Not writing objects directly because I want to write ObjectClass for each object in a comment.
    out.writeField(FieldNames::kObjects, WrappedObjects(map.objects_templates, map.objects));
    out.writeField(FieldNames::kGlobalEvents, map.global_events);
    out.writeField(FieldNames::kPadding, map.padding);
  }
}
