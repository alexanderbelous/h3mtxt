#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/H3SvgJsonWriter/writeEnumIndexedArray.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/SavedGame.h>

namespace Medea_NS
{
  namespace
  {
    // Helper class to pass map_size to JsonValueWriter when writing SavedGame::tiles.
    struct TilesWithMapSize
    {
      std::span<const h3svg::Tile> tiles;
      std::uint32_t map_size {};
      bool has_two_levels {};
    };
  }

  // Serialize TilesWithMapSize as a JSON array.
  template<>
  void JsonArrayWriter<TilesWithMapSize>::operator()(const ArrayElementsWriter& out,
                                                     const TilesWithMapSize& value) const
  {
    const std::size_t num_levels = value.has_two_levels ? 2 : 1;
    const std::size_t expected_num_tiles = num_levels * value.map_size * value.map_size;
    if (value.tiles.size() != expected_num_tiles)
    {
      // Strictly speaking, this is an error - the number of tiles should match expected_num_tiles.
      // However, this is only an error for H3SVG - we can still serialize such arrays of tiles as
      // JSON. We cannot reliably print coordinates though.
      for (const h3svg::Tile& tile : value.tiles)
      {
        out.writeElement(tile);
      }
      return;
    }

    h3m::H3JsonWriter_NS::CommentBuilder comment_builder;
    auto iter = value.tiles.begin();
    for (std::uint32_t z = 0; z < num_levels; ++z)
    {
      for (std::uint32_t y = 0; y < value.map_size; ++y)
      {
        for (std::uint32_t x = 0; x < value.map_size; ++x)
        {
          out.writeComment(comment_builder.build({ "Tile (", x, ", ", y, ", ", z, ")" }));
          out.writeElement(*iter);
          ++iter;
        }
      }
    }
  }

