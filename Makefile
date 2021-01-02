obj-m += loadavg.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD)

load:
	@insmod loadavg.ko

unload:
	@echo 0 > /sys/kernel/livepatch/loadavg/enabled
	@sleep 2s
	@rmmod loadavg

clean:
	rm -rf \
	  *.ko \
	  *.ko.unsigned \
	  *.mod \
	  *.mod.c \
	  *.o \
	  .*.cmd \
	  .tmp_versions \
	  Module.symvers \
	  built-in.a \
	  modules.order

help:
	@echo
	@echo "Build targets"
	@echo "=================================================="
	@echo "default:   build loadavg.ko"
	@echo "load:      (as root) load loadavg.ko"
	@echo "unload:    (as root) disable and unload loadavg.ko"
	@echo "clean:     remove build files"

.PHONY: default load unload clean help
