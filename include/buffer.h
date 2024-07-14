#ifndef BUFFER_H
#define BUFFER_H

#define BUF_INIT {NULL, 0}

typedef struct {
    char* string;
    int len;
} buffer;

void buffer_append(buffer* buf, const char* str, int len);

void buffer_free(buffer* buf);

#endif