#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/ExperienceLevels.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::CustomHero>::operator()(FieldsWriter& out, const h3m::CustomHero& value) const
  {
    using Fields = h3m::FieldNames<h3m::CustomHero>;
    constexpr h3m::HeroPortrait kDefaultPortrait {0xFF};
    out.writeField(Fields::kType, value.type);
    if (auto enum_str = h3m::getEnumString(value.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kPortrait, value.portrait);
    const std::string_view hero_portrait_str =
      (value.portrait == kDefaultPortrait) ? "(Default)" : h3m::getEnumString(value.portrait);
    if (!hero_portrait_str.empty())
    {
      out.writeComment(hero_portrait_str, false);
    }
    out.writeField(Fields::kName, value.name);
    out.writeField(Fields::kCanHire, value.can_hire, true);
  }

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
      out.writeComment("Level " + std::to_string(h3m::getLevelForExperience(*value.experience)), false);
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

  void JsonObjectWriter<h3m::HeroesSettings>::operator()(FieldsWriter& out, const h3m::HeroesSettings& value) const
  {
    // HeroesSettings is essentially std::array<std::optional<h3m::HeroSettings>, h3m::kNumHeroes>.
    // Instead of serializing it as an array, we serialize it as a JSON object with 156 optional fields -
    // 1 field per HeroType.
    constexpr std::span<const std::string_view, h3m::kNumHeroes> kFieldNames =
      h3json::getEnumFieldNames<h3m::HeroType, h3m::kNumHeroes>();

    for (const auto& [hero, settings] : value.settings())
    {
      const std::string_view field_name = kFieldNames[static_cast<std::size_t>(hero)];
      out.writeField(field_name, settings);
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
