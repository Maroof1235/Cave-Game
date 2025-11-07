#include "raylib.h"

typedef struct {
    Texture2D player_tex_left;
    Texture2D player_tex_right;
    Texture2D player_current_tex;
    Music jump_sfx;
    float jump_vol;
} Assets;


void load_media(Assets *a);