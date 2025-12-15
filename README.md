# h3mtxt
Command-line utility for converting .h3m/.h3c files (maps and campaigns for Heroes of Might and Magic 3) to a human-readable format (JSON) or vice versa.

This tool is primarily intended for HoMM3 mapmakers who want to add undocumented features to their maps.

HoMM3 maps are written as (possibly gzip-encoded) binary data. Normally, they are edited via the official Map Editor (or the unofficial Unleashed Editor). However, both programs have limitations: for example, they don't allow selecting a specific terrain sprite for a tile. A possible workaround is to manually edit the binary data in a hex editor, but this is error-prone and can be time-consuming.

*h3mtxt* offers an alternative solution: instead of modifying a .h3m file direclty, you can first convert it to a human-readable format (JSON), edit it, and then convert it back to .h3m.

Or, if you want, you can use the C++ API from this repository to programmatically modify a `h3m::Map` (or `h3m::Campaign`) object.

Note: only **Shadow of Death** maps are supported. Currently, I have no plans to support other versions (e.g., Restoration of Erathia) or mods.

# Usage
Just pass the paths to the input map or campaign (.h3m/.h3c or JSON) and the output file:
```sh
# Convert the map from .h3m to JSON.
h3mtxt my_map.h3m my_map.h3m.json

# Convert the map from JSON to .h3m.
h3mtxt my_map.h3m.json my_map_new.h3m

# Convert the campaign from .h3c to JSON.
h3mtxt my_campaign.h3c my_campaign.h3c.json

# Convert the campaign from JSON to .h3c.
h3mtxt my_campaign.h3c.json my_campaign_new.h3c
```
The filename extensions are not important - the program will detect the file type by inspecting the data.

See [examples](examples) for more details.

# Undocumented features

See the comments in the source code in [Map](Map) or the brief overview in https://gist.github.com/alexanderbelous/e5f0766845476d93eda10469c5667d9b

# Building h3mtxt
```sh
git clone --recurse-submodules https://github.com/alexanderbelous/h3mtxt.git
cd h3mtxt
cmake -S . -B build
cmake --build build --config Release
cmake --install build --config Release --prefix .
```

# Acknowledgment
I would like to thank the authors of [HeroWO-js/h3m2json](https://github.com/HeroWO-js/h3m2json/) and [potmdehex/homm3tools](https://github.com/potmdehex/homm3tools)
for the detailed description of the .h3m file format. These projects share some similarities with *h3mtxt*, but their goals and programming languages (PHP and C respectively) are different.
