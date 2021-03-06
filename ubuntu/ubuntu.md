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
    Capture a webpage. Providing an URL list optional.
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
#### 将视频转换为GIF
`apt install ffmpeg imagemagick`
`ffmpeg -ss 00:00:20 -i input.mp4 -to 10 -r 10 -vf scale=200:-1 output.gif`
#### 合并多个GIF文件
`convert -delay 120 -loop 0 *.gif output.gif`
 * `-delay 120`:表示GIF动画速度
 * `-loop 0`:表示无限循环
#### 从jpg图片序列创建gif动图
`convert -delay 120 -loop 0 *.jpg linux.gif`
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
### Some FFmpeg commands for beginners <a name=ffmpegcommands></a>
The typical syntax of the FFmpeg command is:
      ffmpeg [global_options] {[input_file_options] -i input_url} ... {[output_file_options] output_url} ...
1. Getting audio/vidio file information
       ffmpeg -i video.mp4
     Sample output:
        ffmpeg version 3.3 Copyright (c) 2000-2017 the FFmpeg developers
        built with gcc 6.3.1 (GCC) 20170306
        configuration: --prefix=/usr --disable-debug --disable-static --disable-stripping --enable-avisynth --enable-avresample --enable-fontconfig --enable-gmp --enable-gnutls --enable-gpl --enable-ladspa --enable-libass --enable-libbluray --enable-libfreetype --enable-libfribidi --enable-libgsm --enable-libiec61883 --enable-libmodplug --enable-libmp3lame --enable-libopencore_amrnb --enable-libopencore_amrwb --enable-libopenjpeg --enable-libopus --enable-libpulse --enable-libschroedinger --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libv4l2 --enable-libvidstab --enable-libvorbis --enable-libvpx --enable-libwebp --enable-libx264 --enable-libx265 --enable-libxcb --enable-libxvid --enable-netcdf --enable-shared --enable-version3
        libavutil 55. 58.100 / 55. 58.100
    	libavcodec 57. 89.100 / 57. 89.100
    	libavformat 57. 71.100 / 57. 71.100
    	libavdevice 57. 6.100 / 57. 6.100
    	libavfilter 6. 82.100 / 6. 82.100
    	libavresample 3. 5. 0 / 3. 5. 0
    	libswscale 4. 6.100 / 4. 6.100
    	libswresample 2. 7.100 / 2. 7.100
    	libpostproc 54. 5.100 / 54. 5.100
    	Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'video.mp4':
    	Metadata:
    	major_brand : isom
    	minor_version : 512
    	compatible_brands: isomiso2avc1mp41
    	encoder : Lavf57.22.100
    	Duration: 00:43:18.69, start: 0.000000, bitrate: 1039 kb/s
    	Stream #0:0(und): Video: h264 (High) (avc1 / 0x31637661), yuv420p, 1280x714 [SAR 1071:1072 DAR 120:67], 899 kb/s, 23.98 fps, 23.98 tbr, 24k tbn, 47.95 tbc (default)
    	Metadata:
    	handler_name : VideoHandler
    	Stream #0:1(und): Audio: aac (LC) (mp4a / 0x6134706D), 48000 Hz, stereo, fltp, 132 kb/s (default)
    	Metadata:
    	handler_name : SoundHandler
    	At least one output file must be specified
_As you see in the above output, FFmpeg displays the media file information along with FFmpeg details such as version, configuration details, copyright notice, build and library options etc._
If you don’t want to see the FFmpeg banner and other details, but only the media file information, use -hide_banner flag like below.
		ffmpeg -i video.mp4 -hide_banner
Sample output:
![ffmpeg -hide_banner](ffmpeg_hide_banner.png)
2. Converting video files to different formats
FFmpeg is powerful audio and video converter, thus It’s possible to convert media files between different formats. Say for example, to convert mp4 file to avi file, run:
		ffmpeg -i video.mp4 video.avi
For example, to convert youtube flv format videos to mpeg format, run:
		ffmpeg -i video.flv video.mpeg
If you want to preserve the quality of your source video file, use ‘-qscale 0’ parameter:
		ffmpeg -i input.webm -qscale 0 output.mp4
To check list of supported formats by FFmpeg, run:
		ffmpeg -formats
3. Converting video files to audio files
To convert a video file to audio file, just specify the output format as .mp3, or .ogg, or any other audio formats.
		ffmpeg -i input.mp4 -vn -ab 320 output.mp3
lso, you can use various audio transcoding options to the output file as shown below.
		ffmpeg -i input.mp4 -vn -ar 44100 -ac 2 -ab 320 -f mp3 output.mp3
Here, 
 * -vn: Indicates that we have disabled video recording in the output file. 
 * -ar: Set the audio frequency of the output file. The common values are 22050, 44100, 48000 Hz. 
 * -ac: Set the number of audio channels. 
 * -ab: Indicates the audio bitrate. 
 * -f : Output file format. In our case, it's mp3 format. 
4. Change resolution of video files
Suppose, you want to set a particular resolution to a video file, you can use following command:
		ffmpeg -i input.mp4 -filter:v scale=1280:720 -c:a copy output.mp4
Or,
		ffmpeg -i input.mp4 -s 1280x720 -c:a copy output.mp4
The above command will set the resolution of the given video file to 1280×720.
Similarly, to convert the above file to 640×480 size, run:
		ffmpeg -i input.mp4 -filter:v scale=640:480 -c:a copy output.mp4
Or,
		ffmpeg -i input.mp4 -s 640x480 -c:a copy output.mp4
This trick will help you to scale your video files to smaller display devices such as tablets and mobiles.
5. Compressing video files
It is always better to reduce the media files size to lower size to save the harddisk’s space.
The following command will compress and reduce the output file’s size.
		ffmpeg -i input.mp4 -vf scale=1280:-1 -c:v libx264 -preset veryslow -crf 24 output.mp4
Please note that you will lose the quality if you try to reduce the video file size. You can lower that crf value to 23 or lower if 24 is too aggressive.
You could also transcode the audio down a bit and make it stereo to reduce the size by including the following options.
		-ac 2 -c:a aac -strict -2 -b:a 128k
6. Compressing audio files
Just compressing video files, you can compress audio files using -ab flag in order to save some disk space.
Let us say you have an audio file of 320 kbps bitrate. You want to compress it by changing the bitrate to any lower value like below.
		ffmpeg -i input.mp3 -ab 128 output.mp3
 The list of various available audio bitrates are:
   *  96kbps
   *  112kbps
   *  128kbps
   *  160kbps
   *  192kbps
   *  256kbps
   *  320kbps
7. Removing audio stream from a media file
If you don’t want to a audio from a video file, use -an flag.
		ffmpeg -i input.mp4 -an output.mp4
Here, ‘an’ indicates no audio recording.
The above command will undo all audio related flags, because we don’t audio from the input.mp4.
8. Removing video stream from a media file
Similarly, if you don’t want video stream, you could easily remove it from the media file using ‘vn’ flag. vn stands for no video recording. In other words, this command converts the given media file into audio file.
The following command will remove the video from the given media file.
		ffmpeg -i input.mp4 -vn output.mp3
You can also mention the output file’s bitrate using ‘-ab’ flag as shown in the following example.
		ffmpeg -i input.mp4 -vn -ab 320 output.mp3
9. Extracting images from the video
Another useful feature of FFmpeg is we can easily extract images from a video file. This could be very useful, if you want to create a photo album from a video file.
To extract images from a video file, use the following command:
		ffmpeg -i input.mp4 -r 1 -f image2 image-%2d.png
Here, 
 * -r: Set the frame rate. I.e the number of frames to be extracted into images per second. The default value is 25. 
 * -f: Indicates teh output format, i.e image format in our case.
 * image-%2d.png: Indicates how we want to name the extracted images. In this case, the names should start like image-01.png, image-02.png, image-03.png and so on. If you use %3d, then the name of images will start like image-001.png, image-002.png and so on. 

