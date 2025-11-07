#include <stdio.h>

#include "raylib.h"
#include "load_media.h"

void load_media(Assets *a)
{

    // texture loading and error checks
    a->player_tex_right = LoadTexture("../../tech-demo/assets/tilesets/characterright.png");
    if(a->player_tex_right.id == 0) {
        printf("Failed to load texture from path: ../../tech-demo/assets/tilesets/characterright.png\n");
    }

    a->player_tex_left = LoadTexture("../../tech-demo/assets/tilesets/characterleft.png");
    if(a->player_tex_left.id == 0) {
        printf("Failed to load texture from path: ../../tech-demo/assets/tilesets/characterleft.png\n");
    }

    a->player_current_tex = LoadTexture("../../tech-demo/assets/tilesets/characterright.png");
    if(a->player_current_tex.id == 0) {
        printf("Failed to load texture from path: ../../tech-demo/assets/tilesets/characterright.png\n");
    }

    // audio loading and error checks
    a->jump_sfx = LoadMusicStream("../../tech-demo/assets/sounds/bfxr_sounds/Jump.wav");
    a->jump_sfx.looping = false;
    a->jump_vol = 0.1f;
    if(a->jump_sfx.ctxData == NULL) {
        printf("Failed to load audio from path: ../../tech-demo/assets/sounds/bfxr_sounds/Jump.wav\n");
    }
     
}