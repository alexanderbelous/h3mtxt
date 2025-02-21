#pragma once

#include <h3mtxt/H3Reader/IntegerWidth.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <iosfwd>
#include <type_traits>
#include <vector>

namespace h3m::H3Reader_NS
{
  namespace Detail_NS
  {
    std::vector<SecondarySkill> readSecondarySkillsVectorImpl(std::istream& stream, IntegerWidth sizeof_num_elements);
  }

  // Reads a vector of secondary skills.
  // \param VectorSizeType - unsigned integer type in which the number of secondary skills is encoded.
  //        Usually it's uint32, but in Pandora's Box it's uint8.
  // \param stream - input stream.
  // \return the decoded vector of secondary skills.
  template<class VectorSizeType>
  std::vector<SecondarySkill> readSecondarySkillsVector(std::istream& stream)
  {
    static_assert(std::is_integral_v<VectorSizeType>, "VectorSizeType must be an integral type.");
    static_assert(std::is_unsigned_v<VectorSizeType>, "VectorSizeType must be an unsigned type.");
    return Detail_NS::readSecondarySkillsVectorImpl(stream, Detail_NS::IntegerWidth(std::in_place_type<VectorSizeType>));
  }
}