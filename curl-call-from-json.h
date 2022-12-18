#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

/*
Returns the number of characters in a file, returns -1 if the file is invalid
*/
long getFileSize(FILE * file);

/*
Returns the stringified version of a JSON file, returns NULL if the filename is invalid
*/
char * JSONtoString(char * filename);

/*
Returns a list containing all the objects in the JSON element, returns NULL if failed
*/
struct curl_slist * objectToList(cJSON * object);

/*
Generates and executes a cURL call defined in a JSON file
*/
void curlCallFromJSON(char * filename);