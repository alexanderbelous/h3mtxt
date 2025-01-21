#pragma once

#include <iosfwd>

namespace h3m
{
  struct TimedEventBase;

  void readTimedEventBase(std::istream& stream, TimedEventBase& event);
}
