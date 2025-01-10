#ifndef ARGS_HPP
#define ARGS_HPP

int has_arg(char *argv_, const char *arg_r);
int has_arg(char **argv_, const char *arg_r);
void altoc(char out[], char **argv);

#include "args.tpp"

#endif