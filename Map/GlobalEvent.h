#pragma once

#include <h3mtxt/Map/TimedEventBase.h>

namespace h3m
{

// GlobalEvent doesn't actually have any extra fields, but I want it to be different type.
struct GlobalEvent : TimedEventBase
{
};

}
