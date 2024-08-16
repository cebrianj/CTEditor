#include "row.h"

#include <stdlib.h>

void row_free(row *r) {
    if (r == NULL) return;
    free(r->chars);
}
