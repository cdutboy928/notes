#EXTRA_CFLAGS += -DCONFIG_IEEE80211_NOWEP=y
#EXTRA_CFLAGS += -DCONFIG_RTL8180_IOMAP
EXTRA_CFLAGS += -I$(TOPDIR)/drivers/net/wireless
EXTRA_CFLAGS += -std=gnu89
EXTRA_CFLAGS += -O2
EXTRA_CFLAGS += -mhard-float -DCONFIG_FORCE_HARD_FLOAT=y
#ieee80211-r8180-objs := ieee80211.o ieee80211_rx.o ieee80211_tx.o ieee80211_wx.o ieee80211_module.o

#ieee80211_crypt-r8180 := ieee80211_crypt-r8180.o

r8187-objs := r8187_core.o r8180_93cx6.o r8180_wx.o r8180_rtl8225.o r8180_rtl8225z2.o r8187_led.o

#ieee80211_crpt_wep-r8180-objs := ieee80211_crypt_wep-r8180.o

obj-m := r8187.o


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

MODDESTDIR := /lib/modules/$(KVER)/kernel/drivers/net/wireless
#MOD_ALGDESTDIR := /lib/modules/$(KVER)/kernel/drivers/net/wireless/alg
install: modules
	mkdir -p $(MODDESTDIR)
#	mkdir -p $(MOD_ALGDESTDIR)
	install -p -m 644 r8187.ko  $(MODDESTDIR)
#	install -p -m 644 ieee80211_crypt_wep-r8180.ko $(MOD_ALGDESTDIR)
