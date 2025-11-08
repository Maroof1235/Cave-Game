#include "raylib.h"
#include "load_media.h"

typedef struct {
    Vector2 player_size;
    Vector2 player_pos;
    Color player_colour;
    bool jump;
    bool is_grounded;
    float jump_start;
    float velocity;
    float downward_force;
    float velocity_x;
} Player;

void jump(Player* p, Assets *a);
bool ground_check(Player *p);
void cleanup(Assets *assets);
void player_init(Player *p);
void player_movement(Player *p, Assets *assets);

#define PLAYER_SPEED 9.0f

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

int main(void)
{
    // initialise window and device contexts
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cave Game");

    InitAudioDevice();

    Player p;
    Assets assets = {0};

    // loading textures
    // player sprite
    load_textures(&assets, &assets.player_current_tex, "../../tech-demo/assets/tilesets/characterright.png");
    load_textures(&assets, &assets.player_tex_right, "../../tech-demo/assets/tilesets/characterright.png");
    load_textures(&assets, &assets.player_tex_left, "../../tech-demo/assets/tilesets/characterleft.png");

    // load audio files
    // jump sfx
    load_audio(&assets, &assets.jump_sfx, "../../tech-demo/assets/sounds/bfxr_sounds/Jump.wav");
    assets.jump_sfx.looping = false;
    assets.jump_vol = 0.1f;

    player_init(&p);

    SetTargetFPS(60);

    // main game loop
    while(!WindowShouldClose())
    {
        // update things here
        UpdateMusicStream(assets.jump_sfx);
        player_movement(&p, &assets);

        // draw
        BeginDrawing();
  
        ClearBackground(DARKGRAY);
         
        DrawText("Press A and D to move left and right", 10, 10, 50, RED);
        DrawText("Press space bar to jump", 10, 60, 50, RED);

        DrawTextureEx(assets.player_current_tex, p.player_pos, 0.0f, 2.0f, WHITE);

        // player with no texture
        //DrawRectangleV(p.player_pos, p.player_size, p.player_colour);

        SetMusicVolume(assets.jump_sfx, assets.jump_vol);
        
        EndDrawing();
    }

    // cleanup resources
    cleanup(&assets);


    return 0;
}

void player_init(Player *p)
{
    p->player_size.x = (float)64;
    p->player_size.y = (float)64;

    p->player_pos.x = (float)SCREEN_WIDTH/2;
    p->player_pos.y = SCREEN_HEIGHT - p->player_size.y;

    p->player_colour = BLUE;
}

void jump(Player* p, Assets *a)
{
    // when airborne, set fall speed applied
    // first apply upward velocity (eg 5)
    // add 1 unit of downward acceleration per frame
    // next frame upward velocity is 4 - rising slower
    // repeat until downward acceleration is greater than upward
    // character falls ffaster with each frame
    // character lands when downward velocity = initial upward velocity

    int difference = 0;
    
    if (IsKeyPressed(KEY_SPACE) && p->is_grounded) {
        ground_check(p);
        p->velocity = 175.0f;
        p->downward_force = 8.0f;
        p->jump_start = p->player_pos.y;
        PlayMusicStream(a->jump_sfx);
    }

    if (IsKeyDown(KEY_SPACE)) {
         p->jump = true;
    }

    if((p->jump == true)) {
        
        p->velocity -= p->downward_force;

        // retrieves how much player jumped
        difference = p->jump_start - p->player_pos.y;

        // checks if max height reached
        if(((difference <= 280) && p->velocity >= 0) || p->velocity <= 0) {
            // the actual jump
            p->player_pos.y -= (p->velocity) * 0.15;
        }

        // ground check
        ground_check(p);

    }

}

bool ground_check(Player *p)
{
    if (p->player_pos.y >= SCREEN_HEIGHT - p->player_size.y) {
        p->jump = false;
        p->player_pos.y = SCREEN_HEIGHT - p->player_size.y;
        p->is_grounded = true;
    }
    else {
        p->is_grounded = false;
    }

    return p->is_grounded;
}

void player_movement(Player *p, Assets *assets)
{  
    ground_check(p);

    if(p->is_grounded) {
        if(IsKeyDown(KEY_A)) {
            p->velocity_x = -PLAYER_SPEED;
            
            assets->player_current_tex = assets->player_tex_left;
        }
        else if(IsKeyDown(KEY_D)) {
            p->velocity_x = PLAYER_SPEED;
            assets->player_current_tex = assets->player_tex_right;
        }
        else {
            p->velocity_x = 0;
        }
    }

    p->player_pos.x += p->velocity_x;

    jump(p, assets);
}




void cleanup(Assets *assets)
{
    UnloadTexture(assets->player_tex_right);
    UnloadTexture(assets->player_tex_left);
    CloseAudioDevice();
    CloseWindow();
}