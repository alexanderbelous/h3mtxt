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
      out.writeField("generate_hero", value.generate_hero);
      out.writeField("town_type", value.town_type);
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::StartingHero>
  {
    void operator()(FieldsWriter& out, const h3m::StartingHero& value) const
    {
      out.writeField("is_random", value.is_random);
      out.writeField("type", value.type);
      out.writeField("portrait", value.portrait);
      out.writeField("name", value.name);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::AdditionalPlayerInfo::HeroInfo>
  {
    void operator()(FieldsWriter& out, const h3m::AdditionalPlayerInfo::HeroInfo& value) const
    {
      out.writeField("type", value.type);
      out.writeField("name", value.name);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::AdditionalPlayerInfo>
  {
    void operator()(FieldsWriter& out, const h3m::AdditionalPlayerInfo& value) const
    {
      out.writeField("num_placeholder_heroes", value.num_placeholder_heroes);
      out.writeField("heroes", value.heroes);
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
      out.writeField(Fields::kStartingHero, value.starting_hero);
      if (h3m::shouldHaveAdditionalPlayerInfo(value))
      {
        out.writeField(Fields::kAdditionalInfo, value.additional_info);
      }
    }
  };
}
