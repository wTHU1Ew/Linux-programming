## 注释

### 重要注释
```c++
/*
 * IMPORTANT comment
 */
```

### 多行注释
```c++
/*
 * multi-line
 * comments
 */
```

## 头文件

### 在头文件使用宏来避免重复包含
```c++
#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <example.h>

#endif
```

### 头文件的包含顺序以及要空开一行
**kernel** -> **net** -> **/usr include** -> **/usr global pathname** -> **user include**
```c++
#include <sys/types.h>

#include <sys/route.h>
#include <netinet/in.h>

#include <stdlib.h>

#include <paths.h>

#include "my.h"
```

## 枚举
`enum`中枚举类型要大写, 最后一个枚举类型的后面不加`,`

## 结构
### 结构成员声明
以内存排列的方式声明结构中的成员(虽然我感觉现在编译器能帮忙处理很多, 但是最好还是别犯贱)

对于非要用bitfields的成员, 一定要从小到大排列好

```c++
struct foo {
	unsigned int baz:1,	
		     fuz:5,
		     zap:2;
	uint8_t flag;
};
```

### 结构声明
结构最好声明在文件顶部, 或者单独声明在一个头文件中

### typedef struct
保持`typedef`之后的名称与结构名称一致

```c++
typedef struct foo{
    int flag;
} foo;
```

## 宏
### 命名
遵循全部字母大写, 带`()`

```c++
#define MACRO(x)
```
### 缩进
宏名称前后可以任意空格, 但是TABs应该保持一致

### 宏定义
要用`()`将表达式包含起来

面对多行宏, 则需要用表达式`do{...}while(0)`来确保`;`被正确触发

```c++
#define MACRO(x, y, z)
do {
    x = (y) + (z);
    z = (y) + 2;
} while(0)
```

## 函数
### 私有函数声明(即不在其他文件中使用的函数)
遵循ANSI函数规则，先声明再定义，其中main()也是如此，同时声明的时候不带参数名

对于过长参数, 换行之后应该抱持首字母和`(`后对其

```c++
int toolong(char **[], double, float, char *,
            int, struct asf *);
int main(int, char *[]);
```

### 函数注释
函数定义前要注释写作用和参数意义

函数定义体中在一些主要流程也要写流程的作用

### 大括号
对于函数定义, 保持换行后再用

```c++
int 
main(int argc, char *argv[])
{
    //...
}
```

对于其他情况, `}`与`{`要保持同一行

```c++
if ()
{
    //...
} else {
    //...
}
```

### 函数定义
函数返回值要单独一行

若不存在local variables, 则单独空处一行

使用`assert()`来捕获明显非法的函数参数(Nesbsd为`_DIAGASSERT()`)

### 可变参数
要记得`#include <stdarg.h>`