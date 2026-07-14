#pragma once

#include <h3mtxt/H3Writer/H3WriterBase/H3WriterBase.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <optional>
#include <string>

namespace h3svg
{
  // API for writing various structures into an *UNCOMPRESSED* H3SVG file.
  class H3SVGWriter : public h3mtxt::H3WriterBase
  {
  public:
    // Constructs H3SVGWriter that will append data to the specified stream.
    // \param stream - stream to append data to.
    // \param map_format - the expected format of the map. Currently, only
    //        MapFormat::ArmageddonsBlade and MapFormat::ShadowOfDeath are supported.
    // \throw std::invalid_argument if map_format is not supported.
    explicit H3SVGWriter(std::ostream& stream,
                         MapFormat map_format = MapFormat::ShadowOfDeath);

    // \return MapFormat that was passed to the constructor.
    constexpr MapFormat format() const noexcept;

    // Reintroduce writeData() from the base class, so that the new overloads in H3SVGWriter don't hide it.
    using H3WriterBase::writeData;

    void writeData(const ArtifactMerchants& value) const;

    void writeData(const CreatureBank& value) const;

    void writeData(const Coordinates& value) const;

    void writeData(const CustomHero& value) const;

    void writeData(const Date& value) const;

    template<std::size_t N>
    void writeData(const FixedLengthString<N>& str) const;

    void writeData(const Guardians& guardians) const;

    void writeData(const Hero& hero) const;

    void writeData(const HeroArtifacts& value) const;

    void writeData(const LossCondition& loss_condition) const;

    template<LossConditionType T>
    void writeData(const LossConditionDetails<T>& details) const;

    void writeData(const MapBasicInfo& value) const;

    void writeData(const ObjectTemplate& value) const;

    void writeData(const Object& object) const;

    void writeData(const ObjectExits& exits) const;

    void writeData(const ObjectPropertiesTables& value) const;

    void writeData(const Player& value) const;

    void writeData(const PlayerSpecs& value) const;

    void writeData(const Quest& quest) const;

    template<QuestType T>
    void writeData(const QuestDetails<T>& details) const;

    void writeData(const ReplayEvent& event) const;

    void writeData(const Reward& reward) const;

    template<RewardType T>
    void writeData(const RewardDetails<T>& details) const;

    void writeData(const Rumor& value) const;

    // Writes the given saved game into the underlying stream.
    //
    // FYI: this function always uses the format specified in SavedGame::format, even if it differs
    // from the MapFormat that *this was constructed with. For example,
    // if saved_game.format == MapFormat::ArmageddonsBlade, then
    //   H3SVGWriter{ stream, MapFormat::ShadowOfDeath }.writeData(saved_game);
    // will still write it as a saved game for "Armageddon's Blade".
    //
    // \param saved_game - input SavedGame.
    void writeData(const SavedGame& saved_game) const;

    void writeData(const ScenarioStartingInfo& starting_info) const;

    void writeData(const SecondarySkill& secondary_skill) const;

    void writeData(const SpriteTilesBitmask& value) const;

    void writeData(const StartingHero& value) const;

    void writeData(const Teams& teams) const;

    void writeData(const Tile& value) const;

    void writeData(const TileVisibility& value) const;

    void writeData(const TimedEvent& event) const;

    void writeData(const Town& town) const;

    void writeData(const TownEvent& event) const;

    void writeData(const University& university) const;

    void writeData(const VictoryCondition& victory_condition) const;

    // Appends an array of elements to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    //
    // The function does NOT write the length of the array to the binary stream - it is the
    // responsibility of the user to do that (if needed at all).
    template<class T>
    void writeSpan(std::span<const T> values) const;

    // Appends a fixed-size array to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    template<class T, std::size_t N>
    void writeData(const std::array<T, N>& value) const;

    // Appends an h3m::EnumIndexedArray to the binary stream.
    //
    // This overload hides a similar function from H3WriterBase - this is intentional, so that we
    // can extend the set of types T that are supported.
    template<class Enum, class T, std::size_t NumElements>
    void writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const;

    // Appends std::optional to the binary stream.
    template<class T>
    void writeData(const std::optional<T>& value) const;

  private:
    void writeEventBase(const EventBase& event) const;

    MapFormat map_format_;
  };

  constexpr MapFormat H3SVGWriter::format() const noexcept
  {
    return map_format_;
  }

  template<> void H3SVGWriter::writeData(const LossConditionDetails<LossConditionType::LoseTown>& details) const;

  template<> void H3SVGWriter::writeData(const LossConditionDetails<LossConditionType::LoseHero>& details) const;

  template<> void H3SVGWriter::writeData(const LossConditionDetails<LossConditionType::TimeExpires>& details) const;

  template<> void H3SVGWriter::writeData(const LossConditionDetails<LossConditionType::Normal>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::None>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::Level>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::PrimarySkills>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::DefeatHero>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::DefeatMonster>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::Artifacts>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::Creatures>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::Resources>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::BeHero>& details) const;

  template<> void H3SVGWriter::writeData(const QuestDetails<QuestType::BePlayer>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::None>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Experience>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::SpellPoints>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Morale>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Luck>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Resource>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::PrimarySkill>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::SecondarySkill>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Artifact>& details) const;

  template<> void H3SVGWriter::writeData(const RewardDetails<RewardType::Creatures>& details) const;

  template<class T>
  void H3SVGWriter::writeSpan(std::span<const T> values) const
  {
    if constexpr ((std::is_integral_v<std::remove_cvref_t<T>> && !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                  std::is_enum_v<std::remove_cvref_t<T>>)
    {
      H3WriterBase::writeSpan(values);
    }
    else
    {
      for (const T& element : values)
      {
        writeData(element);
      }
    }
  }

  template<class T, std::size_t N>
  void H3SVGWriter::writeData(const std::array<T, N>& value) const
  {
    writeSpan(std::span<const T>{value});
  }

  template<class Enum, class T, std::size_t NumElements>
  void H3SVGWriter::writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const
  {
    writeData(enum_indexed_array.data);
  }

  template<class T>
  void H3SVGWriter::writeData(const std::optional<T>& value) const
  {
    writeData(static_cast<Bool>(value.has_value()));
    if (value.has_value())
    {
      writeData(*value);
    }
  }
}
