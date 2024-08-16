#define _GNU_SOURCE

#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

row* file_io_read(char* filename, int num_rows, int offset) {
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
    for (i = 0; i < num_rows; i++) {
        line = NULL;
        linelen = getline(&line, &linecap, fp);
        if (linelen != -1) {
            while (linelen > 0 &&
                   (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
                linelen--;
            rows[i].chars = line;
            rows[i].size = linelen;
        }
    }

    fclose(fp);
    return rows;
}