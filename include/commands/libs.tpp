#include <iostream>

#include "curl/curl.h"
#include "libs.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

/* for later

// Callback function to write the response data
size_t write_callback(void *contents, size_t size, size_t nmemb, char **userp) {
  size_t totalSize = size * nmemb;
  // Reallocate memory to hold the new data
  *userp = (char *)realloc(*userp, totalSize + 1);
  if (*userp == NULL) {
    std::cerr << "Failed to allocate memory." << std::endl;
    return 0;  // Return 0 to indicate failure
  }

  memcpy(*userp, contents, totalSize);
  (*userp)[totalSize] = '\0';  // Null-terminate the string
  return totalSize;
}


// Function to get the latest tag from a GitHub repository
void get_latest_tag(char *out, const char *libname) {
  // Split the input string into owner and repo
  char *owner = nullptr;
  char *repo = nullptr;
  char *libname_copy =
      strdup(libname);  // Duplicate the input string for manipulation

  char *pos = strchr(libname_copy, '/');
  if (pos == NULL) {
    std::cerr << "Invalid format. Use <owner>/<repo>." << std::endl;
    free(libname_copy);

    realloc(out, sizeof("N/A"));
    strcpy(out, "N/A");
    return;
  }

  *pos = '\0';           // Split the string
  owner = libname_copy;  // Owner is the first part
  repo = pos + 1;        // Repo is the second part

  CURL *curl;
  CURLcode res;
  char *readBuffer = nullptr;  // Buffer to hold the response

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    char url[256];  // Buffer for the URL
    snprintf(url, sizeof(url), "https://api.github.com/repos/%s/%s/tags", owner,
             repo);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "libcurl-agent/1.0");  // GitHub API requires a user agent

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
      curl_easy_cleanup(curl);
      curl_global_cleanup();
      free(libname_copy);

      realloc(out, sizeof("N/A"));
      strcpy(out, "N/A");
      return;
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  // Parse the JSON response using RapidJSON
  rapidjson::Document document;
  if (document.Parse(readBuffer).HasParseError()) {
    std::cerr << "Failed to parse JSON: "
              << rapidjson::GetParseError_En(document.GetParseError())
              << std::endl;
    free(readBuffer);
    free(libname_copy);

    realloc(out, sizeof("N/A"));
    strcpy(out, "N/A");
    return;
  }

  // Check if there are any tags
  char *result = strdup("N/A");  // Default result
  if (document.IsArray() && document.Size() > 0) {
    const char *latestTag = document[0]["name"].GetString();
    result = strdup(latestTag);
  }

  // Clean up
  free(readBuffer);
  free(libname_copy);

  realloc(out, sizeof(result));
  strcpy(out, result);
}

*/

int install_to_global_libs(char *lib) { return 0; }

int install_to_global_libs(char *lib, char *version) { return 0; }

int remove_from_global_libs(char *lib) { return 0; }

int remove_from_global_libs(char *lib, char *version) { return 0; }