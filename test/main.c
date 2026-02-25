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
    SA_Start(SA_FLAG_WINDOW_RESIZABLE);

    SA_OpenWindow(800, 600, "title");

    SA_Texture* tex = SA_LoadTexture("test/spec.PNG");

    SA_Rect rect = {50, 100, 50, 50};

    SA_Font* font =  SA_LoadFont("FORTE.TTF", 32.0f);   // change path if needed

    SA_SetDefaultFont(font);

    // SA_SetBackgroundColor(SA_BABY_BLUE);
    // SA_SetTargetFPS(240);

    SA_Sound *soft;

    soft = SA_SoundLoad("soft.wav");


    while (SA_Play())
    {
        SA_RunEventCallback(MyEventHandler);
        

        if (SA_IsKeyPressed(SA_KEY_A))      // pressed this exact frame
            rect.x -= 10;

        SA_BeginDrawing();

        SA_DrawTexture(tex, rect.x, rect.y, rect.width, rect.height);

        // In render loop:
        SA_DrawText("This is SageAura! Text works now :)", 50.0f, 250.0f, SA_LIME);

        SA_DrawLine(10, 10, 100, 150, SA_ColorFromHex("#0055FFFF"));

        SA_SoundPlay(soft);



        SA_EndDrawing();
    }
// 
        // At shutdown:
    // SA_UnLoadFont(font); // optional engine will clear the default font registered fonts



    SA_UnLoadTexture(tex);

    SA_SoundUnload(soft);
    SA_CloseWindow();
}