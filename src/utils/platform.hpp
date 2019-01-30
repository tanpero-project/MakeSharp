#ifndef PLATFORM_HPP
#define PLATFORM_HPP

// Visual Studio 下定义的这个宏会与 enum 中的名称冲突
// I saw a bunch of nonsense Text / \  FFFFFFF
// 				   |
#if defined(WIN32)
#undef WIN32
#define WIN32BACK
#elif defined(WIN64)
#undef WIN64
#define WIN64BACK
#endif // WIN32,64

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

			IOS = (UNIX | (1 << 12)),
			OSX = (UNIX | (1 << 13)),
			XCODE = (UNIX | (1 << 14)), // The iOS emulator in Xcode.
			APPLE = (UNIX | (1 << 15)), // Other Apple Platform

			WINDOWS = (1 << 16),
			MSDOS = (1 << 17),
			CYGWIN = (POSIX + WINDOWS + (1 << 18))

	/*		LINUX = 0,
			WINDOWS = 1,
			AIX = 2,
			BSD = 3,
			XCODE = 4,
			iOS = 5,//'i' IN LOWER CASE CUZ 'IOS' AND 'iOS' IS DIFFERENT
			OSX = 6,
			APPLE = 7,//OTHER ENVIRONMENTS IN APPLE
			SOLARIS = 8,
			CYWIN = 9,
			WIN64 = 10,
			WIN32 = 11,
			UNIX = 12,
			POSIX = 13,
			MSDOS = 14
			OTHER = 14*/
		};
		enum class compilerType{
			GNU = 0,
			CLANG = 1,
			INTEL = 2,
			HP = 3,
			IBM = 4,
			MSVC = 5,
			PORTLAND = 6,
			SOLARIS = 7
		};
		class Platform{
			public:
			static platformType getPlatform(){
				platformType type;
#if defined(_AIX)
				type = AIX;
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#if defined(BSD)
				type = platformType::BSD;
	#endif
#elif defined(__hpux)
				type = platformType::HPUX;
#elif defined(__linux__)
				type = platformType::LINUX;
#elif defined(__APPLE__) && defined(__MACH__)
	#if TARGET_IPHONE_SIMULATOR  ==  1
				type = platformType::XCODE;
	#elif TARGET_OS_IPHONE  ==  1
				type = platformType::iOS;
	#elif TARGET_OS_MAC  ==  1
				type = platformType::OSX;
	#else
				type = platformType::APPLE;
	#endif
#elif defined(__sun) && defined(__SVR4)
				type = platformType::SOLARIS;
#elif defined(__CYGWIN__) && !defined(_WIN32)
				type = platformType::CYWIN;
#elif defined(_WIN64)
				type = platformType::WIN64;
#elif defined(_WIN32)
				type=platformType::WIN32;
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
				type=platformType::UNIX;
	#if defined(_POSIX_VERSION)
				type=platformType::POSIX;
	#endif
#else
				type = platformType::OTHER;
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
?
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
#if defined(WIN32BACK)
#undef WIN32BACK
#define WIN32
#elif defined(WIN64BACK)
#undef WIN32BACK
#define WIN64
#endif
#endif
