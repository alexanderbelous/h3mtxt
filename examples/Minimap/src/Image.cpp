#include <Minimap/Image.h>

#include "thirdparty/lodepng/lodepng.h"

#include <algorithm>
#include <utility>

namespace Minimap_NS
{
  Image::Image(unsigned int width, unsigned int height):
    pixels_{ std::make_unique<Color[]>(static_cast<std::size_t>(width) * height) },
    width_{ width },
    height_{ height }
  {}

  Image::Image(const Image& other):
    Image(other.width(), other.height())
  {
    std::span<const Color> pixels_src = other.data();
    std::span<Color> pixels_dest = data();
    std::copy(pixels_src.begin(), pixels_src.end(), pixels_dest.begin());
  }

  Image::Image(Image&& other) noexcept:
    pixels_{ std::move(other.pixels_) },
    width_{ other.width_ },
    height_{ other.height_ }
  {
    other.width_ = 0;
    other.height_ = 0;
  }

  Image& Image::operator=(const Image& other)
  {
    if (area() == other.area())
    {
      // Reuse previously allocated memory if the area is the same.
      std::span<const Color> pixels_src = other.data();
      std::span<Color> pixels_dest = data();
      std::copy(pixels_src.begin(), pixels_src.end(), pixels_dest.begin());
      width_ = other.width();
      height_ = other.height();
    }
    else
    {
      // Delegate to copy ctor and move assignment.
      *this = Image{ other };
    }
    return *this;
  }

  Image& Image::operator=(Image&& other) noexcept
  {
    pixels_ = std::move(pixels_);
    width_ = other.width_;
    height_ = other.height_;
    other.width_ = 0;
    other.height_ = 0;
    return *this;
  }

  void writeImage(const std::filesystem::path& output_path, const Image& image)
  {
    const std::span<const Color> rgb_data = image.data();
    const unsigned int status = lodepng_encode_file(
      output_path.string().c_str(),
      reinterpret_cast<const unsigned char*>(rgb_data.data()),
      image.width(),
      image.height(),
      LodePNGColorType::LCT_RGB, 8);
    if (status != 0)
    {
      throw std::runtime_error(lodepng_error_text(status));
    }
  }
}
