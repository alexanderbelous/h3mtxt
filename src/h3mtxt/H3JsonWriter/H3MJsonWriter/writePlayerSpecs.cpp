#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
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
  void JsonObjectWriter<h3m::MainTown>::operator()(FieldsWriter& out, const h3m::MainTown& value) const
  {
    using Fields = h3json::FieldNames<h3m::MainTown>;
    out.writeField(Fields::kGenerateHero, value.generate_hero);
    out.writeField(Fields::kTownType, value.town_type);
    out.writeField(Fields::kCoordinates, value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const
  {
    using Fields = h3json::FieldNames<h3m::StartingHero>;
    out.writeField(Fields::kType, value.type);
    const bool has_starting_hero = (value.type != h3m::HeroType{ 0xFF });
    // TODO: consider adding h3m::HeroType::None = 0xFF.
    if (!has_starting_hero)
    {
      out.writeComment("(None)", false);
    }
    if (has_starting_hero)
    {
      out.writeField(Fields::kPortrait, value.portrait);
      out.writeField(Fields::kName, value.name);
    }
  }

  template<>
  void JsonObjectWriter<h3m::PlayerSpecs>::operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const
  {
    using Fields = h3json::FieldNames<h3m::PlayerSpecs>;
    out.writeField(Fields::kCanBeHuman, value.can_be_human);
    out.writeField(Fields::kCanBeComputer, value.can_be_computer);
    out.writeField(Fields::kBehavior, value.behavior);
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
