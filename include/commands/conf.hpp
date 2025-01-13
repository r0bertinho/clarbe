#ifndef CONF_HPP
#define CONF_HPP

int add_lib_to_toml(const char *libname);
int add_lib_to_toml(const char *libname, char *version);
int take_lib_from_toml(const char *libname);

#include "conf.tpp"

#endif