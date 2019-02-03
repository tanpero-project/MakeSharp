#include "metadata.h"

namespace MakeSharp
{
    namespace parser
    {
        MetaDataGetter::MetaDataGetter(loader::MetaData metadata)
        {
            m_name = metadata.name;
            m_author = metadata.author;
            m_version = metadata.version;
            m_description = metadata.description;
            m_license = metadata.license;
            m_repository = Repository(metadata.repoType, metadata.repoUrl)
        }

		MetaDataGetter::~MetaDataGetter()
		{
		}
        std::string MetaDataGetter::name(void)
        {
            return m_name;
        }
        std::string MetaDataGetter::author(void)
        {
            return m_author;
        }
        std::string MetaDataGetter::version(void)
        {
            return m_version;
        }
        std::string MetaDataGetter::description(void)
        {
            return m_description;
        }
        Repository MetaDataGetter::repository(void)
        {
            return m_repository;
        }
        std::string MetaDataGetter::license(void)
        {
            return m_license;
        }
        MetaDataGetter::Repository::Repository(std::string _type, std::string _url)
        {
            m_type = _type;
            m_url = _url;
        }
        std::string MetaDataGetter::Repository::url(void)
        {
            return m_url;
        }
        std::string MetaDataGetter::Repository::type(void)
        {
            return m_type;
        }
    }
}
