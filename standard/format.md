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



### Dest element:

"include" will add .h/.hpp files And source will include .c/.cpp files.  

target:

the type section of target decides the File type.It can be either "shared" or "executable".  

"directory" is the directory you want the output in.


