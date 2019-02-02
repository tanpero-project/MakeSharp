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
				void setIncludes(ns vectoe<ns string> s){
					this->includes=s;
				}
				void write(){
					ns ostream file;
					file.open(this->output.c_str());
					file	<<"project("
						<<this->name
						<<")"
						<<ns endl;
					for(ns string sd : this->subdirs){
						file	<<"add_subdirectory("
							<<sd
							<<")"
							<<endl;
					}
					for(ns string inc : this->includes){
						file	<<"include_directories("
							<<inc
							<<")"
							<<endl;
					}
					for(auto exe : this->executables){
						file	<<"add_executable("
							<<exe.key
							<<" ";
						for(ns string src : exe.value){
							file	<<src
								<<" ";
						}
						file	<<")"
							<<endl;
					}
					file.close();
				}
		};
	};
};
#undef ns
#endif
