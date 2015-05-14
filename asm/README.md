> /*============================================
> *   Copyright (C) 2015 All rights reserved.
> *
> *   filename : README.md
> *   author : sulit - sulitsrc@163.com
> *   last modified : 2015-05-15 00:06
> *   description :
> *
> **============================================*/

linux下用intel汇编编程

step 1

nasm -f elf64(elf32) hello.asm

step 2

gcc -o hello hello.o
