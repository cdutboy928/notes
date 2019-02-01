# Windows
## batch scripts
### basics
* echo 表示显示此命令后的字符
* echo off 表示在此语句后所有运行的命令都不显示命令行本身
* @与echo off相象，但它是加在每个命令行的最前面，表示运行时不显示这一行的命令行（只能影响当前行）。
* call 调用另一个批处理文件（如果不用call而直接调用别的批处理文件，那么执行完那个批处理文件后将无法返回当前文件并执行当前文件的后续命令）。
* pause 运行此句会暂停批处理的执行并在屏幕上显示Press any key to continue...的提示，等待用户按任意键后继续
* rem 表示此命令后的字符为解释行（注释），不执行，只是给自己今后参考用的（相当于程序中的注释）。
* Example
例1：用edit编辑a.bat文件，输入下列内容后存盘为c:/a.bat，执行该批处理文件后可实现：将根目录中所有文件写入 a.txt中，启动UCDOS，进入WPS等功能。

　　批处理文件的内容为: 　　　　　　　 命令注释：  

　　　　@echo off　　　　　　　　　　　不显示后续命令行及当前命令行 
　　　　dir c:/*.* >a.txt　　　　　　　将c盘文件列表写入a.txt  
　　　　call c:/ucdos/ucdos.bat　　　　调用ucdos  
　　　　echo 你好 　　　　　　　　　　 显示"你好"  
　　　　pause 　　　　　　　　　　　　 暂停,等待按键继续  
　　　　rem 准备运行wps 　　　　　　　 注释：准备运行wps  
### %[1-9]
#### Example
* 例2：C:根目录下有一批处理文件名为f.bat，内容为： 
@echo off 
format %1 

如果执行C:/>f a: 
那么在执行f.bat时，%1就表示a:，这样format %1就相当于format a:，于是上面的命令运行时实际执行的

是format a: 
* 例3：C:根目录下一批处理文件名为t.bat，内容为: 
@echo off 
type %1  
type %2  

那么运行C:/>t a.txt b.txt  
%1 : 表示a.txt 
%2 : 表示b.txt 
于是上面的命令将顺序地显示a.txt和b.txt文件的内容。 
### if
* 1、if [not] "参数" == "字符串" 待执行的命令  

参数如果等于(not表示不等，下同)指定的字符串，则条件成立，运行命令，否则运行下一句。 

例：if "%1"=="a" format a: 

* 2、if [not] exist [路径/]文件名 待执行的命令  
如果有指定的文件，则条件成立，运行命令，否则运行下一句。 

如: if exist c:/config.sys type c:/config.sys  
表示如果存在c:/config.sys文件，则显示它的内容。 

* 3、if errorlevel <数字> 待执行的命令  

很多DOS程序在运行结束后会返回一个数字值用来表示程序运行的结果(或者状态)，通过if errorlevel命

令可以判断程序的返回值，根据不同的返回值来决定执行不同的命令(返回值必须按照从大到小的顺序排列

)。如果返回值等于指定的数字，则条件成立，运行命令，否则运行下一句。 

如if errorlevel 2 goto x2 
#### Example of if
* 1) 

首先用记事本在C:/建立一个test1.bat批处理文件，文件内容如下：  
@echo off  
IF EXIST /AUTOEXEC.BAT TYPE /AUTOEXEC.BAT  
IF NOT EXIST /AUTOEXEC.BAT ECHO /AUTOEXEC.BAT does not exist  

然后运行它： 
C:/>TEST1.BAT  

如果C:/存在AUTOEXEC.BAT文件，那么它的内容就会被显示出来，如果不存在，批处理就会提示你该文件不

存在。 

* 2) 

接着再建立一个test2.bat文件，内容如下：  
@ECHO OFF  
IF EXIST /%1 TYPE /%1  
IF NOT EXIST /%1 ECHO /%1 does not exist  

执行:  
C:/>TEST2 AUTOEXEC.BAT  
该命令运行结果同上。 

说明：  
(1) IF EXIST 是用来测试文件是否存在的，格式为  
IF EXIST [路径+文件名] 命令  
(2) test2.bat文件中的%1是参数，DOS允许传递9个批参数信息给批处理文件，分别为%1~%9(%0表示test2

命令本身) ，这有点象编程中的实参和形参的关系，%1是形参，AUTOEXEC.BAT是实参。  

* 3) 更进一步的，建立一个名为TEST3.BAT的文件，内容如下：  
@echo off 
IF "%1" == "A" ECHO XIAO  
IF "%2" == "B" ECHO TIAN  
IF "%3" == "C" ECHO XIN  

如果运行： 
C:/>TEST3 A B C  
屏幕上会显示: 
XIAO 
TIAN 
XIN 

如果运行： 
C:/>TEST3 A B  
屏幕上会显示 
 
XIAO 
TIAN 
#### another example of if
建立TEST5.BAT，文件内容如下：  
@echo off  
IF "%1" == "A" FORMAT A:  

执行：  
C:/>TEST5 A  
屏幕上就出现是否将A:盘格式化的内容。  

注意：为了防止参数为空的情况，一般会将字符串用双引号（或者其它符号，注意不能使用保留符号）括

起来。 
如：if [%1]==[A] 或者 if %1*==A* 
### goto
goto 批处理文件运行到这里将跳到goto所指定的标号(标号即label，标号用:后跟标准字符串来定义)

处，goto语句一般与if配合使用，根据不同的条件来执行不同的命令组。  

如: 

goto end  

:end  
echo this is the end  

标号用“:字符串”来定义，标号所在行不被执行。  
### errorlevel
建立TEST4.BAT，内容如下：
@ECHO OFF
XCOPY C:/AUTOEXEC.BAT D:IF ERRORLEVEL 1 ECHO 文件拷贝失败
IF ERRORLEVEL 0 ECHO 成功拷贝文件

然后执行文件:
C:/>TEST4

如果文件拷贝成功，屏幕就会显示“成功拷贝文件”，否则就会显示“文件拷贝失败”。

IF ERRORLEVEL 是用来测试它的上一个DOS命令的返回值的，注意只是上一个命令的返回值，而且返回值必

须依照从大到小次序顺序判断。
因此下面的批处理文件是错误的：
@ECHO OFF
XCOPY C:/AUTOEXEC.BAT D:/
IF ERRORLEVEL 0 ECHO 成功拷贝文件
IF ERRORLEVEL 1 ECHO 未找到拷贝文件
IF ERRORLEVEL 2 ECHO 用户通过ctrl-c中止拷贝操作
IF ERRORLEVEL 3 ECHO 预置错误阻止文件拷贝操作
IF ERRORLEVEL 4 ECHO 拷贝过程中写盘错误

无论拷贝是否成功，后面的：

未找到拷贝文件
用户通过ctrl-c中止拷贝操作
预置错误阻止文件拷贝操作
拷贝过程中写盘错误
