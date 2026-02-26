/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#include "sa_core.h"
#include "glh.h"
#include "sa_inc.h"



#include <stdlib.h>






#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__) || defined(__APPLE__) || defined(_POSIX_C_SOURCE)
    #include <time.h>      // for nanosleep (best precision)
    #include <unistd.h>    // fallback usleep
#endif

void SA_Delay(int ms)
{
    if (ms <= 0) return;   // ignore negative or zero

#ifdef _WIN32
    Sleep((DWORD)ms);      // Windows: milliseconds
#else
    // POSIX (Linux, macOS, etc.)
    #if _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec  = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000L;
        nanosleep(&ts, NULL);
    #else
        usleep((useconds_t)ms * 1000);   // microseconds
    #endif
#endif
}




SA_Mesh* SA_CreateMesh_I(SA_Uint VAO, SA_Uint VBO, SA_Uint EBO)
{
    SA_Mesh* mesh = SA_MALLOC(SA_Mesh);
    if (!mesh) return NULL;

    mesh->VAO = VAO;
    mesh->VBO = VBO;
    mesh->EBO = EBO;
    mesh->VertexCount = 0;
    mesh->IndexCount = 0;

    return mesh;
}




void SA_MeshCounterReset_I(SA_Mesh* mesh)
{
    if (SA_NOT mesh) {
        SA_LOG_WARN("Nothing provided to reset in mesh counter reset function!");
        return;
    }

    mesh->VertexCount = 0;
    mesh->IndexCount = 0;
}





void SA_DestroyMesh_I(SA_Mesh* mesh)
{
    if (SA_NOT mesh) {
        SA_LOG_WARN("No mesh provided for destruction!");
        return;
    }


    GLH_DelVAO(&mesh->VAO, 1);
    GLH_DelBuffers(&mesh->VBO, 1);
    GLH_DelBuffers(&mesh->EBO, 1);

    SA_LOG_INFO("Mesh Destroyed succesfully!");

    free(mesh);

    mesh = NULL;
}






#ifdef _WIN32

SA_Uint32 SA_GetTicks(void)
{
    return GetTickCount();
}

#else
#include <time.h>

SA_Uint32 SA_GetTicks(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

#endif





SA_Timer* SA_StartTimer(void)
{
    SA_Timer* timer = SA_MALLOC(SA_Timer);
    
    if (SA_NOT timer) {
        SA_LOG_WARN("Timer memory allocation failed!");
        return NULL;
    }

    SA_Uint32 now = SA_GetTicks();
    timer->time.start = now;
    timer->time.last = now;
    timer->time.current = now;
    timer->time.delta = 0.0f;

    return timer;
}










float SA_GetDeltaFromTimer(SA_Timer *timer)
{
    if (SA_NOT timer) {
        SA_LOG_WARN("Timer not found!");
        return 0;
    }

    timer->time.current = SA_GetTicks();
    timer->time.delta = (timer->time.current - timer->time.last) / 1000.0f;
    timer->time.last = timer->time.current;
    if (timer->time.delta > 0.05f)  timer->time.delta = 0.05f;

    return timer->time.delta;
}



void SA_StopTimer(SA_Timer* timer)
{
    if (SA_NOT timer) {
        SA_LOG_INFO("Timer stop successfully!");
        return;
    }

    free(timer);
    timer = NULL;
}




float SA_GetElapsed(SA_Timer* timer)
{
    if (SA_NOT timer) {
        SA_LOG_WARN("No timer provided in elapsed function!");
        return 0.0f;
    }
    return (SA_GetTicks() - timer->time.start) / 1000.0f;
}



void SA_ApplyGLFWWindowHint_I(SA_Uint flags)
{
    if (flags & SA_FLAG_WINDOW_RESIZABLE) {
        SA_LOG_INFO("Flag type [window resizable] setted on window!");
        glfwWindowHint(GLFW_RESIZABLE, SA_YES);
    }

    if (flags & SA_FLAG_WINDOW_BORDERLESS) {
        SA_LOG_INFO("Flag type [window border-less] setted on window!");
        glfwWindowHint(GLFW_DECORATED, SA_NO);
    }

    if (flags & SA_FLAG_WINDOW_MAXIMIZED) {
        SA_LOG_INFO("Flag type [window maximized] setted on window!");
        glfwWindowHint(GLFW_MAXIMIZED, SA_YES);
    }

    if (flags & SA_FLAG_WINDOW_FULLSCREEN) {
        SA_LOG_INFO("Flag type [window fullscreen] setted on window!");
        // glfwWindowHint(GLFW_FULL, SA_NO);
    }
    
}