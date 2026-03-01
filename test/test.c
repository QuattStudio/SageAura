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
    SA_Start(SA_RESIZABLE);

    SA_OpenWindow(800, 600, "title");

    SA_Texture* tex = SA_LoadTexture("test.PNG");


    SA_Entity player = SA_SpawnEntity();
    SA_Vec2 pos = {50.0f, 100.0f};
    SA_Sizei PlayerSize = {200, 200};

    SA_EntitySetPosition(player, pos.x, pos.y);
    SA_EntitySetVelocity(player, 0.0f, 0.0f);

    SA_EntityGiveSprite(
        player, tex, SA_RECT(pos.x, pos.y, PlayerSize.width, PlayerSize.height)
    );


    float speed = 180.0f;


    SA_SetEventTo(MyEventHandler);

    // SA_Event event;
    while (SA_Play())
    {

        float DeltaTime = SA_GetDeltaTime();


        // Horizontal
        float vx = 0.0f;
        float vy = 0.0f;

        if (SA_IsKeyDown(SA_KEY_A) || SA_IsKeyDown(SA_KEY_LEFT))  vx = -speed;
        if (SA_IsKeyDown(SA_KEY_D) || SA_IsKeyDown(SA_KEY_RIGHT)) vx = +speed;
        if (SA_IsKeyDown(SA_KEY_W) || SA_IsKeyDown(SA_KEY_UP))    vy = -speed;
        if (SA_IsKeyDown(SA_KEY_S) || SA_IsKeyDown(SA_KEY_DOWN))  vy = +speed;



        SA_EntitySetVelocity(player, vx, vy);
        SA_EntitiesUpdate(DeltaTime);


        SA_BeginDrawing();

        SA_DrawAllSprites();

        SA_EndDrawing();

    }

    SA_UnloadTexture(tex);
    SA_CloseWindow();
}