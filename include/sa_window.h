/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once






#include "sa_types.h"

#include "sa_platforms.h"
#include "sa_common.h"

#include "sa_core.h"



/**
 * 
 */
typedef struct SA_Window SA_Window;



extern int SA_IsControlFlagEnabled;


SA_API
int SA_Start(int flags);


SA_API
int SA_OpenWindow(int width, int height, const char* title);


SA_API
void SA_CloseWindow(void);


SA_API
int SA_Play(void);



SA_API
void SA_BeginFrame(void);



SA_API
void SA_EndFrame(void);









/* Macros for task simplifications */

#define SA_CheckIsControlFlagEnabled_I(retType)\
    if (SA_IsControlFlagEnabled)\
        return retType;\
    else exit(1)


#define SA_CheckIsControlFlagEnabledEx_I(retType, msg)\
    SA_LOG_ERROR(msg);\
    SA_CheckIsControlFlagEnabled_I(retType)

