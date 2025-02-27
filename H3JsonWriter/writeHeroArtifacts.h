#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroArtifacts.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::HeroArtifacts>
  {
  private:
    void writeField(FieldsWriter& out, std::string_view field_name, h3m::ArtifactType artifact) const
    {
      out.writeField(field_name, artifact);
      const std::string_view enum_str = artifact == h3m::ArtifactType{0xFFFF} ? "(Default)"
                                                                              : h3m::getEnumString(artifact);
      if (!enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
    }

  public:
    void operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
    {
      using Fields = h3m::FieldNames<h3m::HeroArtifacts>;
      writeField(out, Fields::kHeadwear, value.headwear);
      writeField(out, Fields::kShoulders, value.shoulders);
      writeField(out, Fields::kNeck, value.neck);
      writeField(out, Fields::kRightHand, value.right_hand);
      writeField(out, Fields::kLeftHand, value.left_hand);
      writeField(out, Fields::kTorso, value.torso);
      writeField(out, Fields::kRightRing, value.right_ring);
      writeField(out, Fields::kLeftRing, value.left_ring);
      writeField(out, Fields::kFeet, value.feet);
      writeField(out, Fields::kMisc1, value.misc1);
      writeField(out, Fields::kMisc2, value.misc2);
      writeField(out, Fields::kMisc3, value.misc3);
      writeField(out, Fields::kMisc4, value.misc4);
      writeField(out, Fields::kMisc5, value.misc5);
      writeField(out, Fields::kDevice1, value.device1);
      writeField(out, Fields::kDevice2, value.device2);
      writeField(out, Fields::kDevice3, value.device3);
      writeField(out, Fields::kDevice4, value.device4);
      writeField(out, Fields::kSpellbook, value.spellbook);
      out.writeField(Fields::kBackpack, value.backpack);
    }
  };
}
