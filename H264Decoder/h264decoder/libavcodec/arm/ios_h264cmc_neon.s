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
function ff_put_h264_chroma_mc8_neon
push	{r4, r5, r6, r7, lr}
ldrd	r4, r5, [sp, #20]
pld	[r1]
pld	[r1, r2]
mul	r7, r4, r5
cmp	r7, #0x0
rsb	r6, r7, r5, lsl #3
rsb	r12, r7, r4, lsl #3
sub.w	r4, r7, r4, lsl #3
sub.w	r4, r4, r5, lsl #3
add.w	r4, r4, #0x40
beq	2f
vdup.8	d0, r4
vdup.8	d1, r12
vld1.8	{d4, d5}, [r1], r2
vdup.8	d2, r6
vdup.8	d3, r7
vext.8	d5, d4, d5, #0x1
1:
vld1.8	{d6, d7}, [r1], r2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vext.8	d7, d6, d7, #0x1
vld1.8	{d4, d5}, [r1], r2
vmlal.u8	q8, d6, d2
pld	[r1]
vext.8	d5, d4, d5, #0x1
vmlal.u8	q8, d7, d3
vmull.u8	q9, d6, d0
subs	r3, #0x2
vmlal.u8	q9, d7, d1
vmlal.u8	q9, d4, d2
vmlal.u8	q9, d5, d3
pld	[r1, r2]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	1b
pop	{r4, r5, r6, r7, pc}
2:
tst	r6, r6
add	r12, r6
vdup.8	d0, r4
vdup.8	d1, r12
beq	4f
vld1.8	{d4}, [r1], r2
3:
vld1.8	{d6}, [r1], r2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d6, d1
vld1.8	{d4}, [r1], r2
vmull.u8	q9, d6, d0
vmlal.u8	q9, d4, d1
pld	[r1]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
pld	[r1, r2]
subs	r3, #0x2
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	3b
pop	{r4, r5, r6, r7, pc}
4:
vld1.8	{d4, d5}, [r1], r2
vld1.8	{d6, d7}, [r1], r2
vext.8	d5, d4, d5, #0x1
vext.8	d7, d6, d7, #0x1
pld	[r1]
subs	r3, #0x2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vmull.u8	q9, d6, d0
vmlal.u8	q9, d7, d1
pld	[r1, r2]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	4b
pop	{r4, r5, r6, r7, pc}

function ff_put_h264_chroma_mc4_neon
push	{r4, r5, r6, r7, lr}
ldrd	r4, r5, [sp, #20]
pld	[r1]
pld	[r1, r2]
mul	r7, r4, r5
cmp	r7, #0x0
rsb	r6, r7, r5, lsl #3
rsb	r12, r7, r4, lsl #3
sub.w	r4, r7, r4, lsl #3
sub.w	r4, r4, r5, lsl #3
add.w	r4, r4, #0x40
beq	2f
vdup.8	d0, r4
vdup.8	d1, r12
vld1.8	{d4}, [r1], r2
vdup.8	d2, r6
vdup.8	d3, r7
vext.8	d5, d4, d5, #0x1
vtrn.32	d4, d5
vtrn.32	d0, d1
vtrn.32	d2, d3
1:
vld1.8	{d6}, [r1], r2
vext.8	d7, d6, d7, #0x1
vtrn.32	d6, d7
vmull.u8	q8, d4, d0
vmlal.u8	q8, d6, d2
vld1.8	{d4}, [r1], r2
vext.8	d5, d4, d5, #0x1
vtrn.32	d4, d5
pld	[r1]
vmull.u8	q9, d6, d0
vmlal.u8	q9, d4, d2
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
vrshrn.i16	d16, q8, #0x6
subs	r3, #0x2
pld	[r1, r2]
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	1b
pop	{r4, r5, r6, r7, pc}
2:
tst	r6, r6
add	r12, r6
vdup.8	d0, r4
vdup.8	d1, r12
vtrn.32	d0, d1
beq	4f
vext.32	d1, d0, d1, #0x1
vld1.32	{d4[0]}, [r1], r2
3:
vld1.32	{d4[1]}, [r1], r2
vmull.u8	q8, d4, d0
vld1.32	{d4[0]}, [r1], r2
vmull.u8	q9, d4, d1
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
pld	[r1]
vrshrn.i16	d16, q8, #0x6
subs	r3, #0x2
pld	[r1, r2]
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	3b
pop	{r4, r5, r6, r7, pc}
4:
vld1.8	{d4}, [r1], r2
vld1.8	{d6}, [r1], r2
vext.8	d5, d4, d5, #0x1
vext.8	d7, d6, d7, #0x1
vtrn.32	d4, d5
vtrn.32	d6, d7
vmull.u8	q8, d4, d0
vmull.u8	q9, d6, d0
subs	r3, #0x2
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
pld	[r1]
vrshrn.i16	d16, q8, #0x6
pld	[r1]
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	4b
pop	{r4, r5, r6, r7, pc}


function ff_put_h264_chroma_mc2_neon
push	{r4, r5, r6, lr}
ldr	r4, [sp, #0x10]
ldr.w	lr, [sp, #20]
pld	[r1]
pld	[r1, r2]
orrs.w	r5, r4, lr
beq	2f
mul	r5, r4, lr
rsb	r6, r5, lr, lsl #3
rsb	r12, r5, r4, lsl #3
sub.w	r4, r5, r4, lsl #3
sub.w	r4, r4, lr, lsl #3
add.w	r4, r4, #0x40
vdup.8	d0, r4
vdup.8	d2, r12
vdup.8	d1, r6
vdup.8	d3, r5
vtrn.16	q0, q1
1:
vld1.32	{d4[0]}, [r1], r2
vld1.32	{d4[1]}, [r1], r2
vrev64.32	d5, d4
vld1.32	{d5[1]}, [r1]
vext.8	q3, q2, q2, #0x1
vtrn.16	q2, q3
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vtrn.32	d16, d17
vadd.i16	d16, d16, d17
vrshrn.i16	d16, q8, #0x6
vst1.16	{d16[0]}, [r0:16], r2
vst1.16	{d16[1]}, [r0:16], r2
subs	r3, #0x2
bgt	1b
pop	{r4, r5, r6, pc}
2:
ldrh	r5, [r1]
add	r1, r2
strh	r5, [r0]
add	r0, r2
ldrh	r6, [r1]
add	r1, r2
strh	r6, [r0]
add	r0, r2
subs	r3, #0x2
bgt	2b
pop	{r4, r5, r6, pc}


function ff_avg_h264_chroma_mc8_neon
push	{r4, r5, r6, r7, lr}
ldrd	r4, r5, [sp, #20]
mov	lr, r0
pld	[r1]
pld	[r1, r2]
mul	r7, r4, r5
cmp	r7, #0x0
rsb	r6, r7, r5, lsl #3
rsb	r12, r7, r4, lsl #3
sub.w	r4, r7, r4, lsl #3
sub.w	r4, r4, r5, lsl #3
add.w	r4, r4, #0x40
beq	2f
vdup.8	d0, r4
vdup.8	d1, r12
vld1.8	{d4, d5}, [r1], r2
vdup.8	d2, r6
vdup.8	d3, r7
vext.8	d5, d4, d5, #0x1
1:
vld1.8	{d6, d7}, [r1], r2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vext.8	d7, d6, d7, #0x1
vld1.8	{d4, d5}, [r1], r2
vmlal.u8	q8, d6, d2
pld	[r1]
vext.8	d5, d4, d5, #0x1
vmlal.u8	q8, d7, d3
vmull.u8	q9, d6, d0
subs	r3, #0x2
vmlal.u8	q9, d7, d1
vmlal.u8	q9, d4, d2
vmlal.u8	q9, d5, d3
pld	[r1, r2]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
vld1.8	{d20}, [lr:64], r2
vld1.8	{d21}, [lr:64], r2
vrhadd.u8	q8, q8, q10
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	1b
pop	{r4, r5, r6, r7, pc}
2:
tst	r6, r6
add	r12, r6
vdup.8	d0, r4
vdup.8	d1, r12
beq	4f
vld1.8	{d4}, [r1], r2
3:
vld1.8	{d6}, [r1], r2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d6, d1
vld1.8	{d4}, [r1], r2
vmull.u8	q9, d6, d0
vmlal.u8	q9, d4, d1
pld	[r1]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
pld	[r1, r2]
vld1.8	{d20}, [lr:64], r2
vld1.8	{d21}, [lr:64], r2
vrhadd.u8	q8, q8, q10
subs	r3, #0x2
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	3b
pop	{r4, r5, r6, r7, pc}
4:
vld1.8	{d4, d5}, [r1], r2
vld1.8	{d6, d7}, [r1], r2
vext.8	d5, d4, d5, #0x1
vext.8	d7, d6, d7, #0x1
pld	[r1]
subs	r3, #0x2
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vmull.u8	q9, d6, d0
vmlal.u8	q9, d7, d1
pld	[r1, r2]
vrshrn.i16	d16, q8, #0x6
vrshrn.i16	d17, q9, #0x6
vld1.8	{d20}, [lr:64], r2
vld1.8	{d21}, [lr:64], r2
vrhadd.u8	q8, q8, q10
vst1.8	{d16}, [r0:64], r2
vst1.8	{d17}, [r0:64], r2
bgt	4b
pop	{r4, r5, r6, r7, pc}

function ff_avg_h264_chroma_mc4_neon
push	{r4, r5, r6, r7, lr}
ldrd	r4, r5, [sp, #20]
mov	lr, r0
pld	[r1]
pld	[r1, r2]
mul	r7, r4, r5
cmp	r7, #0x0
rsb	r6, r7, r5, lsl #3
rsb	r12, r7, r4, lsl #3
sub.w	r4, r7, r4, lsl #3
sub.w	r4, r4, r5, lsl #3
add.w	r4, r4, #0x40
beq	2f
vdup.8	d0, r4
vdup.8	d1, r12
vld1.8	{d4}, [r1], r2
vdup.8	d2, r6
vdup.8	d3, r7
vext.8	d5, d4, d5, #0x1
vtrn.32	d4, d5
vtrn.32	d0, d1
vtrn.32	d2, d3
1:
vld1.8	{d6}, [r1], r2
vext.8	d7, d6, d7, #0x1
vtrn.32	d6, d7
vmull.u8	q8, d4, d0
vmlal.u8	q8, d6, d2
vld1.8	{d4}, [r1], r2
vext.8	d5, d4, d5, #0x1
vtrn.32	d4, d5
pld	[r1]
vmull.u8	q9, d6, d0
vmlal.u8	q9, d4, d2
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
vrshrn.i16	d16, q8, #0x6
subs	r3, #0x2
pld	[r1, r2]
vld1.32	{d20[0]}, [lr:32], r2
vld1.32	{d20[1]}, [lr:32], r2
vrhadd.u8	d16, d16, d20
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	1b
pop	{r4, r5, r6, r7, pc}
2:
tst	r6, r6
add	r12, r6
vdup.8	d0, r4
vdup.8	d1, r12
vtrn.32	d0, d1
beq	4f
vext.32	d1, d0, d1, #0x1
vld1.32	{d4[0]}, [r1], r2
3:
vld1.32	{d4[1]}, [r1], r2
vmull.u8	q8, d4, d0
vld1.32	{d4[0]}, [r1], r2
vmull.u8	q9, d4, d1
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
pld	[r1]
vrshrn.i16	d16, q8, #0x6
vld1.32	{d20[0]}, [lr:32], r2
vld1.32	{d20[1]}, [lr:32], r2
vrhadd.u8	d16, d16, d20
subs	r3, #0x2
pld	[r1, r2]
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	3b
pop	{r4, r5, r6, r7, pc}
4:
vld1.8	{d4}, [r1], r2
vld1.8	{d6}, [r1], r2
vext.8	d5, d4, d5, #0x1
vext.8	d7, d6, d7, #0x1
vtrn.32	d4, d5
vtrn.32	d6, d7
vmull.u8	q8, d4, d0
vmull.u8	q9, d6, d0
subs	r3, #0x2
vadd.i16	d16, d16, d17
vadd.i16	d17, d18, d19
pld	[r1]
vrshrn.i16	d16, q8, #0x6
vld1.32	{d20[0]}, [lr:32], r2
vld1.32	{d20[1]}, [lr:32], r2
vrhadd.u8	d16, d16, d20
pld	[r1]
vst1.32	{d16[0]}, [r0:32], r2
vst1.32	{d16[1]}, [r0:32], r2
bgt	4b
pop	{r4, r5, r6, r7, pc}


function ff_avg_h264_chroma_mc2_neon
push	{r4, r5, r6, lr}
ldr	r4, [sp, #0x10]
ldr.w	lr, [sp, #20]
pld	[r1]
pld	[r1, r2]
orrs.w	r5, r4, lr
beq	2f
mul	r5, r4, lr
rsb	r6, r5, lr, lsl #3
rsb	r12, r5, r4, lsl #3
sub.w	r4, r5, r4, lsl #3
sub.w	r4, r4, lr, lsl #3
add.w	r4, r4, #0x40
vdup.8	d0, r4
vdup.8	d2, r12
vdup.8	d1, r6
vdup.8	d3, r5
vtrn.16	q0, q1
1:
vld1.32	{d4[0]}, [r1], r2
vld1.32	{d4[1]}, [r1], r2
vrev64.32	d5, d4
vld1.32	{d5[1]}, [r1]
vext.8	q3, q2, q2, #0x1
vtrn.16	q2, q3
vmull.u8	q8, d4, d0
vmlal.u8	q8, d5, d1
vld1.16	{d18[0]}, [r0:16], r2
vld1.16	{d18[1]}, [r0:16]
sub.w	r0, r0, r2
vtrn.32	d16, d17
vadd.i16	d16, d16, d17
vrshrn.i16	d16, q8, #0x6
vrhadd.u8	d16, d16, d18
vst1.16	{d16[0]}, [r0:16], r2
vst1.16	{d16[1]}, [r0:16], r2
subs	r3, #0x2
bgt	1b
pop	{r4, r5, r6, pc}
2:
vld1.16	{d16[0]}, [r1], r2
vld1.16	{d16[1]}, [r1], r2
vld1.16	{d18[0]}, [r0:16], r2
vld1.16	{d18[1]}, [r0:16]
sub.w	r0, r0, r2
vrhadd.u8	d16, d16, d18
vst1.16	{d16[0]}, [r0:16], r2
vst1.16	{d16[1]}, [r0:16], r2
subs	r3, #0x2
bgt	2b
pop	{r4, r5, r6, pc}


