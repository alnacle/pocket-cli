#ifndef __POCKET_H__
#define __POCKET_H__

/* URL to be called when the authorization process has been completed */
#define REDIRECT_URI "https://github.com/anavarro/pocket-cli"

#define POCKET_URL    "https://getpocket.com"
#define POCKET_VER    "/v3"

/* Pocket API */
#define URL_REQUEST   POCKET_URL POCKET_VER "/oauth/request"
#define URL_AUTHORIZE POCKET_URL POCKET_VER "/oauth/authorize"
#define URL_GET       POCKET_URL POCKET_VER "/get"
#define URL_ADD       POCKET_URL POCKET_VER "/add"

/* authorize application's request token */
#define URL_AUTH      POCKET_URL "/auth/authorize"

/* use JSON for the requests */
#define HDR_CONTENT_TYPE "Content-Type: application/json; charset=UTF-8"
#define HDR_X_ACCEPT "X-Accept: application/json"

/* Initialization stuff */
int pocket_init(void);

/* Free the mallocs! */
void pocket_clean(void);

/* Request token from server */
char *pocket_get_token(const char *key);

/* Convert a request token into a Pocket access token */
char *pocket_auth(const char *key, const char* token);

/* Make authenticated GET request */
void pocket_get(const char *key, const char *token);

/* Make authenticated ADD request */
void pocket_add(const char *key, const char *token, const char* url); 

#endif
