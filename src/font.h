#ifndef FONT_H
#define FONT_H

#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>

namespace font
{
    struct position
    {
        float x;
        float y;
    };

    using polyline = std::vector<position>;

    struct character
    {
        char code;
        std::vector<polyline> sections;
    };

    extern std::unordered_map<char, std::vector<polyline>> character_table;

    void load(const std::string &path);

    // Defines serialization/deserialization functions.
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(position, x, y)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(character, code, sections)
}

#endif
