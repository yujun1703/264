//
//  Created by landyji on 20140605.
//  Copyright (c) 2013å¹?com.tencent.avteam. All rights reserved.
//

.macro function name
.global _\name
.align 2
_\name:
.endm

.text
function ff_h264_v_loop_filter_luma_neon
ldr.w	r12, [sp]
tst	r2, r2
ldr.w	r12, [r12]
it	ne
tstne.w	r3, r3
vmov.32	d24[0], r12
and.w	r12, r12, r12, lsl #16
it	eq
bxeq	lr
ands.w	r12, r12, r12, lsl #8
it	lt
bxlt	lr
vld1.8	{d0, d1}, [r0:128], r1
vld1.8	{d2, d3}, [r0:128], r1
vld1.8	{d4, d5}, [r0:128], r1
sub.w	r0, r0, r1, lsl #2
sub.w	r0, r0, r1, lsl #1
vld1.8	{d20, d21}, [r0:128], r1
vld1.8	{d18, d19}, [r0:128], r1
vld1.8	{d16, d17}, [r0:128], r1
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
vdup.8	q11, r2
vmovl.u8	q12, d24
vabd.u8	q6, q8, q0
vmovl.u16	q12, d24
vabd.u8	q14, q9, q8
vsli.16	q12, q12, #0x8
vabd.u8	q15, q1, q0
vsli.32	q12, q12, #0x10
vcgt.u8	q6, q11, q6
vdup.8	q11, r3
vclt.s8	q7, q12, #0
vcgt.u8	q14, q11, q14
vcgt.u8	q15, q11, q15
vbic	q6, q6, q7
vabd.u8	q4, q10, q8
vand	q6, q6, q14
vabd.u8	q5, q2, q0
vcgt.u8	q4, q11, q4
vand	q6, q6, q15
vcgt.u8	q5, q11, q5
vand	q4, q4, q6
vand	q5, q5, q6
vand	q12, q12, q6
vrhadd.u8	q14, q8, q0
vsub.i8	q6, q12, q4
vqadd.u8	q7, q9, q12
vhadd.u8	q10, q10, q14
vsub.i8	q6, q6, q5
vhadd.u8	q14, q2, q14
vmin.u8	q7, q7, q10
vqsub.u8	q11, q9, q12
vqadd.u8	q2, q1, q12
vmax.u8	q7, q7, q11
vqsub.u8	q11, q1, q12
vmin.u8	q14, q2, q14
vmovl.u8	q2, d0
vmax.u8	q14, q14, q11
vmovl.u8	q10, d1
vsubw.u8	q2, q2, d16
vsubw.u8	q10, q10, d17
vshl.i16	q2, q2, #0x2
vshl.i16	q10, q10, #0x2
vaddw.u8	q2, q2, d18
vaddw.u8	q10, q10, d19
vsubw.u8	q2, q2, d2
vsubw.u8	q10, q10, d3
vrshrn.i16	d4, q2, #0x3
vrshrn.i16	d5, q10, #0x3
vbsl	q4, q7, q9
vbsl	q5, q14, q1
vneg.s8	q7, q6
vmovl.u8	q14, d16
vmin.s8	q2, q2, q6
vmovl.u8	q6, d17
vmax.s8	q2, q2, q7
vmovl.u8	q11, d0
vmovl.u8	q12, d1
vaddw.s8	q14, q14, d4
vaddw.s8	q6, q6, d5
vsubw.s8	q11, q11, d4
vsubw.s8	q12, q12, d5
vqmovun.s16	d16, q14
vqmovun.s16	d17, q6
vqmovun.s16	d0, q11
vqmovun.s16	d1, q12
sub.w	r0, r0, r1, lsl #1
vst1.8	{d8, d9}, [r0:128], r1
vst1.8	{d16, d17}, [r0:128], r1
vst1.8	{d0, d1}, [r0:128], r1
vst1.8	{d10, d11}, [r0:128]
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
bx	lr


