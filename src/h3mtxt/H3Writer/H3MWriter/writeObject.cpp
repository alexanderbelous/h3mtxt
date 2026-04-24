#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Object.h>

namespace h3m
{
  void H3MWriter::writeEventBase(const EventBase& event) const
  {
    writeData(event.guardians);
    writeData(event.experience);
    writeData(event.spell_points);
    writeData(event.morale);
    writeData(event.luck);
    writeData(event.resources);
    writeData(event.primary_skills);
    writeData(safeCastVectorSize<std::uint8_t>(event.secondary_skills.size()));
    writeSpan(std::span{ event.secondary_skills });
    writeData(safeCastVectorSize<std::uint8_t>(event.artifacts.size()));
    writeSpan(std::span{ event.artifacts });
    writeData(safeCastVectorSize<std::uint8_t>(event.spells.size()));
    writeSpan(std::span{ event.spells });
    writeData(safeCastVectorSize<std::uint8_t>(event.creatures.size()));
    writeSpan(std::span{ event.creatures });
    writeData(event.unknown);
  }

  void H3MWriter::writeData(const Guardians& guardians) const
  {
    writeData(guardians.message);
    writeData(guardians.creatures);
    writeData(guardians.unknown);
  }

  void H3MWriter::writeData(const MessageAndTreasure& value) const
  {
    writeData(value.message);
    writeData(value.resources);
    writeData(value.artifact);
  }

  void H3MWriter::writeData(const TownBuildings& town_buildings) const
  {
    writeData(town_buildings.is_built);
    writeData(town_buildings.is_disabled);
  }

  void H3MWriter::writeData(const TownEvent& event) const
  {
    writeData(static_cast<const TimedEvent&>(event));
    writeData(event.buildings);
    writeData(event.creatures);
    writeData(event.unknown2);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::ABANDONED_MINE>& data) const
  {
    writeData(data.potential_resources);
    writeData(data.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::ARTIFACT>& artifact) const
  {
    writeData(artifact.guardians);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::EVENT>& event) const
  {
    writeEventBase(event);
    writeData(event.affected_players);
    writeData(event.applies_to_computer);
    writeData(event.cancel_after_first_visit);
    writeData(event.unknown2);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::GARRISON>& garrison) const
  {
    writeData(garrison.owner);
    writeData(garrison.unknown);
    writeData(garrison.creatures);
    writeData(garrison.can_remove_units);
    writeData(garrison.unknown2);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::NONE>&) const
  {
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::GRAIL>& grail) const
  {
    writeData(grail.allowable_radius);
    writeData(grail.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::HERO>& hero) const
  {
    writeData(hero.absod_id);
    writeData(hero.owner);
    writeData(hero.type);
    writeData(hero.name);
    writeData(hero.experience);
    writeData(hero.portrait);
    writeData(static_cast<Bool>(hero.secondary_skills.has_value()));
    if (hero.secondary_skills)
    {
      writeData(safeCastVectorSize<std::uint32_t>((*hero.secondary_skills).size()));
      writeSpan(std::span{ *hero.secondary_skills });
    }
    writeData(hero.creatures);
    writeData(hero.formation);
    writeData(hero.artifacts);
    writeData(hero.patrol_radius);
    writeData(hero.biography);
    writeData(hero.gender);
    writeData(hero.spells);
    writeData(hero.primary_skills);
    writeData(hero.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::MONSTER>& monster) const
  {
    writeData(monster.absod_id);
    writeData(monster.count);
    writeData(monster.disposition);
    writeData(monster.message_and_treasure);
    writeData(monster.never_flees);
    writeData(monster.does_not_grow);
    writeData(monster.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::PANDORAS_BOX>& pandoras_box) const
  {
    writeEventBase(pandoras_box);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::PLACEHOLDER_HERO>& hero) const
  {
    constexpr HeroType kRandomHeroType {0xFF};

    writeData(hero.owner);
    writeData(hero.type);
    if (hero.type == kRandomHeroType)
    {
      writeData(hero.power_rating);
    }
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::QUEST_GUARD>& quest_guard) const
  {
    writeData(quest_guard.quest);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING>& dwelling) const
  {
    writeData(dwelling.owner);
    writeData(dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      writeData(dwelling.alignment);
    }
    writeData(dwelling.min_level);
    writeData(dwelling.max_level);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
  {
    writeData(dwelling.owner);
    writeData(dwelling.min_level);
    writeData(dwelling.max_level);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
  {
    writeData(dwelling.owner);
    writeData(dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      writeData(dwelling.alignment);
    }
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::RESOURCE>& data) const
  {
    writeData(data.guardians);
    writeData(data.quantity);
    writeData(data.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SCHOLAR>& scholar) const
  {
    writeData(scholar.rewardType());
    //std::visit([this] (const auto&value) { writeData(value); }, scholar.reward);
    switch (scholar.rewardType())
    {
    case ScholarRewardType::PrimarySkill:
      writeData(std::get<PrimarySkillType>(scholar.reward));
      break;
    case ScholarRewardType::SecondarySkill:
      writeData(std::get<SecondarySkillType>(scholar.reward));
      break;
    case ScholarRewardType::Spell:
      writeData(std::get<SpellType>(scholar.reward));
      break;
    default:
      writeData(std::get<ScholarRandomRewardType>(scholar.reward));
      break;
    }
    writeData(scholar.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SEERS_HUT>& seers_hut) const
  {
    writeData(seers_hut.quest);
    writeData(seers_hut.reward);
    writeData(seers_hut.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SHRINE>& shrine) const
  {
    writeData(shrine.spell);
    writeData(shrine.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SIGN>& sign) const
  {
    writeData(sign.message);
    writeData(sign.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::SPELL_SCROLL>& spell_scroll) const
  {
    writeData(spell_scroll.guardians);
    writeData(spell_scroll.spell);
    writeData(spell_scroll.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::TOWN>& town) const
  {
    writeData(town.absod_id);
    writeData(town.owner);
    writeData(town.name);
    writeData(town.garrison);
    writeData(town.formation);
    writeData(town.buildings);
    if (!town.buildings)
    {
      writeData(town.has_fort);
    }
    writeData(town.must_have_spell);
    writeData(town.may_not_have_spell);
    writeData(safeCastVectorSize<std::uint32_t>(town.events.size()));
    writeSpan(std::span{ town.events });
    writeData(town.alignment);
    writeData(town.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>& data) const
  {
    writeData(data.owner);
    writeData(data.unknown);
  }

  template<>
  void H3MWriter::writeData(const ObjectProperties<ObjectPropertiesType::WITCH_HUT>& witch_hut) const
  {
    writeData(witch_hut.potential_skills);
  }

  void H3MWriter::writeData(const Object& object) const
  {
    writeData(object.coordinates);
    writeData(object.template_idx);
    writeData(object.unknown);
    object.properties.visit([this] <ObjectPropertiesType T> (const ObjectProperties<T>& value)
                            { writeData(value); });
  }
}
