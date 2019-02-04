#include <iostream>
#include <fstream>
#include <cstdio>

#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main()
{
    cout << "Hello\n";

    ifstream t;

    cout << "1\n";

    int length;

    t.open("data1.json");
    t.seekg(0, ios::end);
    length = t.tellg();
    t.seekg(0, ios::beg);
    char* buffer = new char[length];
    t.read(buffer, length);
    t.close();
    printf("buffer:\n");
    printf(buffer);
    // auto j = json::parse("{\"Hello\": \"world\"}");
    //printf(buffer);
   // auto j = json::parse(buffer);














    /*char* s = R"(
    {
        "happy": true,
    "pi": 3.141592
    }
    )";
    json j = json::parse(s);*/
    json j = json::parse(buffer);

    cout << "Begin!\n";

    for (auto& [key, value] : j.items())
    {  
    cout << key << ": " << value << "\n";
    }
    
    cout << "End!\n";

    return 0;
}

