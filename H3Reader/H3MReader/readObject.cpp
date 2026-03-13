#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    std::array<CreatureStack, 7> readCreatureStackArray(const H3MReader& reader)
    {
      std::array<CreatureStack, 7> creatures;
      for (CreatureStack& creature_stack : creatures)
      {
        creature_stack = reader.readCreatureStack();
      }
      return creatures;
    }

    std::vector<SecondarySkill> readSecondarySkillsVector(const H3MReader& reader, std::size_t num_secondary_skills)
    {
      std::vector<SecondarySkill> secondary_skills;
      secondary_skills.reserve(num_secondary_skills);
      for (std::uintmax_t i = 0; i < num_secondary_skills; ++i)
      {
        secondary_skills.push_back(reader.readSecondarySkill());
      }
      return secondary_skills;
    }

    // Utility wrapper around H3MReader::readObjectProperties(), which returns the result as ObjectPropertiesVariant.
    template<ObjectPropertiesType T>
    ObjectPropertiesVariant readObjectPropertiesAsVariant(const H3MReader& reader)
    {
      return reader.readObjectProperties<T>();
    }

    // Reads ObjectProperties for the specified ObjectPropertiesType.
    // \param reader - input stream.
    // \param object_properties_type - ObjectPropertiesType of the object.
    // \return the deserialized data as ObjectPropertiesVariant.
    ObjectPropertiesVariant readObjectPropertiesVariant(const H3MReader& reader,
                                                        ObjectPropertiesType object_properties_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns ObjectPropertiesVariant.
      using ReadObjectPropertiesPtr = ObjectPropertiesVariant(*)(const H3MReader& reader);
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
      return kObjectPropertiesReaders.at(static_cast<std::size_t>(object_properties_type))(reader);
    }
  }

  void H3MReader::readEventBase(EventBase& event) const
  {
    const Bool has_guardians = readBool();
    if (has_guardians)
    {
      event.guardians = readGuardians();
    }
    else
    {
      event.guardians = std::nullopt;
    }
    event.experience = readInt<std::int32_t>();
    event.spell_points = readInt<std::int32_t>();
    event.morale = readInt<std::int8_t>();
    event.luck = readInt<std::int8_t>();
    event.resources = readResources();
    event.primary_skills = readPrimarySkills();
    const std::uint8_t num_secondary_skills = readInt<std::uint8_t>();
    event.secondary_skills = readSecondarySkillsVector(*this, num_secondary_skills);
    const std::uint8_t num_artifacts = readInt<std::uint8_t>();
    event.artifacts.clear();
    event.artifacts.reserve(num_artifacts);
    for (std::uint8_t i = 0; i < num_artifacts; ++i)
    {
      event.artifacts.push_back(readEnum<ArtifactType>());
    }
    const std::uint8_t num_spells = readInt<std::uint8_t>();
    event.spells.clear();
    event.spells.reserve(num_spells);
    for (std::uint8_t i = 0; i < num_spells; ++i)
    {
      event.spells.push_back(readEnum<SpellType>());
    }
    const std::uint8_t num_creatures = readInt<std::uint8_t>();
    event.creatures.clear();
    event.creatures.reserve(num_creatures);
    for (std::uint8_t i = 0; i < num_creatures; ++i)
    {
      event.creatures.push_back(readCreatureStack());
    }
    event.unknown = readReservedData<8>();
  }

  Guardians H3MReader::readGuardians() const
  {
    Guardians guardians;
    guardians.message = readString32();
    const Bool has_creatures = readBool();
    if (has_creatures)
    {
      guardians.creatures = readCreatureStackArray(*this);
    }
    guardians.unknown = readReservedData<4>();
    return guardians;
  }

  MessageAndTreasure H3MReader::readMessageAndTreasure() const
  {
    MessageAndTreasure data;
    data.message = readString32();
    data.resources = readResources();
    data.artifact = readEnum<ArtifactType>();
    return data;
  }

  TownEvent H3MReader::readTownEvent() const
  {
    TownEvent event{ readTimedEvent() };
    event.buildings = readEnumBitmask<TownBuildingType, 6>();
    for (std::uint16_t& creature_growth : event.creatures)
    {
      creature_growth = readInt<std::uint16_t>();
    }
    event.unknown2 = readReservedData<4>();
    return event;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>
  H3MReader::readObjectProperties<ObjectPropertiesType::ABANDONED_MINE>() const
  {
    ObjectProperties<ObjectPropertiesType::ABANDONED_MINE> data;
    data.potential_resources = readEnumBitmask<ResourceType, 1>();
    data.unknown = readReservedData<3>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::ARTIFACT>
  H3MReader::readObjectProperties<ObjectPropertiesType::ARTIFACT>() const
  {
    ObjectProperties<ObjectPropertiesType::ARTIFACT> data;
    const Bool has_guardians = readBool();
    if (has_guardians)
    {
      data.guardians = readGuardians();
    }
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::EVENT>
  H3MReader::readObjectProperties<ObjectPropertiesType::EVENT>() const
  {
    ObjectProperties<ObjectPropertiesType::EVENT> data;
    readEventBase(data);
    data.affected_players = readEnumBitmask<PlayerColor, 1>();
    data.applies_to_computer = readBool();
    data.remove_after_first_visit = readBool();
    data.unknown2 = readReservedData<4>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GARRISON>
  H3MReader::readObjectProperties<ObjectPropertiesType::GARRISON>() const
  {
    ObjectProperties<ObjectPropertiesType::GARRISON> data;
    data.owner = readEnum<PlayerColor>();
    data.unknown = readReservedData<3>();
    data.creatures = readCreatureStackArray(*this);
    data.can_remove_units = readBool();
    data.unknown2 = readReservedData<8>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>
  H3MReader::readObjectProperties<ObjectPropertiesType::GENERIC_NO_PROPERTIES>() const
  {
    return {};
  }

  template<>
  ObjectProperties<ObjectPropertiesType::GRAIL>
  H3MReader::readObjectProperties<ObjectPropertiesType::GRAIL>() const
  {
    ObjectProperties<ObjectPropertiesType::GRAIL> data;
    data.allowable_radius = readInt<std::uint8_t>();
    data.unknown = readReservedData<3>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::HERO>
  H3MReader::readObjectProperties<ObjectPropertiesType::HERO>() const
  {
    ObjectProperties<ObjectPropertiesType::HERO> data;
    data.absod_id = readInt<std::uint32_t>();
    data.owner = readEnum<PlayerColor>();
    data.type = readEnum<HeroType>();
    const Bool has_name = readBool();
    if (has_name)
    {
      data.name = readString32();
    }
    const Bool has_experience = readBool();
    if (has_experience)
    {
      data.experience = readInt<std::int32_t>();
    }
    const Bool has_portrait = readBool();
    if (has_portrait)
    {
      data.portrait = readEnum<HeroPortrait>();
    }
    const Bool has_secondary_skills = readBool();
    if (has_secondary_skills)
    {
      const std::uint32_t num_secondary_skills = readInt<std::uint32_t>();
      data.secondary_skills = readSecondarySkillsVector(*this, num_secondary_skills);
    }
    const Bool has_creatures = readBool();
    if (has_creatures)
    {
      data.creatures = readCreatureStackArray(*this);
    }
    data.formation = readEnum<Formation>();
    const Bool has_artifacts = readBool();
    if (has_artifacts)
    {
      data.artifacts = readHeroArtifacts();
    }
    data.patrol_radius = readInt<std::int8_t>();
    const Bool has_biography = readBool();
    if (has_biography)
    {
      data.biography = readString32();
    }
    data.gender = readEnum<Gender>();
    const Bool has_spells = readBool();
    if (has_spells)
    {
      data.spells = readEnumBitmask<SpellType, 9>();
    }
    const Bool has_primary_skills = readBool();
    if (has_primary_skills)
    {
      data.primary_skills = readPrimarySkills();
    }
    data.unknown = readReservedData<16>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::MONSTER>
  H3MReader::readObjectProperties<ObjectPropertiesType::MONSTER>() const
  {
    ObjectProperties<ObjectPropertiesType::MONSTER> monster;
    monster.absod_id = readInt<std::uint32_t>();
    monster.count = readInt<std::uint16_t>();
    monster.disposition = readEnum<Disposition>();
    const Bool has_message_and_treasure = readBool();
    if (has_message_and_treasure)
    {
      monster.message_and_treasure = readMessageAndTreasure();
    }
    monster.never_flees = readBool();
    monster.does_not_grow = readBool();
    monster.unknown = readReservedData<2>();
    return monster;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>
  H3MReader::readObjectProperties<ObjectPropertiesType::PANDORAS_BOX>() const
  {
    ObjectProperties<ObjectPropertiesType::PANDORAS_BOX> data;
    readEventBase(data);
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>
  H3MReader::readObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>() const
  {
    constexpr HeroType kRandomHeroType {0xFF};

    ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO> data;
    data.owner = readEnum<PlayerColor>();
    data.type = readEnum<HeroType>();
    if (data.type == kRandomHeroType)
    {
      data.power_rating = readInt<std::uint8_t>();
    }
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::QUEST_GUARD>
  H3MReader::readObjectProperties<ObjectPropertiesType::QUEST_GUARD>() const
  {
    ObjectProperties<ObjectPropertiesType::QUEST_GUARD> quest_guard;
    quest_guard.quest = readQuest();
    return quest_guard;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>
  H3MReader::readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>() const
  {
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING> dwelling;
    dwelling.owner = readInt<std::uint32_t>();
    dwelling.town_absod_id = readInt<std::uint32_t>();
    if (dwelling.town_absod_id == 0)
    {
      dwelling.alignment = readEnumBitmask<TownType, 2>();
    }
    dwelling.min_level = readInt<std::uint8_t>();
    dwelling.max_level = readInt<std::uint8_t>();
    return dwelling;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>
  H3MReader::readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>() const
  {
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT> dwelling;
    dwelling.owner = readInt<std::uint32_t>();
    dwelling.min_level = readInt<std::uint8_t>();
    dwelling.max_level = readInt<std::uint8_t>();
    return dwelling;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>
  H3MReader::readObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>() const
  {
    ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL> dwelling;
    dwelling.owner = readInt<std::uint32_t>();
    dwelling.town_absod_id = readInt<std::uint32_t>();
    if (dwelling.town_absod_id == 0)
    {
      dwelling.alignment = readEnumBitmask<TownType, 2>();
    }
    return dwelling;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::RESOURCE>
  H3MReader::readObjectProperties<ObjectPropertiesType::RESOURCE>() const
  {
    ObjectProperties<ObjectPropertiesType::RESOURCE> data;
    const Bool has_guardians = readBool();
    if (has_guardians)
    {
      data.guardians = readGuardians();
    }
    data.quantity = readInt<std::uint32_t>();
    data.unknown = readReservedData<4>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SCHOLAR>
  H3MReader::readObjectProperties<ObjectPropertiesType::SCHOLAR>() const
  {
      ObjectProperties<ObjectPropertiesType::SCHOLAR> data;
      const ScholarRewardType reward_type = readEnum<ScholarRewardType>();
      switch (reward_type)
      {
      case ScholarRewardType::PrimarySkill:
        data.reward = readEnum<PrimarySkillType>();
        break;
      case ScholarRewardType::SecondarySkill:
        data.reward = readEnum<SecondarySkillType>();
        break;
      case ScholarRewardType::Spell:
        data.reward = readEnum<SpellType>();
        break;
      case ScholarRewardType::Random:
        data.reward = readEnum<ScholarRandomRewardType>();
        break;
      default:
        throw std::runtime_error("Invalid ScholarRewardType.");
      }
      data.unknown = readReservedData<6>();
      return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SEERS_HUT>
  H3MReader::readObjectProperties<ObjectPropertiesType::SEERS_HUT>() const
  {
    ObjectProperties<ObjectPropertiesType::SEERS_HUT> data;
    data.quest = readQuest();
    data.reward = readReward();
    data.unknown = readReservedData<2>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SHRINE>
  H3MReader::readObjectProperties<ObjectPropertiesType::SHRINE>() const
  {
    ObjectProperties<ObjectPropertiesType::SHRINE> data;
    data.spell = readEnum<SpellType>();
    data.unknown = readReservedData<3>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SIGN>
  H3MReader::readObjectProperties<ObjectPropertiesType::SIGN>() const
  {
    ObjectProperties<ObjectPropertiesType::SIGN> data;
    data.message = readString32();
    data.unknown = readReservedData<4>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>
  H3MReader::readObjectProperties<ObjectPropertiesType::SPELL_SCROLL>() const
  {
    ObjectProperties<ObjectPropertiesType::SPELL_SCROLL> data;
    const Bool has_guardians = readBool();
    if (has_guardians)
    {
      data.guardians = readGuardians();
    }
    data.spell = readEnum<SpellType>();
    data.unknown = readReservedData<3>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TOWN>
  H3MReader::readObjectProperties<ObjectPropertiesType::TOWN>() const
  {
    ObjectProperties<ObjectPropertiesType::TOWN> town;
    town.absod_id = readInt<std::uint32_t>();
    town.owner = readEnum<PlayerColor>();
    const Bool has_name = readBool();
    if (has_name)
    {
      town.name = readString32();
    }
    const Bool has_garrison = readBool();
    if (has_garrison)
    {
      town.garrison = readCreatureStackArray(*this);
    }
    town.formation = readEnum<Formation>();
    const Bool has_buildings = readBool();
    if (has_buildings)
    {
      town.buildings.emplace();
      town.buildings->is_built = readEnumBitmask<TownBuildingType, 6>();
      town.buildings->is_disabled = readEnumBitmask<TownBuildingType, 6>();
    }
    else
    {
      town.has_fort = readBool();
    }
    town.must_have_spell = readEnumBitmask<SpellType, 9>();
    town.may_not_have_spell = readEnumBitmask<SpellType, 9>();
    const std::uint32_t num_events = readInt<std::uint32_t>();
    town.events.reserve(num_events);
    for (std::uint32_t i = 0; i < num_events; ++i)
    {
      town.events.push_back(readTownEvent());
    }
    town.alignment = readInt<std::uint8_t>();
    town.unknown = readReservedData<3>();
    return town;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>
  H3MReader::readObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>() const
  {
    ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT> data;
    data.owner = readEnum<PlayerColor>();
    data.unknown = readReservedData<3>();
    return data;
  }

  template<>
  ObjectProperties<ObjectPropertiesType::WITCH_HUT>
  H3MReader::readObjectProperties<ObjectPropertiesType::WITCH_HUT>() const
  {
    ObjectProperties<ObjectPropertiesType::WITCH_HUT> data;
    data.potential_skills = readEnumBitmask<SecondarySkillType, 4>();
    return data;
  }

  Object H3MReader::readObject(const ObjectTemplate* objects_templates, std::size_t num_objects_templates) const
  {
    Object result;
    result.coordinates = readCoordinates();
    result.template_idx = readInt<std::uint32_t>();
    result.unknown = readReservedData<5>();

    if (result.template_idx >= num_objects_templates)
    {
      throw std::runtime_error("readObject(): invalid template_idx.");
    }
    const ObjectTemplate& object_template = objects_templates[result.template_idx];
    const ObjectPropertiesType object_properties_type =
      getObjectPropertiesType(object_template.object_class, object_template.object_subclass);
    result.properties = readObjectPropertiesVariant(*this, object_properties_type);
    return result;
  }
}
