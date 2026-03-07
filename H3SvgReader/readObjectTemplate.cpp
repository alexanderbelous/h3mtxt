#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/SavedGame/ObjectTemplate.h>

namespace h3svg
{
  ObjectTemplate H3SvgReader::readObjectTemplate() const
  {
    ObjectTemplate object_template;
    object_template.def = readString16();
    object_template.width = readInt<std::uint8_t>();
    object_template.height = readInt<std::uint8_t>();
    object_template.unknown1 = readSpriteTilesBitmask();
    object_template.passability = readSpriteTilesBitmask();
    object_template.unknown2 = readSpriteTilesBitmask();
    object_template.actionability = readSpriteTilesBitmask();
    object_template.object_class = readInt<std::uint16_t>();
    object_template.object_subclass = readInt<std::uint16_t>();
    object_template.reserved = readReservedData<2>();
    object_template.is_ground = readBool();
    return object_template;
  }
}
