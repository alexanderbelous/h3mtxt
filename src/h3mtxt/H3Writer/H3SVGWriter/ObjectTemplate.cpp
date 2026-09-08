#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ObjectTemplate.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const ObjectTemplate& object_template) const
  {
    writeString16(object_template.def);
    writeData(object_template.width);
    writeData(object_template.height);
    writeData(object_template.unknown1);
    writeData(object_template.passability);
    writeData(object_template.unknown2);
    writeData(object_template.actionability);
    writeData(object_template.object_class);
    writeData(object_template.object_subclass);
    writeData(object_template.reserved);
    writeData(object_template.is_ground);
  }
}
