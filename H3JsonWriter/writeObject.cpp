#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/writeObjectProperties.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Constants/ExperienceLevels.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/ObjectTemplate.h>

#include <stdexcept>

namespace h3m
{
  namespace
  {
    std::string makeObjectTemplateComment(const ObjectTemplate& object_template)
    {
      const ObjectClass object_class = object_template.object_class;
      const MetaObjectType meta_object_type = getMetaObjectType(object_class);

      H3JsonWriter_NS::CommentBuilder comment_builder;
      comment_builder << "ObjectClass: " << static_cast<std::size_t>(object_class);
      if (std::string_view enum_str = getEnumString(object_class); !enum_str.empty())
      {
        comment_builder << " (" << enum_str << ")";
      }
      comment_builder << "\nMetaObjectType: " << static_cast<std::size_t>(meta_object_type);
      if (std::string_view enum_str = getEnumString(meta_object_type); !enum_str.empty())
      {
        comment_builder << " (" << enum_str << ")";
      }
      return comment_builder.str();
    }
  }
}

namespace Medea_NS
{
  void JsonObjectWriter<h3m::ResourcesBitmask>::operator()(FieldsWriter& out,
                                                           const h3m::ResourcesBitmask& resources_bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::ResourcesBitmask>;
    for (std::uint8_t i = 0; i < h3m::ResourcesBitmask::kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], resources_bitmask[static_cast<h3m::ResourceType>(i)]);
    }
  }

  void JsonObjectWriter<h3m::TownBuildingsBitmask>::operator()(
    FieldsWriter& out, const h3m::TownBuildingsBitmask& buildings_bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::TownBuildingsBitmask>;
    for (std::size_t i = 0; i < h3m::TownBuildingsBitmask::kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], buildings_bitmask.bitset[i]);
    }
  }

  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const
  {
    using Fields = h3m::FieldNames<h3m::TownBuildings>;
    out.writeField(Fields::kIsBuilt, town_buildings.is_built);
    out.writeField(Fields::kIsDisabled, town_buildings.is_disabled);
  }

  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const
  {
    using Fields = h3m::FieldNames<h3m::TownEvent>;
    JsonObjectWriter<h3m::TimedEventBase>{}(out, town_event);
    out.writeField(Fields::kBuildings, town_event.buildings);
    out.writeField(Fields::kCreatures, town_event.creatures);
    out.writeField(Fields::kUnknown2, town_event.unknown2);
  }

  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const
  {
    using Fields = h3m::FieldNames<h3m::Guardians>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
    out.writeField(Fields::kUnknown, guardians.unknown);
  }

  void JsonObjectWriter<h3m::MessageAndTreasure>::operator()(FieldsWriter& out,
                                                             const h3m::MessageAndTreasure& data) const
  {
    using Fields = h3m::FieldNames<h3m::MessageAndTreasure>;
    out.writeField(Fields::kMessage, data.message);
    out.writeField(Fields::kResources, data.resources);
    out.writeField(Fields::kArtifact, data.artifact);
    const std::string_view artifact_str = (data.artifact == h3m::ArtifactType{ 0xFFFF }) ?
      "(None)" : h3m::getEnumString(data.artifact);
    if (!artifact_str.empty())
    {
      out.writeComment(artifact_str, false);
    }
  }

  void JsonObjectWriter<h3m::EventBase>::operator()(FieldsWriter& out, const h3m::EventBase& event) const
  {
    using Fields = h3m::FieldNames<h3m::EventBase>;
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

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::ABANDONED_MINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::ABANDONED_MINE>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::ABANDONED_MINE>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kPotentialResources, details.potential_resources);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::ARTIFACT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::ARTIFACT>& artifact) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::ARTIFACT>;
    using Fields = h3m::FieldNames<Details>;
    if (artifact.guardians)
    {
      out.writeField(Fields::kGuardians, *artifact.guardians);
    }
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::EVENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::EVENT>& event) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::EVENT>;
    using Fields = h3m::FieldNames<Details>;
    JsonObjectWriter<h3m::EventBase>{}(out, event);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kRemoveAfterFirstVisit, event.remove_after_first_visit);
    out.writeField(Fields::kUnknown2, event.unknown2);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GARRISON>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::GARRISON>& garrison) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::GARRISON>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kOwner, garrison.owner);
    if (std::string_view enum_str = h3m::getEnumString(garrison.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, garrison.unknown);
    out.writeField(Fields::kCreatures, garrison.creatures);
    out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
    out.writeField(Fields::kUnknown2, garrison.unknown2);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>::operator()(
    FieldsWriter&, const h3m::ObjectProperties<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>&) const
  {
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GRAIL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::GRAIL>& grail) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::GRAIL>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kAllowableRadius, grail.allowable_radius);
    out.writeField(Fields::kUnknown, grail.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::HERO>& hero) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::HERO>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kAbsodId, hero.absod_id);
    out.writeField(Fields::kOwner, hero.owner);
    if (auto enum_str = h3m::getEnumString(hero.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kType, hero.type);
    if (auto enum_str = h3m::getEnumString(hero.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
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
      if (std::string_view enum_str = h3m::getEnumString(*hero.portrait); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
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
    if (auto enum_str = h3m::getEnumString(hero.formation); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    if (hero.artifacts)
    {
      out.writeField(Fields::kArtifacts, *hero.artifacts);
    }
    out.writeField(Fields::kPatrolRadius, hero.patrol_radius);
    if (hero.biography)
    {
      out.writeField(Fields::kBiography, *hero.biography);
    }
    out.writeField(Fields::kGender, hero.gender);
    if (auto enum_str = h3m::getEnumString(hero.gender); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
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

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::MONSTER>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::MONSTER>& monster) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::MONSTER>;
    using Fields = h3m::FieldNames<Details>;

    out.writeField(Fields::kAbsodId, monster.absod_id);
    out.writeField(Fields::kCount, monster.count);
    out.writeField(Fields::kDisposition, monster.disposition);
    if (auto enum_str = h3m::getEnumString(monster.disposition); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    if (monster.message_and_treasure)
    {
      out.writeField(Fields::kMessageAndTreasure, *monster.message_and_treasure);
    }
    out.writeField(Fields::kNeverFlees, monster.never_flees);
    out.writeField(Fields::kDoesNotGrow, monster.does_not_grow);
    out.writeField(Fields::kUnknown, monster.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::PANDORAS_BOX>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::PANDORAS_BOX>& pandoras_box) const
  {
    JsonObjectWriter<h3m::EventBase>{}(out, pandoras_box);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::PLACEHOLDER_HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::PLACEHOLDER_HERO>& hero) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::PLACEHOLDER_HERO>;
    using Fields = h3m::FieldNames<Details>;
    constexpr h3m::HeroType kRandomHeroType {0xFF};

    out.writeField(Fields::kOwner, hero.owner);
    if (auto enum_str = h3m::getEnumString(hero.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kType, hero.type);
    if (hero.type == kRandomHeroType)
    {
      out.writeField(Fields::kPowerRating, hero.power_rating);
    }
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::QUEST_GUARD>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::QUEST_GUARD>& quest_guard) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::QUEST_GUARD>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kQuest, quest_guard.quest);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kTownAbsodId, dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      out.writeField(Fields::kAlignment, dwelling.alignment);
    }
    out.writeField(Fields::kMinLevel, dwelling.min_level);
    out.writeField(Fields::kMaxLevel, dwelling.max_level);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kMinLevel, dwelling.min_level);
    out.writeField(Fields::kMaxLevel, dwelling.max_level);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kOwner, dwelling.owner);
    out.writeField(Fields::kTownAbsodId, dwelling.town_absod_id);
    if (dwelling.town_absod_id == 0)
    {
      out.writeField(Fields::kAlignment, dwelling.alignment);
    }
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RESOURCE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RESOURCE>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::RESOURCE>;
    using Fields = h3m::FieldNames<Details>;
    if (details.guardians)
    {
      out.writeField(Fields::kGuardians, *details.guardians);
    }
    out.writeField(Fields::kQuantity, details.quantity);
    out.writeField(Fields::kUnknown, details.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SCHOLAR>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SCHOLAR>& scholar) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::SCHOLAR>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kRewardType, scholar.reward_type);
    if (std::string_view enum_str = h3m::getEnumString(scholar.reward_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRewardValue, scholar.reward_value);
    out.writeField(Fields::kUnknown, scholar.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SEERS_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SEERS_HUT>& seers_hut) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::SEERS_HUT>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kUnknown, seers_hut.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SHRINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SHRINE>& shrine) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::SHRINE>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kSpell, shrine.spell);
    const std::string_view spell_str = (shrine.spell == h3m::SpellType{ 0xFF }) ?
      "(Random)" : h3m::getEnumString(shrine.spell);
    if (!spell_str.empty())
    {
      out.writeComment(spell_str, false);
    }
    out.writeField(Fields::kUnknown, shrine.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SIGN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SIGN>& sign) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::SIGN>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kMessage, sign.message);
    out.writeField(Fields::kUnknown, sign.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SPELL_SCROLL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SPELL_SCROLL>& spell_scroll) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::SPELL_SCROLL>;
    using Fields = h3m::FieldNames<Details>;
    if (spell_scroll.guardians)
    {
      out.writeField(Fields::kGuardians, *spell_scroll.guardians);
    }
    out.writeField(Fields::kSpell, spell_scroll.spell);
    if (std::string_view enum_str = h3m::getEnumString(spell_scroll.spell); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, spell_scroll.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::TOWN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::TOWN>& town) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::TOWN>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kAbsodId, town.absod_id);
    out.writeField(Fields::kOwner, town.owner);
    if (std::string_view enum_str = h3m::getEnumString(town.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    if (town.name)
    {
      out.writeField(Fields::kName, *town.name);
    }
    if (town.garrison)
    {
      out.writeField(Fields::kGarrison, *town.garrison);
    }
    out.writeField(Fields::kFormation, town.formation);
    if (auto enum_str = h3m::getEnumString(town.formation); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
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

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>& details) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kOwner, details.owner);
    if (std::string_view enum_str = h3m::getEnumString(details.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, details.unknown);
  }

  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::WITCH_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::WITCH_HUT>& witch_hut) const
  {
    using Details = h3m::ObjectProperties<h3m::MetaObjectType::WITCH_HUT>;
    using Fields = h3m::FieldNames<Details>;
    out.writeField(Fields::kPotentialSkills, witch_hut.potential_skills);
  }

  void JsonObjectWriter<h3m::Object>::operator()(FieldsWriter& out, const h3m::Object& object) const
  {
    using Fields = h3m::FieldNames<h3m::Object>;
    out.writeField(Fields::kX, object.x);
    out.writeField(Fields::kY, object.y);
    out.writeField(Fields::kZ, object.z);
    if (objects_templates_)
    {
      if (object.template_idx >= num_objects_templates_)
      {
        throw std::runtime_error("JsonObjectWriter<h3m::Object>: Object::template_idx is out of range.");
      }
      const h3m::ObjectTemplate& object_template = objects_templates_[object.template_idx];
      if (h3m::getMetaObjectType(object_template.object_class) != object.properties.getMetaObjectType())
      {
        throw std::runtime_error("JsonObjectWriter<h3m::Object>: Object::properties has MetaObjectType different "
                                 "from the ObjectTemplate it refers to.");
      }
      out.writeComment(h3m::makeObjectTemplateComment(object_template));
    }
    out.writeField(Fields::kTemplateIdx, object.template_idx);
    out.writeField(Fields::kUnknown, object.unknown);
    if (object.properties.getMetaObjectType() != h3m::MetaObjectType::GENERIC_NO_PROPERTIES)
    {
      object.properties.visit([&out] <h3m::MetaObjectType T> (const h3m::ObjectProperties<T>& details)
                              { out.writeField(Fields::kProperties, details); });
    }
  }
}
