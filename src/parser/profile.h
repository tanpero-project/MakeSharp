#ifndef _SRC_PARSER_PROFILE_H_
#define _SRC_PARSER_PROFILE_H_

#include "loader.h"

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

            /* struct SourceObject
            {
                std::vector<std::string> includes;
                std::vector<std::string> sources;
            }; */

            MetaData getProfileMetaDatas(json j)
            {
                MetaData metadata {
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
                /*Profile(std::string path) {
                    object = loader::getJSON(path);
                }*/

				Profile& operator=(std::string path)
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
