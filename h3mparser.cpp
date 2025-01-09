#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: h3mparser map-path" << std::endl;
    return -1;
  }

  const fs::path path_map(argv[1]);

  return 0;
}
