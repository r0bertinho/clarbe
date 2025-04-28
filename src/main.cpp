#include <print>
#include <vector>
#include <string>
#include <windows.h>

#include "consts.hpp"
#include "commands.hpp"

typedef int (*CMD_func)(const std::vector<std::string>&);

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
    return commands[args[0]](args);
  }

  // Load the command's DLL
  HMODULE dll_file = LoadLibrary((clarbe_env + "/bin/" + args[0] + ".dll").c_str());
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

  // Call the 'proc' function
  int ret = proc(args);

  // Clean up
  FreeLibrary(dll_file);

  return ret;
}