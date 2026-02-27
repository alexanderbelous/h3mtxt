#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/ObjectTemplateSvg.h>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readInt;
  using H3Reader_NS::readSpriteTilesBitmask;
  using H3Reader_NS::readReservedData;

  ObjectTemplateSvg readObjectTemplateSvg(std::istream& stream)
  {
    ObjectTemplateSvg object_template;
    object_template.def = readString16(stream);
    object_template.width = readInt<std::uint8_t>(stream);
    object_template.height = readInt<std::uint8_t>(stream);
    object_template.unknown1 = readSpriteTilesBitmask(stream);
    object_template.passability = readSpriteTilesBitmask(stream);
    object_template.unknown2 = readSpriteTilesBitmask(stream);
    object_template.actionability = readSpriteTilesBitmask(stream);
    object_template.object_class = readInt<std::uint16_t>(stream);
    object_template.object_subclass = readInt<std::uint16_t>(stream);
    object_template.reserved = readReservedData<2>(stream);
    object_template.is_ground = readBool(stream);
    return object_template;
  }
}