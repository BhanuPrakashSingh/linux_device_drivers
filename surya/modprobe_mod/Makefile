
obj-m += modprobe_mod1.o modprobe_mod2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Adding instructions to copy generated modules in "lib/modules/<kernel version>"
# run "depmod -a" to add entries for modules in "modules.dep"
# so that modules can be loaded using modprobe
install:
	cp *.ko /lib/modules/$(shell uname -r)
	depmod -a

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

