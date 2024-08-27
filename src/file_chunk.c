#include "file_chunk.h"

#include <stdlib.h>

file_chunk file_chunk_create(row* rows, int num_rows) {
    return (file_chunk){.rows = rows, num_rows = num_rows};
}

void file_chunk_free_content(file_chunk fc) {
    for (int i = 0; i < fc.num_rows; i++) {
        row_free(&fc.rows[i]);
    }
    free(fc.rows);
}