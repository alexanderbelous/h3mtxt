#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <limits>
#include <optional>
#include <type_traits>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::EnumIndexedArray<h3m::ArtifactType, h3m::Bool, 144>>::operator()(
    FieldsWriter& out, const h3m::EnumIndexedArray<h3m::ArtifactType, h3m::Bool, 144>& boolmask) const
  {
    // Reuse the names of fields for ArtifactsBitmask.
    static constexpr std::span<const std::string_view, 144> kFieldsNames =
      h3m::FieldNames<h3m::ArtifactsBitmask>::kNames;

    for (std::size_t i = 0; i < boolmask.data.size(); ++i)
    {
      out.writeField(kFieldsNames[i], boolmask.data[i]);
    }
  }

  void JsonObjectWriter<h3m::EnumIndexedArray<h3m::SecondarySkillType, h3m::Bool, 28>>::operator()(
    FieldsWriter& out, const h3m::EnumIndexedArray<h3m::SecondarySkillType, h3m::Bool, 28>& boolmask) const
  {
    // Reuse the names of fields for SecondarySkillsBitmask.
    static constexpr std::span<const std::string_view, 32> kFieldsNames =
      h3m::FieldNames<h3m::SecondarySkillsBitmask>::kNames;

    for (std::size_t i = 0; i < boolmask.data.size(); ++i)
    {
      out.writeField(kFieldsNames[i], boolmask.data[i]);
    }
  }

  void JsonObjectWriter<h3m::EnumIndexedArray<h3m::PlayerColor, h3m::PlayerControlType, h3m::kMaxPlayers>>::operator()(
    FieldsWriter& out,
    const h3m::EnumIndexedArray<h3m::PlayerColor, h3m::PlayerControlType, h3m::kMaxPlayers>& players_control) const
  {
    // Reuse the names of fields for PlayersBitmask.
    static constexpr const std::array<std::string_view, h3m::kMaxPlayers>& kFieldsNames =
      h3m::FieldNames<h3m::PlayersBitmask>::kNames;

    for (std::size_t player_idx = 0; player_idx < players_control.data.size(); ++player_idx)
    {
      const h3m::PlayerControlType player_control = players_control.data[player_idx];
      out.writeField(kFieldsNames[player_idx], player_control);
      if (std::string_view enum_str = h3m::getEnumString(player_control); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3m::EnumIndexedArray<h3m::PlayerColor, h3m::TownType32, h3m::kMaxPlayers>>::operator()(
    FieldsWriter& out,
    const h3m::EnumIndexedArray<h3m::PlayerColor, h3m::TownType32, h3m::kMaxPlayers>& alignments) const
  {
    // Reuse the names of fields for PlayersBitmask.
    static constexpr const std::array<std::string_view, h3m::kMaxPlayers>& kFieldsNames =
      h3m::FieldNames<h3m::PlayersBitmask>::kNames;

    for (std::size_t player_idx = 0; player_idx < alignments.data.size(); ++player_idx)
    {
      const h3m::TownType32 alignment = alignments.data[player_idx];
      out.writeField(kFieldsNames[player_idx], alignment);
      if (std::string_view enum_str = h3m::getEnumString(alignment); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3m::Coordinates>::operator()(FieldsWriter& out, const h3m::Coordinates& coordinates) const
  {
    using Fields = h3m::FieldNames<h3m::Coordinates>;
    out.writeField(Fields::kX, coordinates.x);
    out.writeField(Fields::kY, coordinates.y);
    out.writeField(Fields::kZ, coordinates.z);
  }

  void JsonObjectWriter<h3m::PlayerSpecsSvg>::operator()(FieldsWriter& out, const h3m::PlayerSpecsSvg& player) const
  {
    using Fields = h3m::FieldNames<h3m::PlayerSpecsSvg>;

    out.writeField(Fields::kCanBeHuman, player.can_be_human);
    out.writeField(Fields::kCanBeComputer, player.can_be_computer);
    out.writeField(Fields::kBehavior, player.behavior);
    if (auto enum_str = h3m::getEnumString(player.behavior); !enum_str.empty())
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

  void JsonArrayWriter<std::array<h3m::PlayerSpecsSvg, h3m::kMaxPlayers>>::operator()(
    const ArrayElementsWriter& out,
    const std::array<h3m::PlayerSpecsSvg, h3m::kMaxPlayers>& players) const
  {
    h3m::H3JsonWriter_NS::CommentBuilder comment_builder;
    for (std::size_t i = 0; i < h3m::kMaxPlayers; ++i)
    {
      const h3m::PlayerColor player = static_cast<h3m::PlayerColor>(i);
      const std::string_view player_str = h3m::getEnumString(player);
      out.writeComment(comment_builder.build({ "Player ", i, " (", player_str, ")" }));
      out.writeElement(players[i]);
    }
  }

  void JsonObjectWriter<h3m::RumorSvg>::operator()(FieldsWriter& out, const h3m::RumorSvg& rumor) const
  {
    using Fields = h3m::FieldNames<h3m::RumorSvg>;
    out.writeField(Fields::kText, rumor.text);
    out.writeField(Fields::kHasBeenShown, rumor.has_been_shown);
  }

  void JsonArrayWriter<h3m::BlackMarket>::operator()(const ArrayElementsWriter& out, const h3m::BlackMarket& black_market) const
  {
    for (h3m::ArtifactType32 artifact : black_market.artifacts)
    {
      out.writeElement(artifact);
      if (std::string_view enum_str = h3m::getEnumString(artifact); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3m::ObjectSvg>::operator()(FieldsWriter& out, const h3m::ObjectSvg& object) const
  {
    using Fields = h3m::FieldNames<h3m::ObjectSvg>;
    out.writeField(Fields::kCoordinates, object.coordinates);
    out.writeField(Fields::kTemplateIdx, object.template_idx);
  }

  void JsonObjectWriter<h3m::ObjectTemplateSvg>::operator()(FieldsWriter& out,
                                                              const h3m::ObjectTemplateSvg& object_template) const
  {
    using Fields = h3m::FieldNames<h3m::ObjectTemplateSvg>;
    out.writeField(Fields::kDef, object_template.def);
    out.writeField(Fields::kWidth, object_template.width);
    out.writeField(Fields::kHeight, object_template.height);
    out.writeField(Fields::kUnknown1, object_template.unknown1);
    out.writeField(Fields::kPassability, object_template.passability);
    out.writeField(Fields::kUnknown2, object_template.unknown2);
    out.writeField(Fields::kActionability, object_template.actionability);
    out.writeField(Fields::kObjectClass, object_template.object_class);
    if (std::string_view enum_str = h3m::getEnumString(static_cast<h3m::ObjectClass>(object_template.object_class));
        !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, object_template.object_subclass);
    out.writeField(Fields::kReserved, object_template.reserved);
    out.writeField(Fields::kIsGround, object_template.is_ground);
  }

  void JsonObjectWriter<h3m::SavedGame>::operator()(FieldsWriter& out, const h3m::SavedGame& saved_game) const
  {
    using Fields = h3m::FieldNames<h3m::SavedGame>;

    out.writeField(Fields::kReserved1, saved_game.reserved1);
    out.writeField(Fields::kVersionMajor, saved_game.version_major);
    out.writeField(Fields::kVersionMinor, saved_game.version_minor);
    out.writeField(Fields::kReserved2, saved_game.reserved2);
    out.writeField(Fields::kFormat, saved_game.format);
    out.writeField(Fields::kBasicInfo, saved_game.basic_info);
    out.writeField(Fields::kPlayers, saved_game.players);
    out.writeField(Fields::kVictoryCondition, saved_game.victory_condition);
    out.writeField(Fields::kLossCondition, saved_game.loss_condition);
    out.writeField(Fields::kTeams, saved_game.teams);
    out.writeField(Fields::kCustomHeroes, saved_game.custom_heroes);
    out.writeField(Fields::kUnknown1, saved_game.unknown1);
    out.writeField(Fields::kAlignments, saved_game.alignments);
    out.writeField(Fields::kUnknown2, saved_game.unknown2);
    // TODO: it sucks that we serialize this as a JSON array rather than a string.
    // Consider serializing as a string, escaping unprintable characters.
    out.writeField(Fields::kMapFilename, saved_game.map_filename);
    // TODO: consider serializing as a string rather than a JSON array,
    //       escaping unprintable characters.
    out.writeField(Fields::kMapDirectory, saved_game.map_directory);
    out.writeField(Fields::kPlayersControl, saved_game.players_control);
    out.writeField(Fields::kUnknown3, saved_game.unknown3);
    // TODO: consider serializing as a string.
    out.writeField(Fields::kOriginalFilename, saved_game.original_filename);
    out.writeField(Fields::kUnknown4, saved_game.unknown4);
    out.writeField(Fields::kDisabledArtifacts, saved_game.disabled_artifacts);
    out.writeField(Fields::kArtifactsBitmaskUnknown, saved_game.artifacts_bitmask_unknown);
    out.writeField(Fields::kDisabledSkills, saved_game.disabled_skills);
    out.writeField(Fields::kCurrentRumor, saved_game.current_rumor);
    out.writeField(Fields::kUnknown5, saved_game.unknown5);
    out.writeField(Fields::kRumors, saved_game.rumors);
    out.writeField(Fields::kBlackMarkets, saved_game.black_markets);
    // TODO: print the coordinates in a comment for each tile.
    out.writeField(Fields::kTiles, saved_game.tiles);
    // TODO: print the 0-based index for each element
    out.writeField(Fields::kObjectsTemplates, saved_game.objects_templates);
    out.writeField(Fields::kObjects, saved_game.objects);
  }

  template<>
  void JsonObjectWriter<h3m::TileSvg::ObjectToRender>::operator()(FieldsWriter& out,
                                                                  const h3m::TileSvg::ObjectToRender& object_to_render) const
  {
    out.writeField("object_idx", object_to_render.object_idx);
    out.writeField("unknown", object_to_render.unknown);
  }

  void JsonObjectWriter<h3m::TileSvg>::operator()(FieldsWriter& out, const h3m::TileSvg& tile) const
  {
    using Fields = h3m::FieldNames<h3m::TileSvg>;
    out.writeField(Fields::kTerrainType, tile.terrain_type);
    if (std::string_view enum_str = h3m::getEnumString(tile.terrain_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kTerrainSprite, tile.terrain_sprite);
    out.writeField(Fields::kRiverType, tile.river_type);
    if (std::string_view enum_str = h3m::getEnumString(tile.river_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRiverSprite, tile.river_sprite);
    out.writeField(Fields::kRoadType, tile.road_type);
    if (std::string_view enum_str = h3m::getEnumString(tile.road_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRoadSprite, tile.road_sprite);
    out.writeField(Fields::kFlags1, tile.flags1);
    out.writeField(Fields::kFlags2, tile.flags2);
    out.writeField(Fields::kObjectClass, tile.object_class);
    if (std::string_view enum_str = h3m::getEnumString(static_cast<h3m::ObjectClass>(tile.object_class)); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, tile.object_subclass);
    out.writeField(Fields::kObjectIdx, tile.object_idx);
    out.writeField(Fields::kUnknown, tile.unknown);
    out.writeField(Fields::kObjectsToRender, tile.objects_to_render);
  }
}
