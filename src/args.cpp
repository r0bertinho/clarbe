#include "args.hpp"

#include <cstring>
#include <iostream>
#include <regex>

/*
 * Checks if a specific argument exists in the provided input.
 * Forgiving argument recognition.
 */
int has_arg(char *argv_, const char *arg_r) {
  std::regex regex(arg_r, std::regex_constants::optimize);

  try {
    if (std::regex_search(argv_, regex)) {
      return 0;
    }
  } catch (...) {
    return 2;
  }

  return 1;
}

int has_arg(char **argv_, const char *arg_r) {
  char *string = nullptr;
  altoc(string, argv_);

  std::regex regex(arg_r, std::regex_constants::optimize);

  try {
    if (std::regex_search(string, regex)) {
      return 0;
    }
  } catch (...) {
    return 2;
  }

  return 1;
}

/*
  transcribes a list of strings into a single string;
  be sure to set the size of out n' in -put correctly
*/
void altoc(char out[], char **argv) {
  size_t fs = 0;

  for (int n = 0; *(argv + n) != NULL; n++) {
    fs += strlen(*(argv + n)) + 1;
  }

  char *full_str = (char *)calloc(fs, sizeof(char));

  int local = 0;

  for (int i = 1 /* argv[0] is name of file */; *(argv + i) != NULL; i++) {
    for (int j = 0; *(*(argv + i) + j) != '\0'; j++) {
      full_str[local] = *(*(argv + i) + j);
      local++;
    }

    if (*(argv + i) == NULL)
      full_str[local] = '\0';
    else {
      full_str[local] = ' ';
      local++;
    }
  }

  out = (char *)realloc(out, strlen(full_str) * sizeof(char));
  strcpy(out, full_str);
  free(full_str);
}