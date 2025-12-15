#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <SDL3/SDL.h>

struct label
{
    std::string text;
    int font_size;
    SDL_FColor color;
    SDL_Point position;
};

#endif