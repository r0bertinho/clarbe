#ifndef CMD_TEMPLATE_HPP
#define CMD_TEMPLATE_HPP

#include <string>
#include <vector>

#define EXPORT_FN extern "C" __declspec(dllexport)
#define MAIN_FUNC EXPORT_FN int proc
typedef std::vector<std::string> args_t;

#endif