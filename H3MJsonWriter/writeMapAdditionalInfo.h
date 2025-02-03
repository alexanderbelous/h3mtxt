#pragma once

#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MJsonWriter/writeLossCondition.h>
#include <h3mtxt/H3MJsonWriter/writePrimarySkills.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkill.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkillsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeSpellsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeVictoryCondition.h>

namespace Util_NS
{
  template<>
  struct JsonObjectWriter<h3m::TeamsInfo>
  {
    void operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const
    {
      out.writeField("num_teams", value.num_teams);
      if (value.num_teams != 0)
      {
        out.writeField("team_for_player", value.team_for_player);
      }
      else
      {
        out.writeComment("\"team_for_player\" field is missing because teams are disabled.");
      }
    }
  };

  template<>
  struct JsonValueWriter<h3m::HeroesAvailability>
  {
    void operator()(JsonDocumentWriter& out, const h3m::HeroesAvailability& value) const
    {
      writeValue(out, value.data);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::MapAdditionalInfo::CustomHero>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo::CustomHero& value) const
    {
      out.writeField("type", value.type);
      out.writeField("portrait", value.portrait);
      out.writeField("name", value.name);
      out.writeField("can_hire", value.can_hire);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::Rumor>
  {
    void operator()(FieldsWriter& out, const h3m::Rumor& value) const
    {
      out.writeField("name", value.name);
      out.writeField("description", value.description);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::HeroSettings>
  {
    void operator()(FieldsWriter& out, const h3m::HeroSettings& value) const
    {
      if (value.experience)
      {
        out.writeField("experience", *value.experience);
      }
      if (value.secondary_skills)
      {
        out.writeField("secondary_skills", *value.secondary_skills);
      }
      if (value.artifacts)
      {
        out.writeField("artifacts", *value.artifacts);
      }
      if (value.biography)
      {
        out.writeField("biography", *value.biography);
      }
      out.writeField("gender", value.gender);
      if (value.spells)
      {
        out.writeField("spells", *value.spells);
      }
      if (value.primary_skills)
      {
        out.writeField("primary_skills", *value.primary_skills);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::MapAdditionalInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const
    {
      out.writeField("victory_condition", value.victory_condition);
      out.writeField("loss_condition", value.loss_condition);
      out.writeField( "teams", value.teams);
      out.writeField("heroes_availability", value.heroes_availability);
      out.writeField("placeholder_heroes", value.placeholder_heroes);
      out.writeField("custom_heroes", value.custom_heroes);
      out.writeField("reserved", value.reserved);
      out.writeField("artifacts_nonavailability", value.artifacts_nonavailability);
      out.writeField("disabled_spells", value.disabled_spells);
      out.writeField("disabled_skills", value.disabled_skills);
      out.writeField("rumors", value.rumors);
      out.writeField("heroes_settings", value.heroes_settings.settings());
    }
  };
}
