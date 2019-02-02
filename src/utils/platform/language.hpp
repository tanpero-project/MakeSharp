#ifndef _SRC_UTILS_PLATFORM_COMPILER_H_
#define _SRC_UTILS_PLATFORM_COMPILER_H_

#define C89 0
#define C94 1
#define C99 2
#define C11 3
#define CPP98 4
#define CPP11 5
#define CPP14 6
#define CPPCLI 7
#define ECPP 8

#ifdef __embedded_cplusplus
#	define EMBEDDED
#endif

// Refered from https://sourceforge.net/p/predef/wiki/Standards/
#ifdef __cplusplus
#	if (__cplusplus >= 199707L && __cplusplus < 201103L)
#		define LANGUAGE CPP98
#	elif(__cplusplus >= 201103L && __cplusplus <= 201402L)
#		define LANGUAGE CPP11
#	elif (__cplusplus >= 201402L)
#		define LANGUAGE CPP14
#	endif
#	ifdef EMBEDDED
#		undef LANGUAGE
#		define LANGUAGE ECPP
#	endif
#else
#	ifdef __STDC__
#		define LANGUAGE C89
#	elif defined(__STDC_VERSION__)
#		if (__STDC_VERSION__ >= 199409L && __STDC_VERSION__ < 199901L)
#			define LANGUAGE C94
#		elif(__STDC_VERSION__ >= 199901L && __STDC_VERSION__ <= 201112L)
#			define LANGUAGE C99
#		elif (__STDC_VERSION__ >= 201112L)
#			define LANGUAGE C11
#		endif
#	else
#		#error "Unsupported language type!"
#	endif
#endif

#include <iostream>
using namespace std;

int main()
{
	cout << 4 << endl;
	return 0;
}


#endif // !_SRC_UTILS_PLATFORM_COMPILER_H_

