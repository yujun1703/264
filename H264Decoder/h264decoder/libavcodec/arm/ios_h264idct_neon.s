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
function ff_h264_idct_add_neon
vld1.64	{d0, d1, d2, d3}, [r1:128]
vmov.i16	q15, #0x0
vswp	d1, d2
vst1.16	{d30, d31}, [r1:128]!
vadd.i16	d4, d0, d1
vst1.16	{d30, d31}, [r1:128]!
vshr.s16	q8, q1, #0x1
vsub.i16	d5, d0, d1
vadd.i16	d6, d2, d17
vsub.i16	d7, d16, d3
vadd.i16	q0, q2, q3
vsub.i16	q1, q2, q3
vtrn.16	d0, d1
vtrn.16	d3, d2
vtrn.32	d0, d3
vtrn.32	d1, d2
vadd.i16	d4, d0, d3
vld1.32	{d18[0]}, [r0:32], r2
vswp	d1, d3
vshr.s16	q8, q1, #0x1
vld1.32	{d19[1]}, [r0:32], r2
vsub.i16	d5, d0, d1
vld1.32	{d18[1]}, [r0:32], r2
vadd.i16	d6, d16, d3
vld1.32	{d19[0]}, [r0:32], r2
vsub.i16	d7, d2, d17
sub.w	r0, r0, r2, lsl #2
vadd.i16	q0, q2, q3
vsub.i16	q1, q2, q3
vrshr.s16	q0, q0, #0x6
vrshr.s16	q1, q1, #0x6
vaddw.u8	q0, q0, d18
vaddw.u8	q1, q1, d19
vqmovun.s16	d0, q0
vqmovun.s16	d1, q1
vst1.32	{d0[0]}, [r0:32], r2
vst1.32	{d1[1]}, [r0:32], r2
vst1.32	{d0[1]}, [r0:32], r2
vst1.32	{d1[0]}, [r0:32], r2
sub.w	r1, r1, #0x20
bx	lr


function ff_h264_idct_dc_add_neon
mov.w	r3, #0x0
vld1.16	{d2[], d3[]}, [r1:16]
strh	r3, [r1]
vrshr.s16	q1, q1, #0x6
vld1.32	{d0[0]}, [r0:32], r2
vld1.32	{d0[1]}, [r0:32], r2
vaddw.u8	q2, q1, d0
vld1.32	{d1[0]}, [r0:32], r2
vld1.32	{d1[1]}, [r0:32], r2
vaddw.u8	q1, q1, d1
vqmovun.s16	d0, q2
vqmovun.s16	d1, q1
sub.w	r0, r0, r2, lsl #2
vst1.32	{d0[0]}, [r0:32], r2
vst1.32	{d0[1]}, [r0:32], r2
vst1.32	{d1[0]}, [r0:32], r2
vst1.32	{d1[1]}, [r0:32], r2
bx	lr

