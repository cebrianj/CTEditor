#ifndef FILE_CHUNK_H
#define FILE_CHUNK_H

#include "row.h"

typedef struct {
    row* rows;
    int num_rows;
} file_chunk;

file_chunk file_chunk_create(row* rows, int num_rows);

void file_chunk_free_content(file_chunk fc);

#endif