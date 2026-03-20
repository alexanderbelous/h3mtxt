#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>

namespace h3m
{
  void H3CWriter::writeData(const std::string& value) const
  {
    writeString32(value);
  }
}
