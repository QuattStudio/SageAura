/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#pragma once


#include "core/sa_types.h"


#include "sa_platforms.h"


typedef enum
{
    SA_EVENT_NONE = 0,
    SA_EVENT_KEY_DOWN,
    SA_EVENT_KEY_UP,
    SA_EVENT_MOUSE_MOVE,
    SA_EVENT_MOUSE_BUTTON_DOWN,
    SA_EVENT_MOUSE_BUTTON_UP,
    SA_EVENT_MOUSE_SCROLL,
    SA_EVENT_WINDOW_RESIZE,
    SA_EVENT_WINDOW_CLOSE
} SA_EventType;



typedef enum SA_Key
{
    SA_KEY_UNKNOWN         = -1,

    SA_KEY_SPACE           = 32,
    SA_KEY_APOSTROPHE      = 39,   /* ' */
    SA_KEY_COMMA           = 44,   /* , */
    SA_KEY_MINUS           = 45,   /* - */
    SA_KEY_PERIOD          = 46,   /* . */
    SA_KEY_SLASH           = 47,   /* / */

    SA_KEY_0               = 48,
    SA_KEY_1               = 49,
    SA_KEY_2               = 50,
    SA_KEY_3               = 51,
    SA_KEY_4               = 52,
    SA_KEY_5               = 53,
    SA_KEY_6               = 54,
    SA_KEY_7               = 55,
    SA_KEY_8               = 56,
    SA_KEY_9               = 57,

    SA_KEY_SEMICOLON       = 59,   /* ; */
    SA_KEY_EQUAL           = 61,   /* = */

    SA_KEY_A               = 65,
    SA_KEY_B               = 66,
    SA_KEY_C               = 67,
    SA_KEY_D               = 68,
    SA_KEY_E               = 69,
    SA_KEY_F               = 70,
    SA_KEY_G               = 71,
    SA_KEY_H               = 72,
    SA_KEY_I               = 73,
    SA_KEY_J               = 74,
    SA_KEY_K               = 75,
    SA_KEY_L               = 76,
    SA_KEY_M               = 77,
    SA_KEY_N               = 78,
    SA_KEY_O               = 79,
    SA_KEY_P               = 80,
    SA_KEY_Q               = 81,
    SA_KEY_R               = 82,
    SA_KEY_S               = 83,
    SA_KEY_T               = 84,
    SA_KEY_U               = 85,
    SA_KEY_V               = 86,
    SA_KEY_W               = 87,
    SA_KEY_X               = 88,
    SA_KEY_Y               = 89,
    SA_KEY_Z               = 90,

    SA_KEY_LEFT_BRACKET    = 91,   /* [ */
    SA_KEY_BACKSLASH       = 92,   /* \ */
    SA_KEY_RIGHT_BRACKET   = 93,   /* ] */
    SA_KEY_GRAVE_ACCENT    = 96,   /* ` */

    SA_KEY_WORLD_1         = 161,  /* non-US #1 */
    SA_KEY_WORLD_2         = 162,  /* non-US #2 */

    SA_KEY_ESCAPE          = 256,
    SA_KEY_ENTER           = 257,
    SA_KEY_TAB             = 258,
    SA_KEY_BACKSPACE       = 259,
    SA_KEY_INSERT          = 260,
    SA_KEY_DELETE          = 261,
    SA_KEY_RIGHT           = 262,
    SA_KEY_LEFT            = 263,
    SA_KEY_DOWN            = 264,
    SA_KEY_UP              = 265,

    SA_KEY_PAGE_UP         = 266,
    SA_KEY_PAGE_DOWN       = 267,
    SA_KEY_HOME            = 268,
    SA_KEY_END             = 269,

    SA_KEY_CAPS_LOCK       = 280,
    SA_KEY_SCROLL_LOCK     = 281,
    SA_KEY_NUM_LOCK        = 282,
    SA_KEY_PRINT_SCREEN    = 283,
    SA_KEY_PAUSE           = 284,

    SA_KEY_F1              = 290,
    SA_KEY_F2              = 291,
    SA_KEY_F3              = 292,
    SA_KEY_F4              = 293,
    SA_KEY_F5              = 294,
    SA_KEY_F6              = 295,
    SA_KEY_F7              = 296,
    SA_KEY_F8              = 297,
    SA_KEY_F9              = 298,
    SA_KEY_F10             = 299,
    SA_KEY_F11             = 300,
    SA_KEY_F12             = 301,
    SA_KEY_F13             = 302,
    SA_KEY_F14             = 303,
    SA_KEY_F15             = 304,
    SA_KEY_F16             = 305,
    SA_KEY_F17             = 306,
    SA_KEY_F18             = 307,
    SA_KEY_F19             = 308,
    SA_KEY_F20             = 309,
    SA_KEY_F21             = 310,
    SA_KEY_F22             = 311,
    SA_KEY_F23             = 312,
    SA_KEY_F24             = 313,
    SA_KEY_F25             = 314,

    /* Keypad */
    SA_KEY_KP_0            = 320,
    SA_KEY_KP_1            = 321,
    SA_KEY_KP_2            = 322,
    SA_KEY_KP_3            = 323,
    SA_KEY_KP_4            = 324,
    SA_KEY_KP_5            = 325,
    SA_KEY_KP_6            = 326,
    SA_KEY_KP_7            = 327,
    SA_KEY_KP_8            = 328,
    SA_KEY_KP_9            = 329,
    SA_KEY_KP_DECIMAL      = 330,
    SA_KEY_KP_DIVIDE       = 331,
    SA_KEY_KP_MULTIPLY     = 332,
    SA_KEY_KP_SUBTRACT     = 333,
    SA_KEY_KP_ADD          = 334,
    SA_KEY_KP_ENTER        = 335,
    SA_KEY_KP_EQUAL        = 336,

    /* Modifiers */
    SA_KEY_LEFT_SHIFT      = 340,
    SA_KEY_LEFT_CONTROL    = 341,
    SA_KEY_LEFT_ALT        = 342,
    SA_KEY_LEFT_SUPER      = 343,
    SA_KEY_RIGHT_SHIFT     = 344,
    SA_KEY_RIGHT_CONTROL   = 345,
    SA_KEY_RIGHT_ALT       = 346,
    SA_KEY_RIGHT_SUPER     = 347,
    SA_KEY_MENU            = 348,

    SA_KEY_LAST            = 348
} SA_Key;








