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
