#include "raylib.h"

typedef struct {
    Vector2 player_size;
    Vector2 player_pos;
    Color player_colour;
} Player;

int main(void)
{
    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 900;

    // initialise window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cave Game");

    Player p;
    p.player_size.x = (float)50;
    p.player_size.y = (float)50;

    p.player_pos.x = (float)SCREEN_WIDTH/2;
    p.player_pos.y = SCREEN_HEIGHT - p.player_size.x;

    p.player_colour = BLUE;

    SetTargetFPS(60);


    // main game loop
    while(!WindowShouldClose())
    {
        // update things here

        if (IsKeyDown(KEY_A))
        {
            p.player_pos.x -= 4.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            p.player_pos.x += 4.0f;
        }

        // draw
        BeginDrawing();
  
        ClearBackground(DARKGRAY);

        DrawRectangleV(p.player_pos, p.player_size, p.player_colour);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}