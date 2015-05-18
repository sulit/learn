# FUSE 源码结构

./doc 包含了与 FUSE 有关的文档。

./include 包含了 FUSE API 头，您需要这些文件来创建文件系统。您现在唯一需要的就是 fuse.h。

./lib 中存放的是创建 FUSE 库的源代码，您需要将它们与您的二进制文件链接在一起来创建文件系统。

./util 中存放的是 FUSE 工具库的源代码。

./example 当然包含的是一些供您参考的例子，例如 fusexmp.null 和 hello 文件系统。
