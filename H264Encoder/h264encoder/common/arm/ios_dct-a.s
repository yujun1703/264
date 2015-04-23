//
//  ios_cpu-a.s
//  x264EncLib
//
//  Created by sensong on 13-5-15.
//  Copyright (c) 2013年 com.tencent.avteam. All rights reserved.
//

.macro function name
.global _\name
.align 2
_\name:
@ .hidden \name
@ .type \name, %function
@.func \name
@ \name:
.endm





.macro HORIZ_ADD dest, a, b
.ifnb \b
vadd.u16 \a, \a, \b
.endif
vpaddl.u16 \a, \a
vpaddl.u32 \dest, \a
.endm

.macro SUMSUB_AB sum, diff, a, b
vadd.s16 \sum, \a, \b
vsub.s16 \diff, \a, \b
.endm

.macro SUMSUB_ABCD s1, d1, s2, d2, a, b, c, d
SUMSUB_AB \s1, \d1, \a, \b
SUMSUB_AB \s2, \d2, \c, \d
.endm

.macro ABS2 a b
vabs.s16 \a, \a
vabs.s16 \b, \b
.endm





.macro HADAMARD dist, op, d1, d2, s1, s2
.if \dist == 1
vtrn.16 \s1, \s2
.else
vtrn.32 \s1, \s2
.endif
.ifc \op, sumsub
SUMSUB_AB \d1, \d2, \s1, \s2
.else
vabs.s16 \s1, \s1
vabs.s16 \s2, \s2
vmax.s16 \d1, \s1, \s2
.endif
.endm

.macro TRANSPOSE8x8 r0 r1 r2 r3 r4 r5 r6 r7
vtrn.32 \r0, \r4
vtrn.32 \r1, \r5
vtrn.32 \r2, \r6
vtrn.32 \r3, \r7
vtrn.16 \r0, \r2
vtrn.16 \r1, \r3
vtrn.16 \r4, \r6
vtrn.16 \r5, \r7
vtrn.8 \r0, \r1
vtrn.8 \r2, \r3
vtrn.8 \r4, \r5
vtrn.8 \r6, \r7
.endm

.macro TRANSPOSE4x4 r0 r1 r2 r3
vtrn.16 \r0, \r2
vtrn.16 \r1, \r3
vtrn.8 \r0, \r1
vtrn.8 \r2, \r3
.endm

.macro TRANSPOSE4x4_16 d0 d1 d2 d3
vtrn.32 \d0, \d2
vtrn.32 \d1, \d3
vtrn.16 \d0, \d1
vtrn.16 \d2, \d3
.endm
# 27 "common/arm/dct-a.S" 2





.text


.macro SUMSUB_SHR shift sum sub a b t0 t1
vshr.s16 \t0, \b, #\shift
vshr.s16 \t1, \a, #\shift
vadd.s16 \sum, \a, \t0
vsub.s16 \sub, \t1, \b
.endm


.macro SUMSUB_SHR2 shift sum sub a b t0 t1
vshr.s16 \t0, \a, #\shift
vshr.s16 \t1, \b, #\shift
vadd.s16 \sum, \t0, \b
vsub.s16 \sub, \a, \t1
.endm


.macro SUMSUB_15 a b ma mb t0 t1
vshr.s16 \t0, \ma, #1
vshr.s16 \t1, \mb, #1
vadd.s16 \t0, \t0, \ma
vadd.s16 \t1, \t1, \mb
vadd.s16 \a, \a, \t0
vsub.s16 \b, \b, \t1
.endm


function x264_dct4x4dc_neon
vld1.64 {d0-d3}, [r0,:128]
SUMSUB_ABCD d4, d5, d6, d7, d0, d1, d2, d3
SUMSUB_ABCD d0, d2, d3, d1, d4, d6, d5, d7

vmov.s16 d31, #1
HADAMARD 1, sumsub, q2, q3, q0, q1
vtrn.32 d4, d5
vadd.s16 d16, d4, d31
vtrn.32 d6, d7
vadd.s16 d17, d6, d31
vrhadd.s16 d0, d4, d5
vhsub.s16 d1, d16, d5
vhsub.s16 d2, d17, d7
vrhadd.s16 d3, d6, d7
vst1.64 {d0-d3}, [r0,:128]
bx lr


function x264_idct4x4dc_neon
vld1.64 {d0-d3}, [r0,:128]
SUMSUB_ABCD d4, d5, d6, d7, d0, d1, d2, d3
SUMSUB_ABCD d0, d2, d3, d1, d4, d6, d5, d7

