#ifndef PLATFORM_HPP
#define PLATFORM_HPP
namespace MakeSharp{
	namespace utils{
		enum platformType{
			LINUX=0,
			WINDOWS=1
		};
		enum compilerType{
			GNUC=0,
			CLANG=1
		};
		class Platform{
			public:
			static int getPlatform(){
				platformType type;
#if defined( __linux__)
				type=LINUX;
#elif defined(_WIN32)
				type=WINDOWS;
#endif
				return type;
			}
			static int getCompiler(){
				compilerType type;
#if defined(__GNUC__)
				type=GNUC;
#elif defined(__clang__)
				type=CLANG;
#endif
				return type;
			}
		};
		
	};
};
#endif
