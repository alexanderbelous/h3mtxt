#include <h3mtxt/H3Writer/writeh3c.h>
#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/H3Writer/writeh3m.h>
#include <h3mtxt/Campaign/Campaign.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <sstream>
#include <stdexcept>
#include <vector>

namespace h3m::H3Writer_NS
{
  namespace
  {
    void checkCampaign(const Campaign& campaign)
    {
      if (campaign.header.scenarios.size() != countMapRegions(campaign.header.id))
      {
        throw std::runtime_error("writeh3c(): wrong number of scenarios.");
      }
      const std::size_t num_existing_scenarios = countScenarios(campaign.header);
      if (campaign.maps.size() != num_existing_scenarios)
      {
        throw std::runtime_error("writeh3c(): wrong number of maps.");
      }
    }

    std::string compressMap(const h3m::Map& map)
    {
      std::stringstream stream;
      writeh3m(stream, map, true);
      return std::move(stream).str();
    }

    std::vector<std::string> compressMaps(const std::vector<h3m::Map>& maps)
    {
      std::vector<std::string> compressed_maps;
      compressed_maps.reserve(maps.size());
      for (const h3m::Map& map : maps)
      {
        compressed_maps.push_back(compressMap(map));
      }
      return compressed_maps;
    }
  }

  void writeh3c(std::ostream& stream, const Campaign& campaign)
  {
    checkCampaign(campaign);
    // Compress each map.
    const std::vector<std::string> compressed_maps = compressMaps(campaign.maps);
    std::size_t map_idx = 0;
    // Write the header as a gzip stream.
    {
      zstr::ostream zstr_stream(stream);
      writeData(zstr_stream, campaign.header.format);
      writeData(zstr_stream, campaign.header.id);
      writeData(zstr_stream, campaign.header.name);
      writeData(zstr_stream, campaign.header.description);
      writeData(zstr_stream, campaign.header.allow_selecting_difficulty);
      writeData(zstr_stream, campaign.header.theme_music);
      for (const CampaignScenario& scenario : campaign.header.scenarios)
      {
        std::uint32_t compressed_map_size = 0;
        if (!scenario.map_filename.empty())
        {
          // 4GB ought to be enough for any mapmaker.
          compressed_map_size = static_cast<std::uint32_t>(compressed_maps.at(map_idx).size());
          ++map_idx;
        }
        writeCampaignScenario(zstr_stream, scenario, campaign.header.id, compressed_map_size);
      }
    }
    // Append the compressed maps.
    for (const std::string& compressed_map : compressed_maps)
    {
      stream.write(compressed_map.data(), compressed_map.size());
    }
  }
}