HADAMARD 1, sumsub, q2, q3, q0, q1
HADAMARD 2, sumsub, d0, d1, d4, d5
HADAMARD 2, sumsub, d3, d2, d6, d7
vst1.64 {d0-d3}, [r0,:128]
bx lr



.macro DCT_1D d0 d1 d2 d3 d4 d5 d6 d7
SUMSUB_AB \d1, \d6, \d5, \d6
SUMSUB_AB \d3, \d7, \d4, \d7
vadd.s16 \d0, \d3, \d1
vadd.s16 \d4, \d7, \d7
vadd.s16 \d5, \d6, \d6
vsub.s16 \d2, \d3, \d1
vadd.s16 \d1, \d4, \d6
vsub.s16 \d3, \d7, \d5
.endm

function x264_sub4x4_dct_neon
mov r3, #16
mov ip, #32
vld1.32 {d0[]}, [r1,:32], r3
vld1.32 {d1[]}, [r2,:32], ip
vld1.32 {d2[]}, [r1,:32], r3
vsubl.u8 q8, d0, d1
vld1.32 {d3[]}, [r2,:32], ip
vld1.32 {d4[]}, [r1,:32], r3
vsubl.u8 q9, d2, d3
vld1.32 {d5[]}, [r2,:32], ip
vld1.32 {d6[]}, [r1,:32], r3
vsubl.u8 q10, d4, d5
vld1.32 {d7[]}, [r2,:32], ip
vsubl.u8 q11, d6, d7

DCT_1D d0, d1, d2, d3, d16, d18, d20, d22
TRANSPOSE4x4_16 d0, d1, d2, d3
DCT_1D d4, d5, d6, d7, d0, d1, d2, d3
vst1.64 {d4-d7}, [r0,:128]
bx lr


function x264_sub8x4_dct_neon
vld1.64 {d0}, [r1,:64], r3
vld1.64 {d1}, [r2,:64], ip
vsubl.u8 q8, d0, d1
vld1.64 {d2}, [r1,:64], r3
vld1.64 {d3}, [r2,:64], ip
vsubl.u8 q9, d2, d3
vld1.64 {d4}, [r1,:64], r3
vld1.64 {d5}, [r2,:64], ip
vsubl.u8 q10, d4, d5
vld1.64 {d6}, [r1,:64], r3
vld1.64 {d7}, [r2,:64], ip
vsubl.u8 q11, d6, d7

DCT_1D q0, q1, q2, q3, q8, q9, q10, q11
TRANSPOSE4x4_16 q0, q1, q2, q3

SUMSUB_AB q8, q12, q0, q3
SUMSUB_AB q9, q10, q1, q2
vadd.i16 q13, q12, q12
vadd.i16 q11, q10, q10
vadd.i16 d0, d16, d18
vadd.i16 d1, d26, d20
vsub.i16 d2, d16, d18
vsub.i16 d3, d24, d22
vst1.64 {d0-d1}, [r0,:128]!
vadd.i16 d4, d17, d19
vadd.i16 d5, d27, d21
vst1.64 {d2-d3}, [r0,:128]!
vsub.i16 d6, d17, d19
vsub.i16 d7, d25, d23
vst1.64 {d4-d5}, [r0,:128]!
vst1.64 {d6-d7}, [r0,:128]!
bx lr


function x264_sub8x8_dct_neon
push {lr}
mov r3, #16
mov ip, #32
bl _x264_sub8x4_dct_neon
pop {lr}
b _x264_sub8x4_dct_neon


function x264_sub16x16_dct_neon
push {lr}
mov r3, #16
mov ip, #32
bl _x264_sub8x4_dct_neon
bl _x264_sub8x4_dct_neon
sub r1, r1, #8*16 -8
sub r2, r2, #8*32 -8
bl _x264_sub8x4_dct_neon
bl _x264_sub8x4_dct_neon
sub r1, r1, #8
sub r2, r2, #8
bl _x264_sub8x4_dct_neon
bl _x264_sub8x4_dct_neon
sub r1, r1, #8*16 -8
sub r2, r2, #8*32 -8
bl _x264_sub8x4_dct_neon
pop {lr}
b _x264_sub8x4_dct_neon



.macro DCT8_1D type
SUMSUB_AB q2, q1, q11, q12
SUMSUB_AB q3, q11, q10, q13
SUMSUB_AB q13, q10, q9, q14
SUMSUB_AB q14, q8, q8, q15