function ff_h264_h_loop_filter_luma_neon
ldr.w	r12, [sp]
tst	r2, r2
ldr.w	r12, [r12]
it	ne
tstne.w	r3, r3
vmov.32	d24[0], r12
and.w	r12, r12, r12, lsl #16
it	eq
bxeq	lr
ands.w	r12, r12, r12, lsl #8
it	lt
bxlt	lr
sub.w	r0, r0, #0x4
vld1.8	{d6}, [r0], r1
vld1.8	{d20}, [r0], r1
vld1.8	{d18}, [r0], r1
vld1.8	{d16}, [r0], r1
vld1.8	{d0}, [r0], r1
vld1.8	{d2}, [r0], r1
vld1.8	{d4}, [r0], r1
vld1.8	{d26}, [r0], r1
vld1.8	{d7}, [r0], r1
vld1.8	{d21}, [r0], r1
vld1.8	{d19}, [r0], r1
vld1.8	{d17}, [r0], r1
vld1.8	{d1}, [r0], r1
vld1.8	{d3}, [r0], r1
vld1.8	{d5}, [r0], r1
vld1.8	{d27}, [r0], r1
vtrn.32	q3, q0
vtrn.32	q10, q1
vtrn.32	q9, q2
vtrn.32	q8, q13
vtrn.16	q3, q9
vtrn.16	q10, q8
vtrn.16	q0, q2
vtrn.16	q1, q13
vtrn.8	q3, q10
vtrn.8	q9, q8
vtrn.8	q0, q1
vtrn.8	q2, q13
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
vdup.8	q11, r2
vmovl.u8	q12, d24
vabd.u8	q6, q8, q0
vmovl.u16	q12, d24
vabd.u8	q14, q9, q8
vsli.16	q12, q12, #0x8
vabd.u8	q15, q1, q0
vsli.32	q12, q12, #0x10
vcgt.u8	q6, q11, q6
vdup.8	q11, r3
vclt.s8	q7, q12, #0
vcgt.u8	q14, q11, q14
vcgt.u8	q15, q11, q15
vbic	q6, q6, q7
vabd.u8	q4, q10, q8
vand	q6, q6, q14
vabd.u8	q5, q2, q0
vcgt.u8	q4, q11, q4
vand	q6, q6, q15
vcgt.u8	q5, q11, q5
vand	q4, q4, q6
vand	q5, q5, q6
vand	q12, q12, q6
vrhadd.u8	q14, q8, q0
vsub.i8	q6, q12, q4
vqadd.u8	q7, q9, q12
vhadd.u8	q10, q10, q14
vsub.i8	q6, q6, q5
vhadd.u8	q14, q2, q14
vmin.u8	q7, q7, q10
vqsub.u8	q11, q9, q12
vqadd.u8	q2, q1, q12
vmax.u8	q7, q7, q11
vqsub.u8	q11, q1, q12
vmin.u8	q14, q2, q14
vmovl.u8	q2, d0
vmax.u8	q14, q14, q11
vmovl.u8	q10, d1
vsubw.u8	q2, q2, d16
vsubw.u8	q10, q10, d17
vshl.i16	q2, q2, #0x2
vshl.i16	q10, q10, #0x2
vaddw.u8	q2, q2, d18
vaddw.u8	q10, q10, d19
vsubw.u8	q2, q2, d2
vsubw.u8	q10, q10, d3
vrshrn.i16	d4, q2, #0x3
vrshrn.i16	d5, q10, #0x3
vbsl	q4, q7, q9
vbsl	q5, q14, q1
vneg.s8	q7, q6
vmovl.u8	q14, d16
vmin.s8	q2, q2, q6
vmovl.u8	q6, d17
vmax.s8	q2, q2, q7
vmovl.u8	q11, d0
vmovl.u8	q12, d1
vaddw.s8	q14, q14, d4
vaddw.s8	q6, q6, d5
vsubw.s8	q11, q11, d4
vsubw.s8	q12, q12, d5
vqmovun.s16	d16, q14
vqmovun.s16	d17, q6
vqmovun.s16	d0, q11
vqmovun.s16	d1, q12
vtrn.16	q4, q0
vtrn.16	q8, q5
vtrn.8	q4, q8
vtrn.8	q0, q5
sub.w	r0, r0, r1, lsl #4
add.w	r0, r0, #0x2
vst1.32	{d8[0]}, [r0], r1
vst1.32	{d16[0]}, [r0], r1
vst1.32	{d0[0]}, [r0], r1
vst1.32	{d10[0]}, [r0], r1
vst1.32	{d8[1]}, [r0], r1
vst1.32	{d16[1]}, [r0], r1
vst1.32	{d0[1]}, [r0], r1
vst1.32	{d10[1]}, [r0], r1
vst1.32	{d9[0]}, [r0], r1
vst1.32	{d17[0]}, [r0], r1
vst1.32	{d1[0]}, [r0], r1
vst1.32	{d11[0]}, [r0], r1
vst1.32	{d9[1]}, [r0], r1
vst1.32	{d17[1]}, [r0], r1
vst1.32	{d1[1]}, [r0], r1
vst1.32	{d11[1]}, [r0], r1
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
bx	lr