  void JsonObjectWriter<h3svg::Player>::operator()(FieldsWriter& out,
                                                   const h3svg::Player& player) const
  {
    using Fields = h3json::FieldNames<h3svg::Player>;
    out.writeField(Fields::kPlayerColor, player.player_color);
    if (std::string_view enum_str = getEnumString(player.player_color); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kNumHeroes, player.num_heroes);
    out.writeField(Fields::kActiveHero, player.active_hero);
    if (std::string_view enum_str = getEnumString(player.active_hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kHeroes, player.heroes);
    out.writeField(Fields::kHeroesInTavern, player.heroes_in_tavern);
    out.writeField(Fields::kUnknown1, player.unknown1);
    out.writeField(Fields::kPersonality, player.personality);
    if (std::string_view enum_str = getEnumString(player.personality); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown2, player.unknown2);
    out.writeField(Fields::kDaysLeft, player.days_left);
    out.writeField(Fields::kNumTowns, player.num_towns);
    out.writeField(Fields::kCurrentTown, player.current_town);
    out.writeField(Fields::kTowns, player.towns);
    out.writeField(Fields::kUnknown3, player.unknown3);
    out.writeField(Fields::kResources, player.resources);
    out.writeField(Fields::kMysticalGardens, player.mystical_gardens);
    out.writeField(Fields::kUnknown4, player.unknown4);
    out.writeField(Fields::kCorpses, player.corpses);
    out.writeField(Fields::kLeanTos, player.lean_tos);
    out.writeField(Fields::kUnknown5, player.unknown5);
  }

  void JsonObjectWriter<h3svg::PlayerSpecs>::operator()(FieldsWriter& out, const h3svg::PlayerSpecs& player) const
  {
    using Fields = h3json::FieldNames<h3svg::PlayerSpecs>;

    out.writeField(Fields::kCanBeHuman, player.can_be_human);
    out.writeField(Fields::kCanBeComputer, player.can_be_computer);
    out.writeField(Fields::kBehavior, player.behavior);
    if (auto enum_str = getEnumString(player.behavior); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kAllowedAlignments, player.allowed_alignments);
    out.writeField(Fields::kAllowRandomAlignment, player.allow_random_alignment);
    if (player.generated_hero_coordinates.has_value())
    {
      out.writeField(Fields::kGeneratedHeroCoordinates, player.generated_hero_coordinates.value());
    }
    out.writeField(Fields::kStartingHero, player.starting_hero);
  }

  void JsonObjectWriter<h3svg::Rumor>::operator()(FieldsWriter& out, const h3svg::Rumor& rumor) const
  {
    using Fields = h3json::FieldNames<h3svg::Rumor>;
    out.writeField(Fields::kText, rumor.text);
    out.writeField(Fields::kHasBeenShown, rumor.has_been_shown);
  }

  void JsonArrayWriter<h3svg::BlackMarket>::operator()(const ArrayElementsWriter& out,
                                                       const h3svg::BlackMarket& black_market) const
  {
    for (h3svg::ArtifactType32 artifact : black_market.artifacts)
    {
      out.writeElement(artifact);
      if (std::string_view enum_str = getEnumString(artifact); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3svg::Object>::operator()(FieldsWriter& out, const h3svg::Object& object) const
  {
    using Fields = h3json::FieldNames<h3svg::Object>;
    out.writeField(Fields::kCoordinates, object.coordinates);
    out.writeField(Fields::kTemplateIdx, object.template_idx);
  }

  void JsonObjectWriter<h3svg::ObjectTemplate>::operator()(FieldsWriter& out,
                                                           const h3svg::ObjectTemplate& object_template) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectTemplate>;
    out.writeField(Fields::kDef, object_template.def);
    out.writeField(Fields::kWidth, object_template.width);
    out.writeField(Fields::kHeight, object_template.height);
    out.writeField(Fields::kUnknown1, object_template.unknown1);
    out.writeField(Fields::kPassability, object_template.passability);
    out.writeField(Fields::kUnknown2, object_template.unknown2);
    out.writeField(Fields::kActionability, object_template.actionability);
    out.writeField(Fields::kObjectClass, object_template.object_class);
    if (std::string_view enum_str = getEnumString(static_cast<h3svg::ObjectClass>(object_template.object_class));
        !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, object_template.object_subclass);
    out.writeField(Fields::kReserved, object_template.reserved);
    out.writeField(Fields::kIsGround, object_template.is_ground);
  }

  void JsonObjectWriter<h3svg::SavedGame>::operator()(FieldsWriter& out, const h3svg::SavedGame& saved_game) const
  {
    using Fields = h3json::FieldNames<h3svg::SavedGame>;

    out.writeField(Fields::kReserved1, saved_game.reserved1);
    out.writeField(Fields::kVersionMajor, saved_game.version_major);
    out.writeField(Fields::kVersionMinor, saved_game.version_minor);
    out.writeField(Fields::kReserved2, saved_game.reserved2);
    out.writeField(Fields::kFormat, saved_game.format);
    out.writeField(Fields::kBasicInfo, saved_game.basic_info);
    out.writeField(Fields::kPlayersSpecs, saved_game.players_specs);
    out.writeField(Fields::kVictoryCondition, saved_game.victory_condition);
    out.writeField(Fields::kLossCondition, saved_game.loss_condition);
    out.writeField(Fields::kTeams, saved_game.teams);
    out.writeField(Fields::kCustomHeroes, saved_game.custom_heroes);
    out.writeField(Fields::kUnknown1, saved_game.unknown1);
    out.writeField(Fields::kStartingInfo, saved_game.starting_info);
    out.writeField(Fields::kUnknown2, saved_game.unknown2);
    // TODO: consider serializing as a string.
    out.writeField(Fields::kOriginalFilename, saved_game.original_filename);
    out.writeField(Fields::kUnknown3, saved_game.unknown3);
    out.writeField(Fields::kDisabledArtifacts, saved_game.disabled_artifacts);
    out.writeField(Fields::kArtifactsBitmaskUnknown, saved_game.artifacts_bitmask_unknown);
    out.writeField(Fields::kDisabledSkills, saved_game.disabled_skills);
    out.writeField(Fields::kCurrentRumor, saved_game.current_rumor);
    out.writeField(Fields::kUnknown4, saved_game.unknown4);
    out.writeField(Fields::kRumors, saved_game.rumors);
    out.writeField(Fields::kBlackMarkets, saved_game.black_markets);
    out.writeField(Fields::kTiles,
                   TilesWithMapSize{
                     .tiles = saved_game.tiles,
                     .map_size = saved_game.basic_info.map_size,
                     .has_two_levels = static_cast<bool>(saved_game.basic_info.has_two_levels)
                   });
    // TODO: print the 0-based index for each element
    out.writeField(Fields::kObjectsTemplates, saved_game.objects_templates);
    out.writeField(Fields::kObjects, saved_game.objects);
    out.writeField(Fields::kObjectPropertiesTables, saved_game.object_properties_tables);
    out.writeField(Fields::kPlayers, saved_game.players);
    out.writeField(Fields::kTowns, saved_game.towns);
    out.writeField(Fields::kHeroes, saved_game.heroes);
  }

  void JsonObjectWriter<h3svg::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3svg::ScenarioStartingInfo& starting_info) const
  {
    using Fields = h3json::FieldNames<h3svg::ScenarioStartingInfo>;

    out.writeField(Fields::kStartingTowns, starting_info.starting_towns);
    out.writeField(Fields::kUnknown1, starting_info.unknown1);
    out.writeField(Fields::kDifficulty, starting_info.difficulty);
    if (std::string_view enum_str = getEnumString(starting_info.difficulty); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    // TODO: it sucks that we serialize this as a JSON array rather than a string.
    // Consider serializing as a string, escaping unprintable characters.
    out.writeField(Fields::kMapFilename, starting_info.map_filename);
    // TODO: consider serializing as a string rather than a JSON array,
    //       escaping unprintable characters.
    out.writeField(Fields::kMapDirectory, starting_info.map_directory);
    out.writeField(Fields::kPlayersControl, starting_info.players_control);
    out.writeField(Fields::kUnknown2, starting_info.unknown2);
    out.writeField(Fields::kPlayerTurnDuration, starting_info.player_turn_duration);
    if (std::string_view enum_str = getEnumString(starting_info.player_turn_duration); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kStartingHeroes, starting_info.starting_heroes);
    out.writeField(Fields::kStartingBonuses, starting_info.starting_bonuses);
  }

  void JsonObjectWriter<h3svg::Town>::operator()(FieldsWriter& out, const h3svg::Town& town) const
  {
    using Fields = h3json::FieldNames<h3svg::Town>;
    out.writeField(Fields::kId, town.id);
    out.writeField(Fields::kOwner, town.owner);
    if (std::string_view enum_str = getEnumString(town.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kBuiltThisTurn, town.built_this_turn);
    out.writeField(Fields::kUnknown1, town.unknown1);
    out.writeField(Fields::kType, town.type);
    if (std::string_view enum_str = getEnumString(town.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kCoordinates, town.coordinates);
    out.writeField(Fields::kGeneratedBoatX, town.generated_boat_x);
    out.writeField(Fields::kGeneratedBoatY, town.generated_boat_y);
    out.writeField(Fields::kGarrison, town.garrison);
    out.writeField(Fields::kGarrisonedHero, town.garrisoned_hero);
    if (std::string_view enum_str = getEnumString(town.garrisoned_hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kVisitingHero, town.visiting_hero);
    if (std::string_view enum_str = getEnumString(town.visiting_hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kMageGuildLevel, town.mage_guild_level);
    out.writeField(Fields::kUnknown2, town.unknown2);
    out.writeField(Fields::kName, town.name);
    out.writeField(Fields::kRecruitsNonUpgraded, town.recruits_nonupgraded);
    out.writeField(Fields::kRecruitsUpgraded, town.recruits_upgraded);
    out.writeField(Fields::kUnknown3, town.unknown3);
    out.writeField(Fields::kSpells, town.spells);
    out.writeField(Fields::kUnknown4, town.unknown4);
  }

  template<>
  void JsonObjectWriter<h3svg::Tile::ObjectToRender>::operator()(
    FieldsWriter& out, const h3svg::Tile::ObjectToRender& object_to_render) const
  {
    out.writeField("object_idx", object_to_render.object_idx);
    out.writeField("unknown", object_to_render.unknown);
  }

  void JsonObjectWriter<h3svg::Tile>::operator()(FieldsWriter& out, const h3svg::Tile& tile) const
  {
    using Fields = h3json::FieldNames<h3svg::Tile>;
    out.writeField(Fields::kTerrainType, tile.terrain_type);
    if (std::string_view enum_str = getEnumString(tile.terrain_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kTerrainSprite, tile.terrain_sprite);
    out.writeField(Fields::kRiverType, tile.river_type);
    if (std::string_view enum_str = getEnumString(tile.river_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRiverSprite, tile.river_sprite);
    out.writeField(Fields::kRoadType, tile.road_type);
    if (std::string_view enum_str = getEnumString(tile.road_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRoadSprite, tile.road_sprite);
    out.writeField(Fields::kFlags1, tile.flags1);
    out.writeField(Fields::kFlags2, tile.flags2);
    out.writeField(Fields::kObjectClass, tile.object_class);
    if (std::string_view enum_str = getEnumString(tile.object_class); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, tile.object_subclass);
    out.writeField(Fields::kObjectIdx, tile.object_idx);
    out.writeField(Fields::kObjectProperties, tile.object_properties);
    out.writeField(Fields::kObjectsToRender, tile.objects_to_render);
  }
}
