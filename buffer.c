#include <stdlib.h>

#include "buffer.h"
#include "utils.h"

void buffer_init(struct buffer *s) 
{
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        die("malloc() failed");
    }
    s->ptr[0] = '\0';
}

void buffer_cleanup(struct buffer *s) 
{
    if (s->ptr) {
        free(s->ptr);
    }
    s->ptr = NULL;
}
