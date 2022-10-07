#ifndef FILTER_STATE_H
#define FILTER_STATE_H

enum prev_char_e {
  PREV_CHAR_SLASH,
  PREV_CHAR_ASTERISK,
  PREV_CHAR_UNINTERESTING,
};

enum filter_state_e {
  FILTER_STATE_IDLE,
  FILTER_STATE_ONE_LINE_COMMENT,
  FILTER_STATE_MULTILINE_COMMENT,
};


typedef unsigned char prev_char_t;
typedef unsigned char filter_state_t;


extern prev_char_t      prev_char;
extern filter_state_t   filter_state;


#endif // FILTER_STATE_H

