#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/CommentBuilder.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/FixedLengthString.h>
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

  template<>
  void JsonArrayWriter<h3svg::ArtifactMerchants>::operator()(const ArrayElementsWriter& out,
                                                             const h3svg::ArtifactMerchants& artifact_merchants) const
  {
    JsonArrayWriter<std::array<h3svg::ArtifactType32, h3svg::ArtifactMerchants::kNumSlots>>{}(
      out, artifact_merchants.artifacts);
  }

  template<>
  void JsonObjectWriter<h3svg::CreatureBank>::operator()(FieldsWriter& out, const h3svg::CreatureBank& creature_bank) const
  {
    using Fields = h3json::FieldNames<h3svg::CreatureBank>;
    out.writeField(Fields::kGuards, creature_bank.guards);
    out.writeField(Fields::kResources, creature_bank.resources);
    out.writeField(Fields::kCreatures, creature_bank.creatures);
    out.writeField(Fields::kArtifacts, creature_bank.artifacts);
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
  void JsonObjectWriter<h3svg::Object>::operator()(FieldsWriter& out, const h3svg::Object& object) const
  {
    using Fields = h3json::FieldNames<h3svg::Object>;
    out.writeField(Fields::kCoordinates, object.coordinates);
    out.writeField(Fields::kTemplateIdx, object.template_idx);
  }

  template<>
  void JsonObjectWriter<h3svg::ObjectExits>::operator()(FieldsWriter& out, const h3svg::ObjectExits& object_exits) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    out.writeField(Fields::kExits, object_exits.exits);
  }

  template<>
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

  template<>
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

  template<>
  void JsonObjectWriter<h3svg::Rumor>::operator()(FieldsWriter& out, const h3svg::Rumor& rumor) const
  {
    using Fields = h3json::FieldNames<h3svg::Rumor>;
    out.writeField(Fields::kText, rumor.text);
    out.writeField(Fields::kHasBeenShown, rumor.has_been_shown);
  }

  template<>
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
    out.writeField(Fields::kGrailX, saved_game.grail_x);
    out.writeField(Fields::kGrailY, saved_game.grail_y);
    out.writeField(Fields::kGrailZ, saved_game.grail_z);
    out.writeField(Fields::kUnknown4a, saved_game.unknown4a);
    out.writeField(Fields::kIsCheater, saved_game.is_cheater);
    out.writeField(Fields::kCurrentDate, saved_game.current_date, true);
    out.writeField(Fields::kUnknown5, saved_game.unknown5);
    out.writeField(Fields::kArtifactMerchants, saved_game.artifact_merchants);
    out.writeField(Fields::kUnknown6, saved_game.unknown6);
    out.writeField(Fields::kKeymastersTents, saved_game.keymasters_tents);
    out.writeField(Fields::kUnknown7, saved_game.unknown7);
    out.writeField(Fields::kCartographers, saved_game.cartographers);
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
    out.writeField(Fields::kPreviousTurn, saved_game.previous_turn);
  }

  template<>
  void JsonObjectWriter<h3svg::Tile::ObjectToRender>::operator()(
    FieldsWriter& out, const h3svg::Tile::ObjectToRender& object_to_render) const
  {
    out.writeField("object_idx", object_to_render.object_idx);
    out.writeField("unknown", object_to_render.unknown);
  }

  template<>
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

  template<>
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
