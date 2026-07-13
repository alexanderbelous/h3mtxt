#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/SavedGame.h>

namespace Medea_NS
{
  namespace
  {
    // Helper class to pass map_size to JsonValueWriter when writing vectors of elements whose indices are
    // the cooridnates of tiles on the Adventure Map (e.g., SavedGame::tiles and SavedGame::fog_of_war).
    template<class T>
    struct TilesWithMapSize
    {
      std::span<const T> tiles;
      std::uint32_t map_size {};
      bool has_two_levels {};
    };
  }

  // Partial specialization for TilesWithMapSize: serialize it as a JSON array.
  template<class T>
  struct JsonArrayWriter<TilesWithMapSize<T>>
  {
    void operator()(const ArrayElementsWriter& out, const TilesWithMapSize<T>& value) const
    {
      const std::size_t num_levels = value.has_two_levels ? 2 : 1;
      const std::size_t expected_num_tiles = num_levels * value.map_size * value.map_size;
      if (value.tiles.size() != expected_num_tiles)
      {
        // Strictly speaking, this is an error - the number of tiles should match expected_num_tiles.
        // However, this is only an error for H3SVG - we can still serialize such arrays of tiles as
        // JSON. We cannot reliably print coordinates though.
        for (const T& tile : value.tiles)
        {
          out.writeElement(tile);
        }
        return;
      }

      h3json::Detail_NS::CommentBuilder comment_builder;
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
  };

  void JsonObjectWriter<h3svg::RegionInfo>::operator()(FieldsWriter& out,
                                                       const h3svg::RegionInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::RegionInfo>;
    out.writeField(Fields::kIsCompleted, info.is_completed);
    out.writeField(Fields::kDays, info.days);
    out.writeField(Fields::kScore, info.score);
    out.writeField(Fields::kOrder, info.order);
    out.writeField(Fields::kUnknown, info.unknown);
  }

  void JsonObjectWriter<h3svg::CampaignInfo>::operator()(FieldsWriter& out, const h3svg::CampaignInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::CampaignInfo>;
    out.writeField(Fields::kUnknown1, info.unknown1);
    out.writeField(Fields::kRegionIdx, info.region_idx);
    out.writeField(Fields::kId, info.id);
    out.writeField(Fields::kUnknown2, info.unknown2);
    out.writeField(Fields::kStartingBonusIdx, info.starting_bonus_idx);
    out.writeField(Fields::kFilename, info.filename);
    out.writeField(Fields::kFinishedCampaigns, info.finished_campaigns);
    out.writeField(Fields::kRegions, info.regions);
    out.writeField(Fields::kCrossoverInfo, info.crossover_info);
  }

  template<>
  void JsonObjectWriter<h3svg::CreatureBank>::operator()(FieldsWriter& out, const h3svg::CreatureBank& creature_bank) const
  {
    out.writeField("guards", creature_bank.guards);
    out.writeField("resources", creature_bank.resources);
    out.writeField("creatures", creature_bank.creatures);
    out.writeField("artifacts", creature_bank.artifacts);
  }

  void JsonObjectWriter<h3svg::CrossoverInfo::UnknownPair>::operator()(
    FieldsWriter& out, const h3svg::CrossoverInfo::UnknownPair& pair) const
  {
    out.writeField("first", pair.first);
    out.writeField("second", pair.second);
  }

  void JsonObjectWriter<h3svg::CrossoverInfo>::operator()(FieldsWriter& out, const h3svg::CrossoverInfo& info) const
  {
    using Fields = h3json::FieldNames<h3svg::CrossoverInfo>;
    out.writeField(Fields::kCrossoverHeroes, info.crossover_heroes);
    out.writeField(Fields::kUnknown, info.unknown);
  }

  template<>
  void JsonObjectWriter<h3svg::Date>::operator()(FieldsWriter& out, const h3svg::Date& date) const
  {
    using Fields = h3json::FieldNames<h3svg::Date>;
    out.writeField(Fields::kMonth, date.month);
    out.writeField(Fields::kWeek, date.week);
    out.writeField(Fields::kDay, date.day);
  }

