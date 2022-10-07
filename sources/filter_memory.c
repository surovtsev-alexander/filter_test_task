#include "../include/filter_memory.h"
#include "../include/common.h"
#include "../include/symbols.h"
#include "../include/filter_ret_code.h"

#include <stdlib.h>


// region: local varibles
memory_chunk_t *head_memory_chunk       = NULL;

memory_chunk_t *current_memory_chunk    = NULL;
// endregion: local variables


#warning "remove"
#include <stdio.h>

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


filter_ret_code_t store_char(char c)
{
  putchar(c);

  return FILTER_RET_CODE_NO_ERROR;
}

void print_memory_reversely()
{

#warning "print new line if there is at least one char in the memory"
  putchar(SYMBOL_NEW_LINE);
  to_start();
}

void to_start()
{
}

