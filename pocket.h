#ifndef __POCKET_H__
#define __POCKET_H__

/* URL to be called when the authorization process has been completed */
#define REDIRECT_URI "https://github.com/anavarro/pocket-cli"

/* Pocket API */
#define URL_REQUEST "https://getpocket.com/v3/oauth/request"
#define URL_AUTORIZE "https://getpocket.com/v3/oauth/authorize"
#define URL_RETRIEVE "https://getpocket.com/v3/get"

/* authorize application's request token */
#define URL_AUTH "https://getpocket.com/auth/authorize"

/* use JSON for the requests */
#define HDR_CONTENT_TYPE "Content-Type: application/json; charset=UTF-8"
#define HDR_X_ACCEPT "X-Accept: application/json"

/* Initialization stuff */
int pocket_init();

/* Free the mallocs! */
void pocket_clean();

/* Request token from server */
char *pocket_get_token(const char *key);

/* Convert a request token into a Pocket access token */
char *pocket_auth(const char *key);

/* Make authenticated GET request */
void pocket_get(const char *key, const char *token);

/* Make authenticated ADD request */
void pocket_add(const char *key, const char *token);

/* Redirect user to Pocket to continue authorization */
char *get_auth_url(const char *token);

#endif
