#include "s3c6410.h"

void ac97_write(unsigned char reg, unsigned short data);
unsigned short ac97_read(unsigned char reg);
void init_ac97(void);
void init_wm9714(void);
void init_dmac1(void);
#define DMA_SRC_ADDR 0x55000000
#define TRANSFER_SIZE (44100*2*2*60)>>2 

struct lli_t {
	unsigned long source_address;
	unsigned long destination_address;
	unsigned long next;
	unsigned long dmacc0control0;
	unsigned long dmacc0control1;
};

struct lli_t lli;

void init_music()
{
	puts("\nSTART init music\n");
	VIC1INTSELECT &= ~(1<<10);//select irq interrupt
	VIC1INTENABLE |= 1<<10;//enable interrupt

	init_ac97();
	init_wm9714();
	init_dmac1();

	puts("\nEND init music\n");
}

void udelay()
{
	unsigned long i = 0xfffff;
	while(i!=0)
	{
		i--;
	}

}

void init_ac97(void)
{
	GPDCON = 0x44444;
	//cold reset
	AC_GLBCTRL = 1;
	udelay(1000);	
	AC_GLBCTRL = 0;
	udelay(1000);	

	//warm reset, wake up wm9714 from power down
	AC_GLBCTRL = 1<<1;
	udelay(1000);	
	AC_GLBCTRL = 0;
	udelay(1000);	
	AC_GLBCTRL = (1<<2) | (2<<12);//AC-Link on,PCM out mode DMA
	//udelay(1000);	
	AC_GLBCTRL |= (1<<3);//AC_link enable

	AC_CODEC_CMD = 1<<23;//read status
	udelay(1000);	
	if ((AC_GLBSTAT&7) == 3)
		puts("Active\n");
	else 
		puts("Inactive\n");
}

void ac97_write(unsigned char reg, unsigned short data)
{
	AC_CODEC_CMD = (reg<<16) | data;
	udelay(1000);	
}

unsigned short ac97_read(unsigned char reg)
{
	AC_CODEC_CMD = (reg<<16) | (1<<23);
	udelay(1000);	
	return (AC_CODEC_STAT&0xffff);
}

void init_wm9714(void)
{
	//Register 04h controls the headphone output pins, HPL and HPR.
	ac97_write(0x04, (1 << 14) | (10 << 8) | (1 << 6) |10);
	//Register 0Ch controls the audio DACs
	ac97_write(0x0c, 0);

	ac97_write(0x1c, (2 << 6) | (2 << 4));
	ac97_write(0x24, 1 << 4);

	ac97_write(0x26, 0);
	ac97_write(0x2a, 1);
	ac97_write(0x2c, 0xac44);

	ac97_write(0x3c, 0);
	ac97_write(0x3e, 0);
}

void init_dmac1(void)
{
	//P391. 11.7.8 PROGRAMMING A DMA CHANNEL
	SDMA_SEL |= 7<<22;//Select DMA

	//synchronization logic enabled
	DMACSync = 0;

	//   3 Clear pend interrupts
	DMACIntTCClear = 0xff;
	//    3 Clear err interrupts
	DMACIntErrClr = 0xff;
	//   4 
	DMACC0SrcAddr = DMA_SRC_ADDR; //
	//     5 
	DMACC0DestAddr = 0x7F001018;//Address of AC_PCMDATA ?

	//channel control reg  burst size,and transfer width.
	DMACC0Control0 = (1<<12) | (1<<15) | (2<<18) | (2<<21) | (1<<25) | (1<<26) | (1<<28) | (1<<31); //?
	DMACC0Control1 = TRANSFER_SIZE;//transfer size

	//DMACC0LLI = 0;  
	DMACC0LLI = &lli;//
	lli.source_address = DMA_SRC_ADDR;
	lli.destination_address = 0x7F001018; 
	lli.dmacc0control0 = (1<<12) | (1<<15) | (2<<18) | (2<<21) | (1<<25) | (1<<26) | (1<<28) | (1<<31);
	lli.dmacc0control1 = TRANSFER_SIZE;
	lli.next = &lli;

	DMACC0Configuration = 1 | (6<<6) | (1<<11) | (1<<15);

	//enable DMA controler
	DMACConfiguration = 1;
}