function ff_h264_v_loop_filter_chroma_neon
ldr.w	r12, [sp]
tst	r2, r2
ldr.w	r12, [r12]
it	ne
tstne.w	r3, r3
vmov.32	d24[0], r12
and.w	r12, r12, r12, lsl #16
it	eq
bxeq	lr
ands.w	r12, r12, r12, lsl #8
it	lt
bxlt	lr
sub.w	r0, r0, r1, lsl #1
vld1.8	{d18}, [r0:64], r1
vld1.8	{d16}, [r0:64], r1
vld1.8	{d0}, [r0:64], r1
vld1.8	{d2}, [r0:64]
vdup.8	d22, r2
vmovl.u8	q12, d24
vabd.u8	d26, d16, d0
vmovl.u8	q2, d0
vabd.u8	d28, d18, d16
vsubw.u8	q2, q2, d16
vsli.16	d24, d24, #0x8
vshl.i16	q2, q2, #0x2
vabd.u8	d30, d2, d0
vaddw.u8	q2, q2, d18
vcgt.u8	d26, d22, d26
vsubw.u8	q2, q2, d2
vdup.8	d22, r3
vrshrn.i16	d4, q2, #0x3
vcgt.u8	d28, d22, d28
vcgt.u8	d30, d22, d30
vmin.s8	d4, d4, d24
vneg.s8	d25, d24
vand	d26, d26, d28
vmax.s8	d4, d4, d25
vand	d26, d26, d30
vmovl.u8	q11, d0
vand	d4, d4, d26
vmovl.u8	q14, d16
vaddw.s8	q14, q14, d4
vsubw.s8	q11, q11, d4
vqmovun.s16	d16, q14
vqmovun.s16	d0, q11
sub.w	r0, r0, r1, lsl #1
vst1.8	{d16}, [r0:64], r1
vst1.8	{d0}, [r0:64], r1
bx	lr


function ff_h264_h_loop_filter_chroma_neon
ldr.w	r12, [sp]
tst	r2, r2
ldr.w	r12, [r12]
it	ne
tstne.w	r3, r3
vmov.32	d24[0], r12
and.w	r12, r12, r12, lsl #16
it	eq
bxeq	lr
ands.w	r12, r12, r12, lsl #8
it	lt
bxlt	lr
sub.w	r0, r0, #0x2
vld1.32	{d18[0]}, [r0], r1
vld1.32	{d16[0]}, [r0], r1
vld1.32	{d0[0]}, [r0], r1
vld1.32	{d2[0]}, [r0], r1
vld1.32	{d18[1]}, [r0], r1
vld1.32	{d16[1]}, [r0], r1
vld1.32	{d0[1]}, [r0], r1
vld1.32	{d2[1]}, [r0], r1
vtrn.16	d18, d0
vtrn.16	d16, d2
vtrn.8	d18, d16
vtrn.8	d0, d2
vdup.8	d22, r2
vmovl.u8	q12, d24
vabd.u8	d26, d16, d0
vmovl.u8	q2, d0
vabd.u8	d28, d18, d16
vsubw.u8	q2, q2, d16
vsli.16	d24, d24, #0x8
vshl.i16	q2, q2, #0x2
vabd.u8	d30, d2, d0
vaddw.u8	q2, q2, d18
vcgt.u8	d26, d22, d26
vsubw.u8	q2, q2, d2
vdup.8	d22, r3
vrshrn.i16	d4, q2, #0x3
vcgt.u8	d28, d22, d28
vcgt.u8	d30, d22, d30
vmin.s8	d4, d4, d24
vneg.s8	d25, d24
vand	d26, d26, d28
vmax.s8	d4, d4, d25
vand	d26, d26, d30
vmovl.u8	q11, d0
vand	d4, d4, d26
vmovl.u8	q14, d16
vaddw.s8	q14, q14, d4
vsubw.s8	q11, q11, d4
vqmovun.s16	d16, q14
vqmovun.s16	d0, q11
vtrn.16	d18, d0
vtrn.16	d16, d2
vtrn.8	d18, d16
vtrn.8	d0, d2
sub.w	r0, r0, r1, lsl #3
vst1.32	{d18[0]}, [r0], r1
vst1.32	{d16[0]}, [r0], r1
vst1.32	{d0[0]}, [r0], r1
vst1.32	{d2[0]}, [r0], r1
vst1.32	{d18[1]}, [r0], r1
vst1.32	{d16[1]}, [r0], r1
vst1.32	{d0[1]}, [r0], r1
vst1.32	{d2[1]}, [r0], r1
bx	lr


