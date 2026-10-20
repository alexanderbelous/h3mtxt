#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/SavedGame/ObjectPropertiesData.h>
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
    else if constexpr (T == ObjectPropertiesType::Floatsam)
    {
      out.writeField("content", properties.content);
    }
    else if constexpr (T == ObjectPropertiesType::FountainOfFortune)
    {
      out.writeField("reserved1", properties.reserved1);
      out.writeField("reserved2", properties.reserved2);
      out.writeField("luck_bonus", properties.luck_bonus);
      out.writeField("reserved3", properties.reserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Garrison)
    {
      out.writeField("index", properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::LeanTo)
    {
      out.writeField("index", properties.index);
      out.writeField("reserved1", properties.reserved1);
      out.writeField("quantity", properties.quantity);
      out.writeField("resource_type", properties.resource_type);
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
    else
    {
      static_assert(false, "Not implemented.");
    }
  }

  namespace
  {
    template<ObjectPropertiesType T>
    void writeObjectPropertiesImpl(FieldsWriter& out, const h3svg::ObjectPropertiesData& properties)
    {
      JsonObjectWriter<ObjectProperties<T>>{}(out, properties.get<T>());
    }

    template<ObjectPropertiesType T>
    using writeObjectPropertiesImplAlias = SwitchStatement_NS::StaticConstant<&writeObjectPropertiesImpl<T>>;
  }

  void writeObjectProperties(FieldsWriter& out,
                             const h3svg::ObjectPropertiesData& properties,
                             h3svg::ObjectClass object_class)
  {
    static constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<ObjectPropertiesType,
                                                  h3svg::kNumObjectPropertiesTypes,
                                                  writeObjectPropertiesImplAlias>();

    const h3svg::ObjectPropertiesType object_properties_type = h3svg::getObjectPropertiesType(object_class);
    switch_statement(object_properties_type, out, properties);
  }
}
