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
