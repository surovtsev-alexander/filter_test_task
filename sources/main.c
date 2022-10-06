#include "../include/ab.h"

#include <stdio.h>

int main()
{
  printf("starting\n");

  a();
  b();

  int r = printf("finishing\n");

  printf("result: %d", r);

  return 0;
}

