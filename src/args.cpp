#include "args.hpp"

/*
* has_arg(argv, arg_r)
* 
* Checks if a specific argument exists in the provided input.
* Forgiving argument recognition.
*/
int has_arg( char* argv_, const char* arg_r )
{
#ifdef use_c_regex
  regex_t regex;
  int reti;
    
  reti = regcomp(&regex, arg_r, 0);
  if ( reti )
  {
    return 2; // Could not compile regex
  }
    
  reti = regexec(&regex, argv_, 0, NULL, 0);

  if ( !reti )
  {
    return 0; // found
  } else
  if ( reti == REG_NOMATCH )
  {
    return 1; // not found
  } else
  {
    regerror(reti, &regex, argv_, sizeof(argv_));
    return 2; // Regex match failed
  }
  
  regfree(&regex);
#else
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
#endif
  
  return 1;
}