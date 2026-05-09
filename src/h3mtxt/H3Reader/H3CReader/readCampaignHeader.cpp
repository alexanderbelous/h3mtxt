#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>

#include <h3mtxt/Campaign/CampaignHeader.h>

#include <stdexcept>

namespace h3m
{
  H3CReader::H3CReader(std::istream& stream, CampaignFormat format):
    H3ReaderBase{ stream },
    format_{ format }
  {
    if (format != CampaignFormat::ArmageddonsBlade && format != CampaignFormat::ShadowOfDeath)
    {
      throw std::invalid_argument("H3CReader: invalid CampaignFormat.");
    }
  }

  CampaignHeader H3CReader::readCampaignHeader() const
  {
    const CampaignFormat format = readEnum<CampaignFormat>();
    return H3CReader{ stream_, format }.readCampaignHeaderWithoutFormat();
  }

  CampaignHeader H3CReader::readCampaignHeaderWithoutFormat() const
  {
    CampaignHeader campaign;
    campaign.format = format_;
    campaign.id = readEnum<CampaignId>();
    campaign.name = readString32();
    campaign.description = readString32();
    campaign.allow_selecting_difficulty = readBool();
    campaign.theme_music = readEnum<CampaignMusic>();
    const std::uint8_t num_regions = countRegions(campaign.id);
    campaign.scenarios.reserve(num_regions);
    for (std::uint8_t i = 0; i < num_regions; ++i)
    {
      campaign.scenarios.push_back(readCampaignScenario(campaign.id));
    }
    return campaign;
  }
}
