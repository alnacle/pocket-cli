#ifndef __BUFFER_H__
#define __BUFFER_H__

struct buffer {
  char *ptr;
  size_t len;
};

void buffer_init(struct buffer *s);

void buffer_cleanup(struct buffer *s);

#endif