SUMSUB_AB q9, q2, q14, q2
SUMSUB_AB q12, q14, q13, q3

SUMSUB_AB q3, q13, q8, q1
vshr.s16 q0, q10, #1
vshr.s16 q15, q11, #1
vadd.s16 q0, q0, q10
vadd.s16 q15, q15, q11
vsub.s16 q3, q3, q0
vsub.s16 q13, q13, q15

SUMSUB_AB q0, q15, q10, q11
vshr.s16 q10, q8, #1
vshr.s16 q11, q1, #1
vadd.s16 q10, q10, q8
vadd.s16 q11, q11, q1
vadd.s16 q10, q0, q10
vadd.s16 q15, q15, q11

SUMSUB_AB q8, q12, q9, q12
SUMSUB_SHR 2, q9, q15, q10, q15, q0, q1
SUMSUB_SHR 1, q10, q14, q2, q14, q0, q1
SUMSUB_SHR2 2, q11, q13, q3, q13, q0, q1
.endm

function x264_sub8x8_dct8_neon
mov r3, #16
mov ip, #32
vld1.64 {d16}, [r1,:64], r3
vld1.64 {d17}, [r2,:64], ip
vsubl.u8 q8, d16, d17
vld1.64 {d18}, [r1,:64], r3
vld1.64 {d19}, [r2,:64], ip
vsubl.u8 q9, d18, d19
vld1.64 {d20}, [r1,:64], r3
vld1.64 {d21}, [r2,:64], ip
vsubl.u8 q10, d20, d21
vld1.64 {d22}, [r1,:64], r3
vld1.64 {d23}, [r2,:64], ip
vsubl.u8 q11, d22, d23
vld1.64 {d24}, [r1,:64], r3
vld1.64 {d25}, [r2,:64], ip
vsubl.u8 q12, d24, d25
vld1.64 {d26}, [r1,:64], r3
vld1.64 {d27}, [r2,:64], ip
vsubl.u8 q13, d26, d27
vld1.64 {d28}, [r1,:64], r3
vld1.64 {d29}, [r2,:64], ip
vsubl.u8 q14, d28, d29
vld1.64 {d30}, [r1,:64], r3
vld1.64 {d31}, [r2,:64], ip
vsubl.u8 q15, d30, d31

DCT8_1D row
vswp d17, d24
vswp d21, d28
vtrn.32 q8, q10
vtrn.32 q12, q14

vswp d19, d26
vswp d23, d30
vtrn.32 q9, q11
vtrn.32 q13, q15

vtrn.16 q10, q11
vtrn.16 q12, q13
vtrn.16 q8, q9
vtrn.16 q14, q15
DCT8_1D col

vst1.64 {d16-d19}, [r0,:128]!
vst1.64 {d20-d23}, [r0,:128]!
vst1.64 {d24-d27}, [r0,:128]!
vst1.64 {d28-d31}, [r0,:128]!
bx lr


function x264_sub16x16_dct8_neon
push {lr}
bl _x264_sub8x8_dct8_neon
sub r1, r1, #16*8 - 8
sub r2, r2, #32*8 - 8
bl _x264_sub8x8_dct8_neon
sub r1, r1, #8
sub r2, r2, #8
bl _x264_sub8x8_dct8_neon
pop {lr}
sub r1, r1, #16*8 - 8
sub r2, r2, #32*8 - 8
b _x264_sub8x8_dct8_neon




.macro IDCT_1D d4 d5 d6 d7 d0 d1 d2 d3
SUMSUB_AB \d4, \d5, \d0, \d2
vshr.s16 \d7, \d1, #1
vshr.s16 \d6, \d3, #1
vsub.s16 \d7, \d7, \d3
vadd.s16 \d6, \d6, \d1
.endm

function x264_add4x4_idct_neon
mov r2, #32
vld1.64 {d0-d3}, [r1,:128]

IDCT_1D d4, d5, d6, d7, d0, d1, d2, d3
vld1.32 {d30[0]}, [r0,:32], r2
SUMSUB_AB q0, q1, q2, q3

TRANSPOSE4x4_16 d0, d1, d3, d2

IDCT_1D d4, d5, d6, d7, d0, d1, d3, d2
vld1.32 {d30[1]}, [r0,:32], r2
SUMSUB_AB q0, q1, q2, q3