10. Cropping videos 
It is somewhat similar to change the resolution of the video file. let us say you want to a video with size 300×300. You could do that using command:
		ffmpeg -i input.mp4 -croptop 100 -cropbottom 100 -cropleft 300 -cropright 300 output.mp4
Please note that cropping videos will affect the quality. Do not do this unless it is necessary.
11. Convert a specific portion of a video
Sometimes, you might want to convert only a specific portion of the video file to different format. Say for example, the following command will convert the first 50 seconds of given video.mp4 file to video.avi format.
		ffmpeg -i input.mp4 -t 50 output.avi
Here, we specify the the time in seconds. Also, it is possible to specify the time in hh.mm.ss format.
12. Set the aspect ratio to video
You can set the aspect ration to a video file using -aspect flag like below.
		ffmpeg -i input.mp4 -aspect 16:9 output.mp4
The commonly used aspect ratios are:
    16:9
    4:3
    16:10
    5:4
    2:21:1
    2:35:1
    2:39:1
13. Adding poster image to audio files
You can add the poster images to your files, so that the images will be displayed while playing the audio files. This could be useful to host audio files in Video hosting or sharing websites.
		ffmpeg -loop 1 -i inputimage.jpg -i inputaudio.mp3 -c:v libx264 -c:a aac -strict experimental -b:a 192k -shortest output.mp4
14. Cut a video file into smaller clip
To trim down a video to smaller clip, we could the command like below.
		ffmpeg -i input.mp4 -ss 00:00:50 -codec copy -t 50 output.mp4
Here, 
 * -s: Indicates the starting time of the video clip. In our example, starting time is the 50th second. 
 * -t: Indicates the total time duration. 
15. Split video files into multiple parts
Some websites will allow you to upload only a specific size of video. In such cases, you can split the large video files into multiple smaller parts like below.
		ffmpeg -i input.mp4 -t 00:00:30 -c copy part1.mp4 -ss 00:00:30 -codec copy part2.mp4 
Here, -t 00:00:30 indicates a part that is created from the start of the video to the 30th second of video. -ss 00:00:30 shows the starting time stamp for the video. It means that the 2nd part will start from the 30th second and will continue up to the end of the original video file.
16. Joining multiple video parts into one
FFmpeg will also join the multiple video parts and create a single video file.
Create join.txt file that contains the exact paths of the files that you want to join. All files should be same format (same codec). The path name of all files should mentioned one by one like below.
		/home/sk/myvideos/part1.mp4
		/home/sk/myvideos/part2.mp4
		/home/sk/myvideos/part3.mp4
		/home/sk/myvideos/part4.mp4
Now, join all files using command:
		ffmpeg -f concat -i join.txt -c copy output.mp4
The above command will join part1.mp4, part2.mp4, part3.mp4, and part4,mp4 files into a single file called “output.mp4”.
        ffmpeg -i "concat:0119_0159.mpg|0228_0342.mpg" -c copy output.mpg
17. Add subtitles to a video file
We can also add subtitles to a video file using FFmpeg. Download the correct subtitle for your video and add it your video as shown below.
		ffmpeg -i input.mp4 -i subtitle.srt -map 0 -map 1 -c copy -c:v libx264 -crf 23 -preset veryfast output.mp4
18. Preview or test video or audio files 
You might want to preview to verify or test whether the output file has been properly transcoded or not. To do so, you can play it from your Terminal with command:
		ffplay video.mp4
![ffplay video](ffplay_video.png)
Similarly, you can test the audio files as shown below.
		ffplay audio.mp3
![ffplay video](ffplay_audio.png)
19. Increase/decrease video playback speed
FFmpeg allows you to adjust the video playback speed. To increase the video playback speed, run:
`ffmpeg -i inputvideo.mp4 -vf "setpts=0.5*PTS" outputvideo.mp4`
To decrease playback speed, run:
`ffmpeg -i inputvideo.mp4 -vf "setpts=4.0*PTS" outputvideo.mp4`
对视频进行加速时，如果不想丢帧，可以用-r 参数指定输出视频FPS
`ffmpeg -i input.mkv -an -r 60 -filter:v "setpts=0.5*PTS" output.mkv`
调整音频播放速度
`ffmpeg -i input.mkv -filter:a "atempo=2.0" -vn output.mkv`
同时调整音频视频
`ffmpeg -i input.mkv -filter_complex "[0:v]setpts=0.5*PTS[v];[0:a]atempo=2.0[a]" -map "[v]" -map "[a]" output.mkv`
20. Turn X images to a video sequence
        ffmpeg -f image2 -i image%d.jpg video.mpg
This command will transform all the images from the current directory (named image1.jpg, image2.jpg, etc…) to a video file named video.mpg.
21. Turn a video to X images 
        ffmpeg -i video.mpg image%d.jpg
This command will generate the files named image1.jpg, image2.jpg, …
The following image formats are also availables : PGM, PPM, PAM, PGMYUV, JPEG, GIF, PNG, TIFF, SGI.
22. Encode a video sequence for the iPod/iPhone
        ffmpeg -i source_video.avi input -acodec aac -ab 128kb -vcodec mpeg4 -b 1200kb -mbd 2 -flags +4mv+trell -aic 2 -cmp 2 -subcmp 2 -s 320x180 -title X final_video.mp4 
Explanations:
 * Source: source_video.avi
 * Audio codec: aac
 * Audio bitrate: 128kb/s
 * Video codec: mpeg4
 * Video bitrate: 1200kb/s
 * Video size: 320px par 180px
 * Generated video: final_video.mp4
23. Encode video for the PSP
        ffmpeg -i source_video.avi -b 300 -s 320x240 -vcodec xvid -ab 32 -ar 24000 -acodec aac final_video.mp4
Explanations:
 * Source : source_video.avi
 * Audio codec : aac
 * Audio bitrate : 32kb/s
 * Video codec : xvid
 * Video bitrate : 1200kb/s
 * Video size : 320px par 180px
 * Generated video : final_video.mp4
24. Extracting sound from a video, and save it as mp3
        ffmepg -i source_video.avi -vn -ar 44100 -ac 2 -ab 192k -f mp3 sound.mp3
Explanations:
 * Source video: source_video.avi
 * Audio bitrate: 192k/s
 * output format: mp3
 * Generated sound: sound.mp3
25. Convert a wav file to mp3
        ffmpeg -i son_origine.avi -vn -ar 44100 -ac 2 -ab 192k -f mp3 son_final.mp3
26. Convert .avi video to .mpg
        ffmpeg -i video_origin.avi video_final.mpg
27. Convert .mpg to .avi
        ffmpeg -i video_origin.mpg video_final.avi
28. Convert .avi to animated gif (uncompressed)
        ffmpeg -i video_origin.avi gif_anime.gif
29. Mix a video with a sound file
        ffmpeg -i son.wav -i video_origin.avi video_final.mpg
30. Convert .avi to .flv
        ffmpeg -i video_origin.avi -ab 56 -ar 44100 -b 200 -r 15 -s 320x240 -f flv video_final.flv
31. Convert .avi to dv
        ffmpeg -i video_origin.avi -s pal -r pal -aspect 4:3 -ar 48000 -ac 2 video_final.dv
Or:
        ffmpeg -i video_origin.avi -target pal-dv video_final.dv
32. Convert .avi to mpeg for dvd players
        ffmpeg -i source.video.avi -target pal-dvd -ps 2000000000 -aspect 16:9 final_video.mpeg
Explanations:
 * target pal-dvd: Output format
 * ps 2000000000 maximum size for the output file, in bits (here, 2 Gb)
 * aspect 16:9: Widescreen
33. Compress .avi to divx
        ffmpeg -i video_origin.avi -s 320x240 -vcodec msmpeg4v2 video_final.avi
