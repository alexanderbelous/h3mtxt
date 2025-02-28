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
      event.experience = readInt<std::uint32_t>(stream);
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

    // Reads ObjectDetails<T> from the stream.
    // This function needs to be specialized for each valid MetaObjectType. The default implementation
    // cannot be instantiated - it causes a compilation error, reporting a missing specialization.
    template<MetaObjectType T>
    ObjectDetails<T> readObjectDetails(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readObjectDetails<T>().");
      return {};
    }

    template<>
    ObjectDetails<MetaObjectType::ABANDONED_MINE>
    readObjectDetails<MetaObjectType::ABANDONED_MINE>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::ABANDONED_MINE> data;
      data.potential_resources = readEnumBitmask<ResourceType, 1>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::ARTIFACT>
    readObjectDetails<MetaObjectType::ARTIFACT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::ARTIFACT> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::EVENT>
    readObjectDetails<MetaObjectType::EVENT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::EVENT> data;
      readEventBase(stream, data);
      data.affected_players = readEnumBitmask<PlayerColor, 1>(stream);
      data.applies_to_computer = readBool(stream);
      data.remove_after_first_visit = readBool(stream);
      data.unknown2 = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::GARRISON>
    readObjectDetails<MetaObjectType::GARRISON>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::GARRISON> data;
      data.owner = readInt<std::uint32_t>(stream);
      data.creatures = readCreatureStackArray(stream);
      data.can_remove_units = readBool(stream);
      data.unknown = readReservedData<8>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::GENERIC_NO_PROPERTIES>
    readObjectDetails<MetaObjectType::GENERIC_NO_PROPERTIES>(std::istream&)
    {
      return {};
    }

    template<>
    ObjectDetails<MetaObjectType::GRAIL>
    readObjectDetails<MetaObjectType::GRAIL>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::GRAIL> data;
      data.allowable_radius = readInt<std::uint32_t>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::HERO>
    readObjectDetails<MetaObjectType::HERO>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::HERO> data;
      data.absod_id = readInt<std::uint32_t>(stream);
      data.owner = readInt<std::uint8_t>(stream);
      data.type = readEnum<HeroType>(stream);
      const Bool has_name = readBool(stream);
      if (has_name)
      {
        data.name = readString(stream);
      }
      const Bool has_experience = readBool(stream);
      if (has_experience)
      {
        data.experience = readInt<std::uint32_t>(stream);
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
    ObjectDetails<MetaObjectType::MONSTER>
    readObjectDetails<MetaObjectType::MONSTER>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::MONSTER> monster;
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
    ObjectDetails<MetaObjectType::PANDORAS_BOX>
    readObjectDetails<MetaObjectType::PANDORAS_BOX>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::PANDORAS_BOX> data;
      readEventBase(stream, data);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::PLACEHOLDER_HERO>
    readObjectDetails<MetaObjectType::PLACEHOLDER_HERO>(std::istream& stream)
    {
      constexpr HeroType kRandomHeroType {0xFF};

      ObjectDetails<MetaObjectType::PLACEHOLDER_HERO> data;
      data.owner = readEnum<PlayerColor>(stream);
      data.type = readEnum<HeroType>(stream);
      if (data.type == kRandomHeroType)
      {
        data.power_rating = readInt<std::uint8_t>(stream);
      }
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::QUEST_GUARD>
    readObjectDetails<MetaObjectType::QUEST_GUARD>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::QUEST_GUARD> quest_guard;
      quest_guard.quest = readQuest(stream);
      return quest_guard;
    }

    template<>
    ObjectDetails<MetaObjectType::RANDOM_DWELLING>
    readObjectDetails<MetaObjectType::RANDOM_DWELLING>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::RANDOM_DWELLING> dwelling;
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
    ObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>
    readObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.min_level = readInt<std::uint8_t>(stream);
      dwelling.max_level = readInt<std::uint8_t>(stream);
      return dwelling;
    }

    template<>
    ObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>
    readObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL> dwelling;
      dwelling.owner = readInt<std::uint32_t>(stream);
      dwelling.town_absod_id = readInt<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readEnumBitmask<TownType, 2>(stream);
      }
      return dwelling;
    }

    template<>
    ObjectDetails<MetaObjectType::RESOURCE>
    readObjectDetails<MetaObjectType::RESOURCE>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::RESOURCE> data;
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
    ObjectDetails<MetaObjectType::SCHOLAR>
    readObjectDetails<MetaObjectType::SCHOLAR>(std::istream& stream)
    {
       ObjectDetails<MetaObjectType::SCHOLAR> data;
       data.reward_type = readEnum<ScholarRewardType>(stream);
       data.reward_value = readInt<std::uint8_t>(stream);
       data.unknown = readReservedData<6>(stream);
       return data;
    }

    template<>
    ObjectDetails<MetaObjectType::SEERS_HUT>
    readObjectDetails<MetaObjectType::SEERS_HUT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::SEERS_HUT> data;
      data.quest = readQuest(stream);
      data.reward = readReward(stream);
      data.unknown = readReservedData<2>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::SHRINE>
    readObjectDetails<MetaObjectType::SHRINE>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::SHRINE> data;
      data.spell = readEnum<SpellType>(stream);
      data.unknown = readReservedData<3>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::SIGN>
    readObjectDetails<MetaObjectType::SIGN>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::SIGN> data;
      data.message = readString(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::SPELL_SCROLL>
    readObjectDetails<MetaObjectType::SPELL_SCROLL>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::SPELL_SCROLL> data;
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
    ObjectDetails<MetaObjectType::TOWN>
    readObjectDetails<MetaObjectType::TOWN>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::TOWN> town;
      town.absod_id = readInt<std::uint32_t>(stream);
      town.owner = readInt<std::uint8_t>(stream);
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
    ObjectDetails<MetaObjectType::TRIVIAL_OWNED_OBJECT>
    readObjectDetails<MetaObjectType::TRIVIAL_OWNED_OBJECT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::TRIVIAL_OWNED_OBJECT> data;
      data.owner = readInt<std::uint32_t>(stream);
      return data;
    }

    template<>
    ObjectDetails<MetaObjectType::WITCH_HUT>
    readObjectDetails<MetaObjectType::WITCH_HUT>(std::istream& stream)
    {
      ObjectDetails<MetaObjectType::WITCH_HUT> data;
      data.potential_skills = readEnumBitmask<SecondarySkillType, 4>(stream);
      return data;
    }

    // Utility wrapper around readObjectDetails(), which returns the result
    // as ObjectDetailsVariant.
    template<MetaObjectType T>
    ObjectDetailsVariant readObjectDetailsAsVariant(std::istream& stream)
    {
      return readObjectDetails<T>(stream);
    }

    // Reads ObjectDetails for the specified MetaObjectType.
    // \param stream - input stream.
    // \param meta_object_type - MetaObjectType of the object.
    // \return the deserialized data as ObjectDetailsVariant.
    ObjectDetailsVariant readObjectDetailsVariant(std::istream& stream, MetaObjectType meta_object_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns ObjectDetailsVariant.
      using ReadObjectDetailsDataPtr = ObjectDetailsVariant(*)(std::istream& stream);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectDetailsDataAsVariant() ordered by MetaObjectType.
      constexpr std::array<ReadObjectDetailsDataPtr, kNumMetaObjectTypes> kObjectDetailsDataReaders =
        [] <MetaObjectType... meta_object_types>
        (EnumSequence<MetaObjectType, meta_object_types...> seq)
        consteval
        {
          return std::array<ReadObjectDetailsDataPtr, sizeof...(meta_object_types)>
          { &readObjectDetailsAsVariant<meta_object_types>... };
        }(MakeEnumSequence<MetaObjectType, kNumMetaObjectTypes>{});
      // Invoke a function from the generated array.
      return kObjectDetailsDataReaders.at(static_cast<std::size_t>(meta_object_type))(stream);
    }
  }

  Object readObject(std::istream& stream, const ObjectTemplate* objects_templates, std::size_t num_objects_templates)
  {
    Object result;
    result.x = readInt<std::uint8_t>(stream);
    result.y = readInt<std::uint8_t>(stream);
    result.z = readInt<std::uint8_t>(stream);
    result.kind = readInt<std::uint32_t>(stream);
    result.unknown = readReservedData<5>(stream);

    if (result.kind >= num_objects_templates)
    {
      throw std::runtime_error("readObject(): invalid object kind.");
    }
    const ObjectTemplate& object_template = objects_templates[result.kind];
    const MetaObjectType meta_object_type = getMetaObjectType(object_template.object_class);
    result.details = readObjectDetailsVariant(stream, meta_object_type);
    return result;
  }
}
