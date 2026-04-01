#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <array>
#include <type_traits>

namespace h3svg
{
  namespace
  {
    using ::h3m::EnumSequence;
    using ::h3m::MakeEnumSequence;

    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetailsAsVariant(const H3SVGReader& reader)
    {
      return reader.readVictoryConditionDetails<T>();
    }

    VictoryCondition::Details readVictoryConditionDetailsVariant(const H3SVGReader& reader,
                                                                 VictoryConditionType victory_condition_type)
    {
      // Type of a pointer to a function that takes const H3SVGReader& and returns VictoryCondition::Details.
      using ReadVictoryConditionDetailsPtr = VictoryCondition::Details(*)(const H3SVGReader& reader);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readVictoryConditionDetailsAsVariant() ordered by VictoryConditionType.
      static constexpr std::array<ReadVictoryConditionDetailsPtr, kNumSpecialVictoryConditions>
      kVictoryConditionDetailsReaders =
        [] <VictoryConditionType... victory_condition_types>
        (EnumSequence<VictoryConditionType, victory_condition_types...> seq)
        consteval
      {
        return std::array<ReadVictoryConditionDetailsPtr, sizeof...(victory_condition_types)>
        {
          &readVictoryConditionDetailsAsVariant<victory_condition_types>...
        };
      }(MakeEnumSequence<VictoryConditionType, kNumSpecialVictoryConditions>{});

      // Edge case for VictoryConditionType::Normal.
      if (victory_condition_type == VictoryConditionType::Normal)
      {
        return readVictoryConditionDetailsAsVariant<VictoryConditionType::Normal>(reader);
      }
      // Otherwise, invoke a function from the generated array.
      return kVictoryConditionDetailsReaders.at(static_cast<std::size_t>(victory_condition_type))(reader);
    }
  }

  SpecialVictoryConditionBase H3SVGReader::readSpecialVictoryConditionBase() const
  {
    return h3m::H3MReader{ stream_ }.readSpecialVictoryConditionBase();
  }

  // The default implementation reuses H3MReader.
  template<VictoryConditionType T>
  VictoryConditionDetails<T> H3SVGReader::readVictoryConditionDetails() const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::VictoryConditionDetails<T>, VictoryConditionDetails<T>>,
                  "h3svg::VictoryConditionDetails<T> must be derived from h3m::VictoryConditionDetails<T>.");
    static_assert(sizeof(VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>),
                  "h3svg::VictoryConditionDetails<T> must have the same size as h3m::VictoryConditionDetails<T>.");
    return { h3m::H3MReader{stream_}.readVictoryConditionDetails<T>() };
  }

  // Explicit instantiations of H3SVGReader::readVictoryConditionDetails()
  // for VictoryConditionTypes that use the default template implementation.
  //
  // Technically, these are redundant because H3SVGReader::readVictoryCondition() will instantiate them anyway.
  // However, I'm not sure how reliable that is: e.g., if the compiler inlines everything in
  // H3SVGReader::readVictoryCondition(), is it guaranteed that these instantiations will still be found
  // by the linker?
  //
  // Safer to explicitly instantiate them.
  template
  VictoryConditionDetails<VictoryConditionType::AccumulateResources> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::UpgradeTown> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::BuildGrail> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::CaptureTown> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::DefeatMonster> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::FlagDwellings> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::FlagMines> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::TransportArtifact> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> H3SVGReader::readVictoryConditionDetails() const;

  template
  VictoryConditionDetails<VictoryConditionType::Normal> H3SVGReader::readVictoryConditionDetails() const;

  template<>
  VictoryConditionDetails<VictoryConditionType::AcquireArtifact> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details{ readSpecialVictoryConditionBase() };
    details.artifact_type = readEnum<ArtifactType8>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details{ readSpecialVictoryConditionBase() };
    details.creature_type = readEnum<CreatureType8>();
    details.count = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatHero> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::DefeatHero> details{ readSpecialVictoryConditionBase() };
    details.hero = readEnum<HeroType>();
    return details;
  }

  VictoryCondition H3SVGReader::readVictoryCondition() const
  {
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    return VictoryCondition{ .details = readVictoryConditionDetailsVariant(*this, victory_condition_type) };
  }
}
