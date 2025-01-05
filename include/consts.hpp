#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <cstdlib>

#ifdef _WIN32
char* clarbe_env;
size_t clarbe_env_s = 0;
#else
char* clarbe_env = std::getenv("CLARBE_HOME");
#endif

#define get_local_lib_path(varname) char varname[sizeof(clarbe_env) + sizeof("\\local_libs")];\
                                    strcat_s(varname, sizeof(varname), clarbe_env);\
                                    strcat_s(varname, sizeof(varname), "\\local_libs")

#endif