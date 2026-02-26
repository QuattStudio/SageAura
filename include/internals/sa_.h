/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/







#pragma once






#include "sa_inc.h"
#include "internals/sa_core_.h"
#include "core/sa_core.h"


struct SA_Window {
    int width;
    int height;

    GLFWwindow* handle;

    int flags;
    SA_STATE_I state;


    struct {
        float r, g, b;
    } color;

    SA_Timer* timer;

    int fps;
};








extern struct SA_Window *SA_WindowInst_I;