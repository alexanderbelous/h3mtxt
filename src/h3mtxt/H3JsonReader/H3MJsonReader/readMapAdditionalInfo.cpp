#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3json
{
  template<>
  h3m::CustomHero JsonReader2<h3m::CustomHero>::operator()() const
  {
    using Fields = FieldNames<h3m::CustomHero>;
    h3m::CustomHero hero;
    readField(Fields::kType, hero.type);
    readField(Fields::kPortrait, hero.portrait);
    readField(Fields::kName, hero.name);
    readField(Fields::kCanHire, hero.can_hire);
    return hero;
  }

  template<>
  h3m::Teams JsonReader2<h3m::Teams>::operator()() const
  {
    using Fields = FieldNames<h3m::Teams>;
    h3m::Teams teams;
    readField(Fields::kNumTeams, teams.num_teams);
    if (teams.num_teams != 0)
    {
      readField(Fields::kTeamForPlayer, teams.team_for_player);
    }
    return teams;
  }

  template<>
  h3m::Rumor JsonReader2<h3m::Rumor>::operator()() const
  {
    using Fields = FieldNames<h3m::Rumor>;
    h3m::Rumor rumor;
    readField(Fields::kName, rumor.name);
    readField(Fields::kText, rumor.text);
    return rumor;
  }

  template<>
  h3m::HeroesSettings JsonReader2<h3m::HeroesSettings>::operator()() const
  {
    constexpr std::span<const std::string_view, h3m::kNumHeroes> kFieldNames =
      getEnumFieldNames<h3m::HeroType, h3m::kNumHeroes>();

    h3m::HeroesSettings heroes_settings;
    for (std::size_t hero_idx = 0; hero_idx < h3m::kNumHeroes; ++hero_idx)
    {
      const Json::Value& hero_settings_json = getField(kFieldNames[hero_idx]);
      if (!hero_settings_json.isNull())
      {
        const h3m::HeroType hero = static_cast<h3m::HeroType>(hero_idx);
        heroes_settings[hero] = fromJson<h3m::HeroSettings>(hero_settings_json);
      }
    }
    return heroes_settings;
  }

  template<>
  h3m::MapAdditionalInfo JsonReader2<h3m::MapAdditionalInfo>::operator()() const
  {
    using Fields = FieldNames<h3m::MapAdditionalInfo>;

    h3m::MapAdditionalInfo info;
    readField(Fields::kVictoryCondition, info.victory_condition);
    readField(Fields::kLossCondition, info.loss_condition);
    readField(Fields::kTeams, info.teams);
    readField(Fields::kHeroesAvailability, info.heroes_availability);
    readField(Fields::kPlaceholderHeroes, info.placeholder_heroes);
    readField(Fields::kCustomHeroes, info.custom_heroes);
    readField(Fields::kReserved, info.reserved);
    readField(Fields::kDisabledArtifacts, info.disabled_artifacts);
    readField(Fields::kDisabledSpells, info.disabled_spells);
    readField(Fields::kDisabledSkills, info.disabled_skills);
    readField(Fields::kRumors, info.rumors);
    readField(Fields::kHeroesSettings, info.heroes_settings);
    return info;
  }
}
