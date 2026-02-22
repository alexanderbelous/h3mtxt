#pragma once

namespace h3m
{
  // Stores the names of JSON fields for the specified class.
  // This is to ensure that the same names are used when serializing and
  // deserializing an object of type T as JSON:
  // * A typo in a string will only be discovered at runtime, but a typo in a static
  //   data member will cause a compilation error.
  // * This also guarantees that these strings are only stored once in the binary,
  //   even if string pooling is disabled.
  template<class T>
  struct FieldNames;
}
