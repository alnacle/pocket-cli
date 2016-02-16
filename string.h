#ifndef __STRING_H__
#define __STRING_H__

struct string {
  char *ptr;
  size_t len;
};

void string_init(struct string *s);

void string_cleanup(struct string *s);

#endif
