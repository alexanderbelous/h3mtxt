# Structured representation of a saved game (.CGM, .GM1, .GM2, ...)

As with [Map](../Map) and [Campaign](../Campaign), this library only deals with representation of the saved game. Serialization is implemented in separate libraries.

## Coding conventions

### Namespaces

All the code in this library uses the namespace `h3svg`. This library does reuse some types from [Map](../Map), but it does so by reintroducing them into the namespace `h3svg`.

### Type names

A lot of structures are encoded in H3SVG (the file format for saved games) differently from how they are encoded in H3M (the file format for maps). For example, if the victory condition is "Defeat hero", H3SVG stores the hero's type, whereas H3M stores the hero's coordinates. As a result, there are some classes in this library that have the same names as their counterparts from [Map](../Map): for example, `h3svg::VictoryCondition` is not the same type as `h3m::VictoryCondition`.

### Enums

H3SVG is very inconsistent, and a lot of enums are encoded using different width (the number of bytes) in different places. `ArtifactType` is a good example of this: it is sometimes encoded as an 8-bit integer, sometimes as a 16-bit integer, and sometimes even as a 32-bit integer. This brings a question - how to store such enums?
* Use a single type, e.g., `ArtifactType8` for everything
  * Pros: covenient
  * Cons: lossy
* Use raw integers
  * Pros: lossless
  * Cons: not type-safe
* Use different enum types
  * Pros: lossless and type-safe
  * Cons: no implicit conversions, e.g., `ArtifactType8` is not implicitly convertible to `ArtifactType32`

I chose to go with the latter, using different types for enums that have the same constants but different width.