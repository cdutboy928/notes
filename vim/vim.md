# Vim Skills
## insert special characters
* *Note: `Ctrl+Shift+_` or `Ctrl+7`to insert special characters.*
    * <C-k> and type 0U for a smile face: ☻
    * <C-k> and type OK for a tick: ✓
    * <C-k> and type XX for a ballot X: ✗
    * other useful special characters:(http://vimhelp.appspot.com/digraph.txt.html)
⅓     13      2153    8531    VULGAR FRACTION ONE THIRD
⅔     23      2154    8532    VULGAR FRACTION TWO THIRDS
⅕     15      2155    8533    VULGAR FRACTION ONE FIFTH
⅖     25      2156    8534    VULGAR FRACTION TWO FIFTHS
⅗     35      2157    8535    VULGAR FRACTION THREE FIFTHS
⅘     45      2158    8536    VULGAR FRACTION FOUR FIFTHS
⅙     16      2159    8537    VULGAR FRACTION ONE SIXTH
⅚     56      215A    8538    VULGAR FRACTION FIVE SIXTHS
⅛     18      215B    8539    VULGAR FRACTION ONE EIGHTH
⅜     38      215C    8540    VULGAR FRACTION THREE EIGHTHS
⅝     58      215D    8541    VULGAR FRACTION FIVE EIGHTHS
⅞     78      215E    8542    VULGAR FRACTION SEVEN EIGHTHS
Ⅰ     1R      2160    8544    ROMAN NUMERAL ONE
Ⅱ     2R      2161    8545    ROMAN NUMERAL TWO
Ⅲ     3R      2162    8546    ROMAN NUMERAL THREE
Ⅳ     4R      2163    8547    ROMAN NUMERAL FOUR
Ⅴ     5R      2164    8548    ROMAN NUMERAL FIVE
Ⅵ     6R      2165    8549    ROMAN NUMERAL SIX
Ⅶ     7R      2166    8550    ROMAN NUMERAL SEVEN
Ⅷ     8R      2167    8551    ROMAN NUMERAL EIGHT
Ⅸ     9R      2168    8552    ROMAN NUMERAL NINE
Ⅹ     aR      2169    8553    ROMAN NUMERAL TEN
Ⅺ     bR      216A    8554    ROMAN NUMERAL ELEVEN
Ⅻ     cR      216B    8555    ROMAN NUMERAL TWELVE
ⅰ     1r      2170    8560    SMALL ROMAN NUMERAL ONE
ⅱ     2r      2171    8561    SMALL ROMAN NUMERAL TWO
ⅲ     3r      2172    8562    SMALL ROMAN NUMERAL THREE
ⅳ     4r      2173    8563    SMALL ROMAN NUMERAL FOUR
ⅴ     5r      2174    8564    SMALL ROMAN NUMERAL FIVE
ⅵ     6r      2175    8565    SMALL ROMAN NUMERAL SIX
ⅶ     7r      2176    8566    SMALL ROMAN NUMERAL SEVEN
ⅷ     8r      2177    8567    SMALL ROMAN NUMERAL EIGHT
ⅸ     9r      2178    8568    SMALL ROMAN NUMERAL NINE
ⅹ     ar      2179    8569    SMALL ROMAN NUMERAL TEN
ⅺ     br      217A    8570    SMALL ROMAN NUMERAL ELEVEN
ⅻ     cr      217B    8571    SMALL ROMAN NUMERAL TWELVE
←     <-      2190    8592    LEFTWARDS ARROW
↑     -!      2191    8593    UPWARDS ARROW
→     ->      2192    8594    RIGHTWARDS ARROW
↓     -v      2193    8595    DOWNWARDS ARROW
⇐     <=      21D0    8656    LEFTWARDS DOUBLE ARROW
⇒     =>      21D2    8658    RIGHTWARDS DOUBLE ARROW
⇔     ==      21D4    8660    LEFT RIGHT DOUBLE ARROW
○     0m      25CB    9675    WHITE CIRCLE
◎     0o      25CE    9678    BULLSEYE
●     0M      25CF    9679    BLACK CIRCLE
◐     0L      25D0    9680    CIRCLE WITH LEFT HALF BLACK
◑     0R      25D1    9681    CIRCLE WITH RIGHT HALF BLACK
☺     0u      263A    9786    WHITE SMILING FACE
☻     0U      263B    9787    BLACK SMILING FACE
## how to insert emoji in vim
* Using vim-plug: Plug 'junegunn/vim-emoji'
* put "set completefunc=emoji#complete" in .vimrc
* `<C-x>` and then `<C-u>`:
  [![](https://camo.githubusercontent.com/c2c6add271b0719215f2cac78e6a777f83184bed/68747470733a2f2f7261772e6769746875622e636f6d2f6a756e6567756e6e2f692f6d61737465722f656d6f6a692d636f6d706c6574652e676966)](https://camo.githubusercontent.com/c2c6add271b0719215f2cac78e6a777f83184bed/68747470733a2f2f7261772e6769746875622e636f6d2f6a756e6567756e6e2f692f6d61737465722f656d6f6a692d636f6d706c6574652e676966)
## NERDTree
* file node mappings 
    * o: open in preview window (the cursor at the nerdtree window)
    * go: preview (the cursor at the edit window)
    * t: open in new tab
    * T: open in new tab silently
    * i: open split
    * gi: preview split
    * s: open vsplit
    * gs: preview vsplit
* directory node mapping	
    * o: open and close node
    * O: recursively open node
    * t: open in the new tab
    * T: open in the new tab silently
    * e: explore selected dir
* Tree navigation mappings	
    * p: go to the root
    * P: go to the parent 
    * K: go to the first child
    * J: go to the last child
    * `<C-j>`: go to the next sibling
    * `<C-k>`: go to the prev sibling
* Other mappings
    * A: Zoom (maximize-minimize) the NERDTree window
## [fcitx](https://fcitx-im.org/wiki/Special:MyLanguage/Fcitx)
* Fcitx [ˈfaɪtɪks] is an input method framework with extension support. Currently it supports Linux and Unix systems like freebsd. It has three built-in Input Method Engine, Pinyin, QuWei and Table-based input methods. 
* Install
    `sudo add-apt-repository ppa:fcitx-team/stable`
    `sudo apt-get update`
* Config
    If you are using newer Ubuntu, your Ubuntu might use im-config instead of im-switch, you simply run im-config and choose the input method. 
* Install input method
    * You'd better install it with your distribution package management software, usually the input method is in the same repo from which you install Fcitx. All Fcitx related package is start with fcitx, so you will see it when you search fcitx. zhuxianzhan 
    * After you install
        `fcitx -r`
## [vimim](https://vim.sourceforge.io/scripts/script.php?script_id=2506)
### installation
* just put the vimim.vim and 词库文件 to ~/.vim/plugin/
    * [vimim.vim](https://github.com/xhh/vimim)
    * [词库文件](https://code.google.com/archive/p/vimim-data/downloads)
* or install through vundle:
    * Plugin 'vim-scripts/VimIM'
    * Plugin 'vimim/vimim'
    ` let g:vimim_ctrl_space_to_toggle=1`
     `let g:vimim_tab_as_onekey=1`
     `imap <C-L> <C-\>`
* **Note: the spf13 makes the installation failed once again.**
### configuration
* `s:rc["g:Vimim_cloud"]` 中的初始值改为'baidu'
* put `let g:Vimim_cloud='baidu'` in .vimrc
### how to use
* 注意使用的时候得出现百度云才行，百度云前面是当前的输入模式：点石成金是就是无菜单模式，中文动态就是你菜单模式。
 * 通过gi是进入点石成金模式;
 * 用Ctrl+6 也是toggle无菜单的点石成金的模式；
 * 通过Ctrl+/或Ctrl+Shift+－或者ctrl+7都是toggle有菜单的中文动态模式。（最常用）
* 无菜单模式
    在normal 模式下输入gi 即可进入无菜单的中文输入：输入拼音后按空格键选词,按空格键或者Ctrl+n是向下翻词,Ctrl+p 是向上翻,Ctrl+o 是把词语分成字来选。
**注意:**
    * 按gi 之后是在光标的后边输入汉字;
    * 选好词或者字之后就继续打后面的词语就行了,不必再按空格键了。
    * 标点符号也是可以翻词的。比如点号翻成句号。
* 有菜单模式
    * 在insert模式下直接按Ctrl+/或Ctrl+7或Ctrl+Shift+－，即进入有菜单的输入模式，通过数字键选词，空格键可以选择第一个词。Ctrl+p和Ctrl+n上下翻词（不能用j和k来选词）。按回车是无缝上英文的。这个的优势是打完拼音就能直接出中文菜单，可以直接选。缺点是不能jk选词。
    * 在insert 模式下按下Ctrl+6, 即可进入有菜单的输入模式,按菜单提示按对应的字母或者按字母j 和k 上下翻选词就行了。按回车是无缝上英文的。这个的优点是可以jk选词，但是其实是点石成金模式，打完拼音需要按空格才能出现中文选词菜单。
* 拼音搜索中文
    * 用 Vim 打开一个文本，输入 /ceshi 来搜索关键字，然后回车，此时会提示 Pattern not found（确保文中没有 ceshi 这个 5 个字母的关键字，有的话则匹配不到中文的），然后继续按 n ，如果这个文本里有 测试 或拼音一样的中文的话，则都会被搜索匹配到，继续按 n 来匹配一下一个关键字。
## aboout color schemes
### [solarized](https://github.com/altercation/vim-colors-solarized)
![the light and dark](https://raw.githubusercontent.com/altercation/solarized/master/img/solarized-vim.png)
#### installation
* $ cd ~/.vim/bundle
  $ git clone git://github.com/altercation/vim-colors-solarized.git
#### configuration
* syntax enable
  set background=light
  colorscheme solarized
* and add this to .vimrc
  `set rtp+=~/.vim/bundle/vim-colors-solarized`
### ColorSchemePicker
randomly pick up a colorscheme for you
#### installation
through pathogen:
`cd ~/.vim/bundle &&
git clone https://github.com/sunuslee/vim-plugin-random-colorscheme-picker`
#### commands
* 
  if you LOVE this colorscheme,
  Enter( In Normal Mode )
  `:Love`
  then I will never change your colorscheme again.
* 
  if you HATE this colorscheme and don't want to see her again,
  Enter( In Normal Mode )
  `:Hate`
  then I will never pick this colorscheme for you and then
  randomly pick a new colorscheme.
* 
  if you somehow regret what you did and want to get the hated colorscheme back,
  Enter(In Normal Mode)
  `:Back`
  then all you hated colorscheme will back to select pool, and you might see
  her again:)
* 
  Enter(In Normal Mode)
  `:CS`
  to see current colorscheme
* 
  Enter(In Normal Mode)
  `:CSnext`
  to switch to a new random theme without restarting vim.
## relativenumber
* `set relativenumber` or `set rnu`
* use `d4j` `d4k` `g4j` insteada of `4dd`
## 显示空格等不可见的字符
    set list
    set listchars=tab:›\ ,trail:•,extends:#,nbsp:. " Highlight problematic whitespace
## how to note question parts
put the following codes in .vimrc:
        hi Error ctermbg=red guibg=darked
        match Error /???/
        hi Todo ctermbg=green guibg=blue
        2match Todo /???/
        hi Title ctermbg=blue guibg=darked
        3match Title /???/
## auto indent
* set ai          设置自动缩进
* :set shiftwidth=4   设置自动缩进 4 个空格, 当然要设自动缩进先.
## hardcopy
* `hardcopy` 调出打印对话框
* `hardcopy!` 不调出打印对话框
* `：1,100 hardcopy`
* `set printoptions=paper:A4,syntax:y,wrap:y,number:y`
    * paper:A4,A3,letter,legal
    * syntax:
        * 默认值“a”，意味着仅在使用彩色打印机时，打印语法高亮度；
        * 你也可以将值设为“y” ，强制打印语法高亮度。
    * wrap选项，确定是否折行打印。
        * 默认值“:y”，意味着自动折行；
        * 如果你将值设为“n”，那么过长的行在打印时将被截断。
    * number选项，设为“y”时，将会打印行号。

## about folding and unfolding

* `zo` to open the current fold
* `zO` to open all folds
* `zc` to close the current fold
* `zC` to close all folds
* `za` to toggle the current fold
* `zA` to toglle all foldes
* `zr` to open one more level of folds through out the whole buffer
* `zR` to open all folds
* `zm` to close one more level of folds through out the whole buffer
* `zM` to close all folds

## vim slow
* run `vim --startuptime timefile git.md`
* run `vim timefile` to see which plugins make vim slow
* comment the plugin in `.vimrc`
* Open a new terminal tab and run `sudo vim`, and run `PluginUpdate`

## highlight bold and italic words
`highlight htmlBold gui=bold guifg=#af0000 ctermfg=34`
`highlight htmlItalic gui=italic guifg=#ff8700 ctermfg=214`
## write my own vimscript (in `.vimrc`)
* First, write the following function in `.vimrc`:

        function! Bold() range
            let amount = virtcol("'>") - virtcol("'<") + 2
            execute "normal gv"
            execute "normal! A" . "**" . "\<Esc>"
            execute "normal!" . amount . "h"
            execute "normal! i" . "**" . "\<Esc>"
        endfunction
* Second, set the mapping and invoking of the above function in `.vimrc`

        vnoremap <LocalLeader>b :call Bold()<cr>
## Write and install my own vim plugin
* First, create the plugin directory
    * `cd ~/.vim/plugin` (can also be other directory)
    * `mkdir -p vim_markdown_shortcuts.vim/ftplugin`
* Second, create and write the plugin file
    * `cd ~/.vim/plugin/vim_markdown_shortcuts.vim/ftplugin`
    * `vim markdown_shortcuts.vim`
    * the example code

            function! MarkdownBoldFunction() range
                let amount = virtcol("'>") - virtcol("'<") + 2
                execute "normal gv"
                execute "normal! A" . "**" . "\<Esc>"
                execute "normal!" . amount . "h"
                execute "normal! i" . "**" . "\<Esc>"
            endfunction
            
            function! MarkdownItalicFunction() range
                let amount = virtcol("'>") - virtcol("'<") + 1
                execute "normal gv"
                execute "normal! A" . "*" . "\<Esc>"
                execute "normal!" . amount . "h"
                execute "normal! i" . "*" . "\<Esc>"
            endfunction
            
            function! MarkdownCodeFunction() range
                let amount = virtcol("'>") - virtcol("'<") + 1
                execute "normal gv"
                execute "normal! A" . "`" . "\<Esc>"
                execute "normal!" . amount . "h"
                execute "normal! i" . "`" . "\<Esc>"
            endfunction
* Third, add the `runtimepath` for the plugin
    * put the `set runtimepath+=,/home/cdutboy/.vim/plugin/vim_markdown_shortcuts.vim` to the `.vimrc` (note: should be the absolute path)
* Fourth, set the key map (in the `.vimrc`)

        vnoremap <buffer> <localleader>b :call MarkdownBoldFunction()<cr>
        vnoremap <buffer> <localleader>i :call MarkdownItalicFunction()<cr>
        vnoremap <buffer> <localleader>c :call MarkdownCodeFunction()<cr>
## search exactly
`:/\<your_exact_word\>`

## Search
### Basic searching
In normal mode you can search forwards by pressing `/` then typing your search pattern. Press Esc to cancel or press Enter to perform the search. Then press `n` to search forwards for the next occurrence, or `N` to search backwards. Type `ggn` to jump to the first match, or `GN` to jump to the last.
Search backwards by pressing `?` then typing your search pattern. Pressing `n` searches in the same direction (backwards), while `N` searches in the opposite direction (forwards).

### Searching for the current word
In normal mode, move the cursor to any word. Press `*` to search forwards for the next occurrence of that word, or press `#` to search backwards.
Using `*` or `#` searches for the exact word at the cursor (searching for *rain* would not find *rainbow*).
Use `g*` or `g#` if you don't want to search for the exact word.

### More searching
Vim maintains a search history. Type `/` or `?` and use the arrow up/down keys to recall previous search patterns. You can edit a pattern, and press Enter to search for something different.

### Case sensitivity
By default, searching is case sensitive (searching for "the" will not find "The").
With the following in your vimrc (or entered via a toggle mapping), searching is not case sensitive:
`:set ignorecase`
Now the command `/the` will find "the" or "The" etc. You can use `\c` to force a pattern to be case insensitive, or `\C` to force a pattern to be case sensitive. For example, the search `/the\c` is always case insensitive, and `/the\C` is always case sensitive, regardless of the `ignorecase` option.
If `ignorecase` is on, you may also want:
`:set smartcase`
When `ignorcase` and `smartcase` are both on, if a pattern contains an uppercase, it is case sensitive, otherwise, it is not. For example, `\The` would find only "The", while `/the` would find "the" or "The" etc.
The `smartcase` option only applies to search patterns that you type; it does not apply to `*` or `#` or `gd`. If you press `*` to search for a word, you can make `smartcase` apply by pressing `/` then up arrow then Enter (to repeat the search from history).

### Finding a whole word
In a program, you may want to search for an identifier named `i`. However, entering the search `/i` will find every hit, including the "i" in words like "if" and "while". In a pattern, `\<` represents the beginning of a word, and `\>` represents the end of a word, so to find only the whole word "i", use the pattern:
`\<i\>`
The pattern `\<i` finds all words that start with "i", while `i\>` finds all words that end with "i".

### Finding this or that
A search pattern can use `\|` to search for something or something else. For example, to search for all occurrences of "red" or "green" or "blue", enter the following search pattern (in normal mode, press `/` then type the pattern, then press Enter):
`red\|gree\|blue`
To replace all instances of "red" or "green" or "blue" with "purple", enter:
`:%s/red\|green\|blue/purple/g`
However, the above pattern finds "red" in "bored", so the substitute would change "bored" to "bopurple". If that is not what you want, use the following pattern to find only the whole words "red" or "green" or "blue":
`\<\(red\|green\|blue\)\>`
In a pattern, `\<` and `\>` respectively specify the beginning and end of a word, while `\(` and `\)` respectively specify the beginning and end of a group (the pattern `\<red\|green\|blue\>`, without escaped parentheses, would find "red" occurring at the beginning of a word, or "green" occurring anywhere, or "blue" occurring at the end of a word).
After searching with the command `\<\(red\|green\|blue\)\>` you could changes the whole words "red" or "green" or "blue" to "purple" by entering the following (the search pattern is empty in this command, so it uses the last search):
`:%s//purple/g`
In a substitute, you can use `&` in the replacement to mean the "whole matched pattern" (everything that was found). For example, the following will insert quotes around all occurrences of the whole words "red" and "green" and "blue":
`:%s/\<\(red\|green\|blue\)\>/"&"/g`
If you do not want the whole matched pattern, you can use parentheses to group text in the search pattern, and use the replacement variable `\1` to specify the first group. For example, the following finds "color x" and replaces it with "colored x" where x is the whole word "red" or "green" or "blue":
`:%s/color \<\(red\|green\|blue\)\>/colored \1/g`

### Finding two words in either order
You can search for a line that contains two words, in any order. For example, the following pattern finds all lines that contain both "red" and "blue", in any order:
`.*red\&.*blue`
In a pattern, `\&` separates alternates, each of which has to match at the same position. The two alternates in this example are:
* `.*red` (will match all characters from the beginning of a line to end of the last "red");and
* `.*blue` (will match all characters from the beginning of a line to the end of the last "blue").
A line which contains both "red" and "blue" will match both alternates, starting at the beginning of the line. The pattern `.*red\&.*blue` finds the *last* alternate (but only if all alternates match at the same position), so if you are highlighting matches, you will see test matched by `.blue` highlighted.
An alternative procedure is to use a pattern that explicitly finds "red" followed by "blue", or "blue" followed by "red":
`\(red.*blue\)\|\(blue.*red\)`
To search for lines that contain only the whole words "red" and "blue", in either order, use one of the following patterns:
`.*\<red\>\&.*\<blue\>`
`\(\<red\>.*\<blue\>\)\|\(\<blue\>.*\<red\>\)`


### Escape special characters
Certain special characters (`/ & ! . ^ * $ \ ?`) have special significance to the search process and must be "escaped" when they are used in a search. To escape a special character, precede it with a backslash (\). For example, to search for the string "anything?" type `/anything\?` and press Return.
You can use these special characters as commands to the search function. If you want to search for a string that includes one or more of the characters, you must precede the special character with a backslash. To escape a backslash itself, type `\\`.

\#|Matching
---|---
`.`|any character except new line
`\s`|whitespace character
`\d`|digit
`\i`|lowercase character
`\u`|uppercase character
`\S`|non-whitespace character
`\w`|word character
`\.`|dot
` `|space (spaces and numbers are not special characters)

### Refining the Search
* To match the beginning of a line, start the search string with a caret(^). For example, to find the next line beginning with "Search", type:
    `/^Search`
* To match the end of a line, end the search with a dollar sign (`$`). For example, to find the next line ending with "search.", type:
    `/search\.$`
    Note that the period is escaped with a backslash.
* To match the beginning of a word, type `\<` at the beginning of the string; to match the end of a word, type `\>` at the end of the string. Thus, to match a word, rather than a string, combine the end-of-word and beginning-of-word tags in the search pattern. For example, to find the next occurrence of the word-as opposed to the string-"search",type:
    `/\<search\>`
* To match any character, type a period(`.`) in the string at the location to be matched. For example, to find the next occurrence of "disinformation" or "misinformation," type:
    `/.isinformation`
Because this is a search for a string and not a word, this search pattern might also find constructions as "misinfornationalist" and "disinformationism."
* To search for alternative characters in a string, enclose the alternatives in brackets. The search pattern `/[md]<string>` finds strings that begin with either "m" or "d". Conversely, `/[d-m]<string>` finds strings that begin with any letter from "d" through "m."
* To match zero or more occurrences of the last character, type an asterisk(`*`) in the string. You can effectively combine brackets and the asterisk to look for well-defined alternatives. For example, to find all strings beginning with "a" through "z" and ending with "isinformation" and to find all occurrences of the string "isinformation", type:
    `/[a-z]*isinformation`


## Substitute

### Range of Operation, Line Addressing and Marks

`:range s[ubstitute]/pattern/string/cgiI`
For each line in the *the range* replace a match of *the pattern* with *the string* where:

Option|Meaning
---|---
`c`|Confirm each substitute
`g`|Replace all occurrences in the line (without `g`-only first).
`i`|Ignore case for the pattern.
`I`|Don't ignore case for the pattern.


Range Specifier|Description
---|---
`<number>`|an absolute line number
`.`|the current line
`$`|the last line in the file
`%`|the whole file. The same as `1,$`
`'t`|position of mark "t"
## DrawIt
### Install
*DrawIt* is now distributed as a vimball.
* [Download](https://www.vim.org/scripts/script.php?script_id=40&quot;)
* `vim DrawIt.vba.gz`
* `:so %`
* `:q`
### Start and Stop
* to start: `:DIstart`
* to stop: `DIstop`
### Two modes: Draw or Erase
Using space to toggle
### to draw lines

              Home Up  Pgup
               \   |   /
                \  |  /
                 \ | /
                  \|/
        Left-------/-----------Right
                  /|\
                 / | \
                /  |  \
               /   |   \
              /    |    \
             /     |     \
            End   Down   Pgdn
### to draw arrows
* `>` `<` `^` `v` for normal arrows
* `\>` `\<` `\^` `\v` for large arrows
### visual block
`C-v` into visual block mode
* `\a`(`\l` without arrows) to draw a line for the selected block
* `\b` to draw a rectangle
* `\e` to draw an ellipse
### 位置有偏差时
用鼠标选中要移动的块，然后按住ctrl并拖动鼠标。
### 当要擦除一整快的内容时
用鼠标选中要擦除的部分，然后执行`r<space>`（相当于用空格替换）。

## 多屏操作
### 分屏
* `vim -On file1 file2 ...` to vertically
* `vim -on file1 file2 ...` to horizontally
* `ctrl+w s`
* `ctrl+w v`
* `:sp filename`
* `:vsp filename`
### switch and move
* `ctrl+w h/j/k/l` to switch on the orientation, `ctrl+w w` to switch to the next window
* `ctrl+w H/J/K/L` to move the current window's position
### 调整分屏大小
* `ctrl+w =`
* `ctrl+w -`
* `ctrl+w +`
### 浏览目录
* `:He`, `:He!`
* `:Ve`, `:Ve!`
* `:E`
* `-`：到上级目录
* `s`：对文件排序
* `x`：执行文件
* `R`：修改文件名称
* `D`：删除文件
* `回车`：进入子目录
### 同步滚动
`set scb`, `set noscb`: need to run on every window
### 关闭分屏
`ctrl+w c` or `ctrl+w q`
## Copy or delete matching lines
### Copy matching lines

        qaq
        :g/pattern/y A
        :let @+ =@a
The first command clears register a (:help q). The second appends all matching lines to that register (:help quotea). The third copies register a to the clipboard (register +) for easy pasting into another application. Replace pattern with what you want to search for, or omit it (:g//y A) to use the last search.
### Delete matching lines

        :g/pattern/d
        :g//d
The first of the following commands deletes all lines containing pattern, while the second deletes all lines matching the last search.

### Delete not matching lines

    :v/pattern/d
    :v//d
Use `:v//d` to delete all lines that do not match the last search pattern, or `:v/pattern/d` to delete all lines that do not match the given pattern.
## remove BOM
* `: set bomb?`
* `: set nobomb`
* `wq`
* `sudo vim -c "set nobomb" -c wq! 1-3alpha.txt`
* `find . -type f -name "*.txt" -exec vim -c "set nobomb" -c wq! {} \;`
## vim 高级替换查找
* `:s/vivian/sky/` 替换当前行第一个 vivian 为 sky
* `:s/vivian/sky/g` 替换当前行所有 vivian 为 sky
* `:n,$s/vivian/sky/` 替换第 n 行开始到最后一行中每一行的第一个 vivian 为 sky
* `:n,$s/vivian/sky/g` 替换第 n 行开始到最后一行中每一行所有 vivian 为 sky
* n 为数字，若 n 为 .，表示从当前行开始到最后一行
* `%s/vivian/sky/`（等同于 :g/vivian/s//sky/） 替换每一行的第一个 vivian 为 sky
* `:%s/vivian/sky/g`（等同于 :g/vivian/s//sky/g） 替换每一行中所有 vivian 为 sky
* `:s/vivian/sky/` 替换当前行第一个 vivian 为 sky
* `:s/vivian/sky/g` 替换当前行所有 vivian 为 sky
* 删除文本中的^M
 问题描述：对于换行,window下用回车换行(`0A0D`)来表示，Linux下是回车(`0A`)来表示。这样，将window上的文件拷到Unix上用时，总会有个`^M`.请写个用在unix下的过滤windows文件的换行符(0D)的shell或c程序。
`:%s/^M$//g`
* `:s/str1/str2/` 用字符串 str2 替换行中首次出现的字符串 str1
* `:s/str1/str2/g` 用字符串 str2 替换行中所有出现的字符串 str1
* `:.,$ s/str1/str2/g` 用字符串 str2 替换正文当前行到末尾所有出现的字符串 str1
* `:s/^/"`                  用"注释当前行
* `:2,50s/^/"`              在2~50行首添加"注释
* `:.,+3s/^/"`              用"注释当前行和当前行后面的三行
* `:%s/^/"`                 用"注释所有行
* 转义
    而`\e`表示`<esc>`；`\t`表示`<tab>`；`\r`表示`<cr>`；`\b`表示`<bs>`
    使用`\n`可以表示一个换行；而`\s`表示匹配空白，注意是空白不是空格。`\_s`表示匹配换行或者空格；`\_a`表示匹配换行或者一个字母。比 如：`/the\nword`查找以the结束并且下一行以word开始的行的位置。`/the\_sword`查找the和word之间以空白或者换行分割的位 置。`/the\_s\+word`表示the和word之间可以有多个空白。`\+`的含义可以在后面找到。
* `\<`可以限定找到是以指定字符串开始的单词。比如`/\<the`可以找到以the开始在字符串，但是会忽略在单词中间包含the的字符串。而`\>`则是限定必须是以指定字符串结尾的单词。
* 输入`/^string`查找以string开始的行，并且光标停留在这个string的第一个字符。输入`/string$`则查找以string结束的行，并将光标停留在这个string的第一个字符。这个模式不会忽略前导或者后置的空格。
* 句号`.`可以匹配任何一个字符。例如`/t.e`可以找到the或者tae或者tue。
* 可重复的字符。
    * 使用`*`表示它前面的字符可以重复多次或者0次。比如`/be*`可以匹配b,be,bee,beee等等。但是这也会包含b，因为e重复0后是空。如果要匹配诸如be,bebe,bebebe的字符串可以使用\(和\)把他们包括起来，形如：`/\(be\)*`。
    * 使用`\+`来限定为重复至少一次到无数次。如：`/be\+`可以匹配be,bee,bee等等。
    * 重复0次或者一次。`\=`可以指定重复0次或者一次。`/strings\=`表示匹配string或者strings。这在查找单词的复数形式特别有用.
    * 指定重复的次数。`\{n,m}`可以指定重复n到m次。比如：`/be\{2,4}`将会匹配bee,beee,beeee。同样可以使用`\{,4}`表示匹配0到4次；`\{4,}`表示4次到无数次；`\{4}`表示重复4次。
* 匹配列表中的一个。使用一个以`\|`分割的列表，可以表示匹配列表中任何一项。比如`/one\|two`表示查找one或者two；`/one\|two\|three`表示查找one或者two或者three。
* 一个复杂的实例：`/end\(if\|while\|for\)`将会查找endif，endwhile以及endfor。
* 殊的字符集合
    * 使用`[0-9]`可以表示一个0到9范围的字符。比如`/string[1-5]`表示查找string1,string2,string3,string4,string5。
    * 使用`\d`也可以表示0到9的数字，这个选项可以代替[0-9]。`\D`表示非数字代替[^0-9]；`\x`表示十六进制数代替[0-9a- fA-F]；`\X`表示非十六进制数代替[^0-9a-fA-F]；`\s`表示空白字符代替[ ] (<Tab> 和<Space>)；`\S`表示非空白字符代替[^ ] (除<Tab> 和<Space>之外)；`\l`表示小写字母代替[a-z]；`\L`表示非小写字母代替[^a-z]；`\u`表示大写字母代替[A-Z]；`\U`表示 非大写字母代替[^A-Z]
    * 处理方式符号c表示在进行替换前需要用户进行确认。这时你可以选择(y/n/a/q/1/^E/^Y）:y表示同意当前替换；n表示不同意当前 替换；a表示替换当前和后面的并且不再确认；q表示立即结束替换操作；1表示把当前的替换后结束替换操作；^E向上滚屏^Y向下滚屏，用来帮助查看前后内 容以决定进行操作。
* 正则表达式首要的任务就是判断匹配与否，这根据其规则是不难办到的，毕竟那规则定的跟数学公式一般，而数学的确定性是有目共睹的。但是要将它应用到查找与替换中来，还是会产生一些问题的，本文的宗旨就是描述这些问题的解决之道。
  先就搜索而言，假使你想搜索一处数字，用正则表达式 `\d\+` 进行搜索，而文件中有一处数字是 123，这自然是能匹配的，但问题是这个正则表达式不但能匹配 123，还能匹配 1、2、3、12、23，如果你启用了高亮搜索功能，那现在vim应该高亮哪一部分？
  这就是“吞多少”的问题，正则表达式能同时匹配一个目标字符串的整体和部分，但搜索的结果必须是确定的，所以就需要约定一种规则来达成这种确定性。
    vim规定，星号*，加号\+，等号\=或者问号\?，以及大括号\{m,n}都尽可能多的吞掉字符，也就是所谓的“贪婪”法则，在这规定下，尽管正则表达式能同时匹配目标字符串的整体和部分，但搜索结果将是整体，高亮显示的也是整个目标字符串。如果希望尽可能少的匹配，对于星号而言，它的底限是零次，那只要修正正则表达式，去掉星号修饰的那一部分就行了，加号也一样，只是需要去掉加号，而等号和问号也是直接去掉就行，**对于大括号\{m,n}，希望尽可能少的匹配可以使用负数的形式\{-m,n}，这样它就匹配元素的m到n次出现，但它的搜索结果是最少的那一部分，例如用正则表达式\d\{-2,5}去搜索2到5个数字，而文件中出现了12345，则它搜索出来的结果是12，而不是12345，而下一次出现则是34，依此类推。**
    解决了“吞多少”的问题，接下来再看看替换所面临的挑战。
    在替换过程中，正则表达式只是用来搜索需要执行替换操作的位置，确定出需要替换的文本块的两个边界后，要使用新的内容进行替换，如果这个新的内容是一段与搜索内容无关的固定文本，这没啥好说的，但是有时这个新的内容可能要依赖于要被替换掉的旧内容，这听起来像数学语言一样，还是举个例子形象点，假如我的文件中的所有日期都是形如 2015-06-12 的格式，我现在要将它们都替换成 06/12/2015 的格式，啊哈，这个新的内容的年月日部分是来自于要被替换掉的旧内容，这就引出了正则表达式的第二个问题：“吐出来”。
    为解决上述问题，可以在正则表达式中，将用来匹配希望正则表达式“吐出来”的那一部分子表达式用括号括起来，比如上面日期的正则表达式是 \d\{4}-\d\{2}-\d\{2}，我希望它把年月日这三个数字给吐出来，就将用来匹配这三个数字的部分括起来：\ (\d\{4}\ )-\ (\d\{2}\ )-\ (\d\{2}\ )，然后在用来替换旧内容的新内容中用\1、\2、\3这样的格式来引用被正则表达式吐出来的各个子字符串，而这个顺序是由正则表达式中左括号出现的先后来决定的，这样\1将是年份，\2是月份，\3是天数，于是用于替换的新内容可以写成 \2/\3/\1，即将 2015-06-12 替换成 06/12/2015。但要说明一点，由于替换命令s中是用左斜杠区分命令的各个部分，所以这个用于替换的新内容中如果本身也包含左斜杠，需要去掉它的转义，即在其前加上反斜杠，所以完整的命令就是 :%s/\ (\d\{4}\ )-\ (\d\{2}\ )-\ (\d\{2}\ )/\2\/\3\/\1/g，当然你也可以用井号来作分隔符而不用进行这个转义操作，好了，现在你开始吐槽它的可读性吧。
    补充说明一点，上面使用了\1、\2等来引用正则表达式引用的各个部分，如果想引用匹配的整体，除了在正则表达式整体加上一个括号外，也可以直接使用\0来引用它，在上文中，\0就是整个日期字符串。利用\0，你可以使用命令 :%s/正则表达式/\0\0\0/g 在全文中将某个模式字符串由一个复制成若干个，而这却是由替换命令来完成的！
   ???在替换命令中还有一个用于匹配指定位置的特殊字符，\zs和\ze，它俩不匹配任何字符，仅仅是一个位置标记，就好比^和$分别匹配行首和行尾一样，例如你想把 forever 中的 for 改成 FOR，但又不希望 forest 中的 for 有任何变化，你除了使用 :s/forever/FORever/g 之外也可以使用 :s/\zsfor\zeever/FOR/g 来完成这一点，这在有时非常有用，因为它搜索的条件更精确，而替换的只是某一部分。
## [vim高级查找替换实例](substitute_commands.txt)
