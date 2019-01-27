# Macros Definition
--------
Macros Definition is one of the features of Make#.  
To enable it,use "useMacros":true  
When declaring a Macros,you need to add field `macros` to the root of json.  

A macros should be in a scope and is a .h/.hpp file.  
The values must be a String literal.
Ex:  
```json
"macros":{
	"scope.h":{
		"max":"15",//macros "max" with value 15 in declared in scope.h.
		"Fox":"\"dingningningningningningningning~\""//string declaration.
		"isMe":"true"
	}
}
```  
But,If you want your macros to be global,you can just set the scope name to"#".  
Ex:  
```json
"macros":{
	"#":{
		"isGlob":"\"LOL\"",
		"squareRootOf97dividedBy23Less4":"\"pancake\""
	}
}
```
Also,If you want one macros to be shared in multiple scopes,you can use "+" in a scope:  
> "+":[String,String,...]  
Each String is a reference to another macros.Reference is written in form  
`scopeName#macrosName`.  
Ex:
```json
"macros":{
	"horrible.h":{
		"notHorrible":"true"
	},
	"Animals.h":{
		"cat":"\"meow\"",
		"+":["horrible.h#notHorrible"]
	}
}
```
You can also include the whole scope macros into a different scope like:  
> "+":["scopeName#\*"]  
To exclude some of them,you should use:  
> "~":["scopeName#macrosName"]  
To define a macros function:  
> "MAX(a,b)":"((a\>b)?a:b)
