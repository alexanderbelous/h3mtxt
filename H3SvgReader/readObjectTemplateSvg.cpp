#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/SavedGame/ObjectTemplateSvg.h>

#include <stdexcept>

namespace h3m::H3SvgReader_NS
{
  using H3Reader_NS::readBool;
  using H3Reader_NS::readInt;

  ObjectTemplateSvg readObjectTemplateSvg(std::istream& stream)
  {
    ObjectTemplateSvg object_template;
    object_template.def = readString16(stream);
    object_template.width = readInt<std::uint8_t>(stream);
    object_template.height = readInt<std::uint8_t>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 6>{ object_template.unknown1 });
    object_template.passability = H3Reader_NS::readByteArray<6>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 6>{ object_template.unknown2 });
    object_template.actionability = H3Reader_NS::readByteArray<6>(stream);
    object_template.object_class = readInt<std::uint16_t>(stream);
    object_template.object_subclass = readInt<std::uint16_t>(stream);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::span<std::byte, 2>{ object_template.unknown3 });
    object_template.is_ground = readBool(stream);
    return object_template;
  }
}