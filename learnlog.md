> ================================================================
>    Copyright (C) 2015 All rights reserved.
>
>    filename:learnlog.md
>
>    author:sulit sulitsrc@163.com
>
>    modify date,time:2015-05-19 12:54
>
>    discription:
>
> ================================================================

1. 在编译有关线程的程序时，要注意链接pthread库

2. linux的新版chrome已经不支持3.17以下的内核，对于我这种使用debian的用户，
果断下载个最新的长期稳定的3.18.10 kernel，编译换上，我的vimium岂能消亡。

	```
	make menuconfig
	make
	sudo make modules_install install
	```

3. readline库是个不错的库，这个可以学习

4. freebsd是个不错的选择，在开源学习方面，可以follow李鑫

5. 格式化程序文件操作

	```
	indent -kr -i8 program.c
	```

6. **注意：**

  core文件中可能含有用户信息，不要随便传到网上

7. 下面是学习vim的一篇文档，吴哥推荐的，看着不错的样子

  http://learnvimscriptthehardway.onefloweroneworld.com/

8. 浪潮之巅

9. 这个网址的有些文章不错

  [http://dirlt.com](http://dirlt.com)

10. qemu教程

  `#qemu-img create windows.img 2G`

  > 这个就是创建虚拟机磁盘，2G大小

  `#qemu -hda windows.img -cdrom /dev/acd0 -boot d -m 512 -enable-audio
  \-localtime`

  `-hda` 是指定硬盘

  `-cdrom` 指定使用光驱，这个参数后面必须要跟个文件名，可以是物理光驱/dev/hda，可
  以使用ISO文件，为文件的路径

  `-m` 是指定虚拟机使用的内存大小，如512M

  `-boot` 指定虚拟机启动用的设备，-boot后可以选择的参数是 a ,c ,d .其中a 是指从软
  盘启动，c 就是用硬盘启动，d 当然就是光驱启动了。

  `-enable-audio`

  `-localtime` 使用实际主板bios上的时间。

11. 最近关于数据安全问题越发严重

  网易蹲完，支付宝蹲，支付宝蹲完，携程蹲，携程蹲完，艺龙蹲。。。

  这是个数据的未来啊！

12. latex有机会一定要学习下，感觉用处太大了

13. os的学习，以及kali的学习

14. gnome-terminal: keep track of directory in new tab解决办法

  q:I'm on Arch linux, and when I open a new terminal tab, it always goes to
  $HOME. How can I make it so that when I open a new tab, it opens the shell
  in the directory I was in previously?

  a:There is a bug related to this issue
  All you need to do is add the following line to your .bashrc or .zshrc:
  ```
  . /etc/profile.d/vte.sh
  ```
  and exits if you are not.

15. kali linux发行版现在也是不错的选择，但是默认安装的东西确实多了点，基于
debian，现在滚动更新。桌面什么的都还不错，可以试试。
