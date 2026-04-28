#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <string>

namespace h3svg
{
  // The equivalent of h3m::Rumor stored in the saved game.
  struct Rumor
  {
    std::string text;
    // Indicates whether this rumor has been displayed in the Tavern.
    // This doesn't necessarily mean that the player has read this rumor - the value is set to 1
    // when this rumor becomes the "rumor of the week", not when the player sees it in the Tavern.
    // Note, however, that the value can be reset from 1 to 0 sometimes - I'm not sure why.
    Bool has_been_shown = false;
  };
}
