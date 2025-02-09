#include <h3mtxt/H3MJsonReader/readObjectDetailsData.h>

#include <h3mtxt/H3MJsonReader/readCreatureStack.h>
#include <h3mtxt/H3MJsonReader/readPrimarySkills.h>
#include <h3mtxt/H3MJsonReader/readResources.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkill.h>

namespace h3m
{
  namespace Detail_NS
  {
    void readEventBase(const Json::Value& value, EventBase& event)
    {
      using Fields = FieldNames<EventBase>;

      readField(event.guardians, value, Fields::kGuardians);
      readField(event.experience, value, Fields::kExperience);
      readField(event.spell_points, value, Fields::kSpellPoints);
      readField(event.morale, value, Fields::kMorale);
      readField(event.luck, value, Fields::kLuck);
      readField(event.resources, value, Fields::kResources);
      readField(event.primary_skills, value, Fields::kPrimarySkills);
      readField(event.secondary_skills, value, Fields::kSecondarySkills);
      readField(event.artifacts, value, Fields::kArtifacts);
      readField(event.spells, value, Fields::kSpells);
      readField(event.creatures, value, Fields::kCreatures);
      readField(event.unknown, value, Fields::kUnknown);
    }
  }
}