#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace h3m
{
  HeroArtifacts JsonReader<HeroArtifacts>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<HeroArtifacts>;
    HeroArtifacts artifacts;
    readField(artifacts.headwear, value, Fields::kHeadwear);
    readField(artifacts.shoulders, value, Fields::kShoulders);
    readField(artifacts.neck, value, Fields::kNeck);
    readField(artifacts.right_hand, value, Fields::kRightHand);
    readField(artifacts.left_hand, value, Fields::kLeftHand);
    readField(artifacts.torso, value, Fields::kTorso);
    readField(artifacts.right_ring, value, Fields::kRightRing);
    readField(artifacts.left_ring, value, Fields::kLeftRing);
    readField(artifacts.feet, value, Fields::kFeet);
    readField(artifacts.misc1, value, Fields::kMisc1);
    readField(artifacts.misc2, value, Fields::kMisc2);
    readField(artifacts.misc3, value, Fields::kMisc3);
    readField(artifacts.misc4, value, Fields::kMisc4);
    readField(artifacts.misc5, value, Fields::kMisc5);
    readField(artifacts.device1, value, Fields::kDevice1);
    readField(artifacts.device2, value, Fields::kDevice2);
    readField(artifacts.device3, value, Fields::kDevice3);
    readField(artifacts.device4, value, Fields::kDevice4);
    readField(artifacts.spellbook, value, Fields::kSpellbook);
    readField(artifacts.backpack, value, Fields::kBackpack);
    return artifacts;
  }
}
