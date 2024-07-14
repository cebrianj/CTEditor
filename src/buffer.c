#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buffer_append(buffer* buffer, const char* str, int len) {
    char* new_buff = realloc(buffer->string, buffer->len + len);

    if (new_buff == NULL) {
        return;
    }

    memcpy(&new_buff[buffer->len], str, len);

    buffer->string = new_buff;
    buffer->len += len;
}

void buffer_free(buffer* buf) {
    if (buf->string != NULL) {
        free(buf->string);
    }
}