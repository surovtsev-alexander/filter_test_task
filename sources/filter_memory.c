#include "../include/filter_memory.h"
#include "../include/common.h"

#include <stdlib.h>


// region: local varibles
memory_chunk_t *head_memory_chunk       = NULL;

memory_chunk_t *current_memory_chunk    = NULL;
// endregion: local variables


void empty_memory()
{
  memory_chunk_t *curr  = head_memory_chunk;
  memory_chunk_t *tmp   = NULL;

  while (true)
  {
    if (NULL == curr)
    {
      break;
    }

    tmp = curr->next;
    free(curr);
    curr = tmp;
  }

  head_memory_chunk     = NULL;
  current_memory_chunk  = NULL;
}


void store_char(char c)
{
}

void print_memory_reversely()
{
}

void to_start()
{
}

