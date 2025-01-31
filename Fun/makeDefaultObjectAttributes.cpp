#include <h3mtxt/Fun/makeDefaultObjectAttributes.h>

#include <string_view>
#include <stdexcept>

namespace h3m
{
  ObjectAttributes makeDefaultObjectAttributes(ObjectClass object_class)
  {
    switch (object_class)
    {
    case ObjectClass::PANDORAS_BOX:
      return ObjectAttributes
      {
        .def = "AVA0128.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes = 511,
        .landscape_group = 1,
        .object_class = h3m::ObjectClass::PANDORAS_BOX,
        .object_number = 0,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    case ObjectClass::SCHOLAR:
      return h3m::ObjectAttributes{
        .def = "AVXschl0.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes = 511,
        .landscape_group = 255,
        .object_class = h3m::ObjectClass::SCHOLAR,
        .object_number = 0,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::SPELL_SCROLL:
      return h3m::ObjectAttributes{
        .def = "AVA0001.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes = 511,
        .landscape_group = 1,
        .object_class = h3m::ObjectClass::SPELL_SCROLL,
        .object_number = 0,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    default:
      throw std::logic_error("makeDefaultObjectAttributes(): NotImplemented.");
    }
  }
}