function ff_h264_idct8_add_neon
vmov.i16	q7, #0x0
vld1.16	{d16, d17, d18, d19}, [r1:128]
vst1.16	{d14, d15}, [r1:128]!
vst1.16	{d14, d15}, [r1:128]!
vld1.16	{d20, d21, d22, d23}, [r1:128]
vst1.16	{d14, d15}, [r1:128]!
vst1.16	{d14, d15}, [r1:128]!
vld1.16	{d24, d25, d26, d27}, [r1:128]
vst1.16	{d14, d15}, [r1:128]!
vst1.16	{d14, d15}, [r1:128]!
vshr.s16	q2, q10, #0x1
vadd.i16	q0, q8, q12
vld1.16	{d28, d29, d30, d31}, [r1:128]
vst1.16	{d14, d15}, [r1:128]!
vst1.16	{d14, d15}, [r1:128]!
vsub.i16	q1, q8, q12
vshr.s16	q3, q14, #0x1
vsub.i16	q2, q2, q14
vadd.i16	q3, q3, q10
vadd.i16	q10, q1, q2
vsub.i16	q12, q1, q2
vadd.i16	q8, q0, q3
vsub.i16	q14, q0, q3
vsub.i16	q0, q13, q11
vadd.i16	q1, q15, q9
vsub.i16	q2, q15, q9
vadd.i16	q3, q13, q11
vsub.i16	q0, q0, q15
vsub.i16	q1, q1, q11
vadd.i16	q2, q2, q13
vadd.i16	q3, q3, q9
vshr.s16	q9, q9, #0x1
vshr.s16	q11, q11, #0x1
vshr.s16	q13, q13, #0x1
vshr.s16	q15, q15, #0x1
vsub.i16	q0, q0, q15
vsub.i16	q1, q1, q11
vadd.i16	q2, q2, q13
vadd.i16	q3, q3, q9
vshr.s16	q9, q0, #0x2
vshr.s16	q11, q1, #0x2
vshr.s16	q13, q2, #0x2
vshr.s16	q15, q3, #0x2
vsub.i16	q3, q3, q9
vsub.i16	q2, q11, q2
vadd.i16	q1, q1, q13
vadd.i16	q0, q0, q15
vsub.i16	q15, q8, q3
vadd.i16	q8, q8, q3
vadd.i16	q9, q10, q2
vsub.i16	q2, q10, q2
vtrn.16	q8, q9
vadd.i16	q10, q12, q1
vtrn.16	q2, q15
vadd.i16	q11, q14, q0
vsub.i16	q13, q12, q1
vtrn.16	q10, q11
vsub.i16	q12, q14, q0
vtrn.32	q8, q10
vtrn.16	q12, q13
vtrn.32	q9, q11
vtrn.32	q12, q2
vtrn.32	q13, q15
vswp	d21, d4
vshr.s16	q14, q10, #0x1
vswp	d17, d24
vshr.s16	q3, q2, #0x1
vswp	d19, d26
vadd.i16	q0, q8, q12
vswp	d23, d30
vsub.i16	q1, q8, q12
vsub.i16	q14, q14, q2
vadd.i16	q3, q3, q10
vadd.i16	q10, q1, q14
vsub.i16	q12, q1, q14
vadd.i16	q8, q0, q3
vsub.i16	q2, q0, q3
vsub.i16	q0, q13, q11
vadd.i16	q1, q15, q9
vsub.i16	q14, q15, q9
vadd.i16	q3, q13, q11
vsub.i16	q0, q0, q15
vsub.i16	q1, q1, q11
vadd.i16	q14, q14, q13
vadd.i16	q3, q3, q9
vshr.s16	q9, q9, #0x1
vshr.s16	q11, q11, #0x1
vshr.s16	q13, q13, #0x1
vshr.s16	q15, q15, #0x1
vsub.i16	q0, q0, q15
vsub.i16	q1, q1, q11
vadd.i16	q14, q14, q13
vadd.i16	q3, q3, q9
vshr.s16	q9, q0, #0x2
vshr.s16	q11, q1, #0x2
vshr.s16	q13, q14, #0x2
vshr.s16	q15, q3, #0x2
vsub.i16	q3, q3, q9
vsub.i16	q14, q11, q14
vadd.i16	q1, q1, q13
vadd.i16	q0, q0, q15
vsub.i16	q15, q8, q3
vadd.i16	q8, q8, q3
vadd.i16	q9, q10, q14
vsub.i16	q14, q10, q14
vadd.i16	q10, q12, q1
vsub.i16	q13, q12, q1
vadd.i16	q11, q2, q0
vsub.i16	q12, q2, q0
mov	r3, r0
vrshr.s16	q8, q8, #0x6
vld1.8	{d0}, [r0:64], r2
vrshr.s16	q9, q9, #0x6
vld1.8	{d1}, [r0:64], r2
vrshr.s16	q10, q10, #0x6
vld1.8	{d2}, [r0:64], r2
vrshr.s16	q11, q11, #0x6
vld1.8	{d3}, [r0:64], r2
vrshr.s16	q12, q12, #0x6
vld1.8	{d4}, [r0:64], r2
vrshr.s16	q13, q13, #0x6
vld1.8	{d5}, [r0:64], r2
vrshr.s16	q14, q14, #0x6
vld1.8	{d6}, [r0:64], r2
vrshr.s16	q15, q15, #0x6
vld1.8	{d7}, [r0:64], r2
vaddw.u8	q8, q8, d0
vaddw.u8	q9, q9, d1
vaddw.u8	q10, q10, d2
vqmovun.s16	d0, q8
vaddw.u8	q11, q11, d3
vqmovun.s16	d1, q9
vaddw.u8	q12, q12, d4
vqmovun.s16	d2, q10
vst1.8	{d0}, [r3:64], r2
vaddw.u8	q13, q13, d5
vqmovun.s16	d3, q11
vst1.8	{d1}, [r3:64], r2
vaddw.u8	q14, q14, d6
vqmovun.s16	d4, q12
vst1.8	{d2}, [r3:64], r2
vaddw.u8	q15, q15, d7
vqmovun.s16	d5, q13
vst1.8	{d3}, [r3:64], r2
vqmovun.s16	d6, q14
vqmovun.s16	d7, q15
vst1.8	{d4}, [r3:64], r2
vst1.8	{d5}, [r3:64], r2
vst1.8	{d6}, [r3:64], r2
vst1.8	{d7}, [r3:64], r2
sub.w	r1, r1, #0x80
bx	lr

function ff_h264_idct8_dc_add_neon
mov.w	r3, #0x0
vld1.16	{d30[], d31[]}, [r1:16]
strh	r3, [r1]
vld1.32	{d0}, [r0:64], r2
vrshr.s16	q15, q15, #0x6
vld1.32	{d1}, [r0:64], r2
vld1.32	{d2}, [r0:64], r2
vaddw.u8	q8, q15, d0
vld1.32	{d3}, [r0:64], r2
vaddw.u8	q9, q15, d1
vld1.32	{d4}, [r0:64], r2
vaddw.u8	q10, q15, d2
vld1.32	{d5}, [r0:64], r2
vaddw.u8	q11, q15, d3
vld1.32	{d6}, [r0:64], r2
vaddw.u8	q12, q15, d4
vld1.32	{d7}, [r0:64], r2
vaddw.u8	q13, q15, d5
vaddw.u8	q14, q15, d6
vaddw.u8	q15, q15, d7
vqmovun.s16	d0, q8
vqmovun.s16	d1, q9
vqmovun.s16	d2, q10
vqmovun.s16	d3, q11
sub.w	r0, r0, r2, lsl #3
vst1.32	{d0}, [r0:64], r2
vqmovun.s16	d4, q12
vst1.32	{d1}, [r0:64], r2
vqmovun.s16	d5, q13
vst1.32	{d2}, [r0:64], r2
vqmovun.s16	d6, q14
vst1.32	{d3}, [r0:64], r2
vqmovun.s16	d7, q15
vst1.32	{d4}, [r0:64], r2
vst1.32	{d5}, [r0:64], r2
vst1.32	{d6}, [r0:64], r2
vst1.32	{d7}, [r0:64], r2
bx	lr
