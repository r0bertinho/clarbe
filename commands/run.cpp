#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>
#include <print>

#include "toml.hpp"

namespace fs = std::filesystem;

extern "C" __declspec(dllexport) int proc(const std::vector<std::string>& args) {
  if (!fs::is_directory("target/bin")) {
    std::println("Project not built.\n");
    return 0;
  }

  std::string exec_file("target/bin/");

  auto local_config = toml::parse_file("clarbe.toml");
  exec_file += *(local_config["package"]["name"].value<std::string>()) + ".exe";

  ShellExecute(NULL, "open", exec_file.c_str(), NULL, NULL, SW_SHOWDEFAULT);

  return 0;
}