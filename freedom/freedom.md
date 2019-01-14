# Freedom
## set up shadowsocks on vultra
https://my.vultr.com/deploy/
### choose servers
* Los Angeles
* 500GB/mon
### install and configure shadowsocks on server
* `wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks.sh`
* `chmod +x shadowsocks.sh`
* `./shadowsocks.sh 2>&1 | tee shadowsocks.log`
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
* `uname -r lsmod | grep bbr`
