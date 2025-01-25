#pragma once

#include <type_traits>
#include <utility>

namespace h3m
{
  namespace Detail_NS
  {
    // Class for storing the width (in bytes) of any integral type.
    // This is just to make sure that the value passed to readUintImpl() is
    // actually equal to sizeof(T) for some integral type T.
    class IntegerWidth
    {
    public:
      // Constructs IntegerWidth for the specified integral type.
      // This function only participates in the overload resolution if T is an integral type.
      template<class T, class Enable = std::enable_if_t<std::is_integral_v<T>>>
      consteval IntegerWidth(std::in_place_type_t<T>):
        num_bytes_(sizeof(T))
      {
      }

      // \return the size (in bytes) of the integral type for which this IntegerWidth was constructed.
      //         For the returned value N it's guaranteed that
      //             0 < N && N <= sizeof(std::uintmax_t)
      constexpr std::size_t size() const noexcept { return num_bytes_; }

    private:
      std::size_t num_bytes_;
    };
  }
}