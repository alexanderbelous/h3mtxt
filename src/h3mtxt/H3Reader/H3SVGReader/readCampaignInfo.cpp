#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace h3svg
{
  RegionInfo H3SVGReader::readRegionInfo() const
  {
    RegionInfo info;
    info.is_completed = readBool();
    info.num_days = readInt<std::uint32_t>();
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 6>{ info.unknown }));
    return info;
  }

  CampaignInfo H3SVGReader::readCampaignInfo() const
  {
    CampaignInfo info;
    // Read 3 bytes (unknown).
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 3>{ info.unknown1 }));
    // Read 1 byte - the index of the current region.
    info.region_idx = readInt<std::uint8_t>();
    // Read 3 bytes (unknown).
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 3>{ info.unknown2 }));
    // Read 1 byte - the index of the selected starting bonus.
    info.starting_bonus_idx = readInt<std::uint8_t>();
    // Read the original filename of the .h3c file.
    info.filename = readString32();
    // Read 21 bytes (unknown).
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 21>{ info.unknown3 }));
    // Read info for each region.
    {
      const std::uint8_t num_regions = readInt<std::uint8_t>();
      info.regions.reserve(num_regions);
      for (std::size_t i = 0; i < num_regions; ++i)
      {
        info.regions.push_back(readRegionInfo());
      }
    }
    // Read 1 byte (unknown).
    info.unknown4 = readInt<std::uint8_t>();
    return info;
  }
}