function ff_weight_h264_pixels_16_neon
push	{r4, lr}
ldr.w	r12, [sp, #8]
ldr	r4, [sp, #0xc]
cmp	r3, #0x1
lsl.w	r4, r4, r3
vdup.16	q8, r4
mov	r4, r0
ble	20f
rsb.w	lr, r3, #0x1
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d20, d21}, [r0:128], r1
vmull.u8	q2, d0, d20
pld	[r0]
vmull.u8	q3, d0, d21
vld1.8	{d28, d29}, [r0:128], r1
vmull.u8	q12, d0, d28
pld	[r0]
vmull.u8	q13, d0, d29
vhadd.s16	q2, q8, q2
vrshl.s16	q2, q2, q9
vhadd.s16	q3, q8, q3
vrshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vhadd.s16	q12, q8, q12
vrshl.s16	q12, q12, q9
vhadd.s16	q13, q8, q13
vrshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vst1.8	{d4, d5}, [r4:128], r1
vst1.8	{d24, d25}, [r4:128], r1
bne	1b
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d20, d21}, [r0:128], r1
vmull.u8	q2, d0, d20
pld	[r0]
vmull.u8	q3, d0, d21
vld1.8	{d28, d29}, [r0:128], r1
vmull.u8	q12, d0, d28
pld	[r0]
vmull.u8	q13, d0, d29
vhsub.s16	q2, q8, q2
vrshl.s16	q2, q2, q9
vhsub.s16	q3, q8, q3
vrshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vhsub.s16	q12, q8, q12
vrshl.s16	q12, q12, q9
vhsub.s16	q13, q8, q13
vrshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vst1.8	{d4, d5}, [r4:128], r1
vst1.8	{d24, d25}, [r4:128], r1
bne	1b
pop	{r4, pc}
20:
rsb.w	lr, r3, #0x0
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d20, d21}, [r0:128], r1
vmull.u8	q2, d0, d20
pld	[r0]
vmull.u8	q3, d0, d21
vld1.8	{d28, d29}, [r0:128], r1
vmull.u8	q12, d0, d28
pld	[r0]
vmull.u8	q13, d0, d29
vadd.i16	q2, q8, q2
vrshl.s16	q2, q2, q9
vadd.i16	q3, q8, q3
vrshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vadd.i16	q12, q8, q12
vrshl.s16	q12, q12, q9
vadd.i16	q13, q8, q13
vrshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vst1.8	{d4, d5}, [r4:128], r1
vst1.8	{d24, d25}, [r4:128], r1
bne	1b
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d20, d21}, [r0:128], r1
vmull.u8	q2, d0, d20
pld	[r0]
vmull.u8	q3, d0, d21
vld1.8	{d28, d29}, [r0:128], r1
vmull.u8	q12, d0, d28
pld	[r0]
vmull.u8	q13, d0, d29
vsub.i16	q2, q8, q2
vrshl.s16	q2, q2, q9
vsub.i16	q3, q8, q3
vrshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vsub.i16	q12, q8, q12
vrshl.s16	q12, q12, q9
vsub.i16	q13, q8, q13
vrshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vst1.8	{d4, d5}, [r4:128], r1
vst1.8	{d24, d25}, [r4:128], r1
bne	1b
pop	{r4, pc}


