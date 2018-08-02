bhyve总结
=========

- bhyve介介绍

  bhyve是FreeBSD下的虚拟机，可以安装Linux、Windows、FreeBSD等。

- bhyve安装Linux

  * 准备一个镜像就可以了，比如debian-9.5.0-amd64-netinst.iso，
其他需要的用工具生成

  * 生成一块虚拟磁盘文件`truncate -s 50G linux.img`

  * 生成一个device.map的文本文件，用来进行设备映射，内容为

	(cd0)/debian-9.5.0-amd64-netinst.iso
	(hd0)/linux.img

  * 然后用`grub-bhyve -m device.map -r cd0 -M 1024 linuxguest`启动内核

  * 然后用`bhyve -AI -H -P -s 0:0,hostbridge -s 1:0,lpc -s 3:0,virtio-blk,./linux.img
-s 4:0,ahci-cd,./debian-9.5.0-amd64-netinst.iso -l com1,stdio -c 4 -m 1024M linuxguest`
启动系统进行系统安装

- bhyve网络配置

  1 桥接模式

　2 NAT模式

  3 利用物理网卡

  由于机器不行，没有进行测试







**NOTE 1** **系统没有网络，网络配置比较复杂，改天再写**

**NOTE 2** **系统启动必须先用grub-bhyve启动内核**

**NOTE 3** **当关机后，如果改变使用的内存，则需要先执行
`bhyvectl --destroy --vm=linuxguest`，主要是释放虚拟机资源，否则会提示启动错误**

**NOTE 4** **有一些可以方便使用bhyve的配置管理工具**









- 深入阅读

[FreeBSD bhyve](https://people.freebsd.org/~rodrigc/doc/handbook/virtualization-host-bhyve.html)

[FreeBSD bhyve网络配置选项](http://empt1e.blogspot.com/2016/10/bhyve-networking-options.html)
