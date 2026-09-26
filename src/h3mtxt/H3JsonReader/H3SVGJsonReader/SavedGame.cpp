#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

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
  h3svg::CoordinatesPacked JsonReader<h3svg::CoordinatesPacked>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::CoordinatesPacked>;

    const auto readFieldSafe = [&value](std::string_view field_name,
                                        std::int16_t bound_lower, std::int16_t bound_upper)
      {
        const std::int16_t field_value = readField<std::int16_t>(value, field_name);
        if (field_value < bound_lower || field_value > bound_upper)
        {
          throw std::runtime_error("JsonReader<h3svg::CoordinatesPacked>: field \"" +
                                   std::string{ field_name } + "\" is out of range.");
        }
        return field_value;
      };

    return h3svg::CoordinatesPacked{
      .x = readFieldSafe(Fields::kX, -512, 511),
      .padding1 = readFieldSafe(Fields::kPadding1, -32, 31),
      .y = readFieldSafe(Fields::kY, -512, 511),
      .z = readFieldSafe(Fields::kZ, -8, 7),
      .padding2 = readFieldSafe(Fields::kPadding2, -2, 1)
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
  h3svg::ObjectTemplate JsonReader<h3svg::ObjectTemplate>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectTemplate>;
    h3svg::ObjectTemplate object_template;
    readField(object_template.def, value, Fields::kDef);
    readField(object_template.width, value, Fields::kWidth);
    readField(object_template.height, value, Fields::kHeight);
    readField(object_template.unknown1, value, Fields::kUnknown1);
    readField(object_template.passability, value, Fields::kPassability);
    readField(object_template.unknown2, value, Fields::kUnknown2);
    readField(object_template.actionability, value, Fields::kActionability);
    readField(object_template.object_class, value, Fields::kObjectClass);
    readField(object_template.object_subclass, value, Fields::kObjectSubclass);
    readField(object_template.reserved, value, Fields::kReserved);
    readField(object_template.is_ground, value, Fields::kIsGround);
    return object_template;
  }

  template<>
  h3svg::PlayerSpecs JsonReader<h3svg::PlayerSpecs>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::PlayerSpecs>;
    h3svg::PlayerSpecs player;
    readField(player.can_be_human, value, Fields::kCanBeHuman);
    readField(player.can_be_computer, value, Fields::kCanBeComputer);
    readField(player.behavior, value, Fields::kBehavior);
    readField(player.allowed_alignments, value, Fields::kAllowedAlignments);
    readField(player.allow_random_alignment, value, Fields::kAllowRandomAlignment);
    readField(player.generated_hero_coordinates, value, Fields::kGeneratedHeroCoordinates);
    readField(player.starting_hero, value, Fields::kStartingHero);
    return player;
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
    readField(saved_game.grail_x, value, Fields::kGrailX);
    readField(saved_game.grail_y, value, Fields::kGrailY);
    readField(saved_game.grail_z, value, Fields::kGrailZ);
    readField(saved_game.unknown4a, value, Fields::kUnknown4a);
    readField(saved_game.is_cheater, value, Fields::kIsCheater);
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

  // TODO: move the declaration to H3SVGJsonReader.h (requires unnesting Tile::ObjectToRender).
  template<>
  h3svg::Tile::ObjectToRender JsonReader<h3svg::Tile::ObjectToRender>::operator()(const Json::Value & value) const
  {
    h3svg::Tile::ObjectToRender object_to_render;
    readField(object_to_render.object_idx, value, "object_idx");
    readField(object_to_render.unknown, value, "unknown");
    return object_to_render;
  }

  template<>
  h3svg::Tile JsonReader<h3svg::Tile>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Tile>;
    h3svg::Tile tile;
    readField(tile.terrain_type, value, Fields::kTerrainType);
    readField(tile.terrain_sprite, value, Fields::kTerrainSprite);
    readField(tile.river_type, value, Fields::kRiverType);
    readField(tile.river_sprite, value, Fields::kRiverSprite);
    readField(tile.road_type, value, Fields::kRoadType);
    readField(tile.road_sprite, value, Fields::kRoadSprite);
    readField(tile.flags1, value, Fields::kFlags1);
    readField(tile.flags2, value, Fields::kFlags2);
    readField(tile.object_class, value, Fields::kObjectClass);
    readField(tile.object_subclass, value, Fields::kObjectSubclass);
    readField(tile.object_idx, value, Fields::kObjectIdx);
    readField(tile.object_properties, value, Fields::kObjectProperties);
    readField(tile.objects_to_render, value, Fields::kObjectsToRender);
    return tile;
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
  h3svg::Troops JsonReader<h3svg::Troops>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Troops>;
    h3svg::Troops troops;
    readField(troops.creature_types, value, Fields::kCreatureTypes);
    readField(troops.creature_counts, value, Fields::kCreatureCounts);
    return troops;
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
