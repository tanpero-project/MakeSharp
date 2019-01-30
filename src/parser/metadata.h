#ifndef _SRC_PARSER_METADATA_H_
#define _SRC_PARSER_METADATA_H_

#include "loader.h"

namespace MakeSharp
{
	namespace Parser
	{
		using json = nlohmann::json;

		class MetaDataGetter
		{
		public:
			class Repository
			{
			public:
				Repository(std::string, std::string);
				std::string url(void);
				std::string type(void);
			private:
				std::string m_url, m_type;
			};

			using Author = Loader::MetaData::Author;

		public:
			MetaData(Loader::MetaData metadata);
			~MetaData();

			std::string name(void);
			Author author(void);
			std::string version(void);
			std::string description(void);
			Repository repository(void);
			std::string license(void);

		private:
			std::string m_name, m_version,
				m_description, m_license;
			Author m_author;
			Repository m_repository;
		};
	}
}

#endif // !_SRC_PARSER_METADATA_H_