#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <print>
#include <filesystem>

#include "toml.hpp"

namespace fs = std::filesystem;

#define CMD_FUNC [](const std::vector<std::string>& args) -> int

std::map<std::string, std::function<int(const std::vector<std::string>&)>> commands = {
  {"help", CMD_FUNC {
    const char help_msg[] =
      "Software usage: \"clarbe <action> [args]?\"\n"
      "\n"
      "clarbe new <project-name>\n"
      "     | add [<creator>_<name>]\n"
      "     | remove [<creator>_<name>]\n"
      "     | config <placement> [<configuration>=<value>]\n"
      "     | init\n"
      "     | build\n"
      "     | help\n"
      "     | clean\n"
      "     | check\n"
      "     | run\n"
      "--------------------------------";

    std::println("{}", help_msg);
    return 0;
  }},
  {"version", CMD_FUNC {
    const char version[] = "0.0.1";

    std::println("{}", version);
    return 0;    
  }},
  {"clean", CMD_FUNC {
    fs::remove_all(args[1]);
    return 0;
  }}
};

#endif