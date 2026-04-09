# Header-only library that provides a structured representation of a .h3m map

A .h3m map is represented by the struct [`h3m::Map`](Map.h).

The goal of h3mtxt is to provide a convenient way to modify *almost* any byte/value in a .h3m map. There are 2 exceptions, however:
* H3M uses `uint8` for "boolean" values that indicate whether the next field is present or not. In h3mtxt such fields are stored as `std::optional`, so [H3Writer](../H3Writer) will always write either 0 or 1 to indicate the presence of a field.
* Unknown enum values are generally accepted (there are nice use cases for this, for example, `CreatureType{146}` is a Ballista, even though neither the official Editor nor Unleashed Editor allow setting Ballista where a creature is expected). However, in some places enum fields specify the *type* of the next field (e.g., in [`h3m::VictoryCondition`](VictoryCondition.h)). If the value of such an enum field is out of range, it's not clear what should be read/written after it. h3mtxt uses `std::variant` in cases like that, making it impossible to use invalid enum values.

All classes in this library deal only with representing the map and providing convenient getters/setters.
Serialization/deserialization is implemented in other libraries (e.g., [H3Reader](../H3Reader), [H3Writer](../H3Writer), [H3JsonWriter](../H3JsonWriter)).

All classes in this library are [*EqualityComparable*](https://en.cppreference.com/w/cpp/named_req/EqualityComparable). This isn't used in h3mtxt itself (only in tests), but it can be useful if you use h3mtxt as a library. The semantics is always the same: two objects are considered equal if they are serialized as the same sequence of bytes in the H3M file format.
