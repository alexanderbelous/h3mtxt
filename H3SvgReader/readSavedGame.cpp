#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readEnum;
  using H3Reader_NS::readEnumBitmask;
  using H3Reader_NS::readInt;
  using H3Reader_NS::readReservedData;

  Coordinates readCoordinates(std::istream& stream)
  {
    Coordinates result;
    result.x = readInt<std::uint8_t>(stream);
    result.y = readInt<std::uint8_t>(stream);
    result.z = readInt<std::uint8_t>(stream);
    return result;
  }

  StartingHero readStartingHeroSvg(std::istream& stream)
  {
    StartingHero starting_hero;
    starting_hero.type = readEnum<HeroType>(stream);
    if (starting_hero.type != HeroType{ 0xFF })
    {
      starting_hero.portrait = readEnum<HeroPortrait>(stream);
      starting_hero.name = readString16(stream);
    }
    return starting_hero;
  }

  PlayerSpecsSvg readPlayerSpecsSvg(std::istream& stream)
  {
    PlayerSpecsSvg player;
    player.can_be_human = readBool(stream);
    player.can_be_computer = readBool(stream);
    player.behavior = readEnum<PlayerBehavior>(stream);
    player.allowed_alignments = readEnumBitmask<TownType, 2>(stream);
    player.allow_random_alignment = readBool(stream);
    const Bool has_generated_hero = readBool(stream);
    if (has_generated_hero)
    {
      player.generated_hero_coordinates = readCoordinates(stream);
    }
    player.starting_hero = readStartingHeroSvg(stream);
    return player;
  }

  RumorSvg readRumorSvg(std::istream& stream)
  {
    RumorSvg rumor;
    rumor.text = readString16(stream);
    rumor.unknown = h3m::H3Reader_NS::Detail_NS::readByte(stream);
    return rumor;
  }

  ObjectTemplateSvg readObjectTemplateSvg(std::istream& stream)
  {
    ObjectTemplateSvg object_template;
    object_template.def = readString16(stream);
    object_template.width = readInt<std::uint8_t>(stream);
    object_template.height = readInt<std::uint8_t>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 6>{ object_template.unknown1 });
    object_template.passability = H3Reader_NS::readByteArray<6>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 6>{ object_template.unknown2 });
    object_template.actionability = H3Reader_NS::readByteArray<6>(stream);
    object_template.object_class = readInt<std::uint16_t>(stream);
    object_template.object_subclass = readInt<std::uint16_t>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 2>{ object_template.unknown3 });
    object_template.is_ground = readBool(stream);
    return object_template;
  }

  SavedGame readSavedGame(std::istream& stream)
  {
    SavedGame saved_game;
    // Read and check the file signature.
    char file_signature[5] {};
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ file_signature }));
    if (std::string_view{ file_signature, sizeof(file_signature) } != SavedGame::kFileSignature)
    {
      throw std::runtime_error("readSavedGame(): invalid file signature.");
    }
    saved_game.reserved1 = readReservedData<3>(stream);
    saved_game.version_major = readInt<std::uint32_t>(stream);
    saved_game.version_minor = readInt<std::uint32_t>(stream);
    saved_game.reserved2 = readReservedData<32>(stream);
    saved_game.format = readEnum<h3m::MapFormat>(stream);
    saved_game.basic_info = readMapBasicInfoSvg(stream);
    for (PlayerSpecsSvg& player : saved_game.players)
    {
      player = readPlayerSpecsSvg(stream);
    }
    saved_game.victory_condition = H3Reader_NS::readVictoryCondition(stream);
    saved_game.loss_condition = H3Reader_NS::readLossCondition(stream);
    saved_game.teams = H3Reader_NS::readTeamsInfo(stream);
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>(stream);
    saved_game.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      saved_game.custom_heroes.push_back(H3Reader_NS::readCustomHero(stream));
    }
    // Read 16 bytes.
    // These seem to to always be {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 16>{ saved_game.unknown1 });
    // Read 41 bytes.
    // TODO: figure out what it is.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 41>{ saved_game.unknown2 });
    // Read 251 bytes representing the filename of the original map.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ saved_game.map_filename }));
    // Read 100 bytes representing the relative path to the directory in which the original map is located.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ saved_game.map_directory }));
    // Read 30 bytes.
    // TODO: figure out what this is.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 30>{ saved_game.unknown3 });
    // Read 47 bytes representing the original filename for this saved game.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ saved_game.original_filename }));
    // Read 352 bytes.
    // TODO: figure out what this is.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 352>{ saved_game.unknown4 });
    // Read 144 bytes indicating which artifacts are disabled on this map (1 byte per artifact).
    for (int i = 0; i < 144; ++i)
    {
      saved_game.disabled_artifacts.set(static_cast<ArtifactType>(i), readBool(stream));
    }
    // Read 144 bytes for another bitmask for artifacts.
    // TODO: figure out what this is.
    for (int i = 0; i < 144; ++i)
    {
      saved_game.artifacts_bitmask_unknown.set(static_cast<ArtifactType>(i), readBool(stream));
    }
    // Read 28 bytes indicating which secondary skills are disabled on this map (1 byte per skill).
    for (int i = 0; i < 28; ++i)
    {
      saved_game.disabled_skills.set(static_cast<SecondarySkillType>(i), readBool(stream));
    }
    // Read the rumor currently displayed in the Tavern.
    // In H3SVG this is serialized as a length-prefixed string; the length is serialized as a
    // 16-bit little-endian integer.
    saved_game.current_rumor = readString16(stream);
    // Read 256 bytes.
    // TODO: figure out what this is.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 256>{ saved_game.unknown5 });
    // Read custom rumors that can appear in the Tavern.
    const std::uint32_t num_custom_rumors = readInt<std::uint32_t>(stream);
    saved_game.rumors.reserve(num_custom_rumors);
    for (std::uint32_t i = 0; i < num_custom_rumors; ++i)
    {
      saved_game.rumors.push_back(readRumorSvg(stream));
    }
    // Read an 8-bit integer N, followed by N*28 bytes.
    // TODO: figure out what this is. It looks like each array of 28 bytes is actually
    // an array of 7 32-bit integers, but the meaning is not clear. Resources are a natural
    // candidate, but this doesn't seem to be the case.
    const std::uint8_t num_unknown_blocks_of_7_numbers = readInt<std::uint8_t>(stream);
    saved_game.unknown6.reserve(num_unknown_blocks_of_7_numbers);
    for (std::uint32_t i = 0; i < num_unknown_blocks_of_7_numbers; ++i)
    {
      std::array<std::int32_t, 7> data {};
      for (std::int32_t& element : data)
      {
        element = readInt<std::int32_t>(stream);
      }
      saved_game.unknown6.push_back(data);
    }
    // Read tiles.
    const std::size_t num_tiles = countTiles(saved_game.basic_info);
    saved_game.tiles.reserve(num_tiles);
    for (std::size_t i = 0; i < num_tiles; ++i)
    {
      saved_game.tiles.push_back(readTileSvg(stream));
    }
    // Read objects' templates.
    const std::uint32_t num_objects_templates = readInt<std::uint32_t>(stream);
    saved_game.objects_templates.reserve(num_objects_templates);
    for (std::uint32_t i = 0; i < num_objects_templates; ++i)
    {
      saved_game.objects_templates.push_back(readObjectTemplateSvg(stream));
    }
    // TODO: read the rest.
    return saved_game;
  }
}
