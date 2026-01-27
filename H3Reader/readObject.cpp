#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/readSecondarySkillsVector.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <stdexcept>

namespace h3m::H3Reader_NS
{
  namespace
  {
    std::array<CreatureStack, 7> readCreatureStackArray(std::istream& stream)
    {
      std::array<CreatureStack, 7> creatures;
      for (CreatureStack& creature_stack : creatures)
      {
        creature_stack = readCreatureStack(stream);
      }
      return creatures;
    }

    Guardians readGuardians(std::istream& stream)
    {
      Guardians guardians;
      guardians.message = readString(stream);
      const Bool has_creatures = readBool(stream);
      if (has_creatures)
      {
        guardians.creatures = readCreatureStackArray(stream);
      }
      guardians.unknown = readReservedData<4>(stream);
      return guardians;
    }

    void readEventBase(std::istream& stream, EventBase& event)
    {
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        event.guardians = readGuardians(stream);
      }
      else
      {
        event.guardians = std::nullopt;
      }
      event.experience = readInt<std::int32_t>(stream);
      event.spell_points = readInt<std::int32_t>(stream);
      event.morale = readInt<std::int8_t>(stream);
      event.luck = readInt<std::int8_t>(stream);
      event.resources = readResources(stream);
      event.primary_skills = readPrimarySkills(stream);
      event.secondary_skills = readSecondarySkillsVector<std::uint8_t>(stream);
      const std::uint8_t num_artifacts = readInt<std::uint8_t>(stream);
      event.artifacts.clear();
      event.artifacts.reserve(num_artifacts);
      for (std::uint8_t i = 0; i < num_artifacts; ++i)
      {
        event.artifacts.push_back(readEnum<ArtifactType>(stream));
      }
      const std::uint8_t num_spells = readInt<std::uint8_t>(stream);
      event.spells.clear();
      event.spells.reserve(num_spells);
      for (std::uint8_t i = 0; i < num_spells; ++i)
      {
        event.spells.push_back(readEnum<SpellType>(stream));
      }
      const std::uint8_t num_creatures = readInt<std::uint8_t>(stream);
      event.creatures.clear();
      event.creatures.reserve(num_creatures);
      for (std::uint8_t i = 0; i < num_creatures; ++i)
      {
        event.creatures.push_back(readCreatureStack(stream));
      }
      event.unknown = readReservedData<8>(stream);
    }

    // Reads ObjectProperties<T> from the stream.
    // This function needs to be specialized for each valid ObjectPropertiesType. The default implementation
    // cannot be instantiated - it causes a compilation error, reporting a missing specialization.
    template<ObjectPropertiesType T>
    ObjectProperties<T> readObjectProperties(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readObjectProperties<T>().");
      return {};
    }

    template<>
    ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>
    readObjectProperties<ObjectPropertiesType::ABANDONED_MINE>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::ABANDONED_MINE> data;
      data.potential_resources = readEnumBitmask<ResourceType, 1>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::ARTIFACT>
    readObjectProperties<ObjectPropertiesType::ARTIFACT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::ARTIFACT> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::EVENT>
    readObjectProperties<ObjectPropertiesType::EVENT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::EVENT> data;
      readEventBase(stream, data);
      data.affected_players = readEnumBitmask<PlayerColor, 1>(stream);
      data.applies_to_computer = readBool(stream);
      data.remove_after_first_visit = readBool(stream);
      data.unknown2 = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::GARRISON>
    readObjectProperties<ObjectPropertiesType::GARRISON>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::GARRISON> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.unknown = readReservedData<3>(stream);
      data.creatures = readCreatureStackArray(stream);
      data.can_remove_units = readBool(stream);
      data.unknown2 = readReservedData<8>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>
    readObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>(std::istream&)
    {
      return {};
    }

