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

The metadata of the project. These dentify basic information about an project.

#### name 

> String 

As the name suggests, this field is the project name.

#### version

> String

The version number of the project. Format: X.Y.Z

The version specification is detailed in version.md.

#### author

> String | Array{String}

A list of authors or authors of the project.

#### description

> String

A brief introduction to the project. It is recommended to be within 80 characters.

#### repository

> Object{String, String}

The repository information for the project.

The type field is used to fill in the version control tool type used by the project repository;

The url field is used to fill in the warehouse location (URL) of the project.



### Automatic Scripts

---

#### script

> Object{String, ...}

This field is used to hold scripts that can be run when the project is used. Each subfield represents the name of the command and its value is the specific command content. May have platform relevance.

Script execution mode: mash run <command name>



### Dependencies

---

There are two subfields under the same name field: static and runtime.

#### static

> Array{String}

This field, if it exists, should contain a set of static link library paths. MakeSharp traverses the path contained in the array and ignores if it encounters an illegal path.

1. If ending with the '/' character, the path is the directory name. MakeSharp determines the platform-specific static link library suffix name based on the platform information, finds all files with the suffix names in the path, and copies them to the <reserved directory>/dependencies/static/ path.
2. If it does not end with the '/' character, the path points to a specific file. MakeSharp copies the files to the <reserved directory>/dependencies/static/ path. If the file suffix name does not meet the expectations of the platform information, MakeSharp will give a warning and continue to operate.

Notes: If an error is encountered during the path/copy file, etc., MakeSharp will give an error message and terminate the build process.

#### runtime

> Array{String}

This field, if it exists, should contain a set of dynamic link library paths. MakeSharp traverses the path contained in the array and ignores if it encounters an illegal path.

1. If ending with the '/' character, the path is the directory name. MakeSharp determines the platform-specific dynamic link library suffix name based on the platform information, finds all files with the suffix names in the path, and copies them to the <reserved directory>/dependencies/runtime path.
2. If it does not end with the '/' character, the path points to a specific file. MakeSharp copies the files to the <reserved directory/dependencies/runtime/ path. If the file suffix name does not meet the expectations of the platform information, MakeSharp will give a warning and continue to operate.

Notes: If an error is encountered during the path/copy file, etc., MakeSharp will give an error message and terminate the build process.

### Source Object

---

The user source code used to generate the target file.

#### object

> Object{"include": Array, "source": Array}

The object field lists the header file path that needs to be imported and the source file path that needs to be compiled.

*include* contains a list of header files that need to be imported. The value type the field contains: String | Object{Array{String}}

Example:

```json
"include": [
    "src/include/", "common/include/",
    {
        "include/": ["target.h", "graphic.hpp"]
    }
]
```

1. When the value is a string, it may be a file path or directory name. If the end of the '/' character is the directory path, MakeSharp will traverse all the files ending in `.h|.hpp` in that directory and record them. If it is a file path, it will be recorded directly.
2. When the value is an object, the directory path is obtained according to the key name in the object, and then the key value array is traversed, and each element is the name of the header file to be imported. MakeSharp gets the full path of the header file directly based on the known parent directory path and header file name, and records it.

*source* contains a list of source files to compile. Its format and mechanism are equivalent to the *include* field.



### Dest element:

"include" will add .h/.hpp files And source will include .c/.cpp files.  

target:

the type section of target decides the File type.It can be either "shared" or "executable".  

"directory" is the directory you want the output in.


