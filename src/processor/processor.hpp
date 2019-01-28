#ifndef PROC_H
#define PROC_H
#include <string>
#include <map>
#include <vector>
#define ns std::
namespace MakeSharp{
	namespace processor{
		class Processor{
			private:
				ns string version,
				       description,
				       name,
				       url,
				       license,
				       type;
				ns vector<ns string> author;
				ns map<ns string,ns map<ns string,ns string>> macros;
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
		};
	};
};
#undef ns
#endif
