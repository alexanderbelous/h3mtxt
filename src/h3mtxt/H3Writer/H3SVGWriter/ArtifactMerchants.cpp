#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ArtifactMerchants.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const ArtifactMerchants& artifact_merchants) const
  {
    writeData(artifact_merchants.artifacts);
  }
}
