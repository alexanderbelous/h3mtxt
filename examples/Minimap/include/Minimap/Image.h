#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <span>
#include <stdexcept>

namespace Minimap_NS
{
  // RGB24 color.
  struct Color
  {
    constexpr bool operator==(const Color&) const noexcept = default;

    std::uint8_t r = 0;  // Red component
    std::uint8_t g = 0;  // Green component
    std::uint8_t b = 0;  // Blue component
  };

  // RGB24 image.
  class Image
  {
  public:
    // Constructs a 0x0 image.
    constexpr Image() noexcept = default;

    // Constructs an image of the specified size.
    // All pixels are black initially.
    // \param width - width of the image in pixels.
    // \param height - height of the image in pixels.
    Image(unsigned int width, unsigned int height);

    // Copy constructor.
    // \param other - image to copy.
    Image(const Image& other);

    // Move constructor.
    // \param other - image to move-construct from. @other will become a 0x0 image after this call.
    Image(Image&& other) noexcept;

    // Copy assignment.
    // \param other - image to copy.
    // \return *this
    Image& operator=(const Image& other);

    // Move assignment.
    // \param other - image to move-assign from. @other will become a 0x0 image after this call.
    // \return *this
    Image& operator=(Image&& other) noexcept;

    // Destructor.
    ~Image() = default;

    // \return the width of the image in pixels.
    constexpr unsigned int width() const noexcept
    {
      return width_;
    }

    // \return the height of the image in pixels.
    constexpr unsigned int height() const noexcept
    {
      return height_;
    }

    // \return the area of the image in pixels.
    constexpr std::size_t area() const noexcept
    {
      return static_cast<std::size_t>(width()) * height();
    }

    // \return all pixels as a plain array.
    std::span<Color> data() noexcept
    {
      return std::span<Color>{pixels_.get(), area()};
    }

    // \return all pixels as a plain array.
    std::span<const Color> data() const noexcept
    {
      return std::span<const Color>{pixels_.get(), area()};
    }

    // Returns the color of the specified pixel.
    // \param x - X-coordinate of the pixel.
    // \param y - Y-coordinate of the pixel.
    // \return the color of the pixel (x, y).
    // \throw std::out_of_range if x >= width() || y >= height().
    Color& operator()(unsigned int x, unsigned int y)
    {
      return const_cast<Color&>(static_cast<const Image&>(*this)(x, y));
    }

    // Returns the color of the specified pixel.
    // \param x - X-coordinate of the pixel.
    // \param y - Y-coordinate of the pixel.
    // \return the color of the pixel (x, y).
    // \throw std::out_of_range if x >= width() || y >= height().
    const Color& operator()(unsigned int x, unsigned int y) const
    {
      if (x >= width() || y >= height())
      {
        throw std::out_of_range("Image::operator(): (x, y) is out of range.");
      }
      const std::size_t pixel_idx = static_cast<std::size_t>(y) * width_ + x;
      return pixels_[pixel_idx];
    }

  private:
    std::unique_ptr<Color[]> pixels_;
    unsigned int width_ = 0;
    unsigned int height_ = 0;
  };

  // Writes the specified image as PNG.
  // \param output_path - path to the output PNG file.
  // \param image - image to write.
  // \throw std::runtime_error if failed to write the PNG.
  void writeImage(const std::filesystem::path& output_path, const Image& image);
}
