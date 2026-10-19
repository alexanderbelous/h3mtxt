#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3svg::ObjectProperties;
using ::h3svg::ObjectPropertiesType;

namespace Medea_NS
{
  template<ObjectPropertiesType T>
  void JsonObjectWriter<ObjectProperties<T>>::operator()(FieldsWriter& out,
                                                         const ObjectProperties<T>& properties) const
  {
    //using Fields = h3json::FieldNames<ObjectProperties<T>>;
    if constexpr (T == ObjectPropertiesType::None)
    {
      out.writeField("reserved", properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::BlackMarket)
    {
      out.writeField("index", properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Campfire)
    {
      out.writeField("resource_type", properties.resource_type);
      out.writeField("quantity", properties.quantity);
      out.writeField("reserved", properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::CreatureBank)
    {
      out.writeField("reserved1", properties.reserved1);
      out.writeField("visited_by", properties.visited_by);
      out.writeField("index", properties.index);
      out.writeField("reserved2", properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Dwelling)
    {
      out.writeField("index", properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Corpse)
    {
      out.writeField("id", properties.id);
      out.writeField("reserved1", properties.reserved1);
      out.writeField("artifact", properties.artifact);
      out.writeField("is_lootable", properties.is_lootable);
      out.writeField("reserved2", properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::SeersHut)
    {
      out.writeField("index", properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Shrine)
    {
      out.writeField("reserved1", properties.reserved1);
      out.writeField("visited_by", properties.visited_by);
      out.writeField("spell", properties.spell);
      out.writeField("reserved2", properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Sign)
    {
      out.writeField("index", properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::University)
    {
      out.writeField("reserved1", properties.reserved1);
      out.writeField("reserved2", properties.reserved2);
      out.writeField("index", properties.index);
      out.writeField("reserved3", properties.reserved3);
    }
    else if constexpr (T == ObjectPropertiesType::WitchHut)
    {
      out.writeField("reserved1", properties.reserved1);
      out.writeField("reserved2", properties.reserved2);
      out.writeField("skill", properties.skill);
      out.writeField("visited_by", properties.visited_by);
    }
  }

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::None>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::None>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::BlackMarket>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::BlackMarket>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::Campfire>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::Campfire>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::CreatureBank>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::CreatureBank>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::Dwelling>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::Dwelling>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::Corpse>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::Corpse>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::SeersHut>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::SeersHut>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::Shrine>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::Shrine>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::Sign>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::Sign>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::University>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::University>&) const;

  template
  void JsonObjectWriter<ObjectProperties<ObjectPropertiesType::WitchHut>>::operator()(
    FieldsWriter& out, const ObjectProperties<ObjectPropertiesType::WitchHut>&) const;
}
