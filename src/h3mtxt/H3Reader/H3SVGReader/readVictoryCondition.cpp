#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <type_traits>

namespace h3svg
{
  namespace
  {
    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetailsAsVariant(const H3SVGReader& reader)
    {
      return reader.readVictoryConditionDetails<T>();
    }

    template<VictoryConditionType T>
    using VictoryConditionDetailsReaderTemplateAlias =
      SwitchStatement_NS::StaticConstant<&readVictoryConditionDetailsAsVariant<T>>;

    VictoryCondition::Details readVictoryConditionDetailsVariant(const H3SVGReader& reader,
                                                                 VictoryConditionType victory_condition_type)
    {
      static constexpr auto switch_statement =
        SwitchStatement_NS::generateSwitchStatement<VictoryConditionType,
                                                    h3m::kNumSpecialVictoryConditions,
                                                    VictoryConditionDetailsReaderTemplateAlias>();
      // Edge case for VictoryConditionType::Normal.
      if (victory_condition_type == VictoryConditionType::Normal)
      {
        return readVictoryConditionDetailsAsVariant<VictoryConditionType::Normal>(reader);
      }
      // Otherwise, execute the generated switch statement.
      return switch_statement(victory_condition_type, reader);
    }
  }

  SpecialVictoryConditionBase H3SVGReader::readSpecialVictoryConditionBase() const
  {
    return h3m::H3MReader{ stream_ }.readSpecialVictoryConditionBase();
  }

  template<VictoryConditionType T>
  VictoryConditionDetails<T> H3SVGReader::readVictoryConditionDetails() const
  {
    if constexpr (std::is_base_of_v<h3m::VictoryConditionDetails<T>, VictoryConditionDetails<T>> &&
                  sizeof(VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>))
    {
      // Reuse H3MReader.
      return VictoryConditionDetails<T>{ h3m::H3MReader{stream_}.readVictoryConditionDetails<T>() };
    }
    else
    {
      VictoryConditionDetails<T> details{ readSpecialVictoryConditionBase() };
      if constexpr (T == VictoryConditionType::AcquireArtifact)
      {
        details.artifact_type = readEnum<ArtifactType8>();
      }
      else if constexpr (T == VictoryConditionType::AccumulateCreatures)
      {
        details.creatures = readTypedQuantity<CreatureType8, std::int32_t>();
      }
      else if constexpr (T == VictoryConditionType::DefeatHero)
      {
        details.hero = readEnum<HeroType>();
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
      return details;
    }
  }

  VictoryCondition H3SVGReader::readVictoryCondition() const
  {
    // FYI: the definition of this function implicitly instantiates readVictoryConditionDetails<T>()
    // for all valid VictoryConditionTypes.
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    return VictoryCondition{ .details = readVictoryConditionDetailsVariant(*this, victory_condition_type) };
  }
}
