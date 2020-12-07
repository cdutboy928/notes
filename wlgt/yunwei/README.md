# 新入职人员试用期内掌握情况
## 光纤基础知识
* https://www.youtube.com/user/thefoainc/playlists
* https://www.bilibili.com/video/BV1D4411a7Ls
* https://www.bilibili.com/video/BV1VE411C7HV
* https://www.bilibili.com/video/BV1tE411i7xu
* https://www.bilibili.com/video/BV1UE411F7PW?p=4
* 多模光纤和多模光纤
* C波段、L波段
* 光纤几个标准
* 光纤3个损耗小的波长窗口
* dB
* dBm
* 色散
* 光信噪比OSNR
* EDFA放大器和拉曼放大器
* ODF
* 复用器，解复用器，合波器，分波器
* AWG,TFF
* 分光器
* OTU
* 衰减器种类
* GBIC,SFP,XFP,SFP+,SFP28,QSFP,QSFP28,CFP,CFP2,CFP4,CFP8,CFP8,OSFP,QSFP-DD
* https://forum.huawei.com/enterprise/zh/thread-361151-1-1.html
* [光模块博客](https://cshihong.github.io/2020/08/16/%E5%85%89%E6%A8%A1%E5%9D%97%E5%AD%A6%E4%B9%A0%E6%80%BB%E7%BB%93/)
* [How Many Types of SFP Transceivers Do You Know](https://community.fs.com/blog/how-many-types-of-sfp-transceivers-do-you-know.html)
* [Pay Attention to Optical Power Budget of 10G WDM Transceiver](https://community.fs.com/blog/tips-for-buying-cwdm-sfp-dwdm-sfp-transceiver.html)
* [Everything You Need to Know Before Buying CWDM and DWDM SFP+ Transceivers](https://community.fs.com/blog/tips-for-buying-cwdm-sfp-dwdm-sfp-transceiver.html)
* 1000BASE-T,1000BASE-TX,1000BASE-SX,1000BASE-LX,1000BASE-EX,1000BASE-ZX.
* 光模块的损耗大小和光纤的衰减量
* https://zhuanlan.zhihu.com/p/67268672
* MPO/MTP
* https://www.youtube.com/watch?v=a1kMpvdc86U
* [introduction to optical transceivers](https://www.youtube.com/watch?v=Uo-JNY94khk)
* https://www.youtube.com/watch?v=Mrrb6fyxCn4
* 损耗受限距离的估算
* https://community.fs.com/cn/blog/understanding-fiber-loss-what-is-it-and-how-to-calculate-it.html
* https://www.youtube.com/watch?v=QEzHQoTM1KM
* https://www.youtube.com/watch?v=as6AXnGjdUE&list=PLC7CC6B17EF009849&index=19
* https://www.youtube.com/watch?v=PPwOHzLQU2k
* 单模单芯模块选择
    * 1Gbs 速率常用的模块组合
    * 10Gbs 常用的模块组合
* 单模双芯模块:1310nm 有10 20公里模块，1550nm 有40 80公里模块
* 多模双芯模块:850nm 多模没有单芯模块
* 裸纤
## 交换机
* 
* 管理口
* https://forum.huawei.com/enterprise/zh/forum.php?mod=viewthread&tid=242229&extra=page%3D1&page=2
* https://support.huawei.com/enterprise/zh/doc/EDOC1100098004
1. 如何查看设备型号、基础性能、接口类型（及模式），可使用何种类型方式进行接口的使用
2. 可通过所学内容对设备开局使用；
3. 除基本开局外，需掌握设备认证、SNMP、ACL_Telnet访控配置，并理解配置目的；
* 从交换机查看光衰
* 强制千兆命令???
* `?`
* `clock`
* `header`
* `user-interface vty 0 4`
* `user-interface console 0`
* `authentification-mode password`
* `set authentification password cipther huawei`
* `user privilege level 3`
* `interface g 0/0/0`
    * `undo shutdown`
    * `ip address 10.1.1.1 24`
    * `ip address 10.1.1.1 255.255.255.0`
* `restart`
    * `shutdown`
    * `undo shutdown`
* `display ip interface br`
* `save all 1.cfg`
* `startup saved-configuration 1.cfg`
* https://www.bilibili.com/video/BV1V741127f6/?spm_id_from=333.788.videocard.0
* https://www.bilibili.com/video/BV1Kt4y1Q7MJ?p=3
* https://www.bilibili.com/video/BV1Jt41177Ld/?spm_id_from=333.788.videocard.9
## 网络
* [IP地址分类](https://www.bilibili.com/video/av34692686/)
    * 常用内网IP段
    * 非常熟练常用网络号位数与子网主机数量的对应
## 想了解
* 现有网络结构，中间链路的逻辑及实体
## 问题
* 
