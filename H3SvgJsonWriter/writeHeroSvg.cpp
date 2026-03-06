#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/HeroSvg.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::HeroSvg>::operator()(FieldsWriter& out, const h3m::HeroSvg& hero) const
  {
    using Fields = h3m::FieldNames<h3m::HeroSvg>;

    out.writeField(Fields::kX, hero.x);
    out.writeField(Fields::kY, hero.y);
    out.writeField(Fields::kZ, hero.z);
    out.writeField(Fields::kIsVisible, hero.is_visible);
    out.writeField(Fields::kCoordinatesPacked, hero.coordinates_packed);
    out.writeField(Fields::kObjectClassUnder, hero.object_class_under);
    if (auto enum_str = h3m::getEnumString(hero.object_class_under); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown1, hero.unknown1);
    out.writeField(Fields::kBiography, hero.biography);
    out.writeField(Fields::kUnknown2, hero.unknown2);
    out.writeField(Fields::kArmy, hero.army);
    out.writeField(Fields::kName, hero.name);
    out.writeField(Fields::kUnknown3, hero.unknown3);
  }
}
