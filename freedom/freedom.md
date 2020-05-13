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
* Blinkload
* STC-Server
## [v2ray](https://toutyrater.github.io/)
### Installation
#### time
`date -R`
`sudo date --set="2017-01-22 16:16:23"`
#### Installation on Server
* `wget https://install.direct/go.sh`
* `sudo bash go.sh`
    * check the "PORT" and "UUID"
* start: `sudo systemctl start v2ray`
* update: `sudo bash go.sh`
#### Installation on client
https://github.com/v2ray/v2ray-core/releases
wv2ray.exe running on background without a cmd window.
SOCKS v5
### Configuration
#### check
`/usr/bin/v2ray/v2ray -test -config /etc/v2ray/config.json`
#### how it works
{浏览器} <--(socks)--> {V2Ray 客户端 inbound <-> V2Ray 客户端 outbound} <--(VMess)-->  {V2Ray 服务器 inbound <-> V2Ray 服务器 outbound} <--(Freedom)--> {目标网站}
#### Configuration on Server

        {
          "log": {
            "loglevel": "warning",
            "access": "/var/log/v2ray/access.log",
            "error": "/var/log/v2ray/error.log"
          },
          "inbounds": [
            {
              "port": 16823,
              "protocol": "vmess",    
              "settings": {
                "clients": [
                  {
                    "id": "0d787167-4927-4da2-a13d-588613dd6721",
                    "alterID": 64 //这儿不能少
                  }
                ]
              }
            }
          ],
          "outbounds": [
            {
              "protocol": "freedom",
              "settings": {}
            }
          ]
        }

`sudo systemctl restart v2ray`
`service v2ray status`
#### Configuration on client

        {
          "log": {
            "loglevel": "warning",
            "access": "D:\\v2ray\\access.log",
            "error": "D:\\v2ray\\error.log"
          },
          "inbounds": [
            {
              "port": 1080,
              "protocol": "socks",
              "sniffing": {
                "enabled": true,
                "destOverride": ["http", "tls"]
              },
              "settings": {
                "auth": "noauth",
                "udp": true
              }
            }
          ],
          "outbounds": [
            {
              "protocol": "vmess",
              "settings": {
                "vnext": [
                  {
                    "address": "3.91.182.141",
                    "port": 16823,  
                    "users": [
                      {
                        "id": "0d787167-4927-4da2-a13d-588613dd6721",
                        "alterId": 64
                      }
                    ]
                  }
                ]
              }
            },
            {
              "protocol": "freedom",
              "settings": {},
              "tag": "direct" //如果要使用路由，这个 tag 是一定要有的，在这里 direct 就是 freedom 的一个标号，在路由中说 direct V2Ray 就知道是这里的 freedom 了
            }    
          ],
          "routing": {
            "domainStrategy": "IPOnDemand",
            "rules": [
              {
                "type": "field",
                "outboundTag": "direct",
                "domain": ["geosite:cn"] // 中国大陆主流网站的域名
              },
              {
                "type": "field",
                "outboundTag": "direct",
                "ip": [
                  "geoip:cn", // 中国大陆的 IP
                  "geoip:private" // 私有地址 IP，如路由器等
                ]
              }
            ]
          }
        }
### Use BBR
`wget -N --no-check-certificate "https://raw.githubusercontent.com/chiakge/Linux-NetSpeed/master/tcp.sh" && chmod +x tcp.sh && ./tcp.sh`
选择魔改效果的
每次开机都要运行刚一次`./tcp.sh`
可以大大提高速度
### on mobile phone
v2rayNG
## some websites

* http://baa.im/12765

