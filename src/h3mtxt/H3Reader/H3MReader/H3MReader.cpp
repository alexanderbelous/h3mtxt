#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>

#include <stdexcept>

namespace h3m
{
  H3MReader::H3MReader(std::istream& stream, MapFormat map_format):
    H3ReaderBase{ stream },
    map_format_{ map_format }
  {
    if (map_format != MapFormat::ArmageddonsBlade &&
        map_format != MapFormat::ShadowOfDeath)
    {
      throw std::invalid_argument("H3MReader: invalid MapFormat");
    }
  }
}
