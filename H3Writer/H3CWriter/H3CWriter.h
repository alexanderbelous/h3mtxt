#pragma once

#include <h3mtxt/H3Writer/H3WriterBase/H3WriterBase.h>
#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>

#include <optional>
#include <string>

namespace h3m
{
  // API for writing various structures into an *UNCOMPRESSED* .h3c file.
  class H3CWriter : public h3mtxt::H3WriterBase
  {
  public:
    // Constructs H3CWriter that will append data to the specified stream.
    // \param stream - stream to append data to.
    explicit constexpr H3CWriter(std::ostream& stream) noexcept :
      H3WriterBase{ stream }
    {}

    // Reintroduce writeData() from the base class, so that the new overloads in H3CWriter don't hide it.
    using H3WriterBase::writeData;

    // Forbid writing Campaign via H3CWriter.
    // .h3c is weird - it's actually a sequence of concatenated gzip streams:
    // * The first stream contains everything in h3m::Campaign except the maps
    // * Each next stream contains a single h3m::Map from Campaign::maps.
    //
    // During decompression gzip file format treats such concatenated streams
    // as if they were originally one file.
    void writeData(const Campaign& campaign) const = delete;

    // Deleted because it's risk-prone: each CampaignScenario should specify
    // the size of the map in bytes, but maps are stored separately in Campaign::maps.
    void writeData(const CampaignHeader& header) const = delete;

    void writeData(const CrossoverOptions& options) const;

    void writeData(const CutScene& cutscene) const;

    void writeData(const StartingBonus& bonus) const;

    template<StartingBonusType T>
    void writeData(const StartingBonusDetails<T>& details) const;

    void writeData(const StartingOptions& options) const;

    template<StartingOptionsType T>
    void writeData(const StartingOptionsDetails<T>& details) const;

    void writeCampaignScenario(const CampaignScenario& scenario,
                               CampaignId campaign_id,
                               std::uint32_t map_file_size) const;

    // In H3C strings are always written as length-prefixed strings with length being serialized as
    // a 32-bit integer, so we can just overload writeData() for std::string.
    void writeData(const std::string& value) const;

    // Appends std::optional to the binary stream.
    template<class T>
    void writeData(const std::optional<T>& value) const;
  };

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Spell>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Creature>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Building>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Artifact>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::SpellScroll>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::PrimarySkills>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::SecondarySkill>& details) const;

  template<>
  void H3CWriter::writeData(const StartingBonusDetails<StartingBonusType::Resource>& details) const;

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::None>& details) const;

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::StartingBonus>& details) const;

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::HeroCrossover>& details) const;

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::StartingHero>& details) const;

  template<class T>
  void H3CWriter::writeData(const std::optional<T>& value) const
  {
    writeData(static_cast<Bool>(value.has_value()));
    if (value.has_value())
    {
      writeData(*value);
    }
  }
}
