#include <fstream>
#include <iostream>
#include <font.h>

using json = nlohmann::json;

namespace font
{
    std::unordered_map<char, std::vector<polyline>> character_table;

    void load(const std::string &path)
    {
        std::ifstream input(path);
        json data;
        input >> data;
        std::vector<character> mapping = data.get<std::vector<character>>();

        for (auto &c : mapping)
        {
            character_table[c.code] = c.sections;
        }
    }
}
