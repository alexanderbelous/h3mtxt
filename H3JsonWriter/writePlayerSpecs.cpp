#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::PlayerSpecs::HeroInfo>
  {
    void operator()(FieldsWriter& out, const h3m::PlayerSpecs::HeroInfo& value) const
    {
      out.writeField("type", value.type);
      if (auto enum_str = h3m::getEnumString(value.type); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
      out.writeField("name", value.name);
    }
  };

  void JsonObjectWriter<h3m::MainTown>::operator()(FieldsWriter& out, const h3m::MainTown& value) const
  {
    constexpr h3m::TownType kRandomTownType {0xFF};
    using Fields = h3m::FieldNames<h3m::MainTown>;
    out.writeField(Fields::kGenerateHero, value.generate_hero);
    out.writeField(Fields::kTownType, value.town_type);
    const std::string_view town_type_str =
      (value.town_type == kRandomTownType) ? "(Random)" : h3m::getEnumString(value.town_type);
    if (!town_type_str.empty())
    {
      out.writeComment(town_type_str, false);
    }
    out.writeField(Fields::kX, value.x);
    out.writeField(Fields::kY, value.y);
    out.writeField(Fields::kZ, value.z);
  }

  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const
  {
    using Fields = h3m::FieldNames<h3m::StartingHero>;
    out.writeField(Fields::kType, value.type);
    const bool has_starting_hero = (value.type != h3m::HeroType{ 0xFF });
    const std::string_view hero_type_str = has_starting_hero ? h3m::getEnumString(value.type) : "(None)";
    if (!hero_type_str.empty())
    {
      out.writeComment(hero_type_str, false);
    }
    if (has_starting_hero)
    {
      out.writeField(Fields::kPortrait, value.portrait);
      if (auto enum_str = h3m::getEnumString(value.portrait); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kName, value.name);
    }
  }

  void JsonObjectWriter<h3m::PlayerSpecs>::operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const
  {
    using Fields = h3m::FieldNames<h3m::PlayerSpecs>;
    out.writeField(Fields::kCanBeHuman, value.can_be_human);
    out.writeField(Fields::kCanBeComputer, value.can_be_computer);
    out.writeField(Fields::kBehavior, value.behavior);
    if (auto enum_str = h3m::getEnumString(value.behavior); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kHasCustomizedAlignments, value.has_customized_alignments);
    out.writeField(Fields::kAllowedAlignments, value.allowed_alignments);
    out.writeField(Fields::kAllowRandomAlignment, value.allow_random_alignment);
    if (value.main_town)
    {
      out.writeField(Fields::kMainTown, *value.main_town);
    }
    else
    {
      out.writeComment("\"main_town\" field is missing because the player doesn't have a designated main town.");
    }
    out.writeField(Fields::kHasRandomHeroes, value.has_random_heroes);
    out.writeField(Fields::kStartingHero, value.starting_hero);
    out.writeField(Fields::kNumNonspecificPlaceholderHeroes, value.num_nonspecific_placeholder_heroes);
    out.writeField(Fields::kHeroes, value.heroes);
  }
}
