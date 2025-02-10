#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetailsData.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/writeCreatureStack.h>
#include <h3mtxt/H3MJsonWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MJsonWriter/writePrimarySkills.h>
#include <h3mtxt/H3MJsonWriter/writeQuest.h>
#include <h3mtxt/H3MJsonWriter/writeResources.h>
#include <h3mtxt/H3MJsonWriter/writeReward.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkill.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkillsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeSpellsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeTimedEventBase.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::ResourcesBitmask>
  {
    void operator()(FieldsWriter& out, const h3m::ResourcesBitmask& resources_bitmask) const
    {
      using Fields = h3m::FieldNames<h3m::ResourcesBitmask>;
      for (std::uint8_t i = 0; i < 8; ++i)
      {
        out.writeField(Fields::kNames[i], resources_bitmask[static_cast<h3m::ResourceType>(i)]);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::TownBuildings>
  {
    void operator()(FieldsWriter& out, const h3m::TownBuildings& town_buildings) const
    {
      using Fields = h3m::FieldNames<h3m::TownBuildings>;
      out.writeField(Fields::kIsBuilt, town_buildings.is_built);
      out.writeField(Fields::kIsDisabled, town_buildings.is_disabled);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::TownEvent>
  {
    void operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const
    {
      using Fields = h3m::FieldNames<h3m::TownEvent>;
      printTimedEventBase(out, town_event);
      out.writeField(Fields::kBuildings, town_event.buildings);
      out.writeField(Fields::kCreatures, town_event.creatures);
      out.writeField(Fields::kUnknown2, town_event.unknown2);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::Guardians>
  {
    void operator()(FieldsWriter& out, const h3m::Guardians& guardians) const
    {
      using Fields = h3m::FieldNames<h3m::Guardians>;
      out.writeField(Fields::kMessage, guardians.message);
      if (guardians.creatures)
      {
        out.writeField(Fields::kCreatures, *guardians.creatures);
      }
      out.writeField(Fields::kUnknown, guardians.unknown);
    }
  };

  inline void printEventBase(FieldsWriter& out, const h3m::EventBase& event)
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

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::ABANDONED_MINE>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::ABANDONED_MINE>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kPotentialResources, data.potential_resources);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::ARTIFACT>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::ARTIFACT>;

    void operator()(FieldsWriter& out, const DetailsData& artifact) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      if (artifact.guardians)
      {
        out.writeField(Fields::kGuardians, *artifact.guardians);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::EVENT>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::EVENT>;

    void operator()(FieldsWriter& out, const DetailsData& event) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      printEventBase(out, event);
      out.writeField(Fields::kAffectedPlayers, event.affected_players);
      out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
      out.writeField(Fields::kRemoveAfterFirstVisit, event.remove_after_first_visit);
      out.writeField(Fields::kUnknown2, event.unknown2);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GARRISON>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::GARRISON>;

    void operator()(FieldsWriter& out, const DetailsData& garrison) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kOwner, garrison.owner);
      out.writeField(Fields::kCreatures, garrison.creatures);
      out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
      out.writeField(Fields::kUnknown, garrison.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    void operator()(FieldsWriter&,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>&) const
    {
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GRAIL>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::GRAIL>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kAllowableRadius, data.allowable_radius);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::HERO>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::HERO>;

    void operator()(FieldsWriter& out, const DetailsData& hero) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
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
      if (auto enum_str = h3m::getEnumString(hero.formation); !enum_str.empty())
      {
        out.writeComma();
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
        out.writeComma();
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
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>::MessageAndTreasure>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>::MessageAndTreasure& data) const
    {
      out.writeField("message", data.message);
      out.writeField("resources", data.resources);
      out.writeField("artifact", data.artifact);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>& monster) const
    {
      out.writeField("absod_id", monster.absod_id);
      out.writeField("count", monster.count);
      out.writeField("disposition", monster.disposition);
      if (auto enum_str = h3m::getEnumString(monster.disposition); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      if (monster.message_and_treasure)
      {
        out.writeField("message_and_treasure", *monster.message_and_treasure);
      }
      out.writeField("never_flees", monster.never_flees);
      out.writeField("does_not_grow", monster.does_not_grow);
      out.writeField("unknown", monster.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::PANDORAS_BOX>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::PANDORAS_BOX>& pandoras_box) const
    {
      printEventBase(out, pandoras_box);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::PLACEHOLDER_HERO>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::PLACEHOLDER_HERO>;

    void operator()(FieldsWriter& out, const DetailsData& hero) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      constexpr h3m::HeroType kRandomHeroType {0xFF};

      out.writeField(Fields::kOwner, hero.owner);
      out.writeField(Fields::kType, hero.type);
      if (hero.type == kRandomHeroType)
      {
        out.writeField(Fields::kPowerRating, hero.power_rating);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::QUEST_GUARD>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::QUEST_GUARD>& quest_guard) const
    {
      out.writeField("quest", quest_guard.quest);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING>& dwelling) const
    {
      out.writeField("owner", dwelling.owner);
      out.writeField("town_absod_id", dwelling.town_absod_id);
      if (dwelling.town_absod_id != 0)
      {
        out.writeField("alignment", dwelling.alignment);
      }
      out.writeField("min_level", dwelling.min_level);
      out.writeField("max_level", dwelling.max_level);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>& dwelling) const
    {
      out.writeField("owner", dwelling.owner);
      out.writeField("min_level", dwelling.min_level);
      out.writeField("max_level", dwelling.max_level);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>& dwelling) const
    {
      out.writeField("owner", dwelling.owner);
      out.writeField("town_absod_id", dwelling.town_absod_id);
      if (dwelling.town_absod_id != 0)
      {
        out.writeField("alignment", dwelling.alignment);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RESOURCE>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::RESOURCE>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      if (data.guardians)
      {
        out.writeField(Fields::kGuardians, *data.guardians);
      }
      out.writeField(Fields::kQuantity, data.quantity);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SCHOLAR>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::SCHOLAR>& data) const
    {
      out.writeField("reward_type", data.reward_type);
      if (auto enum_str = h3m::getEnumString(data.reward_type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("reward_value", data.reward_value);
      out.writeField("unknown", data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SEERS_HUT>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::SEERS_HUT>& data) const
    {
      out.writeField("quest", data.quest);
      out.writeField("reward", data.reward);
      out.writeField("unknown", data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SHRINE>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::SHRINE>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kSpell, data.spell);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SIGN>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::SIGN>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kMessage, data.message);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SPELL_SCROLL>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::SPELL_SCROLL>;

    void operator()(FieldsWriter& out, const DetailsData& spell_scroll) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      if (spell_scroll.guardians)
      {
        out.writeField(Fields::kGuardians, *spell_scroll.guardians);
      }
      out.writeField(Fields::kSpell, spell_scroll.spell);
      out.writeField(Fields::kUnknown, spell_scroll.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::TOWN>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::TOWN>;

    void operator()(FieldsWriter& out, const DetailsData& town) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kAbsodId, town.absod_id);
      out.writeField(Fields::kOwner, town.owner);
      if (town.name)
      {
        out.writeField(Fields::kName, *town.name);
      }
      if (town.creatures)
      {
        out.writeField(Fields::kCreatures, *town.creatures);
      }
      out.writeField(Fields::kFormation, town.formation);
      if (auto enum_str = h3m::getEnumString(town.formation); !enum_str.empty())
      {
        out.writeComma();
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
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>;

    void operator()(FieldsWriter& out, const DetailsData& data) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      // TODO: consider printing as the name of the enum constant if it's within the range.
      out.writeField(Fields::kOwner, data.owner);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::WITCH_HUT>>
  {
    using DetailsData = h3m::ObjectDetailsData<h3m::MetaObjectType::WITCH_HUT>;

    void operator()(FieldsWriter& out, const DetailsData& witch_hut) const
    {
      using Fields = h3m::FieldNames<DetailsData>;
      out.writeField(Fields::kSkillsAvailability, witch_hut.skills_availability);
    }
  };
}
