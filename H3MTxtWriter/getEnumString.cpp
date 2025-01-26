#include <h3mtxt/H3MTxtWriter/getEnumString.h>

#include <iterator>

namespace h3m
{
  std::string_view getEnumString(MetaObjectType value) noexcept
  {
    static constexpr std::string_view kNames[] = {
      "ABANDONED_MINE",
      "ARTIFACT",
      "EVENT",
      "GARRISON",
      "GENERIC_NO_PROPERTIES",
      "GRAIL",
      "HERO",
      "MONSTER",
      "PANDORAS_BOX",
      "PLACEHOLDER_HERO",
      "QUEST_GUARD",
      "RANDOM_DWELLING",
      "RANDOM_DWELLING_PRESET_ALIGNMENT",
      "RANDOM_DWELLING_PRESET_LEVEL",
      "RESOURCE",
      "SCHOLAR",
      "SEERS_HUT",
      "SHRINE",
      "SIGN",
      "SPELL_SCROLL",
      "TOWN",
      "TRIVIAL_OWNED_OBJECT",
      "WITCH_HUT",
    };
    const std::size_t idx = static_cast<std::size_t>(value);
    if (idx < std::size(kNames))
    {
      return kNames[idx];
    }
    return {};
  }
}
