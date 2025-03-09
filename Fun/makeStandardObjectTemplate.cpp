#include <h3mtxt/Fun/makeStandardObjectTemplate.h>

#include <stdexcept>
#include <string>

namespace h3m
{
  namespace
  {
    // Get the default sprite (.def file) for the specified hero subclass.
    // \param hero_subclass - hero sublcass. Must be within [0; 17].
    // \return the name of the default sprite for @hero_subclass.
    // \throw std::out_of_range if @hero_subclass > 17.
    std::string getSpriteForHeroSubclass(std::uint32_t hero_subclass)
    {
      if (hero_subclass > 17)
      {
        throw std::out_of_range("Hero Class is out of range.");
      }
      std::string def = "ah00_e.def";
      def[2] = (hero_subclass >= 10) ? '1' : '0';
      def[3] = '0' + (hero_subclass % 10);
      return def;
    }
  }

  ObjectTemplate makeStandardObjectTemplate(ObjectClass object_class, std::uint32_t object_subclass)
  {
    switch (object_class)
    {
    case ObjectClass::EVENT:
      return ObjectTemplate
      {
        .def = "AVZevnt0.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000001},
        .object_class = h3m::ObjectClass::EVENT,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::HERO:
      return ObjectTemplate
      {
        .def = getSpriteForHeroSubclass(object_subclass),
        .passability {255, 255, 255, 255, 255, 191},
        .actionability {0, 0, 0, 0, 0, 64},
        .object_class = h3m::ObjectClass::HERO,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Hero,
        .is_ground = 0
      };
    case ObjectClass::PANDORAS_BOX:
      return ObjectTemplate
      {
        .def = "AVA0128.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b00000001, 0b00000000},
        .object_class = h3m::ObjectClass::PANDORAS_BOX,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    case ObjectClass::SCHOLAR:
      return h3m::ObjectTemplate{
        .def = "AVXschl0.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000000},
        .object_class = h3m::ObjectClass::SCHOLAR,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::SEER_HUT:
      return h3m::ObjectTemplate{
        .def = "AVXseer0.def",
        .passability {255, 255, 255, 255, 255, 191},
        .actionability {0, 0, 0, 0, 0, 64},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b11111111, 0b00000000},
        .object_class = h3m::ObjectClass::SEER_HUT,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Terrain,
        .is_ground = 0
      };
    case ObjectClass::SPELL_SCROLL:
      return h3m::ObjectTemplate{
        .def = "AVA0001.def",
        .passability {255, 255, 255, 255, 255, 127},
        .actionability {0, 0, 0, 0, 0, 128},
        .allowed_landscapes {0b11111111, 0b00000001},
        .landscape_group {0b00000001, 0b00000000},
        .object_class = h3m::ObjectClass::SPELL_SCROLL,
        .object_subclass = object_subclass,
        .object_group = h3m::ObjectGroup::Artifact,
        .is_ground = 0
      };
    default:
      throw std::logic_error("makeStandardObjectTemplate(): NotImplemented.");
    }
  }
}