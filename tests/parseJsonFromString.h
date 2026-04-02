#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>

#include <json/json.h>

#include <string_view>

namespace h3json
{
  Json::Value parseJsonFromString(std::string_view str);

  template<class T>
  T parseH3JsonFromString(std::string_view str)
  {
    return fromJson<T>(parseJsonFromString(str));
  }
}