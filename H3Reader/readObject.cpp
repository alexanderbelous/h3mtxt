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
    // This function needs to be specialized for each valid MetaObjectType. The default implementation
    // cannot be instantiated - it causes a compilation error, reporting a missing specialization.
    template<MetaObjectType T>
    ObjectProperties<T> readObjectProperties(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readObjectProperties<T>().");
      return {};
    }

    template<>
    ObjectProperties<MetaObjectType::ABANDONED_MINE>
    readObjectProperties<MetaObjectType::ABANDONED_MINE>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::ABANDONED_MINE> data;
      data.potential_resources = readEnumBitmask<ResourceType, 1>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::ARTIFACT>
    readObjectProperties<MetaObjectType::ARTIFACT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::ARTIFACT> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::EVENT>
    readObjectProperties<MetaObjectType::EVENT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::EVENT> data;
      readEventBase(stream, data);
      data.affected_players = readEnumBitmask<PlayerColor, 1>(stream);
      data.applies_to_computer = readBool(stream);
      data.remove_after_first_visit = readBool(stream);
      data.unknown2 = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::GARRISON>
    readObjectProperties<MetaObjectType::GARRISON>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::GARRISON> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.unknown = readReservedData<3>(stream);
      data.creatures = readCreatureStackArray(stream);
      data.can_remove_units = readBool(stream);
      data.unknown2 = readReservedData<8>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>
    readObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>(std::istream&)
    {
      return {};
    }

    template<>
    ObjectProperties<MetaObjectType::GRAIL>
    readObjectProperties<MetaObjectType::GRAIL>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::GRAIL> data;
      data.allowable_radius = readInt<std::uint8_t>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::HERO>
    readObjectProperties<MetaObjectType::HERO>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::HERO> data;
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
      data.patrol_radius = readInt<std::uint8_t>(stream);
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
    ObjectProperties<MetaObjectType::MONSTER>
    readObjectProperties<MetaObjectType::MONSTER>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::MONSTER> monster;
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
    ObjectProperties<MetaObjectType::PANDORAS_BOX>
    readObjectProperties<MetaObjectType::PANDORAS_BOX>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::PANDORAS_BOX> data;
      readEventBase(stream, data);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>
    readObjectProperties<MetaObjectType::PLACEHOLDER_HERO>(std::istream& stream)
    {
      constexpr HeroType kRandomHeroType {0xFF};

      ObjectProperties<MetaObjectType::PLACEHOLDER_HERO> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.type = readEnum<HeroType>(stream);
      if (data.type == kRandomHeroType)
      {
        data.power_rating = readInt<std::uint8_t>(stream);
      }
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::QUEST_GUARD>
    readObjectProperties<MetaObjectType::QUEST_GUARD>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::QUEST_GUARD> quest_guard;
      quest_guard.quest = readQuest(stream);
      return quest_guard;
    }

    template<>
    ObjectProperties<MetaObjectType::RANDOM_DWELLING>
    readObjectProperties<MetaObjectType::RANDOM_DWELLING>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::RANDOM_DWELLING> dwelling;
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
    ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>
    readObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.min_level = readInt<std::uint8_t>(stream);
      dwelling.max_level = readInt<std::uint8_t>(stream);
      return dwelling;
    }

    template<>
    ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>
    readObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.town_absod_id = readInt<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readEnumBitmask<TownType, 2>(stream);
      }
      return dwelling;
    }

    template<>
    ObjectProperties<MetaObjectType::RESOURCE>
    readObjectProperties<MetaObjectType::RESOURCE>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::RESOURCE> data;
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
    ObjectProperties<MetaObjectType::SCHOLAR>
    readObjectProperties<MetaObjectType::SCHOLAR>(std::istream& stream)
    {
       ObjectProperties<MetaObjectType::SCHOLAR> data;
       data.reward_type = readEnum<ScholarRewardType>(stream);
       data.reward_value = readInt<std::uint8_t>(stream);
       data.unknown = readReservedData<6>(stream);
       return data;
    }

    template<>
    ObjectProperties<MetaObjectType::SEERS_HUT>
    readObjectProperties<MetaObjectType::SEERS_HUT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::SEERS_HUT> data;
      data.quest = readQuest(stream);
      data.reward = readReward(stream);
      data.unknown = readReservedData<2>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::SHRINE>
    readObjectProperties<MetaObjectType::SHRINE>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::SHRINE> data;
      data.spell = readEnum<SpellType>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::SIGN>
    readObjectProperties<MetaObjectType::SIGN>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::SIGN> data;
      data.message = readString(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::SPELL_SCROLL>
    readObjectProperties<MetaObjectType::SPELL_SCROLL>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::SPELL_SCROLL> data;
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
      TownEvent event;
      readTimedEventBase(stream, event);
      event.buildings = readEnumBitmask<TownBuildingType, 6>(stream);
      for (std::uint16_t& creature_growth : event.creatures)
      {
        creature_growth = readInt<std::uint16_t>(stream);
      }
      event.unknown2 = readReservedData<4>(stream);
      return event;
    }

    template<>
    ObjectProperties<MetaObjectType::TOWN>
    readObjectProperties<MetaObjectType::TOWN>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::TOWN> town;
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
    ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>
    readObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectProperties<MetaObjectType::WITCH_HUT>
    readObjectProperties<MetaObjectType::WITCH_HUT>(std::istream& stream)
    {
      ObjectProperties<MetaObjectType::WITCH_HUT> data;
      data.potential_skills = readEnumBitmask<SecondarySkillType, 4>(stream);
      return data;
    }

    // Utility wrapper around readObjectProperties(), which returns the result as ObjectPropertiesVariant.
    template<MetaObjectType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(std::istream& stream)
    {
      return readObjectProperties<T>(stream);
    }

    // Reads ObjectProperties for the specified MetaObjectType.
    // \param stream - input stream.
    // \param meta_object_type - MetaObjectType of the object.
    // \return the deserialized data as ObjectPropertiesVariant.
    ObjectPropertiesVariant readObjectPropertiesVariant(std::istream& stream, MetaObjectType meta_object_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns ObjectPropertiesVariant.
      using ReadObjectPropertiesPtr = ObjectPropertiesVariant(*)(std::istream& stream);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectPropertiesAsVariant() ordered by MetaObjectType.
      constexpr std::array<ReadObjectPropertiesPtr, kNumMetaObjectTypes> kObjectPropertiesReaders =
        [] <MetaObjectType... meta_object_types>
        (EnumSequence<MetaObjectType, meta_object_types...> seq)
        consteval
        {
          return std::array<ReadObjectPropertiesPtr, sizeof...(meta_object_types)>
          { &readObjectPropertiesAsVariant<meta_object_types>... };
        }(MakeEnumSequence<MetaObjectType, kNumMetaObjectTypes>{});
      // Invoke a function from the generated array.
      return kObjectPropertiesReaders.at(static_cast<std::size_t>(meta_object_type))(stream);
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
    const MetaObjectType meta_object_type = getMetaObjectType(object_template.object_class,
                                                              object_template.object_subclass);
    result.properties = readObjectPropertiesVariant(stream, meta_object_type);
    return result;
  }
}
