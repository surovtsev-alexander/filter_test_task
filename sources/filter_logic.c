#include "../include/filter_logic.h"
#include "../include/filter_error_codes.h"
#include "../include/filter_state.h"
#include "../include/filter_memory.h"
#include "../include/symbols.h"
#include "../include/common.h"

#include <stdio.h>

int filter_pipe()
{
  char c;
  char prev_char_new_value;

  while (true)
  {
    c = getchar();

    if (EOF == c)
    {
      break;
    }

    prev_char_new_value = PREV_CHAR_UNINTERESTING;

    switch(filter_state)
    {
      case FILTER_STATE_IDLE:
        if (SYMBOL_SLASH == c)
        {
          if (PREV_CHAR_SLASH == prev_char)
          {
            puts("\n\nFILTER_STATE_ONE_LINE_COMMENT:\n\n");
            filter_state = FILTER_STATE_ONE_LINE_COMMENT;
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
            puts("\n\nFILTER_STATE_MULTILINE_COMMENT\n\n");
            filter_state = FILTER_STATE_MULTILINE_COMMENT;
          }
        }
        break;
      case FILTER_STATE_ONE_LINE_COMMENT:
        if (SYMBOL_NEW_LINE == c)
        {
          puts("\n\nFILTER_STATE_ONE_LINE_COMMENT -> FILTER_STATE_IDLE:\n\n");
          filter_state = FILTER_STATE_IDLE;
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
            puts("\n\nFILTER_STATE_MULTILINE_COMMENT -> FILTER_STATE_IDLE:\n\n");
            filter_state = FILTER_STATE_IDLE;
            prev_char_new_value = PREV_CHAR_UNINTERESTING;
          }
        }
        break;
      default:
        empty_memory();
        return INTERNAL_ERROR_001;
    }

    prev_char = prev_char_new_value;

    putchar(c);
  }

  empty_memory();

  return FILTER_NO_ERROR;
}

