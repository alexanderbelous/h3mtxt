#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Artifact& artifact) const
  {
    writeData(artifact.guardians);
  }

  void H3SVGWriter::writeData(const Boat& boat) const
  {
    writeData(boat.exists);
    writeData(boat.id);
    writeData(boat.object_sublcass);
    writeData(boat.orientation);
    writeData(boat.owner);
    writeData(boat.owner_hero);
    writeData(boat.is_occupied);
    writeData(boat.x);
    writeData(boat.y);
    writeData(boat.z);
    writeData(boat.is_visible);
    writeData(boat.coordinates_packed);
    writeData(boat.unknown);
  }

  void H3SVGWriter::writeData(const Dwelling& dwelling) const
  {
    writeData(dwelling.owner);
    writeData(dwelling.object_class);
    writeData(dwelling.object_subclass);
    writeData(dwelling.creature_types);
    writeData(dwelling.creature_counts);
    writeData(dwelling.coordinates);
    writeData(dwelling.guardians);
    writeData(dwelling.unknown);
  }

  void H3SVGWriter::writeData(const Garrison& garrison) const
  {
    writeData(garrison.owner);
    writeData(garrison.creatures);
    writeData(garrison.coordinates);
    writeData(garrison.can_remove_units);
  }

  void H3SVGWriter::writeData(const Mine& mine) const
  {
    writeData(mine.owner);
    writeData(mine.unknown);
    writeData(mine.creatures);
    writeData(mine.coordinates);
  }

  void H3SVGWriter::writeData(const Monster& monster) const
  {
    writeString16(monster.message);
    writeData(monster.resources);
    writeData(monster.artifact);
  }

  void H3SVGWriter::writeData(const Obelisk& obelisk) const
  {
    writeData(obelisk.visited_by);
  }

  void H3SVGWriter::writeData(const ObjectPropertiesTables& tables) const
  {
    writeVector<std::uint16_t>(std::span{ tables.events_and_pandoras_boxes });
    writeVector<std::uint16_t>(std::span{ tables.artifacts_and_spell_scrolls });
    writeVector<std::uint16_t>(std::span{ tables.monsters });
    writeVector<std::uint16_t>(std::span{ tables.seers_huts });
    writeVector<std::uint16_t>(std::span{ tables.quest_guards });
    writeVector<std::uint32_t>(std::span{ tables.global_events });
    writeVector<std::uint32_t>(std::span{ tables.town_events });
    writeVector<std::uint8_t>(std::span{ tables.signs_and_ocean_bottles });
    writeVector<std::uint8_t>(std::span{ tables.mines_and_lighthouses });
    writeVector<std::uint16_t>(std::span{ tables.dwellings });
    writeVector<std::uint8_t>(std::span{ tables.garrisons });
    writeVector<std::uint8_t>(std::span{ tables.boats });
    writeData(tables.num_obelisks);
    writeData(tables.obelisks);
  }

  void H3SVGWriter::writeData(const QuestGuard& quest_guard) const
  {
    writeData(quest_guard.quest);
    writeData(quest_guard.visited_by);
  }

  void H3SVGWriter::writeData(const SeersHut& seers_hut) const
  {
    writeData(seers_hut.quest);
    writeData(seers_hut.reward);
    writeData(seers_hut.reserved);
    writeData(seers_hut.visited_by);
    writeData(seers_hut.name);
  }

  void H3SVGWriter::writeData(const Sign& sign) const
  {
    writeString16(sign.message);
    writeData(sign.is_custom);
  }

  void H3SVGWriter::writeData(const TimedEvent& event) const
  {
    writeString16(event.message);
    writeData(event.resources);
    writeData(event.affected_players);
    writeData(event.applies_to_human);
    writeData(event.applies_to_computer);
    writeData(event.day_of_first_occurence);
    writeData(event.repeat_after_days);
  }

  void H3SVGWriter::writeData(const TownEvent& event) const
  {
    writeData(static_cast<const TimedEvent&>(event));
    writeData(event.town_id);
    writeData(event.buildings);
    writeData(event.reserved);
    writeData(event.creatures);
  }
}
