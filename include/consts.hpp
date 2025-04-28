#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <string>

const char* getenv_or(const char* env, const char* err) noexcept {
  char* tmp;
  return (tmp = std::getenv(env)) != NULL ? tmp : err;
}

const std::string clarbe_env(getenv_or("CLARBE_HOME", "null"));

#endif