vrshr.s16 q0, q0, #6
vld1.32 {d31[1]}, [r0,:32], r2
vrshr.s16 q1, q1, #6
vld1.32 {d31[0]}, [r0,:32], r2

sub r0, r0, r2, lsl #2
vaddw.u8 q0, q0, d30
vaddw.u8 q1, q1, d31
vqmovun.s16 d0, q0
vqmovun.s16 d2, q1

vst1.32 {d0[0]}, [r0,:32], r2
vst1.32 {d0[1]}, [r0,:32], r2
vst1.32 {d2[1]}, [r0,:32], r2
vst1.32 {d2[0]}, [r0,:32], r2
bx lr


function x264_add8x4_idct_neon
vld1.64 {d0-d3}, [r1,:128]!
IDCT_1D d16, d18, d20, d22, d0, d1, d2, d3
vld1.64 {d4-d7}, [r1,:128]!
IDCT_1D d17, d19, d21, d23, d4, d5, d6, d7
SUMSUB_AB q0, q3, q8, q10
SUMSUB_AB q1, q2, q9, q11

TRANSPOSE4x4_16 q0, q1, q2, q3

IDCT_1D q8, q9, q10, q11, q0, q1, q2, q3
SUMSUB_AB q0, q3, q8, q10
SUMSUB_AB q1, q2, q9, q11

vrshr.s16 q0, q0, #6
vld1.32 {d28}, [r0,:64], r2
vrshr.s16 q1, q1, #6
vld1.32 {d29}, [r0,:64], r2
vrshr.s16 q2, q2, #6
vld1.32 {d30}, [r0,:64], r2
vrshr.s16 q3, q3, #6
vld1.32 {d31}, [r0,:64], r2

sub r0, r0, r2, lsl #2
vaddw.u8 q0, q0, d28
vaddw.u8 q1, q1, d29
vaddw.u8 q2, q2, d30
vaddw.u8 q3, q3, d31

vqmovun.s16 d0, q0
vqmovun.s16 d1, q1
vst1.32 {d0}, [r0,:64], r2
vqmovun.s16 d2, q2
vst1.32 {d1}, [r0,:64], r2
vqmovun.s16 d3, q3
vst1.32 {d2}, [r0,:64], r2
vst1.32 {d3}, [r0,:64], r2
bx lr


function x264_add8x8_idct_neon
mov r2, #32
mov ip, lr
bl _x264_add8x4_idct_neon
mov lr, ip
b _x264_add8x4_idct_neon


function x264_add16x16_idct_neon
mov r2, #32
mov ip, lr
bl _x264_add8x4_idct_neon
bl _x264_add8x4_idct_neon
sub r0, r0, #8*32 -8
bl _x264_add8x4_idct_neon
bl _x264_add8x4_idct_neon
sub r0, r0, #8
bl _x264_add8x4_idct_neon
bl _x264_add8x4_idct_neon
sub r0, r0, #8*32 -8
bl _x264_add8x4_idct_neon
mov lr, ip
b _x264_add8x4_idct_neon



.macro IDCT8_1D type
.ifc \type, col
vswp d21, d28
.endif
SUMSUB_AB q0, q1, q8, q12
.ifc \type, row
vld1.64 {d28-d31}, [r1,:128]!
.else
vswp d19, d26
.endif
SUMSUB_SHR 1, q2, q3, q10, q14, q8, q12
.ifc \type, col
vswp d23, d30
.endif
SUMSUB_AB q8, q10, q13, q11
SUMSUB_15 q8, q10, q9, q15, q12, q14
SUMSUB_AB q14, q15, q15, q9
SUMSUB_15 q15, q14, q13, q11, q12, q9

SUMSUB_SHR 2, q13, q14, q14, q15, q11, q9
SUMSUB_SHR2 2, q12, q15, q8, q10, q11, q9

SUMSUB_AB q10, q2, q0, q2
SUMSUB_AB q11, q3, q1, q3

SUMSUB_AB q8, q15, q10, q15
SUMSUB_AB q9, q14, q11, q14
SUMSUB_AB q10, q13, q3, q13
.ifc \type, row
vtrn.16 q8, q9
.endif
SUMSUB_AB q11, q12, q2, q12
.endm

function x264_add8x8_idct8_neon
mov r2, #32
vld1.64 {d16-d19}, [r1,:128]!
vld1.64 {d20-d23}, [r1,:128]!
vld1.64 {d24-d27}, [r1,:128]!

