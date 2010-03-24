#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "curl/curl.h"
#include <curl/types.h>
#include <curl/easy.h>

jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  slist = curl_slist_append(slist, "RETS-Version: RETS/1.7.2");
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "data/data/com.banandroid.curlretsjni/login.xml";
  FILE *bodyfile;
  
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();

  /* open the files */ 
  headerfile = fopen(headerfilename,"w");
  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return (*env)->NewStringUTF(env, "file error");
  }
  bodyfile = fopen(bodyfilename,"w");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return (*env)->NewStringUTF(env, "file error");
  }
 
  /* set URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
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



    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[4096];
    FILE * myfile;
	
    myfile = fopen("data/data/com.banandroid.curlretsjni/login.xml","r");
	
    while (!feof(myfile))
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }
	
    fclose(myfile);

  sprintf(buffer,"Response code: %i\n",res);

  return (*env)->NewStringUTF(env, strcat(buffer,fbuffer));

}

jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI2( JNIEnv* env,
                                                  jobject thiz )
{
  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "metadata.xml";
  FILE *bodyfile;

  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();

  /* set up the data / http headers list */
  slist = curl_slist_append(slist, "RETS-Version: RETS/1.7.2");

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
 
  /* set options */ 
  curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, "Type=METADATA-SYSTEM&ID=*&Format=COMPACT");

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/getMetadata");
 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[4096];
    FILE * myfile;
    int chunks = 0;

    myfile = fopen("data/data/com.banandroid.curlretsjni/metadata.xml","r");

    while (!feof(myfile) && chunks < 15)
    {
	chunks++;
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);

  sprintf(buffer,"Response code: %i\n",res);

  return (*env)->NewStringUTF(env, strcat(buffer,fbuffer));


}

