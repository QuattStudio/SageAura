/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include <stdio.h>
#include <stdlib.h>


#include "sa_types.h"




#define SA_LOG_INFO(fmt, ...) \
    printf("[INFO] > " fmt "\n", ##__VA_ARGS__)


#define SA_LOG_WARN(fmt, ...) \
    printf("[WARN] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define SA_LOG_ERROR(fmt, ...) \
    printf("[ERR] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define SA_LOG_CRITICAL(fmt, ...) \
    printf("[CRITICAL] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); exit(1)






#ifndef SA_DISABLE_VERBOSE_LOGS_I


#define SA_LOGV_INFO(fmt, ...) \
    printf("[INFO-V] > " fmt "\n", ##__VA_ARGS__)


#define SA_LOGV_WARN(fmt, ...) \
    printf("[WARN-V] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#endif

















#define SA_COLOR_MAX_OPACITY    (255)
#define SA_GL_VERSION_USED      (330)





#define SA_NOT  !
#define SA_OR   ||
#define SA_XOR  ^
#define SA_AND  &&

#define SA_THEN  ?
#define SA_ELSE  :





#define SA_MALLOC(type) ((type*)malloc(sizeof(type)))
#define SA_MALLOC_N(type, n) ((type*)malloc(sizeof(type * n)))



/* structs macros */

#define SA_RECT(x, y, width, height)    ((SA_Rect){(x), (y), (width), (height)})
#define SA_RECTF(x, y, width, height)    ((SA_RectF){(x), (y), (width), (height)})



