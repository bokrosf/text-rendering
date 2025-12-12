#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace text
{
    struct vertex
    {
        float x;
        float y;
    };

    struct symbol
    {
        char code;
        std::vector<vertex> vertices;
    };

    struct font
    {
        float width;
        std::vector<symbol> symbols;
    };

    extern font loaded_font;

    void load_font(const std::string &path);

    // Defines serialization/deserialization functions.
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(vertex, x, y)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(symbol, code, vertices)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(font, width, symbols)
}

#endif
