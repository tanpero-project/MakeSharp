## makeSharp Profile Format

---

### Profile Defintion

#### makesharp.json

A makesharp.json file should be under all marksharp project root directories.  

Please see this Demo Document with format.json.  

First you need to fill in the basic project information(name, author, version, etc.)  

To specify dependencies used:

If the dependency is a .dll file,you should add it in "dependencies",for .lib it should be "static" in stead of "runtime".  



### Meta Datas

---

项目的元数据。标识一个项目的基本信息。

#### name 

> String 

顾名思义，这一字段是项目名称。

#### version

> String

项目的版本号。格式： X.Y.Z

版本规范详见 version.md。

#### author

> String | Array{String}

项目的作者或作者列表。

#### description

> String

项目的简要介绍。建议80字符以内。

#### repository

> Object{String, String}

项目的仓库信息。

type 字段用于填写项目仓库所使用的版本控制工具类型；

url 字段用于填写项目的仓库位置（URL）。



### Automatic Scripts

---

#### script

> Object{String, ...}

这一字段用于存放使用项目时可运行的脚本。每个子字段代表命令名称，其值为具体的命令内容。可能具有平台相关性。

脚本执行方式：mash run <命令名>



### Dependencies

---

在同名字段下具有两个子字段：static 和 runtime。

#### static

> Array{String}

此字段如果存在，则应当包含一组静态链接库路径。MakeSharp 遍历数组中包含的路径，若遇到不合法的路径则忽略。

1. 若以 '/' 字符结尾，说明该路径为目录名。MakeSharp 根据平台信息判断特定于平台的静态链接库后缀名，查找路径下所有后缀名符合的文件，并复制到 <保留目录>/dependencies/static/ 路径下。
2. 若不以 '/' 字符结尾，说明该路径指向具体文件。MakeSharp 将文件复制到<保留目录/dependencies/static/ 路径下。若文件后缀名不符合平台信息的所期望的，MakeSharp 会给出警告提示，仍继续操作。

Notes：若访问路径/复制文件等过程中遇到错误，MakeSharp 会给出相应错误提示并终止生成过程。

#### runtime

> Array{String}

此字段如果存在，则应当包含一组动态链接库路径。MakeSharp 遍历数组中包含的路径，若遇到不合法的路径则忽略。

1. 若以 '/' 字符结尾，说明该路径为目录名。MakeSharp 根据平台信息判断特定于平台的动态链接库后缀名，查找路径下所有后缀名符合的文件，并复制到 <保留目录>/dependencies/runtime 路径下。
2. 若不以 '/' 字符结尾，说明该路径指向具体文件。MakeSharp 将文件复制到<保留目录/dependencies/runtime/ 路径下。若文件后缀名不符合平台信息的所期望的，MakeSharp 会给出警告提示，仍继续操作。

Notes：若访问路径/复制文件等过程中遇到错误，MakeSharp 会给出相应错误提示并终止生成过程。



### 



### Dest element:

"include" will add .h/.hpp files And source will include .c/.cpp files.  

target:

the type section of target decides the File type.It can be either "shared" or "executable".  

"directory" is the directory you want the output in.


