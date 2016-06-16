	.section .text
	.global _start
	.global led_on_all
	.global led_off_all

_start:
	b reset
	b undefined_instruction
	b software_interrupt
	b prefetch_abort
	b data_abort
	.word 0x0
	b irq
	b fiq

undefined_instruction:
	b undefined_instruction
software_interrupt:
	b software_interrupt
prefetch_abort:
	b prefetch_abort
data_abort:
	b data_abort

irq:
	ldr sp,=0x52000000
	sub lr,lr,#4
	stmfd sp!,{r0-r12,lr}

	ldr r0,=0x53000000
	mov lr,pc
	ldr pc,[r0]

	ldmfd sp!,{r0-r12,pc}^

fiq:
	b fiq

reset:
	@ ------- set arm to svc mode,disable irq fiq ---------@
	mrs r0,cpsr
    bic r0,r0,#0x1f
    orr r0,r0,#0xd3
    msr cpsr,r0

	@ ------ disable mmu, DCache, ICache ------@
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, =(1|(1<<2)|(1<<12))
	bic r0, r1
	mcr p15, 0, r0, c1, c0, 0	

	@ ------- Peri port setup ---------@
	ldr r0, =0x70000000
	orr r0, r0, #0x13
	mcr p15,0,r0,c15,c2,4  @ 256M(0x70000000-0x7fffffff)

	@ ------- diable watchdog ---------@
	ldr r0,=0x7E004000      @WTCON
	mov r1,#0x0
	str r1,[r0]

	bl init_led
	bl led_off_all

	@ ------------ PLL init ------------@
	bl pll_init

	@-------- DDR init----------@
	bl ddr_init

	@--------setup stack-----------@
	ldr sp,=0x55000000

	@---------- Nand Flash init------------@
	bl nand_init

	@-------- UART init------------@C start
	bl uart_init
	bl uart_test

	@--------copy pictures to ram----------@
	@----------copy music to ram-----------@
	bl copy_pic_to_sdram
	bl copy_music_to_sdram

	@-------- start show pictures----------@
	bl init_irq
	bl init_music
	bl init_lcd

	@----------- led test -----------@
	bl led_flash

led_flash:
	bl init_led
led_loop:
	bl led_on_all
	bl delay
	bl led_off_all
	bl delay
	b led_loop

init_led:
	ldr r0, =0x7F008820                        @GPMCON
	ldr r1, [r0] 
	ldr r2, =~0xffff 
	and r1, r1, r2 
	ldr r2, =0x1111
	orr r1, r1, r2
	str r1, [r0]
	mov pc, lr

led_on_all:
	ldr r0, =0x7F008824                        @GPMDAT 
	ldr r1, [r0]
	and r1, r1, #~0xf
	str r1, [r0]
	mov pc, lr

led_off_all:
	ldr r0, =0x7F008824                        @GPMDAT 
	ldr r1, [r0]
	orr r1, r1, #0xf
	str r1, [r0]
	mov pc, lr

delay:
	ldr r0, =0xfffff
loop:
	sub r0, r0, #1
	cmp r0, #0
	bne loop
	mov pc, lr

