#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3SVGWriter/Utils.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3svg
{
  void H3SVGWriter::writeData(const CreatureBank& creature_bank) const
  {
    writeData(creature_bank.guards);
    writeData(creature_bank.resources);
    writeData(creature_bank.creatures);
    writeVector<std::uint16_t>(std::span{ creature_bank.artifacts });
  }

  void H3SVGWriter::writeData(const Date& date) const
  {
    writeData(date.day);
    writeData(date.week);
    writeData(date.month);
  }

  void H3SVGWriter::writeData(const ObjectExits& object_exits) const
  {
    writeVector<std::uint16_t>(std::span{ object_exits.exits });
  }

  void H3SVGWriter::writeData(const Rumor& rumor) const
  {
    writeString16(rumor.text);
    writeData(rumor.has_been_shown);
  }

  void H3SVGWriter::writeData(const SavedGame& saved_game) const
  {
    writeData(saved_game.signature);
    writeData(saved_game.reserved1);
    writeData(saved_game.version_major);
    writeData(saved_game.version_minor);
    writeData(saved_game.reserved2);
    writeData(saved_game.format);
    writeData(saved_game.basic_info);
    writeData(saved_game.players_specs);
    writeData(saved_game.victory_condition);
    writeData(saved_game.loss_condition);
    writeData(saved_game.teams);
    writeVector<std::uint8_t>(std::span{ saved_game.custom_heroes });
    writeData(saved_game.unknown1);
    writeData(saved_game.starting_info);
    writeData(saved_game.original_filename);
    writeData(saved_game.unknown2);
    writeData(saved_game.disabled_artifacts);
    writeData(saved_game.artifacts_bitmask_unknown);
    writeData(saved_game.disabled_skills);
    writeString16(saved_game.current_rumor);
    writeData(saved_game.unknown3);
    writeVector<std::uint32_t>(std::span{ saved_game.rumors });
    writeVector<std::uint8_t>(std::span{ saved_game.black_markets });
    writeSpan(std::span{ saved_game.tiles });
    writeVector<std::uint32_t>(std::span{ saved_game.objects_templates });
    writeVector<std::uint32_t>(std::span{ saved_game.objects });
    writeData(saved_game.object_properties_tables);
    writeData(saved_game.players);
    writeVector<std::uint8_t>(std::span{ saved_game.towns });
    if (saved_game.heroes.size() != h3m::kNumHeroes)
    {
      throw std::invalid_argument("H3SVGWriter: wrong number of elements in SavedGame::heroes");
    }
    writeSpan(std::span{ saved_game.heroes });
    writeData(saved_game.unknown4);
    writeData(saved_game.current_date);
    writeData(saved_game.unknown5);
    writeData(saved_game.artifact_merchants);
    writeData(saved_game.unknown6);
    writeData(saved_game.keymasters_tents);
    writeData(saved_game.unknown7);
    writeData(saved_game.cartographers);
    writeData(saved_game.unknown8);
    writeSpan(std::span{ saved_game.fog_of_war });
    writeData(saved_game.monoliths_two_way);
    writeData(saved_game.monoliths_one_way);
    writeData(saved_game.whirlpools);
    writeData(saved_game.subterranean_gates);
    writeVector<std::uint16_t>(std::span{ saved_game.unknown9 });
    writeVector<std::uint16_t>(std::span{ saved_game.universities });
    writeVector<std::uint16_t>(std::span{ saved_game.creature_banks });
    writeVector<std::uint32_t>(std::span{ saved_game.previous_turn });
  }

  void H3SVGWriter::writeData(const TileVisibility& value) const
  {
    writeData(value.visibility);
    writeData(value.has_adjacent_monster);
  }

  void H3SVGWriter::writeData(const University& university) const
  {
    writeData(university.skills);
  }
}
