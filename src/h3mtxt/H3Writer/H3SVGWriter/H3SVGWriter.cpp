#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>

namespace h3svg
{
  H3SVGWriter::H3SVGWriter(std::ostream& stream, MapFormat map_format) :
    H3WriterBase{ stream },
    map_format_{ map_format }
  {
    if (map_format != MapFormat::ArmageddonsBlade &&
        map_format != MapFormat::ShadowOfDeath)
    {
      throw std::invalid_argument("H3SVGWriter: invalid MapFormat");
    }
  }

  void H3SVGWriter::writeData(const Coordinates& value) const
  {
    h3m::H3MWriter{ stream_, format() }.writeData(value);
  }

  void H3SVGWriter::writeData(const CustomHero& value) const
  {
    h3m::H3MWriter{ stream_, format() }.writeData(value);
  }

  void H3SVGWriter::writeData(const Teams& teams) const
  {
    h3m::H3MWriter{ stream_, format() }.writeData(teams);
  }
}
