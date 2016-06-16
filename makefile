OBJS = start.o pll_init.o ddr_init.o \
	   uart.o nand.o pic_show.o music.o
CCFLAGS = -c -nostartfiles -ffreestanding -fno-builtin -nostdlib -I include

all:$(OBJS)
	arm-none-linux-gnueabi-ld -T opration.lds $(OBJS) -o show
	arm-none-linux-gnueabi-objcopy -O binary show /tftpboot/show.bin

%.o : %.c
	arm-none-linux-gnueabi-gcc $< -o $@ $(CCFLAGS)
%.o : %.S
	arm-none-linux-gnueabi-gcc $< -o $@ $(CCFLAGS)

clean:
	rm -fr *.o show /tftpboot/show.bin
