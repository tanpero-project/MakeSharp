#ifndef _SRC_PARSER_PARSER_H_
#define _SRC_PARSER_PARSER_H_

#include "metadata.h"
#include "profile.h"
#include "source.h"

namespace MakeSharp
{
	namespace parser
	{
		using stringList = std::vector<std::string>;

		class Profile
		{
		public:
			Profile(std::string file)
			{
				m_profile = profile::Profile(file);
			}

			MetaDataGetter getMetaDatas()
			{
				MetaDataGetter m(m_profile.getMetaDatas());
				return m;
			}

			stringList getIncludes()
			{
				return source::getIncludes(m_profile.getIncludes());
			}

			stringList getSources()
			{
				return source::getSources(m_profile.getSources());
			}

		private:
			profile::Profile m_profile;
		};

	}
}

#endif // !_SRC_PARSER_PARSER_H_
