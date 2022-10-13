#ifndef FILTER_STATE_H
#define FILTER_STATE_H

#include "./common.h"

enum stored_char_e {
  STORED_CHAR_SLASH,
  STORED_CHAR_ASTERISK,
  STORED_CHAR_UNINTERESTING,
};

enum filter_state_e {
  FILTER_STATE_IDLE,
  FILTER_STATE_STRING,
  FILTER_STATE_ONE_LINE_COMMENT,
  FILTER_STATE_MULTILINE_COMMENT,
};


enum token_e {
  TOKEN_UNINTERESTING,
  TOKEN_NEW_LINE,
  TOKEN_QUOTATION,
  TOKEN_SINGLE_LINE_COMMENT,
  TOKEN_MULTILINE_COMMENT_OPEN,
  TOKEN_MULTILINE_COMMENT_CLOSE,
};


typedef unsigned char stored_char_t;
typedef unsigned char filter_state_t;
typedef unsigned char token_t;


extern stored_char_t    stored_char;
extern filter_state_t   filter_state;
extern bool             candidate_slash_is_found;

#endif // FILTER_STATE_H

