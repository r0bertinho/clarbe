#include "args.hpp"
#include "regex.h"
#include <cstring>

/*
* is_flag(arg)
* 
* Checks if the provided argument is a flag, which is defined as starting with a '-'.
*/
bool is_flag( char* arg )
{
  return *arg == '-';
}

/*
* has_arg(argv, arg_r)
* 
* Checks if a specific argument exists in the provided input.
* Forgiving argument recognition.
*/
int has_arg( char* argv, char* arg_r )
{
  regex_t regex;
  int reti;
    
  reti = regcomp(&regex, arg_r, 0);
  if ( reti )
  {
    return 2; // Could not compile regex
  }
    
  reti = regexec(&regex, argv, 0, NULL, 0);

  if ( !reti )
  {
    return 0; // found
  } else
  if ( reti == REG_NOMATCH )
  {
    return 1; // not found
  } else
  {
    regerror(reti, &regex, argv, sizeof(argv));
    return 2; // Regex match failed
  }
  
  regfree(&regex);
  
  return 1;
}

/* just for good measure */
inline int has_arg( char** argv, char* arg_r )
{
  char string[64];
  altoc<64>(string, argv);
  return has_arg(string, arg_r);
}

template < size_t str_size = 64 >
inline void altoc(char out[str_size], char** argv)
{
  char full_str[str_size];
  int local = 0;
    
  for ( int i = 1; *(argv + i) != NULL; i++ )
  {
    for ( int j = 0; *(*(argv + i) + j) != NULL; j++ )
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
    
  std::strcpy(out, full_str);
}