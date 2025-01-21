#pragma once

#include <iosfwd>

namespace h3m
{
  struct Quest;

  // Reads Quest info from the stream.
  Quest readQuest(std::istream& stream);
}
