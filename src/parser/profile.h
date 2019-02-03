#ifndef _SRC_PARSER_PROFILE_H_
#define _SRC_PARSER_PROFILE_H_

#include "loader.h"
#include "../utils/platform.h"
#include "../include/exception.h"

namespace MakeSharp
{
    namespace parser
    {
        namespace profile
        {
            class Profile;

            using platform = utils::Platform;
            using platformType = utils::platformType;
            bool isDOSStyle = HAS_FLAG(platform::getPlatform, platformType::WINDOWS)
                            || HAS_FLAG(platform::getPlatform, platformType::MSDOS);
            

            class MetaData
            {
			public:
				MetaData() {}
				MetaData(MetaData&) {}
				~MetaData() {}
                std::string name;
                union Author
                {
                    std::string authorName;
                    std::vector<std::string> authorNames;
					Author() {}
					~Author() {}
					Author(const Author&) {}
					Author& operator=(const Author& a) {
						return Author(a);
					}
                };
                Author author;
                std::string version;
                std::string description;
                std::string license;
                std::string repoType;
                std::string repoUrl;
            };

            /* struct SourceObject
            {
                std::vector<std::string> includes;
                std::vector<std::string> sources;
            }; */

            MetaData getProfileMetaDatas(json j)
            {
				MetaData metadata;
				metadata.name = j["name"].get<std::string>();

				json author = j["author"];
				if (author.is_string())
					metadata.author.authorName = author.get<std::string>();
				else if (author.is_array())
					metadata.author.authorNames = author.get<std::vector<std::string>>();
				else
					throw ProfileException(INVALID_VALUE_TYPE);

				metadata.version = j["version"].get<std::string>();
				metadata.description = j["description"].get<std::string>();
				j["license"].get<std::string>();
				j["repository"]["type"].get<std::string>();
				j["repository"]["url"].get<std::string>();
                
                return metadata;
            }

			json getProfileIncludes(json j)
			{
				return j["includes"];
			}

			json getProfileSources(json j)
			{
				return j["source"];
			}

            class Profile
            {
            public:

                Profile() {
					object = nullptr;
                }

				Profile(std::string path)
				{
					object = loader::getJSON(path);
				}

				Profile operator=(std::string path)
				{
					object = loader::getJSON(path);
				}

                MetaData getMetaDatas()
                {
                    return getProfileMetaDatas(object);
                }
                
                json getIncludes()
                {
                    return getProfileIncludes(object["object"]);
                }

                json getSources()
                {
                    return getProfileSources(object["object"]);
                }

            private:
                json object;
            };

        }
    }
}

#endif // !_SRC_PARSER_PROFILE_H_
