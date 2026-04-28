# h3mtxt source code

*h3mtxt* uses modular design to reduce redundancy when used as a library.

| Component                                     | Description                                                                     | Dependencies |
| --------------------------------------------- | ------------------------------------------------------------------------------- | ------------ |
| [`Map`](Map)                                  | A header-only library that provides a structured representation of a .h3m file. | |
| [`Campaign`](Campaign)                        | A header-only library that provides a structured representation of a .h3c file. | [`Map`](Map) |
| [`H3MReader`](H3Reader/H3MReader)             | A library for reading .h3m files.                                               | [`Map`](Map), [`thirdparty/zlib`](thirdparty/zlib), [`thirdparty/zstr`](thirdparty/zstr) |
| [`H3CReader`](H3Reader/H3CReader)             | A library for reading .h3c files.                                               | [`Campaign`](Campaign), [`H3MReader`](H3Reader/H3MReader), [`thirdparty/zlib`](thirdparty/zlib), [`thirdparty/zstr`](thirdparty/zstr) |
| [`H3MWriter`](H3Writer/H3MWriter)             | A library for writing .h3m files.                                               | [`Map`](Map), [`thirdparty/zlib`](thirdparty/zlib), [`thirdparty/zstr`](thirdparty/zstr) |
| [`H3CWriter`](H3Writer/H3CWriter)             | A library for writing .h3c files.                                               | [`Campaign`](Campaign), [`H3MWriter`](H3Writer/H3MWriter), [`thirdparty/zlib`](thirdparty/zlib), [`thirdparty/zstr`](thirdparty/zstr) |
| [`Medea`](Medea)                              | A framework for serializing user-defined classes as JSON.                       | |
| [`JsonCommon`](JsonCommon)                    | A header-only library that provides shared code for [`H3JsonWriter`](H3JsonWriter) and [`H3JsonReader`](H3JsonReader). | |
| [`H3MJsonWriter`](H3JsonWriter/H3MJsonWriter) | A library for serializing classes from [`Map`](Map) as JSON.                    | [`Map`](Map), [`JsonCommon`](JsonCommon), [`Medea`](Medea) |
| [`H3CJsonWriter`](H3JsonWriter/H3CJsonWriter) | A library for serializing classes from [`Campaign`](Campaign) as JSON.          | [`Campaign`](Campaign), [`JsonCommon`](JsonCommon), [`H3MJsonWriter`](H3JsonWriter/H3MJsonWriter), [`Medea`](Medea) |
| [`H3MJsonReader`](H3JsonReader/H3MJsonReader) | A library for deserializing classes from [`Map`](Map) from JSON.                | [`Map`](Map), [`JsonCommon`](JsonCommon), [`thirdparty/jsoncpp`](thirdparty/jsoncpp) |
| [`H3CJsonReader`](H3JsonReader/H3CJsonReader) | A library for deserializing classes from [`Campaign`](Campaign) as JSON.        | [`Campaign`](Campaign), [`JsonCommon`](JsonCommon), [`H3MJsonReader`](H3JsonReader/H3MJsonReader), [`thirdparty/jsoncpp`](thirdparty/jsoncpp) |

For example, if you only need to read .h3m files, you can simply add a dependency from [`H3MReader`](H3Reader/H3MReader), ignoring everything related to Campaign and JSON.

See [examples](../../examples) for actual examples of using *h3mtxt* as a library.
