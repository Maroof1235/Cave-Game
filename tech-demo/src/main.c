#include "raylib.h"

typedef struct {
    Vector2 player_size;
    Vector2 player_pos;
    Color player_colour;
    bool jump;
    float jump_start;
    float velocity;
    float downward_force;
    Texture2D player_tex;
} Player;

void jump(Player* p);

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

int main(void)
{
    // initialise window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cave Game");

    Player p;

    p.player_tex = LoadTexture("../../tech-demo/assets/tilesets/characterleft.png");

    p.player_size.x = (float)64;
    p.player_size.y = (float)64;

    p.player_pos.x = (float)SCREEN_WIDTH/2;
    p.player_pos.y = SCREEN_HEIGHT - p.player_size.y;

    p.player_colour = BLUE;

    SetTargetFPS(60);

    // main game loop
    while(!WindowShouldClose())
    {
        // update things here

        if (IsKeyDown(KEY_A)) {
            p.player_pos.x -= 9.0f;
            p.player_tex = LoadTexture("../../tech-demo/assets/tilesets/characterleft.png");
        }
        if (IsKeyDown(KEY_D)) {
            p.player_pos.x += 9.0f;
            p.player_tex = LoadTexture("../../tech-demo/assets/tilesets/characterright.png");
        }

        jump(&p);

        // draw
        BeginDrawing();
  
        ClearBackground(DARKGRAY);
         
        DrawText("Press A and D to move left and right", 10, 10, 50, RED);
        DrawText("Press space bar to jump", 10, 60, 50, RED);

        DrawTextureEx(p.player_tex, p.player_pos, 0.0f, 2.0f, WHITE);

        // player with no texture
        //DrawRectangleV(p.player_pos, p.player_size, p.player_colour);

        EndDrawing();
    }

    // cleanup resources
    UnloadTexture(p.player_tex);
    CloseWindow();

    return 0;
}


void jump(Player* p)
{
    // when airborne, set fall speed applied
    // first apply upward velocity (eg 5)
    // add 1 unit of downward acceleration per frame
    // next frame upward velocity is 4 - rising slower
    // repeat until downward acceleration is greater than upward
    // character falls ffaster with each frame
    // character lands when downward velocity = initial upward velocity

    int difference = 0;

    // TODO:
        // prevent start and stopping of horizontal movement in the air
    //////////////////////////////////////////////////////////////////////
    
    if (IsKeyPressed(KEY_SPACE)) {
        // ground check
        if (p->player_pos.y >= SCREEN_HEIGHT - p->player_size.y) {
            p->velocity = 175.0f;
            p->downward_force = 8.0f;
            p->jump_start = p->player_pos.y;
            p->jump = true;
        }
    }

    if (IsKeyDown(KEY_SPACE)) {
         p->jump = true;
    }

    if(p->jump == true) {
        
        p->velocity -= p->downward_force;

        // retrieves how much player jumped
        difference = p->jump_start - p->player_pos.y;

        // checks if max height reached
        if(((difference <= 280) && p->velocity >= 0) || p->velocity <= 0) {
            // the actual jump
            p->player_pos.y -= (p->velocity) * 0.15;
        }

        // ground check
        if (p->player_pos.y >= SCREEN_HEIGHT - p->player_size.y) {
            p->jump = false;
            p->player_pos.y = SCREEN_HEIGHT - p->player_size.y;
        }

    }

}