EXTRA_CFLAGS += -I$(TOPDIR)/drivers/net/wireless
EXTRA_CFLAGS += -std=gnu89
EXTRA_CFLAGS += -O2

ieee80211-rtl-objs := ieee80211_softmac.o ieee80211_rx.o ieee80211_tx.o ieee80211_wx.o ieee80211_module.o ieee80211_softmac_wx.o

ieee80211_crypt-rtl-objs := ieee80211_crypt.o
ieee80211_crypt_tkip-rtl-objs := ieee80211_crypt_tkip.o
ieee80211_crypt_ccmp-rtl-objs := ieee80211_crypt_ccmp.o
ieee80211_crypt_wep-rtl-objs := ieee80211_crypt_wep.o

obj-m +=ieee80211-rtl.o
obj-m +=ieee80211_crypt-rtl.o
obj-m +=ieee80211_crypt_wep-rtl.o
obj-m +=ieee80211_crypt_tkip-rtl.o
obj-m +=ieee80211_crypt_ccmp-rtl.o

KVER  := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build

PWD = $(shell pwd)
#KSRC  := /home/realtek/linux-2.6.12
INSTALL_PREFIX :=

#CC = mipsel-linux-gcc
CC = gcc
#LD = mipsel-linux-ld

all: modules

clean:
	rm -f *.mod.c *.mod *.o .*.cmd *.ko *~
	rm -rf $(PWD)/tmp

modules:
	$(MAKE) -C $(KSRC) M=$(PWD) modules

