#include "args.hpp"

#include <regex>
#include <iostream>
#include <cstring>

/*
* has_arg(argv, arg_r)
* 
* Checks if a specific argument exists in the provided input.
* Forgiving argument recognition.
*/
int has_arg( char* argv_, const char* arg_r )
{
  std::regex regex(arg_r);
  
  try
  {
    if ( std::regex_search(argv_, regex) )
    {
      return 0;
    }
  } catch ( ... )
  {
    return 2;
  }
  
  return 1;
}

int has_arg( char** argv_, const char* arg_r )
{
  char* string;
  altoc(string, argv_);
  
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
void altoc( char out[], char** argv )
{
  size_t fs = 0;

  for (int n = 0; *(argv + n) != NULL; n++)
  {
    fs += sizeof(*(argv + n)) + 1;
  }

  char full_str[1];

  realloc(full_str, fs);

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
  
  realloc(out, sizeof(full_str));
  strcpy(out, full_str);
  free(full_str);
}