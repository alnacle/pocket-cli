#include <stdio.h>
#include <string.h>

#include "pocket.h"
#include "utils.h"
#include "config.h"

#define INPUT_SIZE 1024

int main(int argc, char **argv) 
{
    char buf[INPUT_SIZE];

    if (argc < 2) {
        fgets(buf, sizeof buf, stdin);
        if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
        }
    } else {
        strncpy(buf, argv[1], sizeof buf);
    }

    pocket_init();
    pocket_add(POCKET_KEY, POCKET_TOKEN, buf);
    pocket_clean();

    return 0;
}
