#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>

namespace text
{
    struct position
    {
        float x;
        float y;
    };

    using polyline = std::vector<position>;

    struct font
    {
        int width;
        std::unordered_map<char, std::vector<polyline>> table;
    };

    extern font loaded_font;

    void load_font(const std::string &path);

    // Defines serialization/deserialization functions.
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(position, x, y)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(font, width, table)
}

#endif
