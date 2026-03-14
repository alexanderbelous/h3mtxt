#include <h3mtxt/H3Reader/H3SVGReader/parseh3svg.h>

#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
#include <stdexcept>

namespace h3svg
{
  SavedGame parseh3svg(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3svg(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    // Check the first byte. If it's 0x1F, then it cannot be an uncompressed .GM* file,
    // so assume that it's a compressed one.
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3svg(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return H3SVGReader{ stream }.readSavedGame();
    }
    else
    {
      // FIXME: actually, this doesn't work: HoMM3 uses its own implementation of Deflate,
      // which often causes errors/warnings in other compression libraries/tools. zlib handles
      // .h3m and .h3c files fine, but not .GM* files.
      // For now, the workaround is to manually decompress the saved game via 7-Zip, and pass the
      // decompresed file to h3mtxt.
      // Alternatively, you can comment out line 227 in zstr.hpp:
      //     if (ret != Z_OK && ret != Z_STREAM_END) throw Exception(zstrm_p.get(), ret);
      // or at least not throw an exception if ret == Z_DATA_ERROR
      // TODO: add a custom class that derives from zstd::istreambuf and ignores CRC errors.
      zstr::istream zstr_stream(stream);
      return H3SVGReader{ zstr_stream }.readSavedGame();
    }
  }
}
