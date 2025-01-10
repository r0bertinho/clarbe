#include <cstring>
#include <iostream>

#include "args.hpp"
#include "commands/files.hpp"
#include "consts.hpp"
#include "messages.h"
#include "toml++/toml.hpp"

int main(int argc, char** argv) {
  if (clarbe_env != nullptr) {  // no error
  } else {
    std::cout
        << "\'CLARBE_HOME\' environment variable not defined. closing...\n";
    free(clarbe_env);
    return 1;
  }

  char* env_toml_path = new char[sizeof(clarbe_env) + sizeof("/config.toml")];
  strcpy(env_toml_path, clarbe_env);
  strcat(env_toml_path, "/config.toml");

  auto config_file = toml::parse_file(env_toml_path);

  delete[] env_toml_path;

  /* --------------------
                  Error cases
     -------------------- */

  /* --------------------
                  Commands
     -------------------- */
  if (!has_arg(argv[1], "-?-?h(?:elp)?"))  // help command
  {
    std::cout << HELP_MSG;
    free(clarbe_env);
    return 0;
  } else if (!has_arg(argv[1], "-?-?v(?:ersion)?"))  // version command
  {
    std::cout << VERSION << '\n';
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "clean") &&
             !std::strcmp(argv[2], "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (remove_tree(clarbe_local_lib_path)) {
      std::cerr << "Something went wrong while cleaning local libraries\n";
      delete[] clarbe_local_lib_path;
      free(clarbe_env);
      return 1;
    }
    delete[] clarbe_local_lib_path;
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "clean")) {
    if (remove_tree("target")) {
      std::cerr << "Something went wrong while cleaning\n";
      free(clarbe_env);
      return 1;
    }
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "check") &&
             !std::strcmp(argv[2], "--global")) {
    // also for integrity and version of local libs
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "check")) {
    // check code for errors and warnings
    // also for integrity and version of libs
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "run")) {
    if (create_dir("target") == 1) {
      // run existing code
    } else {
      goto compile_code;
    }

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "build") ||
             !std::strcmp(argv[1], "compile")) {
  compile_code:
    if (!path_exists("clarbe.toml")) {
      std::cerr << "No project file detected.\n";
      free(clarbe_env);
      return 1;
    }

    create_dir("target");
    create_dir("target/object");

    // ------ //

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "new")) {
    if (argc < 3) {
      std::cerr << "No project name defined.\nuse \"clarbe new "
                   "<project_name>\"\n";
      free(clarbe_env);
      return 1;
    } else if (create_dir(argv[2]) == 1) {
      std::cerr << "Directory already exists.\n";
      free(clarbe_env);
      return 1;
    }

    generate_new_content(argv[2]);
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "init")) {
    if (argc < 3) {
      std::cerr << "No folder name defined.\nuse \"clarbe init <folder>\"\n";
      free(clarbe_env);
      return 1;
    } else if (create_dir(argv[2]) != 1) {
      std::cerr << "Directory does not exist.\n";
      remove_tree(argv[2]);
      free(clarbe_env);
      return 1;
    }

    generate_new_content(argv[2]);
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "add") && !has_arg(argv, "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\n";
      delete[] clarbe_local_lib_path;
      free(clarbe_env);
      return 1;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      delete[] clarbe_local_lib_path;
      free(clarbe_env);
      return 1;
    }

    delete[] clarbe_local_lib_path;
    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "remove") && !has_arg(argv, "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\"\n";
      delete[] clarbe_local_lib_path;
      free(clarbe_env);
      return 1;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      delete[] clarbe_local_lib_path;
      free(clarbe_env);
      return 1;
    }

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "add")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\n";
      free(clarbe_env);
      return 1;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";
      free(clarbe_env);
      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      free(clarbe_env);
      return 1;
    }

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "remove")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\"\n";
      free(clarbe_env);
      return 1;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";
      free(clarbe_env);
      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      free(clarbe_env);
      return 1;
    }

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "config") && !has_arg(argv, "--global")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";
      free(clarbe_env);
      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      free(clarbe_env);
      return 1;
    }

    free(clarbe_env);
    return 0;
  } else if (!std::strcmp(argv[1], "config")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";
      free(clarbe_env);
      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      free(clarbe_env);
      return 1;
    }

    free(clarbe_env);
    return 0;
  }

  std::cerr << "No valid arguments provided, try '-h' or '--help'\n";
  free(clarbe_env);
  return 0;
}
