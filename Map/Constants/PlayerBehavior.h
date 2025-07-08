#pragma once

#include <cstdint>

namespace h3m
{

enum class PlayerBehavior : std::uint8_t
{
  Random = 0,
  Warrior = 1,
  Builder = 2,
  Explorer = 3,
  // The Map Editor only allows setting behavior to one of the values above, but you can set it to 4,
  // which will be displayed as "Human" in the Tavern even if the player is controlled by the computer.
  // I'm not sure how that actually affects AI's behavior.
  // Human = 4,
  //
  // VCMI also defines None = -1.
};

}
