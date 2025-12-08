#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <SDL3/SDL.h>

struct label
{
    std::string text;
    int font_size;
    SDL_Color color;
};

#endif