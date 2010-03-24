#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
 
int main(int argc, char **argv)
{
  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  slist = curl_slist_append(slist, "RETS-Version: RETS/1.7.2");
  static const char *headerfilename = "headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "login.xml";
  FILE *bodyfile;
  
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();

  /* open the files */ 
  headerfile = fopen(headerfilename,"w");
  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
  bodyfile = fopen(bodyfilename,"w");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
 
  /* set URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/login");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist);

 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist);

  printf("Response Code: %d\n", res);

  return 0;
}

