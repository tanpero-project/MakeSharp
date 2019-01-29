#ifndef PLATFORM_HPP
#define PLATFORM_HPP
//It was hard to declare namespace....
#define coty compilerType::
#define plty platformType::
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
			LINUX=0,
			WINDOWS=1,
			AIX=2,
			BSD=3,
			XCODE=4,
			iOS=5,//'i' IN LOWER CASE CUZ 'IOS' AND 'iOS' IS DIFFERENT
			OSX=6,
			APPLE=7,//OTHER ENVIRONMENTS IN APPLE
			SOLARIS=8,
			CYWIN=9,
			WIN64=10,
			WIN32=11,
			UNIX=12,
			POSIX=13,
			OTHER=14
		};
		enum class compilerType{
			GNU=0,
			CLANG=1,
			INTEL=2,
			HP=3,
			IBM=4,
			VS=5,
			PORTLAND=6,
			SOLARIS=7
		};
		class Platform{
			public:
			static platformType getPlatform(){
				platformType type;
#if defined(_AIX)
				type=AIX;
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#if defined(BSD)
				type=plty BSD;
	#endif
#elif defined(__hpux)
				type=plty HPUX;
#elif defined(__linux__)
				type=plty LINUX;
#elif defined(__APPLE__) && defined(__MACH__)
	#if TARGET_IPHONE_SIMULATOR == 1
				type=plty XCODE;
	#elif TARGET_OS_IPHONE == 1
				type=plty iOS;
	#elif TARGET_OS_MAC == 1
				type=plty OSX;
	#else
				type=plty APPLE;
	#endif
#elif defined(__sun) && defined(__SVR4)
				type=plty SOLARIS;
#elif defined(__CYGWIN__) && !defined(_WIN32)
				type=plty CYWIN;
#elif defined(_WIN64)
				type=plty WIN64;
#elif defined(_WIN32)
				type=plty WIN32;
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
				type=plty UNIX;
	#if defined(_POSIX_VERSION)
				type=plty POSIX;
	#endif
#else
				type=plty OTHER;
#endif
				return type;
			}
			static compilerType getCompiler(){
				compilerType type;
#if defined(__clang__)
				type=coty CLANG;

#elif defined(__ICC) || defined(__INTEL_COMPILER)
				type=coty INTEL;

#elif defined(__GNUC__) || defined(__GNUG__)
				type=coty GNU;

#elif defined(__HP_cc) || defined(__HP_aCC)
				type=coty HP;

#elif defined(__IBMC__) || defined(__IBMCPP__)
				type=coty IBM;

#elif defined(_MSC_VER)
				type=coty VS;

#elif defined(__PGI)
				type=coty PORTLAND;

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
				type=coty SOLARIS;

#endif
				return type;
			}
		};
		
	};
};
#undef coty
#undef plty
#endif
