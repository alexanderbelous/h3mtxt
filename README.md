# h3mtxt
Command-line utility for converting .h3m files (maps for Heroes of Might and Magic 3) to a human-readable format (JSON) or vice versa.

This tool is primarily intended for HoMM3 mapmakers who want to add undocumented features to their maps.

HoMM3 maps are written as (possibly gzip-encoded) binary data. Normally, they are edited via the official Map Editor (or the unofficial Unleashed Editor). However, both programs have limitations: for example, they don't allow selecting a specific terrain sprite for a tile. A possible workaround is to manually edit the binary data in a hex editor, but this is error-prone and can be time-consuming.

*h3mtxt* offers an alternative solution: instead of modifying a .h3m file direclty, you can first convert it to a human-readable format (JSON), edit it, and then convert it back to .h3m.

Or, if you want, you can use the C++ API from this repo to programmatically modify a `h3m::Map` object.

Note: only **Shadow of Death** maps are supported. Currently, I have no plans to support other versions (e.g., Restoration of Erathia) or mods.

# Usage
Just pass the paths to the input map (h3m or JSON) and the output file.
```sh
# Convert the map from .h3m to JSON.
h3mtxt my_map.h3m my_map.h3m.json

# Convert the map from JSON to .h3m.
h3mtxt my_map.h3m.json my_map_new.h3m
```
The filename extensions are not important - the program will check if the input file contains a .h3m map or a JSON document and convert it to JSON or .h3m respectively

# Status
Structured represenation of a .h3m map is complete (see [h3m::Map](Map/Map.h)), but some cosmetic changes (e.g., wrappers for some bitmaks) might be added in the future.

Reading and writing .h3m maps is fully implemented ([H3MReader](H3MReader) and [H3MWriter](H3MWriter) libraries).

Conversion to JSON ([H3MJsonWriter](H3MJsonWriter)) is done, but more comments will be added in the future.

Conversion from JSON to H3M ([H3MJsonReader](H3MJsonReader)) is currently in progress; some objects on the adventure map are skipped.

# Acknowledgment
I would like to thank the authors of [HeroWO-js/h3m2json](https://github.com/HeroWO-js/h3m2json/) and [potmdehex/homm3tools](https://github.com/potmdehex/homm3tools)
for the detailed description of the .h3m file format. These projects share some similarities with *h3mtxt*, but their goals and programming languages (PHP and C respectively) are different.
