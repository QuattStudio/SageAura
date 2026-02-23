/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#include "sa_event.h"

#include <string.h>
#include "sa_.h"
#include "sa_common.h"
#include "sa_inc.h"


#define SA_MAX_EVENTS 256

static SA_Event eventQueue[SA_MAX_EVENTS];
static int eventCount = 0;










// ====================== CONTINUOUS INPUT STATE ======================
static SA_Bool keyDown[SA_KEY_LAST + 1]       = { SA_FALSE };
static SA_Bool keyPressed[SA_KEY_LAST + 1]    = { SA_FALSE };
static SA_Bool keyReleased[SA_KEY_LAST + 1]   = { SA_FALSE };

static SA_Bool mouseDown[SA_MOUSE_BUTTON_LAST + 1]      = { SA_FALSE };
static SA_Bool mousePressed[SA_MOUSE_BUTTON_LAST + 1]   = { SA_FALSE };
static SA_Bool mouseReleased[SA_MOUSE_BUTTON_LAST + 1]  = { SA_FALSE };

static double mouseX = 0.0;
static double mouseY = 0.0;
static double mouseWheel = 0.0;











void SA_PushEvent(SA_Event e)
{
    if (eventCount >= SA_MAX_EVENTS) return;
    eventQueue[eventCount++] = e;
}









// Call once per frame (after glfwPollEvents())
void SA_UpdateInput(void)
{
    // Reset "this frame only" flags
    memset(keyPressed,   0, sizeof(keyPressed));
    memset(keyReleased,  0, sizeof(keyReleased));
    memset(mousePressed, 0, sizeof(mousePressed));
    memset(mouseReleased,0, sizeof(mouseReleased));
    mouseWheel = 0.0;
}

// NEW: User calls this for every event they poll
void SA_ProcessEvent(const SA_Event* e)
{
    if (!e) return;

    switch (e->type)
    {
        case SA_EVENT_KEY_DOWN:
            if (!keyDown[e->key.key]) {
                keyPressed[e->key.key] = SA_TRUE;
            }
            keyDown[e->key.key] = SA_TRUE;
            break;

        case SA_EVENT_KEY_UP:
            if (keyDown[e->key.key]) {
                keyReleased[e->key.key] = SA_TRUE;
            }
            keyDown[e->key.key] = SA_FALSE;
            break;

        case SA_EVENT_MOUSE_BUTTON_DOWN:
            if (!mouseDown[e->mouseButton.button]) {
                mousePressed[e->mouseButton.button] = SA_TRUE;
            }
            mouseDown[e->mouseButton.button] = SA_TRUE;
            break;

        case SA_EVENT_MOUSE_BUTTON_UP:
            if (mouseDown[e->mouseButton.button]) {
                mouseReleased[e->mouseButton.button] = SA_TRUE;
            }
            mouseDown[e->mouseButton.button] = SA_FALSE;
            break;

        case SA_EVENT_MOUSE_MOVE:
            mouseX = e->mouseMove.x;
            mouseY = e->mouseMove.y;
            break;

        case SA_EVENT_MOUSE_SCROLL:
            mouseWheel += e->scroll.offset;
            break;

        default:
            break;
    }
}



// ====================== PUBLIC GETTERS (unchanged) ======================
SA_Bool SA_IsKeyDown(SA_Key key)
{
    if (key < 0 || key > SA_KEY_LAST) return SA_FALSE;
    return keyDown[key];
}

SA_Bool SA_IsKeyPressed(SA_Key key)
{
    if (key < 0 || key > SA_KEY_LAST) return SA_FALSE;
    return keyPressed[key];
}

SA_Bool SA_IsKeyReleased(SA_Key key)
{
    if (key < 0 || key > SA_KEY_LAST) return SA_FALSE;
    return keyReleased[key];
}

SA_Bool SA_IsMouseButtonDown(SA_MouseButton button)
{
    if (button < 0 || button > SA_MOUSE_BUTTON_LAST) return SA_FALSE;
    return mouseDown[button];
}

SA_Bool SA_IsMouseButtonPressed(SA_MouseButton button)
{
    if (button < 0 || button > SA_MOUSE_BUTTON_LAST) return SA_FALSE;
    return mousePressed[button];
}

SA_Bool SA_IsMouseButtonReleased(SA_MouseButton button)
{
    if (button < 0 || button > SA_MOUSE_BUTTON_LAST) return SA_FALSE;
    return mouseReleased[button];
}

double SA_GetMouseX(void) { return mouseX; }
double SA_GetMouseY(void) { return mouseY; }
double SA_GetMouseWheel(void) { return mouseWheel; }




int SA_PollEvent(SA_Event* out)
{
    if (eventCount == 0) return 0;

    *out = eventQueue[0];

    for (int i = 1; i < eventCount; i++)
        eventQueue[i - 1] = eventQueue[i];
    
    SA_ProcessEvent(out);

    eventCount--;
    return 1;
}








static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SA_Event e;

    if (action == GLFW_PRESS) {
        e.type = SA_EVENT_KEY_DOWN;
        e.key.key = key;
        SA_PushEvent(e);
    }
    else if (action == GLFW_RELEASE) {
        e.type = SA_EVENT_KEY_UP;
        e.key.key = key;
        SA_PushEvent(e);
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    SA_Event e;

    if (action == GLFW_PRESS) {
        e.type = SA_EVENT_MOUSE_BUTTON_DOWN;
        e.mouseButton.button = button;
        SA_PushEvent(e);
    }
    else if (action == GLFW_RELEASE) {
        e.type = SA_EVENT_MOUSE_BUTTON_UP;
        e.mouseButton.button = button;
        SA_PushEvent(e);
    }
}

static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    SA_Event e;
    e.type = SA_EVENT_MOUSE_MOVE;
    e.mouseMove.x = xpos;
    e.mouseMove.y = ypos;
    SA_PushEvent(e);
}



static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    SA_Event e;
    e.type = SA_EVENT_MOUSE_SCROLL;
    e.scroll.offset = yoffset;        // positive = scroll up / away from you
    SA_PushEvent(e);
}


void SA_SetWindowEventCallBacks_I(SA_Window* window)
{
    glfwSetKeyCallback(window->handle, key_callback);
    glfwSetCursorPosCallback(window->handle, cursor_callback);
    glfwSetMouseButtonCallback(window->handle, mouse_button_callback);
    glfwSetScrollCallback(window->handle, scroll_callback);
}

















// ================================================================
// USER EVENT CALLBACK (completely new code)
// ================================================================



void SA_RunEventCallback(SA_EventCallback callback)
{
    SA_Event event;
    if (SA_NOT SA_WindowInst_I) return;
    
    if (callback != NULL) {
        while (SA_PollEvent(&event))
            callback(SA_WindowInst_I, &event);
    }
}

