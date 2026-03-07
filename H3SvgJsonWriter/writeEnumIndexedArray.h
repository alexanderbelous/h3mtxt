#pragma once

#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/SavedGame/EnumIndexedArray.h>
#include <h3mtxt/Medea/Medea.h>

#include <type_traits>

namespace Medea_NS
{
  // TODO: merge these full specializations into a single partial specialization for EnumIndexedArray.
  template<>
  struct JsonObjectWriter<h3svg::EnumIndexedArray<h3m::ArtifactType, h3m::Bool, 144>>
  {
    void operator()(FieldsWriter& out,
                    const h3svg::EnumIndexedArray<h3m::ArtifactType, h3m::Bool, 144>& boolmask) const
    {
      // Reuse the names of fields for ArtifactsBitmask.
      constexpr const std::array<std::string_view, 144>& kFieldsNames = h3m::FieldNames<h3m::ArtifactsBitmask>::kNames;

      for (std::size_t i = 0; i < boolmask.data.size(); ++i)
      {
        out.writeField(kFieldsNames[i], boolmask.data[i]);
      }
    }
  };

  template<>
  struct JsonObjectWriter<h3svg::EnumIndexedArray<h3m::SecondarySkillType, h3m::Bool, 28>>
  {
    void operator()(FieldsWriter& out,
                    const h3svg::EnumIndexedArray<h3m::SecondarySkillType, h3m::Bool, 28>& boolmask) const
    {
      // Reuse the names of fields for SecondarySkillsBitmask.
      constexpr std::span<const std::string_view, 32> kFieldsNames =
        h3m::FieldNames<h3m::SecondarySkillsBitmask>::kNames;

      for (std::size_t i = 0; i < boolmask.data.size(); ++i)
      {
        out.writeField(kFieldsNames[i], boolmask.data[i]);
      }
    }
  };

  // Partial specialization for h3m::EnumIndexedArray<h3m::PlayerColor, T, NumElements>
  template<class T, std::size_t NumElements>
  struct JsonObjectWriter<h3svg::EnumIndexedArray<h3m::PlayerColor, T, NumElements>>
  {
    void operator()(FieldsWriter& out,
                    const h3svg::EnumIndexedArray<h3m::PlayerColor, T, NumElements>& enum_indexed_array) const
    {
      // Reuse the names of fields for PlayersBitmask.
      constexpr const std::array<std::string_view, h3m::kMaxPlayers>& kFieldsNames =
        h3m::FieldNames<h3m::PlayersBitmask>::kNames;

      for (std::size_t player_idx = 0; player_idx < enum_indexed_array.data.size(); ++player_idx)
      {
        const T& element = enum_indexed_array.data[player_idx];
        out.writeField(kFieldsNames[player_idx], element);
        if constexpr (std::is_enum_v<T>)
        {
          if (std::string_view enum_str = getEnumString(element); !enum_str.empty())
          {
            out.writeComment(enum_str, false);
          }
        }
      }
    }
  };
}
