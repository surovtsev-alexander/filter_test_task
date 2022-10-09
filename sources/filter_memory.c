#include "../include/filter_memory.h"
#include "../include/common.h"
#include "../include/symbols.h"
#include "../include/filter_ret_code.h"

#include <stdlib.h>
#include <stdio.h>


// region: local varibles
memory_chunk_t *head_memory_chunk       = NULL;

memory_chunk_t *current_memory_chunk    = NULL;
// endregion: local variables


memory_chunk_t* create_empty_memory_chunk();


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
  if (NULL == head_memory_chunk)
  {
    head_memory_chunk = create_empty_memory_chunk();

    if (NULL == head_memory_chunk)
    {
      return FILTER_RET_CODE_INTERNAL_NO_MEMORY_001;
    }
    current_memory_chunk = head_memory_chunk;
  }

  int stored_symbols = current_memory_chunk->stored_symbols;
  if (FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS < stored_symbols)
  {
    return FILTER_RET_CODE_INTERNAL_ERROR_002;
  }

  if (FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS == stored_symbols)
  {
    if (NULL == current_memory_chunk->next)
    {
      memory_chunk_t *new_memory_chunk = create_empty_memory_chunk();
      if (NULL == new_memory_chunk)
      {
        return FILTER_RET_CODE_INTERNAL_NO_MEMORY_002;
      }
      new_memory_chunk->stored_symbols = 0;
      new_memory_chunk->prev           = current_memory_chunk;
      new_memory_chunk->next           = NULL;

      current_memory_chunk->next       = new_memory_chunk;

      current_memory_chunk             = new_memory_chunk;
    }
    else
    {
      current_memory_chunk                 = current_memory_chunk->next;
      current_memory_chunk->stored_symbols = 0;
    }
  }

  current_memory_chunk->data[FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS - 1 - current_memory_chunk->stored_symbols] = c;
  current_memory_chunk->stored_symbols++;

  return FILTER_RET_CODE_NO_ERROR;
}

filter_ret_code_t print_memory_reversely()
{
  while (true)
  {
    if (NULL == current_memory_chunk)
    {
      break;
    }

    int stored_symbols = current_memory_chunk->stored_symbols;
    if (FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS < stored_symbols)
    {
      return FILTER_RET_CODE_INTERNAL_ERROR_003;
    }

    if (0 == stored_symbols && current_memory_chunk == head_memory_chunk)
    {
      return FILTER_RET_CODE_NO_ERROR;
    }

    char *data = current_memory_chunk->data;


    if (0 < stored_symbols)
    {
      printf(
          "%.*s\n",
          stored_symbols,
          data + (FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS - stored_symbols)
      );
    }

    if (current_memory_chunk == head_memory_chunk)
    {
      head_memory_chunk->stored_symbols = 0;
      break;
    }
    else
    {
      current_memory_chunk = current_memory_chunk->prev;

      if (0 == current_memory_chunk->stored_symbols)
      {
        return FILTER_RET_CODE_INTERNAL_ERROR_004;
      }
    }
  }

  return FILTER_RET_CODE_NO_ERROR;
}

memory_chunk_t* create_empty_memory_chunk()
{
  memory_chunk_t *new_memory_chunk = malloc(sizeof(memory_chunk_t));

  if (NULL == new_memory_chunk)
  {
    return NULL;
  }

  new_memory_chunk->stored_symbols      = 0;
  new_memory_chunk->prev                = NULL;
  new_memory_chunk->next                = NULL;

  return new_memory_chunk;
}

