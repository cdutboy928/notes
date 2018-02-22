# Ubuntu skills
## how to get a colored bash in command line
Open ~/.bashrc in text editor and uncomment line:
`#force_color_prompt=yes`
to be:
`force_color_prompt=yes`
save then execute source ~/.bashrc
## had link and soft link
![hard and soft link](hard_link_and_soft_link.jpg)
"An example is worth a hundred paragraphs..."

Create two files:

    $ touch blah1   
    $ touch blah2

Enter some data into them:

    $ echo "Cat" > blah1
    $ echo "Dog" > blah2

And as expected:

    $cat blah1; cat blah2
    Cat
    Dog

Let's create hard and soft links:

    $ ln blah1 blah1-hard
    $ ln -s blah2 blah2-soft

Let's see what just happened:

    $ ls -l
    blah1
    blah1-hard
    blah2
    blah2-soft -> blah2

Changing the name of blah1 does not matter:

    $ mv blah1 blah1-new
    $ cat blah1-hard
    Cat

blah1-hard points to the inode, the contents, of the file - that wasn't changed.

    $ mv blah2 blah2-new
    $ ls blah2-soft
    blah2-soft
    $ cat blah2-soft  
    cat: blah2-soft: No such file or directory

The contents of the file could not be found because the soft link points to the name, that was changed, and not to the contents.
Similarly, If blah1 is deleted, blah1-hard still holds the contents; if blah2 is deleted, blah2-soft is just a link to a non-existing file.
**Note: Cannot make hardlink for a directory!**

    cdutboy@ubuntu:~/testlink$ touch hard
    cdutboy@ubuntu:~/testlink$ echo "cat" > hard
    cdutboy@ubuntu:~/testlink$ ls
    hard
    cdutboy@ubuntu:~/testlink$ cat hard
    cat
    cdutboy@ubuntu:~/testlink$ ln hard hardlink
    cdutboy@ubuntu:~/testlink$ ls
    hard  hardlink
    cdutboy@ubuntu:~/testlink$ cat hardlink
    cat
    cdutboy@ubuntu:~/testlink$ echo "dog" > hard
    cdutboy@ubuntu:~/testlink$ cat hard
    dog
    cdutboy@ubuntu:~/testlink$ cat hardlink
    dog
## 录屏软件
### peek
* installation
         sudo add-apt-repository ppa:peek-developers/stable
         sudo apt-get update
         sudo apt-get install peek
* how to use
    * peek
    * 需要手动调整录屏区域，而且不能动态地跟着移动的窗口。
    * 可以录gif.
### kazam
* installation 
      sudo apt-get install kazam
* how to use
    * kazam
    * 可以录全屏和窗口，但是不能录gif
### 视频转GIF
## [ffmpeg](https://www.ffmpeg.org/ffmpeg.html)
### 1 Synopsis
`ffmpeg [global_options] {[input_file_options] -i input_url} ... {[output_file_options] output_url} ... `

