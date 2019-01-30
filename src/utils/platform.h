#ifndef _SRC_UTILS_PLATFORM_H_
#define _SRC_UTILS_PLATFORM_H_

// Visual Studio 下定义的这个宏会与 enum 中的名称冲突
#ifdef WIN32
#	undef WIN32
#endif // WIN32

#ifdef WIN64
#	undef WIN64
#endif // WIN64


#define HAS_FLAG(target, flag) ((target & flag) != 0)

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#include <sys/param.h>
#elif defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
	#include <unistd.h>
#endif
namespace MakeSharp{
	namespace utils{
		enum class platformType {
			UNKNOWN = 0,
			POSIX = 1,
			UNIX = 2,
			LINUX = 4,

			AIX = (UNIX | (1 << 4)),
			SOLARIS = (UNIX | (1 << 5)),
			BSD = (UNIX | (1 << 6)),
			FREEBSD = (BSD | (1 << 7)),
			NETBSD = (BSD | (1 << 8)),
			OPENBSD = (BSD | (1 << 9)),

			HPUX = (UNIX | (1 << 10)),
			IRIX = (UNIX | (1 << 11)),

			IOS = (BSD | (1 << 12)),
			OSX = (BSD | (1 << 13)),
			XCODE = (BSD | (1 << 14)), // The iOS simulator in Xcode.
			APPLE = (BSD | (1 << 15)), // Other Apple Platform

			WINDOWS = (1 << 16),
			WIN32 = (WINDOWS | (1 << 17)),
			WIN64 = (WINDOWS | (1 << 18)),
			MSDOS = (1 << 19),
			CYGWIN = (POSIX | WINDOWS | (1 << 20))
		};
		enum class compilerType{
			GNU = 2,
			CLANG = 1 << 2,
			INTEL = 1 << 3,
			HP = 1 << 4,
			IBM = 1 << 5,
			MSVC = 1 << 6,
			PORTLAND = 1 << 7,
			SOLARIS = 1 << 8
		};
		class Platform{
			public:
			static platformType getPlatform(){
				platformType type = platformType::UNKNOWN;
#if defined(_AIX)
				type |= AIX;
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#if defined(BSD)
				type |= platformType::BSD;
	#endif
#elif defined(__hpux)
				type |= platformType::HPUX;
#elif defined(__linux__)
				type |= platformType::LINUX;
#elif defined(__APPLE__) && defined(__MACH__)
	#if TARGET_IPHONE_SIMULATOR  ==  1
				type |= platformType::XCODE;
	#elif TARGET_OS_IPHONE  ==  1
				type |= platformType::IOS;
	#elif TARGET_OS_MAC  ==  1
				type |= platformType::OSX;
	#else
				type |= platformType::APPLE;
	#endif
#elif defined(__sun) && defined(__SVR4)
				type |= platformType::SOLARIS;
#elif defined(__CYGWIN__) && !defined(_WIN32)
				type |= platformType::CYGWIN;
#elif defined(_WIN64)
				type |= platformType::WIN64;
#elif defined(_WIN32)
				type |= platformType::WIN32;
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
				type |= platformType::UNIX;
	#if defined(_POSIX_VERSION)
				type |= platformType::POSIX;
	#endif
#else
				type |= platformType::OTHER;
#endif
				return type;
			}
			static compilerType getCompiler(){
				compilerType type;
#if defined(__clang__)
				type = compilerType::CLANG;

#elif defined(__ICC) || defined(__INTEL_COMPILER)
				type = compilerType::INTEL;

#elif defined(__GNUC__) || defined(__GNUG__)
				type = compilerType::GNU;

#elif defined(__HP_cc) || defined(__HP_aCC)
				type = compilerType::HP;

#elif defined(__IBMC__) || defined(__IBMCPP__)
				type = compilerType::IBM;

#elif defined(_MSC_VER)
				type = compilerType::MSVC;

#elif defined(__PGI)
				type = compilerType::PORTLAND;

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
				type = compilerType::SOLARIS;

#endif
				return type;
			}
		};
		
	};
};

#endif // !_SRC_UTILS_PLATFORM_H_
