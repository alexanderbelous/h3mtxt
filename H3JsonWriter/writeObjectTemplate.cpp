#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectTemplate.h>

namespace Medea_NS
{
  void JsonArrayWriter<h3m::TerrainsBitmask>::operator()(ScopedArrayWriter<std::uint8_t>& elements_writer,
                                                         const h3m::TerrainsBitmask& bitmask) const
  {
    writeArray(bitmask.bitset, elements_writer);
  }

  void JsonObjectWriter<h3m::ObjectTemplate>::operator()(FieldsWriter& out, const h3m::ObjectTemplate& value) const
  {
    using Fields = h3m::FieldNames<h3m::ObjectTemplate>;
    out.writeField(Fields::kDef, value.def);
    out.writeField(Fields::kPassability, value.passability);
    out.writeField(Fields::kActionability, value.actionability);
    out.writeField(Fields::kAllowedLandscapes, value.allowed_landscapes);
    out.writeField(Fields::kLandscapeGroup, value.landscape_group);
    out.writeField(Fields::kObjectClass, value.object_class);
    if (std::string_view enum_str = h3m::getEnumString(value.object_class); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, value.object_subclass);
    out.writeField(Fields::kObjectGroup, value.object_group);
    if (std::string_view enum_str = h3m::getEnumString(value.object_group); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kIsGround, value.is_ground);
    out.writeField(Fields::kUnknown, value.unknown);
  }
}
