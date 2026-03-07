#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/SavedGame/HeroSvg.h>

namespace h3svg
{
  HeroSvg H3SvgReader::readHero() const
  {
    HeroSvg hero;
    hero.x = readInt<std::int16_t>();
    hero.y = readInt<std::int16_t>();
    hero.z = readInt<std::int16_t>();
    hero.is_visible = readBool();
    // TODO: use a custom class.
    hero.coordinates_packed = readInt<std::uint32_t>();
    hero.object_class_under = readEnum<ObjectClass>();
    hero.unknown1 = readByteArray<7>();
    hero.biography = readString32();
    readBytes(std::as_writable_bytes(std::span{hero.unknown2}));
    hero.army = readTroops();
    readBytes(std::as_writable_bytes(std::span{hero.name}));
    readBytes(std::as_writable_bytes(std::span{hero.unknown3}));
    return hero;
  }
}
