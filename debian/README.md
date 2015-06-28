> ============================================
>   Copyright (C) 2015 All rights reserved.
>
>   filename : README.md
>
>   author : sulit - sulitsrc@163.com
>
>   last modified : 2015-06-28 16:28
>
>   description :
>
> ============================================

debian使用过程中的一些问题

1. 选择适合自己的更新源
```
man netselect-apt
```
> [这里](mynetselect-apt.sh)有个我自己写的一行脚本，可以参考下。

执行后会生成类似于[sources.list](sources.list)这样的文件，文件可以重命名。然后就可以用这个文
件去覆盖/etc/apt/sources.list（注意保存源文件）。

2. 当你下载或者升级时，出现*.deb size dismatch，这时**可能**时你的源有问题。

3. linux对有些新的网卡支持不好，有时候需要自己去找驱动。
```
lspci -vv
```
用上面命令可以看到自己的网卡信息，然后就用这个型号去找一些驱动。
