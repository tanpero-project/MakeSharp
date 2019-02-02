#ifndef _SRC_PARSER_PROFILE_H_
#define _SRC_PARSER_PROFILE_H_

#include "loader.h"
#include "../include/exception.h"
#include "../utils/platform.h"
#include "../utils/visitpath.h"


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

			MetaData getMetaDatas(json j)
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

			std::vector<std::string> getIncludes(json j)
			{
				json includes = j["include"];
				std::vector<std::string> includePaths;
				bool isDir;

				/*
				* "include": [
				*	  "src/include/",
				*	  "3rd_party/goslin/lang.hpp",
				*     {
				*		  "include/": "first.h"
				*	  },
				*	  {
				*		  "ndk/": "head.hpp",
				*		  "base/include/": ["one.h", "two.h"]
				*	  }
				* ]
				*/

				for (json::iterator it = includes.begin(); it != includes.end(); ++it)
				{

					if (it->is_string())
					{
						// 如果是字符串，直接当做头文件路径
						std::string path = it->get<std::string>();

						// 根据平台和最后一个字符，判定该路径为非法/目录/文件名√
						if (path.at(path.size - 1) == std::string("\\"))
						{
							// 非 DOS/Windows 平台下不允许使用 '\' 作为分隔符
							if (!isDOSStyle)
							{
								throw ProfileException(INVALID_SOURCE_PATH);
							}
							else
							{
								isDir = true;
							}
						}
						else if (path.at(path.size - 1) == std::string("//"))
						{
							isDir = true;
						}
						else
						{
							isDir = false;
							includePaths.push_back(path);
						}

						if (isDir)
						{
							// 将目录下所有符合头文件后缀名的文件路径插入到 includePaths 中
							std::vector<std::string> paths = utils::visitpath::filterHeaderFilePaths(in);
							includePaths.insert(includePaths.end(), paths.begin(), paths.end());
						}

					}
					else if (it->is_object())
					{
						for (json::iterator it2 = it->begin(); it2 != it->end(); ++it2)
						{
							std::string dirName = it2.key();

							if (it2->is_string())
							{
								// 如果是字符串，直接当做头文件名称
								std::string fileName = it2->get<std::string>();

								// 根据平台和最后一个字符，判定该路径为非法/文件名（这时不允许出现目录名）
								if ((fileName.at(path.size - 1) == std::string("\\"))
									|| fileName.at(path.size - 1) == std::string("\\"))
								{
									throw ProfileException(INVALID_SOURCE_PATH);
								}			
								else
								{
									includePaths.push_back(dirName + fileName);
								}
							}
							else if (it2->is_array)
							{
								// 如果是数组，那么数组中项为具体的文件名
								for (json::iterator file = it2->begin(); file != it2->end(); ++file)
								{
									if (file->is_string)
									{
										// 存入文件路径：目录 + 文件名
										includePaths.push_back(dirName + file->get<std::string>());
									}
									else
									{
										// 非法值
										throw ProfileException(INVALID_SOURCE_PATH);
									}
								}
							}
							else
							{
								// 非法值
								throw ProfileException(INVALID_SOURCE_PATH);
							}
						}
					}
					else
					{
						// 非法值
						throw ProfileException(INVALID_SOURCE_PATH);
					}
				}

				return includePaths;
			}

			std::vector<std::string> getSources(json j)
			{
				json sources = j["source"];
				std::vector<std::string> sourcePaths;
				
				for (auto path : sources)
				{
					// 根据平台和最后一个字符，判定该路径为非法/目录/文件名√
					if (path.at(path.size() - 1) == std::string("\\"))
					{
						// 非 DOS/Windows 平台下不允许使用 '\' 作为分隔符
						if (!isDOSStyle)
						{
							throw ProfileException(INVALID_SOURCE_PATH);
						}
						else
						{
							isDir = true;
						}
					}
					else if (path.at(path.size - 1) == std::string("//"))
					{
						isDir = true;
					}
					else
					{
						isDir = false;
						sourcePaths.push_back(path);
					}

					if (isDir)
					{
						// 将目录下所有符合源文件后缀名的文件路径插入到 sourcePaths 中
						std::vector<std::string> paths = utils::visitpath::filterSourceFilePaths(in);
						sourcePaths.insert(sourcePaths.end(), paths.begin(), paths.end());
					}
				}

				return sourcePaths;
			}
			
			class Profile
			{
			public:
				Profile(std::string path) {
					object = loader::getJSON(path);
				}

				MetaData getMetaDatas()
				{
					return getMetaDatas(object);
				}
				
				std::vector<std::string> getIncludes()
				{
					return getIncludes(object);
				}

				std::vector<std::string> getSources()
				{
					return getSources(object);
				}

			private:
				json object;
			};

		}
	}
}

#endif // !_SRC_PARSER_PROFILE_H_
