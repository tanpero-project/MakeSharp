#ifndef _SRC_UTILS_VISITPATH_H_
#define _SRC_UTILS_VISITPATH_H_

#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include "utilstuff.h"

namespace MakeSharp
{
	namespace utils
	{
		namespace visitpath
		{
			using pathList = std::vector<std::string>;

			void getAllFiles(std::string path, pathList& files)
			{
				long handle = 0;
				std::string tmp;
				struct _finddata_t fileinfo;
				handle = _findfirst(tmp.assign(path).append("/*").c_str(), &fileinfo);
				
				if (handle != -1)
				{
					do
					{
						if ((fileinfo.attrib & _A_SUBDIR))
						{
							if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
							{
								files.push_back(tmp.assign(path).append("/").append(fileinfo.name));
								getAllFiles(tmp.assign(path).append("/").append(fileinfo.name), files);
							}
						}
						else
						{
							files.push_back(tmp.assign(path).append("/").append(fileinfo.name));
						}
					} while (_findnext(handle, &fileinfo) == 0);

					_findclose(handle);
				}
			}

			pathList filterHeaderFilePaths(std::string path)
			{
				pathList fromPath, headers;
				getAllFiles(path, fromPath);
				for (auto it : fromPath)
				{
					if (utilsstuff::isHeaderFile(it))
					{
						headers.push_back(it);
					}
				}
				return headers;
			}

			pathList filterSourceFilePaths(std::string path)
			{
				pathList fromPath, sources;
				getAllFiles(path, fromPath);
				for (auto it : fromPath)
				{
					if (utilsstuff::isSourceFile(it))
					{
						sources.push_back(it);
					}
				}
				return sources;
			}
		}
	}
}

#endif // !_SRC_UTILS_VISITPATH_H_
