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

h3m::Bool readBool(std::istream& stream)
{
  return static_cast<h3m::Bool>(readUint8(stream));
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

h3m::MainTown readMainTown(std::istream& stream)
{
  h3m::MainTown main_town;
  main_town.generate_hero = readBool(stream);
  main_town.town_type = readUint8(stream);
  main_town.x = readUint8(stream);
  main_town.y = readUint8(stream);
  main_town.z = readUint8(stream);
  return main_town;
}

h3m::StartingHero readStartingHero(std::istream& stream)
{
  h3m::StartingHero starting_hero;
  starting_hero.is_random = readBool(stream);
  starting_hero.type = readEnum<h3m::HeroType>(stream);
  starting_hero.face = readUint8(stream);
  starting_hero.name = readString(stream);
  return starting_hero;
}

h3m::AdditionalPlayerInfo readAdditionalPlayerInfo(std::istream& stream)
{
  h3m::AdditionalPlayerInfo additional_info;
  additional_info.num_placeholder_heroes = readUint8(stream);
  const std::uint32_t num_heroes = readUint<std::uint32_t>(stream);
  additional_info.heroes.reserve(num_heroes);
  for (std::uint32_t i = 0; i < num_heroes; ++i)
  {
    h3m::AdditionalPlayerInfo::HeroInfo hero;
    hero.type = readEnum<h3m::HeroType>(stream);
    hero.name = readString(stream);
    additional_info.heroes.push_back(std::move(hero));
  }
  return additional_info;
}

h3m::PlayerSpecs readPlayerSpecs(std::istream& stream)
{
  h3m::PlayerSpecs player;
  player.can_be_human = readBool(stream);
  player.can_be_computer = readBool(stream);
  player.behavior = readEnum<h3m::PlayerBehavior>(stream);
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

}

h3m::Map parseh3m(std::istream& stream)
{
  h3m::Map map;
  map.format = readEnum<h3m::MapFormat>(stream);
  map.basic_info.is_playable = readBool(stream);
  map.basic_info.map_size = readUint<std::uint32_t>(stream);
  map.basic_info.has_two_levels = readBool(stream);
  map.basic_info.name = readString(stream);
  map.basic_info.description = readString(stream);
  map.basic_info.difficulty = readEnum<h3m::MapDifficulty>(stream);
  map.basic_info.max_hero_level = readUint8(stream);
  for (int i = 0; i < h3m::kMaxPlayers; ++i)
  {
    map.players[i] = readPlayerSpecs(stream);
  }
  return map;
}

}
