#ifndef FILTER_MEMORY_H
#define FILTER_MEMORY_H

#include "./filter_config.h"
#include "./filter_ret_code.h"

typedef struct memory_chunk_s {
  // symbols are stored in a reverse manner
  char                  data[FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS];
  int                   stored_symbols;

  struct memory_chunk_s *prev;
  struct memory_chunk_s *next;
} memory_chunk_t;


void                    empty_memory();
void                    forget_stored_symbols();
filter_ret_code_t       push_symbol(char symbol);
filter_ret_code_t       print_memory_reversely();

#endif // FILTER_MEMORY_H

