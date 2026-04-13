#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <sstream>
#include <string>
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::ReservedData via H3MWriter.
    // \param reserved_data - input ReservedData.
    // \return std::string storing the encoded data.
    template<std::size_t NumBytes>
    std::string encodeReservedData(const ReservedData<NumBytes>& reserved_data)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(reserved_data);
      return std::move(stream).str();
    }

    // Decodes h3m::ReservedData via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::ReservedData decoded from @encoded_data.
    template<std::size_t NumBytes>
    ReservedData<NumBytes> decodeReservedData(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readReservedData<NumBytes>();
    }

    template<std::size_t N>
    constexpr std::array<std::byte, N> makeIotaArray() noexcept
    {
      std::array<std::byte, N> values {};
      for (std::size_t i = 0; i < N; ++i)
      {
        values[i] = static_cast<std::byte>(i);
      }
      return values;
    }

    // The size of an array that is assumed to be stored inline in ReservedData.
    //
    // The implementation of ReservedData is encouraged not to allocate dynamic memory if the number of elements is
    // small. The threshold is implementation-specific, but it's reasonable to assume that a single byte will not be
    // dynamically allocated.
    //
    // Note that this is merely an assumption - ReservedData doesn't provide an API to check if the
    // array is stored inline.
    using SmallSizeType = std::integral_constant<std::size_t, 1>;

    // The size of an array that is assumed to be dynamically allocated in ReservedData.
    //
    // The implementation of ReservedData is encouraged to allocate dynamic memory if the number of elements is
    // large. The threshold is implementation-specific.
    //
    // Note that this is merely an assumption - ReservedData doesn't provide an API to check if the
    // array is stored inline.
    using LargeSizeType = std::integral_constant<std::size_t, sizeof(void*) + 1>;
  }

  // FYI: only H3M.ReservedData.MakeExplicit checks if ReservedData is implicit or explicit.

  TEMPLATE_TEST_CASE("H3M.ReservedData.DefaultConstructor", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    const ReservedData<kSize> data;
    REQUIRE(data.size() == kSize);
    for (std::size_t i = 0; i < kSize; ++i)
    {
      REQUIRE(data[i] == std::byte{ 0 });
      REQUIRE(data.at(i) == std::byte{ 0 });
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.MakeExplicit", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    ReservedData<kSize> data;
    data.makeExplicit();
    REQUIRE(data.size() == kSize);
    REQUIRE(data.isExplicit() == true);
    REQUIRE(data.data() != nullptr);
    for (std::size_t i = 0; i < kSize; ++i)
    {
      REQUIRE(data[i] == std::byte{ 0 });
      REQUIRE(data.at(i) == std::byte{ 0 });
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.ConstructFromArray", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
    const ReservedData<kSize> data{ kValues };
    REQUIRE(data.size() == kSize);
    for (std::size_t i = 0; i < kSize; ++i)
    {
      REQUIRE(data[i] == kValues[i]);
      REQUIRE(data.at(i) == kValues[i]);
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.CopyConstructor", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    SECTION("All zeroes")
    {
      const ReservedData<kSize> data1;
      const ReservedData<kSize> data2{ data1 };
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == std::byte{ 0 });
        REQUIRE(data1.at(i) == std::byte{ 0 });
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Non-zero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      const ReservedData<kSize> data1{ kValues };
      const ReservedData<kSize> data2{ data1 };
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == kValues[i]);
        REQUIRE(data1.at(i) == kValues[i]);
        REQUIRE(data2[i] == kValues[i]);
        REQUIRE(data2.at(i) == kValues[i]);
      }
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.CopyAssignment", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    SECTION("Assign AllZero to AllZero")
    {
      const ReservedData<kSize> data1;
      ReservedData<kSize> data2;
      data2 = data1;
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == std::byte{ 0 });
        REQUIRE(data1.at(i) == std::byte{ 0 });
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Assign NonZero to AllZero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      const ReservedData<kSize> data1{ kValues };
      ReservedData<kSize> data2;
      data2 = data1;
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == kValues[i]);
        REQUIRE(data1.at(i) == kValues[i]);
        REQUIRE(data2[i] == kValues[i]);
        REQUIRE(data2.at(i) == kValues[i]);
      }
    }
    SECTION("Assign AllZero to NonZero")
    {
      const ReservedData<kSize> data1;
      ReservedData<kSize> data2{ makeIotaArray<kSize>() };
      data2 = data1;
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == std::byte{ 0 });
        REQUIRE(data1.at(i) == std::byte{ 0 });
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Assign NonZero to NonZero")
    {
      constexpr std::array<std::byte, kSize> kValues1 = makeIotaArray<kSize>();
      std::array<std::byte, kSize> values2 = kValues1;
      for (std::byte& value : values2)
      {
        value = static_cast<std::byte>(static_cast<unsigned char>(value) + 1);
      }

      const ReservedData<kSize> data1{ kValues1 };
      ReservedData<kSize> data2{ values2 };
      data2 = data1;
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data1[i] == kValues1[i]);
        REQUIRE(data1.at(i) == kValues1[i]);
        REQUIRE(data2[i] == kValues1[i]);
        REQUIRE(data2.at(i) == kValues1[i]);
      }
    }
    SECTION("Self-assignment AllZero")
    {
      ReservedData<kSize> data;
      data = data;
      REQUIRE(data.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data[i] == std::byte{ 0 });
        REQUIRE(data.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Self-assignment NonZero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      ReservedData<kSize> data{ kValues };
      data = data;
      REQUIRE(data.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data[i] == kValues[i]);
        REQUIRE(data.at(i) == kValues[i]);
      }
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.MoveConstructor", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    SECTION("All zeroes")
    {
      ReservedData<kSize> data1;
      const ReservedData<kSize> data2{ std::move(data1) };
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Non-zero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      ReservedData<kSize> data1{ kValues };
      const ReservedData<kSize> data2{ std::move(data1) };
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == kValues[i]);
        REQUIRE(data2.at(i) == kValues[i]);
      }
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.MoveAssignment", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    SECTION("Assign AllZero to AllZero")
    {
      ReservedData<kSize> data1;
      ReservedData<kSize> data2;
      data2 = std::move(data1);
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Assign NonZero to AllZero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      ReservedData<kSize> data1{ kValues };
      ReservedData<kSize> data2;
      data2 = std::move(data1);
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == kValues[i]);
        REQUIRE(data2.at(i) == kValues[i]);
      }
    }
    SECTION("Assign AllZero to NonZero")
    {
      ReservedData<kSize> data1;
      ReservedData<kSize> data2{ makeIotaArray<kSize>() };
      data2 = std::move(data1);
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == std::byte{ 0 });
        REQUIRE(data2.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Assign NonZero to NonZero")
    {
      constexpr std::array<std::byte, kSize> kValues1 = makeIotaArray<kSize>();
      std::array<std::byte, kSize> values2 = kValues1;
      for (std::byte& value : values2)
      {
        value = static_cast<std::byte>(static_cast<unsigned char>(value) + 1);
      }

      ReservedData<kSize> data1{ kValues1 };
      ReservedData<kSize> data2{ values2 };
      data2 = std::move(data1);
      REQUIRE(data1.size() == kSize);
      REQUIRE(data2.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data2[i] == kValues1[i]);
        REQUIRE(data2.at(i) == kValues1[i]);
      }
    }
    SECTION("Self-assignment AllZero")
    {
      ReservedData<kSize> data;
      data = std::move(data);
      REQUIRE(data.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data[i] == std::byte{ 0 });
        REQUIRE(data.at(i) == std::byte{ 0 });
      }
    }
    SECTION("Self-assignment NonZero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      ReservedData<kSize> data{ kValues };
      data = std::move(data);
      REQUIRE(data.size() == kSize);
      for (std::size_t i = 0; i < kSize; ++i)
      {
        REQUIRE(data[i] == kValues[i]);
        REQUIRE(data.at(i) == kValues[i]);
      }
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.Equality", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    SECTION("All zeroes")
    {
      const ReservedData<kSize> data1;
      const ReservedData<kSize> data2;
      REQUIRE(data1 == data1);
      REQUIRE(data1 == data2);
    }
    SECTION("Non-zero")
    {
      constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      const ReservedData<kSize> data1{ kValues };
      const ReservedData<kSize> data2{ kValues };
      REQUIRE(data1 == data1);
      REQUIRE(data1 == data2);
    }
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.Inequality", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;
    static_assert(kSize > 0, "Don't test zero-sized arrays here - they are always equal");

    std::array<std::byte, kSize> values1 = makeIotaArray<kSize>();
    std::array<std::byte, kSize> values2 = makeIotaArray<kSize>();
    values1.front() = std::byte{1};
    values2.front() = std::byte{2};
    ReservedData<kSize> data1{ values1 };
    ReservedData<kSize> data2{ values2 };
    REQUIRE(data1 != data2);
  }

  TEMPLATE_TEST_CASE("H3M.ReservedData.Encoding", "[H3M]", SmallSizeType, LargeSizeType)
  {
    constexpr std::size_t kSize = TestType::value;

    SECTION("All zero")
    {
      const ReservedData<kSize> kReservedData;
      static constexpr std::array<char, kSize> kBinaryDataArray {};
      static constexpr std::string_view kBinaryData{ kBinaryDataArray.data(), kSize };
      REQUIRE(asByteVector(encodeReservedData(kReservedData)) == asByteVector(kBinaryData));
      REQUIRE(decodeReservedData<kSize>(kBinaryData) == kReservedData);
      REQUIRE(encodeAndDecodeJson(kReservedData) == kReservedData);
    }
    SECTION("Non-zero")
    {
      static constexpr std::array<std::byte, kSize> kValues = makeIotaArray<kSize>();
      const ReservedData<kSize> kReservedData{ kValues };
      const std::string_view kBinaryData{ reinterpret_cast<const char*>(kValues.data()), kSize };
      REQUIRE(asByteVector(encodeReservedData(kReservedData)) == asByteVector(kBinaryData));
      REQUIRE(decodeReservedData<kSize>(kBinaryData) == kReservedData);
      REQUIRE(encodeAndDecodeJson(kReservedData) == kReservedData);
    }
  }
}
