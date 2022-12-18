#include "curl-call-from-json.h"

long getFileSize(FILE * file){
  if(file == NULL)
    return -1;

  unsigned long position = ftell(file);

  fseek(file, 0, SEEK_END);

  long fileSize = ftell(file);

  fseek(file, position, SEEK_SET);

  return fileSize;
}

char * JSONtoString(char * filename){
  FILE * json = fopen(filename, "r");

  if(!json)
    return NULL;

  long fileSize = getFileSize(json);

  char * string = malloc(fileSize + 1); // +1 for space for terminating character

  if(!string){
    fclose(json);
    return NULL;
  }
    
  int position;

  for(position = 0; position < fileSize; position++)
    string[position] = fgetc(json);

  string[position] = '\0';

  fclose(json);

  return string;
}

struct curl_slist * objectToList(cJSON * object){
  if(!object)
    return NULL;

  struct curl_slist * chunk = NULL;

  cJSON * child = object->child;

  while(child){
    char * stringToPass = malloc(strlen(child->string) + strlen(": ") + strlen(child->valuestring) + 1);
    
    if(!stringToPass)
      return NULL;

    stringToPass[0] = '\0';
    strcat(strcat(strcat(stringToPass, child->string), ": "), child->valuestring);
    chunk = curl_slist_append(chunk, stringToPass);

    free(stringToPass);

    child = child->next;
  }

  return chunk;
}

void curlCallFromJSON(char * filename){
  char * string = JSONtoString(filename);
  
  cJSON * json = cJSON_Parse(string);

  free(string);

  curl_global_init(CURL_GLOBAL_DEFAULT);

  CURL * curl = curl_easy_init();

  if(!curl) return;

  curl_easy_setopt(curl, CURLOPT_URL, cJSON_GetObjectItem(json, "url")->valuestring);

  cJSON * headerObject = cJSON_GetObjectItem(json, "header");

  struct curl_slist * headerChunk = objectToList(headerObject);

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerChunk);

  char * dataString = cJSON_Print(cJSON_GetObjectItem(json, "data"));
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataString);

  curl_easy_perform(curl);

  free(dataString);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  cJSON_Delete(json);
  curl_slist_free_all(headerChunk);
}
