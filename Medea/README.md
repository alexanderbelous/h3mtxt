# Simple framework for serializing user-defined classes as JSON

[H3JsonWriter](/H3JsonWriter) doesn't use [jsoncpp](https://github.com/open-source-parsers/jsoncpp) or any other thirdparty library for serialization because I want to add a lot of comments in the output JSON; existing libraries for JSON serialization generally don't have a good API for that.
