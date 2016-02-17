#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <json.h>

#include "pocket.h"
#include "string.h"
#include "utils.h"

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) 
{
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);

    if (s->ptr == NULL) {
        die("realloc() failed");
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

char *create_request_petition(const char *key) 
{
    static char petition[1024];

    sprintf(
            petition,
            "{\"consumer_key\":\"%s\", \"redirect_uri\":\"%s\", \"state\":\"auth\"}",
            key, "pocketapp51314");
    return petition;
}

char *get_auth(const char *key, const char *token) 
{
    static char petition[512];

    sprintf(petition, "{\"consumer_key\":\"%s\", \"access_token\":\"%s\"}",
            key, token);

    return petition;
}

char *add_url(const char *key, const char *token, const char* url) 
{
    static char petition[1024];

    sprintf(petition, "{\"url\":\"%s\", \"consumer_key\":\"%s\", \"access_token\":\"%s\"}",
            url, key, token);

    return petition;
}

char *create_auth_petition(const char *key, const char *token) 
{
    static char petition[2048];

    sprintf(petition, "{\"consumer_key\":\"%s\", \"code\":\"%s\"}", key, token);

    return petition;
}

CURLcode request(const char *url, const char *params, struct string *result,
        int debug) 
{
    CURL *curl = curl_easy_init();
    CURLcode res = CURLE_FAILED_INIT;

    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, HDR_CONTENT_TYPE);
    headers = curl_slist_append(headers, HDR_X_ACCEPT);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);

        if (debug)
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return res;
}

int pocket_init(void) 
{ 
    return curl_global_init(CURL_GLOBAL_ALL); 
}

void pocket_clean(void) 
{ 
    curl_global_cleanup(); 
}

char *pocket_get_token(const char *key) 
{
    struct string s;
    json_object *response;
    char *token;

    string_init(&s);

    request(URL_REQUEST, create_request_petition(key), &s, 0);

    response = json_tokener_parse(s.ptr);
    json_object_object_get_ex(response, "code", &response);
    token = (char *)json_object_get_string(response);

    free(response);
    string_cleanup(&s);

    return token;
}

char *pocket_auth(const char *key, const char *token)
{ 
    struct string s;
    json_object *response;
    char* access_token;

    string_init(&s);

    request(URL_AUTHORIZE, create_auth_petition(key, token), &s, 0);

    response = json_tokener_parse(s.ptr);
    json_object_object_get_ex(response, "access_token", &response);
    access_token = (char *)json_object_get_string(response);

    free(response);
    string_cleanup(&s);

    return access_token;
}

void pocket_add(const char *key, const char *token, const char* url) 
{
    struct string s;

    string_init(&s);
    request(URL_ADD, add_url(key, token, url), &s, 0);
    string_cleanup(&s);
}


void pocket_get(const char *key, const char *token) 
{
    struct string s;

    string_init(&s);
    request(URL_GET, get_auth(key, token), &s, 0);
    string_cleanup(&s);
}
