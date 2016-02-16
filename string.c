#include <stdlib.h>

#include "string.h"
#include "utils.h"

void string_init(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    die("malloc() failed");
  }
  s->ptr[0] = '\0';
}

void string_cleanup(struct string *s) {
  if (s->ptr) {
    free(s->ptr);
  }
  s->ptr = NULL;
}
