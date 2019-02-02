#ifndef _SRC_UTILS_UTILSTUFF_H_
#define _SRC_UTILS_UTILSTUFF_H_

#include <string>

namespace MakeSharp
{
    namespace utils
    {
        namespace utilsstuff
        {
            inline std::string getAppendixName(std::string name)
            {
                std::string appendix = name.substr(name.find_last_of('.') + 1);
                if (appendix == name)
                {
                    return "";
                }
                return appendix;
            }

            inline bool isHeaderFile(std::string name)
            {
                std::string appendix = getAppendixName(name);
                return appendix == "h" || appendix == "hh" || appendix == "h++"
                    || appendix == "hm" || appendix == "hpp" || appendix == "hxx"
                    || appendix == "in" || appendix == "txx";
            }

            inline bool isSourceFile(std::string name)
            {
                std::string appendix = getAppendixName(name);
                return appendix == "c" || appendix == "C" || appendix == "c++"
                    || appendix == "cc" || appendix == "cpp" || appendix == "cxx"
                    || appendix == "cu" || appendix == "m" || appendix == "M"
                    || appendix == "mm";
            }
        }
    }
}

#endif // !_SRC_UTILS_UTILSTUFF_H_
