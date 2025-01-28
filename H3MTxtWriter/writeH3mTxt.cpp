#include <h3mtxt/H3MTxtWriter/writeH3mTxt.h>

#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeGlobalEvent.h>
#include <h3mtxt/H3MTxtWriter/writeMapBasicInfo.h>
#include <h3mtxt/H3MTxtWriter/writeMapAdditionalInfo.h>
#include <h3mtxt/H3MTxtWriter/writeObjectAttributes.h>
#include <h3mtxt/H3MTxtWriter/writeObjectDetailsData.h>
#include <h3mtxt/H3MTxtWriter/writePlayerSpecs.h>
#include <h3mtxt/H3MTxtWriter/writeTile.h>

#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace Util_NS
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
        constexpr std::string kEmptyString;
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

    // Wrapper for std::vector<ObjectDetails> that also keeps a reference to
    // std::vector<h3m::ObjectAttributes>.
    class H3MObjects
    {
    public:
      constexpr H3MObjects(const std::vector<h3m::ObjectAttributes>& objects_attributes,
                           const std::vector<h3m::ObjectDetails>& objects_details) noexcept:
        attributes(objects_attributes),
        details(objects_details)
      {}

      const std::vector<h3m::ObjectAttributes>& attributes;
      const std::vector<h3m::ObjectDetails>& details;
    };

    // Wrapper for ObjectDetails that also keeps a reference to the corresponding
    // ObjectAttributes.
    class H3MObject
    {
    public:
      constexpr H3MObject(const h3m::ObjectAttributes& object_attributes,
                          const h3m::ObjectDetails& object_details) noexcept:
        attributes(object_attributes),
        details(object_details)
      {}

      const h3m::ObjectAttributes& attributes;
      const h3m::ObjectDetails& details;
    };
  }

  // Explicit specialization for std::array<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>
  // to print comments.
  template<>
  struct ValueWriter<std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>>
  {
    void operator()(IndentedTextWriter& out, const std::array<h3m::PlayerSpecs, h3m::kMaxPlayers>& players) const
    {
      CommentBuilder comment_builder;
      ScopedArrayWriter<h3m::PlayerSpecs> array_writer = out.writeArray<h3m::PlayerSpecs>();
      for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
      {
        array_writer.writeComment(comment_builder.build("Player ", i));
        array_writer.writeElement(players[i]);
      }
    }
  };

  template<>
  struct ValueWriter<TilesWithMapSize>
  {
    void operator()(IndentedTextWriter& out, const TilesWithMapSize& value) const
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
  struct StructWriter<H3MObject>
  {
    void operator()(FieldsWriter& out, const H3MObject& object) const
    {
      const h3m::ObjectClass object_class = object.attributes.object_class;
      const h3m::MetaObjectType meta_object_type = object.details.details.getMetaObjectType();
      const std::string_view object_class_name = h3m::getEnumString(object_class);
      const std::string_view meta_object_type_name = h3m::getEnumString(meta_object_type);

      out.writeField("x", object.details.x);
      out.writeField("y", object.details.y);
      out.writeField("z", object.details.z);
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
      out.writeField("kind", object.details.kind);
      out.writeField("unknown", object.details.unknown);
      if (meta_object_type != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
      {
        object.details.details.visit(
          [&out](auto&& details)
          {
            out.writeField("details", std::forward<decltype(details)>(details));
          });
      }
    }

  private:
    mutable CommentBuilder comment_builder_;
  };

  template<>
  struct ValueWriter<H3MObjects>
  {
    void operator()(IndentedTextWriter& out, const H3MObjects& objects) const
    {
      CommentBuilder comment_builder;
      ScopedArrayWriter<H3MObject> array_writer = out.writeArray<H3MObject>();
      for (std::size_t i = 0; i < objects.details.size(); ++i)
      {
        array_writer.writeComment(comment_builder.build("Object ", i));
        const h3m::ObjectDetails& details = objects.details[i];
        const h3m::ObjectAttributes& attributes = objects.attributes.at(details.kind);
        array_writer.writeElement(H3MObject(attributes, details));
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
      // Not writing object_details directly because I want to write ObjectClass for each object in a comment.
      out.writeField("objects_details", H3MObjects(map.objects_attributes, map.objects_details));
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
