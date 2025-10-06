#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace h3m::H3JsonWriter_NS
{
  // TODO: move this forward declaration to H3JsonWriterFwd.h.
  enum class LocalizedStringId : std::size_t;

  class LocalizedStringsData
  {
  public:
    constexpr LocalizedStringsData() noexcept = default;

    // Assigns the given value to the string with the specified ID.
    // All string_views returned by previous calls to get() are invalidated.
    // \param id - unique identifier of the localized string.
    // \param value - value to assign for the string corresponding to @id.
    // \throw std::invalid_argument if @id is not a valid ID.
    void set(LocalizedStringId id, std::string_view value);

    // Returns a string corresponding to the given ID.
    // \param id - unique identifier of the localized string.
    // \return the value corresponding to @id, or an empty string_view if no value was set for @id.
    // \throw std::invalid_argument if @id is not a valid ID.
    // Time complexity: O(1).
    std::string_view get(LocalizedStringId id) const;

  private:
    // Not the best way to store a lot of short strings, but fine for now.
    std::vector<std::string> data_;
  };
}
