//
//  ios_cpu-a.s
//  x264EncLib
//
//  Created by sensong on 13-5-15.
//  Copyright (c) 2013年 com.tencent.avteam. All rights reserved.
//

_x264_cpu_neon_test:
vadd.i16 q0, q0, q0
bx lr
_x264_cpu_enable_armv7_counter:
mrc p15, 0, r2, c9, c12, 0
ands r0, r2, #1
andne r0, r2, #9

orr r2, r2, #1
bic r2, r2, #8
mcreq p15, 0, r2, c9, c12, 0
mov r2, #1 << 31
mcr p15, 0, r2, c9, c12, 1
bx lr
_x264_cpu_disable_armv7_counter:
mrc	p15, 0, r0, c9, c12, 0
bic	r0, r0, #1	@ 0x1
mcr	p15, 0, r0, c9, c12, 0
bx	lr
_x264_cpu_fast_neon_mrc_test:
mrc	p15, 0, r0, c9, c14, 0
cmp	r0, #0	@ 0x0
bxeq	lr
push	{r4, r5, r6, lr}
bl	_x264_cpu_enable_armv7_counter
ands	r1, r0, #8	@ 0x8
mov	r3, #0	@ 0x0
mov	ip, #4	@ 0x4
mov	r6, #4	@ 0x4
moveq	r5, #1	@ 0x1
movne	r5, #64	@ 0x40
average_loop:
mov	r4, r5
mrc	p15, 0, r1, c9, c13, 0
flag70:
subs	r4, r4, #1	@ 0x1
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
vmov.32	lr, d0[0]
add	lr, lr, lr
bgt	flag70
mrc	p15, 0, r2, c9, c13, 0
subs	r6, r6, #1	@ 0x1
sub	r2, r2, r1
cmpgt	r2, #240	@ 0xf0
addle	r3, r3, r2
subsle	ip, ip, #1	@ 0x1
bgt	average_loop
ands	r0, r0, #1	@ 0x1
bleq	_x264_cpu_disable_armv7_counter
lsr	r0, r3, #5
cmp	r0, #10	@ 0xa
movgt	r0, #0	@ 0x0
pop	{r4, r5, r6, pc}
