#include "s3c6410.h"

 @ ------- PLL init -----------
	.global pll_init

pll_init:
	ldr r0, =OTHERS  							
	ldr r1, [r0]
	ldr r2, =(1<<6)                              
	orr r1, r1, r2 
	str r1, [r0]								

	ldr r2, =(1<<7)                              
	orr r1, r1, r2 
	str r1, [r0]								
sync_loop:
	ldr	r1, [r0]
	mov r2, #0xf00								
	and r1, r1, r2
	cmp r1, r2 
	bne sync_loop

@CLK_DIV0 设置分频 [3:0]==0 [11:9]==1 [8]==1 [15:12]==3
	ldr	r0, =CLK_DIV0
	ldr	r1, [r0]
	bic	r1, r1, #0x30000
	bic	r1, r1, #0xff00
	bic	r1, r1, #0xff
	ldr	r2, =((3 << 12) | (1 << 9) | (1 << 8))
	orr	r1, r1, r2
	str	r1, [r0]

@APLL_CON  MPLL_CON 倍频 [2:0]==1 [13:8]==3 [25:16]==266 [31]==1
    ldr r0, =APLL_CON 
	ldr r1, =(1|(3<<8)|(266<<16)|(1<<31))       
	str r1, [r0]								
    ldr r0, =MPLL_CON 
	str r1, [r0]								

@CLK_SRC 使用倍频后的频率 [0]==1 [1]==1
	ldr r0, =CLK_SRC 
	mov r2, #0x7								
	str	r2, [r0]

@等一会儿，等频率稳定
	mov r1, #0x10000
wait:  subs r1, r1, #1
	bne wait
	mov pc, lr
