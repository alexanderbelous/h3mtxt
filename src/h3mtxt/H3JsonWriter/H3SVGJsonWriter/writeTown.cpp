#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Town.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3svg::Town>::operator()(FieldsWriter& out, const h3svg::Town& town) const
  {
    using Fields = h3json::FieldNames<h3svg::Town>;
    out.writeField(Fields::kId, town.id);
    out.writeField(Fields::kOwner, town.owner);
    out.writeField(Fields::kBuiltThisTurn, town.built_this_turn);
    out.writeField(Fields::kUnknown1, town.unknown1);
    out.writeField(Fields::kType, town.type);
    out.writeField(Fields::kCoordinates, town.coordinates);
    out.writeField(Fields::kGeneratedBoatX, town.generated_boat_x);
    out.writeField(Fields::kGeneratedBoatY, town.generated_boat_y);
    out.writeField(Fields::kGarrison, town.garrison);
    out.writeField(Fields::kGarrisonedHero, town.garrisoned_hero);
    out.writeField(Fields::kVisitingHero, town.visiting_hero);
    out.writeField(Fields::kMageGuildLevel, town.mage_guild_level);
    out.writeField(Fields::kUnknown2, town.unknown2);
    out.writeField(Fields::kName, town.name);
    out.writeField(Fields::kRecruitsNonUpgraded, town.recruits_nonupgraded);
    out.writeField(Fields::kRecruitsUpgraded, town.recruits_upgraded);
    out.writeField(Fields::kNumExternalDwellings, town.num_external_dwellings);
    out.writeField(Fields::kNumExternalDwellings2, town.num_external_dwellings2);
    out.writeField(Fields::kUnknown3, town.unknown3);
    out.writeField(Fields::kBuilt, town.built);
    out.writeField(Fields::kReserved1, town.reserved1);
    out.writeField(Fields::kCanBeBuilt, town.can_be_built);
    out.writeField(Fields::kReserved2, town.reserved2);
    out.writeField(Fields::kSpells, town.spells);
    out.writeField(Fields::kBannedSpells, town.banned_spells);
    out.writeField(Fields::kUnknown4, town.unknown4);
    out.writeField(Fields::kUniqueBuildingsProperties, town.unique_buildings_properties);
  }

  template<>
  void JsonObjectWriter<h3svg::TownUniqueBuildingsProperties>::operator()(
    FieldsWriter& out, const h3svg::TownUniqueBuildingsProperties& properties) const
  {
    using Fields = h3json::FieldNames<h3svg::TownUniqueBuildingsProperties>;
    // Written as bool because this bit field can only be 0 or 1.
    out.writeField(Fields::kManaVortexAvailable, static_cast<bool>(properties.mana_vortex_available));
    out.writeField(Fields::kMysticPondResourceAmount, properties.mystic_pond_resource_amount);
    out.writeField(Fields::kMysticPondResourceType, properties.mystic_pond_resource_type);
    // Written as bool because this bit field can only be 0 or 1.
    out.writeField(Fields::kUnknown, static_cast<bool>(properties.unknown));
    out.writeField(Fields::kSummonedCreatureType, properties.summoned_creature_type);
    out.writeField(Fields::kSummonedCreatureCount, properties.summoned_creature_count);
  }
}
