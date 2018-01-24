# Markdown Learning
*Note:  \ for trans, e.g. \\_ \\\*   \\\*\\*    
        There is no need to trans when in code format
## 1 Text format  
* Italics and Bold  
 * \_Italics\_: _Italics_
 * \*\*Bold\*\*: **Bold**
 * \*\*\_both Italics and Bold\_\*\*: **_both Italics and Bold_**
 * \_\*\*both Italics and Bold\*\*\_:_**both Italics and Bold**_
* strike through
     \~\~text\~\~ : ~~text~~
* Emphasize
    \*Emphasize\* : *Emphasize*
* code
 * inline code
        \`inline code\` : `inline code`
        _*Note: can only be used in one line*_
 * code block 
          indenting by 4 spaces will turn an entire paragraph into a code-block
* Headers
 * \# Header One : 
     # Header One
 * \# Header Two :
     ## Header Two
* links
 * inline links
           [Visit Github](www.github.com) :
     [Visit Github](www.github.com)
        _Although it might make for an awkward experience, you can make links within headings too._
 * reference link
            Do you want to [see something fun][a fun place]?
            Well, I do have [another website for you][another fun place].
              [a fun place]:www.zombo.com
              [another fun place]:www.stumbleupon.com

   Do you want to [see something fun][a fun place]?
   Well, I do have [another website for you][another fun place].
   [a fun place]: www.zombo.com
   [another fun place]: www.stumbleupon.com

* image
 * inline image links
   * display the inline image
              ![Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
        ![Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
   * does not display the inline image
              [Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
          [Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
 * reference image links
    * display the reference image
              ![The first father][First Father]
              ![The second father][Second Father]
                  [First father]: http://octodex.github.com/images/founding-father.jpg
                  [Second father]: http://octodex.github.com/images/foundingfather_v2.png
![The first father][First Father]
![The second father][Second Father]
[First father]: http://octodex.github.com/images/founding-father.jpg
[Second father]: http://octodex.github.com/images/foundingfather_v2.png
    * does not display the reference image
              [The first father][First Father]
              [The second father][Second Father]
                  [First father]: http://octodex.github.com/images/founding-father.jpg
                  [Second father]: http://octodex.github.com/images/foundingfather_v2.png
   [The first father][First Father]
   [The second father][Second Father]
   [First father]: http://octodex.github.com/images/founding-father.jpg
   [Second father]: http://octodex.github.com/images/foundingfather_v2.png
   *Note: the text in the brackets is the alt text or the descriptive text for the image.*

