#ifndef FILE_IO_H
#define FILE_IO_H
#include "file_chunk.h"

file_chunk file_io_read(char* filename, int rows, int offset);

#endif