#include <h3mtxt/H3JsonReader/Utils.h>

#include <json/json.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  const Json::Value& getJsonField(const Json::Value& value, std::string_view field_name)
  {
    if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
    {
      return *field;
    }
    throw MissingJsonFieldError(field_name);
  }

  bool JsonReader<bool>::operator()(const Json::Value& value) const
  {
    if (!value.isBool())
    {
      throw std::runtime_error("readH3mJson(): expected bool, got " + value.toStyledString());
    }
    return value.asBool();
  }

  std::string JsonReader<std::string>::operator()(const Json::Value& value) const
  {
    if (!value.isString())
    {
      throw std::runtime_error("readH3mJson(): expected std::string, got " + value.toStyledString());
    }
    return value.asString();
  }
}
