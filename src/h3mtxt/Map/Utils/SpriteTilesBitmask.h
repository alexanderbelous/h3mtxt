#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>

#include <array>
#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // 6x8 matrix (6 rows, 8 columns) with Boolean elements.
  //
  // This is used in ObjectTemplate to specify which tiles of the object are passable/actionable.
  //
  // In .h3m such bitmasks are serialized simply as arrays of 6 bytes; this class provides public
  // access to the underlying array of bytes, but also defines convenient getters/setters.
  //
  // The element A[i][j] of the matrix corresponds to the j-th bit of the byte data[i]
  // (j==0 is LSB, j==7 is MSB). For example, A[5][7] is the bit corresponding to the bottom right
  // tile of the sprite.
  //
  // FYI: in .h3m the coordinates (x, y, z) of the object on the Adventure Map refer to the bottom
  // right tile of the sprite.
  struct SpriteTilesBitmask
  {
    // The number of rows in the matrix, i.e. the maximum possible height of the sprite.
    static constexpr std::uint8_t kRows = 6;
    // The number of columns in the matrix, i.e. the maximum possible width of the sprite.
    static constexpr std::uint8_t kColumns = 8;

    // Read-only access to the specified bit.
    // \param row - 0-based index of row.
    // \param column - 0-based index of the column.
    // \return the value of the bit A[row][column].
    // \throw std::out_of_range if row >= kRows || column >= kColumns.
    constexpr bool at(std::uint8_t row, std::uint8_t column) const;

    // Assigns a value to the specified bit.
    // \param row - 0-based index of row.
    // \param column - 0-based index of the column.
    // \param value - value to assign.
    // \throw std::out_of_range if row >= kRows || column >= kColumns.
    constexpr void set(std::uint8_t row, std::uint8_t column, bool value);

    constexpr bool operator==(const SpriteTilesBitmask&) const noexcept = default;

    std::array<std::uint8_t, 6> data {};
  };

  constexpr bool SpriteTilesBitmask::at(std::uint8_t row, std::uint8_t column) const
  {
    if (column >= kColumns)
    {
      throw std::out_of_range("SpriteTilesBitmask::at(): column is out of range.");
    }
    const std::uint8_t mask = 1 << column;
    return data.at(row) & mask;
  }

  constexpr void SpriteTilesBitmask::set(std::uint8_t row, std::uint8_t column, bool value)
  {
    if (column >= kColumns)
    {
      throw std::out_of_range("SpriteTilesBitmask::set(): column is out of range.");
    }
    Detail_NS::setBit(data.at(row), column, value);
  }
}
