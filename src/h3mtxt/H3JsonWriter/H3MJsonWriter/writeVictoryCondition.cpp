#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/VictoryCondition.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3m::SpecialVictoryConditionBase;
using ::h3m::VictoryConditionDetails;
using ::h3m::VictoryConditionType;

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<SpecialVictoryConditionBase>::operator()(FieldsWriter& out,
                                                                 const SpecialVictoryConditionBase& value) const
  {
    using Fields = h3json::FieldNames<SpecialVictoryConditionBase>;
    out.writeField(Fields::kAllowNormalWin, value.allow_normal_win);
    out.writeField(Fields::kAppliesToComputer, value.applies_to_computer);
  }

  template<VictoryConditionType T>
  void JsonObjectWriter<VictoryConditionDetails<T>>::operator()(FieldsWriter& out,
                                                                const VictoryConditionDetails<T>& details) const
  {
    if constexpr (T == VictoryConditionType::Normal)
    {
      // No fields.
    }
    else
    {
      JsonObjectWriter<SpecialVictoryConditionBase>{}(out, details);
      if constexpr (T == VictoryConditionType::AcquireArtifact)
      {
        out.writeField("artifact_type", details.artifact_type);
      }
      else if constexpr (T == VictoryConditionType::AccumulateCreatures)
      {
        out.writeField("creatures", details.creatures);
      }
      else if constexpr (T == VictoryConditionType::AccumulateResources)
      {
        out.writeField("resources", details.resources);
      }
      else if constexpr (T == VictoryConditionType::UpgradeTown)
      {
        out.writeField("coordinates", details.coordinates);
        out.writeField("hall_level", details.hall_level);
        out.writeField("castle_level", details.castle_level);
      }
      else if constexpr (T == VictoryConditionType::BuildGrail ||
                         T == VictoryConditionType::DefeatHero ||
                         T == VictoryConditionType::CaptureTown ||
                         T == VictoryConditionType::DefeatMonster)
      {
        out.writeField("coordinates", details.coordinates);
      }
      else if constexpr (T == VictoryConditionType::FlagDwellings ||
                         T == VictoryConditionType::FlagMines ||
                         T == VictoryConditionType::DefeatAllMonsters)
      {
        // No fields other than the ones inherited from SpecialVictoryConditionBase.
      }
      else if constexpr (T == VictoryConditionType::TransportArtifact)
      {
        out.writeField("artifact_type", details.artifact_type);
        // details.artifact_type is not an enum (it's std::uint8_t), so the comment is not printed automatically.
        if (std::string_view enum_str = EnumCommentGetter{}(static_cast<h3m::ArtifactType>(details.artifact_type));
            !enum_str.empty())
        {
          out.writeComment(enum_str, false);
        }
        out.writeField("destination", details.destination);
      }
      else if constexpr (T == VictoryConditionType::SurviveBeyondATimeLimit)
      {
        out.writeField("days", details.days);
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
    }
  }

  template<>
  void JsonObjectWriter<h3m::VictoryCondition>::operator()(FieldsWriter& out, const h3m::VictoryCondition& value) const
  {
    using Fields = h3json::FieldNames<h3m::VictoryCondition>;
    out.writeField(Fields::kType, value.type());
    if (value.type() != VictoryConditionType::Normal)
    {
      std::visit([&out] <VictoryConditionType T> (const VictoryConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 value.details);
    }
  }
}
