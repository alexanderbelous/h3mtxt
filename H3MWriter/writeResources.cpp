#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/Resources.h>

namespace h3m
{
  void H3Writer<Resources>::operator()(std::ostream& stream, const Resources& resources) const
  {
    writeData(stream, resources.data);
  }
}
