#ifndef ARGS_HPP
#define ARGS_HPP

bool is_flag( char* arg );
int has_arg( char* argv, char* arg_r );
inline int has_arg( char** argv, char* arg_r );
template < size_t str_size = 64 > inline void altoc( char out[str_size], char** argv );

#endif
