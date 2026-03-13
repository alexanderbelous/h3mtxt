#pragma once

#include <h3mtxt/H3Reader/H3ReaderBase/H3ReaderBase.h>

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>

// API for reading various structures from an *UNCOMPRESSED* .h3c file.
namespace h3m
{
  class H3CReader : public H3ReaderBase
  {
  public:
    // Constructs a H3CReader that will read bytes from the specified istream.
    // \param stream - istream to read bytes from.
    explicit constexpr H3CReader(std::istream& stream) noexcept :
      H3ReaderBase{ stream }
    {}

    CampaignHeader readCampaignHeader() const;

    CampaignScenario readCampaignScenario(CampaignId campaign_id) const;

    CrossoverOptions readCrossoverOptions() const;

    CutScene readCutScene() const;

    StartingBonus readStartingBonus() const;

    template<StartingBonusType T>
    StartingBonusDetails<T> readStartingBonusDetails() const;

    StartingOptions readStartingOptions() const;

    template<StartingOptionsType T>
    StartingOptionsDetails<T> readStartingOptionsDetails() const;
  };

  template<> StartingBonusDetails<StartingBonusType::Spell> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::Creature> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::Building> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::Artifact> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::SpellScroll> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::PrimarySkills> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::SecondarySkill> H3CReader::readStartingBonusDetails() const;

  template<> StartingBonusDetails<StartingBonusType::Resource> H3CReader::readStartingBonusDetails() const;

  template<> StartingOptionsDetails<StartingOptionsType::None> H3CReader::readStartingOptionsDetails() const;

  template<> StartingOptionsDetails<StartingOptionsType::StartingBonus> H3CReader::readStartingOptionsDetails() const;

  template<> StartingOptionsDetails<StartingOptionsType::HeroCrossover> H3CReader::readStartingOptionsDetails() const;

  template<> StartingOptionsDetails<StartingOptionsType::StartingHero> H3CReader::readStartingOptionsDetails() const;
}
