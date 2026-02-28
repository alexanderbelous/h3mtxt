#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>

#include <cstdint>

namespace h3m
{
  // Same as h3m::ArtifactType, but uses int32 as the underlying type.
  //
  // In H3SVG there are places where ArtifactType is serialized as a signed 32-bit integer,
  // unlike .h3m where it's serialized as a 16-bit integer.
  // We cannot simply reuse ArtifactType in such places because that wouldn't be lossless.
  // I don't want to use a raw integer type (int32) either, because type safety.
  //
  // So, instead this enum is defined.
  enum class ArtifactType32 : std::int32_t
  {
    // TODO: add all valid constants.
    // In the naive solution this causes code duplication, which is unfortunate, but not the end of the world.
    // Possible workarounds:
    // 1) Preprocessor: either macros or #include. Lame.
    // 2) Templates:
    //   template<class UnderlyingType>
    //   struct ArtifactTypeTraits
    //   {
    //     static_assert(std::is_integral_v<UnderlyingType>, "Must be an integral type");
    //
    //     enum class type : UnderlyingType
    //     {
    //       Spellbook,
    //       SpellScroll,
    //       ...
    //     };
    //   }
    //
    //   template<class UnderlyingType>
    //   using ArtifactType = typename ArtifactTypeTraits<UnderlyingType>::type;
    //
    //   using ArtifactType16 = ArtifactType<int16_t>;
    //   using ArtifactType32 = ArtifactType<int32_t>;
    //
    // The only disadvantage is that such enums cannot be forward-declared.
  };
}
