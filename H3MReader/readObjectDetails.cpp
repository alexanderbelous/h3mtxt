#include <h3mtxt/H3MReader/readObjectDetails.h>

#include <h3mtxt/H3MReader/readHeroArtifacts.h>
#include <h3mtxt/H3MReader/readPrimarySkills.h>
#include <h3mtxt/H3MReader/readResources.h>
#include <h3mtxt/H3MReader/readSecondarySkillsVector.h>
#include <h3mtxt/H3MReader/Utils.h>
#include <h3mtxt/Map/ObjectAttributes.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    CreatureStack readCreatureStack(std::istream& stream)
    {
      CreatureStack creature_stack;
      creature_stack.type = readEnum<CreatureType>(stream);
      creature_stack.count = readUint<std::uint16_t>(stream);
      return creature_stack;
    }

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
      event.experience = readUint<std::uint32_t>(stream);
      event.spell_points = readUint<std::int32_t>(stream);
      event.morale = readUint<std::int8_t>(stream);
      event.luck = readUint<std::int8_t>(stream);
      event.resources = readResources<std::int32_t>(stream);
      event.primary_skills = readPrimarySkills(stream);
      event.secondary_skills = readSecondarySkillsVector<std::uint8_t>(stream);
      const std::uint8_t num_artifacts = readUint8(stream);
      event.artifacts.clear();
      event.artifacts.reserve(num_artifacts);
      for (std::uint8_t i = 0; i < num_artifacts; ++i)
      {
        event.artifacts.push_back(readEnum<ArtifactType>(stream));
      }
      const std::uint8_t num_spells = readUint8(stream);
      event.spells.clear();
      event.spells.reserve(num_spells);
      for (std::uint8_t i = 0; i < num_spells; ++i)
      {
        event.spells.push_back(readEnum<SpellType>(stream));
      }
      const std::uint8_t num_creatures = readUint8(stream);
      event.creatures.clear();
      event.creatures.reserve(num_creatures);
      for (std::uint8_t i = 0; i < num_creatures; ++i)
      {
        event.creatures.push_back(readCreatureStack(stream));
      }
      event.unknown = readReservedData<8>(stream);
    }

    // Reads ObjectDetailsData<T> from the stream.
    // This function needs to be specialized for each valid MetaObjectType. The default implementation
    // cannot be instantiated - it causes a compilation error, reporting a missing specialization.
    template<MetaObjectType T>
    ObjectDetailsData<T> readObjectDetailsData(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readObjectDetailsData<T>().");
      return {};
    }

    template<>
    ObjectDetailsData<MetaObjectType::ABANDONED_MINE>
    readObjectDetailsData<MetaObjectType::ABANDONED_MINE>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::ABANDONED_MINE> data;
      data.potential_resources = readBitSet<4>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::ARTIFACT>
    readObjectDetailsData<MetaObjectType::ARTIFACT>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::ARTIFACT> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::EVENT>
    readObjectDetailsData<MetaObjectType::EVENT>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::EVENT> data;
      readEventBase(stream, data);
      data.affected_players.bitset = readUint8(stream);
      data.applies_to_computer = readBool(stream);
      data.remove_after_first_visit = readBool(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::GARRISON>
    readObjectDetailsData<MetaObjectType::GARRISON>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::GARRISON> data;
      data.owner = readUint<std::uint32_t>(stream);
      data.creatures = readCreatureStackArray(stream);
      data.can_remove_units = readBool(stream);
      data.unknown = readReservedData<8>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>
    readObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>(std::istream& stream)
    {
      return {};
    }

    template<>
    ObjectDetailsData<MetaObjectType::GRAIL>
    readObjectDetailsData<MetaObjectType::GRAIL>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::GRAIL> data;
      data.allowable_radius = readUint<std::uint32_t>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::HERO>
    readObjectDetailsData<MetaObjectType::HERO>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::HERO> data;
      data.absod_id = readUint<std::uint32_t>(stream);
      data.owner = readUint8(stream);
      data.type = readEnum<HeroType>(stream);
      const Bool has_name = readBool(stream);
      if (has_name)
      {
        data.name = readString(stream);
      }
      const Bool has_experience = readBool(stream);
      if (has_experience)
      {
        data.experience = readUint<std::uint32_t>(stream);
      }
      const Bool has_face = readBool(stream);
      if (has_face)
      {
        data.face = readUint8(stream);
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
      data.patrol_radius = readUint8(stream);
      const Bool has_biography = readBool(stream);
      if (has_biography)
      {
        data.biography = readString(stream);
      }
      data.gender = readEnum<Gender>(stream);
      const Bool has_spells = readBool(stream);
      if (has_spells)
      {
        data.spells = readBitSet<9>(stream);
      }
      const Bool has_primary_skills = readBool(stream);
      if (has_primary_skills)
      {
        data.primary_skills = readPrimarySkills(stream);
      }
      data.unknown = readReservedData<16>(stream);
      return data;
    }

    ObjectDetailsData<MetaObjectType::MONSTER>::MessageAndTreasure
    readMessageAndTreasure(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::MONSTER>::MessageAndTreasure data;
      data.message = readString(stream);
      data.resources = readResources<std::uint32_t>(stream);
      data.artifact = readEnum<ArtifactType>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::MONSTER>
    readObjectDetailsData<MetaObjectType::MONSTER>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::MONSTER> monster;
      monster.absod_id = readUint<std::uint32_t>(stream);
      monster.count = readUint<std::uint16_t>(stream);
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
    ObjectDetailsData<MetaObjectType::PANDORAS_BOX>
    readObjectDetailsData<MetaObjectType::PANDORAS_BOX>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::PANDORAS_BOX> data;
      readEventBase(stream, data);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>
    readObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>(std::istream& stream)
    {
      constexpr HeroType kRandomHeroType {0xFF};

      ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO> data;
      data.owner = readUint8(stream);
      data.type = readEnum<HeroType>(stream);
      if (data.type == kRandomHeroType)
      {
        data.power_rating = readUint8(stream);
      }
      return data;
    }

    template<>
     [[noreturn]] ObjectDetailsData<MetaObjectType::QUEST_GUARD>
    readObjectDetailsData<MetaObjectType::QUEST_GUARD>(std::istream& stream)
    {
      throw std::runtime_error("readObjectDetailsData<QUEST_GUARD>(): NotImplemented.");
    }

    template<>
    ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>
    readObjectDetailsData<MetaObjectType::RANDOM_DWELLING>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::RANDOM_DWELLING> dwelling;
      dwelling.owner = readUint<std::uint32_t>(stream);
      dwelling.town_absod_id = readUint<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readBitSet<2>(stream);
      }
      dwelling.min_level = readUint8(stream);
      dwelling.max_level = readUint8(stream);
      return dwelling;
    }

    template<>
    ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>
    readObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT> dwelling;
      dwelling.owner = readUint<std::uint32_t>(stream);
      dwelling.min_level = readUint8(stream);
      dwelling.max_level = readUint8(stream);
      return dwelling;
    }

    template<>
    ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>
    readObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL> dwelling;
      dwelling.owner = readUint<std::uint32_t>(stream);
      dwelling.town_absod_id = readUint<std::uint32_t>(stream);
      if (dwelling.town_absod_id == 0)
      {
        dwelling.alignment = readBitSet<2>(stream);
      }
      return dwelling;
    }

    template<>
    ObjectDetailsData<MetaObjectType::RESOURCE>
    readObjectDetailsData<MetaObjectType::RESOURCE>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::RESOURCE> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      data.quantity = readUint<std::uint32_t>(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
     [[noreturn]] ObjectDetailsData<MetaObjectType::SCHOLAR>
    readObjectDetailsData<MetaObjectType::SCHOLAR>(std::istream& stream)
    {
      throw std::runtime_error("readObjectDetailsData<SCHOLAR>(): NotImplemented.");
    }

    template<>
     [[noreturn]] ObjectDetailsData<MetaObjectType::SEERS_HUT>
    readObjectDetailsData<MetaObjectType::SEERS_HUT>(std::istream& stream)
    {
      throw std::runtime_error("readObjectDetailsData<SEERS_HUT>(): NotImplemented.");
    }

    template<>
    ObjectDetailsData<MetaObjectType::SHRINE>
    readObjectDetailsData<MetaObjectType::SHRINE>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::SHRINE> data;
      data.spell = readUint<std::uint32_t>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::SIGN>
    readObjectDetailsData<MetaObjectType::SIGN>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::SIGN> data;
      data.message = readString(stream);
      data.unknown = readReservedData<4>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::SPELL_SCROLL>
    readObjectDetailsData<MetaObjectType::SPELL_SCROLL>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::SPELL_SCROLL> data;
      const Bool has_guardians = readBool(stream);
      if (has_guardians)
      {
        data.guardians = readGuardians(stream);
      }
      data.spell = readUint<std::uint32_t>(stream);
      return data;
    }

    template<>
     [[noreturn]] ObjectDetailsData<MetaObjectType::TOWN>
    readObjectDetailsData<MetaObjectType::TOWN>(std::istream& stream)
    {
      throw std::runtime_error("readObjectDetailsData<TOWN>(): NotImplemented.");
    }

    template<>
    ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>
    readObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT> data;
      data.owner = readUint<std::uint32_t>(stream);
      return data;
    }

    template<>
    ObjectDetailsData<MetaObjectType::WITCH_HUT>
    readObjectDetailsData<MetaObjectType::WITCH_HUT>(std::istream& stream)
    {
      ObjectDetailsData<MetaObjectType::WITCH_HUT> data;
      data.skills_availability = readBitSet<4>(stream);
      return data;
    }

    // Utility wrapper around readObjectDetailsData(), which returns the result
    // as ObjectDetailsDataVariant.
    template<MetaObjectType T>
    ObjectDetailsDataVariant readObjectDetailsDataAsVariant(std::istream& stream)
    {
      return readObjectDetailsData<T>(stream);
    }

    // Reads ObjectDetailsData for the specified MetaObjectType.
    // \param stream - input stream.
    // \param meta_object_type - MetaObjectType of the object.
    // \return the deserialized data as ObjectDetailsDataVariant.
    ObjectDetailsDataVariant readObjectDetailsDataVariant(std::istream& stream, MetaObjectType meta_object_type)
    {
      // I'm too lazy to write a switch statement - there are too many MetaObjectTypes, so
      // let's use template metaprogramming instead.

      // The underlying integer type for MetaObjectType.
      using MetaObjectTypeIdx = std::underlying_type_t<MetaObjectType>;

      // Type of a pointer to a function that takes std::istream& and returns ObjectDetails::Data.
      using ReadObjectDetailsDataPtr = ObjectDetailsDataVariant(*)(std::istream& stream);

      // Generate (at compile time) an array of function pointers for each instantiation of
      // readObjectDetailsDataAsVariant() ordered by MetaObjectType.
      constexpr
      std::array<ReadObjectDetailsDataPtr, kNumMetaObjectTypes> kObjectDetailsDataReaders =
        [] <MetaObjectTypeIdx... meta_object_type_idx>
        (std::integer_sequence<MetaObjectTypeIdx, meta_object_type_idx...> seq)
        consteval
      {
        return std::array<ReadObjectDetailsDataPtr, sizeof...(meta_object_type_idx)>
        { &readObjectDetailsDataAsVariant<static_cast<MetaObjectType>(meta_object_type_idx)>... };
      }(std::make_integer_sequence<MetaObjectTypeIdx, kNumMetaObjectTypes>{});

      // Invoke a function from the generated array.
      return kObjectDetailsDataReaders.at(static_cast<MetaObjectTypeIdx>(meta_object_type))(stream);
    }
  }

  ObjectDetails readObjectDetails(std::istream& stream,
                                  std::span<const ObjectAttributes> objects_attributes)
  {
    ObjectDetails result;
    result.x = readUint8(stream);
    result.y = readUint8(stream);
    result.z = readUint8(stream);
    result.kind = readUint<std::uint32_t>(stream);
    result.unknown = readReservedData<5>(stream);

    if (result.kind >= objects_attributes.size())
    {
      throw std::runtime_error("readObjectDetails(): invalid object kind.");
    }
    const ObjectAttributes& object_attributes = objects_attributes[result.kind];
    const MetaObjectType meta_object_type = getMetaObjectType(object_attributes.object_class);
    result.details = readObjectDetailsDataVariant(stream, meta_object_type);
    return result;
  }
}
