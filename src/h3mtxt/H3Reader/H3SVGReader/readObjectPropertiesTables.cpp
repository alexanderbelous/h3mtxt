#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace h3svg
{
  Artifact H3SVGReader::readArtifact() const
  {
    return Artifact{ .guardians = readGuardians() };
  }

  Boat H3SVGReader::readBoat() const
  {
    // Always 28 bytes, apparently.
    Boat boat;
    boat.unknown1 = readByteArray<2>();
    boat.object_sublcass = readInt<std::uint8_t>();
    boat.direction = readInt<std::uint8_t>();
    boat.owner = readEnum<PlayerColor>();
    boat.owner_hero = readInt<std::uint16_t>();
    boat.is_occupied = readBool();
    boat.x = readInt<std::uint16_t>();
    boat.y = readInt<std::uint16_t>();
    boat.z = readInt<std::uint16_t>();
    boat.unknown2 = readByteArray<14>();
    return boat;
  }

  Dwelling H3SVGReader::readDwelling() const
  {
    Dwelling dwelling;
    dwelling.owner = readEnum<PlayerColor>();
    dwelling.object_class = readEnum<ObjectClass8>();
    dwelling.object_subclass = readInt<std::uint8_t>();
    for (CreatureType8& creature_type : dwelling.creature_types)
    {
      creature_type = readEnum<CreatureType8>();
    }
    for (std::uint16_t& creature_count : dwelling.creature_counts)
    {
      creature_count = readInt<std::uint16_t>();
    }
    dwelling.coordinates = readCoordinates();
    dwelling.guardians = readTroops();
    dwelling.unknown = readInt<std::uint8_t>();
    return dwelling;
  }

  Garrison H3SVGReader::readGarrison() const
  {
    Garrison garrison;
    garrison.owner = readEnum<PlayerColor>();
    garrison.creatures = readTroops();
    garrison.coordinates = readCoordinates();
    garrison.can_remove_units = readBool();
    return garrison;
  }

  Mine H3SVGReader::readMine() const
  {
    Mine mine;
    mine.owner = readEnum<PlayerColor>();
    mine.unknown = readByteArray<2>();
    mine.creatures = readTroops();
    mine.coordinates = readCoordinates();
    return mine;
  }

  Monster H3SVGReader::readMonster() const
  {
    Monster monster;
    monster.message = readString16();
    monster.resources = readResources();
    monster.artifact = readEnum<ArtifactType8>();
    return monster;
  }

  Obelisk H3SVGReader::readObelisk() const
  {
    return Obelisk{ .visited_by = readEnumBitmask<PlayerColor, 1>() };
  }

  QuestGuard H3SVGReader::readQuestGuard() const
  {
    QuestGuard quest_guard;
    quest_guard.quest = readQuest();
    quest_guard.visited_by = readEnumBitmask<PlayerColor, 1>();
    return quest_guard;
  }


  SeersHut H3SVGReader::readSeersHut() const
  {
    SeersHut seers_hut;
    seers_hut.quest = readQuest();
    seers_hut.reward = readReward();
    seers_hut.reserved = readInt<std::uint8_t>();
    seers_hut.visited_by = readEnumBitmask<PlayerColor, 1>();
    seers_hut.name = readEnum<SeerName>();
    return seers_hut;
  }

  Sign H3SVGReader::readSign() const
  {
    Sign sign;
    sign.message = readString16();
    sign.is_custom = readBool();
    return sign;
  }

  TimedEvent H3SVGReader::readTimedEvent() const
  {
    TimedEvent event;
    event.message = readString16();
    event.resources = readResources();
    event.affected_players = readEnumBitmask<PlayerColor, 1>();
    event.applies_to_human = readBool();
    event.applies_to_computer = readBool();
    event.day_of_first_occurence = readInt<std::uint16_t>();
    event.repeat_after_days = readInt<std::uint16_t>();
    return event;
  }

  TownEvent H3SVGReader::readTownEvent() const
  {
    TownEvent town_event{ readTimedEvent() };
    town_event.town_id = readInt<std::uint8_t>();
    town_event.buildings = readEnumBitmask<TownBuildingType, 6>();
    town_event.reserved = readReservedData<2>();
    for (std::uint16_t& growth : town_event.creatures)
    {
      growth = readInt<std::uint16_t>();
    }
    return town_event;
  }

  ObjectPropertiesTables H3SVGReader::readObjectPropertiesTables() const
  {
    ObjectPropertiesTables tables;
    // Read Event and Pandora's Box objects.
    // FYI: it's funny that the number of events is serialized as a 16-bit integer - the Map Editor
    // seems to have a limit of 200 Events on the Adventure Map.
    {
      const std::uint16_t num_event_objects = readInt<std::uint16_t>();
      tables.events_and_pandoras_boxes.reserve(num_event_objects);
      for (std::uint16_t i = 0; i < num_event_objects; ++i)
      {
        tables.events_and_pandoras_boxes.push_back(readEventBase());
      }
    }
    // Read Artifact and SpellScroll objects.
    {
      const std::uint16_t num_artifact_objects = readInt<std::uint16_t>();
      tables.artifacts_and_spell_scrolls.reserve(num_artifact_objects);
      for (std::uint16_t i = 0; i < num_artifact_objects; ++i)
      {
        tables.artifacts_and_spell_scrolls.push_back(readArtifact());
      }
    }
    // Read wandering creatures.
    {
      const std::uint16_t num_monster_objects = readInt<std::uint16_t>();
      tables.monsters.reserve(num_monster_objects);
      for (std::uint16_t i = 0; i < num_monster_objects; ++i)
      {
        tables.monsters.push_back(readMonster());
      }
    }
    // Read Seer's Huts.
    {
      const std::uint16_t num_seers_huts = readInt<std::uint16_t>();
      tables.seers_huts.reserve(num_seers_huts);
      for (std::uint16_t i = 0; i < num_seers_huts; ++i)
      {
        tables.seers_huts.push_back(readSeersHut());
      }
    }
    // Read Quest Guards.
    {
      const std::uint16_t num_quest_guards = readInt<std::uint16_t>();
      tables.quest_guards.reserve(num_quest_guards);
      for (std::uint16_t i = 0; i < num_quest_guards; ++i)
      {
        tables.quest_guards.push_back(readQuestGuard());
      }
    }
    // Read global events.
    {
      const std::uint32_t num_global_events = readInt<std::uint32_t>();
      tables.global_events.reserve(num_global_events);
      for (std::uint32_t i = 0; i < num_global_events; ++i)
      {
        tables.global_events.push_back(readTimedEvent());
      }
    }
    // Read town events.
    {
      const std::uint32_t num_town_events = readInt<std::uint32_t>();
      tables.town_events.reserve(num_town_events);
      for (std::uint32_t i = 0; i < num_town_events; ++i)
      {
        tables.town_events.push_back(readTownEvent());
      }
    }
    // Read Signs and Ocean Bottles.
    {
      const std::uint8_t num_signs_and_ocean_bottles = readInt<std::uint8_t>();
      tables.signs_and_ocean_bottles.reserve(num_signs_and_ocean_bottles);
      for (std::uint32_t i = 0; i < num_signs_and_ocean_bottles; ++i)
      {
        tables.signs_and_ocean_bottles.push_back(readSign());
      }
    }
    // Read Mines and Lighthouses.
    {
      const std::uint8_t num_mines_and_lighthouses = readInt<std::uint8_t>();
      tables.mines_and_lighthouses.reserve(num_mines_and_lighthouses);
      for (std::uint32_t i = 0; i < num_mines_and_lighthouses; ++i)
      {
        tables.mines_and_lighthouses.push_back(readMine());
      }
    }
    // Read Creature Dwellings.
    {
      const std::uint16_t num_dwellings = readInt<std::uint16_t>();
      tables.dwellings.reserve(num_dwellings);
      for (std::uint32_t i = 0; i < num_dwellings; ++i)
      {
        tables.dwellings.push_back(readDwelling());
      }
    }
    // Read Garrisons.
    {
      const std::uint8_t num_garrisons = readInt<std::uint8_t>();
      tables.dwellings.reserve(num_garrisons);
      for (std::uint32_t i = 0; i < num_garrisons; ++i)
      {
        tables.garrisons.push_back(readGarrison());
      }
    }
    // Read Boats.
    {
      const std::uint8_t num_boats = readInt<std::uint8_t>();
      tables.boats.reserve(num_boats);
      for (std::uint32_t i = 0; i < num_boats; ++i)
      {
        tables.boats.push_back(readBoat());
      }
    }
    // Read Obelisks (always 49 bytes).
    {
      tables.num_obelisks = readInt<std::uint8_t>();
      for (Obelisk& obelisk : tables.obelisks)
      {
        obelisk = readObelisk();
      }
    }
    return tables;
  }
}
