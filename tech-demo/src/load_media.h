#include "raylib.h"

typedef struct {
    Texture2D player_tex_left;
    Texture2D player_tex_right;
    Texture2D player_current_tex;
    Texture2D background;
    Music jump_sfx;
    float jump_vol;
    Music bgm;
    float bgm_vol;
} Assets;


void load_textures(Assets *a, Texture2D *sprite, const char* filepath);
void load_audio(Assets *a, Music *audio, const char* filepath);