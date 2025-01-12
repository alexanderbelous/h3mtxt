#pragma once

// See https://github.com/HeroWO-js/h3m2json/blob/master/h3m-The-Corpus.txt

#include <h3mparser/Map/Base.h>
#include <h3mparser/Map/BitSet.h>
#include <h3mparser/Map/Constants/Constants.h>
#include <h3mparser/Map/Constants/MapFormat.h>
#include <h3mparser/Map/GlobalEvent.h>
#include <h3mparser/Map/MapAdditionalInfo.h>
#include <h3mparser/Map/MapBasicInfo.h>
#include <h3mparser/Map/PlayerSpecs.h>
#include <h3mparser/Map/Tile.h>


#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

struct ObjectAttributes
{
  // Name of the *.def sprite to use.
  std::string def;
  std::array<std::uint8_t, 6> passability {};
  std::array<std::uint8_t, 6> actionability {};
  // Bitfield.
  std::uint16_t allowed_landscapes;
  // Bitfield.
  std::uint16_t landscape_group;
  std::uint32_t object_class;
  std::uint32_t object_number;
  // TODO: make this an enum.
  std::uint8_t object_group;
  Bool is_ground;
  // Should be 0s.
  std::array<std::uint8_t, 16> unknown;
};

struct Map
{
  MapFormat format = MapFormat::ShadowOfDeath;
  MapBasicInfo basic_info;
  std::array<PlayerSpecs, kMaxPlayers> players {};
  MapAdditionalInfo additional_info;
  // N elements, where N = (has_two_levels ? 2 : 1) * map_size * map_size.
  std::vector<Tile> tiles;
  // TODO: add objects.
  // Global events on this map (called "Timed Events" in the Editor).
  std::vector<GlobalEvent> global_events;
  // Should be 0s. Kept here for compatibility.
  std::array<std::uint8_t, 124> padding {};
};

}
