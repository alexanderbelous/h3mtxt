#include <h3mtxt/H3Writer/writeh3m.h>

#include <h3mtxt/H3Writer/H3Writer.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m
{
  void writeh3m(std::ostream& stream, const Map& map, bool compress)
  {
    // Ugly hack.
    // C++ guarantees that temporary objects remain valid until the end of the expression,
    // but static_cast cannot be used to convert an rvalue reference to an lvalue reference.
    const auto remove_rvalue_ref = [](zstr::ostream&& stream) -> std::ostream& {return stream; };
    writeData(compress ? remove_rvalue_ref(zstr::ostream(stream)) : stream, map);
  }
}
