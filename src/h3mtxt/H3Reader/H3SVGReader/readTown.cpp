#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Town.h>

namespace h3svg
{
  Town H3SVGReader::readTown() const
  {
    Town town;
    town.id = readInt<std::uint8_t>();
    town.owner = readEnum<PlayerColor>();
    town.built_this_turn = readBool();
    town.unknown1 = readInt<std::uint8_t>();
    town.type = readEnum<TownType>();
    town.coordinates = readCoordinates();
    town.generated_boat_x = readInt<std::uint8_t>();
    town.generated_boat_y = readInt<std::uint8_t>();
    town.garrison = readTroops();
    town.garrisoned_hero = readEnum<HeroType>();
    town.visiting_hero = readEnum<HeroType>();
    town.mage_guild_level = readInt<std::uint8_t>();
    town.unknown2 = readInt<std::uint8_t>();
    town.name = readString16();
    for (std::uint16_t& count : town.recruits_nonupgraded)
    {
      count = readInt<std::uint16_t>();
    }
    for (std::uint16_t& count : town.recruits_upgraded)
    {
      count = readInt<std::uint16_t>();
    }
    for (std::uint32_t& count : town.num_external_dwellings)
    {
      count = readInt<std::uint32_t>();
    }
    for (std::uint32_t& count : town.num_external_dwellings2)
    {
      count = readInt<std::uint32_t>();
    }
    town.unknown3 = readByteArray<13>();
    town.built = readEnumBitmask<TownBuildingTypeH3SVG, 6>();
    town.reserved1 = readReservedData<2>();
    town.can_be_built = readEnumBitmask<TownBuildingTypeH3SVG, 6>();
    town.reserved2 = readReservedData<2>();
    for (std::array<SpellType32, 6>& mage_guild_level_slots : town.spells)
    {
      for (SpellType32& spell : mage_guild_level_slots)
      {
        spell = readEnum<SpellType32>();
      }
    }
    town.banned_spells = readEnumBitmask<SpellType, 9>();
    town.unknown4 = readByteArray<61>();
    town.unique_buildings_properties = readTownUniqueBuildingsProperties();
    return town;
  }

  TownUniqueBuildingsProperties H3SVGReader::readTownUniqueBuildingsProperties() const
  {
    TownUniqueBuildingsProperties properties;
    {
      const std::uint8_t packed_data = readInt<std::uint8_t>();
      properties.mana_vortex_available = static_cast<Bool>(packed_data & 1);
      properties.mystic_pond_resource_amount = static_cast<std::uint8_t>((packed_data >> 1) & 0b111);
      properties.mystic_pond_resource_type = static_cast<ResourceType>((packed_data >> 4) & 0b111);
      properties.unknown = static_cast<Bool>(packed_data >> 7);
    }
    properties.summoned_creature_type = readEnum<CreatureType32>();
    properties.summoned_creature_count = readInt<std::int16_t>();
    return properties;
  }
}
