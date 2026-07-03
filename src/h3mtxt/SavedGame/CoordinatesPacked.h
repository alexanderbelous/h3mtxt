#pragma once

#include <cstdint>

namespace h3svg
{
  // H3SVG uses a packed format for coordinates in some places, serializing them as a single 32-bit integer:
  // * Bits [0; 10) store the X coordinate.
  // * Bits [16; 26) store the Y coordinate.
  // * Bit 26 stores the Z coordinate.
  //
  // In H3API this is called h3::H3Position.
  //
  // Note that it's implementation-defined whether bit fields are packed in C++.
  // Similarly, endianness is platform-specific, so it's not guaranteed that the
  // object representation of CoordinatesPacked is equal to the bytes serialized in H3SVG for it.
  //
  // I suspect that the game defines this simply as
  //     struct CoordinatesPacked
  //     {
  //       std::uint16_t x : 10 {};
  //       std::uint16_t y : 10 {};
  //       std::uint16_t z : 1 {};
  //     };
  // i.e. the padding bits are implicit. However, they are explicitly written in H3SVG,
  // so h3mtxt explicitly defines them as well.
  struct CoordinatesPacked
  {
    std::uint16_t x        : 10 {};  // [0; 1023]
    std::uint16_t padding1 : 6  {};  // [0; 63]
    std::uint16_t y        : 10 {};  // [0; 1023]
    std::uint16_t z        : 1  {};  // [0; 1]
    std::uint16_t padding2 : 5  {};  // [0; 31]
  };
}
