#ifndef LIBS_HPP
#define LIBS_HPP

#include "toml.hpp"

size_t write_callback(void *contents, size_t size, size_t nmemb, char **userp);
void get_latest_tag(char *out, const char *libname);
int install_libraries(toml::parse_result &local_config);

#include "libs.tpp"

#endif