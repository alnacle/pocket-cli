#include <stdio.h>
#include <stdlib.h>
#include "pocket.h"
#include "utils.h"

int main(int argc, char **argv) 
{
    char *auth_token;
    char *access_token;
    char key[50];

    FILE *config;

    pocket_init();

    printf("\n Open your browser and go to:\n\n "
            "http://getpocket.com/developer/apps/new \n\n"
            " paste here the autogenerated consumer-key string: ");

    scanf("%s", key);
    getchar(); // Ugly!

    auth_token = pocket_get_token(key);
    printf (" \nReceived token: %s\n", key);

    /* Redirect user to Pocket to continue authorization */
    printf("\n Enter the following URL and confirm the app (Enter when done)\n\n"
            "%s?request_token=%s&redirect_uri=%s\n\n", 
            URL_AUTH, auth_token, REDIRECT_URI);

    getchar();

    access_token = pocket_auth(key, auth_token);

    /* Create a simple config.h file */
    config = fopen("config.h", "w");
    if (NULL == config)
    {
        die("Error when creating config.h file!\n");
    }
    fprintf(config, "#pragma once\n\n"
           "#define POCKET_KEY   \"%s\"\n"
           "#define POCKET_TOKEN \"%s\"\n\n", key, access_token);

    fclose(config);
    
    printf(" config.h file successfully created. Continue with 'make pocket-cli'\n\n");
    pocket_clean();
}
