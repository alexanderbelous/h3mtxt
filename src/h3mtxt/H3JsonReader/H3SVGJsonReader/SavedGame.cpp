#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/SavedGame.h>

namespace h3json
{
  template<>
  h3svg::ArtifactMerchants JsonReader<h3svg::ArtifactMerchants>::operator()(const Json::Value& value) const
  {
    return h3svg::ArtifactMerchants{
      .artifacts = fromJson<std::array<h3svg::ArtifactType32, h3svg::ArtifactMerchants::kNumSlots>>(value)
    };
  }

  template<>
  h3svg::CreatureBank JsonReader<h3svg::CreatureBank>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::CreatureBank>;
    h3svg::CreatureBank creature_bank;
    readField(creature_bank.guards, value, Fields::kGuards);
    readField(creature_bank.resources, value, Fields::kResources);
    readField(creature_bank.creatures, value, Fields::kCreatures);
    readField(creature_bank.artifacts, value, Fields::kArtifacts);
    return creature_bank;
  }

  template<>
  h3svg::Date JsonReader<h3svg::Date>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Date>;
    h3svg::Date date;
    readField(date.month, value, Fields::kMonth);
    readField(date.week, value, Fields::kWeek);
    readField(date.day, value, Fields::kDay);
    return date;
  }

  template<>
  h3svg::Object JsonReader<h3svg::Object>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Object>;
    h3svg::Object object;
    readField(object.coordinates, value, Fields::kCoordinates);
    readField(object.template_idx, value, Fields::kTemplateIdx);
    return object;
  }

  template<>
  h3svg::ObjectExits JsonReader<h3svg::ObjectExits>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    h3svg::ObjectExits object_exits;
    readField(object_exits.exits, value, Fields::kExits);
    return object_exits;
  }

  template<>
  h3svg::Rumor JsonReader<h3svg::Rumor>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Rumor>;
    h3svg::Rumor rumor;
    readField(rumor.text, value, Fields::kText);
    readField(rumor.has_been_shown, value, Fields::kHasBeenShown);
    return rumor;
  }


  template<>
  h3svg::SavedGame JsonReader<h3svg::SavedGame>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::SavedGame>;

    h3svg::SavedGame saved_game;
    readField(saved_game.signature, value, Fields::kSignature);
    readField(saved_game.reserved1, value, Fields::kReserved1);
    readField(saved_game.version_major, value, Fields::kVersionMajor);
    readField(saved_game.version_minor, value, Fields::kVersionMinor);
    readField(saved_game.reserved2, value, Fields::kReserved2);
    readField(saved_game.format, value, Fields::kFormat);
    readField(saved_game.basic_info, value, Fields::kBasicInfo);
    readField(saved_game.players_specs, value, Fields::kPlayersSpecs);
    readField(saved_game.victory_condition, value, Fields::kVictoryCondition);
    readField(saved_game.loss_condition, value, Fields::kLossCondition);
    readField(saved_game.teams, value, Fields::kTeams);
    readField(saved_game.custom_heroes, value, Fields::kCustomHeroes);
    readField(saved_game.unknown1, value, Fields::kUnknown1);
    readField(saved_game.starting_info, value, Fields::kStartingInfo);
    readField(saved_game.original_filename, value, Fields::kOriginalFilename);
    readField(saved_game.unknown2, value, Fields::kUnknown2);
    readField(saved_game.disabled_artifacts, value, Fields::kDisabledArtifacts);
    readField(saved_game.artifacts_bitmask_unknown, value, Fields::kArtifactsBitmaskUnknown);
    readField(saved_game.disabled_skills, value, Fields::kDisabledSkills);
    readField(saved_game.current_rumor, value, Fields::kCurrentRumor);
    readField(saved_game.unknown3, value, Fields::kUnknown3);
    readField(saved_game.rumors, value, Fields::kRumors);
    readField(saved_game.black_markets, value, Fields::kBlackMarkets);
    readField(saved_game.tiles, value, Fields::kTiles);
    readField(saved_game.objects_templates, value, Fields::kObjectsTemplates);
    readField(saved_game.objects, value, Fields::kObjects);
    readField(saved_game.object_properties_tables, value, Fields::kObjectPropertiesTables);
    readField(saved_game.players, value, Fields::kPlayers);
    readField(saved_game.towns, value, Fields::kTowns);
    readField(saved_game.heroes, value, Fields::kHeroes);
    readField(saved_game.unknown4, value, Fields::kUnknown4);
    readField(saved_game.current_date, value, Fields::kCurrentDate);
    readField(saved_game.unknown5, value, Fields::kUnknown5);
    readField(saved_game.artifact_merchants, value, Fields::kArtifactMerchants);
    readField(saved_game.unknown6, value, Fields::kUnknown6);
    readField(saved_game.keymasters_tents, value, Fields::kKeymastersTents);
    readField(saved_game.unknown7, value, Fields::kUnknown7);
    readField(saved_game.cartographers, value, Fields::kCartographers);
    readField(saved_game.unknown8, value, Fields::kUnknown8);
    readField(saved_game.fog_of_war, value, Fields::kFogOfWar);
    readField(saved_game.monoliths_two_way, value, Fields::kMonolithsTwoWay);
    readField(saved_game.monoliths_one_way, value, Fields::kMonolithsOneWay);
    readField(saved_game.whirlpools, value, Fields::kWhirlpools);
    readField(saved_game.subterranean_gates, value, Fields::kSubterraneanGates);
    readField(saved_game.unknown9, value, Fields::kUnknown9);
    readField(saved_game.universities, value, Fields::kUniversities);
    readField(saved_game.creature_banks, value, Fields::kCreatureBanks);
    readField(saved_game.previous_turn, value, Fields::kPreviousTurn);
    return saved_game;
  }

  template<>
  h3svg::TileVisibility JsonReader<h3svg::TileVisibility>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::TileVisibility>;
    h3svg::TileVisibility tile_visibility;
    readField(tile_visibility.visibility, value, Fields::kVisibility);
    readField(tile_visibility.has_adjacent_monster, value, Fields::kHasAdjacentMonster);
    return tile_visibility;
  }

  template<>
  h3svg::University JsonReader<h3svg::University>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::University>;
    h3svg::University university;
    readField(university.skills, value, Fields::kSkills);
    return university;
  }
}
