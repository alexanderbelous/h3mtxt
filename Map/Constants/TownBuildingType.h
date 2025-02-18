#pragma once

#include <cstdint>

namespace h3m
{
  enum class TownBuildingType : std::uint8_t
  {
    TownHall = 0,
    CityHall = 1,
    Capitol = 2,
    Fort = 3,
    Citadel = 4,
    Castle = 5,
    Tavern = 6,
    Blacksmith = 7,

    Marketplace = 8,
    ResourceSilo = 9,
    ArtifactMerchants = 10,
    MageGuild1 = 11,
    MageGuild2 = 12,
    MageGuild3 = 13,
    MageGuild4 = 14,
    MageGuild5 = 15,

    Shipyard  = 16,
    Grail = 17,
    // Lighthouse | Mystic Pond | Library | brimstoneStormclouds |
    // coverOfDarkness | manaVortex | escapeTunnel | cageOfWarlords | magicUniversity
    SpecialBuilding1 = 18, 
    // brotherhoodOfSword | fountainOfFortune | wallOfKnowledge | castleGate |
    // necromancyAmplifier | portalOfSummoning | freelancerGuild | glyphsOfFear
    SpecialBuilding2 = 19,
    // Stables | Treasury | Lookout Tower | Order Of Fire | skeletonTransformer |
    // battleScholarAcademy | ballistaYard | bloodObelisk
    SpecialBuilding3 = 20,
    // Hall of Valhalla
    SpecialBuilding4 = 21,
    Dwelling1 = 22,
    Dwelling1U = 23,

    Horde1 = 24,
    Dwelling2 = 25,
    Dwelling2U = 26,
    Horde2 = 27,
    Dwelling3 = 28,
    Dwelling3U = 29,
    Horde3 = 30,
    Dwelling4 = 31,

    Dwelling4U = 32,
    Horde4 = 33,
    Dwelling5 = 34,
    Dwelling5U = 35,
    Horde5 = 36,
    Dwelling6 = 37,
    Dwelling6U = 38,
    Dwelling7 = 39,

    Dwelling7U = 40,
  };
}
