#include "../include/filter_state.h"

stored_char_t   stored_char              = STORED_CHAR_UNINTERESTING;
filter_state_t  filter_state             = FILTER_STATE_IDLE;
bool            shadowed_by_backslash    = false;
bool            candidate_slash_is_found = false;
