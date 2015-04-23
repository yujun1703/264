//
//  Created by landyji on 20140605.
//  Copyright (c) 2013年 com.tencent.avteam. All rights reserved.
//

.macro function name
.global _\name
.align 2
_\name:
.endm

.text
function ff_clear_blocks_neon
vmov.i16	q0, #0x0
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
vst1.16	{d0, d1}, [r0:128]!
bx	lr

function ff_put_pixels16_neon
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d2, d3}, [r1], r2
vld1.8	{d4, d5}, [r1], r2
pld	[r1, r2, lsl #2]
vld1.8	{d6, d7}, [r1], r2
pld	[r1]
pld	[r1, r2]
pld	[r1, r2, lsl #1]
subs	r3, #0x4
vst1.64	{d0, d1}, [r0:128], r2
vst1.64	{d2, d3}, [r0:128], r2
vst1.64	{d4, d5}, [r0:128], r2
vst1.64	{d6, d7}, [r0:128], r2
bne	_ff_put_pixels16_neon
bx	lr

function ff_put_pixels16_x2_neon
vld1.8	{d0, d1, d2}, [r1], r2
vld1.8	{d4, d5, d6}, [r1], r2
pld	[r1]
pld	[r1, r2]
subs	r3, #0x2
vext.8	q1, q0, q1, #0x1
vrhadd.u8	q0, q0, q1
vext.8	q3, q2, q3, #0x1
vrhadd.u8	q2, q2, q3
vst1.8	{d0, d1}, [r0:128], r2
vst1.8	{d4, d5}, [r0:128], r2
bne	_ff_put_pixels16_x2_neon
bx	lr

function ff_put_pixels16_y2_neon
sub.w	r3, r3, #0x2
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d2, d3}, [r1], r2
1:
subs	r3, #0x2
vrhadd.u8	q2, q0, q1
vld1.8	{d0, d1}, [r1], r2
vrhadd.u8	q3, q0, q1
vld1.8	{d2, d3}, [r1], r2
pld	[r1]
pld	[r1, r2]
vst1.8	{d4, d5}, [r0:128], r2
vst1.8	{d6, d7}, [r0:128], r2
bne	1b
vrhadd.u8	q2, q0, q1
vld1.8	{d0, d1}, [r1], r2
vrhadd.u8	q3, q0, q1
vst1.8	{d4, d5}, [r0:128], r2
vst1.8	{d6, d7}, [r0:128], r2
bx	lr


function ff_put_pixels8_neon
vld1.8	{d0}, [r1], r2
vld1.8	{d1}, [r1], r2
vld1.8	{d2}, [r1], r2
pld	[r1, r2, lsl #2]
vld1.8	{d3}, [r1], r2
pld	[r1]
pld	[r1, r2]
pld	[r1, r2, lsl #1]
subs	r3, #0x4
vst1.8	{d0}, [r0:64], r2
vst1.8	{d1}, [r0:64], r2
vst1.8	{d2}, [r0:64], r2
vst1.8	{d3}, [r0:64], r2
bne	_ff_put_pixels8_neon
bx	lr

function ff_avg_pixels16_neon
mov	r12, r0
1:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d2, d3}, [r1], r2
vld1.8	{d4, d5}, [r1], r2
pld	[r1, r2, lsl #2]
vld1.8	{d6, d7}, [r1], r2
pld	[r1]
pld	[r1, r2]
pld	[r1, r2, lsl #1]
vld1.8	{d16, d17}, [r12:128], r2
vrhadd.u8	q0, q0, q8
vld1.8	{d18, d19}, [r12:128], r2
vrhadd.u8	q1, q1, q9
vld1.8	{d20, d21}, [r12:128], r2
vrhadd.u8	q2, q2, q10
vld1.8	{d22, d23}, [r12:128], r2
vrhadd.u8	q3, q3, q11
subs	r3, #0x4
vst1.64	{d0, d1}, [r0:128], r2
vst1.64	{d2, d3}, [r0:128], r2
vst1.64	{d4, d5}, [r0:128], r2
vst1.64	{d6, d7}, [r0:128], r2
bne	1b
bx	lr


function ff_avg_pixels8_neon
vld1.8	{d0}, [r1], r2
vld1.8	{d1}, [r1], r2
vld1.8	{d2}, [r1], r2
pld	[r1, r2, lsl #2]
vld1.8	{d3}, [r1], r2
pld	[r1]
pld	[r1, r2]
pld	[r1, r2, lsl #1]
vld1.8	{d4}, [r0:64], r2
vrhadd.u8	d0, d0, d4
vld1.8	{d5}, [r0:64], r2
vrhadd.u8	d1, d1, d5
vld1.8	{d6}, [r0:64], r2
vrhadd.u8	d2, d2, d6
vld1.8	{d7}, [r0:64], r2
vrhadd.u8	d3, d3, d7
sub.w	r0, r0, r2, lsl #2
subs	r3, #0x4
vst1.8	{d0}, [r0:64], r2
vst1.8	{d1}, [r0:64], r2
vst1.8	{d2}, [r0:64], r2
vst1.8	{d3}, [r0:64], r2
bne	_ff_avg_pixels8_neon
bx	lr