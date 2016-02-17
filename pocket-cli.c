#include <stdio.h>

#include "pocket.h"
#include "utils.h"
#include "config.h"

int main(int argc, char **argv) 
{
    if (argc < 2) {
        die("URL missed!");
    }

    pocket_init();
    pocket_add(POCKET_KEY, POCKET_TOKEN, argv[1]);
    pocket_clean();
    
    return 0;
}
