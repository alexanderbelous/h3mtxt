#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/GlobalEvent.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/ObjectAttributes.h>
#include <h3mtxt/Map/ObjectDetails.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Tile.h>

#include <array>
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
  // The number of elements should be (has_two_levels ? 2 : 1) * map_size * map_size.
  // Tile (x, y, z) has the index ((z * map_size + y) * map_size + x).
  std::vector<Tile> tiles;
  // Object properties are split into two structures: attributes (common for all objects of the same kind)
  // and details (as many as there are objects on map).
  std::vector<ObjectAttributes> objects_attributes;
  std::vector<ObjectDetails> objects_details;
  // Global events on this map ("Map Specifications"/"Timed Events" tab in the Editor).
  std::vector<GlobalEvent> global_events;
  // Should be 0s. Kept here for compatibility.
  ReservedData<124> padding {};
};

}
