#include <Minimap/Minimap.h>

#include <h3mtxt/Map/Map.h>

#include <optional>
#include <stdexcept>

namespace Minimap_NS
{
  namespace
  {
    // Returns the color for the specified TerrainType.
    constexpr Color getColorForTerrain(h3m::TerrainType terrain_type) noexcept
    {
      switch (terrain_type)
      {
      case h3m::TerrainType::Dirt:         return Color{ .r = 82,  .g = 57,  .b = 8   };
      case h3m::TerrainType::Sand:         return Color{ .r = 222, .g = 206, .b = 140 };
      case h3m::TerrainType::Grass:        return Color{ .r = 0,   .g = 66,  .b = 0   };
      case h3m::TerrainType::Snow:         return Color{ .r = 181, .g = 198, .b = 198 };
      case h3m::TerrainType::Swamp:        return Color{ .r = 74,  .g = 132, .b = 107 };
      case h3m::TerrainType::Rough:        return Color{ .r = 132, .g = 115, .b = 49  };
      case h3m::TerrainType::Subterranean: return Color{ .r = 132, .g = 49,  .b = 0   };
      case h3m::TerrainType::Lava:         return Color{ .r = 74,  .g = 74,  .b = 74  };
      case h3m::TerrainType::Water:        return Color{ .r = 8,   .g = 82,  .b = 148 };
      case h3m::TerrainType::Rock:         return Color{ .r = 0,   .g = 0,   .b = 0   };
      default:                             return Color{};
      }
    }

    // Returns the color for the specified TerrainType with an obstacle on it.
    constexpr Color getColorForTerrainWithObstacle(h3m::TerrainType terrain_type) noexcept
    {
      switch (terrain_type)
      {
      case h3m::TerrainType::Dirt:         return Color{ .r = 57,  .g = 41,  .b = 8   };
      case h3m::TerrainType::Sand:         return Color{ .r = 165, .g = 156, .b = 107 };
      case h3m::TerrainType::Grass:        return Color{ .r = 0,   .g = 49,  .b = 0   };
      case h3m::TerrainType::Snow:         return Color{ .r = 140, .g = 156, .b = 156 };
      case h3m::TerrainType::Swamp:        return Color{ .r = 33,  .g = 90,  .b = 66  };
      case h3m::TerrainType::Rough:        return Color{ .r = 99,  .g = 82,  .b = 33  };
      case h3m::TerrainType::Subterranean: return Color{ .r = 90,  .g = 8,   .b = 0   };
      case h3m::TerrainType::Lava:         return Color{ .r = 41,  .g = 41,  .b = 41  };
      case h3m::TerrainType::Water:        return Color{ .r = 0,   .g = 41,  .b = 107 };
      case h3m::TerrainType::Rock:         return Color{ .r = 0,   .g = 0,   .b = 0   };
      default:                             return Color{};
      }
    }

    // Returns the RGB color for the specified PlayerColor.
    constexpr Color getColorForPlayer(h3m::PlayerColor player) noexcept
    {
      switch (player)
      {
      case h3m::PlayerColor::Red:    return Color{ .r = 255, .g = 0,   .b = 0   };
      case h3m::PlayerColor::Blue:   return Color{ .r = 49,  .g = 82,  .b = 255 };
      case h3m::PlayerColor::Tan:    return Color{ .r = 156, .g = 115, .b = 82  };
      case h3m::PlayerColor::Green:  return Color{ .r = 66,  .g = 148, .b = 41  };
      case h3m::PlayerColor::Orange: return Color{ .r = 255, .g = 132, .b = 0   };
      case h3m::PlayerColor::Purple: return Color{ .r = 140, .g = 41,  .b = 165 };
      case h3m::PlayerColor::Teal:   return Color{ .r = 8,   .g = 156, .b = 165 };
      case h3m::PlayerColor::Pink:   return Color{ .r = 198, .g = 123, .b = 140 };
      default:                       return Color{ .r = 132, .g = 132, .b = 132 };  // PlayerColor{0xFF} aka "None"
      }
    }

    // Returns the owner of the given object on the Adventure Map.
    //
    // Warning: in H3M prisons use the same format as heroes, i.e. ObjectProperties<h3m::ObjectPropertiesType::HERO>.
    // As a consequence, a prison technically does have an "owner" property, but it should be ignored
    // (a player cannot own a prison).
    //
    // \param properties - properties of the object on the Adventure Map.
    // \return the owner of @properties, or std::nullopt if this object cannot be owned.
    std::optional<h3m::PlayerColor> getOwner(const h3m::ObjectPropertiesVariant& properties)
    {
      constexpr h3m::PlayerColor kNoOwner{ 0xFF };
      switch (properties.type())
      {
      case h3m::ObjectPropertiesType::ABANDONED_MINE:
        return kNoOwner;
      case h3m::ObjectPropertiesType::GARRISON:
        return properties.get<h3m::ObjectPropertiesType::GARRISON>().owner;
      case h3m::ObjectPropertiesType::HERO:
        return properties.get<h3m::ObjectPropertiesType::HERO>().owner;
      case h3m::ObjectPropertiesType::PLACEHOLDER_HERO:
        return properties.get<h3m::ObjectPropertiesType::PLACEHOLDER_HERO>().owner;
      case h3m::ObjectPropertiesType::RANDOM_DWELLING:
        return static_cast<h3m::PlayerColor>(properties.get<h3m::ObjectPropertiesType::RANDOM_DWELLING>().owner);
      case h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT:
        return static_cast<h3m::PlayerColor>(properties.get<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>().owner);
      case h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL:
        return static_cast<h3m::PlayerColor>(properties.get<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>().owner);
      case h3m::ObjectPropertiesType::TOWN:
        return properties.get<h3m::ObjectPropertiesType::TOWN>().owner;
      case h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT:
        return properties.get<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>().owner;
      default:
        return std::nullopt;
      }
    }

