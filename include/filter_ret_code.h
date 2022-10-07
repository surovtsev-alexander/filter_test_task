#ifndef FILTER_RET_CODE_H
#define FILTER_RET_CODE_H


#include <stdlib.h>
#include <errno.h>

#define FILTER_RET_CODE_NO_ERROR                EXIT_SUCCESS
#define FILTER_RET_CODE_NO_MEMORY_ERROR         ENOMEM

#define FILTER_RET_CODE_INTERNAL_ERROR_001      -1
#define FILTER_RET_CODE_INTERNAL_ERROR_002      -2
#define FILTER_RET_CODE_INTERNAL_ERROR_003      -3
#define FILTER_RET_CODE_INTERNAL_ERROR_004      -4
#define FILTER_RET_CODE_INTERNAL_NO_MEMORY_001  -101
#define FILTER_RET_CODE_INTERNAL_NO_MEMORY_002  -102

typedef int                                     filter_ret_code_t;

#endif // FILTER_RET_CODE_H

