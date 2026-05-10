#pragma once

// This header is not used by the Map library itself, but it is used in h3mtxt
// to avoid code duplication in H3MReader and H3MWriter.

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/MapFormat.h>

#include <type_traits>

namespace h3m
{
  // Provides a way to detect the presence of features introduced in the expansion packs
  // ("Armageddon's Blade" and "The Shadow of Death").
  //
  // A reasonable alternative could be to put these feature-testing functions in
  // the headers that define the affected classes; however, I chose to put them
  // here to avoid "polluting" those headers/classes.
  struct FeatureTesting
  {
    // Returns the number of bytes used to serialize the specified enum type.
    //
    // The number of bytes used to store a value differs for some enum types
    // between different versions of the H3M file format. For example, CreatureType
    // used to be serialized as 1 byte in "The Restoration of Erathia", but in
    // "Armageddon's Blade" this was changed to 2 bytes.
    //
    // \param Enum - input enum type.
    // \return the number of bytes used to serialize the specified enum type.
    template<class Enum>
    constexpr std::size_t getEnumSize() const noexcept;

    // Returns the number of meaningful bytes in the specified bitmask.
    //
    // The number of bytes used to store a bitmask differs for some bitmasks
    // between different versions of the H3M file format. For example,
    // "The Restoration of Erathia" only had 8 towns, so TownsBitmask was
    // stored as a 1 byte, but in "Armageddon's Blade" this was changed to
    // 2 bytes because the Conflux town was introduced.
    //
    // \param Bitmask - type of the bitmask.
    // \return the number of meaningful bytes in @Bitmask.
    template<class Bitmask>
    constexpr std::size_t getBitmaskSize() const noexcept;

    // \return whether "Map Specifications" / "General" / "Limit hero experience level to" can be customized,
    //         i.e. whether MapBasicInfo::max_hero_level is meaningful.
    constexpr bool maxHeroLevel() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether "Customize" can be set in "Map Specifications" / "Player Specs" / "Allowed Alignments",
    //         i.e. whether PlayerSpecs::has_customized_alignments is meaningful.
    constexpr bool customizedAlignments() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether "Map Specifications" / "Player Specs" / "Generate hero at main town" can be customized,
    //         i.e. whether MainTown::generate_hero is meaningful.
    constexpr bool generateHeroAtMainTown() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether the type of the main town is explicitly stored in H3M,
    //         i.e. whether MainTown::town_type is meaningful.
    constexpr bool mainTownType() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether the number of non-specific placeholder heroes is explicitly stored in H3M,
    //         i.e. whether PlayerSpecs::num_nonspecific_placeholder_heroes is meaningful.
    constexpr bool numNonspecificPlaceholderHeroes() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether the player's starting heroes are explicitly stored in H3M,
    //         i.e. whether PlayerSpecs::heroes is meaningful.
    constexpr bool startingHeroes() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether MapAdditionalInfo::custom_heroes is meaningful.
    constexpr bool customHeroes() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether MapAdditionalInfo::disabled_spells is meaningful.
    constexpr bool disabledSpells() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether MapAdditionalInfo::disabled_skills is meaningful.
    constexpr bool disabledSkills() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether MapAdditionalInfo::heroes_settings is meaningful.
    constexpr bool heroesSettings() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::GARRISON>::can_remove_units is meaningful.
    constexpr bool garrisonCanRemoveUnits() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::HERO>::absod_id is meaningful.
    constexpr bool heroAbsodId() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::HERO>::experience is optional.
    constexpr bool heroOptionalExperience() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::HERO>::gender is meaningful.
    constexpr bool heroGender() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::HERO>::primary_skills is optional.
    constexpr bool heroOptionalPrimarySkills() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether HeroArtifacts::equipped[ArtifactSlot::Misc5] is meaningful.
    constexpr bool artifactSlotMisc5() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::MONSTER>::absod_id is meaningful.
    constexpr bool monsterAbsodId() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether Quests other than "Return with artifact" are supported.
    constexpr bool customQuests() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::TOWN>::absod_id is meaningful.
    constexpr bool townAbsodId() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::TOWN>::must_have_spell is meaningful.
    constexpr bool townMustHaveSpell() const noexcept
    {
      return format >= MapFormat::ArmageddonsBlade;
    }

    // \return whether TimedEvent::applies_to_human is meaningful.
    constexpr bool eventAppliesToHuman() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // \return whether ObjectProperties<ObjectPropertiesType::TOWN>::alignment is meaningful.
    constexpr bool townAlignment() const noexcept
    {
      return format >= MapFormat::ShadowOfDeath;
    }

    // Format of the map.
    MapFormat format = MapFormat::ShadowOfDeath;
  };

  // The default implementation returns sizeof(Enum) - the underlying types of enums are
  // expected to match the actual integer types used in "The Shadow of Death".
  template<class Enum>
  constexpr std::size_t FeatureTesting::getEnumSize() const noexcept
  {
    static_assert(std::is_enum_v<Enum>, "Must be an enum type.");
    return sizeof(Enum);
  }

  // Specialization for ArtifactType.
  template<>
  constexpr std::size_t FeatureTesting::getEnumSize<ArtifactType>() const noexcept
  {
    return format >= MapFormat::ArmageddonsBlade ? 2 : 1;
  }

  // Specialization for CreatureType.
  template<>
  constexpr std::size_t FeatureTesting::getEnumSize<CreatureType>() const noexcept
  {
    return format >= MapFormat::ArmageddonsBlade ? 2 : 1;
  }

  // Specialization for ArtifactsBitmask.
  template<>
  constexpr std::size_t FeatureTesting::getBitmaskSize<ArtifactsBitmask>() const noexcept
  {
    switch (format)
    {
    // In RoE ArtifactsBitmask is never serialized at all, which is equivalent
    // to saying that it has 0 meaningful bytes.
    case MapFormat::RestorationOfErathia:
      return 0;
    case MapFormat::ArmageddonsBlade:
      return 17;
    case MapFormat::ShadowOfDeath:
    default:
      return 18;
    }
  }

  // Specialization for HeroesBitmask.
  template<>
  constexpr std::size_t FeatureTesting::getBitmaskSize<HeroesBitmask>() const noexcept
  {
    return format >= MapFormat::ArmageddonsBlade ? 20 : 16;
  }

  // Specialization for TownsBitmask.
  template<>
  constexpr std::size_t FeatureTesting::getBitmaskSize<TownsBitmask>() const noexcept
  {
    return format >= MapFormat::ArmageddonsBlade ? 2 : 1;
  }
}
