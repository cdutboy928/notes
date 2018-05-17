function! Bold() range
    let length = v$
    "execute "visual! I" . "**" . "^["
    "normal! (length)l
    "execute "normal! a" . "**" . "^["
endfunction
