#include <fstream>
#include <iostream>
#include <text.h>

using json = nlohmann::ordered_json;

namespace text
{
    font loaded_font;

    void load_font(const std::string &path)
    {
        std::ifstream input(path);
        json data = json::parse(input);
        // std::cout << "loaded font: " << data.dump() << std::endl;

        loaded_font = data.get<font>();
    }
}