function ff_weight_h264_pixels_8_neon
push	{r4, lr}
ldr.w	r12, [sp, #8]
ldr	r4, [sp, #0xc]
cmp	r3, #0x1
lsl.w	r4, r4, r3
vdup.16	q8, r4
mov	r4, r0
ble	20f
rsb.w	lr, r3, #0x1
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d4}, [r0:64], r1
vmull.u8	q1, d0, d4
pld	[r0]
vld1.8	{d6}, [r0:64], r1
vmull.u8	q10, d0, d6
vhadd.s16	q1, q8, q1
pld	[r0]
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vhadd.s16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vst1.8	{d2}, [r4:64], r1
vst1.8	{d4}, [r4:64], r1
bne	1b
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d4}, [r0:64], r1
vmull.u8	q1, d0, d4
pld	[r0]
vld1.8	{d6}, [r0:64], r1
vmull.u8	q10, d0, d6
vhsub.s16	q1, q8, q1
pld	[r0]
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vhsub.s16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vst1.8	{d2}, [r4:64], r1
vst1.8	{d4}, [r4:64], r1
bne	1b
pop	{r4, pc}
20:
rsb.w	lr, r3, #0x0
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d4}, [r0:64], r1
vmull.u8	q1, d0, d4
pld	[r0]
vld1.8	{d6}, [r0:64], r1
vmull.u8	q10, d0, d6
vadd.i16	q1, q8, q1
pld	[r0]
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vadd.i16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vst1.8	{d2}, [r4:64], r1
vst1.8	{d4}, [r4:64], r1
bne	1b
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
1:
subs	r2, #0x2
vld1.8	{d4}, [r0:64], r1
vmull.u8	q1, d0, d4
pld	[r0]
vld1.8	{d6}, [r0:64], r1
vmull.u8	q10, d0, d6
vsub.i16	q1, q8, q1
pld	[r0]
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vsub.i16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vst1.8	{d2}, [r4:64], r1
vst1.8	{d4}, [r4:64], r1
bne	1b
pop	{r4, pc}


function ff_weight_h264_pixels_4_neon
push	{r4, lr}
ldr.w	r12, [sp, #8]
ldr	r4, [sp, #0xc]
cmp	r3, #0x1
lsl.w	r4, r4, r3
vdup.16	q8, r4
mov	r4, r0
ble.w	20f
rsb.w	lr, r3, #0x1
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r2, #0x4
vld1.32	{d4[0]}, [r0:32], r1
vld1.32	{d4[1]}, [r0:32], r1
vmull.u8	q1, d0, d4
pld	[r0]
blt	2f
vld1.32	{d6[0]}, [r0:32], r1
vld1.32	{d6[1]}, [r0:32], r1
vmull.u8	q10, d0, d6
pld	[r0]
vhadd.s16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vhadd.s16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r4:32], r1
vst1.32	{d4[1]}, [r4:32], r1
bne	1b
pop	{r4, pc}
2:
vhadd.s16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r2, #0x4
vld1.32	{d4[0]}, [r0:32], r1
vld1.32	{d4[1]}, [r0:32], r1
vmull.u8	q1, d0, d4
pld	[r0]
blt	2f
vld1.32	{d6[0]}, [r0:32], r1
vld1.32	{d6[1]}, [r0:32], r1
vmull.u8	q10, d0, d6
pld	[r0]
vhsub.s16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vhsub.s16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r4:32], r1
vst1.32	{d4[1]}, [r4:32], r1
bne	1b
pop	{r4, pc}
2:
vhsub.s16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
pop	{r4, pc}
20:
rsb.w	lr, r3, #0x0
vdup.16	q9, lr
cmp.w	r12, #0x0
blt	10f
vdup.8	d0, r12
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r2, #0x4
vld1.32	{d4[0]}, [r0:32], r1
vld1.32	{d4[1]}, [r0:32], r1
vmull.u8	q1, d0, d4
pld	[r0]
blt	2f
vld1.32	{d6[0]}, [r0:32], r1
vld1.32	{d6[1]}, [r0:32], r1
vmull.u8	q10, d0, d6
pld	[r0]
vadd.i16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vadd.i16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r4:32], r1
vst1.32	{d4[1]}, [r4:32], r1
bne	1b
pop	{r4, pc}
2:
vadd.i16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
pop	{r4, pc}
10:
rsb.w	r12, r12, #0x0
vdup.8	d0, r12
vorr	q1, q8, q8
vorr	q10, q8, q8
subs	r2, #0x4
vld1.32	{d4[0]}, [r0:32], r1
vld1.32	{d4[1]}, [r0:32], r1
vmull.u8	q1, d0, d4
pld	[r0]
blt	0x113a
vld1.32	{d6[0]}, [r0:32], r1
vld1.32	{d6[1]}, [r0:32], r1
vmull.u8	q10, d0, d6
pld	[r0]
vsub.i16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vsub.i16	q10, q8, q10
vrshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r4:32], r1
vst1.32	{d4[1]}, [r4:32], r1
bne	0x10e2
pop	{r4, pc}
vsub.i16	q1, q8, q1
vrshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r4:32], r1
vst1.32	{d2[1]}, [r4:32], r1
pop	{r4, pc}