typedef enum SA_MouseButton
{
    SA_MOUSE_BUTTON_UNKNOWN = -1,

    SA_MOUSE_BUTTON_1       = 0,
    SA_MOUSE_BUTTON_2       = 1,
    SA_MOUSE_BUTTON_3       = 2,
    SA_MOUSE_BUTTON_4       = 3,
    SA_MOUSE_BUTTON_5       = 4,
    SA_MOUSE_BUTTON_6       = 5,
    SA_MOUSE_BUTTON_7       = 6,
    SA_MOUSE_BUTTON_8       = 7,

    SA_MOUSE_BUTTON_LAST    = 7,

    // Common aliases (most games only use these 3)
    SA_MOUSE_BUTTON_LEFT    = 0,
    SA_MOUSE_BUTTON_RIGHT   = 1,
    SA_MOUSE_BUTTON_MIDDLE  = 2,

    // You can also use SA_MOUSE_BUTTON_4 … SA_MOUSE_BUTTON_8 for extra buttons
} SA_MouseButton;





typedef enum SA_MouseWheel
{
    SA_MOUSE_WHEEL_NONE = 0,
    SA_MOUSE_WHEEL_UP   = 1,
    SA_MOUSE_WHEEL_DOWN = -1
} SA_MouseWheel;




typedef struct SA_Event
{
    SA_EventType type;

    union
    {
        struct { SA_Key key; } key;
        struct { double x, y; } mouseMove;
        struct { SA_MouseButton button; } mouseButton;
        struct { double offset; } scroll;
        struct { int width, height; } resize;
    };

} SA_Event;




/* window type declarations */
typedef struct SA_Window SA_Window;
typedef struct GLFWwindow GLFWwindow;



SA_API
void SA_PushEvent(SA_Event e);



SA_API
int SA_PollEvent(SA_Event* out);



void SA_SetWindowEventCallBacks_I(GLFWwindow* window);









// ================================================================
// Continuous Input (Raylib / SDL / Godot style)
// Call SA_UpdateInput() once per frame!
// ================================================================





SA_API void SA_UpdateInput(void);
SA_API void SA_ProcessEvent(const SA_Event* e);      // ← NEW: Feed one event into the state system

SA_API SA_Bool SA_IsKeyDown(SA_Key key);
SA_API SA_Bool SA_IsKeyPressed(SA_Key key);     // true only this frame
SA_API SA_Bool SA_IsKeyReleased(SA_Key key);

SA_API SA_Bool SA_IsMouseButtonDown(SA_MouseButton button);
SA_API SA_Bool SA_IsMouseButtonPressed(SA_MouseButton button);
SA_API SA_Bool SA_IsMouseButtonReleased(SA_MouseButton button);

SA_API double SA_GetMouseX(void);
SA_API double SA_GetMouseY(void);
SA_API double SA_GetMouseWheel(void);        // last scroll delta this frame













SA_API void SA_HandleEvents(SA_EventCallback callback);