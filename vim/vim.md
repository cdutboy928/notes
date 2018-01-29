# Vim Skills
## insert special characters
* *Note: Ctrl+Shift+\_to insert special characters.*
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
## vimim
### installation
* 
