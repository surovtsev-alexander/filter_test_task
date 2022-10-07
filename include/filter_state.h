#ifndef FILTER_STATE_H
#define FILTER_STATE_H

enum prev_char_e {
  SLASH,
  UNINTERESTING,
};

enum filter_state_e {
  IDLE,
  ONE_LINE_COMMENT,
  MULTILINE_COMMENT,
};


typedef unsigned char prev_char_t;
typedef unsigned char filter_state_t;


extern prev_char_t      prev_char;
extern filter_state_t   filter_state;


#endif // FILTER_STATE_H

