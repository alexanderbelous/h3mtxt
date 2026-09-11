#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Town.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Town& town) const
  {
    writeData(town.id);
    writeData(town.owner);
    writeData(town.built_this_turn);
    writeData(town.unknown1);
    writeData(town.type);
    writeData(town.coordinates);
    writeData(town.generated_boat_x);
    writeData(town.generated_boat_y);
    writeData(town.garrison);
    writeData(town.garrisoned_hero);
    writeData(town.visiting_hero);
    writeData(town.mage_guild_level);
    writeData(town.unknown2);
    writeString16(town.name);
    writeData(town.recruits_nonupgraded);
    writeData(town.recruits_upgraded);
    writeData(town.num_external_dwellings);
    writeData(town.num_external_dwellings2);
    writeData(town.unknown3);
    writeData(town.built);
    writeData(town.reserved1);
    writeData(town.can_be_built);
    writeData(town.reserved2);
    writeData(town.spells);
    writeData(town.banned_spells);
    writeData(town.unknown4);
    writeData(town.unique_buildings_properties);
  }

  void H3SVGWriter::writeData(const TownUniqueBuildingsProperties& properties) const
  {
    static constexpr std::uint8_t kMaskManaVortexAvailable = 0b1u;
    static constexpr std::uint8_t kMaskMysticPondResourceAmount = 0b111u;
    static constexpr std::uint8_t kMaskMysticPondResourceType = 0b111u;
    static constexpr std::uint8_t kMaskUnknown = 0b1u;

    const std::uint8_t packed_data =
      ((static_cast<std::uint8_t>(properties.mana_vortex_available) & kMaskManaVortexAvailable) << 0) |
      ((static_cast<std::uint8_t>(properties.mystic_pond_resource_amount) & kMaskMysticPondResourceAmount) << 1) |
      ((static_cast<std::uint8_t>(properties.mystic_pond_resource_type) & kMaskMysticPondResourceType) << 4) |
      ((static_cast<std::uint8_t>(properties.unknown) & kMaskUnknown) << 7);

    writeData(packed_data);
    writeData(properties.summoned_creatures);
  }
}
