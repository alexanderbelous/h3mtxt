#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <limits>
#include <optional>
#include <type_traits>

namespace Medea_NS
{
  namespace
  {
    // TODO: merge these safeCast...() functions into a single template.
    // It might require refactoring the enum types, though, so that negative values are handled correctly:
    // for example, if there is some
    //   enum class MyEnum : std::uint8_t
    //   {
    //     Foo = 0,
    //     Bar = 1,
    //     None = 0xFF
    //   };
    // then it's unclear which cast should succeed, and which one should fail:
    //   static_cast<MyEnum>(int32_t(-1));
    //   static_cast<MyEnum>(int32_t(255));
    //
    // In practice, almost fucking everything is signed in HoMM3 (which was a poor design choice).
    std::optional<h3m::ArtifactType> safeCastToArtifactType(std::int32_t artifact) noexcept
    {
      static_assert(std::is_same_v<std::underlying_type_t<h3m::ArtifactType>, std::uint16_t>,
                    "This function assumes that h3m::ArtifactType has uint16_t as the underlying type.");
      // Return std::nullopt if @artifact cannot be represented by a 16-bit integer.
      if (artifact < std::numeric_limits<std::int16_t>::min() ||
          artifact > std::numeric_limits<std::int16_t>::max())
      {
        return std::nullopt;
      }
      return static_cast<h3m::ArtifactType>(static_cast<std::int16_t>(artifact));
    }

    std::optional<h3m::TownType> safeCastToTownType(std::int32_t value) noexcept
    {
      using UnderlyingType = std::underlying_type_t<h3m::TownType>;
      if (value >= std::numeric_limits<UnderlyingType>::min() &&
          value <= std::numeric_limits<UnderlyingType>::max())
      {
        return static_cast<h3m::TownType>(value);
      }
      return std::nullopt;
    }
  }

  void JsonObjectWriter<h3m::EnumBoolmask<h3m::ArtifactType, 144>>::operator()(
    FieldsWriter& out, const h3m::EnumBoolmask<h3m::ArtifactType, 144>& boolmask) const
  {
    // Reuse the names of fields for ArtifactsBitmask.
    static constexpr std::span<const std::string_view, 144> kFieldsNames =
      h3m::FieldNames<h3m::ArtifactsBitmask>::kNames;

    for (std::size_t i = 0; i < boolmask.data.size(); ++i)
    {
      out.writeField(kFieldsNames[i], boolmask.data[i]);
    }
  }

  void JsonObjectWriter<h3m::EnumBoolmask<h3m::SecondarySkillType, 28>>::operator()(
    FieldsWriter& out, const h3m::EnumBoolmask<h3m::SecondarySkillType, 28>& boolmask) const
  {
    // Reuse the names of fields for SecondarySkillsBitmask.
    static constexpr std::span<const std::string_view, 32> kFieldsNames =
      h3m::FieldNames<h3m::SecondarySkillsBitmask>::kNames;

    for (std::size_t i = 0; i < boolmask.data.size(); ++i)
    {
      out.writeField(kFieldsNames[i], boolmask.data[i]);
    }
  }

  void JsonObjectWriter<h3m::Alignments>::operator()(FieldsWriter& out, const h3m::Alignments& alignments) const
  {
    using Fields = h3m::FieldNames<h3m::Alignments>;
    for (std::size_t player_idx = 0; player_idx < alignments.data.size(); ++player_idx)
    {
      const std::int32_t alignment = alignments.data[player_idx];
      out.writeField(Fields::kNames.at(player_idx), alignment);
      if (std::optional<h3m::TownType> town_type = safeCastToTownType(alignment))
      {
        if (std::string_view enum_str = h3m::getEnumString(*town_type); !enum_str.empty())
        {
          out.writeComment(enum_str, false);
        }
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
    if (player.can_be_human || player.can_be_computer)
    {
      out.writeField(Fields::kBehavior, player.behavior);
      if (auto enum_str = h3m::getEnumString(player.behavior); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
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
    for (std::int32_t artifact : black_market.artifacts)
    {
      out.writeElement(artifact);
      if (std::optional<h3m::ArtifactType> artifact_enum = safeCastToArtifactType(artifact))
      {
        if (std::string_view enum_str = h3m::getEnumString(*artifact_enum); !enum_str.empty())
        {
          out.writeComment(enum_str, false);
        }
      }
    }
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
