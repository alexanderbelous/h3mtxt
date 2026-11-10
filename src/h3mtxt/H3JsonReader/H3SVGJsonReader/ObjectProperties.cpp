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
  h3svg::ObjectProperties<T> JsonReader2<h3svg::ObjectProperties<T>>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectProperties<T>>;

    const Json::Value& root = value();

    h3svg::ObjectProperties<T> properties;
    if constexpr (T == ObjectPropertiesType::None)
    {
      readField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::Artifact)
    {
      properties.type = readBitField<std::uint16_t, 4>(root, Fields::kType);
      properties.has_setup = readField<bool>(Fields::kHasSetup);
      properties.index = readBitField<std::uint16_t, 12>(root, Fields::kIndex);
      properties.reserved = readBitField<std::uint16_t, 15>(root, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::BlackMarket)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Campfire)
    {
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(root, Fields::kResourceType);
      properties.quantity = readBitField<std::uint8_t, 4>(root, Fields::kQuantity);
      readField(Fields::kReserved, properties.reserved);
    }
    else if constexpr (T == ObjectPropertiesType::CreatureBank)
    {
      properties.reserved1 = readBitField<std::int8_t, 5>(root, Fields::kReserved1);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.index = readBitField<std::uint16_t, 12>(root, Fields::kIndex);
      properties.is_cleared = readField<bool>(Fields::kIsCleared);
      properties.reserved2 = readBitField<std::int8_t, 6>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Dwelling)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Corpse)
    {
      properties.id = readBitField<std::uint16_t, 5>(root, Fields::kId);
      properties.reserved1 = readBitField<std::uint16_t, 1>(root, Fields::kReserved1);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(root, Fields::kArtifact);
      properties.is_lootable = readBitField<std::uint16_t, 1>(root, Fields::kIsLootable);
      properties.reserved2 = readBitField<std::int16_t, 15>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Event)
    {
      properties.id = readBitField<std::uint16_t, 10>(root, Fields::kId);
      readField(Fields::kAffectedPlayers, properties.affected_players);
      properties.applies_to_computer = readField<bool>(Fields::kAppliesToComputer);
      properties.cancel_after_first_visit = readField<bool>(Fields::kCancelAfterFirstVisit);
      properties.reserved = readBitField<std::uint16_t, 12>(root, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::Floatsam)
    {
      readField(Fields::kContent, properties.content);
    }
    else if constexpr (T == ObjectPropertiesType::FountainOfFortune)
    {
      properties.reserved1 = readBitField<std::int32_t, 5>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int32_t, 8>(root, Fields::kReserved2);
      properties.luck_bonus = readBitField<std::int32_t, 4>(root, Fields::kLuckBonus);
      properties.reserved3 = readBitField<std::int32_t, 15>(root, Fields::kReserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Garrison)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Hero)
    {
      readField(Fields::kHero, properties.hero);
    }
    else if constexpr (T == ObjectPropertiesType::LeanTo)
    {
      properties.index = readBitField<std::uint8_t, 5>(root, Fields::kIndex);
      properties.reserved1 = readBitField<std::uint8_t, 1>(root, Fields::kReserved1);
      properties.quantity = readBitField<std::uint8_t, 4>(root, Fields::kQuantity);
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(root, Fields::kResourceType);
      properties.reserved2 = readBitField<std::int32_t, 18>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::MagicSpring)
    {
      properties.index = readBitField<std::uint32_t, 5>(root, Fields::kIndex);
      properties.reserved1 = readBitField<std::uint32_t, 1>(root, Fields::kReserved1);
      properties.has_bonus = readField<bool>(Fields::kHasBonus);
      properties.reserved2 = readBitField<std::int32_t, 25>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Monster)
    {
      properties.quantity = readBitField<std::uint16_t, 12>(root, Fields::kQuantity);
      properties.growth_remainder = readBitField<std::uint16_t, 4>(root, Fields::kGrowthRemainder);
      properties.aggression = readBitField<std::int8_t, 5>(root, Fields::kAggression);
      properties.never_flees = readField<bool>(Fields::kNeverFlees);
      properties.does_not_grow = readField<bool>(Fields::kDoesNotGrow);
      properties.has_message_or_treasure = readField<bool>(Fields::kHasMessageOrTreasure);
      properties.index = readBitField<std::uint8_t, 8>(root, Fields::kIndex);
    }
    else if constexpr (T == ObjectPropertiesType::MysticalGarden)
    {
      properties.index = readBitField<std::uint8_t, 5>(root, Fields::kIndex);
      properties.reserved1 = readBitField<std::uint8_t, 1>(root, Fields::kReserved1);
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(root, Fields::kResourceType);
      properties.is_lootable = readBitField<std::uint8_t, 1>(root, Fields::kIsLootable);
      properties.reserved2 = readBitField<std::int32_t, 21>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Obelisk)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::Pyramid)
    {
      readField(Fields::kSpell, properties.spell);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.is_lootable = readField<bool>(Fields::kIsLootable);
      properties.reserved1 = readBitField<std::int16_t, 4>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 11>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::RefugeeCamp)
    {
      readField(Fields::kQuantity, properties.quantity);
    }
    else if constexpr (T == ObjectPropertiesType::Scholar)
    {
      properties.type = readBitField<h3svg::ScholarRewardType, 3>(root, Fields::kType);
      properties.primary_skill = readBitField<h3svg::PrimarySkillType, 3>(root, Fields::kPrimarySkill);
      properties.secondary_skill = readBitField<h3svg::SecondarySkillType, 7>(root, Fields::kSecondarySkill);
      properties.spell = readBitField<h3svg::SpellType16, 10>(root, Fields::kSpell);
      properties.reserved = readBitField<std::int16_t, 9>(root, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::SeaChest)
    {
      properties.content = readBitField<h3svg::SeaChestContentType, 2>(root, Fields::kContent);
      properties.artifact = readBitField<h3svg::ArtifactType32, 10>(root, Fields::kArtifact);
      properties.reserved1 = readBitField<std::uint32_t, 1>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int32_t, 19>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::SeersHut)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::ShipwreckSurvivor)
    {
      readField(Fields::kArtifact, properties.artifact);
    }
    else if constexpr (T == ObjectPropertiesType::Shrine)
    {
      properties.reserved1 = readBitField<std::int16_t, 5>(root, Fields::kReserved1);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.spell = readBitField<h3svg::SpellType16, 10>(root, Fields::kSpell);
      properties.reserved2 = readBitField<std::int16_t, 9>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::Sign)
    {
      readField(Fields::kIndex, properties.index);
    }
    else if constexpr (T == ObjectPropertiesType::SpellScroll)
    {
      properties.spell = readField<h3svg::SpellType>(Fields::kSpell);
      properties.has_setup = readField<bool>(Fields::kHasSetup);
      properties.index = readBitField<std::uint16_t, 12>(root, Fields::kIndex);
      properties.reserved = readBitField<std::uint16_t, 11>(root, Fields::kReserved);
      }
    else if constexpr (T == ObjectPropertiesType::TreeOfKnowledge)
    {
      properties.index = readBitField<std::uint8_t, 5>(root, Fields::kIndex);
      properties.type = readBitField<h3svg::TreeOfKnowledgeType, 2>(root, Fields::kType);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.reserved1 = readBitField<std::uint8_t, 1>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 16>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::University)
    {
      properties.reserved1 = readBitField<std::int32_t, 5>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int32_t, 8>(root, Fields::kReserved2);
      properties.index = readBitField<std::int32_t, 12>(root, Fields::kIndex);
      properties.reserved3 = readBitField<std::int32_t, 7>(root, Fields::kReserved3);
    }
    else if constexpr (T == ObjectPropertiesType::Wagon)
    {
      properties.is_lootable = readField<bool>(Fields::kIsLootable);
      properties.has_artifact = readField<bool>(Fields::kHasArtifact);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(root, Fields::kArtifact);
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(root, Fields::kResourceType);
      properties.resource_quantity = readBitField<std::uint16_t, 5>(root, Fields::kResourceQuantity);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.reserved = readBitField<std::int8_t, 3>(root, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::WarriorsTomb)
    {
      properties.has_artifact = readBitField<std::uint8_t, 1>(root, Fields::kHasArtifact);
      properties.reserved1 = readBitField<std::int8_t, 4>(root, Fields::kReserved1);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.artifact = readBitField<h3svg::ArtifactType, 10>(root, Fields::kArtifact);
      properties.reserved2 = readBitField<std::int16_t, 9>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WaterWheel)
    {
      properties.bonus = readBitField<std::uint8_t, 5>(root, Fields::kBonus);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.reserved = readBitField<std::int32_t, 19>(root, Fields::kReserved);
    }
    else if constexpr (T == ObjectPropertiesType::Windmill)
    {
      properties.resource_type = readBitField<h3svg::ResourceType, 4>(root, Fields::kResourceType);
      properties.resource_quantity = readBitField<std::uint8_t, 4>(root, Fields::kResourceQuantity);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.reserved1 = readBitField<std::uint16_t, 1>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::int16_t, 15>(root, Fields::kReserved2);
    }
    else if constexpr (T == ObjectPropertiesType::WitchHut)
    {
      properties.skill = readBitField<h3svg::SecondarySkillType, 7>(root, Fields::kSkill);
      readField(Fields::kVisitedBy, properties.visited_by);
      properties.reserved1 = readBitField<std::uint16_t, 5>(root, Fields::kReserved1);
      properties.reserved2 = readBitField<std::uint16_t, 12>(root, Fields::kReserved2);
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
  h3svg::ObjectPropertiesVariant JsonReader2<h3svg::ObjectPropertiesVariant>::operator()() const
  {
    static constexpr auto switch_statement =
      SwitchStatement_NS::generateSwitchStatement<h3svg::ObjectPropertiesType,
                                                  h3svg::kNumObjectPropertiesTypes,
                                                  readObjectPropertiesAsVariantAlias>();

    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesVariant>;
    const h3svg::ObjectClass object_class = readField<h3svg::ObjectClass>(Fields::kObjectClass);
    return switch_statement(h3svg::getObjectPropertiesType(object_class),
                            getField(Fields::kDetails),
                            object_class);
  }
}
