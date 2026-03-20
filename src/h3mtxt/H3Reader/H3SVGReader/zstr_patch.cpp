// The code in this file was copied from zstr library, written by Matei David.
// zstr is a free and open-source library, distributed under the MIT license.
//
// You can find the full license text in the Git submodule h3mtxt/thirdparty/zstr/LICENSE
// or in h3mtxt/ThirdPartyNotices.txt.

#include <h3mtxt/H3Reader/H3SVGReader/zstr_patch.h>

namespace h3svg
{
  ZstrIstreambufPatched::ZstrIstreambufPatched(std::streambuf* _sbuf_p,
                                               std::size_t _buff_size,
                                               bool _auto_detect,
                                               int _window_bits):
    sbuf_p(_sbuf_p),
    in_buff(),
    in_buff_start(nullptr),
    in_buff_end(nullptr),
    out_buff(),
    zstrm_p(nullptr),
    buff_size(_buff_size),
    auto_detect(_auto_detect),
    auto_detect_run(false),
    is_text(false),
    window_bits(_window_bits)
  {
    assert(sbuf_p);
    in_buff = std::unique_ptr<char[]>(new char[buff_size]);
    in_buff_start = in_buff.get();
    in_buff_end = in_buff.get();
    out_buff = std::unique_ptr<char[]>(new char[buff_size]);
    setg(out_buff.get(), out_buff.get(), out_buff.get());
  }

  ZstrIstreambufPatched::pos_type ZstrIstreambufPatched::seekoff(off_type off,
                                                                 std::ios_base::seekdir dir,
                                                                 std::ios_base::openmode which)
  {
    if (off != 0 || dir != std::ios_base::cur)
    {
      return std::streambuf::seekoff(off, dir, which);
    }
    if (!zstrm_p)
    {
      return 0;
    }
    return static_cast<long int>(zstrm_p->total_out - static_cast<uLong>(in_avail()));
  }

  std::streambuf::int_type ZstrIstreambufPatched::underflow()
  {
    if (this->gptr() == this->egptr())
    {
      // pointers for free region in output buffer
      char* out_buff_free_start = out_buff.get();
      int tries = 0;
      do
      {
        if (++tries > 1000)
        {
          throw std::ios_base::failure("Failed to fill buffer after 1000 tries");
        }

        // read more input if none available
        if (in_buff_start == in_buff_end)
        {
          // empty input buffer: refill from the start
          in_buff_start = in_buff.get();
          std::streamsize sz = sbuf_p->sgetn(in_buff.get(), static_cast<std::streamsize>(buff_size));
          in_buff_end = in_buff_start + sz;
          if (in_buff_end == in_buff_start) break; // end of input
        }
        // auto detect if the stream contains text or deflate data
        if (auto_detect && ! auto_detect_run)
        {
          auto_detect_run = true;
          unsigned char b0 = *reinterpret_cast< unsigned char * >(in_buff_start);
          unsigned char b1 = *reinterpret_cast< unsigned char * >(in_buff_start + 1);
          // Ref:
          // http://en.wikipedia.org/wiki/Gzip
          // http://stackoverflow.com/questions/9050260/what-does-a-zlib-header-look-like
          is_text = ! (in_buff_start + 2 <= in_buff_end
                       && ((b0 == 0x1F && b1 == 0x8B)         // gzip header
                           || (b0 == 0x78 && (b1 == 0x01      // zlib header
                                              || b1 == 0x9C
                                              || b1 == 0xDA))));
        }
        if (is_text)
        {
          // simply swap in_buff and out_buff, and adjust pointers
          assert(in_buff_start == in_buff.get());
          std::swap(in_buff, out_buff);
          out_buff_free_start = in_buff_end;
          in_buff_start = in_buff.get();
          in_buff_end = in_buff.get();
        }
        else
        {
          // run inflate() on input
          if (!zstrm_p) zstrm_p = std::make_unique<zstr::detail::z_stream_wrapper>(true, Z_DEFAULT_COMPRESSION, window_bits);
          zstrm_p->next_in = reinterpret_cast< decltype(zstrm_p->next_in) >(in_buff_start);
          zstrm_p->avail_in = uint32_t(in_buff_end - in_buff_start);
          zstrm_p->next_out = reinterpret_cast< decltype(zstrm_p->next_out) >(out_buff_free_start);
          zstrm_p->avail_out = uint32_t((out_buff.get() + buff_size) - out_buff_free_start);
          int ret = inflate(zstrm_p.get(), Z_NO_FLUSH);
          // process return code
// ================================================================================================
// PATCHED BULLSHIT BEGINS
// ================================================================================================
          if (ret != Z_OK && ret != Z_STREAM_END && ret != Z_DATA_ERROR) throw zstr::Exception(zstrm_p.get(), ret);
// ================================================================================================
// PATCHED BULLSHIT ENDS
// ================================================================================================
          // update in&out pointers following inflate()
          in_buff_start = reinterpret_cast< decltype(in_buff_start) >(zstrm_p->next_in);
          in_buff_end = in_buff_start + zstrm_p->avail_in;
          out_buff_free_start = reinterpret_cast< decltype(out_buff_free_start) >(zstrm_p->next_out);
          assert(out_buff_free_start + zstrm_p->avail_out == out_buff.get() + buff_size);

          if (ret == Z_STREAM_END)
          {
            // if stream ended, deallocate inflator
            zstrm_p.reset();
          }
        }
      } while (out_buff_free_start == out_buff.get());
      // 2 exit conditions:
      // - end of input: there might or might not be output available
      // - out_buff_free_start != out_buff: output available
      this->setg(out_buff.get(), out_buff.get(), out_buff_free_start);
    }
    return this->gptr() == this->egptr()
      ? traits_type::eof()
      : traits_type::to_int_type(*this->gptr());
  }

  ZstrIstreamPatched::ZstrIstreamPatched(std::istream& is,
                                         std::size_t _buff_size,
                                         bool _auto_detect,
                                         int _window_bits):
    std::istream(new ZstrIstreambufPatched(is.rdbuf(), _buff_size, _auto_detect, _window_bits))
  {
    exceptions(std::ios_base::badbit);
  }

  ZstrIstreamPatched::ZstrIstreamPatched(std::streambuf* sbuf_p)
    : std::istream(new ZstrIstreambufPatched(sbuf_p))
  {
    exceptions(std::ios_base::badbit);
  }

  ZstrIstreamPatched::~ZstrIstreamPatched()
  {
    delete rdbuf();
  }
}
