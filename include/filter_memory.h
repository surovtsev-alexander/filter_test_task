#ifndef FILTER_MEMORY_H
#define FILTER_MEMORY_H

#include "./filter_config.h"

typedef struct memory_chunk_s {
  char data[FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS];

  struct memory_chunk_s *prev;
  struct memory_chunk_s *next;
} memory_chunk;


#endif // FILTER_MEMORY_H