    // Returns the owner of the given object on the Adventure Map.
    // \param object - object on the Adventure Map.
    // \return the owner of @object, or std::nullopt if this object cannot be owned.
    std::optional<h3m::PlayerColor> getOwner(const h3m::Object& object)
    {
      return getOwner(object.properties);
    }

    // Checks if objects of the specified type should be rendered as obstacles on the minimap.
    //
    // Note that not all obstacles are rendered on the minimap: for example, flowers, mushrooms and reefs
    // are not rendered.
    //
    // \param object_class - input ObjectClass.
    // \return true if objects of the type @object_class should be rendered as obstacles on the minimap,
    //         false otherwise.
    constexpr bool isMinimapObstacle(h3m::ObjectClass object_class) noexcept
    {
      switch (object_class)
      {
      case h3m::ObjectClass::IMPASSABLE_CACTUS:
      case h3m::ObjectClass::IMPASSABLE_CRATER:
      case h3m::ObjectClass::IMPASSABLE_DEADVEGETATION:
      case h3m::ObjectClass::IMPASSABLE_FROZENLIKE:
      case h3m::ObjectClass::IMPASSABLE_LAKE:
      case h3m::ObjectClass::IMPASSABLE_LAVALAKE:
      case h3m::ObjectClass::IMPASSABLE_MANDRAKE:
      case h3m::ObjectClass::IMPASSABLE_MOUND:
      case h3m::ObjectClass::IMPASSABLE_MOUNTAIN:
      case h3m::ObjectClass::IMPASSABLE_OAKTREES:
      case h3m::ObjectClass::IMPASSABLE_PINETREES:
      case h3m::ObjectClass::IMPASSABLE_SANDDUNE:
      case h3m::ObjectClass::IMPASSABLE_SANDPIT:
      case h3m::ObjectClass::IMPASSABLE_STUMP:
      case h3m::ObjectClass::IMPASSABLE_TREES:
      case h3m::ObjectClass::IMPASSABLE_VOLCANO:
      case h3m::ObjectClass::IMPASSABLE_CACTUS2:
      case h3m::ObjectClass::IMPASSABLE_CRATER2:
      case h3m::ObjectClass::IMPASSABLE_DEADVEGETATION2:
      case h3m::ObjectClass::IMPASSABLE_FROZENLIKE2:
      case h3m::ObjectClass::IMPASSABLE_LAKE2:
      case h3m::ObjectClass::IMPASSABLE_LAVALAKE2:
      case h3m::ObjectClass::IMPASSABLE_MANDRAKE2:
      case h3m::ObjectClass::IMPASSABLE_MOUND2:
      case h3m::ObjectClass::IMPASSABLE_MOUNTAIN2:
      case h3m::ObjectClass::IMPASSABLE_OAKTREES2:
      case h3m::ObjectClass::IMPASSABLE_PINETREES2:
      case h3m::ObjectClass::IMPASSABLE_SANDDUNE2:
      case h3m::ObjectClass::IMPASSABLE_SANDPIT2:
      case h3m::ObjectClass::IMPASSABLE_STUMP2:
      case h3m::ObjectClass::IMPASSABLE_TREES2:
      case h3m::ObjectClass::IMPASSABLE_VOLCANO2:
      case h3m::ObjectClass::IMPASSABLE_DESERTHILLS:
      case h3m::ObjectClass::IMPASSABLE_DIRTHILLS:
      case h3m::ObjectClass::IMPASSABLE_GRASSHILLS:
      case h3m::ObjectClass::IMPASSABLE_ROUGHHILLS:
      case h3m::ObjectClass::IMPASSABLE_SUBTERRANEANROCKS:
      case h3m::ObjectClass::IMPASSABLE_SWAMPFOLIAGE:
      case h3m::ObjectClass::IMPASSABLE_HILL:
      case h3m::ObjectClass::IMPASSABLE_STALAGMITE:
      case h3m::ObjectClass::IMPASSABLE_TARPIT:
      case h3m::ObjectClass::IMPASSABLE_WILLOWTREES:
      case h3m::ObjectClass::IMPASSABLE_YUCCATREES:
      case h3m::ObjectClass::IMPASSABLE_HILL2:
      case h3m::ObjectClass::IMPASSABLE_STALAGMITE2:
      case h3m::ObjectClass::IMPASSABLE_TARPIT2:
      case h3m::ObjectClass::IMPASSABLE_WILLOWTREES2:
      case h3m::ObjectClass::IMPASSABLE_YUCCATREES2:
        return true;
      default:
        return false;
      }
    }
  }

