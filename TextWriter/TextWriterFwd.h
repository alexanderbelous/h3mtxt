#pragma once

namespace Util_NS
{
  class IndentedTextWriter;

  class ScopedArrayWriterBase;

  template<class T>
  class ScopedArrayWriter;

  class ScopedStructWriter;

  using FieldsWriter = ScopedStructWriter;

  // Class for writing *values* with indent.
  template<class T, class Enable = void>
  struct ValueWriter;

  // Class for writing *structures* with indent.
  //
  // Specialize this for your structures.
  template<class T, class Enable = void>
  struct StructWriter;
  // {
  //   void operator()(FieldsWriter& out, const T& value);
  // };
}
