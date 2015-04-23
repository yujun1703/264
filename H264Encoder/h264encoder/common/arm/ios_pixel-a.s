//
//  ios_pixel-a.s
//  x264EncLib
//
//  Created by sensong on 13-5-15.
//  Copyright (c) 2013年 com.tencent.avteam. All rights reserved.
//


.macro function name
.global _\name
.align 2
_\name:

.endm




.text


function x264_pixel_sad_4x4_armv6
push	{r4, r5, r6, lr}
ldr	r4, [r2], r3
ldr	r5, [r0], r1
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usad8	ip, r4, r5
ldr	r4, [r2], r3
ldr	r5, [r0], r1
usada8	ip, r6, lr, ip
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usada8	ip, r4, r5, ip
usada8	r0, r6, lr, ip
pop	{r4, r5, r6, pc}
function x264_pixel_sad_4x8_armv6
push	{r4, r5, r6, lr}
ldr	r4, [r2], r3
ldr	r5, [r0], r1
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usad8	ip, r4, r5
ldr	r4, [r2], r3
ldr	r5, [r0], r1
usada8	ip, r6, lr, ip
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usada8	ip, r4, r5, ip
ldr	r4, [r2], r3
ldr	r5, [r0], r1
usada8	ip, r6, lr, ip
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usada8	ip, r4, r5, ip
ldr	r4, [r2], r3
ldr	r5, [r0], r1
usada8	ip, r6, lr, ip
ldr	r6, [r2], r3
ldr	lr, [r0], r1
usada8	ip, r4, r5, ip
usada8	r0, r6, lr, ip
pop	{r4, r5, r6, pc}
function x264_pixel_sad_4x4_neon
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabdl.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_4x8_neon
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabdl.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_8x4_neon
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_8x8_neon
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_8x16_neon
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_16x8_neon
vld1.64	{d2-d3}, [r2], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vabal.u8	q9, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_16x16_neon
vld1.64	{d2-d3}, [r2], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vabal.u8	q9, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_4x4_neon
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabdl.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_4x8_neon
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabdl.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vld1.32	{d1[]}, [r2, :32], r3
vld1.32	{d0[]}, [r0, :32], r1
vabal.u8	q8, d0, d1
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x4_neon
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x8_neon
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x16_neon
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_16x8_neon
vld1.64	{d2-d3}, [r2, :128], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vabal.u8	q9, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_16x16_neon
vld1.64	{d2-d3}, [r2, :128], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q9, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q8, d4, d6
vabal.u8	q9, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x4_neon_dual
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabdl.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x8_neon_dual
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabdl.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_8x16_neon_dual
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabdl.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabdl.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vld1.64	{d1}, [r2, :64], r3
vld1.64	{d0}, [r0, :64], r1
vabal.u8	q8, d0, d1
vld1.64	{d3}, [r2, :64], r3
vld1.64	{d2}, [r0, :64], r1
vabal.u8	q9, d2, d3
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_16x8_neon_dual
vld1.64	{d2-d3}, [r2, :128], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabdl.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabdl.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vabal.u8	q11, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	q9, q10, q11
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_aligned_16x16_neon_dual
vld1.64	{d2-d3}, [r2, :128], r3
vld1.64	{d0-d1}, [r0, :128], r1
vabdl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabdl.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabdl.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabdl.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vld1.64	{d2-d3}, [r2, :128], r3
vabal.u8	q11, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vabal.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2, :128], r3
vabal.u8	q9, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vabal.u8	q10, d4, d6
vabal.u8	q11, d5, d7
vadd.i16	q8, q8, q9
vadd.i16	q9, q10, q11
vadd.i16	q8, q8, q9
vadd.i16	d16, d16, d17
vpadd.i16	d0, d16, d16
vpaddl.u16	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_sad_x3_4x4_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_4x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_8x4_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_8x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_8x16_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_16x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabdl.u8	q8, d2, d0
vabdl.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabdl.u8	q9, d4, d0
vabdl.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabdl.u8	q10, d6, d0
vabdl.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vadd.i16	q8, q8, q12
vadd.i16	q9, q9, q13
vadd.i16	q10, q10, q14
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x3_16x16_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabdl.u8	q8, d2, d0
vabdl.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabdl.u8	q9, d4, d0
vabdl.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabdl.u8	q10, d6, d0
vabdl.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vadd.i16	q8, q8, q12
vadd.i16	q9, q9, q13
vadd.i16	q10, q10, q14
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0}, [r7]!
vst1.32	{d1[0]}, [r7, :32]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_4x4_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabdl.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_4x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabdl.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vld1.32	{d0[]}, [r0, :32], lr
vld1.32	{d1[]}, [r1], r6
vabal.u8	q8, d1, d0
vld1.32	{d2[]}, [r2], r6
vabal.u8	q9, d2, d0
vld1.32	{d3[]}, [r3], r6
vabal.u8	q10, d3, d0
vld1.32	{d4[]}, [ip], r6
vabal.u8	q11, d4, d0
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_8x4_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabdl.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vadd.i16	d22, d22, d23
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_8x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabdl.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vadd.i16	d22, d22, d23
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_8x16_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabdl.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabdl.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabdl.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabdl.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vld1.64	{d0}, [r0, :64], lr
vld1.64	{d1}, [r1], r6
vabal.u8	q8, d1, d0
vld1.64	{d2}, [r2], r6
vabal.u8	q9, d2, d0
vld1.64	{d3}, [r3], r6
vabal.u8	q10, d3, d0
vld1.64	{d4}, [ip], r6
vabal.u8	q11, d4, d0
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vadd.i16	d22, d22, d23
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_16x8_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabdl.u8	q8, d2, d0
vabdl.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabdl.u8	q9, d4, d0
vabdl.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabdl.u8	q10, d6, d0
vabdl.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabdl.u8	q11, d2, d0
vabdl.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vadd.i16	q8, q8, q12
vadd.i16	q9, q9, q13
vadd.i16	q10, q10, q14
vadd.i16	q11, q11, q15
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vadd.i16	d22, d22, d23
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_sad_x4_16x16_neon
push	{r6, r7, lr}
ldrd	r6,r7, [sp, #16]
ldr	ip, [sp, #12]
mov	lr, #16	@ 0x10
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabdl.u8	q8, d2, d0
vabdl.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabdl.u8	q9, d4, d0
vabdl.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabdl.u8	q10, d6, d0
vabdl.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabdl.u8	q11, d2, d0
vabdl.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vld1.64	{d0-d1}, [r0, :128], lr
vld1.64	{d2-d3}, [r1], r6
vabal.u8	q8, d2, d0
vabal.u8	q12, d3, d1
vld1.64	{d4-d5}, [r2], r6
vabal.u8	q9, d4, d0
vabal.u8	q13, d5, d1
vld1.64	{d6-d7}, [r3], r6
vabal.u8	q10, d6, d0
vabal.u8	q14, d7, d1
vld1.64	{d2-d3}, [ip], r6
vabal.u8	q11, d2, d0
vabal.u8	q15, d3, d1
vadd.i16	q8, q8, q12
vadd.i16	q9, q9, q13
vadd.i16	q10, q10, q14
vadd.i16	q11, q11, q15
vadd.i16	d16, d16, d17
vadd.i16	d18, d18, d19
vadd.i16	d20, d20, d21
vadd.i16	d22, d22, d23
vpadd.i16	d0, d16, d18
vpadd.i16	d1, d20, d22
vpaddl.u16	q0, q0
vst1.32	{d0-d1}, [r7]
pop	{r6, r7, pc}
function x264_pixel_ssd_4x4_neon
vld1.32	{d16[]}, [r0, :32], r1
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmull.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vmlal.s16	q0, d4, d4
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_4x8_neon
vld1.32	{d16[]}, [r0, :32], r1
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmull.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vld1.32	{d16[]}, [r0, :32], r1
vmlal.s16	q0, d4, d4
vld1.32	{d17[]}, [r2, :32], r3
vsubl.u8	q2, d16, d17
vmlal.s16	q0, d4, d4
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_8x4_neon
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmull.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_8x8_neon
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmull.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_8x16_neon
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmull.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vld1.64	{d16}, [r0, :64], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q2, d16, d17
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_16x8_neon
vld1.64	{d16-d17}, [r0, :128], r1
vld1.64	{d18-d19}, [r2, :128], r3
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmull.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_ssd_16x16_neon
vld1.64	{d16-d17}, [r0, :128], r1
vld1.64	{d18-d19}, [r2, :128], r3
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmull.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vld1.64	{d16-d17}, [r0, :128], r1
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vld1.64	{d18-d19}, [r2, :128], r3
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vsubl.u8	q2, d16, d18
vsubl.u8	q3, d17, d19
vmlal.s16	q0, d4, d4
vmlal.s16	q0, d5, d5
vmlal.s16	q0, d6, d6
vmlal.s16	q0, d7, d7
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_var_8x8_neon
vld1.64	{d16}, [r0, :64], r1
vmull.u8	q1, d16, d16
vmovl.u8	q0, d16
vld1.64	{d18}, [r0, :64], r1
vmull.u8	q2, d18, d18
vaddw.u8	q0, q0, d18
vld1.64	{d20}, [r0, :64], r1
vmull.u8	q3, d20, d20
vaddw.u8	q0, q0, d20
vpaddl.u16	q1, q1
vld1.64	{d22}, [r0, :64], r1
vmull.u8	q8, d22, d22
vaddw.u8	q0, q0, d22
vpaddl.u16	q2, q2
vld1.64	{d24}, [r0, :64], r1
vmull.u8	q9, d24, d24
vaddw.u8	q0, q0, d24
vpadal.u16	q1, q3
vld1.64	{d26}, [r0, :64], r1
vmull.u8	q10, d26, d26
vaddw.u8	q0, q0, d26
vpadal.u16	q2, q8
vld1.64	{d24}, [r0, :64], r1
vmull.u8	q14, d24, d24
vaddw.u8	q0, q0, d24
vpadal.u16	q1, q9
vld1.64	{d26}, [r0, :64], r1
vmull.u8	q15, d26, d26
vaddw.u8	q0, q0, d26
vpadal.u16	q2, q10
b	_x264_var_end
function x264_pixel_var_16x16_neon
vld1.64	{d16-d17}, [r0, :128], r1
vmull.u8	q12, d16, d16
vmovl.u8	q0, d16
vmull.u8	q13, d17, d17
vaddw.u8	q0, q0, d17
vld1.64	{d18-d19}, [r0, :128], r1
vmull.u8	q14, d18, d18
vaddw.u8	q0, q0, d18
vpaddl.u16	q1, q12
vmull.u8	q15, d19, d19
vaddw.u8	q0, q0, d19
vpaddl.u16	q2, q13
mov	ip, #7	@ 0x7
var16_loop:
subs	ip, ip, #1	@ 0x1
vld1.64	{d16-d17}, [r0, :128], r1
vmull.u8	q12, d16, d16
vaddw.u8	q0, q0, d16
vpadal.u16	q1, q14
vmull.u8	q13, d17, d17
vaddw.u8	q0, q0, d17
vpadal.u16	q2, q15
vld1.64	{d18-d19}, [r0, :128], r1
vmull.u8	q14, d18, d18
vaddw.u8	q0, q0, d18
vpadal.u16	q1, q12
vmull.u8	q15, d19, d19
vaddw.u8	q0, q0, d19
vpadal.u16	q2, q13
bgt	var16_loop
_x264_var_end:
vpaddl.u16	q8, q14
vpaddl.u16	q9, q15
vadd.i32	q1, q1, q8
vadd.i16	d0, d0, d1
vadd.i32	q1, q1, q9
vadd.i32	q1, q1, q2
vpaddl.u16	d0, d0
vadd.i32	d2, d2, d3
vpadd.i32	d0, d0, d2
vmov	r0, r1, d0
bx	lr
function x264_pixel_var2_8x8_neon
vld1.64	{d0}, [r0, :64], r1
vld1.64	{d1}, [r2, :64], r3
vsubl.u8	q0, d0, d1
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vsubl.u8	q8, d16, d17
vmull.s16	q1, d0, d0
vmlal.s16	q1, d1, d1
vld1.64	{d18}, [r0, :64], r1
vld1.64	{d19}, [r2, :64], r3
vadd.i16	q0, q0, q8
vsubl.u8	q9, d18, d19
vmull.s16	q2, d16, d16
vmlal.s16	q2, d17, d17
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vadd.i16	q0, q0, q9
vsubl.u8	q8, d16, d17
vmlal.s16	q1, d18, d18
vmlal.s16	q1, d19, d19
vld1.64	{d18}, [r0, :64], r1
vld1.64	{d19}, [r2, :64], r3
vadd.i16	q0, q0, q8
vsubl.u8	q9, d18, d19
vmlal.s16	q2, d16, d16
vmlal.s16	q2, d17, d17
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vadd.i16	q0, q0, q9
vsubl.u8	q8, d16, d17
vmlal.s16	q1, d18, d18
vmlal.s16	q1, d19, d19
vld1.64	{d18}, [r0, :64], r1
vld1.64	{d19}, [r2, :64], r3
vadd.i16	q0, q0, q8
vsubl.u8	q9, d18, d19
vmlal.s16	q2, d16, d16
vmlal.s16	q2, d17, d17
vld1.64	{d16}, [r0, :64], r1
vld1.64	{d17}, [r2, :64], r3
vadd.i16	q0, q0, q9
vsubl.u8	q8, d16, d17
vmlal.s16	q1, d18, d18
vmlal.s16	q1, d19, d19
vadd.i16	q0, q0, q8
vmlal.s16	q2, d16, d16
vmlal.s16	q2, d17, d17
ldr	ip, [sp]
vadd.i16	d0, d0, d1
vadd.i32	q1, q1, q2
vpaddl.s16	d0, d0
vadd.i32	d1, d2, d3
vpadd.i32	d0, d0, d1
vmov	r0, r1, d0
vst1.32	{d0[1]}, [ip, :32]
mul	r0, r0, r0
sub	r0, r1, r0, lsr #6
bx	lr
function x264_pixel_satd_4x4_neon
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vld1.32	{d3[]}, [r2], r3
vld1.32	{d2[]}, [r0, :32], r1
vld1.32	{d1[1]}, [r2], r3
vld1.32	{d0[1]}, [r0, :32], r1
vld1.32	{d3[1]}, [r2], r3
vld1.32	{d2[1]}, [r0, :32], r1
vsubl.u8	q0, d0, d1
vsubl.u8	q1, d2, d3
vadd.i16	q2, q0, q1
vsub.i16	q3, q0, q1
vadd.i16	d0, d4, d5
vsub.i16	d2, d4, d5
vadd.i16	d1, d6, d7
vsub.i16	d3, d6, d7
vtrn.16	q0, q1
vadd.i16	q2, q0, q1
vsub.i16	q3, q0, q1
vtrn.32	q2, q3
vabs.s16	q2, q2
vabs.s16	q3, q3
vmax.s16	q0, q2, q3
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_satd_4x8_neon
vld1.32	{d1[]}, [r2], r3
vld1.32	{d0[]}, [r0, :32], r1
vld1.32	{d3[]}, [r2], r3
vld1.32	{d2[]}, [r0, :32], r1
vld1.32	{d5[]}, [r2], r3
vld1.32	{d4[]}, [r0, :32], r1
vld1.32	{d7[]}, [r2], r3
vld1.32	{d6[]}, [r0, :32], r1
vld1.32	{d1[1]}, [r2], r3
vld1.32	{d0[1]}, [r0, :32], r1
vsubl.u8	q0, d0, d1
vld1.32	{d3[1]}, [r2], r3
vld1.32	{d2[1]}, [r0, :32], r1
vsubl.u8	q1, d2, d3
vld1.32	{d5[1]}, [r2], r3
vld1.32	{d4[1]}, [r0, :32], r1
vsubl.u8	q2, d4, d5
vld1.32	{d7[1]}, [r2], r3
vadd.i16	q8, q0, q1
vsub.i16	q9, q0, q1
vld1.32	{d6[1]}, [r0, :32], r1
vsubl.u8	q3, d6, d7
vadd.i16	q10, q2, q3
vsub.i16	q11, q2, q3
b	_x264_satd_4x8_8x4_end_neon
function x264_pixel_satd_8x4_neon
vld1.64	{d1}, [r2], r3
vld1.64	{d0}, [r0, :64], r1
vsubl.u8	q0, d0, d1
vld1.64	{d3}, [r2], r3
vld1.64	{d2}, [r0, :64], r1
vsubl.u8	q1, d2, d3
vld1.64	{d5}, [r2], r3
vld1.64	{d4}, [r0, :64], r1
vsubl.u8	q2, d4, d5
vld1.64	{d7}, [r2], r3
vadd.i16	q8, q0, q1
vsub.i16	q9, q0, q1
vld1.64	{d6}, [r0, :64], r1
vsubl.u8	q3, d6, d7
vadd.i16	q10, q2, q3
vsub.i16	q11, q2, q3
function x264_satd_4x8_8x4_end_neon
vadd.i16	q0, q8, q10
vadd.i16	q1, q9, q11
vsub.i16	q2, q8, q10
vsub.i16	q3, q9, q11
vtrn.16	q0, q1
vadd.i16	q8, q0, q1
vtrn.16	q2, q3
vsub.i16	q9, q0, q1
vadd.i16	q10, q2, q3
vsub.i16	q11, q2, q3
vtrn.32	q8, q10
vabs.s16	q8, q8
vtrn.32	q9, q11
vabs.s16	q10, q10
vabs.s16	q9, q9
vabs.s16	q11, q11
vmax.u16	q0, q8, q10
vmax.u16	q1, q9, q11
vadd.i16	q0, q0, q1
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_satd_8x8_neon
mov	ip, lr
bl	_x264_satd_8x8_neon
vadd.i16	q0, q12, q13
vadd.i16	q1, q14, q15
vadd.i16	q0, q0, q1
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
mov	lr, ip
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_satd_8x16_neon
vstmdb	sp!, {d8-d11}
mov	ip, lr
bl	_x264_satd_8x8_neon
vadd.i16	q4, q12, q13
vadd.i16	q5, q14, q15
bl	_x264_satd_8x8_neon
vadd.i16	q4, q4, q12
vadd.i16	q5, q5, q13
vadd.i16	q4, q4, q14
vadd.i16	q5, q5, q15
vadd.i16	q0, q4, q5
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
vldmia	sp!, {d8-d11}
mov	lr, ip
vmov.32	r0, d0[0]
bx	lr
function x264_satd_8x8_neon
vld1.32	{d1}, [r2], r3
vld1.32	{d0}, [r0, :64], r1
vsubl.u8	q8, d0, d1
vld1.32	{d3}, [r2], r3
vld1.32	{d2}, [r0, :64], r1
vsubl.u8	q9, d2, d3
vld1.32	{d5}, [r2], r3
vld1.32	{d4}, [r0, :64], r1
vsubl.u8	q10, d4, d5
vld1.32	{d7}, [r2], r3
vld1.32	{d6}, [r0, :64], r1
vsubl.u8	q11, d6, d7
vld1.64	{d7}, [r2], r3
vadd.i16	q0, q8, q9
vsub.i16	q1, q8, q9
vld1.64	{d6}, [r0, :64], r1
vsubl.u8	q12, d6, d7
vld1.64	{d17}, [r2], r3
vadd.i16	q2, q10, q11
vsub.i16	q3, q10, q11
vld1.64	{d16}, [r0, :64], r1
vsubl.u8	q13, d16, d17
vld1.64	{d19}, [r2], r3
vadd.i16	q8, q0, q2
vsub.i16	q10, q0, q2
vld1.64	{d18}, [r0, :64], r1
vsubl.u8	q14, d18, d19
vld1.64	{d1}, [r2], r3
vadd.i16	q9, q1, q3
vsub.i16	q11, q1, q3
vld1.64	{d0}, [r0, :64], r1
vsubl.u8	q15, d0, d1
function x264_satd_8x4v_8x8h_neon
vadd.i16	q0, q12, q13
vsub.i16	q1, q12, q13
vadd.i16	q2, q14, q15
vsub.i16	q3, q14, q15
vtrn.16	q8, q9
vadd.i16	q12, q0, q2
vsub.i16	q14, q0, q2
vtrn.16	q10, q11
vadd.i16	q13, q1, q3
vsub.i16	q15, q1, q3
vadd.i16	q0, q8, q9
vsub.i16	q1, q8, q9
vtrn.16	q12, q13
vadd.i16	q2, q10, q11
vsub.i16	q3, q10, q11
vtrn.16	q14, q15
vadd.i16	q8, q12, q13
vsub.i16	q9, q12, q13
vtrn.32	q0, q2
vadd.i16	q10, q14, q15
vsub.i16	q11, q14, q15
vtrn.32	q1, q3
vabs.s16	q0, q0
vabs.s16	q2, q2
vtrn.32	q8, q10
vabs.s16	q1, q1
vabs.s16	q3, q3
vtrn.32	q9, q11
vabs.s16	q8, q8
vabs.s16	q10, q10
vabs.s16	q9, q9
vabs.s16	q11, q11
vmax.s16	q12, q0, q2
vmax.s16	q13, q1, q3
vmax.s16	q14, q8, q10
vmax.s16	q15, q9, q11
bx	lr
function x264_pixel_satd_16x8_neon
vstmdb	sp!, {d8-d11}
mov	ip, lr
bl	_x264_satd_16x4_neon
vadd.i16	q4, q12, q13
vadd.i16	q5, q14, q15
bl	_x264_satd_16x4_neon
vadd.i16	q4, q4, q12
vadd.i16	q5, q5, q13
vadd.i16	q4, q4, q14
vadd.i16	q5, q5, q15
vadd.i16	q0, q4, q5
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
vldmia	sp!, {d8-d11}
mov	lr, ip
vmov.32	r0, d0[0]
bx	lr
function x264_pixel_satd_16x16_neon
vstmdb	sp!, {d8-d11}
mov	ip, lr
bl	_x264_satd_16x4_neon
vadd.i16	q4, q12, q13
vadd.i16	q5, q14, q15
bl	_x264_satd_16x4_neon
vadd.i16	q4, q4, q12
vadd.i16	q5, q5, q13
vadd.i16	q4, q4, q14
vadd.i16	q5, q5, q15
bl	_x264_satd_16x4_neon
vadd.i16	q4, q4, q12
vadd.i16	q5, q5, q13
vadd.i16	q4, q4, q14
vadd.i16	q5, q5, q15
bl	_x264_satd_16x4_neon
vadd.i16	q4, q4, q12
vadd.i16	q5, q5, q13
vadd.i16	q4, q4, q14
vadd.i16	q5, q5, q15
vadd.i16	q0, q4, q5
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
vldmia	sp!, {d8-d11}
mov	lr, ip
vmov.32	r0, d0[0]
bx	lr
function x264_satd_16x4_neon
vld1.64	{d2-d3}, [r2], r3
vld1.64	{d0-d1}, [r0, :128], r1
vsubl.u8	q8, d0, d2
vld1.64	{d6-d7}, [r2], r3
vsubl.u8	q12, d1, d3
vld1.64	{d4-d5}, [r0, :128], r1
vsubl.u8	q9, d4, d6
vld1.64	{d2-d3}, [r2], r3
vsubl.u8	q13, d5, d7
vld1.64	{d0-d1}, [r0, :128], r1
vsubl.u8	q10, d0, d2
vld1.64	{d6-d7}, [r2], r3
vsubl.u8	q14, d1, d3
vadd.i16	q0, q8, q9
vld1.64	{d4-d5}, [r0, :128], r1
vsub.i16	q1, q8, q9
vsubl.u8	q11, d4, d6
vsubl.u8	q15, d5, d7
vadd.i16	q2, q10, q11
vsub.i16	q3, q10, q11
vadd.i16	q8, q0, q2
vsub.i16	q10, q0, q2
vadd.i16	q9, q1, q3
vsub.i16	q11, q1, q3
b	_x264_satd_8x4v_8x8h_neon
function x264_pixel_sa8d_8x8_neon
mov	ip, lr
bl	_x264_sa8d_8x8_neon
vadd.i16	q0, q8, q9
vadd.i16	d0, d0, d1
vpaddl.u16	d0, d0
vpaddl.u32	d0, d0
mov	lr, ip
vmov.32	r0, d0[0]
add	r0, r0, #1	@ 0x1
lsr	r0, r0, #1
bx	lr
function x264_pixel_sa8d_16x16_neon
vstmdb	sp!, {d8-d11}
mov	ip, lr
bl	_x264_sa8d_8x8_neon
vpaddl.u16	q4, q8
vpaddl.u16	q5, q9
bl	_x264_sa8d_8x8_neon
vpadal.u16	q4, q8
vpadal.u16	q5, q9
sub	r0, r0, r1, lsl #4
sub	r2, r2, r3, lsl #4
add	r0, r0, #8	@ 0x8
add	r2, r2, #8	@ 0x8
bl	_x264_sa8d_8x8_neon
vpadal.u16	q4, q8
vpadal.u16	q5, q9
bl	_x264_sa8d_8x8_neon
vpaddl.u16	q8, q8
vpaddl.u16	q9, q9
vadd.i32	q0, q4, q8
vadd.i32	q1, q5, q9
vadd.i32	q0, q0, q1
vadd.i32	d0, d0, d1
vpadd.i32	d0, d0, d0
vldmia	sp!, {d8-d11}
mov	lr, ip
vmov.32	r0, d0[0]
add	r0, r0, #1	@ 0x1
lsr	r0, r0, #1
bx	lr
function x264_sa8d_8x8_neon
vld1.32	{d1}, [r2], r3
vld1.32	{d0}, [r0, :64], r1
vsubl.u8	q8, d0, d1
vld1.32	{d3}, [r2], r3
vld1.32	{d2}, [r0, :64], r1
vsubl.u8	q9, d2, d3
vld1.32	{d5}, [r2], r3
vld1.32	{d4}, [r0, :64], r1
vsubl.u8	q10, d4, d5
vld1.32	{d7}, [r2], r3
vld1.32	{d6}, [r0, :64], r1
vsubl.u8	q11, d6, d7
vld1.64	{d7}, [r2], r3
vadd.i16	q0, q8, q9
vsub.i16	q1, q8, q9
vld1.64	{d6}, [r0, :64], r1
vsubl.u8	q12, d6, d7
vld1.64	{d17}, [r2], r3
vadd.i16	q2, q10, q11
vsub.i16	q3, q10, q11
vld1.64	{d16}, [r0, :64], r1
vsubl.u8	q13, d16, d17
vld1.64	{d19}, [r2], r3
vadd.i16	q8, q0, q2
vsub.i16	q10, q0, q2
vld1.64	{d18}, [r0, :64], r1
vsubl.u8	q14, d18, d19
vld1.64	{d1}, [r2], r3
vadd.i16	q9, q1, q3
vsub.i16	q11, q1, q3
vld1.64	{d0}, [r0, :64], r1
vsubl.u8	q15, d0, d1
vadd.i16	q0, q12, q13
vsub.i16	q1, q12, q13
vadd.i16	q2, q14, q15
vsub.i16	q3, q14, q15
vadd.i16	q12, q0, q2
vsub.i16	q14, q0, q2
vadd.i16	q13, q1, q3
vsub.i16	q15, q1, q3
vadd.i16	q0, q8, q12
vsub.i16	q8, q8, q12
vadd.i16	q1, q9, q13
vsub.i16	q9, q9, q13
vadd.i16	q2, q10, q14
vsub.i16	q10, q10, q14
vtrn.16	q8, q9
vadd.i16	q3, q11, q15
vsub.i16	q11, q11, q15
vtrn.16	q0, q1
vadd.i16	q12, q8, q9
vsub.i16	q13, q8, q9
vtrn.16	q10, q11
vadd.i16	q8, q0, q1
vsub.i16	q9, q0, q1
vtrn.16	q2, q3
vadd.i16	q14, q10, q11
vsub.i16	q15, q10, q11
vadd.i16	q10, q2, q3
vtrn.32	q12, q14
vsub.i16	q11, q2, q3
vtrn.32	q13, q15
vadd.i16	q0, q12, q14
vsub.i16	q2, q12, q14
vtrn.32	q8, q10
vadd.i16	q1, q13, q15
vsub.i16	q3, q13, q15
vtrn.32	q9, q11
vadd.i16	q12, q8, q10
vsub.i16	q14, q8, q10
vadd.i16	q13, q9, q11
vsub.i16	q15, q9, q11
vswp	d1, d24
vabs.s16	q0, q0
vabs.s16	q12, q12
vswp	d3, d26
vabs.s16	q1, q1
vabs.s16	q13, q13
vswp	d5, d28
vabs.s16	q2, q2
vabs.s16	q14, q14
vswp	d7, d30
vabs.s16	q3, q3
vabs.s16	q15, q15
vmax.s16	q8, q0, q12
vmax.s16	q9, q1, q13
vmax.s16	q10, q2, q14
vmax.s16	q11, q3, q15
vadd.i16	q8, q8, q9
vadd.i16	q9, q10, q11
bx	lr



function x264_pixel_hadamard_ac_8x8_neon
vstmdb	sp!, {d8-d15}
adr	ip, mask_ac4	@ 0x3404
vmov.i8	q4, #0	@ 0x00
vld1.64	{d12-d15}, [ip, :128]
vmov.i8	q5, #0	@ 0x00
mov	ip, lr
bl	_x264_hadamard_ac_8x8_neon
vadd.i32	d8, d8, d9
vadd.i32	d10, d10, d11
vpadd.i32	d0, d8, d10
vldmia	sp!, {d8-d15}
mov	lr, ip
vmov	r0, r1, d0
lsr	r0, r0, #1
lsr	r1, r1, #2
bx	lr
function x264_pixel_hadamard_ac_8x16_neon
vstmdb	sp!, {d8-d15}
adr	ip, mask_ac4	@ 0x3404
vmov.i8	q4, #0	@ 0x00
vld1.64	{d12-d15}, [ip, :128]
vmov.i8	q5, #0	@ 0x00
mov	ip, lr
bl	_x264_hadamard_ac_8x8_neon
bl	_x264_hadamard_ac_8x8_neon
vadd.i32	d8, d8, d9
vadd.i32	d10, d10, d11
vpadd.i32	d0, d8, d10
vldmia	sp!, {d8-d15}
mov	lr, ip
vmov	r0, r1, d0
lsr	r0, r0, #1
lsr	r1, r1, #2
bx	lr


mask_ac4:
.short 0, -1, -1, -1, 0, -1, -1, -1

.text

function x264_pixel_hadamard_ac_16x8_neon
vstmdb	sp!, {d8-d15}
adr	ip, mask_ac4	@ 0x3404
vmov.i8	q4, #0	@ 0x00
vld1.64	{d12-d15}, [ip, :128]
vmov.i8	q5, #0	@ 0x00
mov	ip, lr
bl	_x264_hadamard_ac_8x8_neon
sub	r0, r0, r1, lsl #3
add	r0, r0, #8	@ 0x8
bl	_x264_hadamard_ac_8x8_neon
vadd.i32	d8, d8, d9
vadd.i32	d10, d10, d11
vpadd.i32	d0, d8, d10
vldmia	sp!, {d8-d15}
mov	lr, ip
vmov	r0, r1, d0
lsr	r0, r0, #1
lsr	r1, r1, #2
bx	lr
function x264_pixel_hadamard_ac_16x16_neon
vstmdb	sp!, {d8-d15}
adr	ip, mask_ac4	@ 0x3404
vmov.i8	q4, #0	@ 0x00
vld1.64	{d12-d15}, [ip, :128]
vmov.i8	q5, #0	@ 0x00
mov	ip, lr
bl	_x264_hadamard_ac_8x8_neon
bl	_x264_hadamard_ac_8x8_neon
sub	r0, r0, r1, lsl #3
add	r0, r0, #8	@ 0x8
bl	_x264_hadamard_ac_8x8_neon
sub	r0, r0, r1, lsl #4
bl	_x264_hadamard_ac_8x8_neon
vadd.i32	d8, d8, d9
vadd.i32	d10, d10, d11
vpadd.i32	d0, d8, d10
vldmia	sp!, {d8-d15}
mov	lr, ip
vmov	r0, r1, d0
lsr	r0, r0, #1
lsr	r1, r1, #2
bx	lr
function x264_hadamard_ac_8x8_neon
vld1.64	{d2}, [r0, :64], r1
vld1.64	{d3}, [r0, :64], r1
vaddl.u8	q0, d2, d3
vld1.64	{d6}, [r0, :64], r1
vsubl.u8	q1, d2, d3
vld1.64	{d7}, [r0, :64], r1
vaddl.u8	q2, d6, d7
vld1.64	{d18}, [r0, :64], r1
vsubl.u8	q3, d6, d7
vld1.64	{d19}, [r0, :64], r1
vaddl.u8	q8, d18, d19
vld1.64	{d22}, [r0, :64], r1
vsubl.u8	q9, d18, d19
vld1.64	{d23}, [r0, :64], r1
vadd.i16	q12, q0, q2
vsub.i16	q14, q0, q2
vadd.i16	q13, q1, q3
vsub.i16	q15, q1, q3
vaddl.u8	q10, d22, d23
vsubl.u8	q11, d22, d23
vtrn.16	q12, q13
vadd.i16	q0, q8, q10
vsub.i16	q2, q8, q10
vadd.i16	q1, q9, q11
vsub.i16	q3, q9, q11
vtrn.16	q14, q15
vadd.i16	q8, q12, q13
vsub.i16	q9, q12, q13
vtrn.16	q0, q1
vadd.i16	q10, q14, q15
vsub.i16	q11, q14, q15
vtrn.16	q2, q3
vadd.i16	q12, q0, q1
vsub.i16	q13, q0, q1
vtrn.32	q8, q10
vadd.i16	q14, q2, q3
vsub.i16	q15, q2, q3
vtrn.32	q9, q11
vadd.i16	q0, q8, q10
vsub.i16	q2, q8, q10
vtrn.32	q12, q14
vadd.i16	q1, q9, q11
vsub.i16	q3, q9, q11
vtrn.32	q13, q15
vadd.i16	q8, q12, q14
vsub.i16	q10, q12, q14
vadd.i16	q9, q13, q15
vsub.i16	q11, q13, q15
vabs.s16	q12, q0
vabs.s16	q13, q8
vabs.s16	q15, q1
vadd.i16	q12, q12, q13
vabs.s16	q14, q2
vand	q12, q12, q6
vabs.s16	q13, q3
vadd.i16	q12, q12, q15
vabs.s16	q15, q9
vadd.i16	q12, q12, q14
vabs.s16	q14, q10
vadd.i16	q12, q12, q13
vabs.s16	q13, q11
vadd.i16	q12, q12, q15
vsub.i16	q15, q11, q3
vadd.i16	q12, q12, q14
vadd.i16	q14, q11, q3
vadd.i16	q12, q12, q13
vsub.i16	q13, q10, q2
vadd.i16	q2, q10, q2
vpadal.u16	q4, q12
vadd.i16	q10, q9, q1
vsub.i16	q11, q9, q1
vadd.i16	q9, q0, q8
vsub.i16	q8, q0, q8
vswp	d29, d30
vabs.s16	q14, q14
vabs.s16	q15, q15
vswp	d5, d26
vabs.s16	q2, q2
vabs.s16	q13, q13
vswp	d21, d22
vabs.s16	q10, q10
vabs.s16	q11, q11
vmax.s16	q3, q14, q15
vmax.s16	q2, q2, q13
vmax.s16	q1, q10, q11
vswp	d19, d16
vadd.i16	q14, q9, q8
vsub.i16	q15, q9, q8
vadd.i16	q2, q2, q3
vadd.i16	q2, q2, q1
vand	q14, q14, q7
vadd.i16	q2, q2, q2
vabs.s16	q15, q15
vabs.s16	q14, q14
vadd.i16	q2, q2, q15
vadd.i16	q2, q2, q14
vpadal.u16	q5, q2
bx	lr
function x264_pixel_ssim_4x4x2_core_neon
ldr	ip, [sp]
vld1.64	{d0}, [r0], r1
vld1.64	{d2}, [r2], r3
vmull.u8	q2, d0, d0
vmull.u8	q3, d0, d2
vld1.64	{d28}, [r0], r1
vmull.u8	q15, d2, d2
vld1.64	{d29}, [r2], r3
vmull.u8	q8, d28, d28
vmull.u8	q9, d28, d29
vpaddl.u16	q2, q2
vpaddl.u16	q3, q3
vaddl.u8	q0, d0, d28
vpadal.u16	q2, q15
vld1.64	{d26}, [r0], r1
vaddl.u8	q1, d2, d29
vmull.u8	q14, d29, d29
vld1.64	{d27}, [r2], r3
vmull.u8	q10, d26, d26
vmull.u8	q11, d26, d27
vpadal.u16	q2, q8
vpadal.u16	q3, q9
vaddw.u8	q0, q0, d26
vpadal.u16	q2, q14
vld1.64	{d28}, [r0], r1
vaddw.u8	q1, q1, d27
vmull.u8	q13, d27, d27
vld1.64	{d29}, [r2], r3
vmull.u8	q8, d28, d28
vmull.u8	q9, d28, d29
vpadal.u16	q2, q10
vpadal.u16	q3, q11
vaddw.u8	q0, q0, d28
vpadal.u16	q2, q13
vaddw.u8	q1, q1, d29
vmull.u8	q15, d29, d29
vpadal.u16	q2, q8
vpaddl.u16	q0, q0
vpaddl.u16	q1, q1
vpadal.u16	q2, q15
vpadal.u16	q3, q9
vpadd.i32	d0, d0, d1
vpadd.i32	d1, d2, d3
vpadd.i32	d2, d4, d5
vpadd.i32	d3, d6, d7
vst4.32	{d0-d3}, [ip]
bx	lr
function x264_pixel_ssim_end4_neon
vld1.32	{d16-d19}, [r0, :128]!
vld1.32	{d20-d23}, [r1, :128]!
vadd.i32	q0, q8, q10
vadd.i32	q1, q9, q11
vld1.32	{d24-d27}, [r0, :128]!
vadd.i32	q0, q0, q1
vld1.32	{d28-d31}, [r1, :128]!
vadd.i32	q2, q12, q14
vadd.i32	q3, q13, q15
vld1.32	{d16-d17}, [r0, :128]
vadd.i32	q1, q1, q2
vld1.32	{d18-d19}, [r1, :128]
vadd.i32	q8, q8, q9
vadd.i32	q2, q2, q3
vadd.i32	q3, q3, q8
vtrn.32	q0, q1
vtrn.32	q2, q3
vswp	d1, d4
vswp	d3, d6
vmul.i32	q8, q0, q1
vmul.i32	q0, q0, q0
vmla.i32	q0, q1, q1
vshl.s32	q3, q3, #7
vshl.s32	q2, q2, #6
vadd.i32	q1, q8, q8
mov	r3, #416	@ 0x1a0
ldr  ip, my235963
vdup.32	q14, r3
vdup.32	q15, ip
vsub.i32	q2, q2, q0
vsub.i32	q3, q3, q1
vadd.i32	q0, q0, q14
vadd.i32	q2, q2, q15
vadd.i32	q1, q1, q14
vadd.i32	q3, q3, q15
vcvt.f32.s32	q0, q0
vcvt.f32.s32	q2, q2
vcvt.f32.s32	q1, q1
vcvt.f32.s32	q3, q3
vmul.f32	q0, q0, q2
vmul.f32	q1, q1, q3
cmp	r2, #4	@ 0x4
fdivs	s0, s4, s0
fdivs	s1, s5, s1
fdivs	s2, s6, s2
fdivs	s3, s7, s3
beq	0x33ec
ldr	r3, mask_ff	@ 0x3400
sub	r3, r3, r2, lsl #2
vld1.64	{d6-d7}, [r3]
vand	q0, q0, q3
flag33ec:
vadd.f32	d0, d0, d1
vpadd.f32	d0, d0, d0
vmov.32	r0, d0[0]
bx	lr

.align 4
my235963:
.word 235963

.byte 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
mask_ff:
.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

