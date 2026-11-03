#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Town.h>

namespace h3json
{
  template<>
  h3svg::Town JsonReader2<h3svg::Town>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Town>;
    h3svg::Town town;
    readField(Fields::kId, town.id);
    readField(Fields::kOwner, town.owner);
    readField(Fields::kBuiltThisTurn, town.built_this_turn);
    readField(Fields::kUnknown1, town.unknown1);
    readField(Fields::kType, town.type);
    readField(Fields::kCoordinates, town.coordinates);
    readField(Fields::kGeneratedBoatX, town.generated_boat_x);
    readField(Fields::kGeneratedBoatY, town.generated_boat_y);
    readField(Fields::kGarrison, town.garrison);
    readField(Fields::kGarrisonedHero, town.garrisoned_hero);
    readField(Fields::kVisitingHero, town.visiting_hero);
    readField(Fields::kMageGuildLevel, town.mage_guild_level);
    readField(Fields::kUnknown2, town.unknown2);
    readField(Fields::kName, town.name);
    readField(Fields::kRecruitsNonUpgraded, town.recruits_nonupgraded);
    readField(Fields::kRecruitsUpgraded, town.recruits_upgraded);
    readField(Fields::kNumExternalDwellings, town.num_external_dwellings);
    readField(Fields::kNumExternalDwellings2, town.num_external_dwellings2);
    readField(Fields::kUnknown3, town.unknown3);
    readField(Fields::kBuilt, town.built);
    readField(Fields::kReserved1, town.reserved1);
    readField(Fields::kCanBeBuilt, town.can_be_built);
    readField(Fields::kReserved2, town.reserved2);
    readField(Fields::kSpells, town.spells);
    readField(Fields::kBannedSpells, town.banned_spells);
    readField(Fields::kUnknown4, town.unknown4);
    readField(Fields::kUniqueBuildingsProperties, town.unique_buildings_properties);
    return town;
  }

  template<>
  h3svg::TownUniqueBuildingsProperties JsonReader2<h3svg::TownUniqueBuildingsProperties>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::TownUniqueBuildingsProperties>;
    h3svg::TownUniqueBuildingsProperties properties;
    properties.mana_vortex_available = readField<bool>(Fields::kManaVortexAvailable);
    properties.mystic_pond_resource_amount = readBitField<std::uint8_t, 3>(value(), Fields::kMysticPondResourceAmount);
    properties.mystic_pond_resource_type = readBitField<h3svg::ResourceType, 3>(value(), Fields::kMysticPondResourceType);
    properties.unknown = readField<bool>(Fields::kUnknown);
    readField(Fields::kSummonedCreatures, properties.summoned_creatures);
    return properties;
  }
}
