#include <stdio.h>

#include "sa.h"






void MyEventHandler(SA_Window* window, const SA_Event* e)
{
    switch (e->type)
    {
        case SA_EVENT_KEY_DOWN:
            printf("User callback: Key DOWN %d\n", e->key.key);
            break;

        case SA_EVENT_MOUSE_BUTTON_DOWN:
            if (e->mouseButton.button == SA_MOUSE_BUTTON_LEFT)
                printf("User callback: LEFT CLICK!\n");
            break;

        case SA_EVENT_MOUSE_SCROLL:
            printf("User callback: Scroll %.1f\n", e->scroll.offset);
            break;


        // add whatever you want
    }
}


int main(SA_MULTIPLE_ARGS)
{
    SA_Start(0);

    SA_OpenWindow(800, 600, "title");

    SA_Texture* tex = SA_LoadTexture("test.PNG");



    float speed = 180.0f;


    SA_SetEventTo(MyEventHandler);

    // SA_Event event;
    while (SA_Play())
    {

        printf("Is FullScreen?: %d", SA_IsFullScreen());

        float DeltaTime = SA_GetDeltaTime();


        // Horizontal
        float vx = 0.0f;
        float vy = 0.0f;





        SA_BeginDrawing();


        SA_EndDrawing();

    }

    SA_UnloadTexture(tex);
    SA_CloseWindow();
}