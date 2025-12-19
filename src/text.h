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

    font load_font(const std::string &path);
    void save_font(const font &font, const std::string &path);
    void scale_down(font &font);

    // Defines serialization/deserialization functions.
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(vertex, x, y)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(symbol, code, vertices)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(font, width, symbols)
}

#endif
