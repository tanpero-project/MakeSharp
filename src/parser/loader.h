#ifndef _SRC_PARSER_LOADER_H_
#define _SRC_PARSER_LOADER_H_

#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
namespace MakeSharp
{
	using json = nlohmann::json;
	namespace Parser
	{
		namespace Loader
		{
			json getJSON(char file[])
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

			struct MetaData
			{
				std::string name;
				union Author
				{
					std::string authorName;
					std::vector<std::string> authorName;
				};
				Author author;
				std::string version;
				std::string description;
				std::string license;
				std::string repoType;
				std::string repoUrl;
			};

			MetaData getMetaDatas(json j)
			{
			    MetaData metadata = {
					j["name"],
					j["author"],
					j["version"],
					j["description"],
					j["license"],
					j["repository"]["type"],
					j["repository"]["url"],
			    };
			    return metadata;
			}
		}
		



		return 0;
	}

};

#endif // !_SRC_PARSER_LOADER_H_
