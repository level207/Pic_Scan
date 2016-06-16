#include "s3c6410.h"

void uart_test()
{
	puts("\n...picture scaner...\n");
}

void uart_init(void)
{
	GPACON = 0x2222;
	ULCON0 = 3;
	UCON0 = 1 | (1<<2) | (2<<10);
	UFCON0 = 0;
	UBRDIV0 = 35;
	UDIVSLOT0 = 0x0080;  
}

void putchar(int ch)
{
	while (!(UTRSTAT0&(1<<1)))
		;
	UTXH0 = ch;	
}

int getchar(void)
{
	while (!(UTRSTAT0&1))
		;
	
	return (URXH0&0xff);
}

int puts(const char *s)
{
	char *q = s;
	while (*q) {
		putchar(*q);
		if (*q == '\n')
			putchar('\r');
		q++;
	}
	return 0;
}

char *gets(char *s)
{
	int ch = 0;
	char *q = s;
	while ((ch=getchar()) != '\r') {
		putchar(ch);
		*q = ch;
		q++;
	}

	return s;
}
