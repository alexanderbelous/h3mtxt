#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/ObjectProperties.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>

using ::h3svg::ObjectPropertiesType;

namespace h3json
{
  template<ObjectPropertiesType T>
  h3svg::ObjectProperties<T> JsonReader<h3svg::ObjectProperties<T>>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectProperties<T>>;

    h3svg::ObjectProperties<T> properties;
    if constexpr (T == ObjectPropertiesType::None)
    {
      readField(properties.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::BlackMarket)
    {
      readField(properties.index, value, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::Campfire)
    {
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(value, Fields::kResourceType);
      properties.quantity = readBitField<std::uint8_t, 4>(value, Fields::kQuantity);
      readField(properties.reserved, value, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::CreatureBank)
    {
      properties.reserved1 = readBitField<std::int8_t, 5>(value, Fields::kReserved1);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.index = readBitField<std::uint16_t, 12>(value, Fields::kIndex);
      properties.is_cleared = readField<bool>(value, Fields::kIsCleared);
      properties.reserved2 = readBitField<std::int8_t, 6>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Dwelling)
    {
      readField(properties.index, value, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::Corpse)
    {
      properties.id = readBitField<std::uint16_t, 5>(value, Fields::kId);
      properties.reserved1 = readBitField<std::uint16_t, 1>(value, Fields::kReserved1);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(value, Fields::kArtifact);
      properties.is_lootable = readBitField<std::uint16_t, 1>(value, Fields::kIsLootable);
      properties.reserved2 = readBitField<std::int16_t, 15>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Event)
    {
      properties.id = readBitField<std::uint16_t, 10>(value, Fields::kId);
      readField(properties.affected_players, value, Fields::kAffectedPlayers);
      properties.applies_to_computer = readField<bool>(value, Fields::kAppliesToComputer);
      properties.cancel_after_first_visit = readField<bool>(value, Fields::kCancelAfterFirstVisit);
      properties.reserved = readBitField<std::uint16_t, 12>(value, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::Floatsam)
    {
      readField(properties.content, value, Fields::kContent);
    }
    else if constexpr (T == ObjectPropertiesType::FountainOfFortune)
    {
      properties.reserved1 = readBitField<std::int32_t, 5>(value, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int32_t, 8>(value, Fields::kReserved2);
      properties.luck_bonus = readBitField<std::int32_t, 4>(value, Fields::kLuckBonus);
      properties.reserved3 = readBitField<std::int32_t, 15>(value, Fields::kReserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Garrison)
    {
      readField(properties.index, value, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::Hero)
    {
      readField(properties.hero, value, Fields::kHero);
    }
    else if constexpr (T == ObjectPropertiesType::LeanTo)
    {
      properties.index = readBitField<std::uint8_t, 5>(value, Fields::kIndex);
      properties.reserved1 = readBitField<std::uint8_t, 1>(value, Fields::kReserved1);
      properties.quantity = readBitField<std::uint8_t, 4>(value, Fields::kQuantity);
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(value, Fields::kResourceType);
      properties.reserved2 = readBitField<std::int32_t, 18>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Pyramid)
    {
      readField(properties.spell, value, Fields::kSpell);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.is_lootable = readField<bool>(value, Fields::kIsLootable);
      properties.reserved1 = readBitField<std::int16_t, 4>(value, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 11>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::RefugeeCamp)
    {
      readField(properties.quantity, value, Fields::kQuantity);
    }
    else if constexpr (T == ObjectPropertiesType::SeersHut)
    {
      readField(properties.index, value, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::ShipwreckSurvivor)
    {
      readField(properties.artifact, value, Fields::kArtifact);
    }
    else if constexpr (T == ObjectPropertiesType::Shrine)
    {
      properties.reserved1 = readBitField<std::int16_t, 5>(value, Fields::kReserved1);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.spell = readBitField<std::int16_t, 10>(value, Fields::kSpell);
      properties.reserved2 = readBitField<std::int16_t, 9>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Sign)
    {
      readField(properties.index, value, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::TreeOfKnowledge)
    {
      properties.index = readBitField<std::uint8_t, 5>(value, Fields::kIndex);
      properties.type = readBitField<h3svg::TreeOfKnowledgeType, 2>(value, Fields::kType);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.reserved1 = readBitField<std::uint8_t, 1>(value, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 16>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::University)
    {
      properties.reserved1 = readBitField<std::int32_t, 5>(value, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int32_t, 8>(value, Fields::kReserved2);
      properties.index = readBitField<std::int32_t, 12>(value, Fields::kIndex);
      properties.reserved3 = readBitField<std::int32_t, 7>(value, Fields::kReserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Wagon)
    {
      properties.is_lootable = readField<bool>(value, Fields::kIsLootable);
      properties.has_artifact = readField<bool>(value, Fields::kHasArtifact);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(value, Fields::kArtifact);
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(value, Fields::kResourceType);
      properties.resource_quantity = readBitField<std::uint16_t, 5>(value, Fields::kResourceQuantity);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.reserved = readBitField<std::int8_t, 3>(value, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::WarriorsTomb)
    {
      properties.has_artifact = readBitField<std::uint8_t, 1>(value, Fields::kHasArtifact);
      properties.reserved1 = readBitField<std::int8_t, 4>(value, Fields::kReserved1);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(value, Fields::kArtifact);
      properties.reserved2 = readBitField<std::int16_t, 9>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WaterWheel)
    {
      properties.bonus = readBitField<std::uint8_t, 5>(value, Fields::kBonus);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.reserved = readBitField<std::int32_t, 19>(value, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::Windmill)
    {
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(value, Fields::kResourceType);
      properties.resource_quantity = readBitField<std::uint8_t, 4>(value, Fields::kResourceQuantity);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.reserved1 = readBitField<std::uint16_t, 1>(value, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 15>(value, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WitchHut)
    {
      properties.reserved1 = readBitField<std::uint16_t, 5>(value, Fields::kReserved1);
      readField(properties.visited_by, value, Fields::kVisitedBy);
      properties.skill = readBitField<h3svg::SecondarySkillType, 8>(value, Fields::kSkill);
      properties.reserved2 = readBitField<std::uint16_t, 11>(value, Fields::kReserved2);
    }
    else
    {
      static_assert(false, "Not implemented.");
    }
    return properties;
  }

  namespace
  {
    template<h3svg::ObjectPropertiesType T>
    h3svg::ObjectPropertiesVariant readObjectPropertiesAsVariant(const Json::Value& value, h3svg::ObjectClass object_class)
    {
      return h3svg::ObjectPropertiesVariant{ object_class, fromJson<h3svg::ObjectProperties<T>>(value) };
    }

    template<h3svg::ObjectPropertiesType T>
    using readObjectPropertiesAsVariantAlias = SwitchStatement_NS::StaticConstant<&readObjectPropertiesAsVariant<T>>;
  }

  template<>
  h3svg::ObjectPropertiesVariant
  JsonReader<h3svg::ObjectPropertiesVariant>::operator()(const Json::Value& value) const
  {
    static constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<h3svg::ObjectPropertiesType,
                                                  h3svg::kNumObjectPropertiesTypes,
                                                  readObjectPropertiesAsVariantAlias>();

    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesVariant>;
    const h3svg::ObjectClass object_class = readField<h3svg::ObjectClass>(value, Fields::kObjectClass);
    return switch_statement(h3svg::getObjectPropertiesType(object_class),
                            getJsonField(value, Fields::kDetails),
                            object_class);
  }
}
