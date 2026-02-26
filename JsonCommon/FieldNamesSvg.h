#pragma once

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string_view>

namespace h3m
{
  template<>
  struct FieldNames<Coordinates>
  {
    static inline constexpr std::string_view kX = "x";
    static inline constexpr std::string_view kY = "y";
    static inline constexpr std::string_view kZ = "z";
  };

  template<>
  struct FieldNames<PlayerSpecsSvg>
  {
    static inline constexpr std::string_view kCanBeHuman = "can_be_human";
    static inline constexpr std::string_view kCanBeComputer = "can_be_computer";
    static inline constexpr std::string_view kBehavior = "behavior";
    static inline constexpr std::string_view kAllowedAlignments = "allowed_alignments";
    static inline constexpr std::string_view kAllowRandomAlignment = "allow_random_alignment";
    static inline constexpr std::string_view kGeneratedHeroCoordinates = "generated_hero_coordinates";
    static inline constexpr std::string_view kStartingHero = "starting_hero";
  };

  template<>
  struct FieldNames<RumorSvg>
  {
    static inline constexpr std::string_view kText = "text";
    static inline constexpr std::string_view kUnknown = "unknown";
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
    static inline constexpr std::string_view kTeams = "teams";
    static inline constexpr std::string_view kCustomHeroes = "custom_heroes";
    static inline constexpr std::string_view kUnknown1 = "unknown1";
    static inline constexpr std::string_view kUnknown2 = "unknown2";
    static inline constexpr std::string_view kMapFilename = "map_filename";
    static inline constexpr std::string_view kMapDirectory = "map_directory";
    static inline constexpr std::string_view kUnknown3 = "unknown3";
    static inline constexpr std::string_view kOriginalFilename = "original_filename";
    static inline constexpr std::string_view kUnknown4 = "unknown4";
    static inline constexpr std::string_view kDisabledArtifacts = "disabled_artifacts";
    static inline constexpr std::string_view kArtifactsBitmaskUnknown = "artifacts_bitmask_unknown";
    static inline constexpr std::string_view kDisabledSkills = "disabled_skills";
    static inline constexpr std::string_view kCurrentRumor = "current_rumor";
    static inline constexpr std::string_view kUnknown5 = "unknown5";
    static inline constexpr std::string_view kRumors = "rumors";
    static inline constexpr std::string_view kUnknown6 = "unknown6";
    static inline constexpr std::string_view kTiles = "tiles";
  };

  template<>
  struct FieldNames<TileSvg>
  {
    static inline constexpr std::string_view kTerrainType = "terrain_type";
    static inline constexpr std::string_view kTerrainSprite = "terrain_sprite";
    static inline constexpr std::string_view kRiverType = "river_type";
    static inline constexpr std::string_view kRiverSprite = "river_sprite";
    static inline constexpr std::string_view kRoadType = "road_type";
    static inline constexpr std::string_view kRoadSprite = "road_sprite";
    static inline constexpr std::string_view kFlags1 = "flags1";
    static inline constexpr std::string_view kFlags2 = "flags2";
    static inline constexpr std::string_view kObjectClass = "object_class";
    static inline constexpr std::string_view kObjectSubclass = "object_subclass";
    static inline constexpr std::string_view kObjectIdx = "object_idx";
    static inline constexpr std::string_view kUnknown = "unknown";
    static inline constexpr std::string_view kObjectsToRender = "objects_to_render";
  };
}
