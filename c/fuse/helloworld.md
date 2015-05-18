# hello world 例子的源码阅读

## 文件介绍

主要介绍了作者，版权，以及如何编译执行

## 全局变量

代码文件中涉及到三个全局变量：

1.hello_str

字符指针变量，用于保存字符串常量，此处内容为Hello World!\n 
这里的内容是往路径文件里写的内容。

2.hello_path

字符指针变量，用于保存路径文件名称，此处内容为/hello
这里就是要挂载的文件路径名称。

3.hello_oper

fuse_operations结构体变量，主要用来保存一些操作函数，这里是四个操作函数：

	.getattr = hello_getattr,
	.readdir = hello_readdir,
	.open	 = hello_open,
	.read	 = hello_read,

功能一看便知，我就不多介绍了。

## 涉及到的四个函数：

上面已有介绍，这里简单作下说明：

* hello_getattr

得到文件的属性，结果保存在结构体stat中

* hello_readdir

读取目录信息

* hello_open

以只读方式打开文件

* hello_read

读取文件内容

## main函数

main直接调用fuse_main()处理，fuse_main(argc, argv, struct fuse_operations \*p, NULL)有四个参数，argc为传入main的参数个数，argv为参数值列表，p为fuse_operations结构提指针，主要保存的是操作函数，而第四个则为用户数据,这里为空。
