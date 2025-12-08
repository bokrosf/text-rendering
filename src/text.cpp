#include <fstream>
#include <iostream>
#include <text.h>

using json = nlohmann::json;

namespace text
{
    font loaded_font;

    void load_font(const std::string &path)
    {
        std::ifstream input(path);
        json data;
        input >> data;

        loaded_font = data.get<font>();
    }
}
