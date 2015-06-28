syntax on
set number
set ts=8
set tw=78
set fo+=m
set autoindent
set cindent
set smartindent
set tags=./tags;/
set fillchars=fold:=

"当新建 .h .c .hpp .cpp 等文件时自动调用SetTitle 函数*/
"autocmd BufNewFile *.[ch],*.hpp,*.cpp exec ":call SetTitle()"
autocmd BufNewFile *.py,*.sh,*.perl exec ":call SetbatComment()"
autocmd BufNewFile *.c,*.cpp,*.h exec ":call SetComment()"
autocmd BufNewFile *.md exec ":call SetmdComment()"

func SetbatComment()
    call setline(1,"#================================================================")
    call append(line("."),   "#   Copyright (C) ".strftime("%Y")." All rights reserved.")
    call append(line(".")+1, "#")
    call append(line(".")+2, "#   filename:".expand("%:t"))
    call append(line(".")+3, "#   author:sulit sulitsrc@163.com")
    call append(line(".")+4, "#   modify date,time:".strftime("%Y-%m-%d %H:%M"))
    call append(line(".")+5, "#   discription:")
    call append(line(".")+6, "#")
    call append(line(".")+7, "#================================================================")
endfunc

"加入注释
func SetComment()
	call setline(1,"/*============================================")
	call append(line("."),   " *   Copyright (C) ".strftime("%Y")." All rights reserved.")
	call append(line(".")+1, " *")
	call append(line(".")+2, " *   filename : ".expand("%:t"))
	call append(line(".")+3, " *   author : sulit - sulitsrc@163.com")
	call append(line(".")+4, " *   last modified : ".strftime("%Y-%m-%d %H:%M"))
	call append(line(".")+5, " *   description :")
	call append(line(".")+6, " *")
	call append(line(".")+7, " *============================================*/")
endfunc

"mdcomment
func SetmdComment()
	call setline(1,"> ============================================")
	call append(line("."),   ">   Copyright (C) ".strftime("%Y")." All rights reserved.")
	call append(line(".")+1, ">")
	call append(line(".")+2, ">   filename : ".expand("%:t"))
	call append(line(".")+3, ">")
	call append(line(".")+4, ">   author : sulit - sulitsrc@163.com")
	call append(line(".")+5, ">")
	call append(line(".")+6, ">   last modified : ".strftime("%Y-%m-%d %H:%M"))
	call append(line(".")+7, ">")
	call append(line(".")+8, ">   description :")
	call append(line(".")+9, ">")
	call append(line(".")+10, "> ============================================")
endfunc

"定义函数SetTitle，自动插入文件头
func SetTitle()
	call SetComment()
	if expand("%:e") == 'hpp'
	call append(line(".")+8, "#ifndef _".toupper(expand("%:t:r"))."_H")
	call append(line(".")+9, "#define _".toupper(expand("%:t:r"))."_H")
	call append(line(".")+10, "#ifdef __cplusplus")
	call append(line(".")+11, "extern \"C\"")
endfunc
