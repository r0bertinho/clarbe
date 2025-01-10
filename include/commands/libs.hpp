#ifndef LIBS_HPP
#define LIBS_HPP

size_t write_callback(void *contents, size_t size, size_t nmemb, char **userp);

void get_latest_tag(char *out, const char *libname);

#import "libs.tpp"

#endif