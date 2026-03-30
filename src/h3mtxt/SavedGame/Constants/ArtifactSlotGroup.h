#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ArtifactSlot.h>

#include <cstdint>
#include <stdexcept>

namespace h3svg
{
  // Represents a more abstract concept of a slot than h3m::ArtifactSlot.
  //
  // h3m::ArtifactSlot represents a specific slot on the Hero Screen. However, some slots are interchangable -
  // for example, any Ring can be worn on either ArtifactSlot::LeftRing or ArtifactSlot::RightRing.
  //
  // In H3SVG there is a case where these "slot groups" are explicitly used to specify which slots are locked
  // by combination artifacts. Locks are not assigned to specific ArtifactSlots - instead, the number of locks
  // is specified for each ArtifactSlotGroup.
  enum class ArtifactSlotGroup : std::uint8_t
  {
    Head        = 0,
    Shoulders   = 1,  // Capes
    Neck        = 2,
    RightHand   = 3,  // Swords
    LeftHand    = 4,  // Shields
    Torso       = 5,  // Breastplates
    Ring        = 6,
    Feet        = 7,
    Misc        = 8,
    WarMachine1 = 9,  // Ballista
    WarMachine2 = 10, // Ammo Cart
    WarMachine3 = 11, // First Aid Tent
    WarMachine4 = 12, // Catapult
    Spellbook   = 13
  };

  // Cardinality of ArtifactSlotGroup.
  inline constexpr std::uint8_t kNumArtifactSlotGroups = 14;

  // Returns the corresponding ArtifactSlotGroup for the given ArtifactSlot.
  // \param artifact_slot - input artifact slot.
  // \return ArtifactSlotGroup for @artifact_slot
  constexpr ArtifactSlotGroup getArtifactSlotGroup(ArtifactSlot artifact_slot)
  {
    switch (artifact_slot)
    {
    case ArtifactSlot::Head:
      return ArtifactSlotGroup::Head;
    case ArtifactSlot::Shoulders:
      return ArtifactSlotGroup::Shoulders;
    case ArtifactSlot::Neck:
      return ArtifactSlotGroup::Neck;
    case ArtifactSlot::RightHand:
      return ArtifactSlotGroup::RightHand;
    case ArtifactSlot::LeftHand:
      return ArtifactSlotGroup::LeftHand;
    case ArtifactSlot::Torso:
      return ArtifactSlotGroup::Torso;
    case ArtifactSlot::RightRing:
    case ArtifactSlot::LeftRing:
      return ArtifactSlotGroup::Ring;
    case ArtifactSlot::Feet:
      return ArtifactSlotGroup::Feet;
    case ArtifactSlot::Misc1:
    case ArtifactSlot::Misc2:
    case ArtifactSlot::Misc3:
    case ArtifactSlot::Misc4:
    case ArtifactSlot::Misc5:
      return ArtifactSlotGroup::Misc;
    case ArtifactSlot::WarMachine1:
      return ArtifactSlotGroup::WarMachine1;
    case ArtifactSlot::WarMachine2:
      return ArtifactSlotGroup::WarMachine2;
    case ArtifactSlot::WarMachine3:
      return ArtifactSlotGroup::WarMachine3;
    case ArtifactSlot::WarMachine4:
      return ArtifactSlotGroup::WarMachine4;
    case ArtifactSlot::Spellbook:
      return ArtifactSlotGroup::Spellbook;
    default:
      throw std::invalid_argument("getSlotGroup(): invalid ArtifactSlot");
    }
  }
}
