#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace h3json
{
  template<>
  h3svg::CampaignInfo JsonReader<h3svg::CampaignInfo>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::CampaignInfo>;
    h3svg::CampaignInfo info;
    readField(info.unknown1, value, Fields::kUnknown1);
    readField(info.region_idx, value, Fields::kRegionIdx);
    readField(info.id, value, Fields::kId);
    readField(info.unknown2, value, Fields::kUnknown2);
    readField(info.starting_bonus_idx, value, Fields::kStartingBonusIdx);
    readField(info.filename, value, Fields::kFilename);
    readField(info.finished_campaigns, value, Fields::kFinishedCampaigns);
    readField(info.regions, value, Fields::kRegions);
    readField(info.crossover_info, value, Fields::kCrossoverInfo);
    return info;    
  }

  // TODO: add a declaration to H3SVGJsonReader.h (requires unnesting CrossoverInfo::UnknownPair).
  template<>
  h3svg::CrossoverInfo::UnknownPair
  JsonReader<h3svg::CrossoverInfo::UnknownPair>::operator()(const Json::Value& value) const
  {
    h3svg::CrossoverInfo::UnknownPair pair;
    readField(pair.first, value, "first");
    readField(pair.second, value, "second");
    return pair;
  }

  template<>
  h3svg::CrossoverInfo JsonReader<h3svg::CrossoverInfo>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::CrossoverInfo>;
    h3svg::CrossoverInfo info;
    readField(info.crossover_heroes, value, Fields::kCrossoverHeroes);
    readField(info.unknown, value, Fields::kUnknown);
    return info;
  }

  template<>
  h3svg::RegionInfo JsonReader<h3svg::RegionInfo>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::RegionInfo>;
    h3svg::RegionInfo info;
    readField(info.is_completed, value, Fields::kIsCompleted);
    readField(info.days, value, Fields::kDays);
    readField(info.score, value, Fields::kScore);
    readField(info.order, value, Fields::kOrder);
    readField(info.unknown, value, Fields::kUnknown);
    return info;
  }
}
