#ifndef _SRC_PARSER_LOADER_H_
#define _SRC_PARSER_LOADER_H_

#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace MakeSharp
{
    using json = nlohmann::json;
    namespace parser
    {
        namespace loader
        {
            json getJSON(std::string)
            {
                std::ifstream t;
                t.open(file);
                t.seekg(0, ios::end);
                length = t.tellg();
                t.seekg(0, ios::beg);
                char* buffer = new char[length];
                t.read(buffer, length);
                t.close();
                return json::parse(buffer);
            }
        }
    }
};

#endif // !_SRC_PARSER_LOADER_H_
