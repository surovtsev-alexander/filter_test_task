#include "../include/filter_logic.h"
#include "../include/filter_error_codes.h"
#include "../include/filter_state.h"
#include "../include/filter_memory.h"
#include "../include/common.h"

#include <stdio.h>

int filter_pipe()
{
  char c;

  while (true)
  {
    c = getchar();

    if (EOF == c)
    {
      break;
    }

    

    putchar(c);
  }


  return FILTER_NO_ERROR;
}

