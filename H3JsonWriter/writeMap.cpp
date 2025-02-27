#include <h3mtxt/H3JsonWriter/writeMap.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/writeGlobalEvent.h>
#include <h3mtxt/H3JsonWriter/writeMapBasicInfo.h>
#include <h3mtxt/H3JsonWriter/writeMapAdditionalInfo.h>
#include <h3mtxt/H3JsonWriter/writeObjectTemplate.h>
#include <h3mtxt/H3JsonWriter/writeObjectDetailsData.h>
#include <h3mtxt/H3JsonWriter/writePlayerSpecs.h>
#include <h3mtxt/H3JsonWriter/writeTile.h>

#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    // Lame alternative for std::format. Not using std::format here because it still causes bloat.
    class CommentBuilder
    {
    public:
      // Appends a value to the comment.
      template<class T>
      CommentBuilder& operator<<(T&& value)
      {
        stream_ << value;
        return *this;
      }

      // Constructs a comment from the input values.
      // First discards the current contents, then appends the values.
      // \return a string_view to the constructed comment.
      template<class... Args>
      std::string_view build(Args&&... args)
      {
        clear();
        const char kUnused[] = { ((void)(stream_ << std::forward<Args>(args)), char(0))... };
        return stream_.view();
      }

      void clear()
      {
        // Replace the contents with an empty string.
        const std::string kEmptyString;
        stream_.str(kEmptyString);
        // Clear state flags.
        stream_.clear();
      }

      std::string_view str() const
      {
        return stream_.view();
      }

    private:
      std::ostringstream stream_;
    };

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
    class H3MObjects
    {
    public:
      constexpr H3MObjects(const std::vector<h3m::ObjectTemplate>& objects_templates,
                           const std::vector<h3m::Object>& objects) noexcept:
        objects_templates(objects_templates),
        objects(objects)
      {}

      const std::vector<h3m::ObjectTemplate>& objects_templates;
      const std::vector<h3m::Object>& objects;
    };

    // Wrapper for Object that also keeps a reference to the corresponding
    // ObjectTemplate.
    class H3MObject
    {
    public:
      constexpr H3MObject(const h3m::ObjectTemplate& object_template,
                          const h3m::Object& object) noexcept:
        object_template(object_template),
        object(object)
      {}

      const h3m::ObjectTemplate& object_template;
      const h3m::Object& object;
    };
  }

  // Explicit specialization for std::array<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>
  // to print comments.
  template<>
  struct JsonValueWriter<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>>
  {
    void operator()(JsonDocumentWriter& out, const std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>& players) const
    {
      CommentBuilder comment_builder;
      ScopedArrayWriter<h3m::PlayerSpecs> array_writer = out.writeArray<h3m::PlayerSpecs>();
      for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        const h3m::PlayerColor player = static_cast<h3m::PlayerColor>(i);
        const std::string_view player_str = h3m::getEnumString(player);
        array_writer.writeComment(comment_builder.build("Player ", i, " (", player_str, ")"));
        array_writer.writeElement(players[i]);
      }
    }
  };

  template<>
  struct JsonValueWriter<TilesWithMapSize>
  {
    void operator()(JsonDocumentWriter& out, const TilesWithMapSize& value) const
    {
      CommentBuilder comment_builder;
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
            array_writer.writeComment(comment_builder.build("Tile (", x, ", ", y, ", ", z, ")"));
            array_writer.writeElement(*iter);
            ++iter;
          }
        }
      }
    }
  };

  template<>
  struct JsonObjectWriter<H3MObject>
  {
    void operator()(FieldsWriter& out, const H3MObject& wrapped_object) const
    {
      using Fields = h3m::FieldNames<h3m::Object>;

      const h3m::Object& object = wrapped_object.object;
      const h3m::ObjectClass object_class = wrapped_object.object_template.object_class;
      const h3m::MetaObjectType meta_object_type = object.details.getMetaObjectType();
      const std::string_view object_class_name = h3m::getEnumString(object_class);
      const std::string_view meta_object_type_name = h3m::getEnumString(meta_object_type);

      out.writeField(Fields::kX, object.x);
      out.writeField(Fields::kY, object.y);
      out.writeField(Fields::kZ, object.z);
      out.writeComma();
      // Print ObjectClass in a comment.
      comment_builder_.clear();
      comment_builder_ << "ObjectClass: " << static_cast<std::size_t>(object_class);
      if (!object_class_name.empty())
      {
        comment_builder_ << " (" << object_class_name << ")";
      }
      out.writeComment(comment_builder_.str());
      // Print MetaObjectType in a comment.
      comment_builder_.clear();
      comment_builder_ << "MetaObjectType: " << static_cast<std::size_t>(meta_object_type);
      if (!meta_object_type_name.empty())
      {
        comment_builder_ << " (" << meta_object_type_name << ")";
      }
      out.writeComment(comment_builder_.str());
      out.writeField(Fields::kKind, object.kind);
      out.writeField(Fields::kUnknown, object.unknown);
      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        object.details.visit(
          [&out](auto&& details)
          {
            out.writeField(Fields::kDetails, std::forward<decltype(details)>(details));
          });
      }
    }

  private:
    mutable CommentBuilder comment_builder_;
  };

  template<>
  struct JsonValueWriter<H3MObjects>
  {
    void operator()(JsonDocumentWriter& out, const H3MObjects& wrapped_objects) const
    {
      CommentBuilder comment_builder;
      ScopedArrayWriter<H3MObject> array_writer = out.writeArray<H3MObject>();
      for (std::size_t i = 0; i < wrapped_objects.objects.size(); ++i)
      {
        array_writer.writeComment(comment_builder.build("Object ", i));
        const h3m::Object& object = wrapped_objects.objects[i];
        const h3m::ObjectTemplate& object_template = wrapped_objects.objects_templates.at(object.kind);
        array_writer.writeElement(H3MObject(object_template, object));
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
    // Not writing object_details directly because I want to write ObjectClass for each object in a comment.
    out.writeField(FieldNames::kObjectsDetails, H3MObjects(map.objects_templates, map.objects));
    out.writeField(FieldNames::kGlobalEvents, map.global_events);
    out.writeField(FieldNames::kPadding, map.padding);
  }
}
