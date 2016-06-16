#include "s3c6410.h"

#define FRAMEBUFFER	0x54000000
#define INDEX		522240

static unsigned long count=500;

void do_irq(void);
void long_delay(void);
void delay(void);
void short_delay(void);

void init_lcd()
{
	GPFCON|=(1<<28);
	GPFDAT|=1<<14;

	GPJCON = 0xaaaaaa;
	GPICON = 0xaaaaaaaa;
	// 1
	MIFPCON&=~(1<<3);
	//2 
	SPCON&=~3;
	SPCON|=1;
	//3 
	VIDCON0=(1<<4)|(14<<6);
	//4 
	VIDCON1 = (1<<5)|(1<<6);
	//5 不配置I80
	//6 ITU (BT.601) Interface Control
	//7
	VIDTCON0 = 9|(1<<8)|(1<<16);
	VIDTCON1 = 40|(1<<8)|(1<<16);
	VIDTCON2 = 479|(271<<11);
	//8
	WINCON0 = 1|(11<<2);
	//9
	VIDOSD0A = 0;
	VIDOSD0B = 271|(479<<11);
	//10
	VIDOSD0C = 480*272;
	//11
	VIDW00ADD0B0 = FRAMEBUFFER+(count%20)*INDEX;
	VIDW00ADD1B0 = FRAMEBUFFER+(count%20)*INDEX+(480*272*4);
	VIDCON0|=3;

/*
	while(1)
	{
		VIDW00ADD0B0 = FRAMEBUFFER+(count%20)*INDEX;
		VIDW00ADD1B0 = FRAMEBUFFER+(count%20)*INDEX+(480*272*4);
		VIDCON0|=3;
		count++;

		led_on_all();
		long_delay();
		led_off_all();
		long_delay();
	}
*/
}

//按键S6控制往上翻页，S7往下翻页，看门口定时往下翻页
void init_irq()
{
	unsigned long *irq_handler = 0x53000000;	
	*irq_handler = (unsigned long)do_irq;

	GPNCON &= ~(0xf<<8);
	GPNCON |= (0xa<<8);

    /* ��Ƕ��࣬���CPRS I����λ�������ж� */
	__asm__ __volatile__ 
	(
	 	"mrs r0, cpsr\n\t"
	 	"bic r0, r0, #0x80\n\t"
	 	"msr cpsr, r0\n\t"
	 	:::"r0"
	);

	VIC0INTSELECT &= ~((1<<1)|(1<<26));//select irq interrupt
	VIC0INTENABLE |= ((1<<1)|(1<<26));//enable interrupt

	EINT0CON0 &= ~(7<<8);//S6-up  s7-down
	EINT0CON0 |= (1<<9);//Falling edge triggered
	EINT0MASK &= ~((1<<4)|(1<<5));

	WTCNT=0xA000;
	WTDAT=0xA000;

	WTCON=0|(1<<2)|(3<<3)|(1<<5)|(60<<8);

}

void do_irq(void)
{
	int i;

	//音乐播放的dma中断
	if (VIC1IRQSTATUS & (1<<10)) 
	{
		puts("dma transfer end!\n");	
		DMACIntTCClear = 0x1;
	}

	//按下按键S6的中断处理
	else if((VIC0IRQSTATUS &(1<<1)) && (EINT0PEND &(1<<4)))//s6 
	{
		delay();//去抖
		EINT0PEND = EINT0PEND;
		WTCON &= ~(1<<5);//看门狗清中断，主要想实现看门狗重新计时

		if((count%20)==0)//如果是第一张，再往上翻，就直接显示最后一张
		{
			VIDW00ADD0B0 = FRAMEBUFFER+19*INDEX;
			VIDW00ADD1B0 = FRAMEBUFFER+19*INDEX+(480*272*4);
		}
		//其他情况下，就实现往上滑动的效果
		else
		{
			//一张图片滑动分为34个小周期
			for(i=0;i<35;i++)
			{
				VIDW00ADD0B0 = FRAMEBUFFER+count%20*INDEX-i*(INDEX/34);
				VIDW00ADD1B0 = FRAMEBUFFER+count%20*INDEX-i*(INDEX/34)+(480*272*4);
				short_delay();
			}
		
		}
		count--;
		//看门狗重新启动并喂狗
		WTCNT=0xA000;
		WTCON|=1<<5;

	}

	//按下按键S7的中断处理
	else if((VIC0IRQSTATUS &(1<<1)) && ( EINT0PEND &(1<<5)))//s7
	{
		delay();
		EINT0PEND = EINT0PEND;
		WTCON &= ~(1<<5);

		if((count%20)==19)
		{
			VIDW00ADD0B0 = FRAMEBUFFER;
			VIDW00ADD1B0 = FRAMEBUFFER+INDEX;
		}
		else
		{
			for(i=0;i<35;i++)
			{
				VIDW00ADD0B0 = FRAMEBUFFER+(count%20)*INDEX+i*(INDEX/34);
				VIDW00ADD1B0 = FRAMEBUFFER+(count%20)*INDEX+i*(INDEX/34)+(480*272*4);
				short_delay();
			}
		}
		count++;

		WTCNT=0xA000;
		WTCON|=1<<5;
	}

	//看门狗定时每4s往下翻页
	else
	{

		if((count%20)==19)
		{
			VIDW00ADD0B0 = FRAMEBUFFER;
			VIDW00ADD1B0 = FRAMEBUFFER+INDEX;
		}
		else
		{
			for(i=0;i<35;i++)
			{
				VIDW00ADD0B0 = FRAMEBUFFER+count%20*INDEX+i*(INDEX/34);
				VIDW00ADD1B0 = FRAMEBUFFER+count%20*INDEX+i*(INDEX/34)+(480*272*4);
				short_delay();
			}
		}
		count++;

		WTCLRINT=0;
	}

}

void long_delay()
{
	unsigned long i;

	for(i=0x2fffff;i>0;i--)
	{
		;
	}

}

void delay()
{
	int i;
	for(i=1000000;i>0;i--)
	{
		;
	}

}

void short_delay()
{
	int i;
	for(i=75000;i>0;i--)
	{
		;
	}

}