  Image makeMinimap(const h3m::Map& map, bool subterranean)
  {
    if (!map.basic_info.has_two_levels && subterranean)
    {
      throw std::invalid_argument("makeMinimap(): there is no subterranean layer.");
    }

    const std::uint32_t map_size = map.basic_info.map_size;
    const std::uint8_t layer = subterranean ? 1 : 0;
    Image image{ map_size, map_size };

    // 1. For each tile (x, y) check if there is an obstacle on it that should be rendered on the minimap.
    //
    // We do it here to avoid unnecessary memory allocation - we will use @image itself for the computed mask:
    // * Color{0, 0, 0} -> no obstacles.
    // * Any other color -> has obstacles.
    for (const h3m::Object& object : map.objects)
    {
      // Skip if the object is not on the requested layer.
      if (object.coordinates.z != layer)
      {
        continue;
      }

      const h3m::ObjectTemplate& object_template = map.objects_templates.at(object.template_idx);

      // Skip if the object is not an obstacle that should be rendered on the minimap.
      if (!isMinimapObstacle(object_template.object_class))
      {
        continue;
      }

      // Process each impassable tile for this object.
      for (std::uint8_t row = 0; row < 6; ++row)
      {
        for (std::uint8_t column = 0; column < 8; ++column)
        {
          // Skip if passable.
          if (object_template.passability.at(row, column))
          {
            continue;
          }
          const std::int16_t x = static_cast<std::int16_t>(object.coordinates.x) - (7 - column);
          const std::int16_t y = static_cast<std::int16_t>(object.coordinates.y) - (5 - row);
          // Skip if the tile is outside of the map.
          if (x < 0 || static_cast<std::uint16_t>(x) >= map_size ||
              y < 0 || static_cast<std::uint16_t>(y) >= map_size)
          {
            continue;
          }
          // Set the color of the pixel.
          constexpr Color kObstacleColor{ .r = 255, .g = 255, .b = 255 };
          static_assert(kObstacleColor != Color{});
          image(static_cast<std::uint16_t>(x), static_cast<std::uint16_t>(y)) = kObstacleColor;
        }
      }
    }

    // 2. Set the color of each pixel based on its TerrainType and whether there is an obstacle on it.
    for (std::uint32_t y = 0; y < map_size; ++y)
    {
      for (std::uint32_t x = 0; x < map_size; ++x)
      {
        const h3m::TerrainType terrain_type = map.getTile(x, y, layer).terrain_type;
        // Check if there is an obstacle on this tile and it should be rendered on the minimap.
        // This was computed during the previous step.
        const bool has_obstacle = (image(x, y) != Color{});
        image(x, y) = has_obstacle ? getColorForTerrainWithObstacle(terrain_type)
                                   : getColorForTerrain(terrain_type);
      }
    }

    // 3. Render objects that can be owned by players.
    for (const h3m::Object& object : map.objects)
    {
      const h3m::ObjectTemplate& object_template = map.objects_templates.at(object.template_idx);

      // Skip if the object is not on the requested layer.
      if (object.coordinates.z != layer)
      {
        continue;
      }

      // Skip if this a prison.
      // Prisons technically have an "owner" property, but it should be ignored. Prisons are not rendered
      // on the minimap.
      if (object_template.object_class == h3m::ObjectClass::PRISON)
      {
        continue;
      }

      const std::optional<h3m::PlayerColor> owner = getOwner(object);
      // Skip if this object cannot be owned by a player.
      if (owner == std::nullopt)
      {
        continue;
      }

      const Color owner_color = getColorForPlayer(*owner);

      // Process each impassable tile for this object.
      for (std::uint8_t row = 0; row < 6; ++row)
      {
        for (std::uint8_t column = 0; column < 8; ++column)
        {
          // Skip if passable.
          if (object_template.passability.at(row, column))
          {
            continue;
          }
          const std::int16_t x = static_cast<std::int16_t>(object.coordinates.x) - (7 - column);
          const std::int16_t y = static_cast<std::int16_t>(object.coordinates.y) - (5 - row);
          // Skip if the tile is outside of the map.
          if (x < 0 || static_cast<std::uint16_t>(x) >= map_size || 
              y < 0 || static_cast<std::uint16_t>(y) >= map_size)
          {
            continue;
          }
          // Set the color of the pixel.
          image(static_cast<std::uint16_t>(x), static_cast<std::uint16_t>(y)) = owner_color;
        }
      }
    }

    return image;
  }
}
