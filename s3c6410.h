#ifndef S3C6410_H
#define S3C6410_H

//pll
#define APLL_LOCK   	0x7E00F000
#define MPLL_LOCK   	0x7E00F004
#define APLL_CON   		0x7E00F00C
#define MPLL_CON   		0x7E00F010
#define EPLL_CON0    	0x7E00F014
#define EPLL_CON1    	0x7E00F018
#define CLK_SRC    		0x7E00F01C
#define OTHERS     		0x7E00F900
#define CLK_DIV0   		0x7E00F020

#define GPMCON     		0x7F008820
#define GPMDAT     		0x7F008824

//memory
#define MEM_SYS_CFG  		0x7E00F120
#define P1MEMCCMD 	 	0x7E001004
#define P1MEMSTAT    		0x7E001000
#define P1REFRESH 	 	0x7E001010
#define P1CASLAT	 	0x7E001014
#define P1T_DQSS	 	0x7E001018
#define P1T_MRD 	 	0x7E00101C
#define P1T_RAS 	 	0x7E001020
#define P1T_RC 	 	 	0x7E001024
#define P1T_RCD	 	 	0x7E001028
#define P1T_RFC		 	0x7E00102C
#define P1T_RP 		 	0x7E001030
#define P1T_RRD		 	0x7E001034
#define P1T_WR 		 	0x7E001038
#define P1T_WTR		 	0x7E00103C
#define P1T_XP 		 	0x7E001040
#define P1T_XSR		 	0x7E001044
#define P1T_ESR		 	0x7E001048
#define P1MEMCFG	 	0x7E00100C
#define P1MEMCFG2 		0x7E00104C
#define P1_chip_0_cfg 		0x7E001200
#define P1_chip_1_cfg 		0x7E001204
#define P1DIRECTCMD     	0x7E001008

//uart
#define GPACON			(*(volatile unsigned long *)0x7F008000)
#define ULCON0			(*(volatile unsigned long *)0x7F005000)
#define UCON0			(*(volatile unsigned long *)0x7F005004)
#define UFCON0			(*(volatile unsigned long *)0x7F005008)
#define UTRSTAT0		(*(volatile unsigned long *)0x7F005010)
#define UTXH0			(*(volatile unsigned long *)0x7F005020)
#define URXH0			(*(volatile unsigned long *)0x7F005024)
#define UBRDIV0			(*(volatile unsigned long *)0x7F005028)
#define UDIVSLOT0		(*(volatile unsigned long *)0x7F00502C)

//lcd
#define GPFCON			(*(volatile unsigned long *)0x7F0080A0)
#define GPFDAT			(*(volatile unsigned long *)0x7F0080A4)
#define GPJCON			(*(volatile unsigned long *)0x7F008120)
#define GPICON			(*(volatile unsigned long *)0x7F008100)
#define MIFPCON			(*(volatile unsigned long *)0x7410800C)
#define SPCON			(*(volatile unsigned long *)0x7F0081A0)
#define VIDCON0			(*(volatile unsigned long *)0x77100000)
#define VIDCON1			(*(volatile unsigned long *)0x77100004)
#define VIDTCON0		(*(volatile unsigned long *)0x77100010)
#define VIDTCON1		(*(volatile unsigned long *)0x77100014)
#define VIDTCON2		(*(volatile unsigned long *)0x77100018)
#define WINCON0			(*(volatile unsigned long *)0x77100020)
#define VIDOSD0A		(*(volatile unsigned long *)0x77100040)
#define VIDOSD0B		(*(volatile unsigned long *)0x77100044)
#define VIDOSD0C		(*(volatile unsigned long *)0x77100048)
#define VIDW00ADD0B0		(*(volatile unsigned long *)0x771000A0)
#define VIDW00ADD1B0		(*(volatile unsigned long *)0x771000D0)

//interrupt
#define GPNCON 		 	(*(volatile unsigned long*)0x7F008830)	
#define VIC0 			(0x71200000)
#define VIC0INTSELECT  		(*(volatile unsigned long*)(VIC0+0x00C))
#define VIC0INTENABLE   	(*(volatile unsigned long*)(VIC0+0x010))
#define VIC0IRQSTATUS   	(*(volatile unsigned long*)(VIC0+0x000))
#define EINT0CON0       	(*(volatile unsigned long*)0x7F008900)
#define EINT0MASK  		(*(volatile unsigned long*)0x7F008920)
#define EINT0PEND   		(*(volatile unsigned long*)0x7F008924)

//watchdog
#define WTCON   		(*(volatile unsigned long *)0x7E004000) 
#define WTDAT   		(*(volatile unsigned long *)0x7E004004) 
#define WTCNT   	 	(*(volatile unsigned long *)0x7E004008) 
#define WTCLRINT	 	(*(volatile unsigned long *)0x7E00400C)

