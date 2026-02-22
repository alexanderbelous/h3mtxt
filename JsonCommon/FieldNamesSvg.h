#pragma once

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string_view>

namespace h3m
{
  template<>
  struct FieldNames<PlayerSpecsSvg>
  {
    static inline constexpr std::string_view kCanBeHuman = "can_be_human";
    static inline constexpr std::string_view kCanBeComputer = "can_be_computer";
    static inline constexpr std::string_view kBehavior = "behavior";
    static inline constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static inline constexpr std::string_view kUnknown = "unknown";
    static inline constexpr std::string_view kStartingHero = "starting_hero";
  };

  template<>
  struct FieldNames<SavedGame>
  {
    static inline constexpr std::string_view kReserved1 = "reserved1";
    static inline constexpr std::string_view kVersionMajor = "version_major";
    static inline constexpr std::string_view kVersionMinor = "version_minor";
    static inline constexpr std::string_view kReserved2 = "reserved2";
    static inline constexpr std::string_view kFormat = "format";
    static inline constexpr std::string_view kBasicInfo = "basic_info";
    static inline constexpr std::string_view kPlayers = "players";
    static inline constexpr std::string_view kVictoryCondition = "victory_condition";
    static inline constexpr std::string_view kLossCondition = "loss_condition";
  };
}
