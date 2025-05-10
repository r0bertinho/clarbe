#include <cstdlib>
#include <filesystem>
#include <print>

#include "cmd_template.hpp"
#include "toml.hpp"

namespace fs = std::filesystem;

MAIN_FUNC(const args_t& args) {
  if (!fs::is_directory("target/bin")) {
    std::println("Project not built.\n");
    return 0;
  }

  toml::table local_config = toml::parse_file("clarbe.toml");

  std::system(("target\\bin\\" + *(local_config["package"]["name"].value<std::string>())).c_str());

  return 0;
}