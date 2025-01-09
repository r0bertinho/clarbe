#include "commands/conf.hpp"

#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>

#include "commands/libs.hpp"
#include "toml++/toml.hpp"

int add_lib_to_toml(char *libname) {
  auto config_file = toml::parse_file("clarbe.toml");

  char *most_recent;

  get_latest_tag(most_recent, libname);

  config_file.insert_or_assign("libraries",
                               toml::table{{libname, most_recent}});

  free(most_recent);

  fprintf(stdout, "added library \'%s\' to clarbe.toml\n", libname);

  return 0;
}

int add_lib_to_toml(char *libname, char *version) {
  auto config_file = toml::parse_file("clarbe.toml");

  config_file.insert_or_assign("libraries", toml::table{{libname, version}});

  fprintf(stdout, "added library \'%s\' to clarbe.toml\n", libname);

  return 0;
}

int take_lib_from_toml(char *libname) {
  std::regex regex(std::string(libname) + " = .+\n");

  std::fstream config_file("clarbe.toml");
  std::string line;

  if (!config_file.good()) {
    fprintf(stderr, "problem with project file.\n");
    return 2;
  }

  try {
    while (getline(config_file, line)) {
      if (regex_search(line, regex)) {
        line = "";

        config_file.close();

        fprintf(stdout, "removed library \'%s\' from clarbe.toml\n", libname);

        return 0;
      }
    }
  } catch (...) {
    config_file.close();

    fprintf(stderr, "an unrecognized error occurred while removing \'%s\'.\n",
            libname);

    return 2;
  }

  config_file.close();

  fprintf(stderr, "library \'%s\' not found in clarbe.toml\n", libname);

  return 1;
}