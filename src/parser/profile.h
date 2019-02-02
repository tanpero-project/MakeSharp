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

			struct SourceObject
			{
				std::vector<std::string> includes;
				std::vector<std::string> sources;
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
			
			SourceObject getSourceObjects(json j)
			{
				json includes = j["include"];
				std::vector<std::string> includePaths;

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
						// ������ַ�����ֱ�ӵ���ͷ�ļ�·��
						std::string path = it->get<std::string>();
						includePaths.push_back(i);
						
						// ����ƽ̨�����һ���ַ����ж���·��Ϊ�Ƿ�/Ŀ¼/�ļ�����

					}
					else if (it->is_object())
					{
						for (json::iterator it2 = it->begin(); it2 != it->end(); ++it2)
						{
							std::string dirName = it.key();

							if (it2->is_string())
							{
								// ������ַ�����ֱ�ӵ���ͷ�ļ�·��
								std::string path = it->get<std::string>();
								includePaths.push_back(i);

								// ����ƽ̨�����һ���ַ����ж���·��Ϊ�Ƿ�/�ļ�������ʱ���������Ŀ¼����
							}
							else if (it2->is_array)
							{
								// ��������飬��ô��������Ϊ������ļ���
								for (json::iterator file = it2->begin(); file != it2->end(); ++file)
								{
									if (file->is_string)
									{
										// �����ļ�·����Ŀ¼ + �ļ���
										includePaths.push_back(dirName + file->get<std::string>());
									}
									else
									{
										// �Ƿ�ֵ
										// throw 
									}
								}
							}
							else
							{
								// �Ƿ�ֵ
								//throw;
							}
						}
					}
				}
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
			private:
				json object;
			};

		}
	}
}


#endif // !_SRC_PARSER_PROFILE_H_
