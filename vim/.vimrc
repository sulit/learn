syntax on
set number
set autoindent
set ts=4
set tags=tags;/
autocmd BufNewFile *.py,*.sh,*.perl exec ":call SetComment()" 
autocmd BufNewFile *.md exec ":call SetmdComment()" 

func SetComment()
    call setline(1,"#================================================================")
    call append(line("."),   "#   Copyright (C) ".strftime("%Y")." All rights reserved.")
    call append(line(".")+1, "#   ")
    call append(line(".")+2, "#   filename:".expand("%:t"))
    call append(line(".")+3, "#   author:sulit sulitsrc@163.com")
    call append(line(".")+4, "#   modify date,time:".strftime("%Y-%m-%d %H:%M"))
    call append(line(".")+5, "#   discription:") 
    call append(line(".")+6, "#")
    call append(line(".")+7, "#================================================================")
endfunc

func SetmdComment()
    call setline(1,"> ================================================================")
    call append(line("."),   ">    Copyright (C) ".strftime("%Y")." All rights reserved.")
    call append(line(".")+1, ">")
    call append(line(".")+2, ">    filename:".expand("%:t"))
    call append(line(".")+3, ">")
    call append(line(".")+4, ">    author:sulit sulitsrc@163.com")
    call append(line(".")+5, ">")
    call append(line(".")+6, ">    modify date,time:".strftime("%Y-%m-%d %H:%M"))
    call append(line(".")+7, ">")
    call append(line(".")+8, ">    discription:") 
    call append(line(".")+9, ">")
    call append(line(".")+10, "> ================================================================")
endfunc
