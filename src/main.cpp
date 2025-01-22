#include <cstring>
#include <filesystem>
#include <iostream>

#include "args.hpp"
#include "commands/conf.hpp"
#include "commands/files.hpp"
#include "commands/libs.hpp"
#include "consts.hpp"
#include "messages.h"
#include "toml.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  if (clarbe_env == nullptr) {
    std::cout
        << "\'CLARBE_HOME\' environment variable not defined. closing...\n";

    return 1;
  }

  char* env_toml_path =
      (char*)malloc(strlen(clarbe_env) + strlen("/config.toml") + 1);
  strcpy(env_toml_path, clarbe_env);
  strcat(env_toml_path, "/config.toml");

  toml::parse_result env_config_file;

  try {
    env_config_file = toml::parse_file(env_toml_path);
  } catch (...) {
    std::cout
        << "An error occurred while reading \'CLARBE_HOME/config.toml\'\n";
    free(env_toml_path);
    return 1;
  }

  free(env_toml_path);

  /* --------------------
                  Error cases
     -------------------- */

  /* --------------------
                  Commands
     -------------------- */
  if (!has_arg(argv[1], "-?-?h(?:elp)?"))  // help command
  {
    std::cout << HELP_MSG;

    return 0;
  } else if (!has_arg(argv[1], "-?-?v(?:ersion)?"))  // version command
  {
    std::cout << VERSION << '\n';

    return 0;
  } else if (!std::strcmp(argv[1], "clean") &&
             !std::strcmp(argv[2], "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (remove_tree(clarbe_local_lib_path)) {
      std::cerr << "Something went wrong while cleaning local libraries\n";
      free(clarbe_local_lib_path);

      return 1;
    }
    free(clarbe_local_lib_path);

    return 0;
  } else if (!std::strcmp(argv[1], "clean")) {
    if (remove_tree("target")) {
      std::cerr << "Something went wrong while cleaning\n";

      return 1;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "check") &&
             !std::strcmp(argv[2], "--global")) {
    // also for integrity and version of local libs

    return 0;
  } else if (!std::strcmp(argv[1], "check")) {
    // check code for errors and warnings
    // also for integrity and version of libs

    return 0;
  } else if (!std::strcmp(argv[1], "run")) {
    if (create_dir("target") == 1) {
      // run existing code
    } else {
      goto compile_code;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "build") ||
             !std::strcmp(argv[1], "compile")) {
  compile_code:
    if (!path_exists("clarbe.toml")) {
      std::cerr << "No project file detected.\n";

      return 1;
    }

    auto local_config = toml::parse_file("clarbe.toml");

    create_dir("target");
    create_dir("target/object");
    create_dir("target/bin");
    create_dir((std::string(clarbe_env) + "/libs").c_str());

    install_libraries(local_config);

    std::optional<std::string> compiler =
        env_config_file["build"]["compiler"].value<std::string>();

    if (!compiler) {
      std::cerr << "Compiler not found or not a string.\n";

      return 1;
    }

    std::string include_arg("");

    if (auto inc_arr = local_config["local"]["includes"].as_array()) {
      for (const auto& include_dir : *inc_arr) {
        if (auto dir = include_dir.value<std::string>()) {
          include_arg += "-I \"" + *dir + "\" ";
        } else {
          std::cerr << "Include directory is not a string.\n";
        }
      }
    } else {
      std::cerr << "Includes not found or not an array.\n";
      return 1;
    }

    std::optional<std::string> pstd;

    if ((pstd = local_config["package"]["std"].value<std::string>())) {
      std::cout << "Compiling with standard " << *pstd << ".\n";
    } else {
      std::cerr
          << "C standard to use not defined correctly, defaulting to c17.\n";
      *pstd = "c17";
    }

    if (auto src_arr = local_config["local"]["sources"].as_array()) {
      for (const auto& source_dir : *src_arr) {
        if (auto dir = source_dir.value<std::string>()) {
          if (fs::exists(*dir) && fs::is_directory(*dir)) {
            for (const auto& source_file : fs::directory_iterator(*dir)) {
              std::string command(*compiler + "-stdlib=libc -std=" + *pstd +
                                  " " + include_arg + "-o target/object/" +
                                  source_file.path().filename().string() +
                                  ".o -c " + *dir + "/" +
                                  source_file.path().filename().string());
              std::system(command.c_str());
            }
          } else {
            std::cerr << "Directory does not exist: " << *dir << '\n';
          }
        } else {
          std::cerr << "Source directory is not a string.\n";
        }
      }
    } else {
      std::cerr << "Sources not found or not an array.\n";
      return 1;
    }

    if (std::optional<std::string> exe_name =
            local_config["package"]["name"].value<std::string>()) {
      std::system(std::string(*compiler + " -o \"target/bin/" + *exe_name +
                              "\" \"target/object/*.*.o\"")
                      .c_str());
    } else {
      std::cerr << "Name of the package not defined or not usable.\n";
      return 1;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "new")) {
    if (argc < 3) {
      std::cerr << "No project name defined.\nuse \"clarbe new "
                   "<project_name>\"\n";

      return 1;
    } else if (create_dir(argv[2]) == 1) {
      std::cerr << "Directory already exists.\n";

      return 1;
    }

    generate_new_content(argv[2]);

    return 0;
  } else if (!std::strcmp(argv[1], "init")) {
    if (argc < 3) {
      std::cerr << "No folder name defined.\nuse \"clarbe init <folder>\"\n";

      return 1;
    } else if (create_dir(argv[2]) != 1) {
      std::cerr << "Directory does not exist.\n";
      remove_tree(argv[2]);

      return 1;
    }

    generate_new_content(argv[2]);

    return 0;
  } else if (!std::strcmp(argv[1], "add") &&
             !std::strcmp(argv[2], "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>_<name>\n";
      free(clarbe_local_lib_path);

      return 1;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      free(clarbe_local_lib_path);

      return 1;
    }

    free(clarbe_local_lib_path);

    return 0;
  } else if (!std::strcmp(argv[1], "remove") &&
             !std::strcmp(argv[2], "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>_<name>\"\n";
      free(clarbe_local_lib_path);

      return 1;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      free(clarbe_local_lib_path);

      return 1;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "add")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>_<name>\n";

      return 1;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";

      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";

      return 1;
    }

    add_lib_to_toml(argv[3]);

    return 0;
  } else if (!std::strcmp(argv[1], "remove")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>_<name>\"\n";

      return 1;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";

      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";

      return 1;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "config") && !has_arg(argv, "--global")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";

      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";

      return 1;
    }

    return 0;
  } else if (!std::strcmp(argv[1], "config")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";

      return 1;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";

      return 1;
    }

    return 0;
  }

  std::cerr << "No valid arguments provided, try '-h' or '--help'\n";

  return 0;
}
