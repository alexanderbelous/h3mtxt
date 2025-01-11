#include <h3mparser/parseh3m.h>

#include <istream>
#include <stdexcept>
#include <type_traits>

namespace h3m
{
namespace
{

// Reads a single byte from the given stream.
std::uint8_t readUint8(std::istream& stream)
{
  using Traits = std::istream::traits_type;
  if (!stream)
  {
    throw std::logic_error("Error in the input stream.");
  }
  const Traits::int_type character = stream.get();
  if (character == Traits::eof())
  {
    throw std::runtime_error("Unexpected end of stream.");
  }
  return static_cast<std::uint8_t>(character);
}

// Reads a little-endian unsigned integer.
std::uintmax_t readUintImpl(std::istream& stream, unsigned int num_bytes)
{
  std::uintmax_t result = 0;
  std::uintmax_t shift = 0;
  for (unsigned int i = 0; i < num_bytes; ++i)
  {
    const std::uint8_t byte = readUint8(stream);
    result |= (static_cast<std::uintmax_t>(byte) << shift);
    shift += 8;
  }
  return result;
}

// Reads a little-endian unsigned integer.
template<class T>
T readUint(std::istream& stream)
{
  static_assert(std::is_integral_v<T>, "T must be an integral type.");
  constexpr int kNumBytes = sizeof(T);
  // TODO: this is probably buggy for signed integers. Cast to a smaller unsigned type first.
  return static_cast<T>(readUintImpl(stream, kNumBytes));
}

Bool readBool(std::istream& stream)
{
  return static_cast<Bool>(readUint8(stream));
}

template<class T>
T readEnum(std::istream& stream)
{
  return static_cast<T>(readUint<std::underlying_type_t<T>>(stream));
}

std::string readString(std::istream& stream)
{
  const std::uint32_t length = readUint<std::uint32_t>(stream);
  std::string result;
  result.reserve(length);
  for (std::uint32_t i = 0; i < length; ++i)
  {
    result.push_back(static_cast<char>(readUint8(stream)));
  }
  return result;
}

MapBasicInfo readMapBasicInfo(std::istream& stream)
{
  MapBasicInfo basic_info;
  basic_info.is_playable = readBool(stream);
  basic_info.map_size = readUint<std::uint32_t>(stream);
  basic_info.has_two_levels = readBool(stream);
  basic_info.name = readString(stream);
  basic_info.description = readString(stream);
  basic_info.difficulty = readEnum<MapDifficulty>(stream);
  basic_info.max_hero_level = readUint8(stream);
  return basic_info;
}

MainTown readMainTown(std::istream& stream)
{
  MainTown main_town;
  main_town.generate_hero = readBool(stream);
  main_town.town_type = readEnum<TownType>(stream);
  main_town.x = readUint8(stream);
  main_town.y = readUint8(stream);
  main_town.z = readUint8(stream);
  return main_town;
}

StartingHero readStartingHero(std::istream& stream)
{
  StartingHero starting_hero;
  starting_hero.is_random = readBool(stream);
  starting_hero.type = readEnum<HeroType>(stream);
  starting_hero.face = readUint8(stream);
  starting_hero.name = readString(stream);
  return starting_hero;
}

AdditionalPlayerInfo readAdditionalPlayerInfo(std::istream& stream)
{
  AdditionalPlayerInfo additional_info;
  additional_info.num_placeholder_heroes = readUint8(stream);
  const std::uint32_t num_heroes = readUint<std::uint32_t>(stream);
  additional_info.heroes.reserve(num_heroes);
  for (std::uint32_t i = 0; i < num_heroes; ++i)
  {
    AdditionalPlayerInfo::HeroInfo hero;
    hero.type = readEnum<HeroType>(stream);
    hero.name = readString(stream);
    additional_info.heroes.push_back(std::move(hero));
  }
  return additional_info;
}

PlayerSpecs readPlayerSpecs(std::istream& stream)
{
  PlayerSpecs player;
  player.can_be_human = readBool(stream);
  player.can_be_computer = readBool(stream);
  player.behavior = readEnum<PlayerBehavior>(stream);
  player.customized_alignments = readUint8(stream);
  player.town_types = readUint8(stream);
  player.town_conflux = readUint8(stream);
  player.random_town = readUint8(stream);
  const bool has_main_town = readBool(stream);
  if (has_main_town)
  {
    player.main_town = readMainTown(stream);
  }
  player.starting_hero = readStartingHero(stream);
  player.additional_info = readAdditionalPlayerInfo(stream);
  return player;
}

VictoryCondition readVictoryCondition(std::istream& stream)
{
  const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>(stream);
  switch (victory_condition_type)
  {
  case VictoryConditionType::AcquireArtifact:
    {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details;
      details.allow_normal_win = readBool(stream);
      details.applies_to_computer = readBool(stream);
      details.artifact_type = readUint<std::uint16_t>(stream);
      return details;
    }
  case VictoryConditionType::Normal:
    return VictoryConditionDetails<VictoryConditionType::Normal>();
  default:
    throw std::runtime_error("Invalid victory condition type.");
  }
}

LossCondition readLossCondition(std::istream& stream)
{
  const LossConditionType loss_condition_type = readEnum<LossConditionType>(stream);
  switch (loss_condition_type)
  {
  case LossConditionType::LoseTown:
  {
    LossConditionDetails<LossConditionType::LoseTown> details;
    details.x = readUint8(stream);
    details.y = readUint8(stream);
    details.z = readUint8(stream);
    return details;
  }
  case LossConditionType::LoseHero:
  {
    LossConditionDetails<LossConditionType::LoseHero> details;
    details.x = readUint8(stream);
    details.y = readUint8(stream);
    details.z = readUint8(stream);
    return details;
  }
  case LossConditionType::TimeExpires:
  {
    LossConditionDetails<LossConditionType::TimeExpires> details;
    details.days = readUint<std::uint16_t>(stream);
    return details;
  }
  case LossConditionType::Normal:
    return LossConditionDetails<LossConditionType::Normal>();
  default:
    throw std::runtime_error("Invalid loss condition type.");
  }
}

MapAdditionalInfo readMapAdditionalInfo(std::istream& stream)
{
  MapAdditionalInfo additional_info;
  additional_info.victory_condition = readVictoryCondition(stream);
  additional_info.loss_condition = readLossCondition(stream);
  return additional_info;
}

}

Map parseh3m(std::istream& stream)
{
  Map map;
  map.format = readEnum<MapFormat>(stream);
  map.basic_info = readMapBasicInfo(stream);
  for (int i = 0; i < kMaxPlayers; ++i)
  {
    map.players[i] = readPlayerSpecs(stream);
  }
  map.additional_info = readMapAdditionalInfo(stream);
  return map;
}

}
