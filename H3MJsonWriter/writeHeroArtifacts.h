#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::HeroArtifacts>
  {
    void operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
    {
      using Fields = h3m::FieldNames<h3m::HeroArtifacts>;
      // TODO: print artifacts' names in comments.
      out.writeField(Fields::kHeadwear, value.headwear);
      out.writeField(Fields::kShoulders, value.shoulders);
      out.writeField(Fields::kNeck, value.neck);
      out.writeField(Fields::kRightHand, value.right_hand);
      out.writeField(Fields::kLeftHand, value.left_hand);
      out.writeField(Fields::kTorso, value.torso);
      out.writeField(Fields::kRightRing, value.right_ring);
      out.writeField(Fields::kLeftRing, value.left_ring);
      out.writeField(Fields::kFeet, value.feet);
      out.writeField(Fields::kMisc1, value.misc1);
      out.writeField(Fields::kMisc2, value.misc2);
      out.writeField(Fields::kMisc3, value.misc3);
      out.writeField(Fields::kMisc4, value.misc4);
      out.writeField(Fields::kMisc5, value.misc5);
      out.writeField(Fields::kDevice1, value.device1);
      out.writeField(Fields::kDevice2, value.device2);
      out.writeField(Fields::kDevice3, value.device3);
      out.writeField(Fields::kDevice4, value.device4);
      out.writeField(Fields::kSpellbook, value.spellbook);
      out.writeField(Fields::kBackpack, value.backpack);
    }
  };
}
