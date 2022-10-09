#include "../include/filter_logic.h"
#include "../include/filter_ret_code.h"
#include "../include/filter_state.h"
#include "../include/filter_memory.h"
#include "../include/symbols.h"
#include "../include/common.h"

#include <stdio.h>


filter_ret_code_t filter_pipe()
{
  char                  c;
  char                  prev_char_new_value;
  filter_ret_code_t     ret_code                = FILTER_RET_CODE_NO_ERROR;

  while (true)
  {
    c = getchar();

    if (EOF == c)
    {
      break;
    }


    // ignore that symbol to avoid confusion with \r\n and \n\r
    if (SYMBOL_CARRIAGE_RETURN == c)
    {
      continue;
    }

    prev_char_new_value = PREV_CHAR_UNINTERESTING;

    switch(filter_state)
    {
      case FILTER_STATE_IDLE:
        if (SYMBOL_SLASH == c)
        {
          if (PREV_CHAR_SLASH == prev_char)
          {
            filter_state = FILTER_STATE_ONE_LINE_COMMENT;
            ret_code = store_char(SYMBOL_SLASH);
            break;
          }
          else
          {
            prev_char_new_value = PREV_CHAR_SLASH;
          }
        }
        else if (SYMBOL_ASTERISK == c)
        {
          if (PREV_CHAR_SLASH == prev_char)
          {
            filter_state = FILTER_STATE_MULTILINE_COMMENT;
            ret_code = store_char(SYMBOL_SLASH);
            break;
          }
        }
        break;
      case FILTER_STATE_ONE_LINE_COMMENT:
        if (SYMBOL_NEW_LINE == c)
        {
          filter_state = FILTER_STATE_IDLE;
          ret_code = print_memory_reversely();
        }
        break;
      case FILTER_STATE_MULTILINE_COMMENT:
        if (SYMBOL_ASTERISK == c)
        {
          prev_char_new_value = PREV_CHAR_ASTERISK;
        }
        else if (SYMBOL_SLASH == c)
        {
          if (PREV_CHAR_ASTERISK == prev_char)
          {
            filter_state = FILTER_STATE_IDLE;
            putchar(SYMBOL_SLASH);
            ret_code = print_memory_reversely();
            prev_char_new_value = PREV_CHAR_UNINTERESTING;
          }
        }
        break;
      default:
        ret_code = FILTER_RET_CODE_INTERNAL_ERROR_001;
        break;
    }

    if (FILTER_RET_CODE_NO_ERROR != ret_code)
    {
      break;
    }

    prev_char = prev_char_new_value;

    if (FILTER_STATE_IDLE != filter_state)
    {
      ret_code = store_char(c);

      if (FILTER_RET_CODE_NO_ERROR != ret_code)
      {
        break;
      }
    }
  }

  if (FILTER_RET_CODE_NO_ERROR == ret_code)
  {
    ret_code = print_memory_reversely();
  }

  empty_memory();

  return ret_code;
}

