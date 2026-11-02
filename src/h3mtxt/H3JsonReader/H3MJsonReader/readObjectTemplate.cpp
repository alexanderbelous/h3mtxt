#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/ObjectTemplate.h>

namespace h3json
{
  template<>
  h3m::SpriteTilesBitmask JsonReader2<h3m::SpriteTilesBitmask>::operator()() const
  {
    return h3m::SpriteTilesBitmask{ .data = fromJson<std::array<std::uint8_t, 6>>(value()) };
  }

  template<>
  h3m::ObjectTemplate JsonReader2<h3m::ObjectTemplate>::operator()() const
  {
    using Fields = FieldNames<h3m::ObjectTemplate>;
    h3m::ObjectTemplate object_template;
    readField(Fields::kDef, object_template.def);
    readField(Fields::kPassability, object_template.passability);
    readField(Fields::kActionability, object_template.actionability);
    readField(Fields::kAllowedLandscapes, object_template.allowed_landscapes);
    readField(Fields::kLandscapeGroup, object_template.landscape_group);
    readField(Fields::kObjectClass, object_template.object_class);
    readField(Fields::kObjectSubclass, object_template.object_subclass);
    readField(Fields::kObjectGroup, object_template.object_group);
    readField(Fields::kIsGround, object_template.is_ground);
    readField(Fields::kUnknown, object_template.unknown);
    return object_template;
  }
}
