#ifndef INIPARSER_H
#define INIPARSER_H
#include <../include/INI.h>
#include <string>

namespace MakeSharp{
	namespace macros{
		class INIParser{
			public:
				INIParser(std::string path){
					this->file=path;
				}
				INIParser(){

				}
				void setPath(std::string path){
					this->file=path;
				}
				void parse(){
					// TODO:parse ini file.
				}
				void addTo(std::map<std::string,std::map<std::string,std::string>>* to){
					// TODO:add them
				}
		};
	};
};
#endif
