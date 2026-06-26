#pragma once

#include <cstdint>

namespace h3m
{
  enum class ResourceType : std::int8_t
  {
    // Special constants that can only be used in campaigns when specifying the resource type
    // in the starting bonus.
    WoodOre                  = -3,  // 0xFD
    MercurySulfurCrystalGems = -2,  // 0xFE

    Wood                     =  0,  // 0x00
    Mercury                  =  1,  // 0x01
    Ore                      =  2,  // 0x02
    Sulfur                   =  3,  // 0x03
    Crystal                  =  4,  // 0x04
    Gems                     =  5,  // 0x05
    Gold                     =  6,  // 0x06
  };
}
