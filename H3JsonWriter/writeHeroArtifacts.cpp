#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/JsonWriter.h>
#include <h3mtxt/Map/HeroArtifacts.h>

namespace Medea_NS
{
  namespace
  {
    void writeArtifact(FieldsWriter& out, std::string_view field_name, h3m::ArtifactType artifact)
    {
      out.writeField(field_name, artifact);
      const std::string_view enum_str = artifact == h3m::ArtifactType{0xFFFF} ? "(Default)"
                                                                              : h3m::getEnumString(artifact);
      if (!enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const
  {
    using Fields = h3m::FieldNames<h3m::HeroArtifacts>;
    writeArtifact(out, Fields::kHead, value.head);
    writeArtifact(out, Fields::kShoulders, value.shoulders);
    writeArtifact(out, Fields::kNeck, value.neck);
    writeArtifact(out, Fields::kRightHand, value.right_hand);
    writeArtifact(out, Fields::kLeftHand, value.left_hand);
    writeArtifact(out, Fields::kTorso, value.torso);
    writeArtifact(out, Fields::kRightRing, value.right_ring);
    writeArtifact(out, Fields::kLeftRing, value.left_ring);
    writeArtifact(out, Fields::kFeet, value.feet);
    writeArtifact(out, Fields::kMisc1, value.misc1);
    writeArtifact(out, Fields::kMisc2, value.misc2);
    writeArtifact(out, Fields::kMisc3, value.misc3);
    writeArtifact(out, Fields::kMisc4, value.misc4);
    writeArtifact(out, Fields::kMisc5, value.misc5);
    writeArtifact(out, Fields::kWarMachine1, value.war_machine1);
    writeArtifact(out, Fields::kWarMachine2, value.war_machine2);
    writeArtifact(out, Fields::kWarMachine3, value.war_machine3);
    writeArtifact(out, Fields::kWarMachine4, value.war_machine4);
    writeArtifact(out, Fields::kSpellbook, value.spellbook);
    out.writeField(Fields::kBackpack, value.backpack);
  }
}
