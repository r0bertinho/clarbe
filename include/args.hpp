#ifndef ARGS_HPP
#define ARGS_HPP

#include <regex>
#include <iostream>
#include <cstring>

int has_arg( char* argv_, const char* arg_r );

template < size_t str_size >
int has_arg( char** argv_, const char* arg_r )
{
  char string[str_size];
  altoc<str_size>(string, argv_);
  
  std::regex regex(arg_r);
    
  try
  {
    if ( std::regex_search(string, regex) )
    {
      return 0;
    }
  } catch ( ... )
  {
    return 2;
  }

  return 1;
}

/*
  transcribes a list of strings into a single string;
  be sure to set the size of out n' in -put correctly
*/
template < size_t str_size > // I love mixing C libs with C++ stuff!
void altoc( char out[str_size], char** argv )
{
  char full_str[str_size];
  int local = 0;
  
  for ( int i = 1 /* argv[0] is name of file */; *(argv + i) != NULL; i++ )
  {
    for ( int j = 0; *(*(argv + i) + j) != '\0'; j++ )
    {
      full_str[local] = *(*(argv + i) + j);
      local++;
    }
        
    if ( *(argv + i) == NULL )
      full_str[local] = '\0';
    else
    {
      full_str[local] = ' ';
      local++;
    }
  }
  
  #ifdef _WIN32
  strcpy_s(out, str_size, full_str);
  #else
  std::strcpy(out, full_str);
  #endif
}

#endif
