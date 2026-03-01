/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#include "sa_window.h"
#include "sa_common.h"
#include "sa_core.h"
#include "sa_text.h"

#include "sa_event.h"

#include "sa_renderer.h"
#include "sa_audio.h"
#include "sa_inc.h"

#include "sa_algo.h" 


// internals
#define GLH_IMPLEMENTATION
#include "glh.h"


#include "sa_.h"
#include "sa_core_.h"


// C std libs
#include <stdio.h>
#include <stdlib.h>


/* Internally Assigned Window */
SA_Window *SA_WindowInst_I = NULL;





/* internal flags */

int SA_IsControlFlagEnabled_I = 0;


static int SA_WindowInitFlags_I = 0;



#define SA_CheckErrState_I(obj, retType, msg)\
    if (SA_NOT obj) {\
        SA_CheckIsControlFlagEnabledEx_I(\
            retType,\
            msg\
        );\
    }



/* Functions uses! */

int SA_Start(int flags)
{
    if (flags & SA_FLAG_ENABLE_CONTROL)
        SA_IsControlFlagEnabled_I = 1;
    



    /* Init GLFW */
    int GLFWInitErrState = glfwInit();

    SA_CheckErrState_I(
        GLFWInitErrState,
        SA_FALSE,
        "GLFW Initialization failed!"
    )

    SA_LOGV_INFO("GLFW Initialization completed!");

    SA_WindowInitFlags_I = flags;

    
    /* Setup Gl version */
    GLH_UseGL330Version();
    SA_LOGV_INFO("GL Version : %d", SA_GL_VERSION_USED);

    SA_OpenAudioEngine_I();


    SA_LOG_INFO("SageAura Initialization completed!");

    return SA_TRUE;
}



/* Create Window */
int SA_OpenWindow(int width, int height, const char* title)
{
    SA_ApplyGLFWWindowHint_I(SA_WindowInitFlags_I);
    // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    // Create GLFW Window
    GLFWwindow* GLFW_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (SA_NOT GLFW_Window)
    {
        SA_CheckIsControlFlagEnabledEx_I(
            SA_FALSE, 
            "GLFW Window Creation Failed!"
        );
    }


    SA_Window *window = SA_MALLOC(SA_Window);
    if (SA_NOT window) 
    {
        SA_CheckIsControlFlagEnabledEx_I(
            SA_FALSE, 
            "SageAura Window allocation Failed!"
        );
    }

    glfwMakeContextCurrent(GLFW_Window);


    
    /* Init renderer */
    SA_InitRenderer_I();
    SA_SetProjectionOrtho(0.0f, (float)width, (float)height, 0.0f); // Y=0 at top

    window->handle = GLFW_Window;
    window->flags = 0;
    window->width = width;
    window->height = height;


    window->fps = 60;

    // set background color greyish by default!
    window->color.r = 0.13f;
    window->color.g = 0.13f;
    window->color.b = 0.13f;

    window->timer = SA_StartTimer();

    window->callback = NULL;


    // global window info filling


    SA_SetWindowEventCallBacks_I(window->handle);


    // register window internally
    SA_WindowInst_I = window;

    
    SA_LOGV_INFO("SageAura Window Creation successfull!");


    return SA_TRUE;
}





int SA_Play()
{

    // don't play if window not found
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, 0);  


    glfwPollEvents();
    SA_UpdateInput();

    // needed for run any type of event handling, can be NULL but important to call for event handling
    SA_HandleEvents(SA_WindowInst_I->callback);

    return SA_NOT glfwWindowShouldClose(SA_WindowInst_I->handle);
}




void SA_SetEventTo(SA_EventCallback callback)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    
    SA_WindowInst_I->callback = callback;
}




void SA_CloseWindow(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);  


    SA_DestroyMesh_I(GlobalMesh);


    glfwDestroyWindow(SA_WindowInst_I->handle);

    SA_LOGV_INFO("GLFW window Destroyed!");

    SA_StopTimer(SA_WindowInst_I->timer);

    free(SA_WindowInst_I);
    SA_WindowInst_I = NULL;

    SA_WindowInitFlags_I = 0;

    // clear the default font

    if (SA_DefaultFont_I) {
        SA_UnLoadFont(SA_DefaultFont_I);
        SA_DefaultFont_I = NULL;        
        SA_LOG_INFO("Default Font unloaded successfully!");
    }


    SA_CloseAudioEngine_I();


    SA_IsControlFlagEnabled_I = 0; // close the flag

    glfwTerminate();

    SA_LOG_INFO("SageAura window closed successfully!");
}












void SA_BeginDrawing(void)
{
    SA_MeshCounterReset_I(GlobalMesh);
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    GLH_ClearColor(
        SA_WindowInst_I->color.r,
        SA_WindowInst_I->color.g,
        SA_WindowInst_I->color.b
    );
}



void SA_EndDrawing(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);

    SA_FlushBatch();

    glfwSwapBuffers(SA_WindowInst_I->handle);

    
    SA_MeshCounterReset_I(GlobalMesh);

    SA_Delay((int)(1000.0 / SA_WindowInst_I->fps));
}









void SA_SetBackgroundColor(SA_Colori color)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_Color fcolor;
    fcolor = SA_NormalizeColorEx(color);

    SA_WindowInst_I->color.r = fcolor.r;
    SA_WindowInst_I->color.g = fcolor.g;
    SA_WindowInst_I->color.b = fcolor.b;

    SA_LOG_INFO("new background color applied successfully! where Color: (R: %f; G: %f; B: %f)", 
        fcolor.r, fcolor.g, fcolor.b);
}



void SA_SetTargetFPS(int fps)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    
    SA_WindowInst_I->fps = fps;
}






float SA_GetDeltaTime()
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, 0.0f);

    return SA_GetDeltaFromTimer(SA_WindowInst_I->timer);
}






void SA_EnableFullScreen()
{

    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    SA_CHECK_WINDOW_I(SA_WindowInst_I->handle, SA_MSG_GLFW_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);


    static int fullscreen = 0;
    static int wx, wy, ww, wh;

    fullscreen = !fullscreen;

    if (fullscreen)
    {
        glfwGetWindowPos(SA_WindowInst_I->handle, &wx, &wy);
        glfwGetWindowSize(SA_WindowInst_I->handle, &ww, &wh);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(SA_WindowInst_I->handle, monitor,
                             0, 0,
                             mode->width, mode->height,
                             mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(SA_WindowInst_I->handle, NULL,
                             wx, wy,
                             ww, wh,
                             0);
    }
}




// 3179 LOC total in something v5.0.1 - v5.0.2