34. Compress Ogg Theora to Mpeg dvd
        ffmpeg -i file.ogm -s 720x576 -vcodec mpeg2video -acodec mp3 film.mpg
35. Compress .avi to SVCD mpeg2
 * NTSC format:
            fmpeg -i video_origin.avi -target ntsc-svcd video_final.mpg
 * PAL format:
            ffmpeg -i video_origin.avi -target pal-svcd video_final.mpg
36. 截取一张352x240尺寸大小，格式为jpg的图片
        ffmpeg -i input_file -y -f image2 -t 0.001 -s 352x240 output.jpg
37. 把视频的前30帧转换成一个Animated Gif
        ffmpeg -i input_file -vframe 30 -y -f gif output.gif
38. 在视频的第8.01秒出截取230x240的缩略图
        ffmpeg -i input_file -y -f mjpeg -ss 8 -t 0.001 -s 230x240 output.jpg
39. 每隔一秒截一张图
        ffmpeg -i input_file -f image2 -vf fps=fps=1 out%d.png
40. 每隔20秒截一张图
        ffmpeg -i input_file -f image2 -vf fps=fps=1/20 out%d.png
41. 从视频中生成GIF图片
        ffmpeg -i input.mp4 -t 10 -pix_fmt rgb24 out.gif
42. 转换视频为图片（每帧一张图）
        ffmpeg -i out.mp4 out%4d.png
43. 图片转换为视频
        ffmpeg -f imge2 -i out%4d.png -r 25 video.mp4
44. 切分视频并生成M3U8文件
        ffmpeg -i input.mp4 -c:v libx264 -c:a aac -strict -2 -f hls -hls_time 20 -hls_list_size 0 -hls_wrap 0 output.m3u8
相关参数说明：
-i 输入视频文件
-c:v 输出视频格式
-c:a 输出音频格式
-strict
-f hls 输出视频为HTTP Live Stream（M3U8）
-hls_time 设置每片的长度，默认为2，单位为秒
-hls_list_size 设置播放列表保存的最多条目，设置为0会保存所有信息，默认为5
-hls_wrap 设置多少片之后开始覆盖，如果设置为0则不会覆盖，默认值为0。这个选项能够避免在磁盘上存储过多的片，而且能够限制写入磁盘的最多片的数量。
45. 分离视频音频流
        ffmpeg -i input_file -vcodec copy -an output_file_video //分离视频流
        ffmpeg -i input_file -acodec copy -vn output_file_audio //分离音频流
46. 视频解复用
        ffmpeg -i test.mp4 -vcoder copy -an -f m4v test.264
        ffmpeg -i test.avi -vcoder copy -an -f m4v test.264
47. 视频转码
        ffmpeg -i test.mp4 -vcoder h264 -s 352*278 -an -f m4v test.264 //转码为码流原始文件
        ffmpeg -i test.mp4 -vcoder h264 -bf 0 -g 25 -s 352-278 -an -f m4v test.264 //转码为码流原始文件
        ffmpeg -i test.avi -vcoder mpeg4 -vtag xvid -qsame test_xvid.avi //转码为封装文件 -bf B帧数目控制， -g 关键帧间隔控制， -s 分辨率控制
48. 视频封装
        ffmpeg -i video_file -i audio_file -vcoder copy -acoder copy output_file
49. 视频剪切
        ffmpeg -i test.avi -r 1 -f imge2 imge.jpeg //视频截图
        ffmpeg -i input.avi -ss 0:1:30 -t 0:0:20 -vcoder copy -acoder copy output.avi //剪切视频： -r 提取图像频率， -ss 开始时间， -t 持续时间。
        ffmpeg -i 180405.mpg -ss 02:28 -t 74 -c copy ~/work/videotodeal/0228_0342.mpg
50. 视频录制
        ffmpeg -i rtsp://hostname/test -vcoder copy out.avi
51. YUV序列播放
        ffplay -f rawvideo -video_size 1920x1080 input.yuv
52. YUV序列转AVI
        ffmpeg -s w*h -pix_fmt yuv420p -i input.yuv -vcoder mpeg4 output.avi
53. 常用参数说明
 * 主要参数
     * -i 设定输入流
     * -f 设定输出格式
     * -ss 开始时间
 * 视频参数
     * -b 设定视频流量，默认是200Kbit/s
     * -s 设定画面的宽和高
     * -aspect 设定画面的比例
     * -vn 不处理视频
     * -vcoder 设定视频的编码器，未设定时则使用与输入流相同的编解码器
 * 视频参数
     * -ar 设定采样率
     * -ac 设定声音的Channel数
     * -acodec 设定音频的Channel数
     * -an 不处理音频
54. 使用ffmpeg合并MP4文件
        ffmepg -i "Apache Sqoop Tutorial Part 1.mp4" -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate1.ts
        ffmepg -i "Apache Sqoop Tutorial Part 2.mp4" -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate2.ts
        ffmepg -i "Apache Sqoop Tutorial Part 3.mp4" -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate3.ts
        ffmepg -i "Apache Sqoop Tutorial Part 4.mp4" -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate4.ts
        ffmpeg -i "concat:intermediate1.ts|intermediate2.ts|intermediate3.ts|intermediate4.ts" -c copy -bsf:a aac_adtsoasc "Apache Sqoop Tutorial.mp4"
55. 使用ffmpeg转换flv到mp4
        ffmpeg -i out.flv -vcodec copy -acodec copy out.mp4
56. 视频添加水印
        ffmpeg -i out.mp4 -i sxyx2008@163.com.gif -filet_complex overlay="(main_w/2)-(overlay_w/2):(main_h/2)-(overlay/2)" output.mp4
参数解释：
    -i out.mp4(视频源)
    -i sxyx2008@163.com.gif(水印图片)
    overlay 水印的位置
    output.mp4 输出文件
57. 视频翻转和旋转
 * 翻转
            ffplay -i out.mp4 -vf hflip
            ffplay -i out.mp4 -vf vflip
 * 旋转
            ffplay -i out.mp4 -vf transpose=1
            ffplay -i out.mp4 -vf transpose=1,hflip
    语法：transpose={0,1,2,3}
       * 0:逆时针旋转90°然后垂直翻转
       * 1:顺时针旋转90°
       * 2:逆时针旋转90°
       * 3:顺时针旋转90°然后水平翻转
58. 添加字幕
        ffmpeg -i my_subtitle.srt my_subtitle.ass
        ffmpeg -i inputfile.mp4 -vf ass=my_subtitle.ass outputfile.mp4
一般我们见到的字幕以srt字幕为主，在ffmpeg里需要首先将srt字幕转化为ass字幕，然后就可以集成到视频中了(不是单独的字幕流，而是直接改写视频流)。
但是值得注意的是：
    my_subtitle.srt需要使用UTF8编码，老外不会注意到这一点，但是中文这是必须要考虑的；
59. 嵌入字幕
        ffmpeg -i input.mp4 -i subtitles.srt -c:s mov_text -c:v copy -c:a copy output.mp4
    在一个MP4文件里面添加字幕，不是把 .srt 字幕文件集成到 MP4 文件里，而是在播放器里选择字幕，这种集成字幕比较简单，速度也相当快
60. 锐化
语法：
        -vf unsharp=l_msize_x:l_msize_y:l_amount:c_msize_x:c_msize_y:c_amount
所有参数都是可选的，默认值是5:5:1.0:5:5:0.0
l_msize_x:水平亮度矩阵，取值范围是3-13，默认值为5
l_msize_y: 垂直亮度矩阵，取值范围3-13，默认值为5
l_amount: 亮度强度，取值范围-2.0-5.0，负数为模糊效果，默认值1.0
c_msize_x: 水平色彩矩阵，取值范围3-13，默认值5
c_msize_y: 垂直色彩矩阵，取值范围3-13，默认值5
c_amount: 色彩强度，取值范围-2.0-5.0，负数为模糊效果，默认值0.0
举例：
* NASA图片锐化举例
    ![unsharp](ffmpeg_unsharp.png)
    1. 是原图
    2. `-vf unsharp`
    3. `-vf unsharp=6:6:3`
    4. `-vf unsharp=6:6:-2`
