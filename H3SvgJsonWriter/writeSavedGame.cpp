#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

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
  void JsonObjectWriter<h3m::ArtifactSvg>::operator()(FieldsWriter& out, const h3m::ArtifactSvg& artifact) const
  {
    using Fields = h3m::FieldNames<h3m::ArtifactSvg>;
    out.writeField(Fields::kGuardians, artifact.guardians);
  }

  void JsonObjectWriter<h3m::EventBaseSvg>::operator()(FieldsWriter& out, const h3m::EventBaseSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::EventBaseSvg>;
    if (event.guardians)
    {
      out.writeField(Fields::kGuardians, *event.guardians);
    }
    out.writeField(Fields::kExperience, event.experience);
    out.writeField(Fields::kSpellPoints, event.spell_points);
    out.writeField(Fields::kMorale, event.morale);
    out.writeField(Fields::kLuck, event.luck);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kPrimarySkills, event.primary_skills);
    out.writeField(Fields::kSecondarySkills, event.secondary_skills);
    out.writeField(Fields::kArtifacts, event.artifacts);
    out.writeField(Fields::kSpells, event.spells);
    out.writeField(Fields::kCreatures, event.creatures);
  }

  void JsonObjectWriter<h3m::GuardiansSvg>::operator()(FieldsWriter& out, const h3m::GuardiansSvg& guardians) const
  {
    using Fields = h3m::FieldNames<h3m::GuardiansSvg>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
  }

  void JsonObjectWriter<h3m::MonsterSvg>::operator()(FieldsWriter& out, const h3m::MonsterSvg& monster) const
  {
    using Fields = h3m::FieldNames<h3m::MonsterSvg>;
    out.writeField(Fields::kMessage, monster.message);
    out.writeField(Fields::kResources, monster.resources);
    out.writeField(Fields::kArtifact, monster.artifact);
    if (std::string_view enum_str = h3m::getEnumString(monster.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
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

  void JsonObjectWriter<h3m::QuestGuardSvg>::operator()(FieldsWriter& out,
                                                          const h3m::QuestGuardSvg& quest_guard) const
  {
    using Fields = h3m::FieldNames<h3m::QuestGuardSvg>;
    out.writeField(Fields::kQuest, quest_guard.quest);
    out.writeField(Fields::kUnknown, quest_guard.unknown);
  }

  void JsonObjectWriter<h3m::SeersHutSvg>::operator()(FieldsWriter& out, const h3m::SeersHutSvg& seers_hut) const
  {
    using Fields = h3m::FieldNames<h3m::SeersHutSvg>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kUnknown, seers_hut.unknown);
  }

  void JsonObjectWriter<h3m::TimedEventSvg>::operator()(FieldsWriter& out,
                                                        const h3m::TimedEventSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::TimedEventSvg>;
    out.writeField(Fields::kMessage, event.message);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToHuman, event.applies_to_human);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    out.writeField(Fields::kRepeatAfterDays, event.repeat_after_days);
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
    out.writeField(Fields::kPlayerTurnDuration, saved_game.player_turn_duration);
    if (std::string_view enum_str = h3m::getEnumString(saved_game.player_turn_duration); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kStartingHeroes, saved_game.starting_heroes);
    out.writeField(Fields::kStartingBonuses, saved_game.starting_bonuses);
    out.writeField(Fields::kUnknown4, saved_game.unknown4);
    // TODO: consider serializing as a string.
    out.writeField(Fields::kOriginalFilename, saved_game.original_filename);
    out.writeField(Fields::kUnknown5, saved_game.unknown5);
    out.writeField(Fields::kDisabledArtifacts, saved_game.disabled_artifacts);
    out.writeField(Fields::kArtifactsBitmaskUnknown, saved_game.artifacts_bitmask_unknown);
    out.writeField(Fields::kDisabledSkills, saved_game.disabled_skills);
    out.writeField(Fields::kCurrentRumor, saved_game.current_rumor);
    out.writeField(Fields::kUnknown6, saved_game.unknown6);
    out.writeField(Fields::kRumors, saved_game.rumors);
    out.writeField(Fields::kBlackMarkets, saved_game.black_markets);
    // TODO: print the coordinates in a comment for each tile.
    out.writeField(Fields::kTiles, saved_game.tiles);
    // TODO: print the 0-based index for each element
    out.writeField(Fields::kObjectsTemplates, saved_game.objects_templates);
    out.writeField(Fields::kObjects, saved_game.objects);
    out.writeField(Fields::kEventsAndPandorasBoxes, saved_game.events_and_pandoras_boxes);
    out.writeField(Fields::kArtifactsAndSpellScrolls, saved_game.artifacts_and_spell_scrolls);
    out.writeField(Fields::kMonsters, saved_game.monsters);
    out.writeField(Fields::kSeersHuts, saved_game.seers_huts);
    out.writeField(Fields::kQuestGuards, saved_game.quest_guards);
    out.writeField(Fields::kGlobalEvents, saved_game.global_events);
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

  void JsonObjectWriter<h3m::TroopsSvg>::operator()(FieldsWriter& out, const h3m::TroopsSvg& troops) const
  {
    using Fields = h3m::FieldNames<h3m::TroopsSvg>;
    out.writeField(Fields::kCreatureTypes, troops.creature_types);
    out.writeField(Fields::kCreatureCounts, troops.creature_counts);
  }
}