IDCT8_1D row
vtrn.16 q10, q11
vtrn.16 q12, q13
vtrn.16 q14, q15
vtrn.32 q8, q10
vtrn.32 q9, q11
vtrn.32 q12, q14
vtrn.32 q13, q15
vswp d17, d24
IDCT8_1D col

vld1.64 {d0}, [r0,:64], r2
vrshr.s16 q8, q8, #6
vld1.64 {d1}, [r0,:64], r2
vrshr.s16 q9, q9, #6
vld1.64 {d2}, [r0,:64], r2
vrshr.s16 q10, q10, #6
vld1.64 {d3}, [r0,:64], r2
vrshr.s16 q11, q11, #6
vld1.64 {d4}, [r0,:64], r2
vrshr.s16 q12, q12, #6
vld1.64 {d5}, [r0,:64], r2
vrshr.s16 q13, q13, #6
vld1.64 {d6}, [r0,:64], r2
vrshr.s16 q14, q14, #6
vld1.64 {d7}, [r0,:64], r2
vrshr.s16 q15, q15, #6
sub r0, r0, r2, lsl #3

vaddw.u8 q8, q8, d0
vaddw.u8 q9, q9, d1
vaddw.u8 q10, q10, d2
vqmovun.s16 d0, q8
vqmovun.s16 d1, q9
vqmovun.s16 d2, q10
vaddw.u8 q11, q11, d3
vst1.64 {d0}, [r0,:64], r2
vaddw.u8 q12, q12, d4
vst1.64 {d1}, [r0,:64], r2
vaddw.u8 q13, q13, d5
vst1.64 {d2}, [r0,:64], r2
vqmovun.s16 d3, q11
vqmovun.s16 d4, q12
vaddw.u8 q14, q14, d6
vaddw.u8 q15, q15, d7
vst1.64 {d3}, [r0,:64], r2
vqmovun.s16 d5, q13
vst1.64 {d4}, [r0,:64], r2
vqmovun.s16 d6, q14
vqmovun.s16 d7, q15
vst1.64 {d5}, [r0,:64], r2
vst1.64 {d6}, [r0,:64], r2
vst1.64 {d7}, [r0,:64], r2
bx lr


function x264_add16x16_idct8_neon
mov ip, lr
bl _x264_add8x8_idct8_neon
sub r0, r0, #8*32 -8
bl _x264_add8x8_idct8_neon
sub r0, r0, #8
bl _x264_add8x8_idct8_neon
sub r0, r0, #8*32 -8
mov lr, ip
b _x264_add8x8_idct8_neon



function x264_add8x8_idct_dc_neon
mov r2, #32
vld1.64 {d16}, [r1,:64]
vrshr.s16 d16, d16, #6
vld1.64 {d0}, [r0,:64], r2
vmov.i16 q15, #0
vld1.64 {d1}, [r0,:64], r2
vld1.64 {d2}, [r0,:64], r2
vdup.16 d20, d16[0]
vld1.64 {d3}, [r0,:64], r2
vdup.16 d21, d16[1]
vld1.64 {d4}, [r0,:64], r2
vdup.16 d22, d16[2]
vld1.64 {d5}, [r0,:64], r2
vdup.16 d23, d16[3]
vld1.64 {d6}, [r0,:64], r2
vsub.s16 q12, q15, q10
vld1.64 {d7}, [r0,:64], r2
vsub.s16 q13, q15, q11

sub r0, r0, #8*32

vqmovun.s16 d20, q10
vqmovun.s16 d22, q11
vqmovun.s16 d24, q12
vqmovun.s16 d26, q13

vmov d21, d20
vqadd.u8 q0, q0, q10
vmov d23, d22
vqadd.u8 q1, q1, q10
vmov d25, d24
vqadd.u8 q2, q2, q11
vmov d27, d26
vqadd.u8 q3, q3, q11
vqsub.u8 q0, q0, q12
vqsub.u8 q1, q1, q12
vqsub.u8 q2, q2, q13

vst1.64 {d0}, [r0,:64], r2
vqsub.u8 q3, q3, q13
vst1.64 {d1}, [r0,:64], r2
vst1.64 {d2}, [r0,:64], r2
vst1.64 {d3}, [r0,:64], r2
vst1.64 {d4}, [r0,:64], r2
vst1.64 {d5}, [r0,:64], r2
vst1.64 {d6}, [r0,:64], r2
vst1.64 {d7}, [r0,:64], r2
bx lr


