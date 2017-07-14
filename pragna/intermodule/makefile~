obj-m += intermodule1.o intermodule2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	cp *.ko /lib/modules/$(shell uname -r)/
	depmod -a

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

