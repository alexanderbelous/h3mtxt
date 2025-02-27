#include <h3mtxt/Fun/makeDefaultObjectAttributes.h>

#include <string_view>
#include <stdexcept>

namespace h3m
{
  ObjectAttributes makeDefaultObjectAttributes(ObjectClass object_class)
  {
    switch (object_class)
    {
    case ObjectClass::EVENT:
      return ObjectAttributes
      {
        .def = "AVZevnt0.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000001},
        .object_class = h3m::ObjectClass::EVENT,
        .object_subclass = 0,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::PANDORAS_BOX:
      return ObjectAttributes
      {
        .def = "AVA0128.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b00000001, 0b00000000},
        .object_class = h3m::ObjectClass::PANDORAS_BOX,
        .object_subclass = 0,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    case ObjectClass::SCHOLAR:
      return h3m::ObjectAttributes{
        .def = "AVXschl0.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000000},
        .object_class = h3m::ObjectClass::SCHOLAR,
        .object_subclass = 0,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::SEER_HUT:
      return h3m::ObjectAttributes{
        .def = "AVXseer0.def",
        .passability {255, 255, 255, 255, 255, 191},
        .actionability {0, 0, 0, 0, 0, 64},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000000},
        .object_class = h3m::ObjectClass::SEER_HUT,
        .object_subclass = 0,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::SPELL_SCROLL:
      return h3m::ObjectAttributes{
        .def = "AVA0001.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b00000001, 0b00000000},
        .object_class = h3m::ObjectClass::SPELL_SCROLL,
        .object_subclass = 0,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    default:
      throw std::logic_error("makeDefaultObjectAttributes(): NotImplemented.");
    }
  }
}