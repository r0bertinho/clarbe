#ifndef CONSTS_HPP
#define CONSTS_HPP

char* clarbe_env = std::getenv("CLARBE_HOME");

#define get_local_lib_path(varname)                                            \
  char* varname =                                                              \
      (char*)calloc(sizeof(clarbe_env) + sizeof("/local_libs"), sizeof(char)); \
  strcat(varname, clarbe_env);                                                 \
  strcat(varname, "/local_libs")

#endif