#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void die(const char *err) {
  fprintf(stderr, "%s\n", err);
  exit(EXIT_FAILURE);
}
