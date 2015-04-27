syntax on
set number
set ts=4
set tags=tags;/
"当新建 .h .c .hpp .cpp 等文件时自动调用SetTitle 函数
autocmd BufNewFile *.[ch],*.hpp,*.cpp,*.cc exec ":call SetTitle()"

"加入注释
func SetComment()
    call setline(1,"/*==================================")
    call append(line("."),   "*   Copyright (C) ".strftime("%Y")." All rights reserved.")
    call append(line(".")+1, "*   ")
    call append(line(".")+2, "*   文件名称：".expand("%:t"))
    call append(line(".")+3, "*   创 建 者：sulit")
    call append(line(".")+4, "*   创建日期：".strftime("%Y年%m月%d日"))
    call append(line(".")+5, "*   描    述：")
    call append(line(".")+6, "*")
    call append(line(".")+7, "================================================================*/")
endfunc

"定义函数SetTitle，自动插入文件头
func SetTitle()
	call SetComment()
	if expand("%:e") == 'hpp'
		call append(line(".")+8, "#ifndef _".toupper(expand("%:t:r"))."_H")
		call append(line(".")+9, "#define _".toupper(expand("%:t:r"))."_H")
		call append(line(".")+10, "#ifdef __cplusplus")
		call append(line(".")+11, "extern \"C\"")
		call append(line(".")+12, "{")
		call append(line(".")+13, "#endif")
		call append(line(".")+14, "")
		call append(line(".")+15, "#ifdef __cplusplus")
		call append(line(".")+16, "}")
		call append(line(".")+17, "#endif")
		call append(line(".")+18, "#endif //".toupper(expand("%:t:r"))."_H")
	elseif expand("%:e") == 'h'
		call append(line(".")+8, "#pragma once")
	elseif &filetype == 'c'
		call append(line(".")+8, "#include \"".expand("%:t:r").".h\"")
	elseif &filetype == 'cc'
		call append(line(".")+8, "#include \"".expand("%:t:r").".h\"")
	elseif &filetype == 'cpp'
		call append(line(".")+8, "#include \"".expand("%:t:r").".h\"")
	endif
endfunc
