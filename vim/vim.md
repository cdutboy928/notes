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
**注意:
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
    Or
        hi Todo ctermbg=red guibg=darked
        match Todo /???/
    Or
        hi Title ctermbg=red guibg=darked
        match Title /???/
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
