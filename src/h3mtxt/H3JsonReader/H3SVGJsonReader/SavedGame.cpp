#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonReader/H3SVGJsonReader/FixedLengthString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/SavedGame.h>

namespace h3json
{
  template<>
  h3svg::ArtifactMerchants JsonReader2<h3svg::ArtifactMerchants>::operator()() const
  {
    return h3svg::ArtifactMerchants{
      .artifacts = fromJson<std::array<h3svg::ArtifactType32, h3svg::ArtifactMerchants::kNumSlots>>(value())
    };
  }

  template<>
  h3svg::CoordinatesPacked JsonReader2<h3svg::CoordinatesPacked>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::CoordinatesPacked>;

    return h3svg::CoordinatesPacked{
      .x = readBitField<std::int16_t, 10>(value(), Fields::kX),
      .padding1 = readBitField<std::int16_t, 6>(value(), Fields::kPadding1),
      .y = readBitField<std::int16_t, 10>(value(), Fields::kY),
      .z = readBitField<std::int16_t, 4>(value(), Fields::kZ),
      .padding2 = readBitField<std::int16_t, 2>(value(), Fields::kPadding2)
    };
  }

  template<>
  h3svg::CreatureBank JsonReader2<h3svg::CreatureBank>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::CreatureBank>;
    h3svg::CreatureBank creature_bank;
    readField(Fields::kGuards, creature_bank.guards);
    readField(Fields::kResources, creature_bank.resources);
    readField(Fields::kCreatures, creature_bank.creatures);
    readField(Fields::kArtifacts, creature_bank.artifacts);
    return creature_bank;
  }

  template<>
  h3svg::Date JsonReader2<h3svg::Date>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Date>;
    h3svg::Date date;
    readField(Fields::kMonth, date.month);
    readField(Fields::kWeek, date.week);
    readField(Fields::kDay, date.day);
    return date;
  }

  template<>
  h3svg::Object JsonReader2<h3svg::Object>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Object>;
    h3svg::Object object;
    readField(Fields::kCoordinates, object.coordinates);
    readField(Fields::kTemplateIdx, object.template_idx);
    return object;
  }

  template<>
  h3svg::ObjectTemplate JsonReader2<h3svg::ObjectTemplate>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectTemplate>;
    h3svg::ObjectTemplate object_template;
    readField(Fields::kDef, object_template.def);
    readField(Fields::kWidth, object_template.width);
    readField(Fields::kHeight, object_template.height);
    readField(Fields::kColors, object_template.colors);
    readField(Fields::kPassability, object_template.passability);
    readField(Fields::kShadows, object_template.shadows);
    readField(Fields::kActionability, object_template.actionability);
    readField(Fields::kObjectClass, object_template.object_class);
    readField(Fields::kObjectSubclass, object_template.object_subclass);
    readField(Fields::kReserved, object_template.reserved);
    readField(Fields::kIsGround, object_template.is_ground);
    return object_template;
  }

  template<>
  h3svg::PlayerSpecs JsonReader2<h3svg::PlayerSpecs>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::PlayerSpecs>;
    h3svg::PlayerSpecs player;
    readField(Fields::kCanBeHuman, player.can_be_human);
    readField(Fields::kCanBeComputer, player.can_be_computer);
    readField(Fields::kBehavior, player.behavior);
    readField(Fields::kAllowedAlignments, player.allowed_alignments);
    readField(Fields::kAllowRandomAlignment, player.allow_random_alignment);
    readField(Fields::kGeneratedHeroCoordinates, player.generated_hero_coordinates);
    readField(Fields::kStartingHero, player.starting_hero);
    return player;
  }

  template<>
  h3svg::Rumor JsonReader2<h3svg::Rumor>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Rumor>;
    h3svg::Rumor rumor;
    readField(Fields::kText, rumor.text);
    readField(Fields::kHasBeenShown, rumor.has_been_shown);
    return rumor;
  }

  template<>
  h3svg::SavedGame JsonReader2<h3svg::SavedGame>::operator()() const
  {
    using Fields = FieldNames<h3svg::SavedGame>;

    h3svg::SavedGame saved_game;
    readField(Fields::kSignature, saved_game.signature);
    readField(Fields::kReserved1, saved_game.reserved1);
    readField(Fields::kVersionMajor, saved_game.version_major);
    readField(Fields::kVersionMinor, saved_game.version_minor);
    readField(Fields::kReserved2, saved_game.reserved2);
    readField(Fields::kFormat, saved_game.format);
    readField(Fields::kBasicInfo, saved_game.basic_info);
    readField(Fields::kPlayersSpecs, saved_game.players_specs);
    readField(Fields::kVictoryCondition, saved_game.victory_condition);
    readField(Fields::kLossCondition, saved_game.loss_condition);
    readField(Fields::kTeams, saved_game.teams);
    readField(Fields::kCustomHeroes, saved_game.custom_heroes);
    readField(Fields::kUnknown1, saved_game.unknown1);
    readField(Fields::kStartingInfo, saved_game.starting_info);
    readField(Fields::kOriginalFilename, saved_game.original_filename);
    readField(Fields::kUnknown2, saved_game.unknown2);
    readField(Fields::kDisabledArtifacts, saved_game.disabled_artifacts);
    readField(Fields::kArtifactsBitmaskUnknown, saved_game.artifacts_bitmask_unknown);
    readField(Fields::kDisabledSkills, saved_game.disabled_skills);
    readField(Fields::kCurrentRumor, saved_game.current_rumor);
    readField(Fields::kUnknown3, saved_game.unknown3);
    readField(Fields::kRumors, saved_game.rumors);
    readField(Fields::kBlackMarkets, saved_game.black_markets);
    readField(Fields::kTiles, saved_game.tiles);
    readField(Fields::kObjectsTemplates, saved_game.objects_templates);
    readField(Fields::kObjects, saved_game.objects);
    readField(Fields::kObjectPropertiesTables, saved_game.object_properties_tables);
    readField(Fields::kPlayers, saved_game.players);
    readField(Fields::kTowns, saved_game.towns);
    readField(Fields::kHeroes, saved_game.heroes);
    readField(Fields::kHeroOwner, saved_game.hero_owner);
    readField(Fields::kHeroCanBeHiredBy, saved_game.hero_can_be_hired_by);
    readField(Fields::kUnknown4, saved_game.unknown4);
    readField(Fields::kGrailX, saved_game.grail_x);
    readField(Fields::kGrailY, saved_game.grail_y);
    readField(Fields::kGrailZ, saved_game.grail_z);
    readField(Fields::kUnknown5, saved_game.unknown5);
    readField(Fields::kIsCheater, saved_game.is_cheater);
    readField(Fields::kCurrentDate, saved_game.current_date);
    readField(Fields::kUnknown6, saved_game.unknown6);
    readField(Fields::kArtifactMerchants, saved_game.artifact_merchants);
    readField(Fields::kVisitedObjects, saved_game.visited_objects);
    readField(Fields::kKeymastersTents, saved_game.keymasters_tents);
    readField(Fields::kCartographerEffects, saved_game.cartographer_effects);
    readField(Fields::kCartographerVisited, saved_game.cartographer_visited);
    readField(Fields::kUnknown7, saved_game.unknown7);
    readField(Fields::kFogOfWar, saved_game.fog_of_war);
    readField(Fields::kPortals, saved_game.portals);
    readField(Fields::kUniversities, saved_game.universities);
    readField(Fields::kCreatureBanks, saved_game.creature_banks);
    readField(Fields::kPreviousTurn, saved_game.previous_turn);
    return saved_game;
  }

  template<>
  h3svg::Tile JsonReader2<h3svg::Tile>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Tile>;
    h3svg::Tile tile;
    readField(Fields::kTerrainType, tile.terrain_type);
    readField(Fields::kTerrainSprite, tile.terrain_sprite);
    readField(Fields::kRiverType, tile.river_type);
    readField(Fields::kRiverSprite, tile.river_sprite);
    readField(Fields::kRoadType, tile.road_type);
    readField(Fields::kRoadSprite, tile.road_sprite);
    readField(Fields::kFlags, tile.flags);
    readField(Fields::kObjectSubclass, tile.object_subclass);
    readField(Fields::kObjectIdx, tile.object_idx);
    readField(Fields::kObjectProperties, tile.object_properties);
    readField(Fields::kObjectsToRender, tile.objects_to_render);
    return tile;
  }

  template<>
  h3svg::TileRenderInfo JsonReader2<h3svg::TileRenderInfo>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::TileRenderInfo>;
    h3svg::TileRenderInfo object_to_render;
    readField(Fields::kObjectIdx, object_to_render.object_idx);
    object_to_render.x = readBitField<std::uint8_t, 4>(value(), Fields::kX);
    object_to_render.y = readBitField<std::uint8_t, 4>(value(), Fields::kY);
    readField(Fields::kZBuffer, object_to_render.z_buffer);
    return object_to_render;
  }

  template<>
  h3svg::TileVisibility JsonReader2<h3svg::TileVisibility>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::TileVisibility>;
    h3svg::TileVisibility tile_visibility;
    readField(Fields::kVisibility, tile_visibility.visibility);
    readField(Fields::kHasAdjacentMonster, tile_visibility.has_adjacent_monster);
    return tile_visibility;
  }

  template<>
  h3svg::Troops JsonReader2<h3svg::Troops>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Troops>;
    h3svg::Troops troops;
    readField(Fields::kCreatureTypes, troops.creature_types);
    readField(Fields::kCreatureCounts, troops.creature_counts);
    return troops;
  }

  template<>
  h3svg::University JsonReader2<h3svg::University>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::University>;
    h3svg::University university;
    readField(Fields::kSkills, university.skills);
    return university;
  }
}
