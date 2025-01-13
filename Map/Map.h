#pragma once

// See https://github.com/HeroWO-js/h3m2json/blob/master/h3m-The-Corpus.txt

#include <h3mparser/Map/Constants/Constants.h>
#include <h3mparser/Map/Constants/MapFormat.h>
#include <h3mparser/Map/GlobalEvent.h>
#include <h3mparser/Map/MapAdditionalInfo.h>
#include <h3mparser/Map/MapBasicInfo.h>
#include <h3mparser/Map/ObjectAttributes.h>
#include <h3mparser/Map/ObjectDetails.h>
#include <h3mparser/Map/PlayerSpecs.h>
#include <h3mparser/Map/Tile.h>


#include <array>
#include <cstdint>
#include <vector>

namespace h3m
{

// Represents a *.h3m map.
struct Map
{
  // Format of the map ("Map Specifications"/"Map version" in the Editor).
  MapFormat format = MapFormat::ShadowOfDeath;
  // Basic information about the map ("Map Specifications"/"General" tab in the Editor).
  MapBasicInfo basic_info;
  // Settings for each player ("Map Specifications"/"Player specs" tab in the Editor).
  std::array<PlayerSpecs, kMaxPlayers> players {};
  // Additional information about the map ("Special Victory Condition", "Special Loss Condition",
  // "Teams", "Heroes", "Artifacts", "Spells", "Secondary Skills" and "Rumors" tabs in the Editor).
  MapAdditionalInfo additional_info;
  // Terrain data for each tile on the map.
  // N elements, where N = (has_two_levels ? 2 : 1) * map_size * map_size.
  //
  // Tiles are stored as if they were written like this:
  //     for (int z = 0; z < num_levels; ++z) {  // 0 is overground, 1 is underground.
  //       for (int y = 0; y < map_size; ++y) {
  //         for (int x = 0; x < map_size; ++x) {
  //           tiles.push_back(...);
  //         }
  //       }
  //     }
  std::vector<Tile> tiles;
  // Object properties are split into two structures: attributes (common for all objects of the same kind)
  // and details (as many as there are objects on map).
  std::vector<ObjectAttributes> objects_attributes;
  std::vector<ObjectDetails> objects_details;
  // Global events on this map ("Map Specifications"/"Timed Events" tab in the Editor).
  std::vector<GlobalEvent> global_events;
  // Should be 0s. Kept here for compatibility.
  std::array<std::uint8_t, 124> padding {};
};

}
