// The code in this file was copied from zstr library, written by Matei David.
// zstr is a free and open-source library, distributed under the MIT license.
//
// You can find the full license text in the Git submodule h3mtxt/thirdparty/zstr/LICENSE
// or in h3mtxt/ThirdPartyNotices.txt.

#pragma once

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3svg
{
  // Patched version of zstr::istreambuf from zstr.hpp.
  //
  // Compressed H3SVG files written by the game have invalid CRC32 (the bytes [-8:-4] of the file).
  // I don't know of a simple way to disable CRC checks in zlib, so instead I'm introducing this
  // class to ignore all Z_DATA_ERROR errors returned by inflate().
  class ZstrIstreambufPatched : public std::streambuf
  {
  public:
    ZstrIstreambufPatched(std::streambuf* _sbuf_p,
                          std::size_t _buff_size = zstr::default_buff_size,
                          bool _auto_detect = true,
                          int _window_bits = 0);

    pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which) override;

    std::streambuf::int_type underflow() override;

  private:
    std::streambuf* sbuf_p;
    std::unique_ptr<char[]> in_buff;
    char* in_buff_start;
    char* in_buff_end;
    std::unique_ptr<char[]> out_buff;
    std::unique_ptr<zstr::detail::z_stream_wrapper> zstrm_p;
    std::size_t buff_size;
    bool auto_detect;
    bool auto_detect_run;
    bool is_text;
    int window_bits;
  };

  // Patched version of zstr::istream.
  class ZstrIstreamPatched : public std::istream
  {
  public:
    ZstrIstreamPatched(std::istream& is,
                       std::size_t _buff_size = zstr::default_buff_size,
                       bool _auto_detect = true,
                       int _window_bits = 0);

    explicit ZstrIstreamPatched(std::streambuf* sbuf_p);

    ~ZstrIstreamPatched() override;
  };
}
