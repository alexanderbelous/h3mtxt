# h3mtxt
Command-line utility for converting .h3m files (maps for Heroes of Might and Magic 3) to a human-readable format or vice versa.

HoMM3 maps are written as (possibly gzip-encoded) binary data. Normally, they are edited via the official Map Editor (or the unofficial Unleashed Editor). However, both programs have limitations: for example, they don't allow selecting a specific terrain sprite for a tile. A possible workaround is to manually edit the binary data in a hex editor, but this is error-prone and can be time-consuming.

*h3mtxt* offers an alternative solution: instead of modifying a .h3m file direclty, you can first convert it to a human-readable format, edit it, and then convert it back to .h3m.

Or, if you want, you can use the C++ API from this repo to programmatically modify a `h3m::Map` object.

Note: only **Shadow of Death** maps are supported. Currently, I have no plans to support other versions (e.g., Restoration of Erathia) or mods.
