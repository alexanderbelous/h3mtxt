#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/H3SvgJsonWriter/writeEnumIndexedArray.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/Hero.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3svg::HeroArtifact>::operator()(FieldsWriter& out, const h3svg::HeroArtifact& artifact) const
  {
    out.writeField("type", artifact.type);
    if (auto enum_str = getEnumString(artifact.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField("spell_type", artifact.spell_type);
    if (artifact.type == static_cast<h3svg::ArtifactType32>(h3m::ArtifactType::SpellScroll))
    {
      if (auto enum_str = getEnumString(artifact.spell_type); !enum_str.empty())
      {
        out.writeComment(enum_str, false);
      }
    }
  }

  void JsonObjectWriter<h3svg::HeroArtifacts>::operator()(FieldsWriter& out,
                                                          const h3svg::HeroArtifacts& artifacts) const
  {
    out.writeField("equipped", artifacts.equipped);
    out.writeField("backpack", artifacts.backpack);
  }

  void JsonObjectWriter<h3svg::Hero>::operator()(FieldsWriter& out, const h3svg::Hero& hero) const
  {
    using Fields = h3json::FieldNames<h3svg::Hero>;

    out.writeField(Fields::kX, hero.x);
    out.writeField(Fields::kY, hero.y);
    out.writeField(Fields::kZ, hero.z);
    out.writeField(Fields::kIsVisible, hero.is_visible);
    out.writeField(Fields::kCoordinatesPacked, hero.coordinates_packed);
    out.writeField(Fields::kObjectClassUnder, hero.object_class_under);
    if (std::string_view enum_str = getEnumString(hero.object_class_under); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown1, hero.unknown1);
    out.writeField(Fields::kIsFemale, hero.is_female);
    out.writeField(Fields::kUseCustomBiography, hero.use_custom_biography);
    out.writeField(Fields::kBiography, hero.biography);
    out.writeField(Fields::kOwner, hero.owner);
    if (std::string_view enum_str = getEnumString(hero.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kPatrolRadius, hero.patrol_radius);
    out.writeField(Fields::kUnknown2, hero.unknown2);
    out.writeField(Fields::kType, hero.type);
    if (std::string_view enum_str = getEnumString(hero.type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kHeroClass, hero.hero_class);
    if (std::string_view enum_str = getEnumString(hero.hero_class); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kPortrait, hero.portrait);
    if (std::string_view enum_str = getEnumString(hero.portrait); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kPatrolX, hero.patrol_x);
    out.writeField(Fields::kPatrolY, hero.patrol_y);
    out.writeField(Fields::kUnknown3, hero.unknown3);
    out.writeField(Fields::kDestinationX, hero.destination_x);
    out.writeField(Fields::kDestinationY, hero.destination_y);
    out.writeField(Fields::kDestinationZ, hero.destination_z);
    out.writeField(Fields::kUnknown4, hero.unknown4);
    out.writeField(Fields::kMovePointsMax, hero.move_points_max);
    out.writeField(Fields::kMovePoints, hero.move_points);
    out.writeField(Fields::kExperience, hero.experience);
    out.writeField(Fields::kUnknown5, hero.unknown5);
    out.writeField(Fields::kSpellPoints, hero.spell_points);
    out.writeField(Fields::kLevel, hero.level);
    out.writeField(Fields::kUnknown6, hero.unknown6);
    out.writeField(Fields::kArmy, hero.army);
    out.writeField(Fields::kName, hero.name);
    out.writeField(Fields::kSecondarySkillsLevels, hero.secondary_skills_levels);
    out.writeField(Fields::kSecondarySkillsSlots, hero.secondary_skills_slots);
    out.writeField(Fields::kPrimarySkills, hero.primary_skills);
    out.writeField(Fields::kSpellsLearned, hero.spells_learned);
    out.writeField(Fields::kSpellsAvailable, hero.spells_available);
    out.writeField(Fields::kArtifacts, hero.artifacts);
    out.writeField(Fields::kUnknown7, hero.unknown7);
  }
}
