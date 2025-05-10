#include <filesystem>
#include <print>
#include <cstdlib>

#include "cmd_template.hpp"
#include "consts.hpp"
#include "toml.hpp"

namespace fs = std::filesystem;

MAIN_FUNC(const args_t& args) {
  if (!fs::exists("clarbe.toml")) {
    std::println("Project file not detected.");
    return 0;
  }

  toml::table local_config;
  toml::table global_config;

  try {
    local_config = toml::parse_file("clarbe.toml");
    global_config = toml::parse_file(clarbe_env + "/config.toml");
  } catch (const toml::parse_error& err) {
    std::println("Error parsing config file:\n{}\n", err.description());
    return 1;
  }

  std::optional<std::string> pkg_name = local_config["package"]["name"].value<std::string>();

  if (!pkg_name) {
    std::println("package name not defined.");
  }

  const auto& source_directories = local_config["local"]["sources"].as_array();
  const auto& include_directories = local_config["local"]["includes"].as_array();

  if (!source_directories) {
    std::println("Source directories not defined properly.");
  } else if (!include_directories) {
    std::println("Source directories not defined properly.");
  }

  std::optional<std::string> compiler = local_config["build"]["compiler"].value<std::string>();

  if (!compiler) /* compiler does not exist */ {
    compiler = global_config["build"]["compiler"].value<std::string>();
  }
  
  if (!compiler) {
    std::println("No compiler provided.");
    return 1;
  }

  std::optional<std::string> std = local_config["package"]["std"].value<std::string>();

  if (!std) /* std not defined */ {
    *std = "";
  } else {
    *std = "-std=" + *std;
  }

  fs::create_directories("target/object");
  fs::create_directories("target/bin");

  std::optional<bool> using_usr_macro = local_config["uses"]["macro_file"].value<bool>();
  std::optional<bool> using_usr_build = local_config["uses"]["macro_file"].value<bool>();

  if (using_usr_macro) {
    // use macros file
  }

  if (using_usr_build) {
    // use build file
  }

  std::string includes = "";
  for (const auto& node : *include_directories) {
    includes += "-I " + node.as_string()->get() + " ";
  }

  // compile source to .obj files
  for (const auto& node : *source_directories) {
    const std::string dir = node.as_string()->get();
    for (const auto& entry : fs::directory_iterator(dir)) {
      const std::string path = entry.path().string();
      const std::string filename = entry.path().stem().string();
      std::system((*compiler + " -c " + path + " -o target/object/" + filename + ".o " + *std + " " + includes).c_str());
    }
  }

  std::string pre = "";
  std::optional<std::string> build_type = local_config["package"]["build_type"].value<std::string>();

  if (!build_type || *build_type == "exec") {
    // build executable
  } else if (*build_type == "plugin" || *build_type == "dll") {
    pre = "-shared";
    *pkg_name += ".dll";
  }

  std::system((*compiler + " " + pre + " -o target/bin/" + *pkg_name + " target/object/*.o " + *std + " " + includes).c_str());

  return 0;
}