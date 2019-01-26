# MakeSharp Build-System Documentaion

---
## makesharp.json
A makesharp.json File should be under all marksharp project root directories.  
Please see this Document with [file-format.json](file-format.json).  
First you need to fill in the basic project information(name,author,version,etc.)  
#### To specify dependencies used:
if the dependency is a .dll file,you should add it in \["dependencies"]\["runtime"],for .lib it should be "static" in stead of "runtime".  
#### Dest element:  
"include" will add .h/.hpp files And source will include .c/.cpp files.  
#### target:  
the type section of target decides the File type.It can be either "shared" or "executable".  
"directory" is the directory you want the output in.
