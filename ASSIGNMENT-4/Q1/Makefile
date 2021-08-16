obj-m:=q1.o 
KDIR=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o q1app q1Application.c
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm q1app
install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	
