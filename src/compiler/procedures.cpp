#include "compiler/procedures.hpp"
#include "curl/curl.h"
#include "args.hpp"
#include <iostream>

/*
* optimization levels
*/
namespace opt {
  int O0()
  {
    return 0;
  }
  
  int O1()
  {
    return 0;
  }
  
  int O2()
  {
    return 0;
  }
}

/*
* assumes the directory it is being ran on
* has a 'clarbe.toml' file
* 
* transform source code files into binaries.
* does not allow:
* - preprocessors;
* - deducted principles;
* 
* it assumes all source code files are
* interdependent and coexist as full source code.
*
* error codes:
* - 0: no errors occured;
* - 1: optimization error;
*/
int compile_all( char** flags )
{
  int (*opt_level)();
  
  opt_level = &opt::O0;
  if ( !has_arg<128>(flags, "-?-(?:O=?|[Oo]ptimization=)0") ) // O0
  {
    opt_level = &opt::O0;
  } else
  if ( !has_arg<128>(flags, "-?-(?:O=?|[Oo]ptimization=)1") ) // O1
  {
    opt_level = &opt::O1;
  } else
  if ( !has_arg<128>(flags, "-?-(?:O=?|[Oo]ptimization=)2") ) // O2
  {
    opt_level = &opt::O2;
  } else
  {
    std::cerr
    << "optimization level non-existant or not recognized;" << '\n'
    << "using default \"-O0\"" << '\n';
  }
  
  return 0;
}