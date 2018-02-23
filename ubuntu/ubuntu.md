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
## 截屏
### shutter <a name=shutter></a>
#### SYNOPSIS
       shutter [options]
#### capture mode options
* -s, --select=[X,Y,WIDTH,HEIGHT]
    Capture an area of the screen. Providing X,Y,WIDTH,HEIGHT is optional.
* -f,--full
    Capture the entire screen.
* -w, --window=[NAME_PATTERN]
    Select a window to capture. Providing a NAME_PATTERN (Perl-style reges) ist optional.
* -a, --active
    Capture the current active window.
* --section
    Capture a section. You will be able to select any child window by moving the mouse over it.
* --web=[URL]
    Capture a webpage. Providing an URL ist optional.
* -r, --redo
    Redo last screenshot.
#### setting options
* -P, --profile=NAME
    Load a specific profile on startup.
* -o, output=FILENAME
    Specify a filename to save the screenshot to (overwrites any profile-related setting).
    Supported image formats: You can save to any popular image format (e.g. jpeg, png, gif, bmp). Additionally it is possible to save to pdf, ps or svg.
    Please note: There are several wildcards available, like
    %Y = year
    %m = month
    %d = day
    %T = time
    \$h = height
    \$w = width
    \$name = multi-purpose (e.g. window title)
    \$nb_name = like $name but without blanks in resulting strings
    \$profile = name of current profile
    \$R = random char (e.g. $RRRR = ag4r)
    %NN = counter
    As an example: shutter -f -e -o './%y-%m-%d_$w_$h.png' would create a file named '11-10-28_1280_800.png' in the current directory.
* -d, --delay=SECONDS
    Wait n seconds before taking a screenshot.
* -c, --include_cursor
    Include cursor when taking a screenshot.
* -C, --remove_cursor
    Remove cursor when taking a screenshot.
#### application options
* -e, --exit_after_capture
    Exit after the first capture has been made. This is useful when using Shutter in scripts. 
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
### Description
ffmpeg is a very fast video and audio converter that can also grab from a live audio/video source. It can also convert between arbitrary sample rates and resize video on the fly with a high quality polyphase filter. 
ffmpeg reads from an arbitrary number of input "files" (which can be regular files, pipes, network streams, grabbing devices, etc.), specified by the -i option, and writes to an arbitrary number of output "files", which are specified by a plain output url. Anything found on the command line which cannot be interpreted as an option is considered to be an output url. 
Each input or output url can, in principle, contain any number of streams of different types (video/audio/subtitle/attachment/data). The allowed number and/or types of streams may be limited by the container format. Selecting which streams from which inputs will go into which output is either done automatically or with the -map option (see the Stream selection chapter). 
To refer to input files in options, you must use their indices (0-based). E.g. the first input file is 0, the second is 1, etc. Similarly, streams within a file are referred to by their indices. E.g. 2:3 refers to the fourth stream in the third input file. Also see the Stream specifiers chapter. 
As a general rule, options are applied to the next specified file. Therefore, order is important, and you can have the same option on the command line multiple times. Each occurrence is then applied to the next input or output file. Exceptions from this rule are the global options (e.g. verbosity level), which should be specified first. 
Do not mix input and output files – first specify all input files, then all output files. Also do not mix options which belong to different files. All options apply ONLY to the next input or output file and are reset between files. 
* To set the video bitrate of the output file to 64Kbit/s:
    `ffmpeg -i input.avi -b:v 64k -bufsize 64k output.avi`
* To force the frame rate of the output file to 24fps:
    `ffmpeg -i input.avi -r 24 output.avi`
* To force the frame rate of the input file (valid for raw formats only) to 1 fps and the frame rate of the output file to 24 fps:
    `ffmpeg -r 1 -i input.avi -r 24 output.avi`
### Detailed description
The transcoding process in ffmpeg for each output can be described by the following diagram: 
![detailed description](ffmpeg_detailed.png)
ffmpeg calls the libavformat library (containing demuxers) to read input files and get packets containing encoded data from them. When there are multiple input files, ffmpeg tries to keep them synchronized by tracking lowest timestamp on any active input stream. 
Encoded packets are then passed to the decoder (unless streamcopy is selected for the stream, see further for a description). The decoder produces uncompressed frames (raw video/PCM audio/...) which can be processed further by filtering (see next section). After filtering, the frames are passed to the encoder, which encodes them and outputs encoded packets. Finally those are passed to the muxer, which writes the encoded packets to the output file. 
#### 3.1 Filtering
Before encoding, ffmpeg can process raw audio and video frames using filters from the libavfilter library. Several chained filters form a filter graph. ffmpeg distinguishes between two types of filtergraphs: simple and complex. 
#### 3.2 Stream copy
Stream copy is a mode selected by supplying the copy parameter to the -codec option. It makes ffmpeg omit the decoding and encoding step for the specified stream, so it does only demuxing and muxing. It is useful for changing the container format or modifying container-level metadata. The diagram above will, in this case, simplify to this: 
![stream_copy](stream_copy.png)
Since there is no decoding or encoding, it is very fast and there is no quality loss. However, it might not work in some cases because of many factors. Applying filters is obviously also impossible, since filters work on uncompressed data. 
### 5 Options
All the numerical options, if not specified otherwise, accept a string representing a number as input, which may be followed by one of the SI unit prefixes, for example: 'K', 'M', or 'G'.
If 'i' is appended to the SI unit prefix, the complete prefix will be interpreted as a unit prefix for binary multiples, which are based on powers of 1024 instead of powers of 1000. Appending 'B' to the SI unit prefix multiplies the value by 8. This allows using, for example: 'KB', 'MiB', 'G' and 'B' as number suffixes. 
Options which do not take arguments are boolean options, and set the corresponding value to true. They can be set to false by prefixing the option name with "no". For example using "-nofoo" will set the boolean option with name "foo" to false. 
#### 5.1 Stream specifiers
Some options are applied per-stream, e.g. bitrate or codec. Stream specifiers are used to precisely specify which stream(s) a given option belongs to. 
#### 5.2 Generic options
These options are shared amongst the ff* tools. 
#### 5.3 AVOptions
#### Main options
## youtube-dl
## mplayer
Q = Quit
P = Pause
Up arrow = Jump forward in file more
Right arrow = Jump forward in file less
Down arrow = Jump back in file more
Left arrow = Jump back in file less
) = Volume up
( = Volume down
M = Volume mute
F = Full screen view
O = On-screen display
V = Toggle subtitles in video
