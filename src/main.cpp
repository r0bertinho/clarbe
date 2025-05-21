#if defined(__linux__)
#include <dlfcn.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#else
#error "platform not supported"
#endif

#include <iostream>
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
    std::cout << "Environment variable 'CLARBE_HOME' not defined.\n";
    return 1;
  }

  std::vector<std::string> args;

  if (argc == 1) {
    std::cout << "No arguments provided, try 'help'.\n";
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

  // Load the command's shared library or DLL
  #if defined(__linux__)
  void* dll_file = dlopen((clarbe_env + "/bin/" + args[0] + ".so").c_str(), RTLD_LAZY);
  #elif defined(_WIN32)
  HMODULE dll_file = LoadLibrary((clarbe_env + "/bin/" + args[0] + ".dll").c_str());
  #endif

  if (!dll_file) {
    std::cout << "Could not find command '" << args[0] << "'.\n";
    return 1;
  }

  // Get the address of the 'proc' function
  CMD_func proc = nullptr;
  #if defined(__linux__)
  proc = (CMD_func)dlsym(dll_file, "proc");
  #elif defined(_WIN32)
  proc = (CMD_func)GetProcAddress(dll_file, "proc");
  #endif

  if (!proc) {
    std::cout << "Could not locate main function in command.\n";
    #if defined(__linux__)
    dlclose(dll_file);
    #elif defined(_WIN32)
    FreeLibrary(dll_file);
    #endif
    return 1;
  }

  run_toml_before_cmd();
  int ret = proc(args);
  run_toml_after_cmd();

  #if defined(__linux__)
  dlclose(dll_file);
  #elif defined(_WIN32)
  FreeLibrary(dll_file);
  #endif

  return ret;
}

void run_toml_before_cmd() {
  toml::table local_config;

  try {
    local_config = toml::parse_file("clarbe.toml");
  } catch (const toml::parse_error& err) {
    std::cout << "Error parsing config file:\n" << err.description() << "\n";
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
    std::cout << "Error parsing config file:\n" << err.description() << "\n";
  }

  if (local_config["build"]["run_after"]) {
    const auto& commands = *(local_config["build"]["run_after"].as_array());

    for (const auto& node : commands) {
      std::system(node.as_string()->get().c_str());
    }
  }
}
