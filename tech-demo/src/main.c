#include "raylib.h"


int main(void)
{
    const int WIDTH = 800;
    const int HEIGHT = 800;

    // initialise window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Cave Game");




    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // update things here
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        if(IsWindowResized)
        {
            SCREEN_WIDTH = GetScreenWidth();
            SCREEN_HEIGHT = GetScreenHeight();
        }

        // draw
        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,20 , 20, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}