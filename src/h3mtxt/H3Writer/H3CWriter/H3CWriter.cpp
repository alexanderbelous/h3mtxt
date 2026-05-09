#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>

#include <stdexcept>

namespace h3m
{
  H3CWriter::H3CWriter(std::ostream& stream, CampaignFormat format):
    H3WriterBase{ stream },
    format_{ format }
  {
    if (format != CampaignFormat::ArmageddonsBlade && format != CampaignFormat::ShadowOfDeath)
    {
      throw std::invalid_argument("H3CReader: invalid CampaignFormat.");
    }
  }

  void H3CWriter::writeData(const std::string& value) const
  {
    writeString32(value);
  }
}
