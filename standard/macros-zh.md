# Macros Definition
--------
宏定义是 Make# 的特性之一.  
加入 "useMacros": true 来开启定义宏.  
定义宏时,在makesharp.json文件加入`macros`字段.  

宏需要定义在一个作用域内，这个作用域需要是一个.h/.hpp 文件.  
宏的值必须是字符串(将会在字符串内转换类型).
例:  
```json
"macros":{
    "scope.h":{
        "max":"15",//宏 "max" 的值是数字 15并被定义在scope.h.
        "Fox":"\"dingningningningningningningning~\""//字符串声明
        "isMe":"true"
    }
}
```
如果想要将此宏成为全局可用，在"#"这个作用域内声明.  
例:  
```json
"macros":{
    "#":{
        "isGlob":"\"LOL\"",
        "squareRootOf97dividedBy23Less4":"\"pancake\""
    }
}
```
如果想要引用其他作用域的宏，在需要引用的作用域里声明"+":  
> "+":[字符串,字符串,...]  
> "+":字符串  
  
每个字符串都代表着对其他宏进行的引用.引用格式如下:  
`scopeName#macrosName`.  
例:
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
同样，可以如下那样引用整个作用域内的宏:  
> "+":["scopeName#\*"]  
  
用以下方式去除一些多引用的宏:  
> "~":["scopeName#macrosName"]  
  
也可以通过设置不想要的宏为false来取消引用:  
> "unwanted":false //注意这里没有引号  
  
以如下方式定义宏函数:  
> "MAX(a,b)":"((a\>b)?a:b)  

