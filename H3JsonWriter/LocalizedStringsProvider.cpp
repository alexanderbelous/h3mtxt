#include <h3mtxt/H3JsonWriter/LocalizedStringsProvider.h>

#include <h3mtxt/H3JsonWriter/LocalizedStringId.h>
#include <h3mtxt/H3JsonWriter/LocalizedStringsReader.h>

#include <utility>

// std::istrstream has been deprecated since C++98 and will be removed in C++26.
// However, the new replacement - std::basic_ispanstream - only appeared in C++23.
#ifdef __cpp_lib_spanstream
#include <spanstream>
#else
#include <strstream>
#endif

namespace h3m::H3JsonWriter_NS
{
  namespace
  {
    // #embed will only appear in C++26 (or C23), so just a string literal for now.
    static constexpr std::string_view kDefaultResource =
R"(Spellbook
Spell scroll
Grail
Catapult
Ballista
Ammo Cart
First Aid Tent
Centaur's Axe
Blackshard of the Dead Knight
Greater Gnoll's Flail
Ogre's Club of Havoc
Sword of Hellfire
Titan's Gladius
Shield of the Dwarven Lords
Shield of the Yawning Dead
Buckler of the Gnoll King
Targ of the Rampaging Ogre
Shield of the Damned
Sentinel's Shield
Helm of the Alabaster Unicorn
Skull Helmet
Helm of Chaos
Crown of the Supreme Magi
Hellstorm Helmet
Thunder Helmet
Breastplate of Petrified Wood
Rib Cage
Scales of the Greater Basilisk
Tunic of the Cyclops King
Breastplate of Brimstone
Titan's Cuirass
Armor of Wonder
Sandals of the Saint
Celestial Necklace of Bliss
Lion's Shield of Courage
Sword of Judgement
Helm of Heavenly Enlightenment
Quiet Eye of the Dragon
Red Dragon Flame Tongue
Dragon Scale Shield
Dragon Scale Armor
Dragonbone Greaves
Dragon Wing Tabard
Necklace of Dragonteeth
Crown of Dragontooth
Still Eye of the Dragon
Clover of Fortune
Cards of Prophecy
Ladybird of Luck
Badge of Courage
Crest of Valor
Glyph of Gallantry
Speculum
Spyglass
Amulet of the Undertaker
Vampire's Cowl
Dead Man's Boots
Garniture of Interference
Surcoat of Counterpoise
Boots of Polarity
Bow of Elven Cherrywood
Bowstring of the Unicorn's Mane
Angel Feather Arrows
Bird of Perception
Stoic Watchman
Emblem of Cognizance
Statesman's Medal
Diplomat's Ring
Ambassador's Sash
Ring of the Wayfarer
Equestrian's Gloves
Necklace of Ocean Guidance
Angel Wings
Charm of Mana
Talisman of Mana
Mystic Orb of Mana
Collar of Conjuring
Ring of Conjuring
Cape of Conjuring
Orb of the Firmament
Orb of Silt
Orb of Tempestuous Fire
Orb of Driving Rain
Recanter's Cloak
Spirit of Oppression
Hourglass of the Evil Hour
Tome of Fire Magic
Tome of Air Magic
Tome of Water Magic
Tome of Earth Magic
Boots of Levitation
Golden Bow
Sphere of Permanence
Orb of Vulnerability
Ring of Vitality
Ring of Life
Vial of Lifeblood
Necklace of Swiftness
Boots of Speed
Cape of Velocity
Pendant of Dispassion
Pendant of Second Sight
Pendant of Holiness
Pendant of Life
Pendant of Death
Pendant of Free Will
Pendant of Negativity
Pendant of Total Recall
Pendant of Courage
Everflowing Crystal Cloak
Ring of Infinite Gems
Everpouring Vial of Mercury
Inexhaustible Cart of Ore
Eversmoking Ring of Sulfur
Inexhaustible Cart of Lumber
Endless Sack of Gold
Endless Bag of Gold
Endless Purse of Gold
Legs of Legion
Loins of Legion
Torso of Legion
Arms of Legion
Head of Legion
Sea Captain's Hat
Spellbinder's Hat
Shackles of War
Orb of Inhibition
Vial of Dragon Blood
Armageddon's Blade
Angelic Alliance
Cloak of the Undead King
Elixir of Life
Armor of the Damned
Statue of Legion
Power of the Dragon Father
Titan's Thunder
Admiral's Hat
Bow of the Sharpshooter
Wizard's Well
Ring of the Magi
Cornucopia
Diplomat's Suit
Mired in Neutrality
Ironfist of the Ogre
)";

    LocalizedStringsData readDefaultLocalizedStringsData()
    {
      // Use std::ispanstream if available (C++23).
#ifdef __cpp_lib_spanstream
      std::ispanstream stream(std::span<const char>(kDefaultResource.data(), kDefaultResource.size()));
#else
      // Use std::istrstream otherwise (deprecated, will be removed in C++26).
      std::istrstream stream(kDefaultResource.data(), kDefaultResource.size());
#endif
      return readLocalizedStringsFromStream(stream);
    }

    LocalizedStringsData makeLocalizedStringsData(LocalizedStringsData* data)
    {
      if (!data)
      {
        return readDefaultLocalizedStringsData();
      }
      else
      {
        // Overwrite missing strings with the strings from the default locale.
        const LocalizedStringsData default_data = readDefaultLocalizedStringsData();
        for (std::size_t i = 0; i < kNumLocalizedStringIds; ++i)
        {
          const LocalizedStringId id = static_cast<LocalizedStringId>(i);
          if (data->get(id).empty())
          {
            data->set(id, default_data.get(id));
          }
        }
        return std::move(*data);
      }
    }
  }

  LocalizedStringsProvider::LocalizedStringsProvider(LocalizedStringsData* data):
    data_(makeLocalizedStringsData(data))
  {}

  LocalizedStringsProvider& LocalizedStringsProvider::getOrCreate(LocalizedStringsData* data)
  {
    static LocalizedStringsProvider singleton(data);
    return singleton;
  }
}
