obj-m:=calculator.o
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o App Application.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm App
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
