#pragma once

#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetails.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::ABANDONED_MINE>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::ABANDONED_MINE>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kPotentialResources, data.potential_resources);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::ARTIFACT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::ARTIFACT>;

    void operator()(FieldsWriter& out, const Details& artifact) const
    {
      using Fields = h3m::FieldNames<Details>;
      if (artifact.guardians)
      {
        out.writeField(Fields::kGuardians, *artifact.guardians);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::EVENT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::EVENT>;

    void operator()(FieldsWriter& out, const Details& event) const
    {
      using Fields = h3m::FieldNames<Details>;
      printEventBase(out, event);
      out.writeField(Fields::kAffectedPlayers, event.affected_players);
      out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
      out.writeField(Fields::kRemoveAfterFirstVisit, event.remove_after_first_visit);
      out.writeField(Fields::kUnknown2, event.unknown2);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::GARRISON>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::GARRISON>;

    void operator()(FieldsWriter& out, const Details& garrison) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kOwner, garrison.owner);
      out.writeField(Fields::kCreatures, garrison.creatures);
      out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
      out.writeField(Fields::kUnknown, garrison.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    void operator()(FieldsWriter&,
                    const h3m::ObjectDetails<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>&) const
    {
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::GRAIL>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::GRAIL>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kAllowableRadius, data.allowable_radius);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::HERO>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::HERO>;

    void operator()(FieldsWriter& out, const Details& hero) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kAbsodId, hero.absod_id);
      out.writeField(Fields::kOwner, hero.owner);
      out.writeField(Fields::kType, hero.type);
      if (auto enum_str = h3m::getEnumString(hero.type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
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
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::MONSTER>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::MONSTER>;

    void operator()(FieldsWriter& out, const Details& monster) const
    {
      using Fields = h3m::FieldNames<Details>;

      out.writeField(Fields::kAbsodId, monster.absod_id);
      out.writeField(Fields::kCount, monster.count);
      out.writeField(Fields::kDisposition, monster.disposition);
      if (auto enum_str = h3m::getEnumString(monster.disposition); !enum_str.empty())
      {
        out.writeComma();
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
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::PANDORAS_BOX>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetails<h3m::MetaObjectType::PANDORAS_BOX>& pandoras_box) const
    {
      printEventBase(out, pandoras_box);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::PLACEHOLDER_HERO>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::PLACEHOLDER_HERO>;

    void operator()(FieldsWriter& out, const Details& hero) const
    {
      using Fields = h3m::FieldNames<Details>;
      constexpr h3m::HeroType kRandomHeroType {0xFF};

      out.writeField(Fields::kOwner, hero.owner);
      if (auto enum_str = h3m::getEnumString(hero.owner); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kType, hero.type);
      if (hero.type == kRandomHeroType)
      {
        out.writeField(Fields::kPowerRating, hero.power_rating);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::QUEST_GUARD>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::QUEST_GUARD>;

    void operator()(FieldsWriter& out, const Details& quest_guard) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kQuest, quest_guard.quest);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING>;

    void operator()(FieldsWriter& out, const Details& dwelling) const
    {
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
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>;

    void operator()(FieldsWriter& out, const Details& dwelling) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kOwner, dwelling.owner);
      out.writeField(Fields::kMinLevel, dwelling.min_level);
      out.writeField(Fields::kMaxLevel, dwelling.max_level);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>;

    void operator()(FieldsWriter& out, const Details& dwelling) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kOwner, dwelling.owner);
      out.writeField(Fields::kTownAbsodId, dwelling.town_absod_id);
      if (dwelling.town_absod_id == 0)
      {
        out.writeField(Fields::kAlignment, dwelling.alignment);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::RESOURCE>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::RESOURCE>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      if (data.guardians)
      {
        out.writeField(Fields::kGuardians, *data.guardians);
      }
      out.writeField(Fields::kQuantity, data.quantity);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::SCHOLAR>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::SCHOLAR>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kRewardType, data.reward_type);
      if (auto enum_str = h3m::getEnumString(data.reward_type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kRewardValue, data.reward_value);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::SEERS_HUT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::SEERS_HUT>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kQuest, data.quest);
      out.writeField(Fields::kReward, data.reward);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::SHRINE>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::SHRINE>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kSpell, data.spell);
      const std::string_view spell_str = (data.spell == h3m::SpellType{ 0xFF }) ?
        "(Random)" : h3m::getEnumString(data.spell);
      if (!spell_str.empty())
      {
        out.writeComma();
        out.writeComment(spell_str, false);
      }
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::SIGN>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::SIGN>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kMessage, data.message);
      out.writeField(Fields::kUnknown, data.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::SPELL_SCROLL>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::SPELL_SCROLL>;

    void operator()(FieldsWriter& out, const Details& spell_scroll) const
    {
      using Fields = h3m::FieldNames<Details>;
      if (spell_scroll.guardians)
      {
        out.writeField(Fields::kGuardians, *spell_scroll.guardians);
      }
      out.writeField(Fields::kSpell, spell_scroll.spell);
      if (std::string_view enum_str = h3m::getEnumString(spell_scroll.spell); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kUnknown, spell_scroll.unknown);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::TOWN>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::TOWN>;

    void operator()(FieldsWriter& out, const Details& town) const
    {
      using Fields = h3m::FieldNames<Details>;
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
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>;

    void operator()(FieldsWriter& out, const Details& data) const
    {
      using Fields = h3m::FieldNames<Details>;
      // TODO: consider printing as the name of the enum constant if it's within the range.
      out.writeField(Fields::kOwner, data.owner);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::ObjectDetails<h3m::MetaObjectType::WITCH_HUT>>
  {
    using Details = h3m::ObjectDetails<h3m::MetaObjectType::WITCH_HUT>;

    void operator()(FieldsWriter& out, const Details& witch_hut) const
    {
      using Fields = h3m::FieldNames<Details>;
      out.writeField(Fields::kPotentialSkills, witch_hut.potential_skills);
    }
  };
}
