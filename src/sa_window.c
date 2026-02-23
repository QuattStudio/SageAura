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

#include "sa_renderer.h"
#include "sa_event.h"
#include "sa_inc.h"


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

int SA_IsControlFlagEnabled = 0;





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
    if (flags & SA_FLAG_TYPE_CONTROL_I)
        SA_IsControlFlagEnabled = 1;

    /* Init GLFW */
    int GLFWInitErrState = glfwInit();

    SA_CheckErrState_I(
        GLFWInitErrState,
        SA_FALSE,
        "GLFW Initialization failed!"
    )

    SA_LOGV_INFO("GLFW Initialization completed!");

    
    /* Setup Gl version */
    GLH_UseGL330Version();
    SA_LOGV_INFO("GL Version : %d", SA_GL_VERSION_USED);


    SA_LOG_INFO("SageAura Initialization completed!");

    return SA_TRUE;
}



/* Create Window */
int SA_OpenWindow(int width, int height, const char* title)
{
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
    window->state = SA_WND_STATE_RUN_I;

    window->fps = 60;

    // set background color greyish by default!
    window->color.r = 0.13f;
    window->color.g = 0.13f;
    window->color.b = 0.13f;

    SA_SetWindowEventCallBacks_I(window);


    // register window internally
    SA_WindowInst_I = window;

    
    SA_LOGV_INFO("SageAura Window Creation successfull!");


    return SA_TRUE;
}





int SA_Play(void)
{

    // don't play if window not found
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, 0);  


    glfwPollEvents();
    SA_UpdateInput();

    return SA_NOT glfwWindowShouldClose(SA_WindowInst_I->handle);
}







void SA_CloseWindow(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);  


    SA_DestroyMesh_I(GlobalMesh);


    glfwDestroyWindow(SA_WindowInst_I->handle);

    SA_LOGV_INFO("GLFW window Destroyed!");


    free(SA_WindowInst_I);
    SA_WindowInst_I = NULL;
    SA_IsControlFlagEnabled = 0; // close the flag

    glfwTerminate();

    SA_LOG_INFO("SageAura window closed successfully!");
}












void SA_BeginFrame(void)
{
    SA_MeshCounterReset_I(GlobalMesh);
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);
    GLH_ClearColor(
        SA_WindowInst_I->color.r,
        SA_WindowInst_I->color.g,
        SA_WindowInst_I->color.b
    );
}



void SA_EndFrame(void)
{
    SA_CHECK_WINDOW_I(SA_WindowInst_I, SA_MSG_WINDOW_NOT_FOUND_I, SA_RET_TYPE_NONE_I);

    SA_FlushBatch();

    glfwSwapBuffers(SA_WindowInst_I->handle);

    
    SA_MeshCounterReset_I(GlobalMesh);

    SA_Delay(16);
}