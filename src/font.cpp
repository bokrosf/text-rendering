#include <fstream>
#include <iostream>
#include <font.h>

using json = nlohmann::json;

namespace font
{
    std::vector<polyline> character_mapping[];

    void load(const std::string &path)
    {
        std::ifstream input(path);
        json data;
        input >> data;
        std::vector<character> mapping = data.get<std::vector<character>>();

        for (auto &c : mapping)
        {
            character_mapping[c.code] = c.sections;
        }
    }
}
