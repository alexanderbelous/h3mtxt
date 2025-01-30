#include <h3mtxt/Fun/generatePlayerSpecs.h>

namespace h3m
{
  PlayerSpecs generatePlayerSpecsNoTown(bool can_be_human, HeroType hero)
  {
    return PlayerSpecs
    {
      .can_be_human = can_be_human,
      .can_be_computer = true,
      .behavior = PlayerBehavior::Random,
      .customized_alignments = false,
      .allowed_alignments {},
      .random_town = false,
      .main_town {},
      .starting_hero {
        .is_random = false,
        .type = hero,
        .portrait = HeroPortrait::DEFAULT
      },
      .additional_info {
        .num_placeholder_heroes = 0,
        .heroes {
          AdditionalPlayerInfo::HeroInfo {.type = hero, .name {}}
        }
      }
    };
  }
}