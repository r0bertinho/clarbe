#include <windows.h>

#include <print>
#include <cstdlib>
#include <string>
#include <vector>

#include "commands.hpp"
#include "consts.hpp"
#include "toml.hpp"

typedef int (*CMD_func)(const std::vector<std::string>&);

void run_toml_before_cmd();
void run_toml_after_cmd();

int main(int argc, char** argv) {
  if (clarbe_env == "null") {
    std::println("Environment variable 'CLARBE_HOME' not defined.");
    return 1;
  }

  std::vector<std::string> args;

  if (argc == 1) {
    std::println("No arguments provided, try 'help'.");
    return 1;
  }

  // Starts at 1 to skip executable's path
  for (int i = 1; i < argc; i++) {
    args.push_back(std::string(argv[i]));
  }

  // Check if it's a basic command
  if (commands.contains(args[0])) {
    run_toml_before_cmd();
    int ret = commands[args[0]](args);
    run_toml_after_cmd();
    return ret;
  }

  // Load the command's DLL
  HMODULE dll_file =
      LoadLibrary((clarbe_env + "/bin/" + args[0] + ".dll").c_str());
  if (!dll_file) {
    std::println("Could not find command '{}'.", args[0]);
    return 1;
  }

  // Get the address of the 'proc' function
  CMD_func proc = (CMD_func)GetProcAddress(dll_file, "proc");
  if (!proc) {
    std::println("Could not locate main function in command.\n");
    FreeLibrary(dll_file);
    return 1;
  }

  run_toml_before_cmd();
  int ret = proc(args);
  run_toml_after_cmd();

  FreeLibrary(dll_file);
  return ret;
}

void run_toml_before_cmd() {
  toml::table local_config;

  try {
    local_config = toml::parse_file("clarbe.toml");
  } catch (const toml::parse_error& err) {
    std::println("Error parsing config file:\n{}\n", err.description());
  }

  if (local_config["build"]["run_before"]) {
    const auto& commands = *(local_config["build"]["run_before"].as_array());

    for (const auto& node : commands) {
      std::system(node.as_string()->get().c_str());
    }
  }
}

void run_toml_after_cmd() {
  toml::table local_config;

  try {
    local_config = toml::parse_file("clarbe.toml");
  } catch (const toml::parse_error& err) {
    std::println("Error parsing config file:\n{}\n", err.description());
  }

  if (local_config["build"]["run_after"]) {
    const auto& commands = *(local_config["build"]["run_after"].as_array());

    for (const auto& node : commands) {
      std::system(node.as_string()->get().c_str());
    }
  }
}