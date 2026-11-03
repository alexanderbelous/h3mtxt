#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace h3json
{
  template<>
  h3svg::CampaignInfo JsonReader2<h3svg::CampaignInfo>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::CampaignInfo>;
    h3svg::CampaignInfo info;
    readField(Fields::kUnknown1, info.unknown1);
    readField(Fields::kIsCheater, info.is_cheater);
    readField(Fields::kUnknown2, info.unknown2);
    readField(Fields::kRegionIdx, info.region_idx);
    readField(Fields::kId, info.id);
    readField(Fields::kUnknown3, info.unknown3);
    readField(Fields::kStartingBonusIdx, info.starting_bonus_idx);
    readField(Fields::kFilename, info.filename);
    readField(Fields::kFinishedCampaigns, info.finished_campaigns);
    readField(Fields::kRegions, info.regions);
    readField(Fields::kCrossoverInfo, info.crossover_info);
    return info;    
  }

  // TODO: add a declaration to H3SVGJsonReader.h (requires unnesting CrossoverInfo::UnknownPair).
  template<>
  h3svg::CrossoverInfo::UnknownPair JsonReader2<h3svg::CrossoverInfo::UnknownPair>::operator()() const
  {
    h3svg::CrossoverInfo::UnknownPair pair;
    readField("first", pair.first);
    readField("second", pair.second);
    return pair;
  }

  template<>
  h3svg::CrossoverInfo JsonReader2<h3svg::CrossoverInfo>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::CrossoverInfo>;
    h3svg::CrossoverInfo info;
    readField(Fields::kCrossoverHeroes, info.crossover_heroes);
    readField(Fields::kUnknown, info.unknown);
    return info;
  }

  template<>
  h3svg::RegionInfo JsonReader2<h3svg::RegionInfo>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::RegionInfo>;
    h3svg::RegionInfo info;
    readField(Fields::kIsCompleted, info.is_completed);
    readField(Fields::kDays, info.days);
    readField(Fields::kScore, info.score);
    readField(Fields::kOrder, info.order);
    readField(Fields::kUnknown, info.unknown);
    return info;
  }
}
