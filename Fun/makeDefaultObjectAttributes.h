#pragma once

#include <h3mtxt/Map/ObjectAttributes.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>

namespace h3m
{
  // Constructs "standard" ObjectAttributes for the given ObjectClass.
  //
  // Basically, the official Map Editor only allows using predefined ObjectAttributes
  // for each {ObjectClass, subclass} combination. For testing it is convenient to
  // replicate the same behavior.
  // \param object_class - ObjectClass of the object to construct.
  // \return the "standard" ObjectAttributes for @object_class.
  // \throw std::logic_error if the logic is not implemented for @object_class.
  ObjectAttributes makeDefaultObjectAttributes(ObjectClass object_class);

}
