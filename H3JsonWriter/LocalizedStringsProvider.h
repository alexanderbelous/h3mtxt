#pragma once

#include <h3mtxt/H3JsonWriter/LocalizedStringsData.h>

namespace h3m::H3JsonWriter_NS
{
  // Singleton class that provides localized strings.
  class LocalizedStringsProvider
  {
  public:
    // Non-copyable, non-movable.
    LocalizedStringsProvider(const LocalizedStringsProvider&) = delete;
    LocalizedStringsProvider(LocalizedStringsProvider&&) = delete;
    LocalizedStringsProvider& operator=(const LocalizedStringsProvider&) = delete;
    LocalizedStringsProvider& operator=(LocalizedStringsProvider&&) = delete;

    // \return the only instance.
    inline static const LocalizedStringsProvider& get();

    // Initializes the storage.
    // If the storage has already been initialized (by calling initialize() or get()), this function has no effect.
    // \param data - localized strings to use.
    //        Empty/missing strings will be replaced by the strings from the default locale (English).
    inline static const LocalizedStringsProvider& initialize(LocalizedStringsData&& data);

    // Returns the string corresponding to the given ID.
    // \param id - unique identifier of the localized string.
    // \return the localized string corresponding to @id.
    //         The returned string_view is guaranteed to remain valid as long as
    //         LocalizedStringsProvider remains valid. Since LocalizedStringsProvider
    //         is a singleton, this means that its destructor is called either when the
    //         program terminates (if linked statically), or when the shared library that
    //         provides it is unloaded (if linked dynamically).
    // \throw std::invalid_argument if @id is not a valid ID.
    inline std::string_view operator()(LocalizedStringId id) const;

  private:
    explicit LocalizedStringsProvider(LocalizedStringsData* data);

    ~LocalizedStringsProvider() = default;

    static LocalizedStringsProvider& getOrCreate(LocalizedStringsData* data = nullptr);

    // This doesn't have to be const, but we also promise that the string_views returned by operator()
    // will remain valid during the lifetime of LocalizedStringsData, so it's safer to forbid modifying
    // the data altogether.
    const LocalizedStringsData data_;
  };

  const LocalizedStringsProvider& LocalizedStringsProvider::get()
  {
    return getOrCreate();
  }

  const LocalizedStringsProvider& LocalizedStringsProvider::initialize(LocalizedStringsData&& data)
  {
    return getOrCreate(&data);
  }

  std::string_view LocalizedStringsProvider::operator()(LocalizedStringId id) const
  {
    return data_.get(id);
  }
}
