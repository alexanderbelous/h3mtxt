#pragma once

#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::HeroArtifacts>
  {
    void operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
    {
      out.writeField("headwear", value.headwear);
      out.writeField("shoulders", value.shoulders);
      out.writeField("neck", value.neck);
      out.writeField("right_hand", value.right_hand);
      out.writeField("left_hand", value.left_hand);
      out.writeField("torso", value.torso);
      out.writeField("right_ring", value.right_ring);
      out.writeField("left_ring", value.left_ring);
      out.writeField("feet", value.feet);
      out.writeField("misc1", value.misc1);
      out.writeField("misc2", value.misc2);
      out.writeField("misc3", value.misc3);
      out.writeField("misc4", value.misc4);
      out.writeField("device1", value.device1);
      out.writeField("device2", value.device2);
      out.writeField("device3", value.device3);
      out.writeField("device4", value.device4);
      out.writeField("spellbook", value.spellbook);
      out.writeField("misc5", value.misc5);
      out.writeField("backpack", value.backpack);
    }
  };
}
