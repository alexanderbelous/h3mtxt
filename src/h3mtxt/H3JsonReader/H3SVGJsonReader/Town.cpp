#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Town.h>

namespace h3json
{
  template<>
  h3svg::Town JsonReader<h3svg::Town>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Town>;
    h3svg::Town town;
    readField(town.id, value, Fields::kId);
    readField(town.owner, value, Fields::kOwner);
    readField(town.built_this_turn, value, Fields::kBuiltThisTurn);
    readField(town.unknown1, value, Fields::kUnknown1);
    readField(town.type, value, Fields::kType);
    readField(town.coordinates, value, Fields::kCoordinates);
    readField(town.generated_boat_x, value, Fields::kGeneratedBoatX);
    readField(town.generated_boat_y, value, Fields::kGeneratedBoatY);
    readField(town.garrison, value, Fields::kGarrison);
    readField(town.garrisoned_hero, value, Fields::kGarrisonedHero);
    readField(town.visiting_hero, value, Fields::kVisitingHero);
    readField(town.mage_guild_level, value, Fields::kMageGuildLevel);
    readField(town.unknown2, value, Fields::kUnknown2);
    readField(town.name, value, Fields::kName);
    readField(town.recruits_nonupgraded, value, Fields::kRecruitsNonUpgraded);
    readField(town.recruits_upgraded, value, Fields::kRecruitsUpgraded);
    readField(town.num_external_dwellings, value, Fields::kNumExternalDwellings);
    readField(town.num_external_dwellings2, value, Fields::kNumExternalDwellings2);
    readField(town.unknown3, value, Fields::kUnknown3);
    readField(town.built, value, Fields::kBuilt);
    readField(town.reserved1, value, Fields::kReserved1);
    readField(town.can_be_built, value, Fields::kCanBeBuilt);
    readField(town.reserved2, value, Fields::kReserved2);
    readField(town.spells, value, Fields::kSpells);
    readField(town.banned_spells, value, Fields::kBannedSpells);
    readField(town.unknown4, value, Fields::kUnknown4);
    readField(town.unique_buildings_properties, value, Fields::kUniqueBuildingsProperties);
    return town;
  }

  template<>
  h3svg::TownUniqueBuildingsProperties
  JsonReader<h3svg::TownUniqueBuildingsProperties>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::TownUniqueBuildingsProperties>;
    h3svg::TownUniqueBuildingsProperties properties;
    properties.mana_vortex_available = readField<bool>(value, Fields::kManaVortexAvailable);
    properties.mystic_pond_resource_amount = readField<std::uint8_t>(value, Fields::kMysticPondResourceAmount);
    properties.mystic_pond_resource_type = readField<h3svg::ResourceType>(value, Fields::kMysticPondResourceType);
    properties.unknown = readField<bool>(value, Fields::kUnknown);
    readField(properties.summoned_creatures, value, Fields::kSummonedCreatures);
    return properties;
  }
}
