#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3m::H3JsonReader_NS
{
  MapBasicInfo JsonReader<MapBasicInfo>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<MapBasicInfo>;
    MapBasicInfo basic_info;
    readField(basic_info.is_playable, value, Fields::kIsPlayable);
    readField(basic_info.map_size, value, Fields::kMapSize);
    readField(basic_info.has_two_levels, value, Fields::kHasTwoLevels);
    readField(basic_info.name, value, Fields::kName);
    readField(basic_info.description, value, Fields::kDescription);
    readField(basic_info.difficulty, value, Fields::kDifficulty);
    readField(basic_info.max_hero_level, value, Fields::kMaxHeroLevel);
    return basic_info;
  }
}