  template<>
  void JsonObjectWriter<h3svg::ObjectExits>::operator()(FieldsWriter& out, const h3svg::ObjectExits& object_exits) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    out.writeField(Fields::kExits, object_exits.exits);
  }

  void JsonObjectWriter<h3svg::Player>::operator()(FieldsWriter& out,
                                                   const h3svg::Player& player) const
  {
    using Fields = h3json::FieldNames<h3svg::Player>;
    out.writeField(Fields::kPlayerColor, player.player_color);
    out.writeField(Fields::kNumHeroes, player.num_heroes);
    out.writeField(Fields::kActiveHero, player.active_hero);
    out.writeField(Fields::kHeroes, player.heroes);
    out.writeField(Fields::kHeroesInTavern, player.heroes_in_tavern);
    out.writeField(Fields::kUnknown1, player.unknown1);
    out.writeField(Fields::kPersonality, player.personality);
    out.writeField(Fields::kUnknown2, player.unknown2);
    out.writeField(Fields::kDaysLeft, player.days_left);
    out.writeField(Fields::kNumTowns, player.num_towns);
    out.writeField(Fields::kCurrentTown, player.current_town);
    out.writeField(Fields::kTowns, player.towns);
    out.writeField(Fields::kResources, player.resources);
    out.writeField(Fields::kMysticalGardens, player.mystical_gardens);
    out.writeField(Fields::kMagicSprings, player.magic_springs);
    out.writeField(Fields::kCorpses, player.corpses);
    out.writeField(Fields::kLeanTos, player.lean_tos);
    out.writeField(Fields::kUnknown3, player.unknown3);
  }

