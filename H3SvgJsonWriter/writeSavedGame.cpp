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
    struct TilesSvgWithMapSize
    {
      std::span<const h3m::TileSvg> tiles;
      std::uint32_t map_size {};
      bool has_two_levels {};
    };
  }

  // Serialize TilesSvgWithMapSize as a JSON array.
  template<>
  void JsonArrayWriter<TilesSvgWithMapSize>::operator()(const ArrayElementsWriter& out,
                                                        const TilesSvgWithMapSize& value) const
  {
    const std::size_t num_levels = value.has_two_levels ? 2 : 1;
    const std::size_t expected_num_tiles = num_levels * value.map_size * value.map_size;
    if (value.tiles.size() != expected_num_tiles)
    {
      // Strictly speaking, this is an error - the number of tiles should match expected_num_tiles.
      // However, this is only an error for H3SVG - we can still serialize such arrays of tiles as
      // JSON. We cannot reliably print coordinates though.
      for (const h3m::TileSvg& tile : value.tiles)
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

  void JsonObjectWriter<h3m::ArtifactSvg>::operator()(FieldsWriter& out, const h3m::ArtifactSvg& artifact) const
  {
    using Fields = h3m::FieldNames<h3m::ArtifactSvg>;
    out.writeField(Fields::kGuardians, artifact.guardians);
  }

  void JsonObjectWriter<h3m::DwellingSvg>::operator()(FieldsWriter& out, const h3m::DwellingSvg& dwelling) const
  {
    using Fields = h3m::FieldNames<h3m::DwellingSvg>;
    out.writeField(Fields::kOwner, dwelling.owner);
    if (std::string_view enum_str = h3m::getEnumString(dwelling.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectClass, dwelling.object_class);
    out.writeField(Fields::kObjectSubclass, dwelling.object_subclass);
    out.writeField(Fields::kCreatureTypes, dwelling.creature_types);
    out.writeField(Fields::kCreatureCounts, dwelling.creature_counts);
    out.writeField(Fields::kCoordinates, dwelling.coordinates);
    out.writeField(Fields::kGuardians, dwelling.guardians);
    out.writeField(Fields::kUnknown, dwelling.unknown);
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

  void JsonObjectWriter<h3m::GarrisonSvg>::operator()(FieldsWriter& out, const h3m::GarrisonSvg& garrison) const
  {
    using Fields = h3m::FieldNames<h3m::GarrisonSvg>;
    out.writeField(Fields::kOwner, garrison.owner);
    if (std::string_view enum_str = h3m::getEnumString(garrison.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kCreatures, garrison.creatures);
    out.writeField(Fields::kCoordinates, garrison.coordinates);
    out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
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

  void JsonObjectWriter<h3m::MineSvg>::operator()(FieldsWriter& out, const h3m::MineSvg& mine) const
  {
    using Fields = h3m::FieldNames<h3m::MineSvg>;
    out.writeField(Fields::kOwner, mine.owner);
    if (std::string_view enum_str = h3m::getEnumString(mine.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, mine.unknown);
    out.writeField(Fields::kCreatures, mine.creatures);
    out.writeField(Fields::kCoordinates, mine.coordinates);
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
    out.writeField(Fields::kVisitedBy, quest_guard.visited_by);
  }

  void JsonObjectWriter<h3m::SeersHutSvg>::operator()(FieldsWriter& out, const h3m::SeersHutSvg& seers_hut) const
  {
    using Fields = h3m::FieldNames<h3m::SeersHutSvg>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kUnknown1, seers_hut.unknown1);
    out.writeField(Fields::kVisitedBy, seers_hut.visited_by);
    out.writeField(Fields::kUnknown2, seers_hut.unknown2);
  }

  void JsonObjectWriter<h3m::SignSvg>::operator()(FieldsWriter& out, const h3m::SignSvg& sign) const
  {
    using Fields = h3m::FieldNames<h3m::SignSvg>;
    out.writeField(Fields::kMessage, sign.message);
    out.writeField(Fields::kIsCustom, sign.is_custom);
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

  void JsonObjectWriter<h3m::TownEventSvg>::operator()(FieldsWriter& out, const h3m::TownEventSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::TownEventSvg>;
    JsonObjectWriter<h3m::TimedEventSvg>{}(out, event);
    out.writeField(Fields::kUnknown1, event.unknown1);
    out.writeField(Fields::kBuildings, event.buildings);
    out.writeField(Fields::kUnknown2, event.unknown2);
    out.writeField(Fields::kCreatures, event.creatures);
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
                   TilesSvgWithMapSize{
                     .tiles = saved_game.tiles,
                     .map_size = saved_game.basic_info.map_size,
                     .has_two_levels = static_cast<bool>(saved_game.basic_info.has_two_levels)
                   });
    // TODO: print the 0-based index for each element
    out.writeField(Fields::kObjectsTemplates, saved_game.objects_templates);
    out.writeField(Fields::kObjects, saved_game.objects);
    out.writeField(Fields::kEventsAndPandorasBoxes, saved_game.events_and_pandoras_boxes);
    out.writeField(Fields::kArtifactsAndSpellScrolls, saved_game.artifacts_and_spell_scrolls);
    out.writeField(Fields::kMonsters, saved_game.monsters);
    out.writeField(Fields::kSeersHuts, saved_game.seers_huts);
    out.writeField(Fields::kQuestGuards, saved_game.quest_guards);
    out.writeField(Fields::kGlobalEvents, saved_game.global_events);
    out.writeField(Fields::kTownEvents, saved_game.town_events);
    out.writeField(Fields::kSignsAndOceanBottles, saved_game.signs_and_ocean_bottles);
    out.writeField(Fields::kMinesAndLighthouses, saved_game.mines_and_lighthouses);
    out.writeField(Fields::kDwellings, saved_game.dwellings);
    out.writeField(Fields::kGarrisons, saved_game.garrisons);
  }

  void JsonObjectWriter<h3m::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3m::ScenarioStartingInfo& starting_info) const
  {
    using Fields = h3m::FieldNames<h3m::ScenarioStartingInfo>;

    out.writeField(Fields::kStartingTowns, starting_info.starting_towns);
    out.writeField(Fields::kUnknown1, starting_info.unknown1);
    out.writeField(Fields::kDifficulty, starting_info.difficulty);
    if (std::string_view enum_str = h3m::getEnumString(starting_info.difficulty); !enum_str.empty())
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
    if (std::string_view enum_str = h3m::getEnumString(starting_info.player_turn_duration); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kStartingHeroes, starting_info.starting_heroes);
    out.writeField(Fields::kStartingBonuses, starting_info.starting_bonuses);
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
    if (std::string_view enum_str = h3m::getEnumString(tile.object_class); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectSubclass, tile.object_subclass);
    out.writeField(Fields::kObjectIdx, tile.object_idx);
    out.writeField(Fields::kObjectProperties, tile.object_properties);
    out.writeField(Fields::kObjectsToRender, tile.objects_to_render);
  }

  void JsonObjectWriter<h3m::TroopsSvg>::operator()(FieldsWriter& out, const h3m::TroopsSvg& troops) const
  {
    using Fields = h3m::FieldNames<h3m::TroopsSvg>;
    out.writeField(Fields::kCreatureTypes, troops.creature_types);
    out.writeField(Fields::kCreatureCounts, troops.creature_counts);
  }
}
