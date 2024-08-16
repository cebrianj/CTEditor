#ifndef ROW_H
#define ROW_H

typedef struct row {
    int size;
    char *chars;
} row;

void row_free(row *r);

#endif