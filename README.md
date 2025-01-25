# h3mtxt
Command-line utility for converting .h3m files (maps for Heroes of Might and Magic 3) to a human-readable format or vice versa.

This tool is primarily intended for HoMM3 mapmakers who want to add undocumented features to their maps.

HoMM3 maps are written as (possibly gzip-encoded) binary data. Normally, they are edited via the official Map Editor (or the unofficial Unleashed Editor). However, both programs have limitations: for example, they don't allow selecting a specific terrain sprite for a tile. A possible workaround is to manually edit the binary data in a hex editor, but this is error-prone and can be time-consuming.

*h3mtxt* offers an alternative solution: instead of modifying a .h3m file direclty, you can first convert it to a human-readable format, edit it, and then convert it back to .h3m.

Or, if you want, you can use the C++ API from this repo to programmatically modify a `h3m::Map` object.

Note: only **Shadow of Death** maps are supported. Currently, I have no plans to support other versions (e.g., Restoration of Erathia) or mods.

# Status
Structured represenation of a .h3m map is complete (see [h3m::Map](Map/Map.h)), but some cosmetic changes (e.g., wrappers for some bitmaks) might be added in the future.

Reading and writing .h3m maps is fully implemented ([H3MReader](H3MReader) and [H3MWriter](H3MWriter) libraries).

Conversion to/from a human-readable text format is currently in progress.

# Acknowledgment
I would like to thank the authors of [HeroWO-js/h3m2json](https://github.com/HeroWO-js/h3m2json/) and [potmdehex/homm3tools](https://github.com/potmdehex/homm3tools)
for the detailed description of the .h3m file format. These projects share some similarities with *h3mtxt*, but their goals and programming languages (PHP and C respectively) are different.
