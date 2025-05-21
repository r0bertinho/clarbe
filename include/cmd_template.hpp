#ifndef CMD_TEMPLATE_HPP
#define CMD_TEMPLATE_HPP

#include <string>
#include <vector>

// Define a macro for exporting functions based on the platform
#if defined(_WIN32)
#define EXPORT_FN extern "C" __declspec(dllexport)
#else
#define EXPORT_FN extern "C"
#endif

#define MAIN_FUNC EXPORT_FN int proc
#define HELP_FUNC EXPORT_FN std::string fhelp
typedef std::vector<std::string> args_t;

#endif // CMD_TEMPLATE_HPP
