#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/FixedLengthString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/CampaignInfo.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::CampaignInfo>::operator()(FieldsWriter& out, const h3svg::CampaignInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::CampaignInfo>;
    out.writeField(Fields::kUnknown1, info.unknown1);
    out.writeField(Fields::kRegionIdx, info.region_idx);
    out.writeField(Fields::kId, info.id);
    out.writeField(Fields::kUnknown2, info.unknown2);
    out.writeField(Fields::kStartingBonusIdx, info.starting_bonus_idx);
    out.writeField(Fields::kFilename, info.filename);
    out.writeField(Fields::kFinishedCampaigns, info.finished_campaigns);
    out.writeField(Fields::kRegions, info.regions);
    out.writeField(Fields::kCrossoverInfo, info.crossover_info);
  }

  template<>
  void JsonObjectWriter<h3svg::CrossoverInfo::UnknownPair>::operator()(
    FieldsWriter& out, const h3svg::CrossoverInfo::UnknownPair& pair) const
  {
    out.writeField("first", pair.first);
    out.writeField("second", pair.second);
  }

  template<>
  void JsonObjectWriter<h3svg::CrossoverInfo>::operator()(FieldsWriter& out, const h3svg::CrossoverInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::CrossoverInfo>;
    out.writeField(Fields::kCrossoverHeroes, info.crossover_heroes);
    out.writeField(Fields::kUnknown, info.unknown);
  }

  template<>
  void JsonObjectWriter<h3svg::RegionInfo>::operator()(FieldsWriter& out,
                                                       const h3svg::RegionInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::RegionInfo>;
    out.writeField(Fields::kIsCompleted, info.is_completed);
    out.writeField(Fields::kDays, info.days);
    out.writeField(Fields::kScore, info.score);
    out.writeField(Fields::kOrder, info.order);
    out.writeField(Fields::kUnknown, info.unknown);
  }
}
