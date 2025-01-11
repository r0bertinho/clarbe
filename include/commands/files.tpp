#include <cstring>
#include <filesystem>
#include <fstream>

#include "files.hpp"

/*
 * remove_tree(path)
 *
 * Recursively removes a directory and all its contents.
 *
 * Usage: Call this function with the path of the directory to be removed.
 * Returns 0 on success, or 1 if an error occurs.
 */
int remove_tree(const char* path) {
  std::error_code errorCode;

  if (!std::filesystem::remove_all(path, errorCode)) {
    return 1;
  }

  return 0;
}

/*
 * create_dir(path)
 *
 * Creates a directory at the specified path if it does not already exist.
 *
 * Usage: Call this function with the desired directory path. Returns 0 on
 * success, or 1 if the directory already exists.
 */
int create_dir(const char path[]) {
  return !std::filesystem::create_directory(path);
}

/*
 * generate_new_content(folder_path)
 *
 * Generates a new project structure in the specified folder, including a
 * configuration file and source files.
 *
 * Usage: Call this function with the path of the folder where the project
 * should be created. Returns 0 on success, 1 if the folder does not exist, 2
 * if there was an error opening files.
 */
int generate_new_content(const char* folder_path) {
  char* config_file_path =
      new char[sizeof(folder_path) + sizeof(".//clarbe.toml")];
  strcpy(config_file_path, "./");
  strcat(config_file_path, folder_path);
  strcat(config_file_path, "/clarbe.toml");
  std::fstream config_file;
  config_file.open(config_file_path, std::fstream::out);

  strcpy(config_file_path, "./");
  strcat(config_file_path, folder_path);
  strcat(config_file_path, "/src");
  // create source directory before freeing
  if (create_dir(config_file_path)) {
    delete[] config_file_path;
    config_file.close();
    return 1;
  }

  delete[] config_file_path;

  if (!config_file.is_open()) {
    return 2;
  }

  config_file << "[package]" << '\n'
              << "name = \"" << folder_path << "\"" << '\n'
              << "std = \"c99\"" << '\n'
              << "build_type = \"executable\"" << '\n'
              << "version = \"0.0.1\"" << '\n'
              << '\n'
              << "[locals]" << '\n'
              << "sources = [\"src\"]" << '\n'
              << "includes = [\"include\"]" << '\n'
              << '\n'
              << "[uses]" << '\n'
              << "macro_file = \"false\"" << '\n'
              << "build_file = \"false\"" << '\n'
              << '\n'
              << "[dependencies]" << '\n'
              << "stdio = \"latest\"" << '\n';

  config_file.flush();
  config_file.close();

  char* source_file_path =
      new char[sizeof(folder_path) + sizeof(".//src/main.c")];
  strcpy(source_file_path, "./");
  strcat(source_file_path, folder_path);
  strcat(source_file_path, "/src/main.c");

  std::fstream source_file;
  source_file.open(source_file_path, std::fstream::out);

  delete[] source_file_path;

  if (!source_file.is_open()) {
    return 3;
  }

  source_file << "#include <stdio.h>" << '\n'
              << '\n'
              << "int main(int argc, char **argv) {" << '\n'
              << "  fprintf(stdout, \"Hello world!\");" << '\n'
              << "  return 0;" << '\n'
              << "}" << '\n';

  config_file.flush();
  source_file.close();

  char* include_folder_path =
      new char[sizeof(folder_path) + sizeof(".//include")];
  strcpy(include_folder_path, "./");
  strcat(include_folder_path, folder_path);
  strcat(include_folder_path, "/include");

  if (create_dir(include_folder_path)) {
    delete[] include_folder_path;
    return 4;
  }

  delete[] include_folder_path;
  return 0;
}

/*
 * file_exists(file_name)
 *
 * Checks if a file exists at the specified file name.
 *
 * Usage: Call this function with the file name to check. Returns 1 if the file
 * exists, or 0 if it does not.
 */
bool path_exists(const char* path_name) {
  if (!std::filesystem::exists(path_name)) {
    return false;
  }

  return true;
}