#include "s3c6410.h"

	.global ddr_init

ddr_init:
	ldr	r0, =MEM_SYS_CFG
	mov	r1, #0
	str	r1, [r0]

	ldr	r0, =P1MEMCCMD
	mov	r1, #4
	str	r1, [r0]

	ldr	r0, =P1REFRESH
	ldr	r1, =1040
	str	r1, [r0]

	ldr	r0, =P1CASLAT
	ldr	r1, =(3 << 1)
	str	r1, [r0]

	ldr	r0, =P1T_DQSS
	mov	r1, #1
	str	r1, [r0]

	ldr	r0, =P1T_MRD
	mov	r1, #2
	str	r1, [r0]

	ldr	r0, =P1T_RAS
	mov	r1, #7
	str	r1, [r0]

	ldr	r0, =P1T_RC
	mov	r1, #9
	str	r1, [r0]
	
	ldr	r0, =P1T_RCD
	mov	r1, #3
	str	r1, [r0]

	ldr	r0, =P1T_RFC
	ldr	r1, =((8 << 5) | (11))	
	str	r1, [r0]

	ldr	r0, =P1T_RP
	mov	r1, #3
	str	r1, [r0]

	ldr	r0, =P1T_RRD
	mov	r1, #2
	str	r1, [r0]

	ldr	r0, =P1T_WR
	mov	r1, #2
	str	r1, [r0]

	ldr	r0, =P1T_WTR
	mov	r1, #2
	str	r1, [r0]

	ldr	r0, =P1T_XP
	mov	r1, #2
	str	r1, [r0]

	ldr	r0, =P1T_XSR
	mov	r1, #16
	str	r1, [r0]

	ldr	r0, =P1T_ESR
	mov	r1, #16
	str	r1, [r0]
	
	ldr	r0, =P1MEMCFG
	ldr	r1, =((2 << 15) | (0 << 6) | (2 << 3) | 2)
	str	r1, [r0]

	ldr	r0, =P1MEMCFG2
	ldr	r1, =((1 << 11) | (3 << 8) | (1 << 6) | 1)
	str	r1, [r0]

	ldr	r0, =P1_chip_0_cfg
	ldr	r1, =(1 << 16)
	str	r1, [r0]

	ldr	r0, =P1DIRECTCMD
	ldr	r1, =(3 << 18)
	str	r1, [r0]	

	mov	r1, #0
	str	r1, [r0]

	mov	r1, #(1 << 18)	
	str	r1, [r0]
	str	r1, [r0]

	ldr	r1, =((2 << 18) | (2 << 16) | 0)
	str	r1, [r0]
	
	ldr	r1, = ((2 << 18) | (0 << 16) | (3<<4) | 2)
	str	r1, [r0]

	ldr	r0, =P1MEMCCMD
	mov	r1, #0
	str	r1, [r0]

	ldr	r0, =P1MEMSTAT

check_loop:
		ldr	r1, [r0]
		ldr	r2, =0xfffffffc
		bic	r1, r2
		cmp	r1, #1
		bne	check_loop

	mov	pc, lr
