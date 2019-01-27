## makeSharp Profile Format

---

### Profile Defintion

#### makesharp.json

一个 makesharp.json 文件应当位于其所属的 MakeSharp 项目的顶级目录。

展现了本文所提及的所有字段的完整示例可参见 reference.md。

在建立一个 MakeSharp 项目的过程中，您应当填写基本的项目信息（名称，作者，版本等）。

在发布自己的项目和包含他人项目时，请注意版权问题。makesharp.json 包含且应当包含必要信息。

本文中简要介绍了一个 makesharp.json 文件中所可能包含的所有一级字段。



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

#### license

> String

项目使用的版权许可协议。

若置为空，默认为 MIT 协议。详见 [License Choose](license.md)



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



### Source Object

---

用于生成目标文件的用户源代码。

#### object

> Object{"include": Array, "source": Array}

object 字段列出了需要引入的头文件路径和需要编译的源文件路径。

*include* 包含所需引入的头文件列表。字段包含的值类型：String | Object{Array{String}}

示例：

```json
"include": [
    "src/include/", "common/include/",
    {
        "include/": ["target.h", "graphic.hpp"]
    }
]
```

1. 当值为字符串的时候，可能是一个文件路径或目录名。若以 '/' 字符结尾，为目录路径，MakeSharp 会遍历该目录下所有以 `.h|.hpp`结尾的文件，并记录。若为文件路径，则直接记录。
2. 当值为对象的时候，根据对象中的键名得到目录路径，然后遍历键值数组，每个元素为需引入的头文件名称。MakeSharp 直接根据已知的父目录路径和头文件名称获取头文件完整路径，并记录。

*source* 包含需编译的源文件列表。其格式与机制与 *include* 字段等同。



### Target Object

---

用于构建二进制目标文件。

#### target

> Object{Object}

包含一组对象，每个对象对应一个实际的二进制文件目标。

其中每个字段对应所生成的文件的名称，type 子字段表明了它是何种类型，MakeSharp 根据平台信息和目标类型，产生带有特定文件后缀名的文件生成方案。path 子字段表明了目标文件应当被存储的位置。详细内容参见 [Target](target.md)。

示例如下：

```json
"target": {
    "graphic": {
        "type": "shared",
        "path": "build/bin"
    },
    "cli": {
        "type": "executable",
        "path": "build/cli"
    }
}
```



### Macros System

---

用于在配置文件中预操作宏的接口。

#### macros

> Object{Object}

子字段(1)名称为一个文件路径，其值为一个对象，这个对象的子字段(2)名称为需要应用到代码中的宏名，其值为具体的宏定义。(1) 的名称应为一个合法的文件名，但是保留一个名称：‘#’。这个名称意味着跟随其定义的宏为全局可见。

