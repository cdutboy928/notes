# Freedom
## set up shadowsocks on vultra or ubuntu
https://my.vultr.com/deploy/
### choose servers
* Los Angeles
* 500GB/mon
### install and configure shadowsocks on server
* `sudo su`
* `wget --no-check-certificate -O shadowsocks-all.sh https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks-all.sh`
* `chmod +x shadowsocks-all.sh`
* `./shadowsocks-all.sh 2>&1 | tee shadowsocks-all.log`
* set the port, password, and encrypt method
    * add the port on security group rules of AWS EC2
### TCP Fast Open
* `vim /etc/rc.local`
    * `echo 3 > /proc/sys/net/ipv4/tcp_fastopen`
* `vim /etc/sysctl.conf`
    * `net.ipv4.tcp_fastopen = 3`
* `vim /etc/shadowsocks.json`
    * `"fast_open":true`
* `/etc/init.d/shadowsocks restart`
### BBR
* `wget --no-check-certificate https://github.com/teddysun/across/raw/master/bbr.sh && chmod +x bbr.sh && ./bbr.sh`
* `uname -r`
* `lsmod | grep bbr`
## candidates
* https://www.chaorenssr.com/user
* 小白加速器
