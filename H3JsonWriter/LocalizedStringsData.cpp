#include <h3mtxt/H3JsonWriter/LocalizedStringsData.h>

#include <h3mtxt/H3JsonWriter/LocalizedStringId.h>

#include <stdexcept>

namespace h3m::H3JsonWriter_NS
{
  void LocalizedStringsData::set(LocalizedStringId id, std::string_view value)
  {
    const std::size_t index = static_cast<std::size_t>(id);
    if (index >= kNumLocalizedStringIds)
    {
      throw std::invalid_argument("LocalizedStringsData::set(): invalid id.");
    }
    if (data_.size() != kNumLocalizedStringIds)
    {
      data_.resize(kNumLocalizedStringIds);
    }
    data_[index].assign(value);
  }

  // Returns a string corresponding to the given ID.
  // \param id - unique identifier of the localized string.
  // \return the value corresponding to @id, or an empty string_view if no value was set for @id.
  // \throw std::invalid_argument if @id is not a valid ID.
  // Time complexity: O(1).
  std::string_view LocalizedStringsData::get(LocalizedStringId id) const
  {
    const std::size_t index = static_cast<std::size_t>(id);
    if (index >= kNumLocalizedStringIds)
    {
      throw std::invalid_argument("LocalizedStringsData::get(): invalid id.");
    }
    // Return an empty string_view if id is valid but the string is missing
    // (e.g., empty LocalizedStringsData).
    if (index >= data_.size())
    {
      return {};
    }
    return data_[index];
  }
}