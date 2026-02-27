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




int main(int argc, char **argv)
{
    SA_Start(SA_RESIZABLE);

    SA_OpenWindow(800, 600, "title");

    SA_Texture* tex = SA_LoadTexture("test.PNG");

    SA_Rect rect = {50, 100, 200, 200};


    while (SA_Play())
    {
        SA_HandleEvents(MyEventHandler);
        

        if (SA_IsKeyPressed(SA_KEY_A))      // pressed this exact frame
            rect.x -= 10;

        if (SA_IsKeyPressed(SA_KEY_F))      // pressed this exact frame
            SA_EnableFullScreen();
        
        SA_BeginDrawing();


        // SA_DrawTexture(tex, &rect);
        SA_DrawTextureEx(tex, &rect, SA_BABY_BLUE);
        SA_DrawRectLines(&rect, SA_RED);
        // SA_DrawRect(&rect, SA_RED);


        SA_EndDrawing();
    }

    SA_UnloadTexture(tex);
    SA_CloseWindow();
}