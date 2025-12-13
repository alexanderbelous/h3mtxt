# Examples

This is a tutorial for using undocumented features of the .h3m file format via *h3mtxt*.

# Prerequisites

1. You need to have "Heroes of Might and Magic III: The Shadow of Death" installed (or The Complete Edition). The undocumented features of the game that can be used via *h3mtxt* refer to the behavior of the official game. I have no idea if these features work in mods (such as HoTA) or alternative engines (such as VCMI), and I don't care.
   * As an exception, [HoMM3 HD](https://sites.google.com/site/heroes3hd/) mod and the [SoD SP](http://heroescommunity.com/viewthread.php3?TID=44581) plugin are fine - generally, they aim to preserve the original behavior of the game.
2. You need to have a compiled *h3mtxt* program. If you are using Microsoft Windows, you can just download the official version from https://github.com/alexanderbelous/h3mtxt/releases . Alternatively, if you have some programming skills, you can build it yourself from the source files: see the instructions at https://github.com/alexanderbelous/h3mtxt .
3. You need to have at least the basic knowledge of how to use the [command-line interface](https://en.wikipedia.org/wiki/Command-line_interface) (CLI). *h3mtxt* doesn't currently have a graphical user interface (GUI), so converting .h3m/.h3c files to JSON (or the other way around) is done via CLI.
4. (Optional) The tutorial will be easier to follow if you have at least basic knowledge of the [JSON](https://en.wikipedia.org/wiki/JSON) serialization format.
5. (Optional) I recommend that you use a text editor that has syntax highlight for JSON (for example, [Sublime Text](https://www.sublimetext.com/)).

# Intro

In HoMM3, some objects on the Adventure Map can give you a `Morale` bonus. Both the official Map Editor and the Unleashed Editor only allow the `Morale` bonus to be within [-3; +3], but the game has well-defined behavior for any number within [-128; 127]. This can be useful if, for example, you want to ensure that the hero's troops will have +3 `Morale` even though they come from 7 different town types (in which case their `Morale` is decreased by 5).

In this example you will learn how to enable such "unusual" `Morale` bonuses via *h3mtxt*.

## Convert the test map to JSON
1. Copy `test_map.h3m` from this directory to the directory in which *h3mtxt* is located.
2. Run the following command from the directory in which *h3mtxt* is located:
```
h3mtxt test_map.h3m test_map.h3m.json
```

This should create a new file named `test_map.h3m.json` in the directory in which *h3mtxt* is located.

## Open the created JSON document

(You can use any text editor, but I recomment using an editor that has syntax highlight for JSON.)

The created JSON documents starts like this:
```jsonc
{
  "format": 28,
  "basic_info": {
    "is_playable": 1,
    "map_size": 36,
    "has_two_levels": 0,
    "name": "h3mtxt Demo Map",
    "description": "This map is used in the Github repository https:\/\/github.com\/alexanderbelous\/h3mtxt to demonstrate how you can use the h3mtxt program.",
    "difficulty": 1, // Normal
    "max_hero_level": 0
  },
```

This describes the [`MapBasicInfo`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/MapBasicInfo.h) section of the .h3m file. Most of the data here can be modified from the official Map Editor: Tools -> Map Specifications...

We don't want to touch it right now, so scroll down to the `"objects"` member of the JSON document (use the Find command of your text editor, if possible).

The `"objects"` member starts like this:
```jsonc
  "objects": [
    // Object 0
    {
      "x": 35,
      "y": 5,
      "z": 0,
      // ObjectClass: 98 (TOWN)
      // ObjectPropertiesType: 20 (TOWN)
      "template_idx": 2,
      "unknown": [0, 0, 0, 0, 0],
      "properties": {
        "absod_id": 1063237438,
        "owner": 1, // Blue
        "formation": 0, // Spread
        "has_fort": 1,
        "must_have_spell": {
          "summon_boat": false,
          "scuttle_boat": false,
```

Each element of `"objects"` is represented by [`Object`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/Object.h) structure.

Different objects on the Adventure Map have different properties. In the .h3m file format, properties are split into 2 groups:
* Properties of the *object template* (represented by [`ObjectTemplate`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/ObjectTemplate.h) structure): for example, all standard `Shipyard` objects use the same template, which defines:
  * the sprite, which determines the image used in the game for such objects.
  * The "type" of the object. In .h3m the type is defined by 2 values, sometimes called `object_class` and `object_subclass`. These determine what the object **does**:
    * `ObjectClass::ALTAR_OF_SACRIFICE` (2) allows sacrificing artifacts and/or creatures in exchange for experience.
    * `ObjectClass::SHIPYARD` (87) allows buying ships.
    * ... and so on. See [`ObjectClass.h`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/Constants/ObjectClass.h) for the full list.
  * which tiles of the object are passable and which ones are not (i.e. if the hero can move freely though these tiles)
  * which tiles of the object are actionable and which ones are not (i.e. the hero can interact with the object on these tiles)
  * ...
* Properties of the *object* itself (represented by [`ObjectProperties`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/ObjectProperties.h)):
  * These vary depending on `object_class` and `object_subclass` from the template used by this object. In practice, even though there are a lot of combinations of `object_class` and `object_subclass`, most of them have the same set of properties. In *h3mtxt* these sets are called [`ObjectPropertiesType`](https://github.com/alexanderbelous/h3mtxt/blob/master/Map/Constants/ObjectPropertiesType.h).


## Find the section for the `Pandora's Box` that gives `Morale` bonus

You can either search for a string `This {Pandora's Box} contains a {Morale} bonus` or search for an object whose `(x, y)` coordinates on the Adventure Map are `(7, 1)`.
* This is a convenient way of finding the relevant sections in JSON documents generated by *h3mtxt*. If your object has a custom message, there is likely exactly 1 match in the JSON document (unless you reuse this message in other objects). Otherwise, you can search for an objects via its coordinates, since you already know them from the Map Editor.

This section looks like this:
```jsonc
    // Object 7
    {
      "x": 7,
      "y": 1,
      "z": 0,
      // ObjectClass: 6 (PANDORAS_BOX)
      // ObjectPropertiesType: 8 (PANDORAS_BOX)
      "template_idx": 9,
      "unknown": [0, 0, 0, 0, 0],
      "properties": {
        "guardians": {
          "message": "This {Pandora's Box} contains a {Morale} bonus.\n\nBoth the official Map Editor and the Unleashed Editor only allow the bonus to be within [-3; +3], but {h3mtxt} allows using any number withing [-128; 127].\n\nThis can be useful if, for example you want to ensure that the hero's troops will have +3 {Morale} even though they come from 7 different town types (in which case their {Morale} is decreased by 5).",
          "unknown": [0, 0, 0, 0]
        },
        "experience": 0,
        "spell_points": 0,
        "morale": 3,
        "luck": 0,
        "resources": {
          "wood": 0,
          "mercury": 0,
          "ore": 0,
          "sulfur": 0,
          "crystal": 0,
          "gems": 0,
          "gold": 0
        },
        "primary_skills": {
          "attack": 0,
          "defense": 0,
          "spell_power": 0,
          "knowledge": 0
        },
        "secondary_skills": [],
        "artifacts": [],
        "spells": [],
        "creatures": [],
        "unknown": [0, 0, 0, 0, 0, 0, 0, 0]
      }
    },
```

## Modify the `Morale` bonus

Change the line
```jsonc
"morale": 3,
```
to
```jsonc
"morale": 20,
```

## Save the modified JSON document

However it's done in your preferred text editor.

## Convert the JSON document back to .h3m

Run the following command from the directory in which *h3mtxt* and `test_map.h3m.json` are located:
```
h3mtxt test_map.h3m.json test_map_morale_20.h3m
```

## Copy the new map to the `Maps` subdirectory of your HoMM3 installation.

Use the File Explorer, or the command line, or whatever you prefer. You are a mapmaker, I'm sure you know how to do this.

The file containing the new map is called `test_map_morale_20.h3m`.

## Run HoMM3

You don't need help doing this, right?

## Start playing the map you've created

It's called "h3mtxt Demo Map".

Your hero starts with troops from 7 different towns, which decreases their `Morale` by 5.

Go north and pick up the `Pandora's Box` that grants `Morale`.

Now your `Morale` is temporarily increased by 20.

Attack the `Peasants` located south to check that your troops have positive (+3) `Morale`:

![Screenshot from the game](test_map_morale_20.jpg)
