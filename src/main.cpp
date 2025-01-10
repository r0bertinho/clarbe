#include <cstring>
#include <iostream>

#include "args.hpp"
#include "commands/files.hpp"
#include "consts.hpp"
#include "messages.h"

int main(int argc, char **argv) {
#ifdef _WIN32
  if (!_dupenv_s(&clarbe_env, &clarbe_env_s, "CLARBE_HOME") &&
      clarbe_env != nullptr) {  // no error
  } else {
    std::cout
        << "\'CLARBE_HOME\' environment variable not defined. closing...\n";
    goto exit_w_error;
  }
#endif

  /* --------------------
                  Error cases
     -------------------- */

  /* --------------------
                  Commands
     -------------------- */
  if (!has_arg(argv[1], "-?-?h(?:elp)?"))  // help command
  {
    std::cout << HELP_MSG;
    goto exit_no_error;
  } else if (!has_arg(argv[1], "-?-?v(?:ersion)?"))  // version command
  {
    std::cout << VERSION << '\n';
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "clean") &&
             !std::strcmp(argv[2], "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (remove_tree(clarbe_local_lib_path)) {
      std::cerr << "Something went wrong while cleaning local libraries\n";
      goto exit_w_error;
    }
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "clean")) {
    if (remove_tree("target")) {
      std::cerr << "Something went wrong while cleaning\n";
      goto exit_w_error;
    }
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "check") &&
             !std::strcmp(argv[2], "--global")) {
    // also for integrity and version of local libs
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "check")) {
    // check code for errors and warnings
    // also for integrity and version of libs
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "run")) {
    if (create_dir("target") == 1) {
      // run existing code
    } else {
      goto compile_code;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "build") ||
             !std::strcmp(argv[1], "compile")) {
  compile_code:
    if (!path_exists("clarbe.toml")) {
      std::cerr << "No project file detected.\n";
      goto exit_w_error;
    }

    create_dir("target");
    create_dir("target/object");
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "new")) {
    if (argc < 3) {
      std::cerr << "No project name defined.\nuse \"clarbe new "
                   "<project_name>\"\n";
      goto exit_w_error;
    } else if (create_dir(argv[2]) == 1) {
      std::cerr << "Directory already exists.\n";
      goto exit_w_error;
    }

    generate_new_content(argv[2]);
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "init")) {
    if (argc < 3) {
      std::cerr << "No folder name defined.\nuse \"clarbe init <folder>\"\n";
      goto exit_w_error;
    } else if (create_dir(argv[2]) != 1) {
      std::cerr << "Directory does not exist.\n";
      remove_tree(argv[2]);
      goto exit_w_error;
    }

    generate_new_content(argv[2]);
    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "add") && !has_arg(argv, "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\n";
      goto exit_w_error;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "remove") && !has_arg(argv, "--global")) {
    get_local_lib_path(clarbe_local_lib_path);

    if (argc < 4) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\"\n";
      goto exit_w_error;
    } else if (argc > 4) {
      std::cerr << "too many arguments.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "add")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\n";
      goto exit_w_error;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";
      goto exit_w_error;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "remove")) {
    if (argc < 3) {
      std::cerr << "Not enough arguments.\ndefine the "
                   "<creator>/<dependency-name>\"\n";
      goto exit_w_error;
    } else if (argc > 3) {
      std::cerr << "too many arguments.\n";
      goto exit_w_error;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "config") && !has_arg(argv, "--global")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";
      goto exit_w_error;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  } else if (!std::strcmp(argv[1], "config")) {
    if (argc < 4) {
      std::cerr << "Not enough arguments provided.\n"
                << "use \"clarbe config <configuration> [values]\"\n";
      goto exit_w_error;
    } else if (!path_exists("clarbe.toml")) {
      std::cerr << "Config file not found.\n";
      goto exit_w_error;
    }

    goto exit_no_error;
  }

  std::cerr << "No valid arguments provided, try '-h' or '--help'\n";
  goto exit_no_error;
exit_no_error:
  free(clarbe_env);
  return 0;
exit_w_error:
  free(clarbe_env);
  return 1;
}
