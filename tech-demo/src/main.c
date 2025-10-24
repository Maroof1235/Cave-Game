#include "raylib.h"


int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;

    // initialise window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cave Game");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // update things here

        // draw
        BeginDrawing();

        ClearBackground(DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}