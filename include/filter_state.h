#ifndef FILTER_STATE_H
#define FILTER_STATE_H

enum stored_char_e {
  STORED_CHAR_SLASH,
  STORED_CHAR_ASTERISK,
  STORED_CHAR_UNINTERESTING,
};

enum filter_state_e {
  FILTER_STATE_IDLE,
  FILTER_STATE_ONE_LINE_COMMENT,
  FILTER_STATE_MULTILINE_COMMENT,
};


typedef unsigned char stored_char_t;
typedef unsigned char filter_state_t;


extern stored_char_t    stored_char;
extern filter_state_t   filter_state;


#endif // FILTER_STATE_H

