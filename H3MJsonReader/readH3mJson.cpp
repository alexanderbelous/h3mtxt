#include <h3mtxt/H3MJsonReader/readH3mJson.h>

#include <json/json.h>

#include <istream>
#include <stdexcept>

namespace h3m
{
  Map readH3mJson(std::istream& stream)
  {
    Json::Value root;
    stream >> root;
    throw std::logic_error("NotImplemented.");
  }
}
