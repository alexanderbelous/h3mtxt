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
    player.unknown = readReservedData<2>(stream);
    player.starting_hero = readStartingHeroSvg(stream);
    return player;
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
    saved_game.basic_info = readMapBasicInfo(stream);
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
    // Read 48 bytes representing the filename of the original map.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ saved_game.map_filename }));
    // Read 203 bytes.
    // These seem to always be zero-filled.
    saved_game.reserved3 = readReservedData<203>(stream);
    // Read 100 bytes representing the relative path to the directory in which the original map is located.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ saved_game.map_directory }));
    // Read 30 bytes.
    // TODO: figure out what this is.
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 30>{ saved_game.unknown3 });
    // TODO: read the rest.
    return saved_game;
  }
}
