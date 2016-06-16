OUTPUT_FORMAT("elf32-littlearm","elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. =0X00000000;
	.text :
	{
		start.o(.text)
		*.o(.text)
	}
	.=ALIGN(4);
	.data :
	{
		*.o(.data)
	}
	.=ALIGN(4);
	.rodata :
	{
		*.o(.rodata)
	}
	.=ALIGN(4);
	.bss :
	{
		*.o(.bss)
	}
	.=ALIGN(4);
}

