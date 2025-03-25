#pragma once

#include <h3mtxt/Medea/IJsonSerializer.h>

#include <iosfwd>
#include <string>

namespace Medea_NS
{
  // Implementation of IJsonSerializer that writes minified JSON to std::ostream.
  //
  // Note that the constructor is private; only the static member function writeJson()
  // can be used directly.
  class MinifiedJsonWriter final : private IJsonSerializer
  {
  public:
    // Serializes the given value into the specified stream as JSON.
    // \param stream - output stream.
    // \param value - value to serialize.
    template<class T>
    static void writeJson(std::ostream& stream, const T& value);

  private:
    explicit constexpr MinifiedJsonWriter(std::ostream& stream) noexcept :
      stream_(stream)
    {}

    void beforeWriteElementOrField() override;

    // Writes a boolean value to the output stream.
    void writeBool(bool value) override;

    // Writes a signed integer value to the output stream.
    void writeInt(std::intmax_t value) override;

    // Writes an unsigned integer value to the output stream.
    void writeUInt(std::uintmax_t value) override;

    // Writes a string value to the output stream.
    void writeString(std::string_view value) override;

    void writeArray(ArrayWriterPtr array_writer, const void* value, bool) override;

    void writeObject(ObjectWriterPtr object_writer, const void* value, bool) override;

    void writeFieldName(std::string_view field_name) override;

    // Does nothing.
    void writeComment(std::string_view, bool) override;

    void beginAggregate(char bracket);

    void endAggregate(char bracket);

    std::ostream& stream_;
    // True if one or more entries (i.e. values or fields) have been printed in the current scope, false otherwise.
    bool has_members_in_scope_ = false;
  };

  template<class T>
  void MinifiedJsonWriter::writeJson(std::ostream& stream, const T& value)
  {
    MinifiedJsonWriter writer(stream);
    writer.writeValueRaw(value, true);
  }
}
