#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <print>

namespace fs = std::filesystem;

void add_content_to_folder(const std::string& path);

extern "C" __declspec(dllexport) int proc(const std::vector<std::string>& args) {
  if (!fs::is_empty(fs::current_path())) {
    std::println("Current directory is not empty.");
    return 0;
  }

  add_content_to_folder(fs::current_path().generic_string());

  return 0;
}

void add_content_to_folder(const std::string& path) {
  fs::create_directory(path + "/src");
  fs::create_directory(path + "/inc");

  std::ofstream source_file(path + "/src/main.c");
  source_file << "#include <stdio.h>" << '\n'
              << '\n'
              << "int main(int argc, char **argv) {" << '\n'
              << "  fprintf(stdout, \"Hello world!\");" << '\n'
              << "  return 0;" << '\n'
              << "}" << '\n';
  source_file.flush();
  source_file.close();

  std::ofstream config_file(path + "/clarbe.toml");
  config_file << "[package]" << '\n'
              << "name = \"" << path << "\"" << '\n'
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
}