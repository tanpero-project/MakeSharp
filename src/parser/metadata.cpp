#include "metadata.h"

namespace MakeSharp
{
    namespace parser
    {
        MetaDataGetter::MetaDataGetter(void)
        {
        }

        MetaDataGetter::MetaDataGetter(const profile::MetaData& metadata)
        {
            m_name = metadata.name;
            m_author = metadata.author;
            m_version = metadata.version;
            m_description = metadata.description;
            m_license = metadata.license;
            m_repository = Repository(metadata.repoType, metadata.repoUrl);
        }



        MetaDataGetter::MetaDataGetter(const MetaDataGetter &)
        {
        }

        MetaDataGetter::~MetaDataGetter()
        {
        }

        MetaDataGetter & MetaDataGetter::operator=(const MetaDataGetter & m)
        {
            return static_cast<MetaDataGetter>(m);
        }

        std::string MetaDataGetter::name(void) const
        {
            return m_name;
        }
        MetaDataGetter::Author MetaDataGetter::author(void) const
        {
            return m_author;
        }
        std::string MetaDataGetter::version(void) const
        {
            return m_version;
        }
        std::string MetaDataGetter::description(void) const
        {
            return m_description;
        }
        MetaDataGetter::Repository MetaDataGetter::repository(void) const
        {
            return m_repository;
        }
        std::string MetaDataGetter::license(void) const
        {
            return m_license;
        }

        MetaDataGetter::Repository::Repository()
        {
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
