#pragma once

#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m
{
  // PlayerSpecs for a player that will not be present on the map.
  constexpr PlayerSpecs kAbsentPlayerSpecs {
      .can_be_human = false,
      .can_be_computer = false,
      .behavior = PlayerBehavior::Random,
      .customized_alignments = false,
      .allowed_alignments {},
      .random_town = false,
      .main_town {},
      .has_random_heroes = false,
      .starting_hero {
        .type = static_cast<HeroType>(0xFF)
      }
  };

  // Generates PlayerSpecs for a player that will only have 1 (non-random) hero on the map,
  // and won't have any towns.
  // \param can_be_human - boolean indicating whether this player can be human.
  // \param hero - starting hero for this player.
  // \return the generated PlayerSpecs.
  PlayerSpecs generatePlayerSpecsNoTown(bool can_be_human, HeroType hero);
}