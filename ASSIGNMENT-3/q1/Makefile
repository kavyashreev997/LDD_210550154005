obj-m:= addn.o avg.o
KDIR=/lib/modules/$(shell uname -r)/build/
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean