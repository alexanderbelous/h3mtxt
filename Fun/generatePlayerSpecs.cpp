#include <h3mtxt/Fun/generatePlayerSpecs.h>

#include <stdexcept>

namespace h3m
{
  PlayerSpecs generatePlayerSpecsNoTown(bool can_be_human, HeroType hero)
  {
    if (hero == HeroType{0xFF})
    {
      // TODO: actually, it's fine if it's 0xFF, we just shouldn't add this hero to PlayerSpecs::heroes.
      throw std::invalid_argument("generatePlayerSpecsNoTown(): hero shouldn't be 0xFF.");
    }

    return PlayerSpecs
    {
      .can_be_human = can_be_human,
      .can_be_computer = true,
      .behavior = PlayerBehavior::Random,
      .customized_alignments = false,
      .allowed_alignments {},
      .random_town = false,
      .main_town {},
      .has_random_heroes = false,
      .starting_hero {
        .type = hero,
        .portrait = HeroPortrait::DEFAULT
      },
      .num_nonspecific_placeholder_heroes = 0,
      .heroes {
        PlayerSpecs::HeroInfo {.type = hero, .name {}}
      }
    };
  }
}