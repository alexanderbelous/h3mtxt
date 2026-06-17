#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Constants/ExperienceLevels.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Medea/Medea.h>

#include <stdexcept>

namespace h3json
{
  namespace
  {
    std::string makeObjectTemplateComment(const h3m::ObjectTemplate& object_template)
    {
      const h3m::ObjectClass object_class = object_template.object_class;
      const h3m::ObjectPropertiesType object_properties_type =
        h3m::getObjectPropertiesType(object_class, object_template.object_subclass);

      Detail_NS::CommentBuilder comment_builder;
      comment_builder << "ObjectClass: " << static_cast<std::size_t>(object_class);
      if (std::string_view enum_str = Medea_NS::EnumCommentGetter{}(object_class); !enum_str.empty())
      {
        comment_builder << " (" << enum_str << ")";
      }
      if (std::string_view enum_str = Medea_NS::EnumCommentGetter{}(object_properties_type); !enum_str.empty())
      {
        comment_builder << "\nObjectPropertiesType: " << enum_str;
      }
      return comment_builder.str();
    }
  }
}

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const
  {
    using Fields = h3json::FieldNames<h3m::TownBuildings>;
    out.writeField(Fields::kIsBuilt, town_buildings.is_built);
    out.writeField(Fields::kIsDisabled, town_buildings.is_disabled);
  }

  template<>
  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const
  {
    using Fields = h3json::FieldNames<h3m::TownEvent>;
    JsonObjectWriter<h3m::TimedEvent>{}(out, town_event);
    out.writeField(Fields::kBuildings, town_event.buildings);
    out.writeField(Fields::kCreatures, town_event.creatures);
    out.writeField(Fields::kUnknown2, town_event.unknown2);
  }

  template<>
  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const
  {
    using Fields = h3json::FieldNames<h3m::Guardians>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
    out.writeField(Fields::kUnknown, guardians.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::MessageAndTreasure>::operator()(FieldsWriter& out,
                                                             const h3m::MessageAndTreasure& data) const
  {
    using Fields = h3json::FieldNames<h3m::MessageAndTreasure>;
    out.writeField(Fields::kMessage, data.message);
    out.writeField(Fields::kResources, data.resources);
    out.writeField(Fields::kArtifact, data.artifact);
  }

  template<>
  void JsonObjectWriter<h3m::EventBase>::operator()(FieldsWriter& out, const h3m::EventBase& event) const
  {
    using Fields = h3json::FieldNames<h3m::EventBase>;
    if (event.guardians)
    {
      out.writeField(Fields::kGuardians, *event.guardians);
    }
    out.writeField(Fields::kExperience, event.experience);
    out.writeField(Fields::kSpellPoints, event.spell_points);
    out.writeField(Fields::kMorale, event.morale);
    out.writeField(Fields::kLuck, event.luck);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kPrimarySkills, event.primary_skills);
    out.writeField(Fields::kSecondarySkills, event.secondary_skills);
    out.writeField(Fields::kArtifacts, event.artifacts);
    out.writeField(Fields::kSpells, event.spells);
    out.writeField(Fields::kCreatures, event.creatures);
    out.writeField(Fields::kUnknown, event.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kPotentialResources, details.potential_resources);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>& artifact) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>;
    using Fields = h3json::FieldNames<Details>;
    if (artifact.guardians)
    {
      out.writeField(Fields::kGuardians, *artifact.guardians);
    }
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>& event) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>;
    using Fields = h3json::FieldNames<Details>;
    JsonObjectWriter<h3m::EventBase>{}(out, event);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kCancelAfterFirstVisit, event.cancel_after_first_visit);
    out.writeField(Fields::kUnknown2, event.unknown2);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>& garrison) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kOwner, garrison.owner);
    out.writeField(Fields::kUnknown, garrison.unknown);
    out.writeField(Fields::kCreatures, garrison.creatures);
    out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
    out.writeField(Fields::kUnknown2, garrison.unknown2);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>>::operator()(
    FieldsWriter&, const h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>&) const
  {
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>& grail) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kAllowableRadius, grail.allowable_radius);
    out.writeField(Fields::kUnknown, grail.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>& hero) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kAbsodId, hero.absod_id);
    out.writeField(Fields::kOwner, hero.owner);
    out.writeField(Fields::kType, hero.type);
    if (hero.name)
    {
      out.writeField(Fields::kName, *hero.name);
    }
    if (hero.experience)
    {
      out.writeField(Fields::kExperience, *hero.experience);
      out.writeComment("Level " + std::to_string(h3m::getLevelForExperience(*hero.experience)), false);
    }
    if (hero.portrait)
    {
      out.writeField(Fields::kPortrait, *hero.portrait);
    }
    if (hero.secondary_skills)
    {
      out.writeField(Fields::kSecondarySkills, *hero.secondary_skills);
    }
    if (hero.creatures)
    {
      out.writeField(Fields::kCreatures, *hero.creatures);
    }
    out.writeField(Fields::kFormation, hero.formation);
    if (hero.artifacts)
    {
      out.writeField(Fields::kArtifacts, *hero.artifacts);
    }
    out.writeField(Fields::kPatrolRadius, hero.patrol_radius);
    if (hero.patrol_radius < 0)
    {
      out.writeComment("(None)", false);
    }
    if (hero.biography)
    {
      out.writeField(Fields::kBiography, *hero.biography);
    }
    out.writeField(Fields::kGender, hero.gender);
    if (hero.spells)
    {
      out.writeField(Fields::kSpells, *hero.spells);
    }
    if (hero.primary_skills)
    {
      out.writeField(Fields::kPrimarySkills, *hero.primary_skills);
    }
    out.writeField(Fields::kUnknown, hero.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>& monster) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>;
    using Fields = h3json::FieldNames<Details>;

    out.writeField(Fields::kAbsodId, monster.absod_id);
    out.writeField(Fields::kQuantity, monster.quantity);
    out.writeField(Fields::kDisposition, monster.disposition);
    if (monster.message_and_treasure)
    {
      out.writeField(Fields::kMessageAndTreasure, *monster.message_and_treasure);
    }
    out.writeField(Fields::kNeverFlees, monster.never_flees);
    out.writeField(Fields::kDoesNotGrow, monster.does_not_grow);
    out.writeField(Fields::kUnknown, monster.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>& pandoras_box) const
  {
    JsonObjectWriter<h3m::EventBase>{}(out, pandoras_box);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO_PLACEHOLDER>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO_PLACEHOLDER>& hero) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO_PLACEHOLDER>;
    using Fields = h3json::FieldNames<Details>;
    constexpr h3m::HeroType kRandomHeroType {0xFF};

    out.writeField(Fields::kOwner, hero.owner);
    out.writeField(Fields::kType, hero.type);
    if (hero.type == kRandomHeroType)
    {
      out.writeField(Fields::kPowerRating, hero.power_rating);
    }
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>& quest_guard) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kQuest, quest_guard.quest);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kUnknown, dwelling.unknown);
    out.writeField(Fields::kTownAbsodId, dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      out.writeField(Fields::kAlignment, dwelling.alignment);
    }
    out.writeField(Fields::kMinLevel, dwelling.min_level);
    out.writeField(Fields::kMaxLevel, dwelling.max_level);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kUnknown, dwelling.unknown);
    out.writeField(Fields::kMinLevel, dwelling.min_level);
    out.writeField(Fields::kMaxLevel, dwelling.max_level);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kUnknown, dwelling.unknown);
    out.writeField(Fields::kTownAbsodId, dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      out.writeField(Fields::kAlignment, dwelling.alignment);
    }
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>;
    using Fields = h3json::FieldNames<Details>;
    if (details.guardians)
    {
      out.writeField(Fields::kGuardians, *details.guardians);
    }
    out.writeField(Fields::kQuantity, details.quantity);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>& scholar) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kRewardType, scholar.rewardType());
    // reward_value is always a 1-byte enum type.
    std::visit([&out](auto reward_value)
               {
                 out.writeField(Fields::kRewardValue, reward_value);
               },
               scholar.reward);
    out.writeField(Fields::kUnknown, scholar.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>& seers_hut) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kUnknown, seers_hut.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>& shrine) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kSpell, shrine.spell);
    out.writeField(Fields::kUnknown, shrine.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>& sign) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kMessage, sign.message);
    out.writeField(Fields::kUnknown, sign.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>& spell_scroll) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>;
    using Fields = h3json::FieldNames<Details>;
    if (spell_scroll.guardians)
    {
      out.writeField(Fields::kGuardians, *spell_scroll.guardians);
    }
    out.writeField(Fields::kSpell, spell_scroll.spell);
    out.writeField(Fields::kUnknown, spell_scroll.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>& town) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kAbsodId, town.absod_id);
    out.writeField(Fields::kOwner, town.owner);
    if (town.name)
    {
      out.writeField(Fields::kName, *town.name);
    }
    if (town.garrison)
    {
      out.writeField(Fields::kGarrison, *town.garrison);
    }
    out.writeField(Fields::kFormation, town.formation);
    if (town.buildings)
    {
      out.writeField(Fields::kBuildings, *town.buildings);
    }
    else
    {
      out.writeField(Fields::kHasFort, town.has_fort);
    }
    out.writeField(Fields::kMustHaveSpell, town.must_have_spell);
    out.writeField(Fields::kMayNotHaveSpell, town.may_not_have_spell);
    out.writeField(Fields::kEvents, town.events);
    out.writeField(Fields::kAlignment, town.alignment);
    out.writeField(Fields::kUnknown, town.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kOwner, details.owner);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>& witch_hut) const
  {
    using Details = h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>;
    using Fields = h3json::FieldNames<Details>;
    out.writeField(Fields::kPotentialSkills, witch_hut.potential_skills);
  }

  void JsonObjectWriter<h3m::Object>::operator()(FieldsWriter& out, const h3m::Object& object) const
  {
    using Fields = h3json::FieldNames<h3m::Object>;
    out.writeField(Fields::kCoordinates, object.coordinates);
    if (objects_templates_)
    {
      if (object.template_idx >= num_objects_templates_)
      {
        throw std::runtime_error("JsonObjectWriter<h3m::Object>: Object::template_idx is out of range.");
      }
      const h3m::ObjectTemplate& object_template = objects_templates_[object.template_idx];
      if (object.properties.type() !=
          h3m::getObjectPropertiesType(object_template.object_class, object_template.object_subclass))
      {
        throw std::runtime_error("JsonObjectWriter<h3m::Object>: Object::properties has ObjectPropertiesType "
                                 "different from the ObjectTemplate it refers to.");
      }
      out.writeComment(h3json::makeObjectTemplateComment(object_template));
    }
    out.writeField(Fields::kTemplateIdx, object.template_idx);
    out.writeField(Fields::kUnknown, object.unknown);
    if (object.properties.type() != h3m::ObjectPropertiesType::NONE)
    {
      object.properties.visit([&out] <h3m::ObjectPropertiesType T> (const h3m::ObjectProperties<T>& details)
                              { out.writeField(Fields::kProperties, details); });
    }
  }
}
