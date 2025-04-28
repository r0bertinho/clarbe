#include <string>
#include <vector>
#include <filesystem>
#include <print>
#include "toml.hpp"

namespace fs = std::filesystem;

extern "C" __declspec(dllexport) int proc(const std::vector<std::string>& args) {
  if (!fs::exists("clarbe.toml")) {
    std::println("Project file not detected.");
    return 0;
  }

  auto local_config = toml::parse_file("clarbe.toml");

  fs::create_directories("target/object");
  fs::create_directories("target/bin");

  // compile code

  return 0;
}