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
  stored_char_t         stored_char_new_value;
  filter_state_t        filter_state_new_value;
  filter_ret_code_t     ret_code                = FILTER_RET_CODE_NO_ERROR;
  token_t               token;

  while (true)
  {
    c = getchar();

    if (EOF == c)
    {
      break;
    }


    token                       = TOKEN_UNINTERESTING;
    stored_char_new_value       = STORED_CHAR_UNINTERESTING;
    if (shadowed_by_backslash)
    {
      switch(c)
      {
        case SYMBOL_CARRIAGE_RETURN:
          stored_char_new_value = stored_char;
          break;
        case SYMBOL_NEW_LINE:
          shadowed_by_backslash = false;
          stored_char_new_value = stored_char;
          break;
        default:
          shadowed_by_backslash = false;
          break;
      }
    }
    else
    {
      switch(c)
      {
        case SYMBOL_BACKSLASH:
          shadowed_by_backslash = true;
          stored_char_new_value = stored_char;
          break;
        case SYMBOL_SLASH:
          if (STORED_CHAR_SLASH == stored_char)
          {
            token = TOKEN_SINGLE_LINE_COMMENT;
          }
          else if (STORED_CHAR_ASTERISK == stored_char)
          {
            token = TOKEN_MULTILINE_COMMENT_CLOSE;
          }
          else
          {
            stored_char_new_value = STORED_CHAR_SLASH;
          }
          break;
        case SYMBOL_ASTERISK:
          if (STORED_CHAR_SLASH == stored_char)
          {
            token = TOKEN_MULTILINE_COMMENT_OPEN;
          }
          else
          {
            stored_char_new_value = STORED_CHAR_ASTERISK;
          }
          break;
        case SYMBOL_QUOTATION:
          token = TOKEN_QUOTATION;
          break;
        case SYMBOL_NEW_LINE:
          token = TOKEN_NEW_LINE;
          break;
      }
    }
    stored_char = stored_char_new_value;

    if (false && TOKEN_UNINTERESTING != token)
    {
      printf("TOKEN: %d\n", token);
    }

    filter_state_new_value = filter_state;
    switch(token)
    {
      case TOKEN_NEW_LINE:
        if (FILTER_STATE_ONE_LINE_COMMENT == filter_state)
        {
          filter_state_new_value = FILTER_STATE_IDLE;
        }
        break;
      case TOKEN_QUOTATION:
        if (FILTER_STATE_STRING == filter_state)
        {
          filter_state_new_value = FILTER_STATE_IDLE;
        }
        else if (FILTER_STATE_IDLE == filter_state)
        {
          filter_state_new_value = FILTER_STATE_STRING;
        }
        break;
      case TOKEN_SINGLE_LINE_COMMENT:
        if (FILTER_STATE_IDLE == filter_state)
        {
          filter_state_new_value = FILTER_STATE_ONE_LINE_COMMENT;
        }
        break;
      case TOKEN_MULTILINE_COMMENT_OPEN:
        if (FILTER_STATE_IDLE == filter_state)
        {
          filter_state_new_value = FILTER_STATE_MULTILINE_COMMENT;
        }
        break;
      case TOKEN_MULTILINE_COMMENT_CLOSE:
        if (FILTER_STATE_MULTILINE_COMMENT == filter_state)
        {
          filter_state_new_value = FILTER_STATE_IDLE;
        }
        break;
    }

    if (true && filter_state_new_value != filter_state)
    {
      printf("filter_state: %d -> %d\n", filter_state, filter_state_new_value);
    }
    filter_state = filter_state_new_value;

    // TODO: remove this temporary solution
    continue;


    // ignore that symbol to avoid confusion with \r\n and \n\r
    if (SYMBOL_CARRIAGE_RETURN == c)
    {
      continue;
    }

    stored_char_new_value = STORED_CHAR_UNINTERESTING;

    switch(filter_state)
    {
      case FILTER_STATE_IDLE:
        if (SYMBOL_SLASH == c)
        {
          if (STORED_CHAR_SLASH == stored_char)
          {
            filter_state = FILTER_STATE_ONE_LINE_COMMENT;
            ret_code = store_char(SYMBOL_SLASH);
            break;
          }
          else
          {
            stored_char_new_value = STORED_CHAR_SLASH;
          }
        }
        else if (SYMBOL_ASTERISK == c)
        {
          if (STORED_CHAR_SLASH == stored_char)
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
          stored_char_new_value = STORED_CHAR_ASTERISK;
        }
        else if (SYMBOL_SLASH == c)
        {
          if (STORED_CHAR_ASTERISK == stored_char)
          {
            filter_state = FILTER_STATE_IDLE;
            putchar(SYMBOL_SLASH);
            ret_code = print_memory_reversely();
            stored_char_new_value = STORED_CHAR_UNINTERESTING;
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

    stored_char = stored_char_new_value;

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

