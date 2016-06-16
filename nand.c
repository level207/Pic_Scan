#include "s3c6410.h"
#define DEVICE_SIZE 2048*64*2048
#define BLOCK_SIZE 64*2048
#define PAGE_SIZE 2048

void nand_init()
{
	GPOCON &=~3;
	GPOCON |= 2;

	GPPCON &=~(0x3ff<<6);
	GPPCON |= 0x2aa<<6;
	NFCONF = (1<<2)|(1<<4)|(2<<8)|(1<<12);
	NFCONT = 1|(1<<1);
}

unsigned long nand_read(unsigned long mem_addr,unsigned int addr,unsigned  int size)
{
	unsigned int nand_addr,i,len;

	NFCONT &= ~(1<<1);
	addr &= ~(PAGE_SIZE -1);

	len = PAGE_SIZE;

	for(nand_addr = addr;nand_addr < addr + size;nand_addr += PAGE_SIZE )
	{
		NFCMMD = 0x00;

		NFADDR = nand_addr & 0xff;
		NFADDR = (nand_addr >> 8) & 0x7;
		NFADDR = (nand_addr >> 11) & 0xff;
		NFADDR = (nand_addr >> 19) & 0xff;
		NFADDR = (nand_addr >> 27) & 0x1;

		NFCMMD = 0x30;
		while( !(NFSTAT & 1));
		for(i = 0;i<len;i++)
			*( volatile char *)mem_addr++ = NFDATA;
	}

	NFCONT |= (1<<1);
	return 0;
}

void copy_pic_to_sdram()
{
	puts("\nSTART copy pic to sdram\n");
	nand_read( 0x54000000 , 0x40000 , 0xA00000 );
	puts("\nEND copy pic to sdram\n");
}

void copy_music_to_sdram()
{
	puts("\nSTART copy music to sdram\n");
	nand_read( 0x55000000 , 0x1000000 , 0x2000000 );
	puts("\nEND copy msic to sdram\n");
}

