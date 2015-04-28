syntax on
set number
set ts=4
set tags=tags;/
当新建 .h .c .hpp .cpp 等文件时自动调用SetTitle 函数
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

"进行版权声明的设置
"添加或更新头
map <F4> :call TitleDet()<cr>'s
function AddTitle()
    call append(0,"/*=============================================================================")
    call append(1,"#")
    call append(2,"# Author: dantezhu - dantezhu@vip.qq.com")
    call append(3,"#")
    call append(4,"# QQ : 327775604")
    call append(5,"#")
    call append(6,"# Last modified: ".strftime("%Y-%m-%d %H:%M"))
    call append(7,"#")
    call append(8,"# Filename: ".expand("%:t"))
    call append(9,"#")
    call append(10,"# Description: ")
    call append(11,"#")
    call append(12,"=============================================================================*/")
    echohl WarningMsg | echo "Successful in adding the copyright." | echohl None
endf
"更新最近修改时间和文件名
function UpdateTitle()
    normal m'
    execute '/# *Last modified:/s@:.*$@\=strftime(":\t%Y-%m-%d %H:%M")@'
    normal ''
    normal mk
    execute '/# *Filename:/s@:.*$@\=":\t\t".expand("%:t")@'
    execute "noh"
    normal 'k
    echohl WarningMsg | echo "Successful in updating the copy right." | echohl None
endfunction
"判断前10行代码里面，是否有Last modified这个单词，
"如果没有的话，代表没有添加过作者信息，需要新添加；
"如果有的话，那么只需要更新即可
function TitleDet()
    let n=1
    "默认为添加
    while n < 10
        let line = getline(n)
        if line =~ '^\#\s*\S*Last\smodified:\S*.*$'
            call UpdateTitle()
            return
        endif
        let n = n + 1
    endwhile
    call AddTitle()
endfunction
