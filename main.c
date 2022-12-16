#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
 
int main(void)
{
  CURL * curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.lootlocker.io/server/session");

    struct curl_slist * chunk = NULL;
    chunk = curl_slist_append(chunk, "LL-Version: 2021-03-01");
    chunk = curl_slist_append(chunk, "x-server-key: dev_6bcd909878f544df81e4362908b1317a");
    chunk = curl_slist_append(chunk, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"game_version\": \"1.0.0.0\"}");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
  
    curl_easy_cleanup(curl);
  }

  return 0;
}
