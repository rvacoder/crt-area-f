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
    char *fbuffer[1024];
    FILE * myfile;

    strcpy(buffer,"");
    strcpy(fbuffer,"");
    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);
	
    myfile = fopen("data/data/com.banandroid.curlretsjni/login.xml","r");

    while (!feof(myfile))
    {
        fgets(fbufferchunk,256,myfile);	
	strcat(fbuffer, fbufferchunk);
    }
	
    fclose(myfile);

  return (*env)->NewStringUTF(env, fbuffer);

}


jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI2( JNIEnv* env,
                                                  jobject thiz )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "data/data/com.banandroid.curlretsjni/metadata.xml";
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
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
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
    char *fbuffer[15360];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);
    myfile = fopen("data/data/com.banandroid.curlretsjni/metadata.xml","r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 200)
    {
        fgets(fbufferchunk,256,myfile);
	strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);

  return (*env)->NewStringUTF(env, fbuffer);


}


jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI3( JNIEnv* env,
                                                  jobject thiz )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "data/data/com.banandroid.curlretsjni/search.xml";
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
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, "Format=COMPACT&SearchType=Property&Class=RES&StandardNames=0&QueryType=DMQL2&Query=(ListPrice=500000-)");

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/search");
 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

  printf("Response Code: %d\n", res);
    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[15360];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);

    myfile = fopen("data/data/com.banandroid.curlretsjni/search.xml","r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 200)
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);

  return (*env)->NewStringUTF(env, fbuffer);

}


jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI5( JNIEnv* env,
                                                  jobject thiz )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "data/data/com.banandroid.curlretsjni/logout.xml";
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
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/logout");
 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

  printf("Response Code: %d\n", res);
    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[1024];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);

    myfile = fopen("data/data/com.banandroid.curlretsjni/logout.xml","r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 4)
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);

  return (*env)->NewStringUTF(env, fbuffer);

}

jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNIFOUR( JNIEnv* env,
                                                  jobject thiz, int id )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  char fn1[150] = "data/data/com.banandroid.curlretsjni/photo";
  char fn2[150];
  char fn3[10] = ".jpg";
  sprintf(fn2, "%s%d%s", fn1, id, fn3);
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
  bodyfile = fopen(fn2,"w");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
 
  /* set options */ 
  curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

  char str1[50] = "Resource=Property&Type=Photo&Location=0&ID=";
  char str2[50];
  sprintf(str2, "%s%d", str1, id);
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, str2);

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/getObject");
 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

  printf("Response Code: %d\n", res);
    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[1024];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);

    myfile = fopen("data/data/com.banandroid.curlretsjni/photo.jpg","r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 4)
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);
  return (*env)->NewStringUTF(env, "If I return the actual photo as string VM will take exception");

}

jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI4( JNIEnv* env,
                                                  jobject thiz, int id )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  char fn1[150] = "data/data/com.banandroid.curlretsjni/photo";
  char fn2[150];
  char fn3[10] = ".jpg";
  sprintf(fn2, "%s%d%s", fn1, id, fn3);
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
  bodyfile = fopen(fn2,"w");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }

  curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

  char str1[50] = "Resource=Property&Type=Photo&Location=0&ID=";
  char str2[50];
  sprintf(str2, "%s%d", str1, id);
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, str2);

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/getObject");
 
  CURLcode res = curl_easy_perform(curl_handle);
 
  fclose(headerfile);
  fclose(bodyfile);
 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

  printf("Response Code: %d\n", res);
    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[1024];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);

    myfile = fopen(fn2,"r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 4)
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);
  return (*env)->NewStringUTF(env, "If I return the actual photo as string VM will take exception");

}

jstring
Java_com_banandroid_curlretsjni_curlretsjni_stringFromJNI6( JNIEnv* env,
                                                  jobject thiz, int id )
{

  CURL *curl_handle;
  struct curl_slist *slist=NULL;
  static const char *headerfilename = "data/data/com.banandroid.curlretsjni/headers.txt";
  FILE *headerfile;
  static const char *bodyfilename = "data/data/com.banandroid.curlretsjni/search.xml";
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
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
  curl_easy_setopt(curl_handle, CURLOPT_USERNAME, "Joe");
  curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, "Schmoe");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "curlcbot/0.1");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist); 
  
  curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, "data/data/com.banandroid.curlretsjni/cookies.txt");
  curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
  
  char str1[150] = "Format=COMPACT&SearchType=Property&Class=RES&StandardNames=0&QueryType=DMQL2&Query=(ListingID=";
  char str2[150];
  sprintf(str2, "%s%d)", str1, id);
  curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, str2);

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://demo.crt.realtors.org:6103/rets/search");
 
  /* get it! */ 
  CURLcode res = curl_easy_perform(curl_handle);
 
  /* close the header file */ 
  fclose(headerfile);
  fclose(bodyfile);
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(slist); 

  printf("Response Code: %d\n", res);
    char *buffer[25];
    char *fbufferchunk[256];
    char *fbuffer[15360];

    strcpy(buffer,"");
    strcpy(fbufferchunk,"");
    strcpy(fbuffer,"");

    FILE * myfile;
    int chunks = 0;

    sprintf(buffer,"Response code: %i\n",res);
    strcat(fbuffer,buffer);

    myfile = fopen("data/data/com.banandroid.curlretsjni/search.xml","r");

    if(myfile==NULL)
    {
       curl_easy_cleanup(curl_handle);
       return (*env)->NewStringUTF(env, "file problem");
    }

    int reads = 0;
    while (!feof(myfile) && reads++ < 200)
    {
        fgets(fbufferchunk,256,myfile);
        strcat(fbuffer,fbufferchunk);
    }

    fclose(myfile);

  return (*env)->NewStringUTF(env, fbuffer);

}
