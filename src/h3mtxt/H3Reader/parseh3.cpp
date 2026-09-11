#include <h3mtxt/H3Reader/parseh3.h>

#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/H3Reader/H3SVGReader/zstr_patch.h>

namespace h3m
{
  std::variant<Map, Campaign> parseh3(std::istream& stream)
  {
    std::variant<Map, Campaign, h3svg::SavedGame> data = h3mtxt::parseh3(stream);
    switch (data.index())
    {
    case 0:
      return std::move(std::get<h3m::Map>(data));
    case 1:
      return std::move(std::get<h3m::Campaign>(data));
    default:
      throw std::runtime_error("parseh3(): Unknown file format.");
    }
  }
}

namespace h3mtxt
{
  namespace
  {
    // Reads an uncompressed map/campaign/saved game from the input stream.
    std::variant<h3m::Map, h3m::Campaign, h3svg::SavedGame> parseh3Uncompressed(std::istream& stream)
    {
      switch (stream.peek())
      {
      case static_cast<int>(h3m::MapFormat::RestorationOfErathia):
      case static_cast<int>(h3m::MapFormat::ArmageddonsBlade):
      case static_cast<int>(h3m::MapFormat::ShadowOfDeath):
        return h3m::H3MReader{ stream }.readMap();
      case static_cast<int>(h3m::CampaignFormat::RestorationOfErathia):
      case static_cast<int>(h3m::CampaignFormat::ArmageddonsBlade):
      case static_cast<int>(h3m::CampaignFormat::ShadowOfDeath):
      {
        h3m::Campaign campaign{ .header = h3m::H3CReader{ stream }.readCampaignHeader() };
        const std::size_t num_scenarios = countScenarios(campaign.header);
        campaign.maps.reserve(num_scenarios);
        for (std::size_t i = 0; i < num_scenarios; ++i)
        {
          // TODO: add support for the case when the header is compressed but one or more maps are uncompressed.
          campaign.maps.push_back(h3m::H3MReader{ stream }.readMap());
        }
        return campaign;
      }
      case static_cast<int>('H'):
        return h3svg::H3SVGReader{ stream }.readSavedGame();
      default:
        throw std::runtime_error("parseh3(): Unknown file format.");
      }
    }
  }

  std::variant<h3m::Map, h3m::Campaign, h3svg::SavedGame> parseh3(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3(): Empty stream passed.");
    }
    if (stream.peek() == kGzipFirstByte)
    {
      // TODO: decompress only the first Gzip stream. This is needed to support campaigns with
      // compressed headers that contain one or more uncompressed maps.
      h3svg::ZstrIstreamPatched zstr_stream{ stream };
      return parseh3Uncompressed(zstr_stream);
    }
    else
    {
      return parseh3Uncompressed(stream);
    }
  }
}
