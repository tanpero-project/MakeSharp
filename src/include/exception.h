#ifndef _SRC_INCLUDE_EXCEPTION_H_
#define _SRC_INCLUDE_EXCEPTION_H_

#include "errno.h"
#include <exception>

class ProfileException : std::exception
{
public:
	ProfileException(int _errno) : m_errno(_errno) {}

	int type()
	{
		return m_errno;
	}

private:
	int m_errno;
};


#endif // !_SRC_INCLUDE_EXCEPTION_H_

