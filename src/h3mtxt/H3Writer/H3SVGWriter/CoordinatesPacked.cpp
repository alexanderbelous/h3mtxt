#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/CoordinatesPacked.h>

namespace h3svg
{
  namespace
  {
    constexpr std::uint32_t packCoordinates(const CoordinatesPacked& coordinates) noexcept
    {
      constexpr std::uint32_t kMaskX = 0b1111111111u;
      constexpr std::uint32_t kMaskPadding1 = 0b111111u;
      constexpr std::uint32_t kMaskY = 0b1111111111u;
      constexpr std::uint32_t kMaskZ = 0b1111u;
      constexpr std::uint32_t kMaskPadding2 = 0b11u;

      return ((static_cast<std::uint32_t>(coordinates.x) & kMaskX) << 0) |
             ((static_cast<std::uint32_t>(coordinates.padding1) & kMaskPadding1) << 10) |
             ((static_cast<std::uint32_t>(coordinates.y) & kMaskY) << 16) |
             ((static_cast<std::uint32_t>(coordinates.z) & kMaskZ) << 26) |
             ((static_cast<std::uint32_t>(coordinates.padding2) & kMaskPadding2) << 30);
    }
  }

  void H3SVGWriter::writeData(const CoordinatesPacked& coordinates) const
  {
    writeData(packCoordinates(coordinates));
  }
}
