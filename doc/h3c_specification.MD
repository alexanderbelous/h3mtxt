# Specification of the H3C file format

## Introduction

This document describes the H3C file format used by *Heroes of Might and Magic 3* for campaigns. It specifically addresses **The Shadow of Death** campaigns - I haven't checked if the other versions (i.e. "The Restoration of Erathia" and "Armageddon's Blade") use the same format.

An H3C file is a concatenated sequence of sections:
* Campaign header
* H3M map 1
* H3M map 2
* ...
* H3M map N

Normally, each of these sections is GZIP-compressed (1 GZIP stream per section). However, **any section can be stored decompressed** - both the game and the Campaign Editor support such campaigns.

When the header and all maps are GZIP-compressed, you can treat the entire H3C file as a GZIP archive - GZIP format explicitly specifies that the result of decompressing a file constrcuted by concatenating several GZIP streams is the result of concatenating decompressed data from each GZIP stream.

Note, however, that the Campaign header stores the original sizes of each map in bytes. If you take an H3C file, in which all sections are GZIP-compressed, and decompress it (e.g., via 7-Zip), the Campaign header will almost certainly become invalid (because it's extremely unlikely that the size of the decompressed data will be equal to the size of compressed data for all maps).

GZIP format is specified in [RFC 1952](https://www.rfc-editor.org/rfc/rfc1952).

## Notation

The description below groups parts of the H3C file into typed structures. These structures are written as a sequence of fields; each field itself can be a primitive type, a structure or an array.

### Primitive types

| Type        | Size in bytes | Description                                                                      |
| ----------- | ------------- | -------------------------------------------------------------------------------- |
| `Bool`      | 1             | 1 byte that should be interpreted as Boolean: zero is `false`, nonzero is `true` |
| `int8`      | 1             | signed 8-bit integer (values within [-128; 127])                                 |
| `uint8`     | 1             | unsigned 8-bit integer (values within [0; 255])                                  |
| `int16`     | 2             | signed 16-bit integer (values within [-32768; 32767])                            |
| `uint16`    | 2             | unsigned 16-bit integer (values within [0; 65535])                               |
| `int32`     | 4             | signed 32-bit integer (values within [-2147483648; 2147483647])                  |
| `uint32`    | 4             | unsigned 32-bit integer (values within [0; 4294967295])                          |
| `String32`  | varies        | length-prefixed string: a 32-bit integer N (`uint32`), followed by N bytes       |

Integers are always little-endian in H3C. For example, a 32-bit integer 1025 is encoded as 4 bytes `[0x01, 0x04, 0x00, 0x00]`.

### Structures

Composite data types are described like this:

`Person`:
| Field name  | Type       | Size in bytes | Description        |
| ----------- | ---------- | ------------- | ------------------ |
| name        | `String32` | varies        | Name of the person |
| age         | `uint16`   | 2             | Age (in years)     |

which means that the structure `Person` is written as 2 fields: first, the name is written as `String32`, then the age is written as `uint16`.

Some fields are conditionally present, i.e. they should only be read/written when a specific condition is true. Such fields are indicated here like `?field`, i.e. their name starts with a question mark. The description for this field explains when this field is present and when it's not.

Some fields are intentionally left typeless - they always represent meaningless bytes in H3C. The size of such such fields is always known in advance (i.e. never varies). You can interpret them as arrays of 8-bit integers, or as whatever you want.

### Arrays

`T[N]` indicates an array of N elements of type T: for example, `int32[10]` means an array of 10 signed 32-bit integers.

## File format

An H3C file is a single structure which we will naturally call [`Campaign`](#Campaign).

### `Campaign`

| Field name | Type                                | Size in bytes | Description                                                   |
| ---------- | ----------------------------------- | ------------- | ------------------------------------------------------------- |
| header     | [`CampaignHeader`](#CampaignHeader) | varies        | Possibly GZIP-compressed header                               |
| maps       | [`Map[NUM_REGIONS]`](#Map)          | varies        | H3M data for each scenario. `NUM_REGIONS` depends on `header` |

See [`CampaignHeader`](#CampaignHeader) for more information about `NUM_REGIONS`.

`maps[i]` is an array of bytes, whose length is equal to `header.scenarios[i].map_file_size` (length is 0 for unused regions). A non-empty byte array should be interpreted as the contents of an H3M file.


### `CampaignHeader`
| Field name                 | Type       | Size in bytes | Description                                                    |
| -------------------------- | ---------- | ------------- | -------------------------------------------------------------- |
| format                     | `uint32`   | 4             | Enum `CampaignFormat` (4 - RoE, 5 - AB, 6 - SoD)               |
| id                         | `uint8`    | 1             | Enum `CampaignId`. The Campaign Editor calls it "Campaign Map" |
| name                       | `String32` | varies        | The name of the campaign                                       |
| description                | `String32` | varies        | The description of the campaign                                |
| allow_selecting_difficulty | `Bool`     | 1             | 0 if difficulty cannot be selected, nonzero otherwise          |
| theme_music                | `uint8`    | 1             | Enum `CampaignMusic`                                           |
| scenarios                  | [`CampaignScenario[NUM_REGIONS]`](#CampaignScenario) | varies | Properties for each region  |

`NUM_REGIONS` depends on `id`:

| id | NUM_REGIONS | description             |
| -- | ----------- | ----------------------- |
| 1  | 3           | Long Live the Queen     |
| 2  | 4           | Liberation              |
| 3  | 3           | Song for the Father     |
| 4  | 7           | Dungeons and Devils     |
| 5  | 4           | Long Live the King      |
| 6  | 3           | Spoils of War           |
| 7  | 3           | Seeds of Discontent     |
| 8  | 4           | Bracada                 |
| 9  | 4           | Islands                 |
| 10 | 4           | Krewlod                 |
| 11 | 4           | Nighon                  |
| 12 | 3           | Tatalia                 |
| 13 | 8           | Armageddon              |
| 14 | 4           | Hack and Slash          |
| 15 | 5           | Birth of a Barbarian    |
| 16 | 4           | New Beginning           |
| 17 | 4           | Elixir of Life          |
| 18 | 4           | Rise of the Necromancer |
| 19 | 12          | Unholy Alliance         | 
| 20 | 4           | Specter of Power        |


### `CampaignScenario`
| Field name              | Type                                    | Size in bytes | Description                                                  |
| ----------------------- | --------------------------------------- | ------------- | ------------------------------------------------------------ |
| map_filename            | `String32`                              | varies        | Filename for the H3M file (displayed in the Campaign Editor) |
| map_file_size           | `uint32`                                | 4             | The size of the map file in bytes                            |
| prerequisites           | `uint8[BITMASK_SIZE]`                   | varies        | Bitmask; 1 bit per scenario in `Campaign.scenarios`, indicating whether that scenario must be finished before playing the current scenario. `BITMASK_SIZE` is 2 if `Campaign.id` = 19 (Unholy Alliance), otherwise 1 |
| region_color            | `uint8`                                 | 1             | Enum `RegionColor`                                           |
| default_difficulty      | `uint8`                                 | 1             | Enum `MapDifficulty`                                         |
| region_right_click_text | `String32`                              | varies        | Displayed in the main menu when you right-click on the region for this scenario |
| has_prologue            | `Bool`                                  | 1             | 0 if there is no prologue, nonzero otherwise                 |
| ?prologue               | [`CutScene`](#CutScene)                 | varies        | Only present if `has_prologue` is nonzero                    |
| has_epilogue            | `Bool`                                  | 1             | 0 if there is no epilogue, nonzero otherwise                 |
| ?epilogue               | [`CutScene`](#CutScene)                 | varies        | Only present if `has_epilogue` is nonzero                    |
| crossover_options       | [`CrossoverOptions`](#CrossoverOptions) | 38            | Describes what crossover heroes retain                       |
| starting_options        | [`StartingOptions`](#StartingOptions)   | varies        | Starting options that the player can choose from in the main menu |


### `CutScene`
| Field name | Type       | Size in bytes | Description          |
| ---------- | ---------- | ------------- | -------------------- |
| movie      | `uint8`    | 1             | Enum `CampaignVideo` |
| music      | `uint8`    | 1             | Enum `CampaignMusic` |
| message    | `String32` | varies        | Text to display      |


### `CrossoverOptions`
| Field name        | Type        | Size in bytes | Description                                                                               |
| ----------------- | ----------- | ------------- | ----------------------------------------------------------------------------------------- |
| retained_features | `uint8`     | 1             | Bitmask; 1 bit per enum `CrossoverFeature`, indicating if this feature is retained        |
| creatures         | `uint8[19]` | 19            | Bitmask; 1 bit per enum `CreatureType`, indicating if creatures of this type are retained |
| artifacts         | `uint8[18]` | 18            | Bitmask; 1 bit per enum `ArtifactType`, indicating if artifacts of this type are retained |


### `StartingOptions`
| Field name         | Type                                            | Size in bytes | Description                |
| ------------------ | ----------------------------------------------- | ------------- | -------------------------- |
| type               | `uint8`                                         | 1             | Enum `StartingOptionsType` |
| ?starting_bonuses  | [`StartingBonuses`](#StartingBonuses)           | varies        | Only present if `type` = 1 |
| ?hero_crossover    | [`HeroCrossoverOptions`](#HeroCrossoverOptions) | varies        | Only present if `type` = 2 |
| ?starting_heroes   | [`StartingHeroes`](#StartingHeroes)             | varies        | Only present if `type` = 3 |


### `StartingBonuses`
| Field name  | Type                                           | Size in bytes | Description        |
| ----------- | ---------------------------------------------- | ------------- | ------------------ |
| player      | `uint8`                                        | 1             | Enum `PlayerColor` |
| num_options | `uint8`                                        | 1             |                    |
| options     | [`StartingBonus[num_options]`](#StartingBonus) | varies        |                    |


### `StartingBonus`
| Field name       | Type                                                          | Size in bytes | Description                |
| ---------------- | ------------------------------------------------------------- | ------------- | -------------------------- |
| type             | `uint8`                                                       | 1             | Enum `StartingBonusType`   |
| ?spell           | [`StartingBonusSpell`](#StartingBonusSpell)                   | 3             | Only present if `type` = 0 |
| ?creature        | [`StartingBonusCreature`](#StartingBonusCreature)             | 6             | Only present if `type` = 1 |
| ?building        | `uint8`                                                       | 1             | Only present if `type` = 2. Enum `TownBuildingType` |
| ?artifact        | [`StartingBonusArtifact`](#StartingBonusArtifact)             | 4             | Only present if `type` = 3 |
| ?spell_scroll    | [`StartingBonusSpell`](#StartingBonusSpell)                   | 3             | Only present if `type` = 4 |
| ?primary_skills  | [`StartingBonusPrimarySkills`](#StartingBonusPrimarySkills)   | 6             | Only present if `type` = 5 |
| ?secondary_skill | [`StartingBonusSecondarySkill`](#StartingBonusSecondarySkill) | 4             | Only present if `type` = 6 |
| ?resource        | [`StartingBonusResource`](#StartingBonusResource)             | 5             | Only present if `type` = 7 |


### `StartingBonusSpell`
| Field name | Type     | Size in bytes | Description                                          |
| ---------- | -------- | ------------- | ---------------------------------------------------- |
| hero       | `uint16` | 2             | Enum `HeroType` or 0xFDFF for the most powerful hero |
| spell      | `uint8`  | 1             | Enum `SpellType`                                     |


### `StartingBonusCreature`
| Field name    | Type     | Size in bytes | Description                                          |
| ------------- | -------- | ------------- | ---------------------------------------------------- |
| hero          | `uint16` | 2             | Enum `HeroType` or 0xFDFF for the most powerful hero |
| creature_type | `uint16` | 2             | Enum `CreatureType`                                  |
| count         | `int16`  | 2             | The number of creatures                              |


### `StartingBonusArtifact`
| Field name | Type     | Size in bytes | Description                                          |
| ---------- | -------- | ------------- | ---------------------------------------------------- |
| hero       | `uint16` | 2             | Enum `HeroType` or 0xFDFF for the most powerful hero |
| artifact   | `uint16` | 2             | Enum `ArtifactType`                                  |


### `StartingBonusPrimarySkills`
| Field name | Type      | Size in bytes | Description                                                                 |
| ---------- | --------- | ------------- | --------------------------------------------------------------------------- |
| hero       | `uint16`  | 2             | Enum `HeroType` or 0xFDFF for the most powerful hero                        |
| skills     | `int8[4]` | 4             | Increments for each primary skill (Attack, Defense, Spell Power, Knowledge) |


### `StartingBonusSecondarySkill`
| Field name | Type     | Size in bytes | Description                                              |
| ---------- | -------- | ------------- | -------------------------------------------------------- |
| hero       | `uint16` | 2             | Enum `HeroType` or 0xFDFF for the most powerful hero     |
| type       | `uint8`  | 1             | Enum `SecondarySkillType`                                |
| level      | `uint8`  | 1             | Level of expertise (1 - Basic, 2 - Advanced, 3 - Expert) |


### `StartingBonusResource`
| Field name | Type     | Size in bytes | Description                      |
| ---------- | -------- | ------------- | -------------------------------- |
| type       | `uint8`  | 1             | Enum `StartingBonusResourceType` |
| amount     | `uint32` | 4             |                                  |


### `HeroCrossoverOptions`
| Field name  | Type                                           | Size in bytes | Description |
| ----------- | ---------------------------------------------- | ------------- | ----------- |
| num_options | `uint8`                                        | 1             |             |
| options     | [`HeroCrossover[num_options]`](#HeroCrossover) | varies        |             |


### `HeroCrossover`
| Field name      | Type     | Size in bytes | Description                                                                             |
| --------------- | -------- | ------------- | --------------------------------------------------------------------------------------- |
| player          | `uint8`  | 1             | Enum `PlayerColor`                                                                      |
| source_scenario | `uint8`  | 1             | 0-based index of the source scenario from [`CampaignHeader.scenarios`](#CampaignHeader) |


### `StartingHeroes`
| Field name  | Type                                         | Size in bytes | Description |
| ----------- | -------------------------------------------- | ------------- | ----------- |
| num_options | `uint8`                                      | 1             |             |
| options     | [`StartingHero[num_options]`](#StartingHero) | varies        |             |


### `StartingHero`
| Field name  | Type     | Size in bytes | Description                         |
| ----------- | -------- | ------------- | ----------------------------------- |
| player      | `uint8`  | 1             | Enum `PlayerColor`                  |
| type        | `uint16` | 2             | Enum `HeroType` or 0xFFFF if random |


### `Map`

Contents of an H3M file. This document does not cover the H3M file format.
* [HeroWO](https://github.com/HeroWO-js/h3m2json/blob/master/h3m-The-Corpus.txt) has a good description of the file format, although it has a few bugs.
* [H3MReader](../src/h3mtxt/H3Reader/H3MReader) from this repository is a C++ library for parsing H3M files.
