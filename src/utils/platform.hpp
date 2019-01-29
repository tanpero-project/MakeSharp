#ifndef PLATFORM_HPP
#define PLATFORM_HPP

// Visual Studio �¶������������ enum �е����Ƴ�ͻ
#ifdef WIN32
#undef WIN32
#endif // WIN32


#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#include <sys/param.h>
#elif defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
	#include <unistd.h>
#endif
namespace MakeSharp{
	namespace utils{
		enum class platformType{
			LINUX = 0,
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
			OTHER = 14
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
#undef coty
#undef plty
#endif