* 使用默认值，亮度矩阵为5x5和亮度值为1.0
        ffmpeg -i input -vf unsharp output.mp4
* 高斯模糊效果（比较强的模糊效果）
        ffplay -f lavfi -i testxrc -vf unsharp=13:13:-2
* 降低锐化
        ffmpeg -i input -vf unsharp=6:6:-2 output.mp4
* ffmpeg预处理，增加亮度
        ffmpeg -i E:\music\1\1.mov -vf "scale=-1:720,unsharp=luma_msize_x=7:luma_msize_y=7:luma_amount=1.5" -f mp4 E:\music\1\out_sharpen.mp4
* 增加亮度
        ffmpeg -i 0228_0342.mpg -vf unsharp=luma_msize_x=7:luma_msize_y=7:luma_amount=1.5 -f mp4 -strict -2 0228_0342_sharpen.mpg
## youtube-dl
### Installation
* On ubuntu
    * `sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl`
    * `sudo chmod a+rx /usr/local/bin/youtube-dl`
* via pip
    * `sudo -H pip install --upgrade youtube-dl`
### command
* `sudo youtube-dl [OPTIONS] URL [URL...]`
### Options
* `--proxy ""`
* `--proxy "socks5://127.0.0.1:1080/"`
* `--write-sub`
* `--write-auto-sub`
* `--all-subs`
* `sudo youtube-dl -U`
### Video quality
* `-F`
* `-f 22`
* `-f best`
* `-f 'bestvideo[ext=mp4]+bestaudio[ext=m4a]/bestvideo+bestaudio' --merge-output-format mp4`
* `-f 137+141`
## download other videos
* add on: FLVCD helper
* shuoshu
## mplayer
* Q = Quit
* P = Pause
* Up arrow = Jump forward in file more
* Right arrow = Jump forward in file less
* Down arrow = Jump back in file more
* Left arrow = Jump back in file less
* ) = Volume up
* ( = Volume down
* M = Volume mute
* F = Full screen view
* O = On-screen display
* V = Toggle subtitles in video
* time control
    * Stop at 56 seconds.
            -endpos 56
    * Stop at 1 hour 10 minutes.
            -endpos 01:10:00
    * Stop at 1 minutes 6 seconds.
            -ss 10 -endpos 56
    * Stop playback after reading 100MB of the input file.
            mplayer -endpos 100mb
## zathura <a name=zathura></a>
### navigation and shortcuts
* same as vim navigation
* f: Follow links on the page
* F: Display link target
* r: Rotate by 90 degrees
* ^r: Recolor
* Tab: Show index and switch to Index mode
    * k,j: Move to upper or lower entry
    * l: Expand entry
    * L: Expand all entries
    * h: Collapse entry
    * H: Collapse all entries
    * space, return: Select and open entry
* 100gg: go to page 100
* d: Toggle dual page view
* F11: Switch to fullscreen mode
* +,-,=: Zoom in, out or to the original size
* zI, zO, z0: Zoom in, out or the oringal size
* a: Zoom to fit
* s: Zoom to width
* mX: Set a quickmark to a letter or number X
* \`X: Goto quickmark saved at letter or number X
* /: Search forwards
* ?: Search backwards
* q: Quit
### commands
* :: Enter command
* bmark: Save a bookmark
* bdelete: Delete a bookmark
* blist: List bookmarks
    press Tab after blist to show all the bookmarks and Press Tab to go through the bookmarks and then press return to open one.
* close: Close document
* exec: Excute an external command ???
* info: Show document information
* open: Open a document
* print: Print document
* write(!): Save document (and force overwritting) ???
* export: Export attachments
        export attachment-{name} {file-name}
        export image-p{page_number}-{image_number} {file_name}
  Press Tab to show all the images that can be exported and then press Tab to go through the images and press return to select one.
* dump: Write values, descriptions, etc. of all current settings to a file.
### Enable copy to clipboard
        vim ~/.config/zathura/zathurarc
        set selection-clipboard clipboard
## FoxitReader
https://blog.csdn.net/github_38704428/article/details/79091407
## webtorrent
* [Download](https://webtorrent.io/desktop/)
* install
        dpkg -i webtorrent-desktop_0.19.0-1_amd64.deb
* put torrent to `https://instant.io/` if cannot play
* can only be launched from gui
## xdg-open
### Examples

        jelline@jelline:~$ xdg-open la_isla_bonita.mp3
        jelline@jelline:~$ xdg-open http://baidu.com
### Usage

        xdg-open { file | URL }
        xdg-open { --help | --manual | --version }
### Manual
    xdg-open opens a file or URL in the user's preferred application. If a URL is provided the URL will be opened in the user's preferred web browser. If a file is provided the file will be opened in the preferred application for files of that type. xdg-open supports file, ftp, http and https URLs.
    xdg-open is for use inside a desktop session only. It is not recommended to use xdg-open as root.
## gimp
* `sudo apt install gimp`
* `sudo apt install gimp-plugin-registry gimp-data-extras`
## Write
http://www.styluslabs.com/download/
`chmod a+x ./*`
`Write/Write`
## 用专门的程序打开文件

        libreoffice 文件名 &
* 打开  .doc .docx .xls .xlsx .ppt .pptx
* 打‘&’的目的是让文件在后台运行，命令行终端还能用。如果忘了打&可以 Ctrl+z，然后打bg回车
* 文件名中含空格要打成'\ '
*  文件名太长不用打完，如 abcdefghijklmn.pdf,可以打完前几个abc,然后点tab键，剩下的就自动打出来了。
## ffplay
        ffplay videofile
        ffplay picfile
* time control
        -ss pos
        -t duration
## Adding shared printers
1. 查找网络打印机，输入对方IP地址，然后查找
![searching printer](searching_printer.jpg)
2. 输入对方用户名和密码
3. 记得点下面的Set authentication details now，然后输入对方的用户名和密码，这样就不会出现等待验证的问题了。
![authentication](adding_shared_printers.jpg)
4. 后面就是选择合适的驱动就行了。
## To expand virtual disk for ubuntu in vmware workstation
1. 先查看要扩展的vmdk文件是哪个
2. 执行扩展命令：
        vmware-vdiskmanger -x 80GB "G:\Ubuntu_64_new\Ubuntu_64-000003_single.vmdk"
 - 如果是单个磁盘文件，则上述命令可以正常进行。
 - 如果是分开的文件，会出现错误：`The called function cannot be performed on partial chains: please open the parent virtual disk. `需要先合并,在vmware的安装目录运行cmd：
            vmware-vdiskmanager -r "G:\Ubuntu_64_new\Ubuntu_64-000003.vmdk" -t 0 "G:\Ubuntu_64_new\Ubuntu_64-000003_single.vmdk"
3. 在vmware中虚拟机的硬盘查看磁盘大小是否已经变化
4. 进入ubuntu进行配置
 - 查看已有分区
            sudo fdisk -l
 - 分区
            sudo fdisk /dev/sda
            m
            n
            p
            default
            default
            如果大小只有1023B，则再进行一遍：
            m
            n
            p
            default
            default
            出现大小50GB的分区则可以。
 - 查看分区是否正确
            sudo fdisk -l
 - reboot (否则不能格式化分区）
 - 格式化分区
            sudo mkfs -t ext4 /dev/sda4
 - 挂载分区
    + 手动挂载
            mkdir ~/disk
            sudo mount /dev/sda4 /home/cdutboy/disk
    + 自动挂载
            sudo vim /etc/fstab
            /dev/sda4 /home/cdutboy/disk ext4 defaults 0 0
 - `df -hl` 查看已有分区的使用情况。
## Extend the home directory of Ubuntu using gparted
* through CD-ROM on Vmware
    * download the ISO file from https://jaist.dl.sourceforge.net/project/gparted/gparted-live-stable/0.32.0-1/gparted-live-0.32.0-1-amd64.iso
    * Vmware Machine Settings>CD/DVD>Use ISO file
    * reboot and select the GParted boot option
* through U disk
    * Download Tuxboot on your computer
        * sudo apt-add-repository ppa:thomas.tsai/ubuntu-tuxboot
        * sudo apt-get update
        * sudo apt-get install tuxboot
        * tuxboot
    * format the U disk to exfat and plug in
    * select the 64-bit Gparted
    * select the right U disk
    * click on OK and start downloading the ISO file
* move and resize
    * select the partition to free space and fill the preceding size
    * move on and forward the unlocated space to the order after the home directory
    * resize and expand the home partition by adding the unlocated space.
## vmware ubuntu share folder
1. 安装vmware tools
    - 挂载镜像文件
        从虚拟机CD/DVD里挂载镜像文件，在vmware workstation的安装目录。
    - 进入ubuntu后，打开DVD光驱，解压VMware*tar.gz的压缩包，然后`sudo ./vmware-install.pl`,然后一直默认回车。
2. 添加共享目录，必须在虚拟机关机的状态下。
3. 进入虚拟机ubuntu，如果`/mnt/hgfs`下有共享的目录就说明可以了。
4. 刚开机时vmhgfs-fuse会占用挺多cpu,过一会会儿记好了。
## top
`top`
`top -o P` (_if `top` cannot show pid_)
top 交互命令：
`h`: to show help information
`0`: Zero-Suppress toggle
`A`: Alternate-Display-Mode toggle
`B`: Bold-Disable/Enable toggle
`k`: Kill a task
`q`: Quit
`m`: Memory/Swap-Usage toggle
`t`: 切换显示进程和CPU状态信息
`c`: 切换显示命令名称和完整命令行
`M`: 根据驻留内存大小进行排序
`P`: 根据CPU使用百分比大小进行排序
`T`: 根据时间/累计时间进行排序
## [BaiduPCS-Go](https://github.com/iikira/BaiduPCS-Go)
### Install and run
* Install Go language

           sudo apt install golang-go
* [Download the zip](https://github.com/iikira/BaiduPCS-Go/releases)
* unzip to ~
* type `./BaiduPCS-Go` to run
### Commands
#### about accounts
* `login`   to login
* `loglist` to list logging accounts
* `su <uid>` to switch account
* `logout` to log out
#### directories and files
* `quota` 获取网盘配额
* `cd <directory>` 切换工作目录
* `cd -l <directory>` 切换工作目录后自动列出工作目录下的文件和目录
* `pwd` 输出工作目录
* `ls` 列出当前工作目录的文件和目录或指定目录
* `ls <directory>` 
* `tree <directory>` 列出当前工作目录的文件和目录或指定目录的树形图
* `meta <file/directory>` 获取单个文件/目录的元信息
#### download
* `download <网盘文件或目录的路径1> <文件或目录2> <文件或目录3> ...`
* `d <网盘文件或目录的路径1> <文件或目录2> <文件或目录3> ...`
##### 可选参数 (貌似只有`--test`可用）
* `--test`: 测试下载, 此操作不会保存文件到本地
* `--status`: 输出所有线程的工作状态
* `--save`: 将下载的文件直接保存到当前工作目录
* `--saveto`: 将下载的文件直接保存到指定的目录
_下载的文件默认保存到 程序所在目录 的 download/ 目录, 支持设置指定目录, 重名的文件会自动跳过!_
#### upload
* `upload <本地文件/目录的路径1> <文件/目录2> <文件/目录3> ... <目标目录>`
* `u <本地文件/目录的路径1> <文件/目录2> <文件/目录3> ... <目标目录>`
    * 上传的文件将会保存到, <目标目录>.
    * 遇到同名文件将会自动覆盖!!
    * 当上传的文件名和网盘的目录名称相同时, 不会覆盖目录, 防止丢失数据.
#### config
* `config` or `config set` 显示和修改程序配置项
* `config -h` or `config set -h`: 显示所有可以设置的值
* `config set --savedir /home/cdutboy/Downloads`:设置下载文件的储存目录(have to use absolute path)
* `config set --max_parallel 150`: 设置下载最大并发量为 150

### Problems
#### No permission to do this operation
`config set -appid 266719`
## unzip
* unzip the test.zip to the current directory: `unzip test.zip`
* 将压缩文件text.zip在指定目录/tmp下解压缩，如果已有相同的文件存在，要求unzip命令不覆盖原先的文件: `unzip -n test.zip -d /tmp`
* 将压缩文件test.zip在指定目录/tmp下解压缩，如果已有相同的文件存在，要求unzip命令覆盖原先的文件: `unzip -o test.zip -d /tmp`
* 查看压缩文件目录，但不解压: `unzip -v test.zip`

## how to type faster
**type the whole word** uninterruptedly
## autokey
### install

        sudo add-apt-repository ppa:troxor/autokey
        sudo apt update
        sudo apt install autokey-gtk
## Pip
### To install pip on Ubuntu 18.04
Pip is a package management system that simplifies installation and management of software packages written in Python such as those found in the Python Packages Index (PyPI). Pip is not installed by default on Ubuntu 18.04, but the installation is pretty straightforward.
#### Install pip
There are several different ways to install pip on Ubuntu 18.04, depending on your preferences and needs. In this guide, we will install pip for both Python 2 `pip` and Python 3 `pip3` using the `apt` package manager.
Before installing any package with `apt` it is recommended to update the package list with:
`$ sudo apt update`
##### Install pip for Python 2
The following command will install pip for Python 2 and all of it's dependencies:
`$ sudo apt install python-pip`
Once this installation is complete, we can verify the installation with the following command which will print the pip version:
`$ pip --version`
The version number may vary, but it will look something like this:
`pip 9.0.1 from /usr/lib/python2.7/dist-packages (python 2.7)`
##### Install pi for Python 3
To install pip3 for Python 3.x run:
`$ sudo apt install python3-pip`
Same as before we will verify the pip3 installation with:
`$ pip3 --version`
`pip 9.0.1 from /usr/lib/python3/dist-packages (python 3.6)`
#### Install development tools
We will also install development tools which are required for building Python modules, for Python 2 run:
`$ sudo apt install build-essential python-dev python-setuptools`
For Python 3:
`$ sudo apt install build-essential python3-dev python3-setuptools`
#### Pip Usage
In this section we will go through a few useful basic pip commands. With pip we ca install packages from PyPI, version control, local projects, and from distribution files but in most cases you will install packages from PyPI.
Let's say we want to install a package named `scrapy`, we can do that by issuing the following command:
`$ pip install scrapy`
To uninstall a package run:
`$ pip uninstall scrapy`
To search packages from PyPI:
`$ pip search "search_query"`
To list installed packages:
`$ pip list`
To list outdated packages:
`$ pip list --outdated`
### To install pip another way
If you don't have pip, install pip with the script provided by the Python Packaging Authority.
1. Download the installation script from pypa.io:
`$ curl -O https://bootstrap.pypa.io/get-pip.py`
The script downloads and installs the latest version of pip and another required package named setuptools.
2. Run the script with Python:
`$ python get-pip.py --user`
3. Add the executable path to your PATH variable: `~/.local/bin`
  To modify your PATH variable (Linux, macOS, or Unix)
  * Find your shell's profile script in your user folder. If you are not sure which shell you have, run `echo $SHELL`.
      `$ ls -a ~`
      `. .. .bash_logout .bash_profile .bashrc Desktip Documents Downloads`
      * Bash- .bash_profile, .profile, or .bash_login.
      * Zsh- .zshrc
      * Tcsh- .tcshrc, .cshrc or .login.
  * Add an export command to your profile script.
      `export PATH=~/.local/bin:$PATH`
      This command adds a path, `~/.local/bin` in this example, to the current PATH variable.
  * Load the profile into your current session
      `$ source ~/.bahs_profile`
4. Verify that pip is installed correctly.
`$ pip --version`
`pip 8.1.2 from ~/.local/lib/python3.4/site-packaes (python 3.4)`

## [free up space on Ubuntu](https://www.linuxdashen.com/debianubuntu%E6%B8%85%E7%90%86%E7%A1%AC%E7%9B%98%E7%A9%BA%E9%97%B4%E7%9A%848%E4%B8%AA%E6%8A%80%E5%B7%A7)
* 删除剩余的配置文件
    * `dpkg --list | grep "^rc" | cut -d " " -f 3 | xargs sudo dpkg --purge`
* 删除没用的deb软件安装包
    * `du -sh /var/cache/apt/archives`
    * `sudo apt-get clean`
    * `sudo apt-get autoclean`
* 删除孤儿软件包
    * `sudo apt-get autoremove`
    * `sudo apt install deborphan`
        * `deborphan`
        * `deborphan | xargs sudo apt-get purge -y`
* 删除过时的软件包
    * `sudo aptitude search ?obsolete`
        * `sudo apt-get purge linux-3.2.0-29-generic`
* 清理日志文件
    * `sudo apt-get install ncdu`
    * `sudo ncdu /var/log`
    * `sudo dd if=/dev/null of=/var/log/shadowsocks.log`
* baobab硬盘空间用量分析工具
    * `baobab`
* 删除大容量软件包
    * `sudo apt-get install debian-goodies`
    * `dpigs -H --line=20`
* 使用ubuntu-tweak来清理
    * `sudo apt-get install gdebi`
    * `sudo gdebi ubuntu-tweak*.deb`
## wc
`-c`
`-l`
`-w`
`cat test.txt | wl -l`
## 命令连接符
* `&`: 单纯的连接命令，不管前面的命令是否执行成功，都执行后面的命令。
* `;`: 同`&`。
* `&&`: 前面的执行成功了才会执行后面的命令。
* `||`: 前面的命令执行成功了就不执行后面的命令了。
* `|`: 管道命令，前面命令的执行结果传输给后面的命令。
## Named Pipe
Almost everything in Linux can be considered a file, but the main difference between a **regular file** and a **named pipe** is that a named pipe is a special instance of a file that has no contents on the filesystem.
Here is quote from `man fifo`:
A FIFO special file (a named pipe) is similar to a pipe, except that it is accessed as part of the filesystem. It can be opened by multiple processes for reading or writing. When processes are exchanging data via the FIFO, the kernel passes all data internally without writing it to the filesystem. Thus, the FIFO special file has no contents on the filesystem; the filesystem entry merely serves as a reference point so that processes can access the pipe using a name in the filesystem.
The kernel maintains exactly one pipe object for each FIFO special file that is opened by at least one process. The FIFO must be opened on both ends (reading and writing) before data can be passed. Normally, opening the FIFO blocks until the other end is opened also.
So actually a named pipe does nothing until some process reads and writes to it. It does not take any space on the hard disk (except a bit of meta information), it does not use the CPU.
`mkfifo blah`
`find . -type p`
`rm ./blah`
`find . -type p -delete`
`find . -maxdepth 1 -type p -delete`
## using screen in SSH
The `screen` command is very useful for remote administration. It can prevent the sessions being executed on the server through ssh from the local computer to be closed or interrupted even when the local terminal is closed or the local computer is shutdown.
你是不是经常需要 SSH 或者 telent 远程登录到 Linux 服务器？你是不是经常为一些长时间运行的任务而头疼，比如系统备份、ftp 传输等等。通常情况下我们都是为每一个这样的任务开一个远程终端窗口，因为他们执行的时间太长了。必须等待它执行完毕，在此期间可不能关掉窗口或者断开连接，否则这个任务就会被杀掉，一切半途而废了。
### session
一个session可以包含多个window。
* `screen`: create a session and a window
* `screen -S session_name`: create a session named of session_name and enter a window
* `screen vim test.c`: create a session and execute the following command.
* `C-a d`: detach the current session. 暂时离开当前session，将目前的 screen session (可能含有多个 windows) 丢到后台执行，并会回到还没进 screen 时的状态，此时在 screen session 里，每个 window 内运行的 process (无论是前台/后台)都在继续执行，即使 logout 也不影响。
* `screen -d session_name/session_id`: same as `C-a d`
* `screen -ls`: list all sessions
* `screen -r session_name/session_id`
* `screen -d -r session_name/session_id`: detach the current session and recover to the specified session
* `screen -wipe`

        [root@tivf18 root]# kill -9 8462
        [root@tivf18 root]# screen -ls  
        There are screens on:
                8736.pts-1.tivf18       (Detached)
                8462.pts-0.tivf18       (Dead ???)
        Remove dead screens with 'screen -wipe'.
        2 Sockets in /root/.screen.
         
        [root@tivf18 root]# screen -wipe
        There are screens on:
                8736.pts-1.tivf18       (Detached)
                8462.pts-0.tivf18       (Removed)
        1 socket wiped out.
        1 Socket in /root/.screen.
         
        [root@tivf18 root]# screen -ls  
        There is a screen on:
                8736.pts-1.tivf18       (Detached)
        1 Socket in /root/.screen.
         
        [root@tivf18 root]#
### window
* `C-a ?`
* `C-a w`: list all the windows
* `C-a C-a`: toggle to the previously displayed window
* `C-a c`: create a new shell window and toggle to it
* `C-a n`: toggle to the next window
* `C-a p`: toggle to the previous window
* `C-a 0..9`: toggle to the window 0..9
* `C-a K`: kill the current window
* `C-a |`: split the window vertically
* `C-a S`: split the window horizontally
* `C-a A`: name the current window
### copy and paste
* `C-a [` -> 进入 copy mode，在 copy mode 下可以回滚、搜索、复制就像用使用 vi 一样
    * `C-b` Backward，PageUp 
    * `C-f` Forward，PageDown 
    * `H`(大写) High，将光标移至左上角 
    * `L` Low，将光标移至左下角 
    * `0` 移到行首 
    * `$` 行末 
    * `w` forward one word，以字为单位往前移 
    * `b` backward one word，以字为单位往后移 
    * `Space` 第一次按为标记区起点，第二次按为终点 
    * `Esc` 结束 copy mode
* `C-a ]` -> Paste，把刚刚在 copy mode 选定的内容贴上
### share the session
还有一种比较好玩的会话恢复，可以实现会话共享。假设你在和朋友在不同地点以相同用户登录一台机器，然后你创建一个screen会话，你朋友可以在他的终端上命令：
`[root@TS-DEV ~]# screen -x`
这个命令会将你朋友的终端Attach到你的Screen会话上，并且你的终端不会被Detach。这样你就可以和朋友共享同一个会话了，如果你们当前又处于同一个窗口，那就相当于坐在同一个显示器前面，你的操作会同步演示给你朋友，你朋友的操作也会同步演示给你。当然，如果你们切换到这个会话的不同窗口中去，那还是可以分别进行不同的操作的。
## 7z
* `7z a dicmerge_1.zip dicmerge_1.txt`
* `7z x dicmerge_1.zip`
* `find . -type f -name "*.7z" -exec 7z e {} \;`
    * `7z e` means extract files here
    * `7z x` means extract files to a created directory
* to avoid BSoD (blue screen of death) crashes
    * set the number of cpus to 6
    * dictionary size to 24M
    * ultra

## [Dropbox-Uploader](https://github.com/andreafabrizi/Dropbox-Uploader)

### Getting started
* `git clone https://github.com/andreafabrizi/Dropbox-Uploader.git`
* `cd Dropbox-Uploader`
* `chmod +x dropbox_uploader.sh`
* `./dropbox_uploader.sh`
* The first time you run `dropbox_uploader`, you'll be guided through a wizard in order to configure access to your Dropbox. This configuration will be stored in `~/.dropbox_uploader`. aVWek70BOpgAAAAAAAAAR5a65CsgUEpJOSxEdqsj3xLZv0uUm52M6aTl2lDPyQOn

### Setup a proxy
* `export HTTP_PROXY_USER=XXXX`
* `export HTTP_PROXY_PASSWORD=YYYY`
* `export https_proxy=http://127.0.0.1:8123`
* `export http_proxy=socks5://127.0.0.1:1081`
* `export https_proxy=socks5://127.0.0.1:1081`
### Usage

        ./dropbox_uploader.sh [PARAMETERS] COMMAND...
        
        [%%]: Optional param
        <%%>: Required param
* commands
    * `upload <LOCAL_FILE/DIR ...> <REMOTE_FILE/DIR>`
    * `download <REMOTE_FILE/DIR> [LOCAL_FILE/DIR]`
    * `delete <REMOTE_FILE/DIR>`
    * `move <REMOTE_FILE/DIR> <REMOTE_FILE/DIR>`
    * `copy <REMOTE_FILE/DIR> <REMOTE_FILE/DIR>`
    * `mkdir <REMOTE_DIR>`
    * `list [REMOTE_DIR]`
    * `monitor [REMOTE_DIR] [TIMEOUT]`
    * `share <REMOTE_FILE>`
    * `saveurl <URL> <REMOTE_DIR>`
    * `search <QUERY>`
    * `info`
    * `space`
    * `unlink`
* Optional parameters
    * `-f <FILENAME>`
    * `-s`
    * `-d`
    * `-q`
    * `-h`
    * `-x <filename>`
* Examples

        ./dropbox_uploader.sh upload /etc/passwd /myfiles/passwd.old
        ./dropbox_uploader.sh upload *.zip /
        ./dropbox_uploader.sh -x .git upload ./project /
        ./dropbox_uploader.sh download /backup.zip
        ./dropbox_uploader.sh delete /backup.zip
        ./dropbox_uploader.sh mkdir /myDir/
        ./dropbox_uploader.sh upload "My File.txt" "My File 2.txt"
        ./dropbox_uploader.sh share "My File.txt"
        ./dropbox_uploader.sh list

## [Xmonad](http://www.ruanyifeng.com/blog/2017/07/xmonad.html)
每个人的偏好不一样，我的开发环境是 Fish Shell + Xfce + xmonad + Vim，已经用了好多年，非常满意。
### 一、xmonad 是什么？
xmonad 是一种窗口管理器（window manager），用来管理软件窗口的位置和大小，会自动在桌面上平铺（tiling）窗口。
注意，窗口管理器不是桌面环境（desktop environment）。后者是一套功能完善、集成各种工具的图形用户界面，比如 Gnome 和 KDE。桌面环境肯定包含了窗口管理器，但是（某些）窗口管理器可以不需要桌面环境，独立运行，xmonad 就是这种。
### 二、安装
`$ sudo apt-get install xmonad`
`$ sudo apt-get install xmobar dmenu`
`$ sudo apt install xmonad-contrib`
安装完成后，退出当前对话（session），选择 xmonad 会话重新登录。登录后，你会看到一个完全空白的桌面，什么也没有，这说明 xmonad 起作用了，因为这时还没有任何软件窗口。
### how to start
Click the "config" icon and choose the "Xmonad" when prepare to enter the password.
### 三、常用命令
#### 3.1 打开终端
第一步，你需要打开一个窗口。一般来说，总是打开命令行终端窗口。
xmonad 提供一个功能键，称为`mod`键（modifier 的缩写），所有操作都要使用这个键，默认为`alt`键，但是一般会把它改掉，比如改成Windows键，具体修改方法请看后文。
* 打开终端窗口，按下`mod + shift + return`（默认为`alt + shift + return`）。这会打开一个终端窗口，占据了所有桌面空间。
* 按下`mod + shift + return`，再打开一个终端窗口。它与第一个窗口水平地平分屏幕，每个窗口占据50%空间。
    注意，第二个窗口占据桌面的左边，自动获得焦点，成为当前窗口。这个左边部分就称为"主栏"（master pane），右边部分称为"副栏"，前面打开的第一个窗口自动进入副栏。
* 再按一次`mod + shift + return`，打开第三个窗口。
    这时，第三个窗口就会占据主栏，前两个窗口自动进入副栏。规则就是，新窗口总是独占主栏，旧窗口平分副栏。
#### 3.2 布局模式
默认的布局模式是，主栏在左边，副栏在右边。
* 按下`mod + space`，布局模式改成主栏在上方，副栏在下
* 再按一次`mod + space`，就变成独占模式，当前窗口独占整个桌面，其他窗口不可见。
* 再按一次`mod + space`，就变回默认模式（主栏在左边，副栏在右边）。
* 按下`mod + ,`（mod + 逗号），一个副栏窗口会移动到主栏，即主栏变成有两个窗口，副栏变成只有一个窗口
* 再按一次`mod + ,`（mod + 逗号），主栏变成三个窗口，副栏消失。
* 按下`mod + .`（mod + 句号），主栏减少一个窗口，副栏增加一个窗口。
#### 3.3 移动焦点
* 新窗口总是自动获得焦点，变成当前窗口。按下`mod + j`，焦点顺时针移动到下一个窗口。
* 按下`mod + k`，焦点逆时针移动到上一个窗口。
* 如果当前窗口在副栏，按下`mod + return`，会与主栏窗口对调位置。
#### 3.4 调整窗口顺序
* 按下`mod + shift + j`，按照顺时针的顺序，当前窗口与下一个窗口交换位置，即当前窗口前进到下一个位置。
* 按下`mod + shift + k`，按照逆时针顺序，当前窗口与上一个窗口交换位置。即当前窗口后退到上一个位置。
#### 3.5 调整栏位大小
* 按下`mod + l`，主栏增加尺寸。
* 按下`mod + h`，副栏增加尺寸。
#### 3.6 浮动窗口
正常情况下，xmonad 决定了窗口的位置和大小，但有时我们希望自己控制。xmonad 允许某个窗口浮动，脱离原有的布局。
* 按下`mod + 鼠标左键`拖动窗口，该窗口就会变成浮动窗口，可以放到屏幕的任何位置。
* 按下`mod + 鼠标右键`可以调整窗口大小。
* 按下`mod + t`，当前浮动窗口就会结束浮动，重新回到 xmonad 的布局。
#### 3.7 关闭窗口
* 窗口可以自然关闭（比如终端窗口按ctrl + d），也可以让 xmonad 强行关闭它。
* 按下`mod + shift + c`，会关闭当前窗口，焦点移到下一个窗口。
#### 3.8 退出 xmonad
按下`mod + shift + q`，将会立刻关闭所有窗口，退出 xmonad，用户需要重新登录。
### 四、工作区
xmonad 提供9个工作区，相当于提供9个桌面。按下`mod + 1`到`mod + 9`切换。 xmonad 启动后，默认处于1号工作区 。
如果要将一个窗口移到不同的工作区，先用`mod + j`或`mod + k`，将其变成焦点窗口，然后使用`mod + shift + 6`，就将其移到了6号工作区。
我的习惯是，1号工作区是终端，2号是浏览器，4号是虚拟机。
### 五、多显示器
多显示器需要使用配置工具，我用的是 xrandr。其他工具还有 Xinerama 和 winView，另外 arandr 是 xrandr 的图形界面，也可以用。
下面的命令查看显示器的连接情况。
`$ xrandr -q`
具体的配置教程可以看[这里](https://wiki.archlinux.org/index.php/xrandr)。
使用多显示器时，每个显示器会分配到一个工作区。默认情况下，1号工作区显示在主显示器，2号工作区显示在第二个显示器。如果要将4号工作区显示在当前显示器，那么按下`mod + 4`，4号工作就会与当前屏幕中的工作区互换位置。
`mod + w` 转移焦点到左显示器，`mod + e`转移焦点到右显示器。
`mod + shift + w`将当前窗口移到左显示器，`mod + shift + e`将当前窗口移到右显示器。
### 六、配置文件
xmonad 的配置文件是～/.xmonad/xmonad.hs。该文件需要用户自己新建，这里是一个简单的范例，详细的解释可以看官网。
这个文件里面，modMask决定了mod到底是哪一个键(`modMask = mod4Mask`)。

        import XMonad
        import XMonad.Config.Desktop
        import XMonad.Hooks.EwmhDesktops
        import XMonad.Hooks.DynamicLog
        import XMonad.Hooks.ManageDocks
        import XMonad.Util.Run(spawnPipe)
        import XMonad.Util.EZConfig(additionalKeys)
        import System.IO
        
        main = do
            xmproc <- spawnPipe "xmobar"
        
            xmonad $ defaultConfig
                { manageHook = manageDocks <+> manageHook defaultConfig
                , layoutHook = avoidStruts  $  layoutHook defaultConfig
                , logHook = dynamicLogWithPP xmobarPP
                                { ppOutput = hPutStrLn xmproc
                                , ppTitle = xmobarColor "green" "" . shorten 50
                                }
                , modMask = mod4Mask     -- Rebind Mod to the Windows key
                } `additionalKeys`
                [ ((mod4Mask .|. shiftMask, xK_z), spawn "xscreensaver-command -lock; xset dpms force off")
                , ((controlMask, xK_Print), spawn "sleep 0.2; scrot -s")
                , ((0, xK_Print), spawn "scrot")
                ]

修改配置文件以后，按下`mod + q`，or `xmonad --recompile && xmonad --restart`新的配置就会生效。
### 七、xmobar
xmonad 的默认桌面，什么也没有，不太方便。xmobar 提供了一个状态栏，将常用信息显示在上面，比如 CPU 和内存的占用情况、天气、时间等等。
它的配置文件是~/.xmobarrc（教程1，2，3）。[这里](https://gist.github.com/ruanyf/a640a98d41383387d3a6401796f54710)是一个最简单配置，这里是我的笔记本电脑使用的配置。

        Config { font = "-*-Fixed-Bold-R-Normal-*-13-*-*-*-*-*-*-*"
        , bgColor = "black"
        , fgColor = "grey"
        , position = Top
        , lowerOnStart = True
        , commands = [ Run Weather "EGPN" ["-t","<station>: <tempC>C","-L","18","-H","25","--normal","green","--high","red","--low","lightblue"] 36000
                     , Run Network "eth0" ["-L","0","-H","32","--normal","green","--high","red"] 10
                     , Run Network "eth1" ["-L","0","-H","32","--normal","green","--high","red"] 10
                     , Run Cpu ["-L","3","-H","50","--normal","green","--high","red"] 10
                     , Run Memory ["-t","Mem: <usedratio>%"] 10
                     , Run Swap [ ] 10
                     , Run Date "%a %b %_d %Y %H:%M:%S" "date" 10
                     ]
        , sepChar = "%"
        , alignSep = "}{"
        , template = "%cpu% | %memory% * %swap% | %eth0% }{ %EGPN% | <fc=#ee9a00>%date%</fc>"
        }

Change `, lowerOnStart = True` to `False` if the bar doesn't appear.

### 八、dmenu
最后，dmenu 在桌面顶部提供了一个菜单条，可以快速启动应用程序。
（图片说明：dmenu 显示在屏幕顶部，输入fire会自动显示包含fire的启动命令。）
它从系统变量$PATH指定的路径中，寻找所有的应用程序，根据用户的键入，动态提示最符合的结果。
按下mod + p就会进入dmenu菜单栏，按下ESC键可以退出。方向键用来选择应用程序，return键用来启动。
### run `<command> & disown` and then you can exit the window without killing the process.
### When xmonad shortcuts stops working
* run `ls -l /proc/1001/fd/` and look for the largest numbered pipe
* run `cat /proc/1001/fd/4` to unblock xmonad so you can fix your xmonad
## `date`
## tee
Copy standard input to each FILE, and also to standard output.
* `-a`, `--append`: append to the given FILEs, do not overwrite.
* `-i`, `--ignore-interrupts`: ignore interrupt signals
* `cat slayers.story | tee ss-copy1 ss-copy2 ss-copy3`

## ConEmu
* shortcuts
    * `Ctrl`+`N` to create a new `{Bash::bash}`
    * `Alt + K => Tab(4, -1); Tab(1);`
    * `Alt + J => Tab(4, 1); Tab(1);`
    * `Ctrl+Alt+K => Move active tab lefward`
    * `Ctrl+Alt+J => Move active tab rightward`
* proxy
    * `export http_proxy=socks5://127.0.0.1:1081`
    * `export https_proxy=socks5://127.0.0.1:1081`
* ConEmu对VimIM的支持不好，不能显示菜单。
## terminus
* shortcuts
    * `Alt+K` to previous tab;
    * `Alt+J` to next tab;
    * `Ctrl+T` to create new bash window
* proxy
    * `export http_proxy=socks5://127.0.0.1:1081`
    * `export https_proxy=socks5://127.0.0.1:1081`
## fluent terminal 不卡，比较好用
## open usb drive
* `sudo fdisk -l`
* `sudo mkdir /media/usb`
* `sudo mount /dev/sdb1 /media/usb`
* `sudo umount /media/usb`
## head
* `head 1.txt`  print the first 10 lines in 1.txt
* `head -n 100`  print the first 100 lines in 1.txt
    * `head -n -100`: print all but the last 100 lines, can be used to scroll viewing
* `head -c 100` print the first 100 bytes in 1.txt
## tail
Just like `head`.
## cat all files in sub directories
`cat * */* */*/*`
## split text file
* Usage: `split [OPTION] [INPUT [PREFIX]]`
* Options
    * `-a N`: use suffixes of length N (default 2)
    * `-b 200m`: put 200M bytes per output file
    * `-d`: use numeric suffixes instead of alphabetic
    * `-l N`: put N lines per output file
* Example:`split -a 3 -d -l 99 my_big_file.txt big_file_chunk_`
    * `-a 3` : says to use a unique 3 character suffix for each chuck file
    * `-d`   : says make that suffix a number so 001 002 all the way to 999
    * `-l 99`: split file by line and have 99 lines or less in each chuck.
    * output
           big_file_chunk_001
           big_file_chunk_002
           ....
## how to mass add file extension
`find . -type f -name "*" -exec mv -v "{}" "{}".txt \;`
## to debug
* press `ESC` while booting to grub mode
* press `Ctrl+Alt+F4` after booting to command mode
## export path
* add `export PATH=$PATH:~/bin` to the end of `~/.bashrc`
    * Note: end with the directory, instead of the name of the program
* `source ~/.bashrc`
## call bomber
Note:这两个的原理都是在商家页面上留言然后获得回访电话，所以频率都不高，更不会一直拨打。
### [js](https://github.com/aqiongbei/buy_pig_plan)
### [python](https://github.com/wuhuanyan/buy_pig_plan_python)
* `# coding=UTF-8`
* `python3 mySelenium.py`
* `www.flylily.top`
* `export PATH=$PATH:/opt/google/chrome/`
