#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/Object.h>

namespace h3m::H3Writer_NS
{
  namespace
  {
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
  }

  void H3Writer<Guardians>::operator()(std::ostream& stream, const Guardians& guardians) const
  {
    writeData(stream, guardians.message);
    writeData(stream, guardians.creatures);
    writeData(stream, guardians.unknown);
  }

  void H3Writer<TownBuildings>::operator()(std::ostream& stream, const TownBuildings& town_buildings) const
  {
    writeData(stream, town_buildings.is_built);
    writeData(stream, town_buildings.is_disabled);
  }

  void H3Writer<TownEvent>::operator()(std::ostream& stream, const TownEvent& event) const
  {
    writeTimedEventBase(stream, event);
    writeData(stream, event.buildings);
    writeData(stream, event.creatures);
    writeData(stream, event.unknown2);
  }

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::ABANDONED_MINE>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::ABANDONED_MINE>& data) const
    {
      writeData(stream, data.potential_resources);
      writeData(stream, data.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::ARTIFACT>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::ARTIFACT>& artifact) const
    {
      writeData(stream, artifact.guardians);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::EVENT>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::EVENT>& event) const
    {
      writeEventBase(stream, event);
      writeData(stream, event.affected_players);
      writeData(stream, event.applies_to_computer);
      writeData(stream, event.remove_after_first_visit);
      writeData(stream, event.unknown2);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::GARRISON>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::GARRISON>& garrison) const
    {
      writeData(stream, garrison.owner);
      writeData(stream, garrison.creatures);
      writeData(stream, garrison.can_remove_units);
      writeData(stream, garrison.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    void operator()(std::ostream&, const ObjectProperties<MetaObjectType::GENERIC_NO_PROPERTIES>&) const
    {
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::GRAIL>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::GRAIL>& grail) const
    {
      writeData(stream, grail.allowable_radius);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::HERO>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::HERO>& hero) const
    {
      writeData(stream, hero.absod_id);
      writeData(stream, hero.owner);
      writeData(stream, hero.type);
      writeData(stream, hero.name);
      writeData(stream, hero.experience);
      writeData(stream, hero.portrait);
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
  struct H3Writer<ObjectProperties<MetaObjectType::MONSTER>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::MONSTER>& monster) const
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
  struct H3Writer<ObjectProperties<MetaObjectType::PANDORAS_BOX>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::PANDORAS_BOX>& pandoras_box) const
    {
      writeEventBase(stream, pandoras_box);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::PLACEHOLDER_HERO>& hero) const
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
  struct H3Writer<ObjectProperties<MetaObjectType::QUEST_GUARD>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::QUEST_GUARD>& quest_guard) const
    {
      writeData(stream, quest_guard.quest);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::RANDOM_DWELLING>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::RANDOM_DWELLING>& dwelling) const
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
  struct H3Writer<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    void operator()(std::ostream& stream,
                    const ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
    {
      writeData(stream, dwelling.owner);
      writeData(stream, dwelling.min_level);
      writeData(stream, dwelling.max_level);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    void operator()(std::ostream& stream,
                    const ObjectProperties<MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
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
  struct H3Writer<ObjectProperties<MetaObjectType::RESOURCE>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::RESOURCE>& data) const
    {
      writeData(stream, data.guardians);
      writeData(stream, data.quantity);
      writeData(stream, data.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::SCHOLAR>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::SCHOLAR>& scholar) const
    {
      writeData(stream, scholar.reward_type);
      writeData(stream, scholar.reward_value);
      writeData(stream, scholar.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::SEERS_HUT>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::SEERS_HUT>& seers_hut) const
    {
      writeData(stream, seers_hut.quest);
      writeData(stream, seers_hut.reward);
      writeData(stream, seers_hut.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::SHRINE>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::SHRINE>& shrine) const
    {
      writeData(stream, shrine.spell);
      writeData(stream, shrine.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::SIGN>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::SIGN>& sign) const
    {
      writeData(stream, sign.message);
      writeData(stream, sign.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::SPELL_SCROLL>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::SPELL_SCROLL>& spell_scroll) const
    {
      writeData(stream, spell_scroll.guardians);
      writeData(stream, spell_scroll.spell);
      writeData(stream, spell_scroll.unknown);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::TOWN>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::TOWN>& town) const
    {
      writeData(stream, town.absod_id);
      writeData(stream, town.owner);
      writeData(stream, town.name);
      writeData(stream, town.garrison);
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
  struct H3Writer<ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::TRIVIAL_OWNED_OBJECT>& data) const
    {
      writeData(stream, data.owner);
    }
  };

  template<>
  struct H3Writer<ObjectProperties<MetaObjectType::WITCH_HUT>>
  {
    void operator()(std::ostream& stream, const ObjectProperties<MetaObjectType::WITCH_HUT>& witch_hut) const
    {
      writeData(stream, witch_hut.potential_skills);
    }
  };

  void H3Writer<Object>::operator()(std::ostream& stream, const Object& object) const
  {
    writeData(stream, object.x);
    writeData(stream, object.y);
    writeData(stream, object.z);
    writeData(stream, object.template_idx);
    writeData(stream, object.unknown);
    object.properties.visit([&stream] <MetaObjectType T> (const ObjectProperties<T>& value)
                            { writeData(stream, value); });
  }
}
