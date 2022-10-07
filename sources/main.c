#include "../include/filter_logic.h"
#include "../include/filter_ret_code.h"

int main()
{
  filter_ret_code_t filtering_ret_code = filter_pipe();

  return filtering_ret_code;
}

