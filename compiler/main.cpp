#include "consts.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{
#ifdef _WIN32
	if ( !_dupenv_s(&clarbe_env, &clarbe_env_s, "CLARBE_HOME") && clarbe_env != nullptr )
  { // no error
  } else
	{
		std::fprintf(stderr, "\'CLARBE_HOME\' environment variable not defined. closing...\n");
		goto exit_w_error;
	}
#endif

  goto exit_no_error;
exit_no_error:
  free(clarbe_env);
	return 0;
exit_w_error:
  free(clarbe_env);
	return 1;
}