  void JsonObjectWriter<h3svg::PlayerSpecs>::operator()(FieldsWriter& out, const h3svg::PlayerSpecs& player) const
  {
    using Fields = h3json::FieldNames<h3svg::PlayerSpecs>;

    out.writeField(Fields::kCanBeHuman, player.can_be_human);
    out.writeField(Fields::kCanBeComputer, player.can_be_computer);
    out.writeField(Fields::kBehavior, player.behavior);
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

  void JsonArrayWriter<h3svg::ArtifactMerchants>::operator()(const ArrayElementsWriter& out,
                                                             const h3svg::ArtifactMerchants& artifact_merchants) const
  {
    JsonArrayWriter<std::array<h3svg::ArtifactType32, 7>>{}(out, artifact_merchants.artifacts);
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
    if (std::string_view enum_str = EnumCommentGetter{}(static_cast<h3svg::ObjectClass>(object_template.object_class));
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

    out.writeField(Fields::kSignature, saved_game.signature);
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
    out.writeField(Fields::kOriginalFilename, saved_game.original_filename);
    out.writeField(Fields::kUnknown2, saved_game.unknown2);
    out.writeField(Fields::kDisabledArtifacts, saved_game.disabled_artifacts);
    out.writeField(Fields::kArtifactsBitmaskUnknown, saved_game.artifacts_bitmask_unknown);
    out.writeField(Fields::kDisabledSkills, saved_game.disabled_skills);
    out.writeField(Fields::kCurrentRumor, saved_game.current_rumor);
    out.writeField(Fields::kUnknown3, saved_game.unknown3);
    out.writeField(Fields::kRumors, saved_game.rumors);
    out.writeField(Fields::kBlackMarkets, saved_game.black_markets);
    out.writeField(Fields::kTiles,
                   TilesWithMapSize<h3svg::Tile>{
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
    out.writeField(Fields::kUnknown4, saved_game.unknown4);
    out.writeField(Fields::kCurrentDate, saved_game.current_date, true);
    out.writeField(Fields::kUnknown5, saved_game.unknown5);
    out.writeField(Fields::kArtifactMerchants, saved_game.artifact_merchants);
    out.writeField(Fields::kUnknown6, saved_game.unknown6);
    out.writeField(Fields::kKeymastersTents, saved_game.keymasters_tents);
    out.writeField(Fields::kUnknown7, saved_game.unknown7);
    out.writeField(Fields::kCartographerWater, saved_game.cartographer_water);
    out.writeField(Fields::kCartographerLand, saved_game.cartographer_land);
    out.writeField(Fields::kCartographerSubterranean, saved_game.cartographer_subterranean);
    out.writeField(Fields::kUnknown8, saved_game.unknown8);
    out.writeField(Fields::kFogOfWar, TilesWithMapSize<h3svg::TileVisibility>{
                                        .tiles = saved_game.fog_of_war,
                                        .map_size = saved_game.basic_info.map_size,
                                        .has_two_levels = static_cast<bool>(saved_game.basic_info.has_two_levels)
                                      });
    out.writeField(Fields::kMonolithsTwoWay, saved_game.monoliths_two_way);
    out.writeField(Fields::kMonolithsOneWay, saved_game.monoliths_one_way);
    out.writeField(Fields::kWhirlpools, saved_game.whirlpools);
    out.writeField(Fields::kSubterraneanGates, saved_game.subterranean_gates);
    out.writeField(Fields::kUnknown9, saved_game.unknown9);
    out.writeField(Fields::kUniversities, saved_game.universities);
    out.writeField(Fields::kCreatureBanks, saved_game.creature_banks);
    out.writeField("previous_turn", saved_game.previous_turn);
    //out.writeField("unknown10", saved_game.unknown10);
  }

  void JsonObjectWriter<h3svg::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3svg::ScenarioStartingInfo& starting_info) const
  {
    using Fields = h3json::FieldNames<h3svg::ScenarioStartingInfo>;

    out.writeField(Fields::kStartingTowns, starting_info.starting_towns);
    out.writeField(Fields::kUnknown1, starting_info.unknown1);
    out.writeField(Fields::kDifficulty, starting_info.difficulty);
    out.writeField(Fields::kMapFilename, starting_info.map_filename);
    out.writeField(Fields::kMapDirectory, starting_info.map_directory);
    out.writeField(Fields::kPlayersControl, starting_info.players_control);
    out.writeField(Fields::kUnknown2, starting_info.unknown2);
    out.writeField(Fields::kPlayerTurnDuration, starting_info.player_turn_duration);
    out.writeField(Fields::kStartingHeroes, starting_info.starting_heroes);
    out.writeField(Fields::kStartingBonuses, starting_info.starting_bonuses);
    if (starting_info.campaign_info.has_value())
    {
      out.writeField(Fields::kCampaignInfo, *starting_info.campaign_info);
    }
    out.writeField(Fields::kPlaceholderHeroes, starting_info.placeholder_heroes);
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
    out.writeField(Fields::kTerrainSprite, tile.terrain_sprite);
    out.writeField(Fields::kRiverType, tile.river_type);
    out.writeField(Fields::kRiverSprite, tile.river_sprite);
    out.writeField(Fields::kRoadType, tile.road_type);
    out.writeField(Fields::kRoadSprite, tile.road_sprite);
    out.writeField(Fields::kFlags1, tile.flags1);
    out.writeField(Fields::kFlags2, tile.flags2);
    out.writeField(Fields::kObjectClass, tile.object_class);
    out.writeField(Fields::kObjectSubclass, tile.object_subclass);
    out.writeField(Fields::kObjectIdx, tile.object_idx);
    out.writeField(Fields::kObjectProperties, tile.object_properties);
    out.writeField(Fields::kObjectsToRender, tile.objects_to_render);
  }

  void JsonObjectWriter<h3svg::TileVisibility>::operator()(FieldsWriter& out,
                                                           const h3svg::TileVisibility& tile_visibility) const
  {
    using Fields = h3json::FieldNames<h3svg::TileVisibility>;
    out.writeField(Fields::kVisibility, tile_visibility.visibility, true);
    out.writeField(Fields::kHasAdjacentMonster, tile_visibility.has_adjacent_monster);
  }

  template<>
  void JsonObjectWriter<h3svg::University>::operator()(FieldsWriter& out, const h3svg::University& university) const
  {
    using Fields = h3json::FieldNames<h3svg::University>;
    out.writeField(Fields::kSkills, university.skills);
  }
}
