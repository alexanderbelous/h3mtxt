#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/SavedGame.h>

#include <stdexcept>

namespace h3m::H3SvgReader_NS
{
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
    saved_game.format = H3Reader_NS::readEnum<h3m::MapFormat>(stream);
    saved_game.basic_info = readMapBasicInfo(stream);
    // TODO: read the rest.
  }
}
