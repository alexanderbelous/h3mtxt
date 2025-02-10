#pragma once

#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MJsonWriter/writeLossCondition.h>
#include <h3mtxt/H3MJsonWriter/writePlayersBitmask.h>
#include <h3mtxt/H3MJsonWriter/writePrimarySkills.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkill.h>
#include <h3mtxt/H3MJsonWriter/writeSecondarySkillsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeSpellsBitmask.h>
#include <h3mtxt/H3MJsonWriter/writeVictoryCondition.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::TeamsInfo>
  {
    void operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const
    {
      using Fields = h3m::FieldNames<h3m::TeamsInfo>;
      out.writeField(Fields::kNumTeams, value.num_teams);
      if (value.num_teams != 0)
      {
        out.writeField(Fields::kTeamForPlayer, value.team_for_player);
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
      using Fields = h3m::FieldNames<h3m::Rumor>;
      out.writeField(Fields::kName, value.name);
      out.writeField(Fields::kDescription, value.description);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::HeroSettings>
  {
    void operator()(FieldsWriter& out, const h3m::HeroSettings& value) const
    {
      using Fields = h3m::FieldNames<h3m::HeroSettings>;
      if (value.experience)
      {
        out.writeField(Fields::kExperience, *value.experience);
      }
      if (value.secondary_skills)
      {
        out.writeField(Fields::kSecondarySkills, *value.secondary_skills);
      }
      if (value.artifacts)
      {
        out.writeField(Fields::kArtifacts, *value.artifacts);
      }
      if (value.biography)
      {
        out.writeField(Fields::kBiography, *value.biography);
      }
      out.writeField(Fields::kGender, value.gender);
      if (auto enum_str = h3m::getEnumString(value.gender); !enum_str.empty())
      {
        if (value.spells.has_value() || value.primary_skills.has_value())
        {
          out.writeComma();
        }
        out.writeComment(enum_str, false);
      }
      if (value.spells)
      {
        out.writeField(Fields::kSpells , *value.spells);
      }
      if (value.primary_skills)
      {
        out.writeField(Fields::kPrimarySkills, *value.primary_skills);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::MapAdditionalInfo>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const
    {
      using Fields = h3m::FieldNames<h3m::MapAdditionalInfo>;

      out.writeField(Fields::kVictoryCondition, value.victory_condition);
      out.writeField(Fields::kLossCondition, value.loss_condition);
      out.writeField(Fields::kTeams, value.teams);
      out.writeField(Fields::kHeroesAvailability, value.heroes_availability);
      out.writeField(Fields::kPlaceholderHeroes, value.placeholder_heroes);
      out.writeField(Fields::kCustomHeroes, value.custom_heroes);
      out.writeField(Fields::kReserved, value.reserved);
      out.writeField(Fields::kArtifactsNonavailability, value.artifacts_nonavailability);
      out.writeField(Fields::kDisabledSpells, value.disabled_spells);
      out.writeField(Fields::kDisabledSkills, value.disabled_skills);
      out.writeField(Fields::kRumors, value.rumors);
      out.writeField(Fields::kHeroesSettings, value.heroes_settings.settings());
    }
  };
}
