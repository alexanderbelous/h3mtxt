# Specification of the H3M file format

## Introduction

This document describes the H3M file format used by *Heroes of Might and Magic 3* for maps. It specifically addresses **Armageddon's Blade** and **The Shadow of Death** maps - "The Restoration of Erathia" uses a slightly different format, which is not covered here.

The libraries [`Map`](../src/h3mtxt/Map), [`H3MReader`](../src/h3mtxt/H3Reader/H3MReader) and [`H3MWriter`](../src/h3mtxt/H3Writer/H3MWriter) from this repository provide a reference implementation of this specification in C++.

## Acknowledgment

This document is largely based on `h3m-The-Corpus.txt` from [HeroWO.js](https://github.com/HeroWO-js/h3m2json/) project, but differs in a few ways:
* This document uses [Markdown](https://en.wikipedia.org/wiki/Markdown) for readability.
* `h3m-The-Corpus.txt` has a few things wrong; for example, it claims that the frequency of a Timed Event is encoded as an 8-bit integer, whereas in reality it is encoded as a 16-bit integer.
* A few things are missing from `h3m-The-Corpus.txt`: for example, it doesn't cover the undocumented Special Victory Conditions "Defeat All Monsters" and "Survive Beyond A Time Limit".

## Compression

The maps created via the official Map Editor (or RoseKavalier's [Unleashed Editor](http://heroescommunity.com/viewthread.php3?TID=43775)) are [GZIP](https://en.wikipedia.org/wiki/Gzip)-compressed by default, but the game supports uncompressed maps as well. You can manually compress/decompress maps via programs like [7-Zip](https://7-zip.org/).

GZIP format is specified in [RFC 1952](https://www.rfc-editor.org/rfc/rfc1952).

This document descirbes the format of the uncompessed data.

## Notation

The description below groups parts of the H3M file into typed structures. These structures are written as a sequence of fields; each field itself can be a primitive type, a structure or an array.

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

Integers are always [little-endian](https://en.wikipedia.org/wiki/Endianness) in H3M. For example, a 32-bit integer 1025 is encoded as 4 bytes `[0x01, 0x04, 0x00, 0x00]`.

### Structures

Composite data types are described like this:

`Person`:
| Field name  | Type       | Size in bytes | Description        |
| ----------- | ---------- | ------------- | ------------------ |
| name        | `String32` | varies        | Name of the person |
| age         | `uint16`   | 2             | Age (in years)     |

which means that the structure `Person` is written as 2 fields: first, the name is written as `String32`, then the age is written as `uint16`. For example, a `Person` with `name = "Tom"` and `age = 30` is encoded as 9 bytes: `[0x03, 0x00, 0x00, 0x00, 0x54, 0x4F, 0x4D, 0x1E, 0x00]`.

Some fields are conditionally present, i.e. they should only be read/written when a specific condition is met. Such fields are indicated here like `?field`, i.e. their name starts with a question mark. The description for this field explains when this field is present and when it's not.

### Arrays

`T[N]` indicates an array of N elements of type T: for example, `int32[10]` means an array of 10 signed 32-bit integers.

### Bitmasks

H3M uses [bitmasks](https://en.wikipedia.org/wiki/Mask_(computing)) in many places. A bitmask is always serialized as an array of bytes:
* The 0th bit is the [least significant bit](https://en.wikipedia.org/wiki/Bit_numbering) (LSB) of the 0th byte.
* The 7th bit is the most significant bit (MSB) of the 0th byte.
* The 8th bit is LSB of the 1st byte.
* ...

This document doesn't use any special type for bitmasks: they are indicated simply as an array of bytes. The description of a bitmask field explains the meaning of the bits.

## File format

An H3M file is a single structure which we will naturally call [`Map`](#Map).

### `Map`

| Field name            | Type                                                       | Size in bytes | Description |
| --------------------- | ---------------------------------------------------------- | ------------- | ----------- |
| format                | `uint32`                                                   | 4             | Enum [`MapFormat`](../src/h3mtxt/Map/Constants/MapFormat.h). Format of the map ("Map Specifications"/"Map version" in the Map Editor) |
| basic_info            | [`MapBasicInfo`](#MapBasicInfo)                            | varies        | Basic information about the map ("Map Specifications"/"General" tab in the Map Editor) |
| players               | [`PlayerSpecs[8]`](#PlayerSpecs)                           | varies        | Settings for each player ("Map Specifications"/"Player specs" tab in the Map Editor) in order of [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) |
| additional_info       | [`MapAdditionalInfo`](#MapAdditionalInfo)                  | varies        | Additional information about the map ("Special Victory Condition", "Special Loss Condition", "Teams", "Heroes", "Artifacts", "Spells", "Secondary Skills" and "Rumors" tabs in the Map Editor) |
| tiles                 | [`Tile[NUM_TILES]`](#Tile)                                 | varies        | Terrain data for each tile on the Adventure Map. `NUM_TILES = NUM_LEVELS * basic_info.map_size * basic_info.map_size`, where `NUM_LEVELS` is 2 if `basic_info.has_two_levels` is nonzero, 1 otherwise |
| num_objects_templates | `uint32`                                                   | 4             | The number of templates for objects on the Adventure Map |
| objects_templates     | [`ObjectTemplate[num_objects_templates]`](#ObjectTemplate) | varies        | Templates for objects on the Adventure Map |
| num_objects           | `uint32`                                                   | 4             | The number of objects on the Adventure Map |
| objects               | [`Object[num_objects]`](#Object)                           | varies        | Objects on the Adventure Map |
| num_timed_events      | `uint32`                                                   | 4             | The number of global Timed Events |
| timed_events          | [`TimedEvent[num_timed_events]`](#TimedEvent)              | varies        | Global events on this map ("Map Specifications"/"Timed Events" tab in the Editor) |
| padding               | `uint8[124]`                                               | 124           | Not used; always set to 0s by the Map Editor |


### `MapBasicInfo`
| Field name     | Type       | Size in bytes | Description                                                          |
| -------------- | ---------- | ------------- | -------------------------------------------------------------------- |
| is_playable    | `Bool`     | 1             | 0 if there are no heroes and towns on the map, nonzero otherwise     |
| map_size       | `uint32`   | 4             | Width and height of the map (in tiles)                               |
| has_two_levels | `Bool`     | 1             | 0 if there is only 1 level on the map, nonzero if there are 2 levels |
| name           | `String32` | varies        | The name of the map                                                  |
| description    | `String32` | varies        | Description of the map                                               |
| difficulty     | `uint8`    | 1             | Enum [`MapDifficulty`](../src/h3mtxt/Map/Constants/MapDifficulty.h). Difficulty level as suggested by the mapmaker |
| max_hero_level | `uint8`    | 1             | Maximum allowed level for all heroes. 0 means to limit               |


### `PlayerSpecs`
| Field name                         | Type                                | Size in bytes | Description |
| ---------------------------------- | ----------------------------------- | ------------- | ----------- |
| can_be_human                       | `Bool`                              | 1             | 0 if this player cannot be controlled by a human player, nonzero otherwise |
| can_be_computer                    | `Bool`                              | 1             | 0 if this player cannot be controlled by AI, nonzero otherwise |
| behavior                           | `uint8`                             | 1             | Enum [`PlayerBehavior`](../src/h3mtxt/Map/Constants/PlayerBehavior.h) |
| ?has_customized_alignments         | `Bool`                              | 1             | Reflects the state of the "Customize" checkbox in "Map Specifications/Player Specs/Allowed alignments" in the Map Editor. Only present in **The Shadow of Death** maps |
| allowed_alignments                 | `uint8[2]`                          | 2             | Bitmask; 1 bit for each [`TownType`](../src/h3mtxt/Map/Constants/TownType.h) indicating if this town can be the player's alignment. Only the first 9 bits are meaningful; the last 7 bits are set to 0s by default by the Map Editor |
| allow_random_alignment             | `Bool`                              | 1             | Reflects the state of the "Random" checkbox in "Map Specifications/Player Specs/Allowed alignments" |
| has_main_town                      | `Bool`                              | 1             | Reflects the state of "Has main town" checkbox in "Map Specifications/Player Specs" |
| ?main_town                         | [`MainTown`](#MainTown)             | 5             | Information about the player's main town. Only present if `has_main_town` is nonzero |
| has_random_heroes                  | `Bool`                              | 1             | Nonzero if the player starts with at least one Random Hero, 0 otherwise |
| starting_hero                      | [`StartingHero`](#StartingHero)     | varies        | Starting hero as displayed when starting a new game |
| num_nonspecific_placeholder_heroes | `uint8`                             | 1             |  The number of non-specific hero placeholders (i.e. configured as "Power Rating" rather than "Specific hero") at the beginning of the game |
| num_heroes                         | `uint32`                            | 4             | The number of specific heroes that the player has at the beginning of the game (i.e. non-Random heroes and hero placeholdwers configured as "Specific hero") |
| heroes                             | [`HeroInfo[num_heroes]`](#HeroInfo) | varies        | Specific heroes that the player has at the beginning of the game (i.e. non-Random heroes and hero placeholdwers configured as "Specific hero") |


### `MainTown`
| Field name    | Type                          | Size in bytes | Description |
| ------------- | ----------------------------- | ------------- | ----------- |
| generate_hero | `Bool`                        | 1             | Reflects the state of "Generate hero at main town" checkbox in "Map Specifications/Player Specs" |
| town_type     | `int8`                        | 1             | Enum [`TownType`](../src/h3mtxt/Map/Constants/TownType.h); type of the player's main town or `-1` if it's a Random Town |
| coordinates   | [`Coordinates`](#Coordinates) | 3             | Coordinates of the actionable spot (i.e. the entrance) |


### `Coordinates`
| Field name | Type    | Size in bytes | Description  |
| ---------- | ------- | ------------- | ------------ |
| x          | `uint8` | 1             | X-coordinate |
| y          | `uint8` | 1             | Y-coordinate |
| z          | `uint8` | 1             | Z-coordinate |


### `StartingHero`
| Field name | Type       | Size in bytes | Description |
| ---------- | ---------- | ------------- | ----------- |
| type       | `uint8`    | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h); identity of the starting hero or `0xFF` if there is none |
| ?portrait  | `uint8`    | 1             | Enum [`HeroPortrait`](../src/h3mtxt/Map/Constants/HeroPortrait.h); portrait of the starting hero. Only present if `type` is not `0xFF` |
| ?name      | `String32` | varies        | The name of the starting hero. Only present if `type` is not `0xFF` |


### `HeroInfo`
| Field name | Type       | Size in bytes | Description                                                                         |
| ---------- | ---------- | ------------- | ----------------------------------------------------------------------------------- |
| type       | `uint8`    | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h); identity of the hero     |
| name       | `String32` | varies        | The name of the hero, or an empty string if the default name should be used instead |


### `MapAdditionalInfo`
| Field name             | Type                                           | Size in bytes | Description |
| ---------------------- | ---------------------------------------------- | ------------- | ----------- |
| victory_condition      | [`VictoryCondition`](#VictoryCondition)        | varies        | "Map Specifications/Special Victory Condition" in the Map Editor |
| loss_condition         | [`LossCondition`](#LossCondition)              | varies        | "Map Specifications/Special Loss Condition" in the Map Editor |
| teams                  | [`Teams`](#Teams)                              | varies        | "Map Specifications/Teams" in the Map Editor |
| heroes_availability    | `uint8[20]`                                    | 20            | Bitmask; 1 bit per [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h), reflecting the state of the checkbox in "Map Specifications/Heroes/Available heroes" for this hero. Only the first 156 bits are meaningful; the last 4 bits are set to 0 by default by the Map Editor |
| num_placeholder_heroes | `uint32`                                       | 4             | The number of hero placeholders on this map |
| placeholder_heroes     | `uint8[num_placeholder_heroes]`                | varies        | Hero placeholders on this map; each element is enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h) |
| ?num_custom_heroes     | `uint8`                                        | 1             | The number of heroes with customized name, portrait or "May be hired by" settings. Only present in **The Shadow of Death** maps |
| ?custom_heroes         | [`CustomHero[num_custom_heroes]`](#CustomHero) | varies        | Heroes with customized name, portrait or "May be hired by" settings. Only present in **The Shadow of Death** maps |
| reserved               | `uint8[31]`                                    | 31            | Not used; set to 0s by default by the Map Editor |
| disabled_artifacts     | `uint8[ARTIFACTS_BITMASK_LENGTH]`              | varies        | Bitmask; 1 bit per [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h), indicating whether this artifact is disabled in this scenario (1 - disabled, 0 - enabled). `ARTIFACTS_BITMASK_LENGTH` is `18` in **The Shadow of Death** maps, but `17` in **Armageddon's Blade** |
| ?disabled_spells       | `uint8[9]`                                     | 9             | Bitmask; 1 bit per [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h), indicating whether this spell is disabled in this scenario (1 - disabled, 0 - enabled). Only present in **The Shadow of Death** maps |
| ?disabled_skills       | `uint8[4]`                                     | 4             | Bitmask; 1 bit per [`SecondarySkillType`](../src/h3mtxt/Map/Constants/SecondarySkillType.h), indicating whether this secondary skill is disabled in this scenario (1 - disabled, 0 - enabled). Only present in **The Shadow of Death** maps |
| num_rumors             | `uint32`                                       | 4             | The number of Rumors in this scenario |
| rumors                 | [`Rumor[num_rumors]`](#Rumor)                  | varies        | "Map Specifications/Rumors" in the Map Editor |
| ?heroes_settings       | [`HeroSettingsEntry[156]`](#HeroSettingsEntry) | varies        | Settings for each hero in order of [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h). Only present in **The Shadow of Death** maps |


### `VictoryCondition`
| Field name                   | Type    | Size in bytes | Description |
| ---------------------------- | ------- | ------------- | ----------- |
| type                         | `uint8` | 1             | Enum [`VictoryConditionType`](../src/h3mtxt/Map/Constants/VictoryConditionType.h) |
| ?allow_normal_win            | `Bool`  | 1             | Nonzero if the normal victory condition (defeat all enemies) is also enabled, 0 otherwise. Only present if `type` is not `0xFF` (Normal) |
| ?applies_to_computer         | `Bool`  | 1             | Nonzero if the special victory condition applies to the computer, 0 otherwise. Only present if `type` is not `0xFF` (Normal) |
| ?acquire_artifact            | [`VictoryConditionAcquireArtifact`](#VictoryConditionAcquireArtifact) | 2 | Only present if `type` is `0` |
| ?accumulate_creatures        | [`VictoryConditionAccumulateCreatures`](#VictoryConditionAccumulateCreatures) | 6 | Only present if `type` is `1` |
| ?accumulate_resources        | [`VictoryConditionAccumulateResources`](#VictoryConditionAccumulateResources) | 5 | Only present if `type` is `2` |
| ?upgrade_town                | [`VictoryConditionUpgradeTown`](#VictoryConditionUpgradeTown) | 5 | Only present if `type` is `3` |
| ?build_grail                 | [`VictoryConditionBuildGrail`](#VictoryConditionBuildGrail) | 3 | Only present if `type` is `4` |
| ?defeat_hero                 | [`VictoryConditionDefeatHero`](#VictoryConditionDefeatHero) | 3 | Only present if `type` is `5` |
| ?capture_town                | [`VictoryConditionCaptureTown`](#VictoryConditionCaptureTown) | 3 | Only present if `type` is `6` |
| ?defeat_monster              | [`VictoryConditionDefeatMonster`](#VictoryConditionDefeatMonster) | 3 | Only present if `type` is `7` |
| ?transport_artifact          | [`VictoryConditionTransportArtifact`](#VictoryConditionTransportArtifact) | 4 | Only present if `type` is `10` |
| ?survive_beyond_a_time_limit | [`VictoryConditionSurviveBeyondATimeLimit`](#VictoryConditionSurviveBeyondATimeLimit) | 4 | Only present if `type` is `12` |


### `VictoryConditionAcquireArtifact`
| Field name    | Type    | Size in bytes | Description                                                       |
| ------------- | ------- | ------------- | ----------------------------------------------------------------- |
| artifact_type | `int16` | 2             | Enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |


### `VictoryConditionAccumulateCreatures`
| Field name    | Type    | Size in bytes | Description                                                       |
| ------------- | ------- | ------------- | ----------------------------------------------------------------- |
| creature_type | `int16` | 2             | Enum [`CreatureType`](../src/h3mtxt/Map/Constants/CreatureType.h) |
| quantity      | `int32` | 4             | The number of creatures to accumulate                             |


### `VictoryConditionAccumulateResources`
| Field name    | Type    | Size in bytes | Description                                                       |
| ------------- | ------- | ------------- | ----------------------------------------------------------------- |
| resource_type | `uint8` | 1             | Enum [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |
| quantity      | `int32` | 4             | The amount to accumulate                                          |


### `VictoryConditionUpgradeTown`
| Field name   | Type                          | Size in bytes | Description                       |
| ------------ | ----------------------------- | ------------- | --------------------------------- |
| coordinates  | [`Coordinates`](#Coordinates) | 3             | Coordinates of the town. If all the components X, Y, Z are equal to `0xFF`, implies any town |
| hall_level   | `uint8`                       | 1             | 0 - Town, 1 - City, 2 - Capitol   |
| castle_level | `uint8`                       | 1             | 0 - Fort, 1 - Citadel, 2 - Castle |


### `VictoryConditionBuildGrail`
| Field name  | Type                          | Size in bytes | Description |
| ----------- | ----------------------------- | ------------- | ----------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the town. If all the components X, Y, Z are equal to `0xFF`, implies any town |


### `VictoryConditionDefeatHero`
| Field name  | Type                          | Size in bytes | Description             |
| ----------- | ----------------------------- | ------------- | ----------------------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the hero |


### `VictoryConditionCaptureTown`
| Field name  | Type                          | Size in bytes | Description             |
| ----------- | ----------------------------- | ------------- | ----------------------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the town |


### `VictoryConditionDefeatMonster`
| Field name  | Type                          | Size in bytes | Description                |
| ----------- | ----------------------------- | ------------- | -------------------------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the monster |


### `VictoryConditionTransportArtifact`
| Field name    | Type                          | Size in bytes | Description                                                       |
| ------------- | ----------------------------- | ------------- | ----------------------------------------------------------------- |
| artifact_type | `uint8`                       | 1             | Enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |
| destination   | [`Coordinates`](#Coordinates) | 3             | Coordinates of the town                                           |


### `VictoryConditionSurviveBeyondATimeLimit`
| Field name | Type    | Size in bytes | Description                                                 |
| ---------- | ------- | ------------- | ------------------------------------------------------------|
| days       | `int32` | 4             | The number of in-game days that the player needs to survive |


### `LossCondition`
| Field name    | Type                                                    | Size in bytes | Description                   |
| ------------- | ------------------------------------------------------- | ------------- | ----------------------------- |
| type          | `uint8`                                                 | 1             | Enum [`LossConditionType`](../src/h3mtxt/Map/Constants/LossConditionType.h) |
| ?lose_town    | [`LossConditionLoseTown`](#LossConditionLoseTown)       | 3             | Only present if `type` is `0` |
| ?lose_hero    | [`LossConditionLoseHero`](#LossConditionLoseHero)       | 3             | Only present if `type` is `1` |
| ?time_expires | [`LossConditionTimeExpires`](#LossConditionTimeExpires) | 2             | Only present if `type` is `2` |


### `LossConditionLoseTown`
| Field name  | Type                          | Size in bytes | Description             |
| ----------- | ----------------------------- | ------------- | ----------------------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the town |


### `LossConditionLoseHero`
| Field name  | Type                          | Size in bytes | Description             |
| ----------- | ----------------------------- | ------------- | ----------------------- |
| coordinates | [`Coordinates`](#Coordinates) | 3             | Coordinates of the hero |


### `LossConditionTimeExpires`
| Field name | Type    | Size in bytes | Description                |
| ---------- | ------- | ------------- | -------------------------- |
| days       | `int16` | 2             | The number of in-game days |


### `Teams`
| Field name       | Type       | Size in bytes | Description                                    |
| ---------------- | ---------- | ------------- | ---------------------------------------------- |
| num_teams        | `uint8`    | 1             | The number of teams or 0 if teams are disabled |
| ?team_for_player | `uint8[8]` | 8             | Team number for each player in order of [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h). Each element should be < `num_teams`. Only present if `num_teams` is nonzero |


### `CustomHero`
| Field name | Type       | Size in bytes | Description                                                       |
| ---------- | ---------- | ------------- | ----------------------------------------------------------------- |
| type       | `uint8`    | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h)         |
| portrait   | `uint8`    | 1             | Enum [`HeroPortrait`](../src/h3mtxt/Map/Constants/HeroPortrait.h) |
| name       | `String32` | varies        | Hero's name or an empty string if the default name should be used |
| can_hire   | `uint8`    | 1             | Bitmask; 1 bit per [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h), indicating whether that player can hire this hero |


### `Rumor`
| Field name | Type       | Size in bytes | Description                                        |
| ---------- | ---------- | ------------- | -------------------------------------------------- |
| name       | `String32` | varies        | The name of the rumor to display in the Map Editor |
| text       | `String32` | varies        | Text to display in the game                        |


### `HeroSettingsEntry`
| Field name   | Type                            | Size in bytes | Description                                     |
| ------------ | ------------------------------- | ------------- | ----------------------------------------------- |
| has_settings | `Bool`                          | 1             | Indicates whether this hero has custom settings |
| settings     | [`HeroSettings`](#HeroSettings) | varies        | Only present if `has_settings` is nonzero       |


### `HeroSettings`
| Field name            | Type       | Size in bytes | Description                                                                        |
| --------------------- | ---------- | ------------- | ---------------------------------------------------------------------------------- |
| has_experience        | `Bool`     | 1             | Indicates whether experience is customized for this hero                           |
| ?experience           | `int32`    | 4             | Only present if `has_experience` is nonzero                                        |
| has_secondary_skills  | `Bool`     | 1             | Indicates whether the secondary skills are customized for this hero                |
| ?num_secondary_skills | `uint32`   | 4             | The number of secondary skills. Only present if `has_secondary_skills` is nonzero` |
| ?secondary_skills     | [`SecondarySkill[num_secondary_skills]`](#SecondarySkill) | varies | Only present if `has_secondary_skills` is nonzero` |
| has_artifacts         | `Bool`     | 1             | Indicates whether artifacts are customized for this hero                           |
| ?artifacts            | [`HeroArtifacts`](#HeroArtifacts) | varies | Only present if `has_artifacts` is nonzero                         |
| has_biography         | `Bool`     | 1             | Indicates whether biography is customized for this hero                            |
| ?biography            | `String32` | varies        | Only present if `has_biography` is nonzero                                         |
| gender                | `uint8`    | 1             | Enum [`Gender`](../src/h3mtxt/Map/Constants/Gender.h)                              |
| has_spells            | `Bool`     | 1             | Indicates whether spells are customized for this hero                              |
| ?spells               | `uint8[9]` | 9             | Bitmask; 1 bit per [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h), indicating whether the hero knows this spell. Only present if `has_spells` is nonzero |
| has_primary_skills    | `Bool`     | 1             | Indicates whether the primary skills are customized for this hero                  |
| ?primary_skills       | `int8[4]`  | 4             | The value for each primary skill in order of [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h). Only present if `has_primary_skills` is nonzero |


### `SecondarySkill`
| Field name | Type    | Size in bytes | Description                                                                   |
| ---------- | ------- | ------------- | ----------------------------------------------------------------------------- |
| type       | `uint8` | 1             | Enum [`SecondarySkillType`](../src/h3mtxt/Map/Constants/SecondarySkillType.h) |
| level      | `int8`  | 1             | Level of proficiency (1 - Basic, 2 - Advanced, 3 - Expert)                    |


### `HeroArtifacts`
| Field name     | Type                        | Size in bytes | Description                             |
| -------------- | --------------------------- | ------------- | --------------------------------------- |
| equipped       | `int16[NUM_ARTIFACT_SLOTS]` | varies        | Enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) for each [`ArtifactSlot`](../src/h3mtxt/Map/Constants/ArtifactSlot.h). `NUM_ARTIFACT_SLOTS` is `19` in **The Shadow of Death**, but `18` in **Armageddon's Blade** |
| backpack_count | `uint16`                    | 2             | The number of artifacts in the backpack |
| backpack       | `int16[backpack_count]`     | varies        | Artifacts in the backpack; each element is enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |


### `Tile`
| Field name     | Type    | Size in bytes | Description                                                             |
| -------------- | ------- | ------------- | ----------------------------------------------------------------------- |
| terrain_type   | `uint8` | 1             | Enum [`TerrainType`](../src/h3mtxt/Map/Constants/TerrainType.h)         |
| terrain_sprite | `uint8` | 1             | 0-based index of the terrain sprite to render                           |
| river_type     | `uint8` | 1             | Enum [`RiverType`](../src/h3mtxt/Map/Constants/RiverType.h)             |
| river_sprite   | `uint8` | 1             | 0-based index of the river sprite to render                             |
| road_type      | `uint8` | 1             | Enum [`RoadType`](../src/h3mtxt/Map/Constants/RoadType.h)               |
| road_sprite    | `uint8` | 1             | 0-based index of the road sprite to render                              |
| flags          | `uint8` | 1             | Bitmask; 1 bit per [`TileFlag`](../src/h3mtxt/Map/Constants/TileFlag.h) |


### `ObjectTemplate`
| Field name         | Type        | Size in bytes | Description                                                                                 |
| ------------------ | ----------- | ------------- | ------------------------------------------------------------------------------------------- |
| def                | `String32`  | varies        | Name of the *.def sprite to render for objects that use this template                       |
| passability        | `uint8[6]`  | 6             | 6x8 matrix of boolean values (6 rows, 8 columns), indicating whether the tile `A[i][j]` is passable (1 - passable, 0 - not) |
| actionability      | `uint8[6]`  | 6             | 6x8 matrix of boolean values (6 rows, 8 columns), indicating whether the tile `A[i][j]` is actionable (1 - actionable, 0 - not) |
| allowed_landscapes | `uint8[2]`  | 2             | Bitmask; 1 bit per [`TerrainType`](../src/h3mtxt/Map/Constants/TerrainType.h), indicating whether objects that use this template should be allowed to be placed on that terrain in the Map Editor |
| landscape_group    | `uint8[2]`  | 2             | Bitmask; 1 bit per [`TerrainType`](../src/h3mtxt/Map/Constants/TerrainType.h), indicating whether this template should appear in the Objects tab corresponding to that terrain (e.g., "Dirt Objects", "Sand Objects", etc) in the Map Editor |
| object_class       | `uint32`    | 4             | Enum [`ObjectClass`](../src/h3mtxt/Map/Constants/ObjectClass.h)                             |
| object_subclass    | `uint32`    | 4             | Refines `object_class`                                                                      |
| object_group       | `uint8`     | 1             | Enum [`ObjectGroup`](../src/h3mtxt/Map/Constants/ObjectGroup.h)                             |
| is_ground          | `Bool`      | 1             | Indicates whether objects that use this template should be rendered as a part of the ground |
| reserved           | `uint8[16]` | 16            | Not used; set to 0s by default by the Map Editor                                            |


### `Object`
| Field name                                   | Type                          | Size in bytes | Description                                      |
| -------------------------------------------- | ----------------------------- | ------------- | ------------------------------------------------ |
| coordinates                                  | [`Coordinates`](#Coordinates) | 3             | Coordinates of the bottom right corner           |
| template_idx                                 | `uint32`                      | 4             | 0-based index of the corresponding [`ObjectTemplate`](#ObjectTemplate) from [`Map.objects_templates`](#Map) |
| reserved                                     | `uint8[5]`                    | 5             | Not used; set to 0s by default by the Map Editor |
| ?properties_abandoned_mine                   | [`ObjectPropertiesAbandonedMine`](#ObjectPropertiesAbandonedMine)                     | 4      | Only present if `OBJECT_CLASS` is 53 or 220 and `OBJECT_SUBCLASS` is 7 |
| ?properties_artifact                         | [`ObjectPropertiesArtifact`](#ObjectPropertiesArtifact)                               | varies | Only present if `OBJECT_CLASS` is 5, 65, 66, 67, 68 or 69 |
| ?properties_event                            | [`ObjectPropertiesEvent`](#ObjectPropertiesEvent)                                     | varies | Only present if `OBJECT_CLASS` is 26 |
| ?properties_flaggable                        | [`ObjectPropertiesFlaggable`](#ObjectPropertiesFlaggable)                             | 4      | Only present if `OBJECT_CLASS` is 17, 20, 42 or 87, or if `OBJECT_CLASS` is 53 or 220 and `OBJECT_SUBCLASS` is **not** 7 |
| ?properties_garrison                         | [`ObjectPropertiesGarrison`](#ObjectPropertiesGarrison)                               | 41     | Only present if `OBJECT_CLASS` is 33 or 219 |
| ?properties_grail                            | [`ObjectPropertiesGrail`](#ObjectPropertiesGrail)                                     | 4      | Only present if `OBJECT_CLASS` is 36 |
| ?properties_hero                             | [`ObjectPropertiesHero`](#ObjectPropertiesHero)                                       | varies | Only present if `OBJECT_CLASS` is 34, 62 or 70 |
| ?properties_hero_placeholder                 | [`ObjectPropertiesHeroPlaceholder`](#ObjectPropertiesHeroPlaceholder)                 | varies | Only present if `OBJECT_CLASS` is 214 |
| ?properties_monster                          | [`ObjectPropertiesMonster`](#ObjectPropertiesMonster)                                 | varies | Only present if `OBJECT_CLASS` is 54, 71, 72, 73, 74, 75, 162, 163 or 164 |
| ?properties_pandoras_box                     | [`ObjectPropertiesPandorasBox`](#ObjectPropertiesPandorasBox)                         | varies | Only present if `OBJECT_CLASS` is 6 |
| ?properties_quest_guard                      | [`ObjectPropertiesQuestGuard`](#ObjectPropertiesQuestGuard)                           | varies | Only present if `OBJECT_CLASS` is 215 |
| ?properties_random_dwelling                  | [`ObjectPropertiesRandomDwelling`](#ObjectPropertiesRandomDwelling)                   | varies | Only present if `OBJECT_CLASS` is 216 |
| ?properties_random_dwelling_alignment        | [`ObjectPropertiesRandomDwellingAlignment`](#ObjectPropertiesRandomDwellingAlignment) | 6      | Only present if `OBJECT_CLASS` is 218 |
| ?properties_random_dwelling_level            | [`ObjectPropertiesRandomDwellingLevel`](#ObjectPropertiesRandomDwellingLevel)         | varies | Only present if `OBJECT_CLASS` is 217 |
| ?properties_resource                         | [`ObjectPropertiesResource`](#ObjectPropertiesResource)                               | varies | Only present if `OBJECT_CLASS` is 76 or 79 |
| ?properties_scholar                          | [`ObjectPropertiesScholar`](#ObjectPropertiesScholar)                                 | 8      | Only present if `OBJECT_CLASS` is 81 |
| ?properties_seers_hut                        | [`ObjectPropertiesSeersHut`](#ObjectPropertiesSeersHut)                               | varies | Only present if `OBJECT_CLASS` is 83 |
| ?properties_shrine                           | [`ObjectPropertiesShrine`](#ObjectPropertiesShrine)                                   | 4      | Only present if `OBJECT_CLASS` is 88, 89 or 90 |
| ?properties_sign                             | [`ObjectPropertiesSign`](#ObjectPropertiesSign)                                       | varies | Only present if `OBJECT_CLASS` is 59 or 91 |
| ?properties_spell_scroll                     | [`ObjectPropertiesSpellScroll`](#ObjectPropertiesSpellScroll)                         | varies | Only present if `OBJECT_CLASS` is 93 |
| ?properties_town                             | [`ObjectPropertiesTown`](#ObjectPropertiesTown)                                       | varies | Only present if `OBJECT_CLASS` is 77 or 98 |
| ?properties_witch_hut                        | [`ObjectPropertiesWitchHut`](#ObjectPropertiesWitchHut)                               | 4      | Only present if `OBJECT_CLASS` is 113 |

`OBJECT_CLASS` and `OBJECT_SUBCLASS` are equal to `object_class` and `object_subclass` fields of `Map.objects_templates[template_idx]`. Due to this dependency, H3M cannot be described by a [context-free grammar](https://en.wikipedia.org/wiki/Context-free_grammar).


### `ObjectPropertiesAbandonedMine`
| Field name          | Type       | Size in bytes | Description                                      |
| ------------------- | ---------- | ------------- | ------------------------------------------------ |
| potential_resources | `uint8`    | 1             | Bitmask; 1 bit per [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) indicating if that resource can be produced by this mine |
| reserved            | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor |


### `ObjectPropertiesArtifact`
| Field name    | Type                      | Size in bytes | Description                                                                 |
| ------------- | ------------------------- | ------------- | --------------------------------------------------------------------------- |
| has_guardians | `Bool`                    | 1             | Indicates whether the message or guardians are customized for this artifact |
| ?guardians    | [`Guardians`](#Guardians) | varies        | Only present if `has_guardians` is nonzero                                  |


### `Guardians`
| Field name    | Type               | Size in bytes | Description                                                                  |
| ------------- | ------------------ | ------------- | ---------------------------------------------------------------------------- |
| message       | `String32`         | varies        | Message to display when the player tries to pick up the artifact             |
| has_creatures | `Bool`             | 1             | Indicates whether the creatures guarding this artifact are customized        |
| ?creatures    | [`CreatureStack[7]`](#CreatureStack) | 28 | Creatures guarding this artifact. Only present if `has_creatures` is nonzero |
| reserved      | `uint8[4]`         | 4             | Not used; set to 0s by default by the Map Editor                             |


### `CreatureStack`
| Field name | Type    | Size in bytes | Description                                                                                            |
| ---------- | ------- | ------------- | ------------------------------------------------------------------------------------------------------ |
| type       | `int16` | 2             | Enum [`CreatureType`](../src/h3mtxt/Map/Constants/CreatureType.h). Type of the creatures in this stack |
| quantity   | `int16` | 2             | The number of creatures in this stack                                                                  |


### `ObjectPropertiesEvent`
| Field name               | Type                      | Size in bytes | Description                                          |
| ------------------------ | ------------------------- | ------------- | ---------------------------------------------------- |
| event_base               | [`EventBase`](#EventBase) | varies        | Details about this event                             |
| affected_players         | `uint8`                   | 1             | Bitmask; 1 bit per [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) indicating if the event affects that player |
| applies_to_computer      | `Bool`                    | 1             | Indicates whether the event affects computer players |
| cancel_after_first_visit | `Bool`                    | 1             | Indicates whether the event should be canceled after the first time it's triggered |
| reserved                 | `uint8[4]`                | 4             | Not used; set to 0s by default by the Map Editor     |


### `EventBase`
| Field name           | Type                      | Size in bytes | Description                                                              |
| -------------------- | ------------------------- | ------------- | ------------------------------------------------------------------------ |
| has_guardians        | `Bool`                    | 1             | Indicates whether the message or guardians are customized for this event |
| ?guardians           | [`Guardians`](#Guardians) | varies        | Only present if `has_guardians` is nonzero                               |
| experience           | `int32`                   | 4             | Experience bonus (in experience points)                                  |
| spell_points         | `int32`                   | 4             | Spell points bonus                                                       |
| morale               | `int8`                    | 1             | Morale bonus                                                             |
| luck                 | `int8`                    | 1             | Luck bonus                                                               |
| resources            | `int32[7]`                | 28            | Given/taken amount for each [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |
| primary_skills       | `int8[4]`                 | 4             | The value for each primary skill in order of [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h) |
| num_secondary_skills | `uint8`                   | 1             | The number of secondary skills to grant to the visiting hero             |
| secondary_skills     | [`SecondarySkill[num_secondary_skills]`](#SecondarySkill) | varies | Secondary skills to grant to the visiting hero  |
| num_artifacts        | `uint8`                   | 1             | The number of artifacts to grant to the visiting hero                    |
| artifacts            | `int16[num_artifacts]`    | varies        | Artifacts to grant to the visiting hero. Each element is enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |
| num_spells           | `uint8`                   | 1             | The number of spells to grant to the visiting hero                       |
| spells               | `int8[num_spells]`        | varies        | Spells to grant to the visiting hero. Each element is enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h) |
| num_creatures        | `uint8`                   | 1             | The number of creature stacks to grant to the visiting hero              |
| creatures            | [`CreatureStack[num_creatures]`](#CreatureStack) | varies | Creatures to grant to the visiting hero |
| reserved             | `uint8[8]`                | 8             | Not used; set to 0s by default by the Map Editor                         |


### `ObjectPropertiesFlaggable`
| Field name | Type       | Size in bytes | Description                                                     |
| ---------- | ---------- | ------------- | --------------------------------------------------------------- |
| owner      | `uint8`    | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) |
| reserved   | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor                |


### `ObjectPropertiesGarrison`
| Field name       | Type                                 | Size in bytes | Description                                                     |
| ---------------- | ------------------------------------ | ------------- | --------------------------------------------------------------- |
| owner            | `uint8`                              | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) |
| reserved         | `uint8[3]`                           | 3             | Not used; set to 0s by default by the Map Editor                |
| creatures        | [`CreatureStack[7]`](#CreatureStack) | 28            | Troops in the garrison                                          |
| can_remove_units | `Bool`                               | 1             | Indicates whether the troops are removable                      |
| reserved2        | `uint8[8]`                           | 8             | Not used; set to 0s by default by the Map Editor                |


### `ObjectPropertiesGrail`
| Field name       | Type       | Size in bytes | Description                                      |
| ---------------- | ---------- | ------------- | ------------------------------------------------ |
| allowable_radius | `uint8`    | 1             | Allowable placement radius (in tiles)            |
| reserved         | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor |


### `ObjectPropertiesHero`
| Field name            | Type        | Size in bytes | Description                                                                        |
| --------------------- | ----------- | ------------- | ---------------------------------------------------------------------------------- |
| absod_id              | `uint32`    | 4             | Unique identifier assigned by the Map Editor                                       |
| owner                 | `uint8`     | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) (0xFF for imprisoned heroes) |
| type                  | `uint8`     | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h) (0xFF for Random Heroes) |
| has_name              | `Bool`      | 1             | Indicates whether the hero has a custom name                                       |
| ?name                 | `String32`  | varies        | The hero's name. Only present if `has_name` is nonzero                             |
| ?has_experience       | `Bool`      | 1             | Indicates whether the hero has a custom experience. Only present in **The Shadow of Death** maps |
| ?experience           | `int32`     | 4             | The hero's experience points. Only present if `has_experience` is present and nonzero or if this is an **Armageddon's Blade** map |
| has_portrait          | `Bool`      | 1             | Indicates whether the hero has a custom portrait                                   |
| ?portrait             | `uint8`     | 1             | Enum [`HeroPortrait`](../src/h3mtxt/Map/Constants/HeroPortrait.h). Only present if `has_portrait` is nonzero |
| has_secondary_skills  | `Bool`      | 1             | Indicates whether the hero has custom secondary skills                             |
| ?num_secondary_skills | `uint32`    | 4             | The number of secondary skills. Only present if `has_secondary_skills` is nonzero  |
| ?secondary_skills     | [`SecondarySkill[num_secondary_skills]`](#SecondarySkill) | varies | The hero's secondary skills. Only present if `has_secondary_skills` is nonzero |
| has_creatures         | `Bool`      | 1             | Indicates whether the hero has custom troops                                       |
| ?creatures            | [`CreatureStack[7]`](#CreatureStack) | 28 | The hero's troops. Only present if `has_creatures` is nonzero        |
| formation             | `uint8`     | 1             | Enum [`Formation`](../src/h3mtxt/Map/Constants/Formation.h). Formation of the hero's troops |
| has_artifacts         | `Bool`      | 1             | Indicates whether the hero has custom artifacts                                    |
| ?artifacts            | [`HeroArtifacts`](#HeroArtifacts) | varies | The hero's artifacts. Only present if `has_artifacts` is nonzero    |
| patrol_radius         | `int8`      | 1             | The hero's patrol radius (in tiles). Negative values imply no patrol               |
| has_biography         | `Bool`      | 1             | Indicates whether the hero has a custom biography                                  |
| ?biography            | `String32`  | varies        | The hero's biography. Only present if `has_biography` is nonzero                   |
| gender                | `uint8`     | 1             | Enum [`Gender`](../src/h3mtxt/Map/Constants/Gender.h). The hero's gender           |
| ?has_spells           | `Bool`      | 1             | Indicates whether the spells are customized for this hero. Only present in **The Shadow of Death** maps |
| ?spells               | `uint8[9]`  | 9             | Bitmask; 1 bit per [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h), indicating whether the hero knows that spell. Only present if `has_spells` is present and is nonzero |
| ?spell                | `uint8`     | 1             | Enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h). Only present in **Armageddon's Blade** maps |
| has_primary_skills    | `Bool`      | 1             | Indicates whether the primary skills are customized for this hero                  |
| ?primary_skills       | `int8[4]`   | 4             | The value of each primary skill in order of [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h). Only present if `has_primary_skills` is nonzero |
| reserved              | `uint8[16]` | 1             | Not used; set to 0s by default by the Map Editor                                   |


### `ObjectPropertiesHeroPlaceholder`
| Field name    | Type    | Size in bytes | Description                                                                                       |
| ------------- | ------- | ------------- | ------------------------------------------------------------------------------------------------- |
| owner         | `uint8` | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h)                                   |
| type          | `uint8` | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h) or `0xFF` if this is a power-rated hero |
| ?power_rating | `uint8` | 1             | The hero's Power Rating. Only present if `type` is `0xFF`                                         |


### `ObjectPropertiesMonster`
| Field name               | Type       | Size in bytes | Description                                                                   |
| ------------------------ | ---------- | ------------- | ----------------------------------------------------------------------------- |
| absod_id                 | `uint32`   | 4             | Unique identifier assigned by the Map Editor                                  |
| quantity                 | `uint16`   | 2             | Th number of creatures or 0 if it's random. In the game the number of creatures will be initialized with `quantity MOD 4096` |
| disposition              | `uint8`    | 1             | Enum [`Disposition`](../src/h3mtxt/Map/Constants/Disposition.h)               |
| has_message_and_treasure | `Bool`     | 1             | Indicates whether the message and/or treature are customized for this monster |
| ?message_and_treasure    | [`MessageAndTreasure`](#MessageAndTreasure) | varies | The message and treasure |
| never_flees              | `Bool`     | 1             | Indicates whether the monster never flees                                     |
| does_not_grow            | `Bool`     | 1             | Indicates whether the quantity doesn't grow                                   |
| reserved                 | `uint8[2]` | 2             | Not used; set to 0s by default by the Map Editor                              |


### `MessageAndTreasure`
| Field name | Type       | Size in bytes | Description                                                                                |
| ---------- | ---------- | ------------- | ------------------------------------------------------------------------------------------ |
| message    | `String32` | varies        | Message to display                                                                         |
| resources  | `int32[7]` | 28            | Given/taken quantity for each [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |
| artifact   | `int16`    | 2             | Enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h)                          |


### `ObjectPropertiesPandorasBox`
| Field name | Type                      | Size in bytes | Description                      |
| ---------- | ------------------------- | ------------- | -------------------------------- |
| event_base | [`EventBase`](#EventBase) | varies        | Details about this Pandora's Box |


### `ObjectPropertiesQuestGuard`
| Field name | Type              | Size in bytes | Description             |
| ---------- | ----------------- | ------------- | ----------------------- |
| quest      | [`Quest`](#Quest) | varies        | Details about the quest |


### `Quest`
| Field name            | Type                                        | Size in bytes | Description                                         |
| --------------------- | ------------------------------------------- | ------------- | --------------------------------------------------- |
| type                  | `uint8`                                     | 1             | Enum [`QuestType`](../src/h3mtxt/Map/Constants/QuestType.h). Type of the quest |
| ?quest_level          | [`QuestLevel`](#QuestLevel)                 | 4             | Only present if `type` is 1                         |
| ?quest_primary_skills | [`QuestPrimarySkills`](#QuestPrimarySkills) | 4             | Only present if `type` is 2                         |
| ?quest_defeat_hero    | [`QuestDefeatHero`](#QuestDefeatHero)       | 4             | Only present if `type` is 3                         |
| ?quest_defeat_monster | [`QuestDefeatMonster`](#QuestDefeatMonster) | 4             | Only present if `type` is 4                         |
| ?quest_artifacts      | [`QuestArtifacts`](#QuestArtifacts)         | varies        | Only present if `type` is 5                         |
| ?quest_creatures      | [`QuestCreatures`](#QuestCreatures)         | varies        | Only present if `type` is 6                         |
| ?quest_resources      | [`QuestResources`](#QuestResources)         | 28            | Only present if `type` is 7                         |
| ?quest_be_hero        | [`QuestBeHero`](#QuestBeHero)               | 1             | Only present if `type` is 8                         |
| ?quest_be_player      | [`QuestBePlayer`](#QuestBePlayer)           | 1             | Only present if `type` is 9                         |
| ?deadline             | `uint32`                                    | 4             | The day before which the quest must be completed, or `0xFFFFFFFF` if there is no deadline. 0 is "Month: 1, Week: 1, Day: 1". Only present if `type` is not 0 |
| ?proposal             | `String32`                                  | varies        | Proposal message. Only present if `type` is not 0   |
| ?progress             | `String32`                                  | varies        | Progress message. Only present if `type` is not 0   |
| ?completion           | `String32`                                  | varies        | Completion message. Only present if `type` is not 0 |


### `QuestLevel`
| Field name | Type    | Size in bytes | Description                                |
| ---------- | ------- | ------------- | ------------------------------------------ |
| level      | `int32` | 4             | Experience level that needs to be achieved |


### `QuestPrimarySkills`
| Field name | Type      | Size in bytes | Description |
| ---------- | --------- | ------------- | ----------- |
| skills     | `int8[4]` | 4             | The value for each primary skill in order of [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h) |


### `QuestDefeatHero`
| Field name | Type     | Size in bytes | Description |
| ---------- | -------- | ------------- | ----------- |
| absod_id   | `uint32` | 4             | ID of the hero that needs to be defeated (see absod_id in [`ObjectPropertiesHero`](#ObjectPropertiesHero)) |


### `QuestDefeatMonster`
| Field name | Type     | Size in bytes | Description |
| ---------- | -------- | ------------- | ----------- |
| absod_id   | `uint32` | 4             | ID of the monster that needs to be defeated (see absod_id in [`ObjectPropertiesMonster`](#ObjectPropertiesMonster)) |


### `QuestArtifacts`
| Field name    | Type                   | Size in bytes | Description                        |
| ------------- | ---------------------- | ------------- | ---------------------------------- |
| num_artifacts | `uint8`                | 1             | The number of artifacts to deliver |
| artifacts     | `int16[num_artifacts]` | varies        | Artifacts to deliver; each element is enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |


### `QuestCreatures`
| Field name    | Type                                             | Size in bytes | Description                              |
| ------------- | ------------------------------------------------ | ------------- | ---------------------------------------- |
| num_creatures | `uint8`                                          | 1             | The number of creature stacks to deliver |
| creatures     | [`QuestCreature[num_creatures]`](#QuestCreature) | varies        | Creatures to deliver                     |


### `QuestCreature`
| Field name | Type     | Size in bytes | Description                                                                                            |
| ---------- | -------- | ------------- | ------------------------------------------------------------------------------------------------------ |
| type       | `int16`  | 2             | Enum [`CreatureType`](../src/h3mtxt/Map/Constants/CreatureType.h). Type of the creatures in this stack |
| quantity   | `uint16` | 2             | The number of creatures in this stack                                                                  |


### `QuestResources`
| Field name | Type       | Size in bytes | Description                                                                               |
| ---------- | ---------- | ------------- | ----------------------------------------------------------------------------------------- |
| resources  | `int32[7]` | 28            | The required amount for each [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |


### `QuestBeHero`
| Field name | Type    | Size in bytes | Description                                               |
| ---------- | ------- | ------------- | --------------------------------------------------------- |
| hero       | `uint8` | 1             | Enum [`HeroType`](../src/h3mtxt/Map/Constants/HeroType.h) |


### `QuestBePlayer`
| Field name | Type    | Size in bytes | Description                                                     |
| ---------- | ------- | ------------- | --------------------------------------------------------------- |
| player     | `uint8` | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) |


### `ObjectPropertiesRandomDwelling`
| Field name    | Type       | Size in bytes | Description                                                                             |
| ------------- | ---------- | ------------- | --------------------------------------------------------------------------------------- |
| owner         | `uint8`    | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h)                         |
| reserved      | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor                                        |
| town_absod_id | `uint32`   | 4             | `absod_id` of the town, or 0 if the dwelling's alignment is not tied to a specific town |
| ?alignment    | `uint8[2]` | 2             | Bitmask; 1 bit per [`TownType`](../src/h3mtxt/Map/Constants/TownType.h) indicating whether that town can be the alignment of this dwelling. Only present if `town_absod_id` is 0 |
| min_level     | `uint8`    | 1             | The minimum level of the generated creatures (0 - Level 1, 6 - Level 7)                 |
| max_level     | `uint8`    | 1             | The maximum level of the generated creatures (0 - Level 1, 6 - Level 7)                 |


### `ObjectPropertiesRandomDwellingAlignment`
| Field name    | Type       | Size in bytes | Description                                                             |
| ------------- | ---------- | ------------- | ----------------------------------------------------------------------- |
| owner         | `uint8`    | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h)         |
| reserved      | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor                        |
| min_level     | `uint8`    | 1             | The minimum level of the generated creatures (0 - Level 1, 6 - Level 7) |
| max_level     | `uint8`    | 1             | The maximum level of the generated creatures (0 - Level 1, 6 - Level 7) |


### `ObjectPropertiesRandomDwellingLevel`
| Field name    | Type       | Size in bytes | Description                                                                             |
| ------------- | ---------- | ------------- | --------------------------------------------------------------------------------------- |
| owner         | `uint8`    | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h)                         |
| reserved      | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor                                        |
| town_absod_id | `uint32`   | 4             | `absod_id` of the town, or 0 if the dwelling's alignment is not tied to a specific town |
| ?alignment    | `uint8[2]` | 2             | Bitmask; 1 bit per [`TownType`](../src/h3mtxt/Map/Constants/TownType.h) indicating whether that town can be the alignment of this dwelling. Only present if `town_absod_id` is 0 |


### `ObjectPropertiesResource`
| Field name    | Type                      | Size in bytes | Description                                                                 |
| ------------- | ------------------------- | ------------- | --------------------------------------------------------------------------- |
| has_guardians | `Bool`                    | 1             | Indicates whether the message or guardians are customized for this resource |
| ?guardians    | [`Guardians`](#Guardians) | varies        | Only present if `has_guardians` is nonzero                                  |
| quantity      | `uint32`                  | 4             | Multiply by 100 for Gold (i.e. if `object_subclass` is 6); 0 means Random   |
| reserved      | `uint8[4]`                | 4             | Not used; set to 0s by default by the Map Editor                            |


### `ObjectPropertiesScholar`
| Field name       | Type       | Size in bytes | Description                                                                              |
| ---------------- | ---------- | ------------- | ---------------------------------------------------------------------------------------- |
| type             | `uint8`    | 1             | Enum [`ScholarRewardType`](../src/h3mtxt/Map/Constants/ScholarRewardType.h)              |
| ?primary_skill   | `uint8`    | 1             | Enum [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h). Only present if `type` is 0 |
| ?secondary_skill | `uint8`    | 1             | Enum [`SecondarySkillType`](../src/h3mtxt/Map/Constants/SecondarySkillType.h). Only present if `type` is 1 |
| ?spell           | `uint8`    | 1             | Enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h). Only present if `type` is 2 |
| ?random          | `uint8`    | 1             | Not used; set to 0 by default by the Map Editor. Only present if `type` is 0xFF          |
| reserved         | `uint8[6]` | 6             | Not used; set to 0s by default by the Map Editor                                         |


### `ObjectPropertiesSeersHut`
| Field name | Type                | Size in bytes | Description                                      |
| ---------- | ------------------- | ------------- | ------------------------------------------------ |
| quest      | [`Quest`](#Quest)   | varies        |                                                  |
| reward     | [`Reward`](#Reward) | varies        |                                                  |
| reserved   | `uint8[2]`          | 2             | Not used; set to 0s by default by the Map Editor |


### `Reward`
| Field name       | Type                                | Size in bytes | Description                                                   |
| ---------------- | ----------------------------------- | ------------- | ------------------------------------------------------------- |
| type             | `uint8`                             | 1             | Enum [`RewardType`](../src/h3mtxt/Map/Constants/RewardType.h) |
| ?experience      | `int32`                             | 4             | Only present if `type` is 1                                   |
| ?spell_points    | `int32`                             | 4             | Only present if `type` is 2                                   |
| ?morale          | `int8`                              | 1             | Only present if `type` is 3                                   |
| ?luck            | `int8`                              | 1             | Only present if `type` is 4                                   |
| ?resource        | [`RewardResource`](#RewardResource) | 5             | Only present if `type` is 5                                   |
| ?primary_skill   | [`RewardPrimarySkill`](#RewardPrimarySkill) | 2     | Only present if `type` is 6                                   |
| ?secondary_skill | [`SecondarySkill`](#SecondarySkill) | 2             | Only present if `type` is 7                                   |
| ?artifact        | `int16`                             | 2             | Only present if `type` is 8. Enum [`ArtifactType`](../src/h3mtxt/Map/Constants/ArtifactType.h) |
| ?spell           | `int8`                              | 1             | Only present if `type` is 9. Enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h) |
| ?creatures       | [`CreatureStack`](#CreatureStack)   | 4             | Only present if `type` is 10                                  |


### `RewardResource`
| Field name    | Type    | Size in bytes | Description                                                       |
| ------------- | ------- | ------------- | ----------------------------------------------------------------- |
| resource_type | `uint8` | 1             | Enum [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |
| quantity      | `int32` | 4             |                                                                   |


### `RewardPrimarySkill`
| Field name | Type    | Size in bytes | Description                                                               |
| ---------- | ------- | ------------- | ------------------------------------------------------------------------- |
| type       | `uint8` | 1             | Enum [`PrimarySkillType`](../src/h3mtxt/Map/Constants/PrimarySkillType.h) |
| bonus      | `int8`  | 1             |                                                                           |


### `ObjectPropertiesShrine`
| Field name | Type       | Size in bytes | Description                                                 |
| ---------- | ---------- | ------------- | ----------------------------------------------------------- |
| spell      | `int8`     | 1             | Enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h) | 
| reserved   | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor            |


### `ObjectPropertiesSign`
| Field name | Type       | Size in bytes | Description                                                                    |
| ---------- | ---------- | ------------- | ------------------------------------------------------------------------------ |
| message    | `String32` | varies        | Message to display, or an empty string if a random message should be displayed | 
| reserved   | `uint8[4]` | 4             | Not used; set to 0s by default by the Map Editor                               |


### `ObjectPropertiesSpellScroll`
| Field name    | Type                      | Size in bytes | Description                                                                 |
| ------------- | ------------------------- | ------------- | --------------------------------------------------------------------------- |
| has_guardians | `Bool`                    | 1             | Indicates whether the message or guardians are customized for this artifact |
| ?guardians    | [`Guardians`](#Guardians) | varies        | Only present if `has_guardians` is nonzero                                  |
| spell         | `int8`                    | 1             | Enum [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h)                 | 
| reserved      | `uint8[3]`                | 3             | Not used; set to 0s by default by the Map Editor                            |


### `ObjectPropertiesTown`
| Field name         | Type       | Size in bytes | Description |
| ------------------ | ---------- | ------------- | ------------------------------------------------------------------------------- |
| absod_id           | `uint32`   | 4             | Unique identifier assigned by the Map Editor                                    |
| owner              | `uint8`    | 1             | Enum [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h)                 |
| has_name           | `Bool`     | 1             | Indicates whether the name is customized for this town                          |
| ?name              | `String32` | varies        | The name of this town. Only present if `has_name` is nonzero                    |
| has_garrison       | `Bool`     | 1             | Indicates whether the garrisoned creatures are customized                       |
| ?garrison          | [`CreatureStack[7]`](#CreatureStack) | 28 | Only present if `has_garrison` is nonzero                        |
| formation          | `Bool`     | 1             | Enum [`Formation`](../src/h3mtxt/Map/Constants/Formation.h). Formation of the garrisoned troops |
| has_buildings      | `Bool`     | 1             | Indicates whether built/allowed buildings are customized for this town          |
| ?buildings         | [`TownBuildings`](#TownBuildings) | 12 | Build/allowed buildings. Only present if `has_buildings` is nonzero |
| ?has_fort          | `Bool`     | 1             | Only present if `has_buildings` is zero                                         |
| must_have_spell    | `uint8[9]` | 9             | Bitmask; 1 bit per [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h), indicating whether this spell must appear in the Mage Guild |
| may_not_have_spell | `uint8[9]` | 9             | Bitmask; 1 bit per [`SpellType`](../src/h3mtxt/Map/Constants/SpellType.h), indicating whether this spell may not appear in the Mage Guild |
| num_events         | `uint32`   | 4             | The number of Timed Events for this town                                        |
| events             | [`TownEvent[num_events]`](#TownEvent) | varies | Timed Events for this town |
| alignment          | `uint8`    | 1             | For a non-random town: should be `0xFF`. For a Random Town: should be interpreted as [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) ("Same as Player N"); `0xFF` means "Same as Owner or Random" |
| reserved           | `uint8[3]` | 3             | Not used; set to 0s by default by the Map Editor                                |


### `TownBuildings`
| Field name  | Type       | Size in bytes | Description |
| ----------- | ---------- | ------------- | ----------- |
| is_built    | `uint8[6]` | 6             | Bitmask; 1 bit per [`TownBuildingType`](../src/h3mtxt/Map/Constants/TownBuildingType.h), indicating whether that building is built |
| is_disabled | `uint8[6]` | 6             | Bitmask; 1 bit per [`TownBuildingType`](../src/h3mtxt/Map/Constants/TownBuildingType.h), indicating whether that building is disabled |


### `TownEvent`
| Field name | Type                        | Size in bytes | Description                                      |
| ---------- | --------------------------- | ------------- | ------------------------------------------------ |
| base       | [`TimedEvent`](#TimedEvent) | varies        | Common properties of this event                  |
| buildings  | `uint8[6]`                  | 6             | Bitmask; 1 bit per [`TownBuildingType`](../src/h3mtxt/Map/Constants/TownBuildingType.h), indicating whether that building gets built |
| creatures  | `uint16[7]`                 | 14            | Growth for each creature level                   |
| reserved   | `uint8[4]`                  | 4             | Not used; set to 0s by default by the Map Editor |


### `ObjectPropertiesWitchHut`
| Field name       | Type       | Size in bytes | Description |
| ---------------- | ---------- | ------------- | ----------- |
| potential_skills | `uint8[4]` | 4             | Bitmask; 1 bit per [`SecondarySkillType`](../src/h3mtxt/Map/Constants/SecondarySkillType.h) indicating whether this Witch Hut can grant that secondary skill |


### `TimedEvent`
| Field name             | Type        | Size in bytes | Description                                                                              |
| ---------------------- | ----------- | ------------- | ---------------------------------------------------------------------------------------- |
| name                   | `String32`  | varies        | The name to display in the Map Editor                                                    |
| message                | `String32`  | varies        | Message to display in the game                                                           |
| resources              | `int32[7]`  | 28            | Given/taken amount for each [`ResourceType`](../src/h3mtxt/Map/Constants/ResourceType.h) |
| affected_players       | `uint8`     | 1             | Bitmask; 1 bit per [`PlayerColor`](../src/h3mtxt/Map/Constants/PlayerColor.h) indicating whether this event affects that player |
| ?applies_to_human      | `Bool`      | 1             | Indicates whether this event affects human players. Only present in **The Shadow of Death** maps |
| applies_to_computer    | `Bool`      | 1             | Indicates whether this event affects computer players                                    |
| day_of_first_occurence | `int16`     | 2             | 0-based day of the first occurence for this event (0 stands for "Month: 1, Week: 1, Day: 1") |
| repeat_after_days      | `uint16`    | 2             | Frequency of this event; 0 means that the event doesn't repeat[^1].                      |
| reserved               | `uint8[16]` | 16            | Not used; set to 0s by default by the Map Editor                                         |


[^1]: Strictly speaking, *all* events are recurring: even if `repeat_after_days` is set to 0, the event will trigger again after 65536 months because time is a flat circle.
