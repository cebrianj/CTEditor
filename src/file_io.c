#define _GNU_SOURCE

#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>

#include "row.h"
#include "utils.h"

file_chunk file_io_read(char* filename, int num_rows, int offset) {
    FILE* fp = fopen(filename, "r");
    if (!fp) panic("fopen");

    int i = 0;
    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    for (i = 0; i < offset; i++) {
        getline(&line, &linecap, fp);
    }

    row* rows = malloc(num_rows * sizeof(row));
    int readed_rows = 0;
    for (i = 0; i < num_rows; i++) {
        line = NULL;
        linelen = getline(&line, &linecap, fp);
        if (linelen != -1) {
            readed_rows++;
            while (linelen > 0 &&
                   (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
                linelen--;
            rows[i].chars = line;
            rows[i].size = linelen;
        }
    }

    file_chunk chunk = file_chunk_create(rows, readed_rows);
    fclose(fp);
    return chunk;
}