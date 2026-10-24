#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3svg::ObjectProperties;
using ::h3svg::ObjectPropertiesType;

namespace Medea_NS
{
  template<ObjectPropertiesType T>
  void JsonObjectWriter<ObjectProperties<T>>::operator()(FieldsWriter& out,
                                                         const ObjectProperties<T>& properties) const
  {
    using Fields = h3json::FieldNames<ObjectProperties<T>>;
    if constexpr (T == ObjectPropertiesType::None)
    {
      out.writeField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::BlackMarket)
    {
      out.writeField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Campfire)
    {
      out.writeField(Fields::kResourceType, properties.resource_type);
      out.writeField(Fields::kQuantity, properties.quantity);
      out.writeField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::CreatureBank)
    {
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kIndex, properties.index);
      out.writeField(Fields::kIsCleared, static_cast<bool>(properties.is_cleared));
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Dwelling)
    {
      out.writeField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Corpse)
    {
      out.writeField(Fields::kId, properties.id);
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kArtifact, properties.artifact);
      out.writeField(Fields::kIsLootable, properties.is_lootable);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Event)
    {
      out.writeField(Fields::kId, properties.id);
      out.writeField(Fields::kAffectedPlayers, properties.affected_players);
      out.writeField(Fields::kAppliesToComputer, static_cast<bool>(properties.applies_to_computer));
      out.writeField(Fields::kCancelAfterFirstVisit, static_cast<bool>(properties.cancel_after_first_visit));
      out.writeField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::Floatsam)
    {
      out.writeField(Fields::kContent, properties.content);
    }
    else if constexpr (T == ObjectPropertiesType::FountainOfFortune)
    {
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
      out.writeField(Fields::kLuckBonus, properties.luck_bonus);
      out.writeField(Fields::kReserved3, properties.reserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Garrison)
    {
      out.writeField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Hero)
    {
      out.writeField(Fields::kHero, properties.hero);
    }
    else if constexpr (T == ObjectPropertiesType::LeanTo)
    {
      out.writeField(Fields::kIndex, properties.index);
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kQuantity, properties.quantity);
      out.writeField(Fields::kResourceType, properties.resource_type);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Pyramid)
    {
      out.writeField(Fields::kSpell, properties.spell);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kIsLootable, static_cast<bool>(properties.is_lootable));
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::RefugeeCamp)
    {
      out.writeField(Fields::kQuantity, properties.quantity);
    }
    else if constexpr (T == ObjectPropertiesType::SeersHut)
    {
      out.writeField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::ShipwreckSurvivor)
    {
      out.writeField(Fields::kArtifact, properties.artifact);
    }
    else if constexpr (T == ObjectPropertiesType::Shrine)
    {
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kSpell, properties.spell);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Sign)
    {
      out.writeField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::TreeOfKnowledge)
    {
      out.writeField(Fields::kIndex, properties.index);
      out.writeField(Fields::kType, properties.type);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::University)
    {
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
      out.writeField(Fields::kIndex, properties.index);
      out.writeField(Fields::kReserved3, properties.reserved3);
    }
    else if constexpr (T == ObjectPropertiesType::WarriorsTomb)
    {
      out.writeField(Fields::kHasArtifact, properties.has_artifact);
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kArtifact, properties.artifact);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WaterWheel)
    {
      out.writeField(Fields::kBonus, properties.bonus);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::Windmill)
    {
      out.writeField(Fields::kResourceType, properties.resource_type);
      out.writeField(Fields::kResourceQuantity, properties.resource_quantity);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WitchHut)
    {
      out.writeField(Fields::kReserved1, properties.reserved1);
      out.writeField(Fields::kReserved2, properties.reserved2);
      out.writeField(Fields::kSkill, properties.skill);
      out.writeField(Fields::kVisitedBy, properties.visited_by);
    }
    else
    {
      static_assert(false, "Not implemented.");
    }
  }

  template<>
  void JsonObjectWriter<h3svg::ObjectPropertiesVariant>::operator()(
    FieldsWriter& out, const h3svg::ObjectPropertiesVariant& properties) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesVariant>;
    out.writeField(Fields::kObjectClass, properties.objectClass());
    properties.visit([&out] <h3svg::ObjectPropertiesType T> (const h3svg::ObjectProperties<T>& details)
                     {
                       out.writeField(Fields::kDetails, details);
                     });
  }
}
