#include "../include/filter_logic.h"
#include "../include/filter_ret_code.h"
#include "../include/filter_state.h"
#include "../include/filter_memory.h"
#include "../include/symbols.h"
#include "../include/common.h"

#include <stdio.h>


static token_t           calculate_token_by_next_char(char current_symbol);
static filter_state_t    calculate_filter_state_by_next_token(token_t token);
static filter_ret_code_t push_symbol_if_required(char current_symbol);
static filter_ret_code_t print_memory_if_required();

#define BREAK_IF_ERROR()                                \
if (FILTER_RET_CODE_NO_ERROR != ret_code) break

static stored_char_t  stored_char_new_value  = STORED_CHAR_UNINTERESTING;
static filter_state_t filter_state_new_value = FILTER_STATE_IDLE;


filter_ret_code_t filter_pipe()
{
  char               c;
  filter_ret_code_t  ret_code = FILTER_RET_CODE_NO_ERROR;

  while (true)
  {
    c = getchar();

    if (EOF == c)
    {
      break;
    }

    // step 1
    token_t token = calculate_token_by_next_char(c);

    // step 2
    filter_state_new_value =
      calculate_filter_state_by_next_token(token);

    // step 3
    ret_code = push_symbol_if_required(c);
    BREAK_IF_ERROR();

    // step 4
    ret_code = print_memory_if_required();
    BREAK_IF_ERROR();

    // step 5
    stored_char  = stored_char_new_value;
    filter_state = filter_state_new_value;
  }

  if (FILTER_RET_CODE_NO_ERROR == ret_code &&
      (FILTER_STATE_ONE_LINE_COMMENT  == filter_state ||
       FILTER_STATE_MULTILINE_COMMENT == filter_state))
  {
    ret_code = print_memory_reversely();
  }

  empty_memory();

  return ret_code;
}


static token_t calculate_token_by_next_char(char current_symbol)
{
  static bool shadowed_by_backslash = false;

  token_t res = TOKEN_UNINTERESTING;

  stored_char_new_value = STORED_CHAR_UNINTERESTING;
  if (shadowed_by_backslash)
  {
    switch(current_symbol)
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
    switch(current_symbol)
    {
      case SYMBOL_BACKSLASH:
        shadowed_by_backslash = true;
        stored_char_new_value = stored_char;
        break;
      case SYMBOL_SLASH:
        if (STORED_CHAR_SLASH == stored_char)
        {
          res = TOKEN_SINGLE_LINE_COMMENT;
        }
        else if (STORED_CHAR_ASTERISK == stored_char &&
            FILTER_STATE_MULTILINE_COMMENT == filter_state)
        {
          res = TOKEN_MULTILINE_COMMENT_CLOSE;
        }
        else
        {
          if (!(FILTER_STATE_ONE_LINE_COMMENT  == filter_state ||
                FILTER_STATE_MULTILINE_COMMENT == filter_state))
          {
            forget_stored_symbols();
            candidate_slash_is_found = true;
          }

          stored_char_new_value = STORED_CHAR_SLASH;
        }
        break;
      case SYMBOL_ASTERISK:
        if (STORED_CHAR_SLASH == stored_char &&
            FILTER_STATE_MULTILINE_COMMENT != filter_state)
        {
          res = TOKEN_MULTILINE_COMMENT_OPEN;
        }
        else
        {
          stored_char_new_value = STORED_CHAR_ASTERISK;
        }
        break;
      case SYMBOL_QUOTATION:
        res = TOKEN_QUOTATION;
        break;
      case SYMBOL_NEW_LINE:
        res = TOKEN_NEW_LINE;
        break;
    }
  }

  return res;
}


static filter_state_t calculate_filter_state_by_next_token(token_t token)
{
  filter_state_t res = filter_state;

  switch(token)
  {
    case TOKEN_NEW_LINE:
      if (FILTER_STATE_ONE_LINE_COMMENT == filter_state)
      {
        res = FILTER_STATE_IDLE;
      }
      break;
    case TOKEN_QUOTATION:
      if (FILTER_STATE_STRING == filter_state)
      {
        res = FILTER_STATE_IDLE;
      }
      else if (FILTER_STATE_IDLE == filter_state)
      {
        res = FILTER_STATE_STRING;
      }
      break;
    case TOKEN_SINGLE_LINE_COMMENT:
      if (FILTER_STATE_IDLE == filter_state)
      {
        res = FILTER_STATE_ONE_LINE_COMMENT;
      }
      break;
    case TOKEN_MULTILINE_COMMENT_OPEN:
      if (FILTER_STATE_IDLE == filter_state)
      {
        res = FILTER_STATE_MULTILINE_COMMENT;
      }
      break;
    case TOKEN_MULTILINE_COMMENT_CLOSE:
      if (FILTER_STATE_MULTILINE_COMMENT == filter_state)
      {
        res = FILTER_STATE_IDLE;
      }
      break;
  }

  return res;
}


static filter_ret_code_t push_symbol_if_required(char current_symbol)
{
  filter_ret_code_t res = FILTER_RET_CODE_NO_ERROR;

  if (STORED_CHAR_SLASH != stored_char_new_value ||
      FILTER_STATE_IDLE != filter_state)
  {
    candidate_slash_is_found = false;
  }

  if (!candidate_slash_is_found &&
      FILTER_STATE_IDLE == filter_state &&
      FILTER_STATE_IDLE == filter_state_new_value)
  {
    return res;
  }

  // ignore that symbols to avoid confusion with \r\n and \n\r
  if (SYMBOL_CARRIAGE_RETURN == current_symbol)
  {
    return res;
  }

  if (SYMBOL_NEW_LINE == current_symbol &&
      FILTER_STATE_IDLE == filter_state_new_value &&
      (FILTER_STATE_ONE_LINE_COMMENT == filter_state ||
       FILTER_STATE_MULTILINE_COMMENT == filter_state))
  {
    return res;
  }

  res = push_symbol(current_symbol);

  return res;
}


static filter_ret_code_t print_memory_if_required()
{
  filter_ret_code_t res = FILTER_RET_CODE_NO_ERROR;

  if (filter_state_new_value == filter_state ||
      FILTER_STATE_IDLE != filter_state_new_value)
  {
    return res;
  }

  if (FILTER_STATE_ONE_LINE_COMMENT  == filter_state ||
      FILTER_STATE_MULTILINE_COMMENT == filter_state)
  {
    res = print_memory_reversely();
  }

  return res;
}