    template<>
    ObjectProperties<ObjectPropertiesType::GRAIL>
    readObjectProperties<ObjectPropertiesType::GRAIL>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::GRAIL> data;
      data.allowable_radius = readInt<std::uint8_t>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::HERO>
    readObjectProperties<ObjectPropertiesType::HERO>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::HERO> data;
      data.absod_id = readInt<std::uint32_t>(stream);
      data.owner = readEnum<PlayerColor>(stream);
      data.type = readEnum<HeroType>(stream);
      const Bool has_name = readBool(stream);
      if (has_name)
      {
        data.name = readString(stream);
      }
      const Bool has_experience = readBool(stream);
      if (has_experience)
      {
        data.experience = readInt<std::int32_t>(stream);
      }
      const Bool has_portrait = readBool(stream);
      if (has_portrait)
      {
        data.portrait = readEnum<HeroPortrait>(stream);
      }
      const Bool has_secondary_skills = readBool(stream);
      if (has_secondary_skills)
      {
        data.secondary_skills = readSecondarySkillsVector<std::uint32_t>(stream);
      }
      const Bool has_creatures = readBool(stream);
      if (has_creatures)
      {
        data.creatures = readCreatureStackArray(stream);
      }
      data.formation = readEnum<Formation>(stream);
      const Bool has_artifacts = readBool(stream);
      if (has_artifacts)
      {
        data.artifacts = readHeroArtifacts(stream);
      }
      data.patrol_radius = readInt<std::int8_t>(stream);
      const Bool has_biography = readBool(stream);
      if (has_biography)
      {
        data.biography = readString(stream);
      }
      data.gender = readEnum<Gender>(stream);
      const Bool has_spells = readBool(stream);
      if (has_spells)
      {
        data.spells = readEnumBitmask<SpellType, 9>(stream);
      }
      const Bool has_primary_skills = readBool(stream);
      if (has_primary_skills)
      {
        data.primary_skills = readPrimarySkills(stream);
      }
      data.unknown = readReservedData<16>(stream);
      return data;
    }

    MessageAndTreasure readMessageAndTreasure(std::istream& stream)
    {
      MessageAndTreasure data;
      data.message = readString(stream);
      data.resources = readResources(stream);
      data.artifact = readEnum<ArtifactType>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::MONSTER>
    readObjectProperties<ObjectPropertiesType::MONSTER>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::MONSTER> monster;
      monster.absod_id = readInt<std::uint32_t>(stream);
      monster.count = readInt<std::uint16_t>(stream);
      monster.disposition = readEnum<Disposition>(stream);
      const Bool has_message_and_treasure = readBool(stream);
      if (has_message_and_treasure)
      {
        monster.message_and_treasure = readMessageAndTreasure(stream);
      }
      monster.never_flees = readBool(stream);
      monster.does_not_grow = readBool(stream);
      monster.unknown = readReservedData<2>(stream);
      return monster;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>
    readObjectProperties<ObjectPropertiesType::PANDORAS_BOX>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> data;
      readEventBase(stream, data);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>
    readObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>(std::istream& stream)
    {
      constexpr HeroType kRandomHeroType {0xFF};

      ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.type = readEnum<HeroType>(stream);
      if (data.type == kRandomHeroType)
      {
        data.power_rating = readInt<std::uint8_t>(stream);
      }
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::QUEST_GUARD>
    readObjectProperties<ObjectPropertiesType::QUEST_GUARD>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::QUEST_GUARD> quest_guard;
      quest_guard.quest = readQuest(stream);
      return quest_guard;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>
    readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.town_absod_id = readInt<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readEnumBitmask<TownType, 2>(stream);
      }
      dwelling.min_level = readInt<std::uint8_t>(stream);
      dwelling.max_level = readInt<std::uint8_t>(stream);
      return dwelling;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
    readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.min_level = readInt<std::uint8_t>(stream);
      dwelling.max_level = readInt<std::uint8_t>(stream);
      return dwelling;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
    readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.town_absod_id = readInt<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readEnumBitmask<TownType, 2>(stream);
      }
      return dwelling;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::RESOURCE>
    readObjectProperties<ObjectPropertiesType::RESOURCE>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::RESOURCE> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      data.quantity = readInt<std::uint32_t>(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::SCHOLAR>
    readObjectProperties<ObjectPropertiesType::SCHOLAR>(std::istream& stream)
    {
       ObjectProperties<ObjectPropertiesType::SCHOLAR> data;
       const ScholarRewardType reward_type = readEnum<ScholarRewardType>(stream);
       switch (reward_type)
       {
       case ScholarRewardType::PrimarySkill:
         data.reward = readEnum<PrimarySkillType>(stream);
         break;
       case ScholarRewardType::SecondarySkill:
         data.reward = readEnum<SecondarySkillType>(stream);
         break;
       case ScholarRewardType::Spell:
         data.reward = readEnum<SpellType>(stream);
         break;
       case ScholarRewardType::Random:
         data.reward = readEnum<ScholarRandomRewardType>(stream);
         break;
       default:
         throw std::runtime_error("Invalid ScholarRewardType.");
       }
       data.unknown = readReservedData<6>(stream);
       return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::SEERS_HUT>
    readObjectProperties<ObjectPropertiesType::SEERS_HUT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::SEERS_HUT> data;
      data.quest = readQuest(stream);
      data.reward = readReward(stream);
      data.unknown = readReservedData<2>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::SHRINE>
    readObjectProperties<ObjectPropertiesType::SHRINE>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::SHRINE> data;
      data.spell = readEnum<SpellType>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::SIGN>
    readObjectProperties<ObjectPropertiesType::SIGN>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::SIGN> data;
      data.message = readString(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>
    readObjectProperties<ObjectPropertiesType::SPELL_SCROLL>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::SPELL_SCROLL> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      data.spell = readEnum<SpellType>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    TownEvent readTownEvent(std::istream& stream)
    {
      TownEvent event { readTimedEvent(stream) };
      event.buildings = readEnumBitmask<TownBuildingType, 6>(stream);
      for (std::uint16_t& creature_growth : event.creatures)
      {
        creature_growth = readInt<std::uint16_t>(stream);
      }
      event.unknown2 = readReservedData<4>(stream);
      return event;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::TOWN>
    readObjectProperties<ObjectPropertiesType::TOWN>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::TOWN> town;
      town.absod_id = readInt<std::uint32_t>(stream);
      town.owner = readEnum<PlayerColor>(stream);
      const Bool has_name = readBool(stream);
      if (has_name)
      {
        town.name = readString(stream);
      }
      const Bool has_garrison = readBool(stream);
      if (has_garrison)
      {
        town.garrison = readCreatureStackArray(stream);
      }
      town.formation = readEnum<Formation>(stream);
      const Bool has_buildings = readBool(stream);
      if (has_buildings)
      {
        town.buildings.emplace();
        town.buildings->is_built = readEnumBitmask<TownBuildingType, 6>(stream);
        town.buildings->is_disabled = readEnumBitmask<TownBuildingType, 6>(stream);
      }
      else
      {
        town.has_fort = readBool(stream);
      }
      town.must_have_spell = readEnumBitmask<SpellType, 9>(stream);
      town.may_not_have_spell = readEnumBitmask<SpellType, 9>(stream);
      const std::uint32_t num_events = readInt<std::uint32_t>(stream);
      town.events.reserve(num_events);
      for (std::uint32_t i = 0; i < num_events; ++i)
      {
        town.events.push_back(readTownEvent(stream));
      }
      town.alignment = readInt<std::uint8_t>(stream);
      town.unknown = readReservedData<3>(stream);
      return town;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
    readObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<ObjectPropertiesType::WITCH_HUT>
    readObjectProperties<ObjectPropertiesType::WITCH_HUT>(std::istream& stream)
    {
      ObjectProperties<ObjectPropertiesType::WITCH_HUT> data;
      data.potential_skills = readEnumBitmask<SecondarySkillType, 4>(stream);
      return data;
    }

    // Utility wrapper around readObjectProperties(), which returns the result as ObjectPropertiesVariant.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(std::istream& stream)
    {
      return readObjectProperties<T>(stream);
    }

    // Reads ObjectProperties for the specified ObjectPropertiesType.
    // \param stream - input stream.
    // \param object_properties_type - ObjectPropertiesType of the object.
    // \return the deserialized data as ObjectPropertiesVariant.
    ObjectPropertiesVariant readObjectPropertiesVariant(std::istream& stream,
                                                        ObjectPropertiesType object_properties_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns ObjectPropertiesVariant.
      using ReadObjectPropertiesPtr = ObjectPropertiesVariant(*)(std::istream& stream);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectPropertiesAsVariant() ordered by ObjectPropertiesType.
      constexpr std::array<ReadObjectPropertiesPtr, kNumObjectPropertiesTypes> kObjectPropertiesReaders =
        [] <ObjectPropertiesType... object_properties_types>
        (EnumSequence<ObjectPropertiesType, object_properties_types...> seq)
        consteval
        {
          return std::array<ReadObjectPropertiesPtr, sizeof...(object_properties_types)>
          { &readObjectPropertiesAsVariant<object_properties_types>... };
        }(MakeEnumSequence<ObjectPropertiesType, kNumObjectPropertiesTypes>{});
      // Invoke a function from the generated array.
      return kObjectPropertiesReaders.at(static_cast<std::size_t>(object_properties_type))(stream);
    }
  }

  Object readObject(std::istream& stream, const ObjectTemplate* objects_templates, std::size_t num_objects_templates)
  {
    Object result;
    result.x = readInt<std::uint8_t>(stream);
    result.y = readInt<std::uint8_t>(stream);
    result.z = readInt<std::uint8_t>(stream);
    result.template_idx = readInt<std::uint32_t>(stream);
    result.unknown = readReservedData<5>(stream);

    if (result.template_idx >= num_objects_templates)
    {
      throw std::runtime_error("readObject(): invalid template_idx.");
    }
    const ObjectTemplate& object_template = objects_templates[result.template_idx];
    const ObjectPropertiesType object_properties_type =
      getObjectPropertiesType(object_template.object_class, object_template.object_subclass);
    result.properties = readObjectPropertiesVariant(stream, object_properties_type);
    return result;
  }
}