.macro ADD16x4_IDCT_DC dc
vld1.64 {d16-d17}, [r0,:128], r3
vld1.64 {d18-d19}, [r0,:128], r3
vdup.16 d4, \dc[0]
vdup.16 d5, \dc[1]
vld1.64 {d20-d21}, [r0,:128], r3
vdup.16 d6, \dc[2]
vdup.16 d7, \dc[3]
vld1.64 {d22-d23}, [r0,:128], r3
vsub.s16 q12, q15, q2
vsub.s16 q13, q15, q3

vqmovun.s16 d4, q2
vqmovun.s16 d5, q3
vqmovun.s16 d6, q12
vqmovun.s16 d7, q13

vqadd.u8 q8, q8, q2
vqadd.u8 q9, q9, q2
vqadd.u8 q10, q10, q2
vqadd.u8 q11, q11, q2

vqsub.u8 q8, q8, q3
vqsub.u8 q9, q9, q3
vqsub.u8 q10, q10, q3
vst1.64 {d16-d17}, [r2,:128], r3
vqsub.u8 q11, q11, q3
vst1.64 {d18-d19}, [r2,:128], r3
vst1.64 {d20-d21}, [r2,:128], r3
vst1.64 {d22-d23}, [r2,:128], r3
.endm

function x264_add16x16_idct_dc_neon
mov r2, r0
mov r3, #32
vmov.i16 q15, #0

vld1.64 {d0-d3}, [r1,:64]
vrshr.s16 q0, #6
vrshr.s16 q1, #6

ADD16x4_IDCT_DC d0
ADD16x4_IDCT_DC d1
ADD16x4_IDCT_DC d2
ADD16x4_IDCT_DC d3
bx lr


function x264_sub8x8_dct_dc_neon
mov r3, #16
mov ip, #32
vld1.64 {d16}, [r1,:64], r3
vld1.64 {d17}, [r2,:64], ip
vsubl.u8 q8, d16, d17
vld1.64 {d18}, [r1,:64], r3
vld1.64 {d19}, [r2,:64], ip
vsubl.u8 q9, d18, d19
vld1.64 {d20}, [r1,:64], r3
vld1.64 {d21}, [r2,:64], ip
vsubl.u8 q10, d20, d21
vld1.64 {d22}, [r1,:64], r3
vadd.s16 q0, q8, q9
vld1.64 {d23}, [r2,:64], ip
vsubl.u8 q11, d22, d23
vld1.64 {d24}, [r1,:64], r3
vadd.s16 q0, q0, q10
vld1.64 {d25}, [r2,:64], ip
vsubl.u8 q12, d24, d25
vld1.64 {d26}, [r1,:64], r3
vadd.s16 q0, q0, q11
vld1.64 {d27}, [r2,:64], ip
vsubl.u8 q13, d26, d27
vld1.64 {d28}, [r1,:64], r3
vld1.64 {d29}, [r2,:64], ip
vsubl.u8 q14, d28, d29
vld1.64 {d30}, [r1,:64], r3
vadd.s16 q1, q12, q13
vld1.64 {d31}, [r2,:64], ip
vsubl.u8 q15, d30, d31
vadd.s16 q1, q1, q14

vadd.s16 d4, d0, d1
vadd.s16 q1, q1, q15
vsub.s16 d5, d0, d1
vadd.s16 d6, d2, d3
vsub.s16 d7, d2, d3
vadd.s16 q0, q2, q3
vsub.s16 q1, q2, q3

vpadd.s16 d0, d0, d2
vpadd.s16 d1, d1, d3
vpadd.s16 d0, d0, d1
vst1.64 {d0}, [r0,:64]
bx lr


.align 4
scan4x4_frame:
.byte 0,1, 8,9, 2,3, 4,5
.byte 2,3, 8,9, 16,17, 10,11
.byte 12,13, 6,7, 14,15, 20,21
.byte 10,11, 12,13, 6,7, 14,15

.text
function x264_zigzag_scan_4x4_frame_neon
adr r2, scan4x4_frame
vld1.64 {d0-d3}, [r1,:128]
vld1.64 {d16-d19}, [r2,:128]
vtbl.8 d4, {d0-d1}, d16
vtbl.8 d5, {d1-d3}, d17
vtbl.8 d6, {d0-d2}, d18
vtbl.8 d7, {d2-d3}, d19
vst1.64 {d4-d7}, [r0,:128]
bx lr

