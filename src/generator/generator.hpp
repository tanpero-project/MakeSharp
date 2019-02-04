#ifndef PROC_H
#define PROC_H
#include <string>
#include <map>
#include <vector>
#include <fstream>
#define ns std::
namespace MakeSharp{
	namespace generator{
		class Generator{
			private:
				ns string version,
				       description,
				       name,
				       url,
				       license,
				       type,
				       output;
				ns vector<ns string> author;
				ns map<ns string,ns map<ns string,ns string>> macros;
				ns vector<ns string> subdirs;
				ns map<ns string,ns vector<ns string>> executables;
				ns vector<ns string> includes;
			public:
				void setVersion(ns string v){
					this->version=v;
				}
				void setDescription(ns string desc){
					this->description=desc;
				}
				void setName(ns string n){
					this->name=n;
				}
				void setUrl(ns string u){
					this->url=u;
				}
				void setLicense(ns string l){
					this->license=l;
				}
				void setType(ns string t){
					this->type=t;
				}
				void setAuthor(ns string a){
					//only one author
					//this->author=new ns vector<ns string>();
					this->author.push_back(a);
				}
				void setAuthor(ns vector<ns string> a){
					//more than one author
					this->author=ns vector<ns string> (a);
				}
				void setMacros(ns map<ns string,ns map<ns string,ns string>> m){
					this->macros=m;
				}
				void setOut(ns string out){
					this->output=out;
				}
				void setSubDirs(ns vector<ns string> s){
					this->subdirs=s;
				}
				void setIncludes(ns vector<ns string> s){
					this->includes=s;
				}
				void write(){
					ns ofstream file;
					file.open(this->output.c_str());
					file	<<"project("
						<<this->name
						<<")"
						<<ns endl;
					for(ns string sd : this->subdirs){
						file	<<"add_subdirectory("
							<<sd
							<<")"
							<<ns endl;
					}
					for(ns string inc : this->includes){
						file	<<"include_directories("
							<<inc
							<<")"
							<<ns endl;
					}
					for(const auto& [key,value] : this->executables){
						file	<<"add_executable("
							<<key
							<<" ";
						for(ns string src : value){
							file	<<src
								<<" ";
						}
						file	<<")"
							<<ns endl;
					}
					file.close();
					writeMacros();
				}
				void writeMacros(){
					for(const auto& [key,value] : this->macros){
						ns ofstream scope;
						scope.open(key.c_str());
						for(const auto& [key,value] : value){
							scope	<<"#define "
								<<key
								<<" "
								<<value
								<<ns endl;
						}
						scope.close();
					}
				}
				void writeMacrosToIni(){
					for(const auto& [key,value] : this->macros){
						ns ofstream scope;
						scope.open((key+".ini").c_str());
						for(const auto& [key,value] : value){
							scope	<<key
								<<"="
								<<value
								<<ns endl;
						}
						scope.close();
					}
				}
				void writeMacrosToSingleIni(){
					ns ofstream single;
					ns string dog="collected.ini";
					single.open(dog);
					for(const auto& [key,value] : this->macros){
						single	<<"["
							<<key
							<<"]"
							<<endl;
						for(const auto& [k,v] : value){
							single	<<k
								<<"="
								<<v
								<<endl;
						}
					}
					single.close();
				}
		};
	};
};
#undef ns
#endif
