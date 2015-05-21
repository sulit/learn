> ============================================
>   Copyright (C) 2015 All rights reserved.
>
>   filename : clearnnotte.md
>
>   author : sulit - sulitsrc@163.com
>
>   last modified : 2015-05-19 21:04
>
>   description :
>
> ============================================

[想到的需要解决的问题](question.md)

1. `EOF` 是-1，定义在stdio.h中

2. `#include <stdio.h>` 当文件名用一对尖括号<和>括起来时，预处理器将在由具体实现
定义的有关位置中查找指定的文件，例如unix中，文件一般放在目录/usr/include中

3. 注意下面语句中`*`的使用

	```
	printf("%.*s", max, p);
	```

4. 注意下面的p中不能含有%号

	```
	printf(p);
	```

5. va_start、va_arg、va_end的使用

6. ld.so.conf中可以添加动态库的地址，添加完之后记得ldconfig

7. python的c结构于lua的c api类似
