#include <stdio.h>

#include "raylib.h"
#include "load_media.h"

void load_textures(Assets *a, Texture2D *sprite, const char* filepath)
{
    // texture loading and error checks
    *sprite = LoadTexture(filepath);
    if(sprite->id == 0) {
        printf("Failed to load texture from path: %s\n", filepath);
    }
}

void load_audio(Assets *a, Music *audio, const char* filepath)
{
    *audio = LoadMusicStream(filepath);
    if(audio->ctxData == NULL) {
        printf("Failed to load audio from path: %s\n", filepath);
    }
}