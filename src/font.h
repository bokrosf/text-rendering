#ifndef FONT_H
#define FONT_H

#include <string_view>
#include <vector>

struct font
{
public:
    struct position
    {
        float x;
        float y;
    };

    using polyline = std::vector<position>;
public:
    char character;
    std::vector<polyline> sections;
};

extern font::polyline character_mapping[127];

void load_font(std::string_view name);

#endif
