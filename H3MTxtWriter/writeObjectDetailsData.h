#pragma once

#include <h3mtxt/Map/ObjectDetailsData.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MTxtWriter/writePrimarySkills.h>
#include <h3mtxt/H3MTxtWriter/writeResources.h>
#include <h3mtxt/H3MTxtWriter/writeSecondarySkill.h>
#include <h3mtxt/H3MTxtWriter/writeSecondarySkillsBitmask.h>
#include <h3mtxt/H3MTxtWriter/writeSpellsBitmask.h>
#include <h3mtxt/H3MTxtWriter/writeTimedEventBase.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::TownBuildings>
  {
    void operator()(FieldsWriter& out, const h3m::TownBuildings& town_buildings) const
    {
      out.writeField("is_built", town_buildings.is_built);
      out.writeField("is_disabled", town_buildings.is_disabled);
    }
  };

  template<>
  struct StructWriter<h3m::TownEvent>
  {
    void operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const
    {
      printTimedEventBase(out, town_event);
      out.writeField("buildings", town_event.buildings);
      out.writeField("creatures", town_event.creatures);
      out.writeField("unknown", town_event.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::CreatureStack>
  {
    void operator()(FieldsWriter& out, const h3m::CreatureStack& guardians) const
    {
      out.writeField("type", guardians.type);
      out.writeField("count", guardians.count);
    }
  };

  template<>
  struct StructWriter<h3m::Guardians>
  {
    void operator()(FieldsWriter& out, const h3m::Guardians& guardians) const
    {
      out.writeField("message", guardians.message);
      if (guardians.creatures)
      {
        out.writeField("guardians", *guardians.creatures);
      }
    }
  };

  // Default implementation for ObjectDetailsData.
  // TODO: remove once specialized for all MetaObjectTypes.
  template<h3m::MetaObjectType T>
  struct StructWriter<h3m::ObjectDetailsData<T>>
  {
    void operator()(FieldsWriter& out, const h3m::ObjectDetailsData<T>&) const
    {
      out.writeComment("NotImplemented");
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::ARTIFACT>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::ARTIFACT>& artifact) const
    {
      if (artifact.guardians)
      {
        out.writeField("guardians", *artifact.guardians);
      }
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GARRISON>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::GARRISON>& garrison) const
    {
      out.writeField("owner", garrison.owner);
      out.writeField("creatures", garrison.creatures);
      out.writeField("can_remove_units", garrison.can_remove_units);
      out.writeField("unknown", garrison.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>
  {
    void operator()(FieldsWriter&,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>&) const
    {
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::GRAIL>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::GRAIL>& data) const
    {
      out.writeField("allowable_radius", data.allowable_radius);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::HERO>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::HERO>& hero) const
    {
      out.writeField("absod_id", hero.absod_id);
      out.writeField("owner", hero.owner);
      out.writeField("type", hero.type);
      if (hero.name)
      {
        out.writeField("name", *hero.name);
      }
      if (hero.experience)
      {
        out.writeField("experience", *hero.experience);
      }
      if (hero.portrait)
      {
        out.writeField("portrait", *hero.portrait);
      }
      if (hero.secondary_skills)
      {
        out.writeField("secondary_skills", *hero.secondary_skills);
      }
      if (hero.creatures)
      {
        out.writeField("creatures", *hero.creatures);
      }
      out.writeField("formation", hero.formation);
      if (hero.artifacts)
      {
        out.writeField("artifacts", *hero.artifacts);
      }
      out.writeField("patrol_radius", hero.patrol_radius);
      if (hero.biography)
      {
        out.writeField("biography", *hero.biography);
      }
      out.writeField("gender", hero.gender);
      if (hero.spells)
      {
        out.writeField("spells", *hero.spells);
      }
      if (hero.primary_skills)
      {
        out.writeField("primary_skills", *hero.primary_skills);
      }
      out.writeField("unknown", hero.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>::MessageAndTreasure>
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
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::MONSTER>& monster) const
    {
      out.writeField("absod_id", monster.absod_id);
      out.writeField("count", monster.count);
      out.writeField("disposition", monster.disposition);
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
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::PLACEHOLDER_HERO>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::PLACEHOLDER_HERO>& hero) const
    {
      constexpr h3m::HeroType kRandomHeroType {0xFF};

      out.writeField("owner", hero.owner);
      out.writeField("type", hero.type);
      if (hero.type == kRandomHeroType)
      {
        out.writeField("power_rating", hero.power_rating);
      }
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING>>
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
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>
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
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>
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
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::RESOURCE>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::RESOURCE>& data) const
    {
      if (data.guardians)
      {
        out.writeField("guardians", *data.guardians);
      }
      out.writeField("quantity", data.quantity);
      out.writeField("unknown", data.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SHRINE>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::SHRINE>& data) const
    {
      out.writeField("spell", data.spell);
      out.writeField("unknown", data.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SIGN>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::SIGN>& data) const
    {
      out.writeField("message", data.message);
      out.writeField("unknown", data.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::SPELL_SCROLL>>
  {
    void operator()(FieldsWriter& out,
      const h3m::ObjectDetailsData<h3m::MetaObjectType::SPELL_SCROLL>& spell_scroll) const
    {
      if (spell_scroll.guardians)
      {
        out.writeField("guardians", *spell_scroll.guardians);
      }
      out.writeField("spell", spell_scroll.spell);
      out.writeField("unknown", spell_scroll.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::TOWN>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::ObjectDetailsData<h3m::MetaObjectType::TOWN>& town) const
    {
      out.writeField("absod_id", town.absod_id);
      out.writeField("owner", town.owner);
      if (town.name)
      {
        out.writeField("name", *town.name);
      }
      if (town.creatures)
      {
        out.writeField("creatures", *town.creatures);
      }
      out.writeField("formation", town.formation);
      if (town.buildings)
      {
        out.writeField("buildings", *town.buildings);
      }
      else
      {
        out.writeField("has_fort", town.has_fort);
      }
      out.writeField("must_have_spell", town.must_have_spell);
      out.writeField("may_not_have_spell", town.may_not_have_spell);
      out.writeField("events", town.events);
      out.writeField("alignment", town.alignment);
      out.writeField("unknown", town.unknown);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>>
  {
    void operator()(FieldsWriter& out,
      const h3m::ObjectDetailsData<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>& data) const
    {
      // TODO: consider printing as the name of the enum constant if it's within the range.
      out.writeField("owner", data.owner);
    }
  };

  template<>
  struct StructWriter<h3m::ObjectDetailsData<h3m::MetaObjectType::WITCH_HUT>>
  {
    void operator()(FieldsWriter& out,
      const h3m::ObjectDetailsData<h3m::MetaObjectType::WITCH_HUT>& witch_hut) const
    {
      out.writeField("skills_availability", witch_hut.skills_availability);
    }
  };
}
