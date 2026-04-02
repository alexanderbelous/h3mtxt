#include "parseJsonFromString.h"

#include <sstream>
#include <stdexcept>
#include <string>

namespace h3json
{
  Json::Value parseJsonFromString(std::string_view str)
  {
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    Json::String errs;
    // TODO: ideally, this should be std::ispanstream, but it only became available in C++23.
    // std::istrstream can also be used, but it will get deprecated in C++26.
    // So fuck it. This is only for tests anyway.
    std::istringstream stream{ std::string{str} };

    Json::Value root;
    if (!parseFromStream(builder, stream, &root, &errs))
    {
      throw std::runtime_error("readH3mJson(): " + errs);
    }
    return root;
  }
}
