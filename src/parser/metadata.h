#ifndef _SRC_PARSER_METADATA_H_
#define _SRC_PARSER_METADATA_H_

#include "profile.h"

namespace MakeSharp
{
    namespace parser
    {
        using json = nlohmann::json;

        class MetaDataGetter
        {
        public:
            class Repository
            {
            public:
				Repository();
                Repository(std::string, std::string);
                std::string url(void);
                std::string type(void);
            private:
                std::string m_url, m_type;
            };

            using Author = profile::MetaData::Author;

        public:
			MetaDataGetter();

			//MetaDataGetter(profile::MetaData metadata);
            MetaDataGetter(const profile::MetaData& metadata);
			
			MetaDataGetter(const MetaDataGetter&);
            ~MetaDataGetter();

			MetaDataGetter& operator=(const MetaDataGetter& m);

            std::string name(void) const;
            Author author(void) const;
            std::string version(void) const;
            std::string description(void) const;
            Repository repository(void) const;
            std::string license(void) const;

        private:
            std::string m_name, m_version,
                m_description, m_license;
            Author m_author;
            Repository m_repository;
        };
    }
}

#endif // !_SRC_PARSER_METADATA_H_
