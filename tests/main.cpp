#define CATCH_CONFIG_RUNNER
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "args.hpp"
#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "commands/conf.hpp"
#include "commands/files.hpp"
#include "commands/libs.hpp"

// Args

TEST_CASE("args.hpp/has_arg", "[int has_arg(char*, char*)]") {
  REQUIRE(has_arg(strdup("clarbe build -O3"), strdup("-?-?b(?:uild)?")) == 0);
  REQUIRE(has_arg(strdup("clarbe help build"),
                  strdup("-?-?h(?:elp)? +build")) == 0);
}

TEST_CASE("args.hpp/has_arg", "[int has_arg(char**, char*)]") {
  char* arr1[] = {strdup("clarbe"), strdup("build"), strdup("-O3")};
  REQUIRE(has_arg(arr1, strdup("-?-?b(?:uild)?")) == 0);
  char* arr2[] = {strdup("clarbe"), strdup("help"), strdup("build")};
  REQUIRE(has_arg(arr2, strdup("-?-?h(?:elp)? +build")) == 0);
}

TEST_CASE("args.hpp/altoc", "[void altoc(char*, char**)]") {
  char* output = (char*)malloc(1);
  char* arr1[] = {strdup("clarbe"), strdup("build"), strdup("-O3")};
  altoc(output, arr1);
  REQUIRE(strcmp(output, "clarbe build -O3") == 0);
  char* arr2[] = {strdup("clarbe"), strdup("help"), strdup("build")};
  altoc(output, arr2);
  REQUIRE(strcmp(output, strdup("clarbe help build")) == 0);
  free(output);
}

// Conf

TEST_CASE("conf.hpp/add_lib_to_toml", "[int add_lib_to_toml(const char*)]") {
  std::fstream toml_file("clarbe.toml");
  toml_file << "[package]" << '\n'
            << "name = \"" << "unit-test" << "\"" << '\n'
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
  toml_file.flush();
  toml_file.close();

  REQUIRE(add_lib_to_toml("catchorg_Catch2") == 0);
}

TEST_CASE("conf.hpp/add_lib_to_toml",
          "[int add_lib_to_toml(const char*, char*)]") {
  REQUIRE(add_lib_to_toml(strdup("catchorg_Clara"), strdup("v1.1.5")) == 0);
}

TEST_CASE("conf.hpp/take_lib_from_toml",
          "[int take_lib_from_toml(const char*)]") {
  REQUIRE(take_lib_from_toml(strdup("catchorg_Clara")) == 0);
}

// Files

TEST_CASE("files.hpp/create_dir", "[int create_dir(const char*)]") {
  REQUIRE(create_dir("temp_dir") == 0);
}

TEST_CASE("files.hpp/generate_new_content",
          "[int generate_new_content(const char*)]") {
  REQUIRE(generate_new_content("temp_dir") == 0);
}

TEST_CASE("files.hpp/path_exists", "[int path_exists(const char*)]") {
  REQUIRE(path_exists("temp_dir"));
}

TEST_CASE("files.hpp/remove_tree", "[int remove_tree(const char*)]") {
  REQUIRE(remove_tree("temp_dir") == 0);
}

// Libs

TEST_CASE("libs.hpp/install_libraries",
          "[int install_libraries(toml::parse_result&)]") {
  toml::parse_result toml_file = toml::parse_file("clarbe.toml");
  // Later
}

TEST_CASE("libs.hpp/get_latest_tag",
          "[int get_latest_tag(char*, const char*)]") {
  char* output = (char*)malloc(1);
  get_latest_tag(output, "catchorg_Catch2");
  // Later
  free(output);
}

TEST_CASE("libs.hpp/write_callback",
          "[int write_callback(void*, size_t, size_t, char**)]") {
  // Later
}

int main(int argc, char** argv) {
  const int retval = Catch::Session().run(argc, argv);
  return retval;
}