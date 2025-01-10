#ifndef CONSTS_HPP
#define CONSTS_HPP

char* clarbe_env = std::getenv("CLARBE_HOME");

#define get_local_lib_path(varname)                                     \
  char* varname = new char[sizeof(clarbe_env) + sizeof("/local_libs")]; \
  strcat(varname, clarbe_env);                                          \
  strcat(varname, "/local_libs")

#endif