#ifndef FILTER_MEMORY_H
#define FILTER_MEMORY_H

#include "./filter_config.h"
#include "./filter_ret_code.h"

typedef struct memory_chunk_s {
  char                  data[FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS];
  int                   position;

  struct memory_chunk_s *prev;
  struct memory_chunk_s *next;
} memory_chunk_t;


void                    empty_memory();
filter_ret_code_t       store_char(char c);
void                    print_memory_reversely();
void                    to_start();

#endif // FILTER_MEMORY_H

