#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonArrayWriter<h3m::SpriteTilesBitmask>::operator()(const ArrayElementsWriter& elements_writer,
                                                            const h3m::SpriteTilesBitmask& sprite_tiles_bitmask) const
  {
    h3m::H3JsonWriter_NS::Detail_NS::printBitSetImpl(elements_writer, sprite_tiles_bitmask.data);
  }

  void JsonArrayWriter<h3m::TerrainsBitmask>::operator()(const ArrayElementsWriter& elements_writer,
                                                         const h3m::TerrainsBitmask& bitmask) const
  {
    JsonArrayWriter<h3m::BitSet<2>>{}(elements_writer, bitmask.bitset);
  }

  void JsonObjectWriter<h3m::ObjectTemplate>::operator()(FieldsWriter& out, const h3m::ObjectTemplate& value) const
  {
    using Fields = h3json::FieldNames<h3m::ObjectTemplate>;
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
