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
    SA_Start(0);

    SA_OpenWindow(800, 600, "title");

    SA_Texture* tex = SA_LoadTexture("test/spec.PNG");

    SA_Rect rect = {50, 100, 50, 50};

    SA_Font* font =  SA_CreateFont("FORTE.TTF", 32.0f);   // change path if needed
    SA_Font* font2 = SA_CreateFont("BAUHS93.TTF", 32.0f);   // change path if needed




    while (SA_Play())
    {
        SA_RunEventCallback(MyEventHandler);
        

        if (SA_IsKeyPressed(SA_KEY_A))      // pressed this exact frame
            rect.x -= 10;

        SA_BeginFrame();

        SA_DrawTexture(tex, rect.x, rect.y, rect.width, rect.height);

            // In render loop:
        SA_DrawText(font2, "This is SageAura! Text works now :)", 50.0f, 250.0f, SA_LIME);

        SA_DrawLine(10, 10, 100, 150, SA_ColorFromHex("#0055FFFF"));



        SA_EndFrame();
    }
// 
        // At shutdown:
    SA_UnLoadFont(font);
    SA_UnLoadFont(font2);



    SA_UnLoadTexture(tex);

    SA_CloseWindow();
}