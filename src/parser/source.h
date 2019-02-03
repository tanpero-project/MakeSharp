#ifndef _SRC_PARSER_SOURCE_H_
#define _SRC_PARSER_SOURCE_H_

#include "../include/exception.h"
#include "../utils/platform.h"
#include "../utils/visitpath.h"
#include "profile.h"

namespace MakeSharp
{
    namespace parser
    {
        namespace source
        {
			std::vector<std::string> getIncludes(json includes)
			{
				std::vector<std::string> includePaths;
				bool isDir;

				/*
				* "include": [
				*      "src/include/",
				*      "3rd_party/goslin/lang.hpp",
				*     {
				*          "include/": "first.h"
				*      },
				*      {
				*          "ndk/": "head.hpp",
				*          "base/include/": ["one.h", "two.h"]
				*      }
				* ]
				*/

				for (json::iterator it = includes.begin(); it != includes.end(); ++it)
				{

					if (it->is_string())
					{
						// 如果是字符串，直接当做头文件路径
						std::string path = it->get<std::string>();

						// 根据平台和最后一个字符，判定该路径为非法/目录/文件名√
						if (path.at(path.size() - 1) == '\\')
						{
							// 非 DOS/Windows 平台下不允许使用 '\' 作为分隔符
							if (!profile::isDOSStyle)
							{
								throw ProfileException(INVALID_SOURCE_PATH);
							}
							else
							{
								isDir = true;
							}
						}
						else if (path.at(path.size() - 1) == '/')
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
							std::vector<std::string> paths = utils::visitpath::filterHeaderFilePaths(path);
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
								if ((fileName.at(fileName.size() - 1) == '\\')
									|| fileName.at(fileName.size() - 1) == '\\')
								{
									throw ProfileException(INVALID_SOURCE_PATH);
								}
								else
								{
									includePaths.push_back(dirName + fileName);
								}
							}
							else if (it2->is_array())
							{
								// 如果是数组，那么数组中项为具体的文件名
								for (json::iterator file = it2->begin(); file != it2->end(); ++file)
								{
									if (file->is_string())
									{
										// 存入文件路径：目录 + 文件名
										includePaths.push_back(dirName + file->get<std::string>());
									}
									else
									{
										// 非法值
										throw ProfileException(INVALID_VALUE_TYPE);
									}
								}
							}
							else
							{
								// 非法值
								throw ProfileException(INVALID_VALUE_TYPE);
							}
						}
					}
					else
					{
						// 非法值
						throw ProfileException(INVALID_VALUE_TYPE);
					}
				}

				return includePaths;
			}

			std::vector<std::string> getSources(json sources)
			{
				bool isDir;

				/*
				* "source": ["aaa.cpp", "base.mm", "src/"]
				*/
				std::vector<std::string> sourcePaths;

				if (!sources.is_array())
				{
					throw ProfileException(INVALID_VALUE_TYPE);
				}

				for (auto index : sources)
				//for (auto path = sources.begin(); path != sources.end(); ++path)
				{
					std::string path = index.get<std::string>();

					// 根据平台和最后一个字符，判定该路径为非法/目录/文件名√
					if (path.at(path.size() - 1) == '\\')
					{
						// 非 DOS/Windows 平台下不允许使用 '\' 作为分隔符
						if (!profile::isDOSStyle)
						{
							throw ProfileException(INVALID_SOURCE_PATH);
						}
						else
						{
							isDir = true;
						}
					}
					else if (path.at(path.size() - 1) == '/')
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
						std::vector<std::string> paths = utils::visitpath::filterSourceFilePaths(path);
						sourcePaths.insert(sourcePaths.end(), paths.begin(), paths.end());
					}
				}

				return sourcePaths;
			}

        }
    }
}


#endif // !_SRC_PARSER_SOURCE_H_
