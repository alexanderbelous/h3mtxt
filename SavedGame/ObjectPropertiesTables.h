#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/SavedGame/Constants/SeerName.h>
#include <h3mtxt/SavedGame/EventBase.h>
#include <h3mtxt/SavedGame/Quest.h>
#include <h3mtxt/SavedGame/Reward.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace h3svg
{
  // The equivalent of ObjectProperties<ObjectPropertiesType::ARTIFACT> in H3SVG.
  // Unlike H3M, guardians are not optional here.
  struct Artifact
  {
    Guardians guardians;
  };

  // Yet another idiotic format.
  // 1) The coordinates are stored twice: first as 16-bit integers, then as a singled 32-bit integer (packed).
  // 2) The coordinates (and direction) are apparently "stale" if the boat is currently occupied by
  //    a hero - they indicate the position where the hero boarded the boat, not the current one.
  // 3) AFAIU, if the hero dies on a boat, the boat is not removed from the table.
  //
  // This is almost as bad as Tile::object_properties. Seriously, who fucking designed H3SVG?
  struct Boat
  {
    // unknown[1] seems to be the boat ID, i.e. the index of the boat in SavedGame::boats.
    // Why the fuck is it serialized at all?
    std::array<std::uint8_t, 2> unknown1 {};
    // (0 - Necropolis, 1 - Castle, 2 - Fortress)
    std::uint8_t object_sublcass {};
    // (0 - North, 2 - East, 3 - SouthEast, 7 - NorthWest, ...)
    std::uint8_t direction {};
    // 0-7 or 0xFF if no owner.
    PlayerColor owner {};
    // ~ The last hero who used this boat, or 0xFFFF if none
    std::uint16_t owner_hero {};
    // 0 if the boat exists (hasn't been scuttled) and is not boarded by a hero, 1 otherwise.
    // Not entirely sure about this one though - maybe scuttled boats are removed from the table.
    Bool is_occupied {};
    std::uint16_t x {};
    std::uint16_t y {};
    std::uint16_t z {};
    // TODO: figure out what this is.
    // Seems to duplicate the coordinates, but in the packed format.
    std::array<std::uint8_t, 14> unknown2 {};
  };

  struct Dwelling
  {
    PlayerColor owner {};
    //// CREATURE_GENERATOR1 or CREATURE_GENERATOR4
    std::uint8_t object_class {};
    std::uint8_t object_subclass {};
    // Creatures available for hire.
    std::array<std::uint8_t, 4> creature_types {};
    std::array<std::uint16_t, 4> creature_counts {};
    Coordinates coordinates;
    // Creatures guarding this dwelling.
    Troops guardians {};
    std::uint8_t unknown {};
  };

  struct Garrison
  {
    PlayerColor owner {};
    Troops creatures;
    Coordinates coordinates;
    Bool can_remove_units {};
  };

  struct Mine
  {
    PlayerColor owner {};
    // TODO: replace with something type-safe.
    // * For regular mines - stores {ResourceType, 0} (aka object_subclass of the mine).
    // * For lighthouses - stores {100, 0}.
    // * For abandoned mines - stores {ResourceType, 1}
    std::array<std::uint8_t, 2> unknown {};
    Troops creatures;
    Coordinates coordinates;
  };

  struct Monster
  {
    // Serialized in H3SVG as a length-prefixed string, with length being serialized as a 16-bit little-endian integer.
    std::string message;
    Resources resources;
    // ArtifactType or 0xFF if there is none.
    ArtifactType8 artifact {};
  };

  struct Obelisk
  {
    // 1 bit per player, indicating whether the player has visited this Obelisk.
    PlayersBitmask visited_by;
  };

  struct QuestGuard
  {
    // Note: H3SVG stores QuestType::None for completed quests.
    Quest quest;
    // 1 bit per player, indicating whether the player has visited this Quest Guard.
    PlayersBitmask visited_by;
  };

  struct SeersHut
  {
    // Note: H3SVG stores QuestType::None for completed quests.
    Quest quest;
    // Reward, on the other hand, remains unchanged for completed quests.
    Reward reward;
    // 0 by default; modifying has no effect.
    std::uint8_t reserved {};
    PlayersBitmask visited_by;
    SeerName name {};
  };

  struct Sign
  {
    std::string message;
    // 0 if a random default message should be displayed, 1 otherwise.
    // Note that in H3M an empty string implies that a random default message will be
    // displayed. However, in H3SVG this field has a higher priority - if you manually modify this
    // byte so that is_custom == 1, then some default message will be displayed even if !message.empty().
    Bool is_custom {};
  };

  // The equivalent of h3m::TimedEvent stored in the saved game.
  //
  // This is nearly identical to h3m::TimedEvent, except that `name` and `unknown` are missing.
  struct TimedEvent
  {
    std::string message;
    // Given/taken resources.
    Resources resources;
    PlayersBitmask affected_players;
    Bool applies_to_human {};
    Bool applies_to_computer {};
    // 0-based day of first occurence (e.g., 0 stands for Day 1).
    std::uint16_t day_of_first_occurence {};
    // Frequency of this event; 0 means that the event doesn't repeat.
    std::uint16_t repeat_after_days {};
  };

  // The equivalent of h3m::TownEvent stored in the saved game.
  struct TownEvent : TimedEvent
  {
    // ID of the affected town (see h3svg::Town::id).
    std::uint8_t town_id {};
    // 1 bit per TownBuildingType indicating whether the building gets built.
    TownBuildingsBitmask buildings;
    // Always [0, 0]; probably padding bytes for @buildings.
    ReservedData<2> reserved;
    // Extra creatures for each creature level.
    std::array<std::uint16_t, 7> creatures {};
  };

  // Tables that store additional properties for objects of certain types.
  //
  // In H3SVG the properties of an object are stored in 3 places:
  // * ObjectTemplate, which describes the shared immutable properties of the object -
  //   objects that use the same template share those properties.
  // * Tile, which stored 2+4 bytes that describe the properties of the object.
  //   For some objects that's not enough though, in which case Tile stores the index
  //   of the relevant element in a specific array of additional structures.
  // * ObjectPropertiesTables, which stores the above-mentioned arrays of additional structures.
  //
  // As usual, H3SVG is inconsistent as fuck, so this class does NOT include Black Markets,
  // but it does include Global Events and Town Events (even though they aren't objects on the
  // Adventure Map). The reason is simply the order in which data is serialized in H3SVG.
  struct ObjectPropertiesTables
  {
    // Events and Pandora's Boxes on the Adventure Map.
    std::vector<EventBase> events_and_pandoras_boxes;
    // Artifacts and Spell scrolls on the Adventure Map.
    // FYI: it seems that the elements are persistent: they are not deleted even after a hero picks them up.
    // Guardians are mutable though.
    // TODO: rename to point out that this also includes resources on the adventure map.
    //       Tile::object_properties stores the quantity, but message&guardians are stored here.
    std::vector<Artifact> artifacts_and_spell_scrolls;
    // Wandering creatures on the Adventure Map.
    // TODO: consider renaming; this seems more like "monsters with custom message or treasure".
    std::vector<Monster> monsters;
    // Seer's Huts.
    std::vector<SeersHut> seers_huts;
    // Quest guards.
    std::vector<QuestGuard> quest_guards;
    // Global events (called "Timed Events" in the Map Editor).
    // FYI: it seems that HD mod appends one event to the end of this array.
    // The message looks like Base64-encoded data, but the meaning is unclear.
    // Perhaps, BIG BARATORCH IS WATCHING YOU.
    std::vector<TimedEvent> global_events;
    // Timed Events affecting a specific town.
    std::vector<TownEvent> town_events;
    // Signs and Ocean Bottles on the Adventure Map.
    std::vector<Sign> signs_and_ocean_bottles;
    // Mines, Abandoned Mines and Lighthouses
    std::vector<Mine> mines_and_lighthouses;
    // Creature Dwellings.
    std::vector<Dwelling> dwellings;
    // Garrisons on the Adventure Map.
    // The number of elements should not exceed 255 because in H3SVG it's serialized as an 8-bit integer.
    std::vector<Garrison> garrisons;
    // Boats on the Adventure Map.
    // The number of elements should not exceed 255 because in H3SVG it's serialized as an 8-bit integer.
    std::vector<Boat> boats;
    // Obelisks on the Adventure Map.
    // As usual, H3SVG is doing stupid shit: first, the number of obelisks N is serialized as an 8-bit integer,
    // followed by 48 bytes - 1 byte per obelisk. Only the bytes [0; N) are meaningful - the rest will likely
    // be 0s.
    std::uint8_t num_obelisks {};
    std::array<Obelisk, 48> obelisks;
  };
}
