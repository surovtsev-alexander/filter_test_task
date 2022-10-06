#include "../include/filter_logic.h"

#include <stdio.h>

#include <stdbool.h>

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
