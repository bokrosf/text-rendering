#include <fstream>
#include <iostream>
#include <text.h>

using json = nlohmann::ordered_json;

namespace text
{
    font load_font(const std::string &path)
    {
        std::ifstream input(path);
        json data = json::parse(input);
        // std::cout << "loaded font: " << data.dump() << std::endl;

        return data.get<font>();
    }

    void scale_down(font &font, const std::string &path)
    {
        for (auto &s : font.symbols)
        {
            for (auto &v : s.vertices)
            {
                v.x *= (1.0 / 16.0);
                v.y *= (1.0 / 16.0);
            }
        }

        json data = font;
        std::ofstream output(path);
        output << data;
        output.close();
    }
}
