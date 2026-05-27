#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace h3svg
{
  CrossoverInfo H3SVGReader::readCrossoverInfo() const
  {
    CrossoverInfo info;
    // Read crossover heroes.
    {
      const std::uint8_t num_crossover_heroes = readInt<std::uint8_t>();
      info.crossover_heroes.reserve(num_crossover_heroes);
      for (std::size_t i = 0; i < num_crossover_heroes; ++i)
      {
        info.crossover_heroes.push_back(readHero());
      }
    }
    // Read unknown stuff.
    {
      const std::uint16_t num_elements = readInt<std::uint16_t>();
      info.unknown.reserve(num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        CrossoverInfo::UnknownPair pair;
        pair.first = readInt<std::uint16_t>();
        pair.second = readInt<std::uint16_t>();
        info.unknown.push_back(pair);
      }
    }
    return info;
  }

  RegionInfo H3SVGReader::readRegionInfo() const
  {
    RegionInfo info;
    info.is_completed = readBool();
    info.days = readInt<std::uint32_t>();
    info.score = readInt<std::uint32_t>();
    info.order = readInt<std::uint8_t>();
    info.unknown = readInt<std::uint8_t>();
    return info;
  }

  CampaignInfo H3SVGReader::readCampaignInfo() const
  {
    CampaignInfo info;
    // Read 3 bytes (unknown).
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 3>{ info.unknown1 }));
    // Read 1 byte - the index of the current region.
    info.region_idx = readInt<std::uint8_t>();
    // Read 1 byte - ID of the campaign.
    info.id = readEnum<CampaignId>();
    // Read 2 bytes (unknown).
    readBytes(std::as_writable_bytes(std::span<std::uint8_t, 2>{ info.unknown2 }));
    // Read 1 byte - the index of the selected starting bonus.
    info.starting_bonus_idx = readInt<std::uint8_t>();
    // Read the original filename of the .h3c file.
    info.filename = readString32();
    // Read 21 bytes - the flags indicating which standard campaigns have been finished.
    for (Bool& flag : info.finished_campaigns.data)
    {
      flag = readBool();
    }
    // Read info for each region.
    {
      const std::uint8_t num_regions = readInt<std::uint8_t>();
      info.regions.reserve(num_regions);
      for (std::size_t i = 0; i < num_regions; ++i)
      {
        info.regions.push_back(readRegionInfo());
      }
    }
    // Read crossover info.
    {
      const std::uint8_t num_crossover_elements = readInt<std::uint8_t>();
      info.crossover_info.reserve(num_crossover_elements);
      for (std::size_t i = 0; i < num_crossover_elements; ++i)
      {
        info.crossover_info.push_back(readCrossoverInfo());
      }
    }
    return info;
  }
}
