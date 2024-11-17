obj-m	:= hid-mousebtnfix.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)
MOD_NAME  := hid-mousebtnfix
MOD_FILE  := $(MOD_NAME).ko
DESTDIR 	:= /lib/modules/$(shell uname -r)/kernel/drivers/hid/

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

dkms:
	make -C $(INCLUDEDIR) M=$(PWD) modules

install: all
	install -v -m 644 $(MOD_FILE) $(DESTDIR)
	depmod -a
	modprobe $(MOD_NAME)

uninstall:
	modprobe -r $(MOD_NAME) || true
	rm -vf $(DESTDIR)/$(MOD_FILE)
	depmod -a

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers built-in.a
