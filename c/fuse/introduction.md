# fuse概要介绍

### 通用信息

FUSE 是一个为用户空间程序导入虚拟文件系统到内核的简单接口。FUSE 旨在为没有权限的用户生成和挂载他们自己实现的文件系统提供一种安全的方式。

可以去sourceforge和github找到源码。

### 依赖

linux内核版本要求不小于2.6.9

小于这个版本的，建议去官网查看相关说明。

### 安装

linux源码安装三板斧，再加一步

	./configure
	make
	make install
	modprobe fuse

你可能也需要添加/usr/local/lib到/etc/ld.so.conf 和（或）运行ldconfig。

你可能将需要一个fuse内核模块，linux内核2.6.14以及之后的版本包含FUSE支持

更多详情参见INSTALL

### 如何用

FUSE 由三个部分组成：

1.一个内核文件系统模块

2.一个用户空间库

3.一个挂载/卸载程序

下面是如何通过五个容易步骤（安装FUSE之后）生成自己的文件系统:

1.编辑文件example/fusexmp.c做你想做的任何事

2.建立fusexmp程序

3.运行 'example/fusexmp /mnt/fuse -d'

4.ls -al /mnt/fuse

5.乐享其成

如果它不能工作，可以看文件/include/fuse.h了解库文件接口更详细的文档描述。

### 安全

如果你运行'make install'，FUSE挂载程序被以root权限安装，这样做将允许普通用户挂载他们自己实现的文件系统。

然而必须有一些权限，为了防止非法用户做龌龊的事，现在这些权限有：

  * 一个用户只可以挂载在一个挂载点，并且只有这个挂载点的写权限

  * 挂载点不是一个固定的目录，这个目录也不被一个特定用户所拥有（就像通常的/tmp目录）

  * 没有其他用户（包括root）可以访问这个挂载文件系统的内容

### 配置

一些选项关系到挂载策略可以在/etc/fuse.conf中被设置。

现在这些选项有：

	mount_max = NNN

设置允许非root用户FUSE挂载的最大数目，默认是1000

	user_allow_other

允许非root用户指定'allow_other'或者'allow_root'选项

### 挂载点

在'man mount'中描述的通用的挂载选项中的大部分都是被支持的（ro, rw, suid, nosuid, dev, nodev, exec, noexec, noexec, atime,, noatime, sync async, dirsync）。文件系统默认用选项'-nodev,nosuid'挂载，这个只能通过特权用户重写。

有FUSE指定的那些可以为所有文件系统指定的挂载选项：

	default_permissions

FUSE默认不检测文件访问权限，文件是自由的实施他的访问权限策略或者

待补

### fuse分布的模块

  * iconv

执行文件名字字符的设置转换。选项有：

	from_code=CHARSET

字符设置为转换字符编码来源（iconv -l 有一个可能值的列表）。默认是UTF-8

	to_code=CHARSET

字符设置为转换字符编码结果。默认是系统当前locale的字符编码值

  * subdir

追加一个给定的目录到每个路径。选项有：？？？

	subdir=DIR

目录追加到所有路径。这个选项是强制的。？？？

	rellinks

转换绝对链接到相对的

	norellinks

不要转换绝对链接到相对的，默认行为

### bug报告

这个自行查一下
