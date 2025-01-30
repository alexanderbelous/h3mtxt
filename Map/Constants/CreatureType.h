#pragma once

#include <cstdint>

namespace h3m
{

enum class CreatureType : std::uint16_t
{
  PIKEMAN = 0,
  HALBERDIER = 1,
  ARCHER = 2,
  MARKSMAN = 3,
  GRIFFIN = 4,
  ROYAL_GRIFFIN = 5,
  SWORDSMAN = 6,
  CRUSADER = 7,
  MONK = 8,
  ZEALOT = 9,
  CAVALIER = 10,
  CHAMPION = 11,
  ANGEL = 12,
  ARCHANGEL = 13,
  CENTAUR = 14,
  CENTAUR_CAPTAIN = 15,
  DWARF = 16,
  BATTLE_DWARF = 17,
  WOOD_ELF = 18,
  GRAND_ELF = 19,
  PEGASUS = 20,
  SILVER_PEGASUS = 21,
  DENDROID_GUARD = 22,
  DENDROID_SOLDIER = 23,
  UNICORN = 24,
  WAR_UNICORN = 25,
  GREEN_DRAGON = 26,
  GOLD_DRAGON = 27,
  GREMLIN = 28,
  MASTER_GREMLIN = 29,
  STONE_GARGOYLE = 30,
  OBSIDIAN_GARGOYLE = 31,
  STONE_GOLEM = 32,
  IRON_GOLEM = 33,
  MAGE = 34,
  ARCH_MAGE = 35,
  GENIE = 36,
  MASTER_GENIE = 37,
  NAGA = 38,
  NAGA_QUEEN = 39,
  GIANT = 40,
  TITAN = 41,
  IMP = 42,
  FAMILIAR = 43,
  GOG = 44,
  MAGOG = 45,
  HELL_HOUND = 46,
  CERBERUS = 47,
  DEMON = 48,
  HORNED_DEMON = 49,
  PIT_FIEND = 50,
  PIT_LORD = 51,
  EFREETI = 52,
  EFREET_SULTAN = 53,
  DEVIL = 54,
  ARCH_DEVIL = 55,
  SKELETON = 56,
  SKELETON_WARRIOR = 57,
  WALKING_DEAD = 58,
  ZOMBIE = 59,
  WIGHT = 60,
  WRAITH = 61,
  VAMPIRE = 62,
  VAMPIRE_LORD = 63,
  LICH = 64,
  POWER_LICH = 65,
  BLACK_KNIGHT = 66,
  DREAD_KNIGHT = 67,
  BONE_DRAGON = 68,
  GHOST_DRAGON = 69,
  TROGLODYTE = 70,
  INFERNAL_TROGLODYTE = 71,
  HARPY = 72,
  HARPY_HAG = 73,
  BEHOLDER = 74,
  EVIL_EYE = 75,
  MEDUSA = 76,
  MEDUSA_QUEEN = 77,
  MINOTAUR = 78,
  MINOTAUR_KING = 79,
  MANTICORE = 80,
  SCORPICORE = 81,
  RED_DRAGON = 82,
  BLACK_DRAGON = 83,
  GOBLIN = 84,
  HOBGOBLIN = 85,
  WOLF_RIDER = 86,
  WOLF_RAIDER = 87,
  ORC = 88,
  ORC_CHIEFTAIN = 89,
  OGRE = 90,
  OGRE_MAGE = 91,
  ROC = 92,
  THUNDERBIRD = 93,
  CYCLOPS = 94,
  CYCLOPS_KING = 95,
  BEHEMOTH = 96,
  ANCIENT_BEHEMOTH = 97,
  GNOLL = 98,
  GNOLL_MARAUDER = 99,
  LIZARDMAN = 100,
  LIZARD_WARRIOR = 101,
  GORGON = 102,
  MIGHTY_GORGON = 103,
  SERPENT_FLY = 104,
  DRAGON_FLY = 105,
  BASILISK = 106,
  GREATER_BASILISK = 107,
  WYVERN = 108,
  WYVERN_MONARCH = 109,
  HYDRA = 110,
  CHAOS_HYDRA = 111,
  AIR_ELEMENTAL = 112,
  EARTH_ELEMENTAL = 113,
  FIRE_ELEMENTAL = 114,
  WATER_ELEMENTAL = 115,
  GOLD_GOLEM = 116,
  DIAMOND_GOLEM = 117,
  PIXIE = 118,
  SPRITE = 119,
  PSYCHIC_ELEMENTAL = 120,
  MAGIC_ELEMENTAL = 121,
  NOT_USED1 = 122,
  ICE_ELEMENTAL = 123,
  NOT_USED2 = 124,
  MAGMA_ELEMENTAL = 125,
  NOT_USED3 = 126,
  STORM_ELEMENTAL = 127,
  NOT_USED4 = 128,
  ENERGY_ELEMENTAL = 129,
  FIREBIRD = 130,
  PHOENIX = 131,
  AZURE_DRAGON = 132,
  CRYSTAL_DRAGON = 133,
  FAERIE_DRAGON = 134,
  RUST_DRAGON = 135,
  ENCHANTER = 136,
  SHARPSHOOTER = 137,
  HALFLING = 138,
  PEASANT = 139,
  BOAR = 140,
  MUMMY = 141,
  NOMAD = 142,
  ROGUE = 143,
  TROLL = 144,
  // Secret stuff.
  // Note that during battlefield it's only safe to put war machines as creatures if they are
  // units in the army of some hero who has secondary skills for these machines. Otherwise
  // (e.g., if you try to put them as neutral creatures), the game will crash when it's the
  // "War Machine's turn" (their speed is 0, so after all creatures).
  CATAPULT = 145,
  BALLISTA = 146,
  FIRST_AID_TENT = 147,
  AMMO_CART = 148,
  ARROW_TOWERS = 149,
  // NO_CREATURE = 0xFFFF
};

}
