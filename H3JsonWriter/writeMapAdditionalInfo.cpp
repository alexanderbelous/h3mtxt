#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::MapAdditionalInfo::CustomHero>
  {
    void operator()(FieldsWriter& out, const h3m::MapAdditionalInfo::CustomHero& value) const
    {
      constexpr h3m::HeroPortrait kDefaultPortrait {0xFF};
      out.writeField("type", value.type);
      if (auto enum_str = h3m::getEnumString(value.type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("portrait", value.portrait);
      const std::string_view hero_portrait_str =
        (value.portrait == kDefaultPortrait) ? "(Default)" : h3m::getEnumString(value.portrait);
      if (!hero_portrait_str.empty())
      {
        out.writeComma();
        out.writeComment(hero_portrait_str, false);
      }
      out.writeField("name", value.name);
      out.writeField("can_hire", value.can_hire);
    }
  };

  void JsonObjectWriter<h3m::TeamsInfo>::operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const
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

  void JsonObjectWriter<h3m::HeroesBitmask>::operator()(FieldsWriter& out, const h3m::HeroesBitmask& value) const
  {
    using FiledNames = h3m::FieldNames<h3m::HeroesBitmask>;
    for (std::size_t i = 0; i < h3m::HeroesBitmask::kNumBits; ++i)
    {
      out.writeField(FiledNames::kNames[i], value.bitset[i]);
    }
  }

  void JsonObjectWriter<h3m::Rumor>::operator()(FieldsWriter& out, const h3m::Rumor& value) const
  {
    using Fields = h3m::FieldNames<h3m::Rumor>;
    out.writeField(Fields::kName, value.name);
    out.writeField(Fields::kDescription, value.description);
  }

  void JsonObjectWriter<h3m::HeroSettings>::operator()(FieldsWriter& out, const h3m::HeroSettings& value) const
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

  using HeroesSettingsEntry = std::pair<const h3m::HeroType, h3m::HeroSettings>;

  template<>
  struct JsonObjectWriter<HeroesSettingsEntry>
  {
    void operator()(FieldsWriter& out, const HeroesSettingsEntry& entry) const
    {
      out.writeField("hero", entry.first);
      if (std::string_view enum_str = h3m::getEnumString(entry.first); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("settings", entry.second);
    }
  };

  void JsonValueWriter<h3m::HeroesSettings>::operator()(JsonDocumentWriter& out, const h3m::HeroesSettings& value) const
  {
    auto scoped_array_writer = out.writeArray<HeroesSettingsEntry>();
    for (const HeroesSettingsEntry& entry : value.settings())
    {
      scoped_array_writer.writeElement(entry);
    }
  }

  void JsonObjectWriter<h3m::MapAdditionalInfo>::operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const
  {
    using Fields = h3m::FieldNames<h3m::MapAdditionalInfo>;

    out.writeField(Fields::kVictoryCondition, value.victory_condition);
    out.writeField(Fields::kLossCondition, value.loss_condition);
    out.writeField(Fields::kTeams, value.teams);
    out.writeField(Fields::kHeroesAvailability, value.heroes_availability);
    out.writeField(Fields::kPlaceholderHeroes, value.placeholder_heroes);
    out.writeField(Fields::kCustomHeroes, value.custom_heroes);
    out.writeField(Fields::kReserved, value.reserved);
    out.writeField(Fields::kDisabledArtifacts, value.disabled_artifacts);
    out.writeField(Fields::kDisabledSpells, value.disabled_spells);
    out.writeField(Fields::kDisabledSkills, value.disabled_skills);
    out.writeField(Fields::kRumors, value.rumors);
    out.writeField(Fields::kHeroesSettings, value.heroes_settings);
  }
}
