#ifndef FILTER_RET_CODE_H
#define FILTER_RET_CODE_H


#include <stdlib.h>
#include <errno.h>

#define FILTER_RET_CODE_NO_ERROR                EXIT_SUCCESS
#define FILTER_RET_CODE_ERROR_NO_MEMORY         ENOMEM

#define FILTER_RET_CODE_INTERNAL_ERROR_001      -1

typedef int                                     filter_ret_code_t;

#endif // FILTER_RET_CODE_H

