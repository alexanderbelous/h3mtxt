#include <h3mtxt/H3MWriter/writeh3m.h>

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/H3MWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MWriter/writeMapAdditionalInfo.h>
#include <h3mtxt/H3MWriter/writeMapBasicInfo.h>
#include <h3mtxt/H3MWriter/writeObjectAttributes.h>
#include <h3mtxt/H3MWriter/writePlayerSpecs.h>
#include <h3mtxt/H3MWriter/writePrimarySkills.h>
#include <h3mtxt/H3MWriter/writeSecondarySkill.h>
#include <h3mtxt/H3MWriter/writeTile.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3m
{
  template<class T>
  struct H3MWriter<Resources<T>>
  {
    void operator()(std::ostream& stream, const Resources<T>& resources) const
    {
      writeData(stream, resources.data);
    }
  };

  template<>
  struct H3MWriter<AffectedPlayers>
  {
    void operator()(std::ostream& stream, const AffectedPlayers& affected_players) const
    {
      writeData(stream, affected_players.bitset);
    }
  };

  template<>
  struct H3MWriter<CreatureStack>
  {
    void operator()(std::ostream& stream, const CreatureStack& value) const
    {
      writeData(stream, value.type);
      writeData(stream, value.count);
    }
  };

  template<>
  struct H3MWriter<Guardians>
  {
    void operator()(std::ostream& stream, const Guardians& guardians) const
    {
      writeData(stream, guardians.message);
      writeData(stream, guardians.creatures);
      writeData(stream, guardians.unknown);
    }
  };

  void writeEventBase(std::ostream& stream, const EventBase& event)
  {
    writeData(stream, event.guardians);
    writeData(stream, event.experience);
    writeData(stream, event.spell_points);
    writeData(stream, event.morale);
    writeData(stream, event.luck);
    writeData(stream, event.resources);
    writeData(stream, event.primary_skills);
    writeVector<std::uint8_t>(stream, event.secondary_skills);
    writeVector<std::uint8_t>(stream, event.artifacts);
    writeVector<std::uint8_t>(stream, event.spells);
    writeVector<std::uint8_t>(stream, event.creatures);
    writeData(stream, event.unknown);
  }

  void writeTimedEventBase(std::ostream& stream, const TimedEventBase& event)
  {
    writeData(stream, event.name);
    writeData(stream, event.message);
    writeData(stream, event.resources);
    writeData(stream, event.affected_players);
    writeData(stream, event.applies_to_human);
    writeData(stream, event.applies_to_computer);
    writeData(stream, event.day_of_first_occurence);
    writeData(stream, event.repeat_after_days);
    writeData(stream, event.unknown);
  }

  template<>
  struct H3MWriter<TownBuildings>
  {
    void operator()(std::ostream& stream, const TownBuildings& town_buildings) const
    {
      writeData(stream, town_buildings.is_built);
      writeData(stream, town_buildings.is_disabled);
    }
  };

  template<>
  struct H3MWriter<TownEvent>
  {
    void operator()(std::ostream& stream, const TownEvent& event) const
    {
      writeTimedEventBase(stream, event);
      writeData(stream, event.buildings);
      writeData(stream, event.creatures);
      writeData(stream, event.unknown);
    }
  };

  // TODO: remove once specialized for each MetaObjectType.
  template<MetaObjectType T>
  struct H3MWriter<ObjectDetailsData<T>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<T>& data) const
    {
      throw std::logic_error("NotImplemented.");
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::ABANDONED_MINE>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::ABANDONED_MINE>& data) const
    {
      writeData(stream, data.potential_resources);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::ARTIFACT>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::ARTIFACT>& data) const
    {
      writeData(stream, data.guardians);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::EVENT>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::EVENT>& event) const
    {
      writeEventBase(stream, event);
      writeData(stream, event.affected_players);
      writeData(stream, event.applies_to_computer);
      writeData(stream, event.remove_after_first_visit);
      writeData(stream, event.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::GARRISON>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GARRISON>& garrison) const
    {
      writeData(stream, garrison.owner);
      writeData(stream, garrison.creatures);
      writeData(stream, garrison.can_remove_units);
      writeData(stream, garrison.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GENERIC_NO_PROPERTIES>& data) const
    {
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::GRAIL>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::GRAIL>& grail) const
    {
      writeData(stream, grail.allowable_radius);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::HERO>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::HERO>& hero) const
    {
      writeData(stream, hero.absod_id);
      writeData(stream, hero.owner);
      writeData(stream, hero.type);
      writeData(stream, hero.name);
      writeData(stream, hero.experience);
      writeData(stream, hero.face);
      writeData(stream, static_cast<Bool>(hero.secondary_skills.has_value()));
      if (hero.secondary_skills)
      {
        writeVector<std::uint32_t>(stream, *hero.secondary_skills);
      }
      writeData(stream, hero.creatures);
      writeData(stream, hero.formation);
      writeData(stream, hero.artifacts);
      writeData(stream, hero.patrol_radius);
      writeData(stream, hero.biography);
      writeData(stream, hero.gender);
      writeData(stream, hero.spells);
      writeData(stream, hero.primary_skills);
      writeData(stream, hero.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::MONSTER>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::MONSTER>& monster) const
    {
      writeData(stream, monster.absod_id);
      writeData(stream, monster.count);
      writeData(stream, monster.disposition);
      writeData(stream, static_cast<Bool>(monster.message_and_treasure.has_value()));
      if (monster.message_and_treasure)
      {
        writeData(stream, monster.message_and_treasure->message);
        writeData(stream, monster.message_and_treasure->resources);
        writeData(stream, monster.message_and_treasure->artifact);
      }
      writeData(stream, monster.never_flees);
      writeData(stream, monster.does_not_grow);
      writeData(stream, monster.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::PANDORAS_BOX>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::PANDORAS_BOX>& pandoras_box) const
    {
      writeEventBase(stream, pandoras_box);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::PLACEHOLDER_HERO>& hero) const
    {
      constexpr HeroType kRandomHeroType {0xFF};

      writeData(stream, hero.owner);
      writeData(stream, hero.type);
      if (hero.type == kRandomHeroType)
      {
        writeData(stream, hero.power_rating);
      }
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::RANDOM_DWELLING>& dwelling) const
    {
      writeData(stream, dwelling.owner);
      writeData(stream, dwelling.town_absod_id);
      if (dwelling.town_absod_id == 0)
      {
        writeData(stream, dwelling.alignment);
      }
      writeData(stream, dwelling.min_level);
      writeData(stream, dwelling.max_level);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    void operator()(std::ostream& stream,
                    const ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
    {
      writeData(stream, dwelling.owner);
      writeData(stream, dwelling.min_level);
      writeData(stream, dwelling.max_level);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    void operator()(std::ostream& stream,
                    const ObjectDetailsData<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
    {
      writeData(stream, dwelling.owner);
      writeData(stream, dwelling.town_absod_id);
      if (dwelling.town_absod_id == 0)
      {
        writeData(stream, dwelling.alignment);
      }
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::RESOURCE>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::RESOURCE>& data) const
    {
      writeData(stream, data.guardians);
      writeData(stream, data.quantity);
      writeData(stream, data.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::SCHOLAR>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SCHOLAR>& scholar) const
    {
      writeData(stream, scholar.reward_type);
      writeData(stream, scholar.reward_value);
      writeData(stream, scholar.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::SHRINE>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SHRINE>& shrine) const
    {
      writeData(stream, shrine.spell);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::SIGN>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SIGN>& sign) const
    {
      writeData(stream, sign.message);
      writeData(stream, sign.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::SPELL_SCROLL>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::SPELL_SCROLL>& spell_scroll) const
    {
      writeData(stream, spell_scroll.guardians);
      writeData(stream, spell_scroll.spell);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::TOWN>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::TOWN>& town) const
    {
      writeData(stream, town.absod_id);
      writeData(stream, town.owner);
      writeData(stream, town.name);
      writeData(stream, town.creatures);
      writeData(stream, town.formation);
      writeData(stream, town.buildings);
      if (!town.buildings)
      {
        writeData(stream, town.has_fort);
      }
      writeData(stream, town.must_have_spell);
      writeData(stream, town.may_not_have_spell);
      writeVector<std::uint32_t>(stream, town.events);
      writeData(stream, town.alignment);
      writeData(stream, town.unknown);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::TRIVIAL_OWNED_OBJECT>& data) const
    {
      writeData(stream, data.owner);
    }
  };

  template<>
  struct H3MWriter<ObjectDetailsData<MetaObjectType::WITCH_HUT>>
  {
    void operator()(std::ostream& stream, const ObjectDetailsData<MetaObjectType::WITCH_HUT>& witch_hut) const
    {
      writeData(stream, witch_hut.skills_availability);
    }
  };

  template<>
  struct H3MWriter<ObjectDetails>
  {
    void operator()(std::ostream& stream, const ObjectDetails& object_details) const
    {
      writeData(stream, object_details.x);
      writeData(stream, object_details.y);
      writeData(stream, object_details.z);
      writeData(stream, object_details.kind);
      writeData(stream, object_details.unknown);
      // TODO: Check that MetaObjectType in object_details.details matches the one in ObjectAttributes.
      object_details.details.visit(
        [&stream](auto&& value)
        {
          writeData(stream, std::forward<decltype(value)>(value));
        });
    }
  };

  template<>
  struct H3MWriter<GlobalEvent>
  {
    void operator()(std::ostream& stream, const GlobalEvent& global_event) const
    {
      writeTimedEventBase(stream, global_event);
    }
  };

  template<>
  struct H3MWriter<Map>
  {
    void operator()(std::ostream& stream, const Map& map) const
    {
      writeData(stream, map.format);
      writeData(stream, map.basic_info);
      writeData(stream, map.players);
      writeData(stream, map.additional_info);
      // Write tiles.
      if (map.tiles.size() != countTiles(map.basic_info))
      {
        throw std::runtime_error("Wrong number of elements in Map.tiles.");
      }
      for (const Tile& tile : map.tiles)
      {
        writeData(stream, tile);
      }
      writeVector<std::uint32_t>(stream, map.objects_attributes);
      writeVector<std::uint32_t>(stream, map.objects_details);
      writeVector<std::uint32_t>(stream, map.global_events);
      writeData(stream, map.padding);
    }
  };

  void writeh3m(std::ostream& stream, const Map& map)
  {
    writeData(stream, map);
  }
}