function ff_biweight_h264_pixels_16_neon
push	{r4, r5, r6, lr}
ldr.w	r12, [sp, #16]
add	r4, sp, #0x14
ldm	r4, {r4, r5, r6}
lsr.w	lr, r4, #0x1f
add.w	r6, r6, #0x1
eors.w	lr, lr, r5, lsr #30
orr	r6, r6, #0x1
vdup.16	q9, r12
lsl.w	r6, r6, r12
vmvn	q9, q9
vdup.16	q8, r6
mov	r6, r0
beq	10f
subs.w	lr, lr, #0x1
beq	20f
subs.w	lr, lr, #0x1
beq.w	30f
b	40f
10:
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q2, q8, q8
vorr	q3, q8, q8
1:
subs	r3, #0x2
vld1.8	{d20, d21}, [r0:128], r2
vmlal.u8	q2, d0, d20
pld	[r0]
vmlal.u8	q3, d0, d21
vld1.8	{d22, d23}, [r1:128], r2
vmlal.u8	q2, d1, d22
pld	[r1]
vmlal.u8	q3, d1, d23
vorr	q12, q8, q8
vld1.8	{d28, d29}, [r0:128], r2
vorr	q13, q8, q8
vmlal.u8	q12, d0, d28
pld	[r0]
vmlal.u8	q13, d0, d29
vld1.8	{d30, d31}, [r1:128], r2
vmlal.u8	q12, d1, d30
pld	[r1]
vmlal.u8	q13, d1, d31
vshl.s16	q2, q2, q9
vshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vshl.s16	q12, q12, q9
vshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vorr	q3, q8, q8
vst1.8	{d4, d5}, [r6:128], r2
vorr	q2, q8, q8
vst1.8	{d24, d25}, [r6:128], r2
bne	1b
pop	{r4, r5, r6, pc}
20:
rsb.w	r4, r4, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q2, q8, q8
vorr	q3, q8, q8
1:
subs	r3, #0x2
vld1.8	{d20, d21}, [r0:128], r2
vmlsl.u8	q2, d0, d20
pld	[r0]
vmlsl.u8	q3, d0, d21
vld1.8	{d22, d23}, [r1:128], r2
vmlal.u8	q2, d1, d22
pld	[r1]
vmlal.u8	q3, d1, d23
vorr	q12, q8, q8
vld1.8	{d28, d29}, [r0:128], r2
vorr	q13, q8, q8
vmlsl.u8	q12, d0, d28
pld	[r0]
vmlsl.u8	q13, d0, d29
vld1.8	{d30, d31}, [r1:128], r2
vmlal.u8	q12, d1, d30
pld	[r1]
vmlal.u8	q13, d1, d31
vshl.s16	q2, q2, q9
vshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vshl.s16	q12, q12, q9
vshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vorr	q3, q8, q8
vst1.8	{d4, d5}, [r6:128], r2
vorr	q2, q8, q8
vst1.8	{d24, d25}, [r6:128], r2
bne	1b
pop	{r4, r5, r6, pc}
30:
rsb.w	r4, r4, #0x0
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q2, q8, q8
vorr	q3, q8, q8
1:
subs	r3, #0x2
vld1.8	{d20, d21}, [r0:128], r2
vmlsl.u8	q2, d0, d20
pld	[r0]
vmlsl.u8	q3, d0, d21
vld1.8	{d22, d23}, [r1:128], r2
vmlsl.u8	q2, d1, d22
pld	[r1]
vmlsl.u8	q3, d1, d23
vorr	q12, q8, q8
vld1.8	{d28, d29}, [r0:128], r2
vorr	q13, q8, q8
vmlsl.u8	q12, d0, d28
pld	[r0]
vmlsl.u8	q13, d0, d29
vld1.8	{d30, d31}, [r1:128], r2
vmlsl.u8	q12, d1, d30
pld	[r1]
vmlsl.u8	q13, d1, d31
vshl.s16	q2, q2, q9
vshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vshl.s16	q12, q12, q9
vshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vorr	q3, q8, q8
vst1.8	{d4, d5}, [r6:128], r2
vorr	q2, q8, q8
vst1.8	{d24, d25}, [r6:128], r2
bne	1b
pop	{r4, r5, r6, pc}
40:
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q2, q8, q8
vorr	q3, q8, q8
1:
subs	r3, #0x2
vld1.8	{d20, d21}, [r0:128], r2
vmlal.u8	q2, d0, d20
pld	[r0]
vmlal.u8	q3, d0, d21
vld1.8	{d22, d23}, [r1:128], r2
vmlsl.u8	q2, d1, d22
pld	[r1]
vmlsl.u8	q3, d1, d23
vorr	q12, q8, q8
vld1.8	{d28, d29}, [r0:128], r2
vorr	q13, q8, q8
vmlal.u8	q12, d0, d28
pld	[r0]
vmlal.u8	q13, d0, d29
vld1.8	{d30, d31}, [r1:128], r2
vmlsl.u8	q12, d1, d30
pld	[r1]
vmlsl.u8	q13, d1, d31
vshl.s16	q2, q2, q9
vshl.s16	q3, q3, q9
vqmovun.s16	d4, q2
vqmovun.s16	d5, q3
vshl.s16	q12, q12, q9
vshl.s16	q13, q13, q9
vqmovun.s16	d24, q12
vqmovun.s16	d25, q13
vorr	q3, q8, q8
vst1.8	{d4, d5}, [r6:128], r2
vorr	q2, q8, q8
vst1.8	{d24, d25}, [r6:128], r2
bne	1b
pop	{r4, r5, r6, pc}


function ff_biweight_h264_pixels_8_neon
push	{r4, r5, r6, lr}
ldr.w	r12, [sp, #16]
add	r4, sp, #0x14
ldm	r4, {r4, r5, r6}
lsr.w	lr, r4, #0x1f
add.w	r6, r6, #0x1
eors.w	lr, lr, r5, lsr #30
orr	r6, r6, #0x1
vdup.16	q9, r12
lsl.w	r6, r6, r12
vmvn	q9, q9
vdup.16	q8, r6
mov	r6, r0
beq	10f
subs.w	lr, lr, #0x1
beq	20f
subs.w	lr, lr, #0x1
beq	30f
b	40f
10:
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x2
vld1.8	{d4}, [r0:64], r2
vmlal.u8	q1, d0, d4
pld	[r0]
vld1.8	{d5}, [r1:64], r2
vmlal.u8	q1, d1, d5
pld	[r1]
vld1.8	{d6}, [r0:64], r2
vmlal.u8	q10, d0, d6
pld	[r0]
vld1.8	{d7}, [r1:64], r2
vmlal.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.8	{d2}, [r6:64], r2
vorr	q1, q8, q8
vst1.8	{d4}, [r6:64], r2
bne	1b
pop	{r4, r5, r6, pc}
20:
rsb.w	r4, r4, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x2
vld1.8	{d4}, [r0:64], r2
vmlsl.u8	q1, d0, d4
pld	[r0]
vld1.8	{d5}, [r1:64], r2
vmlal.u8	q1, d1, d5
pld	[r1]
vld1.8	{d6}, [r0:64], r2
vmlsl.u8	q10, d0, d6
pld	[r0]
vld1.8	{d7}, [r1:64], r2
vmlal.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.8	{d2}, [r6:64], r2
vorr	q1, q8, q8
vst1.8	{d4}, [r6:64], r2
bne	1b
pop	{r4, r5, r6, pc}
30:
rsb.w	r4, r4, #0x0
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x2
vld1.8	{d4}, [r0:64], r2
vmlsl.u8	q1, d0, d4
pld	[r0]
vld1.8	{d5}, [r1:64], r2
vmlsl.u8	q1, d1, d5
pld	[r1]
vld1.8	{d6}, [r0:64], r2
vmlsl.u8	q10, d0, d6
pld	[r0]
vld1.8	{d7}, [r1:64], r2
vmlsl.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.8	{d2}, [r6:64], r2
vorr	q1, q8, q8
vst1.8	{d4}, [r6:64], r2
bne	1b
pop	{r4, r5, r6, pc}
40:
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x2
vld1.8	{d4}, [r0:64], r2
vmlal.u8	q1, d0, d4
pld	[r0]
vld1.8	{d5}, [r1:64], r2
vmlsl.u8	q1, d1, d5
pld	[r1]
vld1.8	{d6}, [r0:64], r2
vmlal.u8	q10, d0, d6
pld	[r0]
vld1.8	{d7}, [r1:64], r2
vmlsl.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.8	{d2}, [r6:64], r2
vorr	q1, q8, q8
vst1.8	{d4}, [r6:64], r2
bne	1b
pop	{r4, r5, r6, pc}


function ff_biweight_h264_pixels_4_neon
push	{r4, r5, r6, lr}
ldr.w	r12, [sp, #16]
add	r4, sp, #0x14
ldm	r4, {r4, r5, r6}
lsr.w	lr, r4, #0x1f
add.w	r6, r6, #0x1
eors.w	lr, lr, r5, lsr #30
orr	r6, r6, #0x1
vdup.16	q9, r12
lsl.w	r6, r6, r12
vmvn	q9, q9
vdup.16	q8, r6
mov	r6, r0
beq	10f
subs.w	lr, lr, #0x1
beq	20f
subs.w	lr, lr, #0x1
beq.w	30f
b	40f
10:
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x4
vld1.32	{d4[0]}, [r0:32], r2
vld1.32	{d4[1]}, [r0:32], r2
vmlal.u8	q1, d0, d4
pld	[r0]
vld1.32	{d5[0]}, [r1:32], r2
vld1.32	{d5[1]}, [r1:32], r2
vmlal.u8	q1, d1, d5
pld	[r1]
blt	2f
vld1.32	{d6[0]}, [r0:32], r2
vld1.32	{d6[1]}, [r0:32], r2
vmlal.u8	q10, d0, d6
pld	[r0]
vld1.32	{d7[0]}, [r1:32], r2
vld1.32	{d7[1]}, [r1:32], r2
vmlal.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r6:32], r2
vst1.32	{d4[1]}, [r6:32], r2
bne	1b
pop	{r4, r5, r6, pc}
2:
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
pop	{r4, r5, r6, pc}
20:
rsb.w	r4, r4, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x4
vld1.32	{d4[0]}, [r0:32], r2
vld1.32	{d4[1]}, [r0:32], r2
vmlsl.u8	q1, d0, d4
pld	[r0]
vld1.32	{d5[0]}, [r1:32], r2
vld1.32	{d5[1]}, [r1:32], r2
vmlal.u8	q1, d1, d5
pld	[r1]
blt	2f
vld1.32	{d6[0]}, [r0:32], r2
vld1.32	{d6[1]}, [r0:32], r2
vmlsl.u8	q10, d0, d6
pld	[r0]
vld1.32	{d7[0]}, [r1:32], r2
vld1.32	{d7[1]}, [r1:32], r2
vmlal.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r6:32], r2
vst1.32	{d4[1]}, [r6:32], r2
bne	1b
pop	{r4, r5, r6, pc}
2:
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
pop	{r4, r5, r6, pc}
30:
rsb.w	r4, r4, #0x0
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x4
vld1.32	{d4[0]}, [r0:32], r2
vld1.32	{d4[1]}, [r0:32], r2
vmlsl.u8	q1, d0, d4
pld	[r0]
vld1.32	{d5[0]}, [r1:32], r2
vld1.32	{d5[1]}, [r1:32], r2
vmlsl.u8	q1, d1, d5
pld	[r1]
blt	2f
vld1.32	{d6[0]}, [r0:32], r2
vld1.32	{d6[1]}, [r0:32], r2
vmlsl.u8	q10, d0, d6
pld	[r0]
vld1.32	{d7[0]}, [r1:32], r2
vld1.32	{d7[1]}, [r1:32], r2
vmlsl.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r6:32], r2
vst1.32	{d4[1]}, [r6:32], r2
bne	1b
pop	{r4, r5, r6, pc}
2:
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
pop	{r4, r5, r6, pc}
40:
rsb.w	r5, r5, #0x0
vdup.8	d0, r4
vdup.8	d1, r5
vorr	q1, q8, q8
vorr	q10, q8, q8
1:
subs	r3, #0x4
vld1.32	{d4[0]}, [r0:32], r2
vld1.32	{d4[1]}, [r0:32], r2
vmlal.u8	q1, d0, d4
pld	[r0]
vld1.32	{d5[0]}, [r1:32], r2
vld1.32	{d5[1]}, [r1:32], r2
vmlsl.u8	q1, d1, d5
pld	[r1]
blt	2f
vld1.32	{d6[0]}, [r0:32], r2
vld1.32	{d6[1]}, [r0:32], r2
vmlal.u8	q10, d0, d6
pld	[r0]
vld1.32	{d7[0]}, [r1:32], r2
vld1.32	{d7[1]}, [r1:32], r2
vmlsl.u8	q10, d1, d7
pld	[r1]
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vshl.s16	q10, q10, q9
vqmovun.s16	d4, q10
vorr	q10, q8, q8
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
vorr	q1, q8, q8
vst1.32	{d4[0]}, [r6:32], r2
vst1.32	{d4[1]}, [r6:32], r2
bne	1b
pop	{r4, r5, r6, pc}
2:
vshl.s16	q1, q1, q9
vqmovun.s16	d2, q1
vst1.32	{d2[0]}, [r6:32], r2
vst1.32	{d2[1]}, [r6:32], r2
pop	{r4, r5, r6, pc}
nop
