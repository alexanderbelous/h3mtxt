#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3JsonWriter/CommentBuilder.h>
#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/SavedGame.h>

namespace Medea_NS
{
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
    out.writeField(Fields::kUnknown, player.unknown);
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
    out.writeField(Fields::kUnknown2, saved_game.unknown2);
    out.writeField(Fields::kMapFilename, saved_game.map_filename);
  }
}
