#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const CampaignInfo& campaign_info) const
  {
    writeData(campaign_info.unknown1);
    writeData(campaign_info.region_idx);
    writeData(campaign_info.id);
    writeData(campaign_info.unknown2);
    writeData(campaign_info.starting_bonus_idx);
    writeString32(campaign_info.filename);
    writeData(campaign_info.finished_campaigns);
    writeData(safeCastVectorSize<std::uint8_t>(campaign_info.regions.size()));
    writeSpan(std::span{ campaign_info.regions });
    writeData(safeCastVectorSize<std::uint8_t>(campaign_info.crossover_info.size()));
    writeSpan(std::span{ campaign_info.crossover_info });
  }

  void H3SVGWriter::writeData(const CrossoverInfo& crossover_info) const
  {
    writeData(safeCastVectorSize<std::uint8_t>(crossover_info.crossover_heroes.size()));
    writeSpan(std::span{ crossover_info.crossover_heroes });
    writeData(safeCastVectorSize<std::uint16_t>(crossover_info.unknown.size()));
    for (const CrossoverInfo::UnknownPair& unknown_pair : crossover_info.unknown)
    {
      writeData(unknown_pair.first);
      writeData(unknown_pair.second);
    }
  }

  void H3SVGWriter::writeData(const RegionInfo& region_info) const
  {
    writeData(region_info.is_completed);
    writeData(region_info.days);
    writeData(region_info.score);
    writeData(region_info.order);
    writeData(region_info.unknown);
  }
}
