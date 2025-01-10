#pragma once

#include <cstdint>

namespace h3m
{

// H3M file format uses a single byte to store a boolean. Normally, the stored value
// should be either 0 or 1, but there are some fields which sometimes store other values
// (interpreted as "true"). Just to be safe, h3mparser stores the exact value for boolean
// fields.
using Bool = std::uint8_t;

}
