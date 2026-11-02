#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/MapBasicInfo.h>

namespace h3json
{
  template<>
  h3m::MapBasicInfo JsonReader2<h3m::MapBasicInfo>::operator()() const
  {
    using Fields = FieldNames<h3m::MapBasicInfo>;
    h3m::MapBasicInfo basic_info;
    readField(Fields::kIsPlayable, basic_info.is_playable);
    readField(Fields::kMapSize, basic_info.map_size);
    readField(Fields::kHasTwoLevels, basic_info.has_two_levels);
    readField(Fields::kName, basic_info.name);
    readField(Fields::kDescription, basic_info.description);
    readField(Fields::kDifficulty, basic_info.difficulty);
    readField(Fields::kMaxHeroLevel, basic_info.max_hero_level);
    return basic_info;
  }
}
