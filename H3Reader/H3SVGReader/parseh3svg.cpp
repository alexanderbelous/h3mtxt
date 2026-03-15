#include <h3mtxt/H3Reader/H3SVGReader/parseh3svg.h>

#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/H3Reader/H3SVGReader/zstr_patch.h>

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
      // FYI: saved games written by HoMM3 have invalid CRC32 checksums at the end of the file
      // (bytes [-8:-4]). Because of this, we cannot use zstr::istream directly - it raises an
      // exception when invalid CRC is detected, and doesn't provide access to the "corrupted"
      // bytes even if you suppress the exception.
      //
      // The class ZstrIstreamPatched was introduced as a workaround for this issue. The class
      // basically copies zstd::istream, but ignores all Z_DATA_ERROR errors returned by inflate().
      // This is a shitty solution - maybe there are other cases when Z_DATA_ERROR is returned, so
      // it would be a terrible idea to reuse ZstrIstreamPatched for anything else.
      ZstrIstreamPatched zstr_stream{ stream };
      return H3SVGReader{ zstr_stream }.readSavedGame();
    }
  }
}
