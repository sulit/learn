> ============================================
>   Copyright (C) 2015 All rights reserved.
>
>   filename : README.md
>
>   author : sulit - sulitsrc@163.com
>
>   last modified : 2015-05-22 23:22
>
>   description :
>
> ============================================

1. 书中建议用bzero初始化一个结构体为0，现在这种做法不是很好了，因为bzero这个函
数已被弃用。建议用memset代替bzero。
