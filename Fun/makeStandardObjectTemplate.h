#pragma once

#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>

namespace h3m
{
  // Constructs "standard" ObjectTemplate for the given ObjectClass.
  //
  // Basically, the official Map Editor only allows using predefined ObjectTemplate
  // for each {ObjectClass, subclass} combination. For testing it is convenient to
  // replicate the same behavior.
  // \param object_class - ObjectClass of the object to construct.
  // \param object_subclass - subclass of @object_class.
  // \return the "standard" ObjectTemplate for @object_class.
  // \throw std::logic_error if the logic is not implemented for @object_class.
  ObjectTemplate makeStandardObjectTemplate(ObjectClass object_class, std::uint32_t object_subclass = 0);
}
