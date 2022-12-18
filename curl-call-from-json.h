#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

long getFileSize(FILE * file);
char * JSONtoString(char * file);
struct curl_slist * objectToList(cJSON * object);
void curlCallFromJSON(char * filename);