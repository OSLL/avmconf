
obj-m	:= snapfs.o

snapfs-objs := snapfs-module.o snapfs-mgmt.o
EXTRA_CFLAGS += -Wall #-Werror

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -rf *~
default:
	all

