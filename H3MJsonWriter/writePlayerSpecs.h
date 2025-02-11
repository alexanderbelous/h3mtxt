#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3MJsonWriter/getEnumString.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::MainTown>
  {
    void operator()(FieldsWriter& out, const h3m::MainTown& value) const
    {
      using Fields = h3m::FieldNames<h3m::MainTown>;
      out.writeField(Fields::kGenerateHero, value.generate_hero);
      out.writeField(Fields::kTownType, value.town_type);
      out.writeField(Fields::kX, value.x);
      out.writeField(Fields::kY, value.y);
      out.writeField(Fields::kZ, value.z);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingHero>
  {
    void operator()(FieldsWriter& out, const h3m::StartingHero& value) const
    {
      using Fields = h3m::FieldNames<h3m::StartingHero>;
      out.writeField(Fields::kType, value.type);
      if (value.type != h3m::HeroType{0xFF})
      {
        out.writeField(Fields::kPortrait, value.portrait);
        out.writeField(Fields::kName, value.name);
      }
      else
      {
        out.writeComment("None", false);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3m::PlayerSpecs::HeroInfo>
  {
    void operator()(FieldsWriter& out, const h3m::PlayerSpecs::HeroInfo& value) const
    {
      out.writeField("type", value.type);
      out.writeField("name", value.name);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::PlayerSpecs>
  {
    void operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const
    {
      using Fields = h3m::FieldNames<h3m::PlayerSpecs>;
      out.writeField(Fields::kCanBeHuman, value.can_be_human);
      out.writeField(Fields::kCanBeComputer, value.can_be_computer);
      out.writeField(Fields::kBehavior, value.behavior);
      if (auto enum_str = h3m::getEnumString(value.behavior); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField(Fields::kCustomizedAlignments, value.customized_alignments);
      out.writeField(Fields::kAllowedAlignments, value.allowed_alignments.bitset);
      out.writeField(Fields::kRandomTown, value.random_town);
      if (value.main_town)
      {
        out.writeField(Fields::kMainTown, *value.main_town);
      }
      else
      {
        out.writeComma();
        out.writeComment("\"main_town\" field is missing because the player doesn't have a designated main town.");
      }
      out.writeField(Fields::kHasRandomHeroes, value.has_random_heroes);
      out.writeField(Fields::kStartingHero, value.starting_hero);
      out.writeField(Fields::kNumNonspecificPlaceholderHeroes, value.num_nonspecific_placeholder_heroes);
      out.writeField(Fields::kHeroes, value.heroes);
    }
  };
}