//nand flash
#define GPOCON 			(*(volatile unsigned long*)0x7F008140)
#define GPPCON 			(*(volatile unsigned long*)0x7F008160)
#define Base   			0x70200000
#define NFCONF     	 	(*(volatile unsigned long*)(Base + 0x00))
#define NFCONT     	 	(*(volatile unsigned long*)(Base + 0x04))
#define NFCMMD     	 	(*(volatile unsigned long*)(Base + 0x08))
#define NFADDR     	 	(*(volatile unsigned long*)(Base + 0x0c))
#define NFDATA     	 	(*(volatile unsigned char*)(Base + 0x10))
#define NFMECCD0   	 	(*(volatile unsigned long*)(Base + 0x14))
#define NFMECCD1   	 	(*(volatile unsigned long*)(Base + 0x18))
#define NFSECCD    	 	(*(volatile unsigned long*)(Base + 0x1c))
#define NFSBLK     	 	(*(volatile unsigned long*)(Base + 0x20))
#define NFEBLK     	 	(*(volatile unsigned long*)(Base + 0x24))
#define NFSTAT     	 	(*(volatile unsigned long*)(Base + 0x28))
#define NFECCERR0   		(*(volatile unsigned long*)(Base + 0x2C))
#define NFECCERR1   		(*(volatile unsigned long*)(Base + 0x30))
#define NFMECC0     		(*(volatile unsigned long*)(Base + 0x34))
#define NFMECC1     		(*(volatile unsigned long*)(Base + 0x38))
#define NFSECC      		(*(volatile unsigned long*)(Base + 0x3C))
#define NFMLCBITPT  		(*(volatile unsigned long*)(Base + 0x40))
#define NF8ECCERR0  		(*(volatile unsigned long*)(Base + 0x44))
#define NF8ECCERR1  		(*(volatile unsigned long*)(Base + 0x48))
#define NF8ECCERR2  		(*(volatile unsigned long*)(Base + 0x4C))
#define NFM8ECC0    		(*(volatile unsigned long*)(Base + 0x50))
#define NFM8ECC1   		(*(volatile unsigned long*)(Base + 0x54))
#define NFM8ECC2    		(*(volatile unsigned long*)(Base + 0x58))
#define NFM8ECC3    		(*(volatile unsigned long*)(Base + 0x5C))
#define NFMLC8BITPT0		(*(volatile unsigned long*)(Base + 0x60))
#define NFMLC8BITPT1 		(*(volatile unsigned long*)(Base + 0x64))

//ac97
#define VIC1  (0x71300000)
#define VIC1IRQSTATUS      (*(volatile unsigned long*)(VIC1+0x000))
#define VIC1FIQSTATUS      (*(volatile unsigned long*)(VIC1+0x004))
#define VIC1RAWINTR        (*(volatile unsigned long*)(VIC1+0x008))
#define VIC1INTSELECT      (*(volatile unsigned long*)(VIC1+0x00C))
#define VIC1INTENABLE      (*(volatile unsigned long*)(VIC1+0x010))
#define VIC1INTENCLEAR     (*(volatile unsigned long*)(VIC1+0x014))
#define VIC1SOFTINT        (*(volatile unsigned long*)(VIC1+0x018))
#define VIC1SOFTINTCLEAR   (*(volatile unsigned long*)(VIC1+0x01C))
#define VIC1PROTECTION     (*(volatile unsigned long*)(VIC1+0x020))
#define VIC1SWPRIORITYMASK (*(volatile unsigned long*)(VIC1+0x024))
#define VIC1PRIORITYDAISY  (*(volatile unsigned long*)(VIC1+0x028))
#define DMAC1 0x75100000
#define DMACIntStatus		   (*(volatile unsigned long*)(DMAC1+0x000)) 
#define DMACIntTCStatus		   (*(volatile unsigned long*)(DMAC1+0x004))
#define DMACIntTCClear		   (*(volatile unsigned long*)(DMAC1+0x008))
#define DMACIntErrorStatus     (*(volatile unsigned long*)(DMAC1+0x00C))
#define DMACIntErrClr  		   (*(volatile unsigned long*)(DMAC1+0x010))
#define DMACRawIntTCStatus 	   (*(volatile unsigned long*)(DMAC1+0x014))
#define DMACRawIntErrorStatus  (*(volatile unsigned long*)(DMAC1+0x018))
#define DMACEnbldChns  		   (*(volatile unsigned long*)(DMAC1+0x01C))
#define DMACConfiguration	   (*(volatile unsigned long*)(DMAC1+0x030)) 
#define DMACSync			   (*(volatile unsigned long*)(DMAC1+0x034))
#define DMACC0SrcAddr		   (*(volatile unsigned long*)(DMAC1+0x100)) 
#define DMACC0DestAddr		   (*(volatile unsigned long*)(DMAC1+0x104)) 
#define DMACC0LLI			   (*(volatile unsigned long*)(DMAC1+0x108))
#define DMACC0Control0		   (*(volatile unsigned long*)(DMAC1+0x10C)) 
#define DMACC0Control1		   (*(volatile unsigned long*)(DMAC1+0x110))
#define DMACC0Configuration    (*(volatile unsigned long*)(DMAC1+0x114))
#define DMACC0ConfigurationExp (*(volatile unsigned long*)(DMAC1+0x118))
#define SDMA_SEL 			   (*(volatile unsigned long*)0x7E00F110)
#define AC_GLBCTRL    (*(volatile unsigned long *)0x7F001000) 
#define AC_GLBSTAT    (*(volatile unsigned long *)0x7F001004)
#define AC_CODEC_CMD  (*(volatile unsigned long *)0x7F001008)
#define AC_CODEC_STAT (*(volatile unsigned long *)0x7F00100C)
#define AC_PCMADDR    (*(volatile unsigned long *)0x7F001010)
#define AC_MICADDR    (*(volatile unsigned long *)0x7F001014)
#define AC_PCMDATA    (*(volatile unsigned long *)0x7F001018)
#define AC_MICDATA    (*(volatile unsigned long *)0x7F00101C)
#define GPDCON        (*(volatile unsigned long *)0x7F008060)



#endif
